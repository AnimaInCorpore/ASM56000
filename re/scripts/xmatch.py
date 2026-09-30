"""Find identical user functions in two CLAS56 binaries (same source module
compiled into both, e.g. util.c or eval.c).

Functions are fingerprinted like crtmatch.py (x86 instructions with absolute
addresses and call targets masked).  A match needs identical fingerprints
that are unique in both binaries and a size of at least MINSIZE bytes.

usage: xmatch.py <BIN-A> <BIN-B> [MINSIZE]
reads  re/out/<BIN>/modules.txt (user functions and modules)
prints matches with modules; writes re/out/<BIN-B>/xmatch_<BIN-A>.txt:
       addrB nameB moduleB addrA nameA moduleA
"""
import sys, os, collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from crtmatch import fingerprint
from x86dis import load, reader

RE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

def index(b):
    d, base, secs = load(os.path.join(RE, "bin", b + ".EXE"))
    rd = reader(d, secs)
    hi = max(s[0] + s[1] for s in secs)
    rows = [l.rstrip("\n").split("\t") for l in open(os.path.join(RE, "out", b, "modules.txt"))]
    fs = sorted((int(r[0], 16), r[1], int(r[2]), r[3]) for r in rows)
    out = {}
    for i, (a, n, sz, m) in enumerate(fs):
        end = fs[i + 1][0] if i + 1 < len(fs) else a + sz
        end = min(end, a + max(sz, 1))
        h, _ = fingerprint(rd, a, end, base, hi)
        out[a] = (n, m, h, end - a)
    return out

A, B = sys.argv[1], sys.argv[2]
minsize = int(sys.argv[3]) if len(sys.argv) > 3 else 16
fa, fb = index(A), index(B)
ca = collections.Counter(v[2] for v in fa.values())
cb = collections.Counter(v[2] for v in fb.values())
bya = {v[2]: a for a, v in fa.items() if ca[v[2]] == 1}
pairs = []
for b, (n, m, h, sz) in sorted(fb.items()):
    if sz >= minsize and cb[h] == 1 and h in bya:
        a = bya[h]
        pairs.append((b, n, m, a, fa[a][0], fa[a][1]))
with open(os.path.join(RE, "out", B, "xmatch_%s.txt" % A), "w") as fp:
    for p in pairs:
        fp.write("%08x\t%s\t%s\t%08x\t%s\t%s\n" % p)
tot = collections.Counter(v[1] for v in fb.values())
hit = collections.Counter(p[2] for p in pairs)
via = collections.defaultdict(collections.Counter)
for p in pairs:
    via[p[2]][p[5]] += 1
for m in sorted(tot, key=lambda m: min(a for a, v in fb.items() if v[1] == m)):
    print("%-8s %3d/%3d identical   (%s modules: %s)" % (m, hit[m], tot[m], A,
          ", ".join("%s:%d" % kv for kv in via[m].most_common())))
print("total %d of %d %s functions identical to %s functions" % (len(pairs), len(fb), B, A))
