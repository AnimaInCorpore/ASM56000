#!/usr/bin/env python3
"""reg_field_pack: translation vs original."""
from common import *
import random

lib = build('memacc', ['memacc.c'])
lib.reg_field_pack.restype = ctypes.c_ulong
lib.reg_field_pack.argtypes = [ctypes.c_long, ctypes.c_ulong, ctypes.c_long]
pe = PE(EXE)
random.seed(1)
bad = n = 0
ids = list(range(0x1d, 0x5d)) + list(range(0x5d, 0x9d)) + list(range(0x9d, 0xdb))
for id_ in ids:
    u = id_ - 0x1d
    nparts = [2,1,4,2,6,3,4,2][u & 7] if not (u & 0x80) else [5,3,3,2][u & 3]
    for idx in range(0, nparts):
        for _ in range(6):
            val = random.choice([random.getrandbits(24), random.getrandbits(12), random.getrandbits(4), 0, 1, 0xffffff])
            try:
                want = pe.call(0x42c7f0, [id_, val, idx])
            except RuntimeError as e:
                continue      # table index out of range in the original (reads garbage): skip
            got = lib.reg_field_pack(id_, val, idx) & 0xffffffff
            n += 1
            if got != want:
                bad += 1
                if bad < 10:
                    print('id %x val %x idx %d: want %x got %x' % (id_, val, idx, want, got))
print('reg_field_pack: %d cases, %d differences' % (n, bad))
sys.exit(1 if bad else 0)
