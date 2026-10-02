# exec'd by gentab_sim.py --verify: writes re/out/SIM56000/simverify.c (prints every scalar and string
# of every generated object) and simverify.exp (the values read from the EXE).  Build and compare:
#   gcc -std=c89 -Isrc/sim56000 re/out/SIM56000/simverify.c src/sim56000/simd_*.c -o simverify
#   ./simverify | cmp - re/out/SIM56000/simverify.exp
# Data pointers/function pointers are only checked for null / non-null.

NL = chr(92) + "n"      # backslash-n as C source text


def field_exprs(tname, cols, elem):
    out = []
    if tname in TYPESPEC:
        for f in TYPESPEC[tname]:
            cnt = f[2] if len(f) > 2 else 1
            for i in range(cnt):
                out.append("%s.%s%s" % (elem, f[0], "" if cnt == 1 else "[%d]" % i))
    else:
        for j in range(len(cols)):
            out.append("%s.w%d" % (elem, j))
    return out


def verify():
    exp = []
    c = ['#include <stdio.h>', '#include "simdata.h"',
         'static const char *S(const char *p) { return p ? p : "(nil)"; }',
         "int main(void) {"]
    for s, e, name, L in OBJINFO:
        if L["kind"] == "scalar":
            w = 4 if L["ctype"].endswith("long") else 2 if "short" in L["ctype"] else 1
            if L["count"] == 1:
                c.append('printf("%%lx%s", (unsigned long)%s & 0x%xUL);' % (NL, name, (1 << (8 * w)) - 1))
            else:
                c.append('{ int i; for (i = 0; i < %d; i++) printf("%%lx%s", (unsigned long)%s[i] & 0x%xUL); }'
                         % (L["count"], NL, name, (1 << (8 * w)) - 1))
            for v in L["vals"]:
                exp.append("%x" % (v & ((1 << (8 * w)) - 1)))
        elif L["kind"] in ("struct", "ptrarray"):
            if L["kind"] == "ptrarray":
                cols = [L["pk"]]
                tname = None
                st = 1
            else:
                st = L["stride"]
                cols = L["cols"]
                tname = NAMES.get(s, {}).get("type")
            cnt = L["count"]
            words = L["words"]
            for r in range(cnt):
                if L["kind"] == "ptrarray":
                    fe = [name if cnt == 1 else "%s[%d]" % (name, r)]
                else:
                    fe = field_exprs(tname, cols, "%s[%d]" % (name, r))
                for j in range(st):
                    k = cols[j]
                    v = words[r * st + j]
                    if k in "LU":
                        c.append('printf("%%lx%s", (unsigned long)%s & 0xffffffffUL);' % (NL, fe[j]))
                        exp.append("%x" % v)
                    elif k == "S" and v and not isstr(v):
                        c.append('printf("%%d%s", %s != 0);' % (NL, fe[j]))
                        exp.append("1")
                    elif k == "S":
                        c.append('printf("%%s%s", S(%s));' % (NL, fe[j]))
                        exp.append(cstr_at(v).decode("latin-1") if v else "(nil)")
                    else:
                        c.append('printf("%%d%s", %s != 0);' % (NL, fe[j]))
                        exp.append("1" if v else "0")
    c.append("return 0; }")
    d = os.path.join(ROOT, "re", "out", "SIM56000")
    open(os.path.join(d, "simverify.c"), "w", encoding="latin-1", newline="\n").write("\n".join(c) + "\n")
    open(os.path.join(d, "simverify.exp"), "w", encoding="latin-1", newline="\n").write("\n".join(exp) + "\n")
    print(len(exp), "expected lines")


_old_verify = verify


def verify():
    _old_verify()
    d = os.path.join(ROOT, "re", "out", "SIM56000")
    o = ["/* link stubs for simverify (functions and BSS objects the data refers to) */"]
    used = set()
    comparators = set()
    for fname, lo, hi in FILES:
        for line in open(os.path.join(OUT, fname), encoding="latin-1"):
            if line.startswith("extern void "):
                used.add(line[12:].split("(")[0])
            elif line.startswith("extern long "):
                comparators.add(line[12:].split("(")[0])
    for f in sorted(used - {"main"}):
        o.append("void %s() {}" % f)
    for f in sorted(comparators):
        o.append("long %s(void *a, void *b) { (void)a; (void)b; return 0; }" % f)
    for a, n in sorted(BSS_USED.items()):
        o.append("char %s[16];" % n)
    open(os.path.join(d, "simverify_stubs.c"), "w", newline="\n").write("\n".join(o) + "\n")
