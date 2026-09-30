"""Name the SIM56000 functions that no analysis group named (code reachable only through
data tables: instruction-class handler tables, command handler variants ...).
Writes re/names/SIM56000/hidden.names.txt ('low' confidence, name only, no prototype).
Naming: command handlers from the table in re/notes/SIM56000/cmd.md (cmd_<name>_h<i> /
cmd_<name>_parse); table handlers <table>_<addr>; the rest <caller>_sub_<addr>.
"""
import re, os, struct, glob, bisect
RE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
d = open(os.path.join(RE, "bin/SIM56000.EXE"), "rb").read()
base = 0x400000
def sec(name):
    pe = struct.unpack_from('<I', d, 0x3c)[0]; ns = struct.unpack_from('<H', d, pe+6)[0]
    so = struct.unpack_from('<H', d, pe+20)[0]
    for i in range(ns):
        o = pe+24+so+i*40
        if d[o:o+8].rstrip(b'\0') == name:
            vs, va, rs, ro = struct.unpack_from('<IIII', d, o+8); return va+base, ro, rs
funcs = {}
for l in open(os.path.join(RE, "out/SIM56000/functions.txt")):
    p = l.split('\t'); funcs[int(p[0], 16)] = p
named = {}; dnames = {}
for f in glob.glob(os.path.join(RE, "names/SIM56000/*.names.txt")):
    if f.endswith("hidden.names.txt"): continue
    for l in open(f, encoding="utf-8"):
        p = l.rstrip("\n").split("\t")
        if l.startswith("#") or len(p) < 3: continue
        a = int(p[0], 16)
        if p[1] == "F": named[a] = p[2]
        else: dnames[a] = p[2]
# command handlers
cmdname = {}
for l in open(os.path.join(RE, "notes/SIM56000/cmd.md"), encoding="utf-8"):
    m = re.match(r'\| (\d+) \| (\w+) \| \w+ \| \w+ \| ([0-9a-f]+) \(\w+\) \| \d \d \| (.*) \|$', l)
    if not m: continue
    c = m.group(2)
    cmdname.setdefault(int(m.group(3), 16), "cmd_%s_parse" % c)
    for i, h in enumerate(re.findall(r'([0-9a-f]{6}):\d', m.group(4))):
        cmdname.setdefault(int(h, 16), "cmd_%s_h%d" % (c, i))
# table references
refs = {}
for n in (b'.data', b'.rdata'):
    va, ro, rs = sec(n)
    for o in range(0, rs-3, 4):
        v = struct.unpack_from('<I', d, ro+o)[0]
        if v in funcs and v not in named: refs.setdefault(v, []).append(va+o)
dsorted = sorted(dnames)
def tabname(ref):
    i = bisect.bisect_right(dsorted, ref)-1
    if i >= 0 and ref-dsorted[i] < 0x400: return dnames[dsorted[i]]
    return None
out = []; used = set(named.values())
def emit(a, nm):
    base_nm = nm; k = 2
    while nm in used: nm = "%s_%d" % (base_nm, k); k += 1
    used.add(nm); out.append((a, nm))
later = []
todo = sorted(a for a in funcs if a < 0x483400 and a not in named)
for a in todo:
    if a in cmdname: emit(a, cmdname[a]); continue
    t = None
    for r in refs.get(a, []):
        t = tabname(r)
        if t: break
    if t:
        t = re.sub(r'_(handlers|tab|table|records|vtable)$', '', t)
        emit(a, "%s_h%06x" % (t, a)); continue
    if any(0x4ad360 <= r < 0x4ad3c0 for r in refs.get(a, [])):
        emit(a, "igrp_method_%06x" % a); continue
    later.append(a)
def cname(c):
    m = re.match(r'FUN_([0-9a-f]+)', c)
    if m:
        x = int(m.group(1), 16)
        return named.get(x) or dict(out).get(x) or "fn_%06x" % x
    return c
for a in later:
    callers = funcs[a][4].replace("callers:", "").split()
    cn = cname(callers[0]) if callers else None
    if cn: cn = re.sub(r"_sub_[0-9a-f]+.*$", "", cn)
    emit(a, ("%s_sub_%06x" % (cn, a)) if cn else "hid_%06x" % a)
with open(os.path.join(RE, "names/SIM56000/hidden.names.txt"), "w") as f:
    f.write("# SIM56000 functions found only via data tables and named mechanically by namehidden.py\n")
    for a, nm in out:
        f.write("%08x\tF\t%s\t\tlow\thidden\n" % (a, nm))
print(len(out), "named;", sum(1 for a in todo if a in cmdname), "commands")
