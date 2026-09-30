"""Refined function -> source module map for a CLAS56 binary.

Votes come from every absolute reference into initialized .data (strings and
static variables live in each module's own .data run, which starts at its
RCS $Id string), weighted by distance to the $Id anchors.  Modules keep link
order in .text, so the map is then made monotonic: each module becomes one
contiguous run of functions, with boundaries placed to agree with the most
votes (dynamic programming over the known module order).

usage: modmap2.py <BIN> <crt-start-hex> [data-only modules,comma,separated] [code-start-hex]
writes re/out/<BIN>/modules.txt   (addr, name, size, module, votes)
"""
import sys, os, re, collections
import capstone
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from x86dis import load, reader

RE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
b = sys.argv[1]
crt = int(sys.argv[2], 16)
dataonly = set(sys.argv[3].split(",")) if len(sys.argv) > 3 and sys.argv[3] else set()
start = int(sys.argv[4], 16) if len(sys.argv) > 4 else 0
out = os.path.join(RE, "out", b)

d, base, secs = load(os.path.join(RE, "bin", b + ".EXE"))
rd = reader(d, secs)
data = [s for s in secs if s[4] == ".data"][0]
dlo, dhi = data[0], data[0] + data[3]           # initialized part only
# the CRT's own data follows the last module: stop at the lowest CRT data label
for l in open(os.path.join(RE, "crt", b + ".names.txt"), encoding="utf-8"):
    p = l.split("	")
    if len(p) > 2 and p[1] == "D":
        a = int(p[0], 16)
        if dlo <= a < dhi:
            dhi = a

ids = []
for l in open(os.path.join(out, "strings.txt"), encoding="utf-8", errors="replace"):
    p = l.split("\t")
    m = re.match(r"\$Id: (\w+)\.c,v", p[1]) if len(p) > 1 else None
    if m:
        ids.append((int(p[0], 16), m.group(1)))
ids.sort()
order = [m for _, m in ids]

def module_of(a):
    if a < ids[0][0] - 0x40:
        return order[0] if a >= dlo else None
    mod = None
    for x, name in ids:
        if a >= x - 0x40:
            mod = name
    return mod

fs = []
for l in open(os.path.join(out, "functions.txt"), encoding="utf-8"):
    p = l.rstrip("\n").split("\t")
    fs.append((int(p[0], 16), p[1], int(p[2][5:])))
fs.sort()
fs = [f for f in fs if start <= f[0] < crt]

md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
HEX = re.compile(r"0x[0-9a-f]+")
votes = []
for i, (a, n, sz) in enumerate(fs):
    end = fs[i + 1][0] if i + 1 < len(fs) else crt
    c = collections.Counter()
    for ins in md.disasm(rd(a, end - a), a):
        for h in HEX.findall(ins.op_str):
            v = int(h, 16)
            if dlo <= v < dhi:
                m = module_of(v)
                if m and m not in dataonly:
                    c[m] += 1
    votes.append(c)

# monotonic assignment: modules of the code order (data-only ones excluded)
morder = [m for m in order if m not in dataonly]
N, M = len(fs), len(morder)
INF = float("inf")
# cost[i][j] = best cost for functions 0..i-1 with function i-1 in module j
best = [[INF] * M for _ in range(N + 1)]
back = [[0] * M for _ in range(N + 1)]
for j in range(M):
    best[0][j] = 0
for i in range(1, N + 1):
    v = votes[i - 1]
    tot = sum(v.values())
    run = INF; arg = 0
    for j in range(M):
        if best[i - 1][j] < run:
            run, arg = best[i - 1][j], j
        # stay in j, or move to j from the best earlier module
        stay = best[i - 1][j]
        prev, pj = (stay, j) if stay <= run else (run, arg)
        best[i][j] = prev + (tot - v[morder[j]])
        back[i][j] = pj
j = min(range(M), key=lambda k: best[N][k])
assign = [None] * N
for i in range(N, 0, -1):
    assign[i - 1] = morder[j]
    j = back[i][j]

with open(os.path.join(out, "modules.txt"), "w") as fp:
    for (a, n, sz), m, v in zip(fs, assign, votes):
        fp.write("%08x\t%s\t%d\t%s\t%s\n" % (a, n, sz, m,
                 " ".join("%s:%d" % kv for kv in v.most_common())))
runs = []
for (a, n, sz), m in zip(fs, assign):
    if runs and runs[-1][2] == m:
        runs[-1][1] = a; runs[-1][3] += 1; runs[-1][4] += sz
    else:
        runs.append([a, a, m, 1, sz])
for a, e, m, k, sz in runs:
    print("%08x-%08x %4d funcs %6d bytes  %s" % (a, e, k, sz, m))
conflicts = sum(1 for (f, m, v) in zip(fs, assign, votes) if v and v.most_common(1)[0][0] != m)
print("functions whose majority vote disagrees with the assignment:", conflicts)
