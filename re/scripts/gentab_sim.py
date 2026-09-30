"""Generate the initialized data of SIM56000.EXE as portable C (src/sim56000/simd_*.c + simdata.h).

usage: gentab_sim.py              write the files
       gentab_sim.py --check      compare only
       gentab_sim.py --dump ADDR [LEN]   annotated words of any data range
       gentab_sim.py --report     object list with layout decisions (re/notes/SIM56000/datamap.txt)

The whole initialized data (.rdata 0x492000-0x4945ff, .data 0x495000-0x4db1ff) is split into
objects (boundaries: pointer targets found in data, absolute operands found in machine code,
named globals), each object is typed from the word classification and from the access widths
seen in the code (simdata.py), and emitted as a C array (or array of struct).  Strings that are
pointed to become string literals, function pointers become function names, data pointers become
address constants of the generated objects.  Nothing depends on the host word size or byte order.
Curated names/types for important tables: gentab_sim_spec.py (NAMES, FIELDNAMES, OBJ_STARTS).
"""
import os, re, sys, struct, bisect, hashlib, collections
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
from simdata import *   # noqa

OUT = os.path.join(ROOT, "src", "sim56000")
refs = sweep()

# ---------------------------------------------------------------- names
FN = {}      # addr -> function name
DN = {}      # addr -> (name, type, size)
for l in open(os.path.join(ROOT, "re", "names", "SIM56000.names.txt"), encoding="utf-8"):
    if l.startswith("#") or not l.strip():
        continue
    p = l.rstrip("\n").split("\t")
    if p[1] == "F":
        FN[int(p[0], 16)] = p[2]
    else:
        DN[int(p[0], 16)] = (p[2], p[3] if len(p) > 3 else "", p[6] if len(p) > 6 and p[6].isdigit() else "")
FUNCS = set()
for l in open(os.path.join(ROOT, "re", "out", "SIM56000", "functions.txt")):
    FUNCS.add(int(l.split("\t")[0], 16))


def funcname(a):
    return FN.get(a, "FUN_%08x" % a)


def cq(bs):
    out = '"'
    for c in bs:
        ch = chr(c)
        if ch == '"' or ch == "\\":
            out += "\\" + ch
        elif ch == "\n":
            out += "\\n"
        elif ch == "\t":
            out += "\\t"
        elif ch == "\r":
            out += "\\r"
        elif ch == "?":
            out += "\\?"          # avoid trigraphs
        elif 32 <= c < 127:
            out += ch
        else:
            out += "\\%03o" % c
    return out + '"'


def isstr(a):
    if not in_data(a):
        return False
    b = cstr_at(a, 4096)
    if b is None or not printable(b):
        return False
    if in_data(a - 1) and rd(a - 1, 1) != b"\0":
        return False
    if len(b) < 4 and (in_data(u32(a)) or in_text(u32(a))):
        return False               # a short "string" that is really a pointer word
    if a in DN and DN[a][0].startswith(("dev_", "cmd", "tab")):
        return False
    return True


exec(open(os.path.join(HERE, "gentab_sim_spec.py"), encoding="utf-8").read())

# ---------------------------------------------------------------- object discovery
LO, HI = RDATA[0], DATA[1]


DROPPED = []


def build_objects():
    ptrs = {}
    for lo, hi in (RDATA, DATA):
        for a in range(lo, hi - 3, 4):
            v = u32(a)
            if in_data(v) or in_bss(v):
                if isstr(v) or v % 4 == 0:
                    ptrs.setdefault(v, []).append(a)
    strs = set(v for v in ptrs if isstr(v))
    strs |= set(a for a, sz in refs.items() if in_data(a) and a not in DN and isstr(a) and all((x & 0xfff) >> 4 <= 1 for x in sz))
    cov = bytearray(HI - LO)
    for s in strs:
        e = s + len(cstr_at(s)) + 1
        for x in range(s, min(e, HI)):
            cov[x - LO] = 1
    bounds = set(a for a in DN if in_data(a)) | set(v for v in ptrs if v not in strs) | \
        set(a for a in refs if a not in strs) | set(OBJ_STARTS)
    for fs, fe in FORCE:
        bounds -= set(range(fs + 1, fe))
        bounds |= {fs, fe}
        for x in range(fs, fe):
            cov[x - LO] = 0
    objs = []
    a = LO
    while a < HI:
        if not in_data(a) or cov[a - LO]:
            a += 1
            continue
        s = a
        a += 1
        while a < HI and in_data(a) and not cov[a - LO] and a not in bounds:
            a += 1
        objs.append([s, a])
    # drop custom-block ranges and tiny orphans (padding / unreferenced string tails)
    keep = []
    for o in objs:
        if any(cs <= o[0] < ce for cs, ce, _ in CUSTOM):
            continue
        if o[0] not in bounds and o[1] - o[0] < 8 and o[0] not in DN:
            DROPPED.append(tuple(o))
            continue
        keep.append(o)
    return keep, ptrs, strs


OBJS, PTRS, STRS = build_objects()
OBJ_START = [o[0] for o in OBJS]


def obj_at(a):
    for cs, ce, _ in CUSTOM:
        if cs <= a < ce:
            return None
    i = bisect.bisect_right(OBJ_START, a) - 1
    if i >= 0 and OBJS[i][0] <= a < OBJS[i][1]:
        return OBJS[i]
    return None


def sym(s):
    if s in NAMES and NAMES[s].get("sym"):
        return NAMES[s]["sym"]
    if s in DN and in_data(s):
        return DN[s][0]
    return "d_%06x" % s


def word_kind(v):
    if v == 0:
        return "Z"
    if in_text(v):
        return "F" if v in FUNCS else "I"
    if in_data(v) or in_bss(v):
        if isstr(v):
            return "S"
        if in_bss(v):
            return "P" if v % 4 == 0 or v in refs else "I"
        if obj_at(v) is not None and (v % 4 == 0 or v in refs):
            return "P"
    return "I"


BSS_USED = {}


def ptr_expr(v):
    if in_bss(v):
        n = DN[v][0] if v in DN else "bss_%06x" % v
        BSS_USED[v] = n
        return "(void *)&%s" % n
    o = obj_at(v)
    if o is None and isstr(v):
        return "(void *)%s" % cq(cstr_at(v))
    if o is None:
        raise ValueError("pointer %08x not inside an object" % v)
    off = v - o[0]
    b = sym(o[0])
    return "(void *)&%s" % b if off == 0 else "(void *)((char *)&%s + %d)" % (b, off)


def int_lit(v, unsigned):
    v &= 0xffffffff
    if unsigned:
        return "0x%xUL" % v if v > 9 else "%dUL" % v if v else "0"
    if v >= 0x80000000:
        v -= 1 << 32
    if v == -2147483648:
        return "(-2147483647L-1)"
    if -32768 <= v <= 32767:
        return "%d" % v
    return "%dL" % v


def access_width(s, e):
    sizes = collections.Counter()
    sgn = False
    for a in range(s, e):
        for x in refs.get(a, ()):
            sz = (x & 0xfff) >> 4
            if x & 4096:
                sgn = True
            if sz:
                sizes[sz] += 1
    return sizes, sgn


CTYPE = {1: "unsigned char", 2: "unsigned short", 4: "unsigned long"}
CTYPES = {1: "signed char", 2: "short", 4: "long"}

TYPEDEFS = collections.OrderedDict()   # struct name -> signature
SIGS = {}


def struct_for(cols, hint=None):
    sig = tuple(cols)
    if hint:
        name = hint
    elif sig in SIGS:
        return SIGS[sig]
    else:
        h = hashlib.md5(repr(sig).encode()).hexdigest()[:5]
        name = "rec%dw_%s" % (len(cols), h)
    if name not in TYPEDEFS:
        TYPEDEFS[name] = sig
    SIGS.setdefault(sig, name)
    return name


FT = {"S": "const char *", "F": "simfn", "P": "void *", "L": "long", "U": "unsigned long"}


def col_kind(vals):
    ks = set(k for k, v in vals if k != "Z")
    if not ks:
        return "L"
    if ks == {"S", "P"}:
        return "S"
    if len(ks) == 1 and ks != {"I"}:
        return ks.pop()
    if ks == {"I"}:
        big = any(0x80000000 <= v < 0xffff0000 for k, v in vals if k == "I")
        return "U" if big else "L"
    return None


TYPECOLS = {}


def typecols(tname):
    """column kinds of a curated record type: merged over all objects that carry the type"""
    if tname in TYPECOLS:
        return TYPECOLS[tname]
    if tname in TYPESPEC:
        cols = []
        for f in TYPESPEC[tname]:
            cols += [f[1][0]] * (f[2] if len(f) > 2 else 1)
        TYPECOLS[tname] = cols
        return cols
    cols = None
    for os_, oe in OBJS:
        h = NAMES.get(os_, {})
        if h.get("type") != tname:
            continue
        st = h["stride"]
        n = (oe - os_) // 4
        nel = n // st
        ws = [u32(os_ + 4 * i) for i in range(nel * st)]
        ks = [word_kind(v) for v in ws]
        cc = []
        for c in range(st):
            k = col_kind([(ks[r * st + c], ws[r * st + c]) for r in range(nel)])
            cc.append(k)
        if cols is None:
            cols = cc
        else:
            for i in range(st):
                if cols[i] is None or cc[i] is None:
                    cols[i] = None
                elif cols[i] != cc[i]:
                    if cc[i] == "L":
                        pass
                    elif cols[i] == "L":
                        cols[i] = cc[i]
                    else:
                        cols[i] = None
    if cols is None or None in cols:
        raise ValueError("type %s: inconsistent columns %s" % (tname, cols))
    TYPECOLS[tname] = cols
    return cols


def layout(s, e):
    n = e - s
    hint = NAMES.get(s, {})
    if hint.get("type") and hint.get("stride") and s % 4 == 0:
        st = hint["stride"]
        words = [u32(s + i) for i in range(0, n - n % 4, 4)]
        nel = len(words) // st
        kinds = [word_kind(v) for v in words]
        cols = typecols(hint["type"])
        tw = words[nel * st:]
        tk = kinds[nel * st:]
        return dict(kind="struct", stride=st, cols=cols, words=words[:nel * st], kinds=kinds[:nel * st],
                    count=nel, tail=(tw, tk))
    if hint.get("ctype") == "char *" and n == 4:      # pointer that is NULL in the image (set at run time)
        return dict(kind="scalar", ctype="char *", vals=[0], count=1)
    sizes, sgn = access_width(s, e)
    if hint.get("width"):
        w = hint["width"]
        sgn = hint.get("signed", False)
    else:
        w = 4
        if sizes and not sizes.get(4) and not sizes.get(8):
            w = 2 if sizes.get(2) else 1
        if s % 4 != 0 or n % 4 != 0:
            w = 2 if (s % 2 == 0 and n % 2 == 0 and sizes.get(1, 0) == 0) else 1
    if w != 4:
        cnt = n // w
        vals = [int.from_bytes(rd(s + i * w, w), "little", signed=bool(sgn)) for i in range(cnt)]
        return dict(kind="scalar", ctype=(CTYPES if sgn else CTYPE)[w], vals=vals, count=cnt)
    words = [u32(s + i) for i in range(0, n - n % 4, 4)]
    kinds = [word_kind(v) for v in words]
    if not any(k in "SFP" for k in kinds) and "stride" not in hint:
        big = any(0x80000000 <= v < 0xffff0000 for v in words)
        return dict(kind="scalar", ctype="unsigned long" if big else "long", vals=words,
                    count=len(words), unsigned=big)
    strides = [hint["stride"]] if "stride" in hint else range(1, len(words) + 1)
    best = None
    for st in strides:
        nel = len(words) // st
        if nel < 2 and "stride" not in hint and st != len(words):
            continue
        pad = len(words) - nel * st
        if nel < 1:
            continue
        fullwords = words[:nel * st]
        fullkinds = kinds[:nel * st]
        cols = []
        ok = True
        for c in range(st):
            col = [(fullkinds[r * st + c], fullwords[r * st + c]) for r in range(nel)]
            k = col_kind(col)
            if k is None:
                ok = False
                break
            cols.append(k)
        if not ok:
            continue
        tailw = words[nel * st:]
        tailk = kinds[nel * st:]
        # cost: columns + tail words (prefer few columns, little tail)
        cost = st + 3 * len(tailw)
        if best is None or cost < best[0]:
            best = (cost, st, cols, fullwords, fullkinds, tailw, tailk)
        if "stride" in hint:
            break
    if best is None:
        return dict(kind="mixed", words=words, kinds=kinds)
    cost, st, cols, fullwords, fullkinds, tailw, tailk = best
    if st == 1 and cols[0] in "SFP" and not tailw:
        return dict(kind="ptrarray", pk=cols[0], words=fullwords, count=len(fullwords))
    return dict(kind="struct", stride=st, cols=cols, words=fullwords, kinds=fullkinds,
                count=len(fullwords) // st, tail=(tailw, tailk))


def emit_value(k, v, cast=None):
    if k == "P" and cast and v:
        return "(%s)%s" % (cast, ptr_expr(v)[len("(void *)"):])
    if k in "LU":
        return int_lit(v, k == "U")
    if v == 0:
        return "0"
    if k == "S":
        if not isstr(v):
            return "(const char *)" + ptr_expr(v)[len("(void *)"):]
        return cq(cstr_at(v))
    if k == "F":
        return funcname(v)
    if k == "P":
        return ptr_expr(v)
    raise ValueError(k)


OBJINFO = []     # (start, end, sym, layout)


def emit_row(tname, cols, ws):
    """initializer text for one record"""
    if tname not in TYPESPEC:
        return "{ %s }" % ", ".join(emit_value(cols[j], ws[j]) for j in range(len(cols)))
    out = []
    j = 0
    for f in TYPESPEC[tname]:
        cnt = f[2] if len(f) > 2 else 1
        kd = f[1]
        cast = None
        if len(kd) > 2 and kd[1] == "=":
            cast = "struct %s *" % kd[2:]
        vals = [emit_value(kd[0], ws[j + i], cast) for i in range(cnt)]
        j += cnt
        if cnt == 1:
            out.append(vals[0])
        elif all(v == "0" for v in vals):
            out.append("{ 0 }")
        else:
            out.append("{ %s }" % ", ".join(vals))
    return "{ %s }" % ", ".join(out)


def gen_all():
    for s, e in OBJS:
        OBJINFO.append((s, e, sym(s), layout(s, e)))
    decls = []
    bodies = []
    for s, e, name, L in OBJINFO:
        c = "/* %08x %d */" % (s, e - s)
        lines = []
        if L["kind"] == "scalar":
            ty = L["ctype"]
            if L["count"] == 1:
                decls.append((s, "extern %s %s;" % (ty, name)))
                v = L["vals"][0]
                lit = int_lit(v, ty == "unsigned long") if ty in ("long", "unsigned long") else "%d" % v
                bodies.append((s, "%s %s = %s; %s" % (ty, name, lit, c)))
                continue
            decls.append((s, "extern %s %s[%d];" % (ty, name, L["count"])))
            if ty in ("long", "unsigned long"):
                lit = [int_lit(v, ty == "unsigned long") for v in L["vals"]]
                per = 8
            else:
                lit = ["%d" % v for v in L["vals"]]
                per = 16
            lines.append("%s %s[%d] = { %s" % (ty, name, L["count"], c))
            for i in range(0, len(lit), per):
                lines.append("    " + ", ".join(lit[i:i + per]) + ("," if i + per < len(lit) else ""))
            lines.append("};")
        elif L["kind"] == "ptrarray":
            pt = NAMES.get(s, {}).get("ptype")
            ty = pt if pt else FT[L["pk"]]
            cast = pt if pt else None
            if L["count"] == 1:
                decls.append((s, "extern %s%s%s;" % (ty, "" if ty.endswith("*") else " ", name)))
                bodies.append((s, "%s%s%s = %s; %s" % (ty, "" if ty.endswith("*") else " ", name,
                                                      emit_value(L["pk"], L["words"][0], cast), c)))
                continue
            decls.append((s, "extern %s%s%s[%d];" % (ty, "" if ty.endswith("*") else " ", name, L["count"])))
            lines.append("%s%s%s[%d] = { %s" % (ty, "" if ty.endswith("*") else " ", name, L["count"], c))
            vs = [emit_value(L["pk"], v, cast) for v in L["words"]]
            per = 4 if L["pk"] != "P" else 2
            for i in range(0, len(vs), per):
                lines.append("    " + ", ".join(vs[i:i + per]) + ("," if i + per < len(vs) else ""))
            lines.append("};")
        elif L["kind"] == "struct":
            th = NAMES.get(s, {}).get("type")
            ty = "struct " + (th if th in TYPESPEC else struct_for(L["cols"], th))
            L["ty"] = ty
            st = L["stride"]
            decls.append((s, "extern %s %s[%d];" % (ty, name, L["count"])))
            lines.append("%s %s[%d] = { %s" % (ty, name, L["count"], c))
            th = NAMES.get(s, {}).get("type")
            for r in range(L["count"]):
                lines.append("    %s%s" % (emit_row(th, L["cols"], L["words"][r * st:(r + 1) * st]),
                                            "," if r + 1 < L["count"] else ""))
            lines.append("};")
            tw, tk = L["tail"]
            if tw:
                tcols = [{"Z": "L", "I": "L"}.get(k, k) for k in tk]
                tty = "struct " + struct_for(tcols, "flat_%06x" % (s + 4 * len(L["words"])))
                decls.append((s + 1, "extern %s %s_tail;" % (tty, name)))
                lines.append("%s %s_tail = { /* %08x tail of %s */" % (tty, name, s + 4 * len(L["words"]), name))
                tv = [emit_value(k, v) for k, v in zip(tcols, tw)]
                for i in range(0, len(tv), 4):
                    lines.append("    " + ", ".join(tv[i:i + 4]) + ("," if i + 4 < len(tv) else ""))
                lines.append("};")
        else:
            cols = [{"Z": "L", "I": "L"}.get(k, k) for k in L["kinds"]]
            ty = "struct " + struct_for(cols, "flat_%06x" % s)
            L["ty"] = ty
            decls.append((s, "extern %s %s;" % (ty, name)))
            lines.append("%s %s = { %s" % (ty, name, c))
            vs = [emit_value(k, v) for k, v in zip(cols, L["words"])]
            for i in range(0, len(vs), 4):
                lines.append("    " + ", ".join(vs[i:i + 4]) + ("," if i + 4 < len(vs) else ""))
            lines.append("};")
        bodies.append((s, "\n".join(lines)))
    for cs, ce, fn in CUSTOM:
        fn(decls, bodies)
    return decls, bodies


def header_text(decls):
    o = ["/* simdata.h - GENERATED by re/scripts/gentab_sim.py from SIM56000.EXE; do not edit.",
         "   Types and extern declarations of all initialized data tables of the simulator. */",
         "#ifndef SIMDATA_H", "#define SIMDATA_H", "",
         "typedef void (*simfn)();", ""] + list(HEADER_PRE)
    for name in TYPESPEC:
        o.append("struct %s;" % name)
    o.append("")
    for name, fl in TYPESPEC.items():
        o.append("struct %s {" % name)
        for f in fl:
            cnt = f[2] if len(f) > 2 else 1
            kd = f[1]
            ct = FT[kd[0]]
            if len(kd) > 2 and kd[1] == "=":
                ct = "struct %s *" % kd[2:]
            o.append("    %s%s%s;%s" % (ct, "" if ct.endswith("*") else " ", f[0] if cnt == 1 else "%s[%d]" % (f[0], cnt),
                                       "  /* %s */" % f[3] if len(f) > 3 else ""))
        o.append("};")
    o.append("")
    for name, sig in TYPEDEFS.items():
        if name in TYPESPEC:
            continue
        o.append("struct %s {" % name)
        for i, k in enumerate(sig):
            fname = FIELDNAMES.get(name, {}).get(i, "w%d" % i)
            o.append("    %s %s;" % (FT[k], fname))
        o.append("};")
    o.append("")
    for s, dl in sorted(decls):
        o.append(dl)
    for a, n in sorted(BSS_USED.items()):
        o.append("extern char %s[]; /* BSS object %08x referenced from initialized data */" % (n, a))
    o.append("")
    o.append("#endif")
    return "\n".join(o) + "\n"


FNAMES_ALL = set(FN.values())


def file_text(fname, bodies):
    o = ["/* %s - GENERATED by re/scripts/gentab_sim.py from SIM56000.EXE; do not edit. */" % fname,
         '#include "simdata.h"', ""]
    fn = set()
    for s, b in bodies:
        for tok in b.replace(",", " ").replace("{", " ").replace("}", " ").replace("(", " ").replace(")", " ").replace(";", " ").split():
            if tok in FNAMES_ALL:
                fn.add(tok)
    for f in sorted(fn):
        o.append("extern void %s();" % f)
    o.append("")
    for s, b in bodies:
        o.append(b)
        o.append("")
    return "\n".join(o)


FILES = [
    ("simd_a.c", 0x492000, 0x4a0000),
    ("simd_dev.c", 0x4a0000, 0x4a8000),
    ("simd_b.c", 0x4a8000, 0x4b4000),
    ("simd_c.c", 0x4b4000, 0x4bf800),
    ("simd_dec.c", 0x4bf800, 0x4c4f00),
    ("simd_e.c", 0x4c4f00, 0x4d5800),
    ("simd_f.c", 0x4d5800, 0x4dc000),
]


def report():
    with open(os.path.join(ROOT, "re", "notes", "SIM56000", "datamap.txt"), "w") as f:
        f.write("# initialized data objects of SIM56000.EXE (generated by gentab_sim.py --report)\n")
        f.write("# addr\tsize\tsymbol\tlayout\n")
        for s, e, name, L in OBJINFO:
            if L["kind"] == "scalar":
                d = "%s[%d]" % (L["ctype"], L["count"])
            elif L["kind"] == "ptrarray":
                d = "%s[%d]" % (FT[L["pk"]], L["count"])
            elif L["kind"] == "struct":
                d = "%s[%d] stride=%d cols=%s" % (L["ty"], L["count"], L["stride"], "".join(L["cols"]))
            else:
                d = "MIXED %s" % "".join(L["kinds"])
            f.write("%08x\t%d\t%s\t%s\n" % (s, e - s, name, d))


def dump(a, n):
    e = a + n
    while a < e:
        w = u32(a)
        note = ""
        if isstr(a):
            s = cstr_at(a)
            print("%08x: str %s" % (a, cq(s)))
            a += (len(s) + 4) & ~3
            continue
        k = word_kind(w)
        if k == "S":
            note = " -> " + cq(cstr_at(w))[:60]
        elif k == "F":
            note = " -> " + funcname(w)
        elif k == "P":
            note = " -> data " + (sym(obj_at(w)[0]) if obj_at(w) else "bss")
        print("%08x: %08x %11d %s%s" % (a, w, s32(a), k, note))
        a += 4


def main():
    args = sys.argv[1:]
    if args and args[0] == "--dump":
        dump(int(args[1], 16), int(args[2], 16) if len(args) > 2 else 0x100)
        return 0
    decls, bodies = gen_all()
    if args and args[0] == "--report":
        report()
        return 0
    if args and args[0] == "--verify":
        exec(open(os.path.join(HERE, "gentab_sim_verify.py"), encoding="utf-8").read(), globals())
        verify()
        return 0
    if args and args[0] == "--audit":
        for a, e in DROPPED:
            b = rd(a, e - a)
            if any(b) and not printable(b.rstrip(bytes(1))):
                print("dropped %08x-%08x %s" % (a, e, b.hex()))
        return 0
    outs = {"simdata.h": header_text(decls)}
    for fname, lo, hi in FILES:
        outs[fname] = file_text(fname, [(s, b) for s, b in bodies if lo <= s < hi])
    bs = ["/* simbss.c - GENERATED by re/scripts/gentab_sim.py: uninitialized (BSS) objects that initialized data points to.",
          "   Sizes are the gaps to the next such object (lower bounds for pools); the translators give them proper types. */", ""]
    allb = sorted(BSS_USED)
    for a, n in sorted(BSS_USED.items()):
        nxt = [x for x in allb if x > a]
        sz = (nxt[0] if nxt else BSS[1]) - a
        bs.append("char %s[%d]; /* %08x */" % (n, sz, a))
    outs["simbss.c"] = chr(10).join(bs) + chr(10)
    check = bool(args and args[0] == "--check")
    bad = 0
    for name, text in outs.items():
        path = os.path.join(OUT, name)
        old = open(path, encoding="latin-1").read() if os.path.exists(path) else None
        if check:
            if old != text:
                print(name, "differs")
                bad = 1
        elif old != text:
            os.makedirs(OUT, exist_ok=True)
            open(path, "w", encoding="latin-1", newline="\n").write(text)
            print("wrote", path)
    if BSS_USED:
        print("BSS objects referenced from data:", ", ".join("%08x:%s" % (a, n) for a, n in sorted(BSS_USED.items())))
    return bad


if __name__ == "__main__":
    sys.exit(main())
