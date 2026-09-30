"""Split a Ghidra export into one file per source module and inventory the
global data.

usage: splitmods.py <BIN> [addr:module ...]   (overrides, e.g. 401000-40116d:asmglb)
reads  re/out/<BIN>/{modules.txt,decomp.c,strings.txt}
writes re/out/<BIN>/mod/<module>.c     functions of the module, in address order
       re/out/<BIN>/globals.txt        data address, gap to next ref'd address,
                                       section, owner module ($Id range), user modules
"""
import sys, os, re, collections
import capstone
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from x86dis import load, reader

RE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
b = sys.argv[1]
out = os.path.join(RE, "out", b)
overrides = []
for a in sys.argv[2:]:
    r, m = a.split(":")
    lo, hi = (r.split("-") + [r])[:2]
    overrides.append((int(lo, 16), int(hi, 16), m))

rows = [l.rstrip("\n").split("\t") for l in open(os.path.join(out, "modules.txt"))]
modof = {}
for r in rows:
    a = int(r[0], 16)
    m = r[3]
    for lo, hi, om in overrides:
        if lo <= a <= hi:
            m = om
    modof[a] = (r[1], m)

# split decomp.c
text = open(os.path.join(out, "decomp.c"), encoding="utf-8", errors="replace").read()
parts = re.split(r"(?m)^/\* ==== (\S+) @ ([0-9a-f]+) ==== \*/\n", text)
bymod = collections.defaultdict(list)
for i in range(1, len(parts), 3):
    name, addr, body = parts[i], int(parts[i + 1], 16), parts[i + 2]
    if addr in modof:
        bymod[modof[addr][1]].append((addr, name, body))
os.makedirs(os.path.join(out, "mod"), exist_ok=True)
for m, fl in bymod.items():
    with open(os.path.join(out, "mod", m + ".c"), "w", encoding="utf-8") as fp:
        fp.write("/* %s: %d functions from %s */\n\n" % (m, len(fl), b))
        for addr, name, body in sorted(fl):
            fp.write("/* ==== %s @ %08x ==== */\n%s" % (name, addr, body))
    print("%-10s %3d functions" % (m, len(fl)))

# global data inventory
d, base, secs = load(os.path.join(RE, "bin", b + ".EXE"))
rd = reader(d, secs)
data = [s for s in secs if s[4] == ".data"][0]
dlo, dinit, dend = data[0], data[0] + data[3], data[0] + data[1]
ids = []
for l in open(os.path.join(out, "strings.txt"), encoding="utf-8", errors="replace"):
    p = l.split("\t")
    mm = re.match(r"\$Id: (\w+)\.c,v", p[1]) if len(p) > 1 else None
    if mm:
        ids.append((int(p[0], 16), mm.group(1)))
ids.sort()
strings = set(int(l[:8], 16) for l in open(os.path.join(out, "strings.txt"), encoding="utf-8", errors="replace")
              if re.match(r"[0-9a-f]{8}\t", l))

def owner(a):
    if a >= dinit:
        return "bss"
    o = "?"
    for x, n in ids:
        if a >= x - 0x40:
            o = n
    return o

md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
HEX = re.compile(r"0x[0-9a-f]+")
users = collections.defaultdict(set)
fa = sorted(modof)
for i, a in enumerate(fa):
    end = fa[i + 1] if i + 1 < len(fa) else a + 0x1000
    for ins in md.disasm(rd(a, end - a), a):
        for h in HEX.findall(ins.op_str):
            v = int(h, 16)
            if dlo <= v < dend and v not in strings:
                users[v].add(modof[a][1])
        if ins.mnemonic == "ret" and ins.address + ins.size >= end:
            break
addrs = sorted(users)
with open(os.path.join(out, "globals.txt"), "w") as fp:
    fp.write("# addr\tgap\towner\tused by\n")
    for i, a in enumerate(addrs):
        gap = (addrs[i + 1] - a) if i + 1 < len(addrs) else 0
        fp.write("%08x\t%d\t%s\t%s\n" % (a, gap, owner(a), ",".join(sorted(users[a]))))
print("%d global data addresses referenced (%d in bss)" % (len(addrs), sum(1 for a in addrs if a >= dinit)))
