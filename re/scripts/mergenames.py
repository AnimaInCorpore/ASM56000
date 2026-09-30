"""Merge the per-group naming results of a binary into one names file.

usage: mergenames.py <BIN> [override-file]
reads  re/names/<BIN>/*.names.txt   lines: addr F|D name type conf module [size]
       optional override file (same format, first 3-4 columns) - wins always
writes re/names/<BIN>.names.txt     (read by ApplyNames.java)
       re/names/<BIN>.conflicts.txt  addresses with several different names,
                                     and names used for several addresses
Resolution for an address named differently by several groups: the group
whose module owns it (column 6 == owner) wins, then higher confidence, then
the first group in file-name order.
"""
import sys, os, glob, collections

RE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
b = sys.argv[1]
RANK = {"high": 3, "med": 2, "medium": 2, "low": 1}

owner = {}
gl = os.path.join(RE, "out", b, "globals.txt")
if os.path.exists(gl):
    for l in open(gl):
        if not l.startswith("#"):
            p = l.rstrip("\n").split("\t")
            owner[int(p[0], 16)] = p[2]
fmod = {}
for l in open(os.path.join(RE, "out", b, "modules.txt")):
    p = l.rstrip("\n").split("\t")
    fmod[int(p[0], 16)] = p[3]

cands = collections.defaultdict(list)
for f in sorted(glob.glob(os.path.join(RE, "names", b, "*.names.txt"))):
    grp = os.path.basename(f).split(".")[0]
    for n, l in enumerate(open(f, encoding="utf-8"), 1):
        if l.startswith("#") or not l.strip():
            continue
        p = l.rstrip("\n").split("\t")
        if len(p) < 3:
            print("%s:%d: short line" % (f, n)); continue
        try:
            a = int(p[0], 16)
        except ValueError:
            print("%s:%d: bad address" % (f, n)); continue
        p += [""] * (7 - len(p))
        cands[a].append((grp, p))

override = {}
if len(sys.argv) > 2:
    for l in open(sys.argv[2], encoding="utf-8"):
        if l.startswith("#") or not l.strip():
            continue
        p = l.rstrip("\n").split("\t")
        p += [""] * (7 - len(p))
        override[int(p[0], 16)] = ("override", p)

final = {}
conf_lines = []
for a, cl in sorted(cands.items()):
    names = {p[2] for g, p in cl}
    if a in override:
        final[a] = override[a][1]
        if len(names) > 1:
            conf_lines.append("%08x\tresolved by override -> %s\t%s" % (a, override[a][1][2],
                              " | ".join("%s:%s" % (g, p[2]) for g, p in cl)))
        continue
    own = owner.get(a) or fmod.get(a)
    def key(gp):
        g, p = gp
        return (p[5] == own, RANK.get(p[4].lower(), 0))
    best = max(cl, key=key)
    final[a] = best[1]
    if len(names) > 1:
        conf_lines.append("%08x\t%s -> %s\t%s" % (a, "owner %s" % own, best[1][2],
                          " | ".join("%s:%s(%s,%s)" % (g, p[2], p[4], p[5]) for g, p in cl)))
for a, (g, p) in override.items():
    final.setdefault(a, p)

byname = collections.defaultdict(list)
for a, p in final.items():
    byname[p[2]].append(a)
dups = {n: al for n, al in byname.items() if len(al) > 1}

with open(os.path.join(RE, "names", b + ".names.txt"), "w", encoding="utf-8") as fp:
    fp.write("# merged by mergenames.py from re/names/%s/*.names.txt\n" % b)
    for a in sorted(final):
        p = final[a]
        name = p[2]
        if name in dups:                       # keep Ghidra names unique
            name = "%s_%08x" % (name, a)
        fp.write("%08x\t%s\t%s\t%s\t%s\t%s\t%s\n" % (a, p[1], name, p[3], p[4], p[5], p[6]))
with open(os.path.join(RE, "names", b + ".conflicts.txt"), "w", encoding="utf-8") as fp:
    fp.write("# addresses named differently by several groups\n")
    fp.write("\n".join(conf_lines) + "\n")
    fp.write("# names given to several addresses (suffixed with the address in the merged file)\n")
    for n, al in sorted(dups.items()):
        fp.write("%s\t%s\n" % (n, " ".join("%08x" % a for a in sorted(al))))
nf = sum(1 for p in final.values() if p[1] == "F")
nd = sum(1 for p in final.values() if p[1] == "D")
missing = [a for a in fmod if a not in final]
print("%d functions, %d data names; %d address conflicts, %d duplicate names; %d functions unnamed"
      % (nf, nd, len(conf_lines), len(dups), len(missing)))
