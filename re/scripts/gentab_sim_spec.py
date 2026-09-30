# Curated names/types for gentab_sim.py (exec'd inside it, so u32, DN, ... are available).
#
# NAMES     object start -> dict(sym=, type=, stride=(words), width=, signed=)
# FORCE     (start, end) extents that must stay one object (interior pointers/refs do not split it)
# OBJ_STARTS extra object boundaries
# TYPESPEC  record types: name -> [(field, kind[, count[, comment]])]
#           kind: L long, U unsigned long, S const char *, F function pointer, P void *, P=type  struct type *
# CUSTOM    (start, end, func(decls, bodies)): hand generated blocks replacing the auto objects
import collections

NAMES = {}
OBJ_STARTS = []
FIELDNAMES = {}
FORCE = []
TYPESPEC = collections.OrderedDict()
CUSTOM = []
HEADER_PRE = []


def _ts(name, fields):
    TYPESPEC[name] = fields


# ------------------------------------------------------------------ device model (notes exec_a 1.1/1.2, devinit_asm 1.2)
_ts("dev_type", [
    ("name", "S", 1, "+0x00 device name"),
    ("magic", "L", 1, "+0x04 0x2c5 (DSP56000 COFF magic)"),
    ("family", "L", 1, "+0x08 family bit mask (1 56000, 2 56001, 4 56002, 8 56004, 0x108 56004rom, 0x44 56005, 0x200 56007, 0x400 56009, 0x1000 56011, 0x2000 56012, 0x80 68356, 0x800 56030)"),
    ("flags", "L", 1, "+0x0c 0x4000008"),
    ("f10", "L", 1, "+0x10"),
    ("n_periph", "L", 1, "+0x14 number of peripheral groups"),
    ("periph", "P=periph_desc", 1, "+0x18 group array"),
    ("n_map", "L", 1, "+0x1c number of memory regions"),
    ("map", "P=mem_region", 1, "+0x20 memory region array"),
    ("mem_name", "S", 1, "+0x24 DSPMEM"),
    ("vtable", "P=core_vtable", 1, "+0x28 core method table"),
    ("f2c", "L", 1, "+0x2c 0x1d"),
    ("f30", "L", 1, "+0x30"),
    ("mask_tab", "P", 1, "+0x34 per-space bit masks"),
    ("space_x", "L", 1, "+0x38 'X'"),
    ("vec_names", "P", 1, "+0x3c interrupt vector name records"),
    ("f40", "L", 1, "+0x40"),
    ("aux44", "P", 1, "+0x44"),
    ("reserved", "L", 293, "+0x48..+0x4d7 (region index per space at +0x4c, hooks at +0x4e0 in the runtime copy)"),
    ("key", "S", 1, "+0x4dc licence key text (keyed devices), set by device_install"),
])
_ts("periph_desc", [
    ("name", "S", 1, "+0x00 group name (core host ssi sci portb portc timer count sai shi emi gpio wdg pwm dax)"),
    ("pin_block", "L", 1, "+0x04 pin block index"),
    ("pin_mask", "U", 1, "+0x08"),
    ("f0c", "L", 1), ("f10", "L", 1),
    ("io_first", "L", 1, "+0x14"), ("io_count", "L", 1, "+0x18"), ("io_base", "L", 1, "+0x1c"),
    ("vec_base", "L", 1, "+0x20"), ("f24", "L", 1),
    ("prio_mask", "L", 1, "+0x28 IPR field mask"),
    ("def", "P=group_def", 1, "+0x2c group definition (method table)"),
    ("enable", "P", 1, "+0x30 empty string object"),
    ("res", "L", 5),
])
_ts("group_def", [
    ("peek", "F"), ("poke", "F"), ("io_read", "F"), ("io_write", "F"),
    ("clock", "F"), ("reset", "F"), ("irq_poll", "F"), ("irq_ack", "F"),
    ("f20", "L"), ("nstore", "L", 1, "+0x24 regs array size / storable registers"),
    ("nreg", "L", 1, "+0x28 number of registers"),
    ("regs", "P=reg_desc", 1, "+0x2c register table"),
    ("res", "L", 4),
])
_ts("reg_desc", [
    ("name", "S"), ("wmask", "U", 1, "write mask"), ("io_off", "L"), ("f0c", "U"),
    ("flags", "U", 1, "0x40 write side effects, 0x20 read side effects"), ("hint", "P"), ("index", "L"),
])
_ts("mem_region", [
    ("name", "S"), ("space", "L"), ("cls", "U"), ("lo", "L"), ("hi", "L"), ("f14", "L"),
    ("attr", "U", 1, "0x10000 peripheral mapped, 8 read only, 0x20000 holey"), ("f1c", "L"),
    ("size_m1", "L"), ("f24", "U"), ("f28", "L"),
])
_ts("core_vtable", [
    ("mem_read", "F"), ("mem_write", "F"), ("mem_write_n", "F"), ("region_of", "F"),
    ("omr_remap", "F"), ("reg_write_check", "F"), ("reg_read_check", "F"),
])

_devs = sorted(a for a, n in DN.items() if n[0].startswith("dev_") and n[2] == "1248")
for _a in _devs:
    FORCE.append((_a, _a + 0x4e0))
    NAMES[_a] = dict(type="dev_type", stride=312)
    _w = [u32(_a + 4 * i) for i in range(18)]
    NAMES[_w[6]] = dict(type="periph_desc", stride=18, sym="periph_%06x" % _w[6])
    NAMES[_w[8]] = dict(type="mem_region", stride=11, sym="regions_%06x" % _w[8])
    NAMES[_w[10]] = dict(type="core_vtable", stride=7)
    for _i in range(_w[5]):
        _d = u32(_w[6] + 72 * _i + 0x2c)
        if _d:
            NAMES[_d] = dict(type="group_def", stride=16, sym="grpdef_%06x" % _d)
            _r = u32(_d + 0x2c)
            if _r:
                NAMES[_r] = dict(type="reg_desc", stride=7, sym="regs_%06x" % _r)

# ------------------------------------------------------------------ opcode class table, mnemonic table
_ts("opclass_entry", [("mask", "U"), ("match", "U"), ("cls", "L"), ("flag", "L")])
FORCE.append((0x4c45b0, 0x4c4c80))
NAMES[0x4c45b0] = dict(type="opclass_entry", stride=4, sym="opclass_table")
_ts("mnem_entry", [("name", "S"), ("a", "L"), ("b", "L")])
FORCE.append((0x4c16f0, 0x4c1d80))
NAMES[0x4c16f0] = dict(type="mnem_entry", stride=3, sym="asm_mnem_table")

# ------------------------------------------------------------------ command table (cmd.md 3.2)
_ts("command_entry", [("name", "S"), ("abbrev", "S"), ("usage_name", "S"), ("help_lines", "P"),
                      ("arg_help", "P"), ("parse", "F"), ("f1", "L"), ("f2", "L")])
_ts("cmd_ptr", [("entry", "P=command_entry")])
NAMES[0x4a8c90] = dict(type="cmd_ptr", stride=1, sym="command_entries")
for _l in open(os.path.join(ROOT, "re", "notes", "SIM56000", "cmd.md"), encoding="utf-8").read().splitlines():
    _m = re.match(r'\| (\d+) \| (\w+) \| \w+ \| ([0-9a-f]+) \| ', _l)
    if _m:
        NAMES[int(_m.group(3), 16)] = dict(type="command_entry", stride=8, sym="cmd_entry_%s" % _m.group(2))


# ------------------------------------------------------------------ flex tables of the C expression lexer (cdblex)
_ts("yysvf", [("stoff", "L", 1, "index into yycrank (2-byte units, may be negative); YYNONE = NULL"),
              ("other", "P=yysvf", 1, "next state (pointer into yysvec)"),
              ("stops", "L", 1, "index into yyvstop; -1 = none")])
CUSTOM_LEX = (0x4d6dd4, 0x4d7970 + 4)


def _lex_block(decls, bodies):
    VS, CR, SV, TOP = 0x4d6dd4, 0x4d6fe8, 0x4d7520, 0x4d78e0
    nvs = (CR - VS) // 4
    o = []
    o.append("long yyvstop[%d] = { /* %08x */" % (nvs, VS))
    vals = [int_lit(u32(VS + 4 * i), False) for i in range(nvs)]
    for i in range(0, len(vals), 8):
        o.append("    " + ", ".join(vals[i:i + 8]) + ("," if i + 8 < len(vals) else ""))
    o.append("};")
    decls.append((VS, "extern long yyvstop[%d];" % nvs))
    ncr = (SV - CR)
    o.append("unsigned char yycrank[%d] = { /* %08x, pairs {verify, advance} */" % (ncr, CR))
    vals = ["%d" % b for b in rd(CR, ncr)]
    for i in range(0, len(vals), 16):
        o.append("    " + ", ".join(vals[i:i + 16]) + ("," if i + 16 < len(vals) else ""))
    o.append("};")
    decls.append((CR, "extern unsigned char yycrank[%d];" % ncr))
    nsv = (TOP - SV) // 12
    o.append("struct yysvf yysvec[%d] = { /* %08x */" % (nsv, SV))
    for i in range(nsv):
        a = SV + 12 * i
        c0, c1, c2 = u32(a), u32(a + 4), u32(a + 8)
        f0 = "YYNONE" if c0 == 0 else "%dL" % ((c0 - CR) // 2)
        f1 = "0" if c1 == 0 else "yysvec + %d" % ((c1 - SV) // 12)
        f2 = "-1L" if c2 == 0 else "%dL" % ((c2 - VS) // 4)
        assert c0 == 0 or (c0 - CR) % 2 == 0
        o.append("    { %s, %s, %s }%s" % (f0, f1, f2, "," if i + 1 < nsv else ""))
    o.append("};")
    decls.append((SV, "extern struct yysvf yysvec[%d];" % nsv))
    # 4d78e0 yytop, 4d78e4 yybgin, 4d78e8 yymatch (132 bytes), 4d796c yylsp (BSS ptr), 4d7970 yyprevious
    top = u32(TOP)
    bg = u32(TOP + 4)
    o.append("unsigned char *yytop = yycrank + %d; /* %08x */" % (top - CR, TOP))
    o.append("struct yysvf *yybgin = yysvec + %d; /* %08x */" % ((bg - SV) // 12, TOP + 4))
    o.append("signed char yymatch[132] = { /* %08x */" % (TOP + 8))
    vals = ["%d" % (b - 256 if b > 127 else b) for b in rd(TOP + 8, 132)]
    for i in range(0, 132, 16):
        o.append("    " + ", ".join(vals[i:i + 16]) + ("," if i + 16 < 132 else ""))
    o.append("};")
    o.append("long yyprevious = %d; /* %08x; the pointer at %08x is set by the lexer at run time */" % (u32(TOP + 0x90), TOP + 0x90, TOP + 0x8c))
    decls.append((TOP, "extern unsigned char *yytop;"))
    decls.append((TOP + 4, "extern struct yysvf *yybgin;"))
    decls.append((TOP + 8, "extern signed char yymatch[132];"))
    decls.append((TOP + 0x90, "extern long yyprevious;"))
    bodies.append((VS, "\n".join(o)))


CUSTOM.append((CUSTOM_LEX[0], CUSTOM_LEX[1], _lex_block))
HEADER_PRE.append("#define YYNONE 0x7fffffffL /* NULL yystoff */")

# named data objects with a known size stay in one piece
_dstarts = sorted(a for a in DN if 0x492000 <= a < 0x4db200)
for _i, _a in enumerate(_dstarts):
    _sz = DN[_a][2]
    if _sz.isdigit() and int(_sz) >= 8:
        _e = _a + int(_sz)
        if not any(_a < x < _e for x in _dstarts) and not any(fs <= _a < fe for fs, fe in FORCE):
            FORCE.append((_a, _e))

# real function entry points inside bodies of other Ghidra functions (shared tails / overlaps)
EXTRA_FUNCS = {0x42fa60: "insn_class_h_42fa60", 0x432160: "alu_h_432160", 0x4325f0: "alu_h_4325f0",
               0x432a70: "alu_h_432a70", 0x450210: "cmd_display_h_450210"}
FUNCS.update(EXTRA_FUNCS)
FN.update(EXTRA_FUNCS)

# typed pointer variables (the pointer variable holds the address of an array in BSS / .data)
HEADER_PRE.append("struct sim_state;")
HEADER_PRE.append("struct dev_inst;")
NAMES[0x4a8d98] = dict(ptype="struct sim_state **")     # dev_state_tab -> 0x4dba88 (BSS, 32 slots)
NAMES[0x4aab10] = dict(ptype="struct dev_type **" if False else "struct dev_inst **")   # dev_tab -> 0x4dbb08 (BSS, 32 slots)
NAMES[0x4aab08] = dict(ptype="struct dev_type **")      # chiptype_tab -> 0x4aaac8
NAMES[0x4aaac8] = dict(ptype="struct dev_type *")       # 13 slots, 10 filled
