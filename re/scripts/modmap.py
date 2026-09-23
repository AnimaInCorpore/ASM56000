"""Assign functions of a Ghidra export to original source modules.

MSVC 5 places string literals in .data next to each module's globals, and the
modules keep link order in both .text and .data.  Each module's .data starts
near its RCS "$Id: name.c ..." string, so a string's address tells us which
module references it.  Functions between two anchored functions of the same
module are assumed to belong to it.

usage: modmap.py <export dir>   -> writes <export dir>/modules.txt
"""
import re, sys, os, collections

d = sys.argv[1]
# modules that only hold shared tables/strings; they vote for nothing
DATAONLY = set(sys.argv[2].split(",")) if len(sys.argv) > 2 else set()
ids = []            # (addr, module)
strref = collections.defaultdict(list)  # func -> [string addr]
for line in open(os.path.join(d, "strings.txt"), encoding="utf-8", errors="replace"):
    parts = line.rstrip("\n").split("\t")
    if len(parts) < 3:
        continue
    addr = int(parts[0], 16)
    m = re.match(r"\$Id: (\w+)\.c,v", parts[1])
    if m:
        ids.append((addr, m.group(1)))
    for f in parts[2].strip("[] ").split():
        strref[f].append(addr)
ids.sort()

def module_of(addr):
    if not ids or addr < ids[0][0] - 0x100:   # before first module -> CRT/.rdata
        return None
    mod = ids[0][1]
    for a, name in ids:
        if addr >= a - 0x40:   # tolerate a few statics declared before rcsid
            mod = name
    return mod

funcs = []
for line in open(os.path.join(d, "functions.txt"), encoding="utf-8"):
    parts = line.rstrip("\n").split("\t")
    funcs.append((int(parts[0], 16), parts[1], int(parts[2][5:])))
funcs.sort()

# vote per function
anchor = {}
for addr, name, size in funcs:
    c = collections.Counter(m for m in (module_of(a) for a in strref.get(name, []))
                            if m and m not in DATAONLY)
    if c:
        anchor[addr] = c.most_common(1)[0][0]

# fill gaps: take previous anchor's module when next anchor agrees,
# otherwise mark as boundary-uncertain
order = [m for _, m in ids]
out = []
last = None
anchored = sorted(anchor)
for addr, name, size in funcs:
    if addr in anchor:
        mod = anchor[addr]; tag = "S"
    else:
        prev = max((a for a in anchored if a < addr), default=None)
        nxt = min((a for a in anchored if a > addr), default=None)
        pm = anchor.get(prev); nm = anchor.get(nxt)
        if pm and pm == nm:
            mod = pm; tag = "="
        elif pm and nm:
            mod = pm + "|" + nm; tag = "?"
        else:
            mod = pm or "?"; tag = "?"
    out.append((addr, name, size, mod, tag))

with open(os.path.join(d, "modules.txt"), "w") as fp:
    for addr, name, size, mod, tag in out:
        fp.write("%08x\t%s\t%d\t%s\t%s\n" % (addr, name, size, tag, mod))

# summary: contiguous runs
runs = []
for addr, name, size, mod, tag in out:
    if runs and runs[-1][2] == mod:
        runs[-1][1] = addr; runs[-1][3] += 1
    else:
        runs.append([addr, addr, mod, 1])
for a, b, mod, n in runs:
    print("%08x-%08x %4d  %s" % (a, b, n, mod))
