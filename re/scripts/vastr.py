#!/usr/bin/env python3
"""vastr.py EXE VA... : print the C string (or --dbl a double) stored at each virtual address.
   Also: vastr.py EXE --scan file.c  prints every s_*_00XXXXXX / DAT_00XXXXXX string referenced in a Ghidra export."""
import sys, struct, re

def load(path):
    d = open(path, 'rb').read()
    pe = struct.unpack_from('<I', d, 0x3c)[0]
    n = struct.unpack_from('<H', d, pe + 6)[0]
    opt = struct.unpack_from('<H', d, pe + 20)[0]
    base = struct.unpack_from('<I', d, pe + 24 + 28)[0]
    o = pe + 24 + opt
    secs = []
    for i in range(n):
        vs, va, rs, ro = struct.unpack_from('<IIII', d, o + 8 + i * 40)
        secs.append((va, vs, ro))
    return d, base, secs

def cstr(img, va):
    d, base, secs = img
    r = va - base
    for a, vs, ro in secs:
        if a <= r < a + vs:
            p = ro + r - a
            return d[p:d.index(b'\0', p)].decode('latin1')
    return None

def dbl(img, va):
    d, base, secs = img
    r = va - base
    for a, vs, ro in secs:
        if a <= r < a + vs:
            return struct.unpack_from('<d', d, ro + r - a)[0]

if __name__ == '__main__':
    img = load(sys.argv[1])
    if sys.argv[2] == '--scan':
        seen = set()
        for m in re.finditer(r'(?:s_\w*?_|DAT_)(00[0-9a-f]{6})\b', open(sys.argv[3]).read()):
            va = int(m.group(1), 16)
            if va not in seen:
                seen.add(va)
                print('%08x %r' % (va, cstr(img, va)))
    elif sys.argv[2] == '--dbl':
        for a in sys.argv[3:]:
            print(a, dbl(img, int(a, 16)))
    else:
        for a in sys.argv[2:]:
            print(a, repr(cstr(img, int(a, 16))))
