"""Make fixed-time copies of the original tools for reproducible comparisons.

The CRT time() of each binary (the only place that reads the clock) is
overwritten with
    mov eax, T ; mov ecx,[esp+4] ; test ecx,ecx ; jz +2 ; mov [ecx],eax ; ret
so it always returns T.  Copies go to re/bin_ft/; binaries without time()
are copied unchanged.  The rebuilt tools honour SOURCE_DATE_EPOCH=T instead.

usage: patchtime.py [T]      (default 931953600 = 1999-07-14 12:00:00 UTC)
"""
import os, sys, struct, shutil

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from x86dis import load

RE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
T = int(sys.argv[1]) if len(sys.argv) > 1 else 931953600

def va2off(secs, va):
    for sva, sz, roff, rsz, _ in secs:
        if sva <= va < sva + rsz:
            return roff + va - sva
    raise ValueError(hex(va))

os.makedirs(os.path.join(RE, "bin_ft"), exist_ok=True)
for exe in sorted(os.listdir(os.path.join(RE, "bin"))):
    src = os.path.join(RE, "bin", exe)
    dst = os.path.join(RE, "bin_ft", exe)
    shutil.copy2(src, dst)
    names = os.path.join(RE, "crt", exe[:-4] + ".names.txt")
    addr = None
    for l in open(names, encoding="utf-8"):
        p = l.split("\t")
        if len(p) > 2 and p[1] == "F" and p[2] == "time":
            addr = int(p[0], 16)
    if addr is None:
        print("%-12s unchanged" % exe)
        continue
    d, base, secs = load(src)
    off = va2off(secs, addr)
    code = (b"\xb8" + struct.pack("<I", T) + b"\x8b\x4c\x24\x04\x85\xc9\x74\x02\x89\x01\xc3")
    buf = bytearray(open(dst, "rb").read())
    buf[off:off + len(code)] = code
    open(dst, "wb").write(buf)
    print("%-12s time() at %08x patched to return %d" % (exe, addr, T))
