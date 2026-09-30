"""Make patched COFF (.cld) variants of t2.cld / t3.cld for the srec tests.

The assembler only writes DSP56000 files, so other processors, memory
spaces and broken files are made by patching the big-endian headers.
Run from tests/srec: python mkcoff.py
"""
import struct

FILHSZ, SCNHSZ = 0x1c, 0x34

def load(name):
    return bytearray(open(name, "rb").read())

def get(d, off):
    return struct.unpack_from(">I", d, off)[0]

def put(d, off, v):
    struct.pack_into(">I", d, off, v & 0xffffffff)

def scn(d, i):
    return FILHSZ + get(d, 20) + i * SCNHSZ

def nscns(d):
    return get(d, 4)

def find(d, mem, block=None):
    """sections (index) in COFF memory space mem"""
    r = []
    for i in range(nscns(d)):
        s = scn(d, i)
        if get(d, s + 12) == mem and get(d, s + 24) != 0:
            if block is None or bool(get(d, s + 48) & 0x400) == block:
                r.append(i)
    return r

def save(name, d):
    open(name, "wb").write(bytes(d))

t2 = load("t2.cld")
t3 = load("t3.cld")

# other processors (magic numbers 0x2c5..0x2cc) and a bad one
for magic, name in ((0x2c6, "m96000"), (0x2c7, "m56100"), (0x2c8, "m56300"),
                    (0x2c9, "m56800"), (0x2ca, "m56600"), (0x2cb, "m100"),
                    (0x2cc, "m56700"), (0x2cd, "badmagic")):
    d = bytearray(t3)
    put(d, 0, magic)
    save(name + ".cld", d)

# 56100 style file without Y/L data (only P and X)
d = bytearray(t3)
put(d, 0, 0x2c7)
for i in find(d, 2) + find(d, 3):
    put(d, scn(d, i) + 24, 0)            # size 0: section skipped
save("p56100.cld", d)

# 56600: flag 0x4000 on an X section, one X section moved to E memory
d = bytearray(t3)
put(d, 0, 0x2ca)
x = find(d, 1)
put(d, scn(d, x[0]) + 48, get(d, scn(d, x[0]) + 48) | 0x4000)
put(d, scn(d, x[1]) + 12, 0x1d)
for i in find(d, 2) + find(d, 3):
    put(d, scn(d, i) + 24, 0)            # drop Y and L
save("e56600.cld", d)

# 56300 with E memory and an entry point above 64K
d = bytearray(t3)
put(d, 0, 0x2c8)
put(d, scn(d, find(d, 1)[0]) + 12, 0x1c)
put(d, FILHSZ + 0x14, 0x123456)
save("e56300.cld", d)

# 56000 with D memory (0x11d) and extended spaces (PA, XE, YI, LI)
d = bytearray(t3)
x = find(d, 1)
put(d, scn(d, x[0]) + 12, 0x11d)
put(d, scn(d, x[1]) + 12, 0x12)
put(d, scn(d, find(d, 0)[0]) + 12, 0xb)
put(d, scn(d, find(d, 2)[0]) + 12, 0x18)
put(d, scn(d, find(d, 3)[0]) + 12, 10)
save("dmem.cld", d)

# 96000 spaces: LAA (5), XA (0x10), YA (0x15)
d = bytearray(t3)
put(d, 0, 0x2c6)
put(d, scn(d, find(d, 3)[0]) + 12, 5)
put(d, scn(d, find(d, 1)[0]) + 12, 0x10)
put(d, scn(d, find(d, 2)[0]) + 12, 0x15)
save("s96000.cld", d)

# invalid memory spaces
d = bytearray(t2); put(d, scn(d, find(d, 1)[0]) + 12, 0x1a); save("badmem.cld", d)
d = bytearray(t2); put(d, scn(d, find(d, 1)[0]) + 12, 0x11e); save("badmem2.cld", d)
d = bytearray(t2); put(d, scn(d, find(d, 1)[0]) + 12, 0xffffffff); save("badmem3.cld", d)

# relocatable (F_RELFLG clear)
d = bytearray(t2); put(d, 24, get(d, 24) & ~1); save("reloc.cld", d)
# no sections
d = bytearray(t2); put(d, 4, 0); save("nosec.cld", d)
# section header table past the end of the file
d = bytearray(t2); put(d, 4, 200); save("manysec.cld", d)
# truncated: header only, part of the file header, part of the raw data
save("hdronly.cld", t2[:FILHSZ + get(t2, 20)])
save("short.cld", t2[:10])
d = bytearray(t3); last = max(get(d, scn(d, i) + 28) for i in range(nscns(d)))
save("trunc.cld", d[:last + 2])
# optional header longer than the file
d = bytearray(t2); put(d, 20, 0x100000); save("bigopt.cld", d)
# raw data pointer negative -> cannot seek
d = bytearray(t2); put(d, scn(d, 0) + 28, 0xfffffff0); save("badptr.cld", d)
# block section of 3 words: the third word becomes the address
d = bytearray(t3); b = find(d, 1, True)[0]
put(d, scn(d, b) + 24, 3); save("blk3.cld", d)
# odd L data word count
d = bytearray(t3); l = find(d, 3, False)[0]
put(d, scn(d, l) + 24, get(d, scn(d, l) + 24) - 1); save("lodd.cld", d)

# without optional header: drop it and move all file pointers
d = bytearray(t2)
opt = get(d, 20)
for i in range(nscns(d)):
    s = scn(d, i)
    for o in (28, 32, 36):
        if get(d, s + o):
            put(d, s + o, get(d, s + o) - opt)
put(d, 12, get(d, 12) - opt)
put(d, 20, 0)
save("noopt.cld", d[:FILHSZ] + d[FILHSZ + opt:])
