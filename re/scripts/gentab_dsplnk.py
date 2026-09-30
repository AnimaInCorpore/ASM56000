"""Generate src/dsplnk/lnkglb.c (and the flex/yacc table headers) from DSPLNK.EXE.

usage: gentab_dsplnk.py            write src/dsplnk/lnkglb.c, abilextb.h, abipartb.h
       gentab_dsplnk.py --check    compare instead of writing (exit 1 on difference)
       gentab_dsplnk.py --dump ADDR [LEN]
                                   print any data range of the EXE as words with
                                   string annotations (for translators)

lnkglb.c holds
  1. the initialized data of the original lnkglb.c object (.data 0x457b10-0x458e38),
     decoded from the EXE according to SPEC below (every pointer into the data
     becomes a string literal or a reference to another global), and
  2. the definitions of all other globals that are used by more than one source
     file (BSS in the original), listed in BSS below.
The declarations of all of them are in src/dsplnk/dsplnk.h; compiling lnkglb.c
therefore cross-checks every type.

The flex and yacc tables of the ABI expression parser go into abilextb.h and
abipartb.h, which abilex.c / abiparse.c include (they were static there).
"""
import os, re, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "re", "scripts"))
from x86dis import load, reader        # noqa: E402

EXE = os.path.join(ROOT, "re", "bin", "DSPLNK.EXE")
OUT = os.path.join(ROOT, "src", "dsplnk")

_d, _base, _secs = load(EXE)
rd = reader(_d, _secs)


def u32(a):
    return struct.unpack("<I", rd(a, 4))[0]


def s32(a):
    return struct.unpack("<i", rd(a, 4))[0]


def u16(a):
    return struct.unpack("<H", rd(a, 2))[0]


def s16(a):
    return struct.unpack("<h", rd(a, 2))[0]


def cstr(a):
    b = rd(a, 4096)
    return b[:b.index(b"\0")].decode("latin-1")


def cq(s):
    """C string literal"""
    out = '"'
    for ch in s:
        o = ord(ch)
        if ch == '"' or ch == "\\":
            out += "\\" + ch
        elif ch == "\n":
            out += "\\n"
        elif ch == "\t":
            out += "\\t"
        elif ch == "\r":
            out += "\\r"
        elif 32 <= o < 127:
            out += ch
        else:
            out += "\\%03o" % o
    return out + '"'


# incremental link thunks 0x401000-0x40150f: jmp <function>
def _thunks():
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    t = {}
    for ins in md.disasm(rd(0x401000, 0x510), 0x401000):
        if ins.mnemonic == "jmp":
            t[ins.address] = int(ins.op_str, 16)
    return t


THUNK = _thunks()

# function address -> final C name (for function pointer tables)
FUNCNAMES = {}
_fm = os.path.join(ROOT, "re", "notes", "DSPLNK", "filemap.txt")
if os.path.exists(_fm):
    for _l in open(_fm, encoding="utf-8"):
        if _l.startswith("#") or not _l.strip():
            continue
        _p = _l.split()
        FUNCNAMES[int(_p[0], 16)] = _p[1]


def funcname(a):
    a = THUNK.get(a, a)
    if a == 0:
        return "0"
    return FUNCNAMES.get(a, "FUN_%08x" % a)


# ---------------------------------------------------------------------------
# SPEC: the initialized globals of lnkglb.c in address order.
#   (addr, kind, C declarator, comment[, extra])
# kinds:
#   long / ulong / int    one 32-bit value
#   str                   char *x = "literal" (pointer into .data)
#   chars N               char x[N] = "..."  (extra = N)
#   ref                   pointer to another global: extra = C expression
#   longs N               long x[N]
#   struct                extra = (count, [field kinds]); field kinds as above
#                         (str, long, ulong, func); the declarator is the array
#   funcs N               array of N function pointers (resolved through the
#                         incremental-link thunks)
# ---------------------------------------------------------------------------
SPEC = []            # filled in below (see the "lnkglb.c data" section)
BSS = []             # (C definition, comment) of shared uninitialized globals


def gen_value(kind, a):
    if kind == "long":
        return "%dL" % s32(a) if s32(a) not in (0,) else "0"
    if kind == "ulong":
        v = u32(a)
        return "0x%lxUL" % v if v else "0"
    if kind == "int":
        return "%d" % s32(a)
    if kind == "str":
        p = u32(a)
        return cq(cstr(p)) if p else "0"
    if kind == "func":
        return funcname(u32(a))
    raise ValueError(kind)


def gen_spec():
    out = []
    for ent in SPEC:
        a, kind, decl, com = ent[:4]
        extra = ent[4] if len(ent) > 4 else None
        c = "/* %08x %s */" % (a, com) if com else "/* %08x */" % a
        if kind in ("long", "ulong", "int", "str"):
            out.append("%s = %s;%s%s" % (decl, gen_value(kind, a),
                                          " " * max(1, 40 - len(decl) - 6), c))
        elif kind == "chars":
            out.append("%s = %s; %s" % (decl, cq(cstr(a)), c))
        elif kind == "ref":
            out.append("%s = %s; %s" % (decl, extra, c))
        elif kind in ("longs", "ulongs"):
            n = extra
            vals = [gen_value("long" if kind == "longs" else "ulong", a + 4 * i) for i in range(n)]
            out.append("%s = { %s" % (decl, c))
            for i in range(0, n, 6):
                out.append("    " + ", ".join(vals[i:i + 6]) + ("," if i + 6 < n else ""))
            out.append("};")
        elif kind == "funcs":
            n = extra
            out.append("%s = { %s" % (decl, c))
            vals = [funcname(u32(a + 4 * i)) for i in range(n)]
            for i in range(0, n, 4):
                out.append("    " + ", ".join(vals[i:i + 4]) + ("," if i + 4 < n else ""))
            out.append("};")
        elif kind == "struct":
            n, fields = extra
            size = 4 * len(fields)
            out.append("%s = { %s" % (decl, c))
            for i in range(n):
                e = a + i * size
                vals = [gen_value(f, e + 4 * j) for j, f in enumerate(fields)]
                out.append("    { %s }%s" % (", ".join(vals), "," if i + 1 < n else ""))
            out.append("};")
        else:
            raise ValueError(kind)
    return out


def dump(a, n):
    e = a + n
    while a < e:
        w = u32(a)
        note = ""
        try:
            s = cstr(a)
            if len(s) >= 2 and all(32 <= ord(ch) < 127 or ch in "\t\n\r" for ch in s):
                print("%08x: str %s" % (a, cq(s)))
                a += (len(s) + 4) & ~3
                continue
        except ValueError:
            pass
        if 0x450000 <= w < 0x470000:
            try:
                s = cstr(w)
                if s and all(32 <= ord(ch) < 127 or ch in "\t\n\r" for ch in s):
                    note = " -> " + cq(s)[:60]
            except ValueError:
                pass
        elif 0x401000 <= w < 0x43c2d0:
            note = " -> " + funcname(w)
        print("%08x: %08x %11d%s" % (a, w, s32(a), note))
        a += 4


# ---------------------------------------------------------------------------
exec(open(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                       "gentab_dsplnk_spec.py"), encoding="utf-8").read())
# ---------------------------------------------------------------------------


def write(path, text, check):
    old = open(path, encoding="latin-1").read() if os.path.exists(path) else None
    if check:
        if old != text:
            print("%s differs" % path)
            return 1
        return 0
    if old != text:
        with open(path, "w", encoding="latin-1", newline="\n") as fp:
            fp.write(text)
        print("wrote %s" % path)
    return 0


def main():
    args = sys.argv[1:]
    if args and args[0] == "--dump":
        a = int(args[1], 16)
        n = int(args[2], 16) if len(args) > 2 else 0x100
        dump(a, n)
        return 0
    check = bool(args and args[0] == "--check")
    bad = 0
    for name, text in OUTPUTS():
        bad |= write(os.path.join(OUT, name), text, check)
    return bad


if __name__ == "__main__":
    sys.exit(main())
