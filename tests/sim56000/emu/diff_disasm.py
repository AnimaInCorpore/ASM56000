#!/usr/bin/env python3
"""disasm.c (disassemble, dis_move_addrs, dis_ea_addr, dis_agu_addr): translation vs original."""
from common import *
import random

lib = build('disasm', ['disasm.c', 'disfmt.c', 'asm.c'], ['simd_dec.c', 'simd_e.c', 'simd_a.c', 'simd_b.c', 'simd_c.c', 'simd_f.c'])
pe = PE(EXE)
random.seed(41)
OPCL = ctypes.CFUNCTYPE(ctypes.c_long, ctypes.c_ulong, ctypes.c_ulong)
cb1 = OPCL(lambda o, c: pe.call(0x430740, [o & 0xffffffff, c & 0xffffffff]))
ctypes.c_void_p.in_dll(lib, 'cb_opclass_lookup').value = ctypes.cast(cb1, ctypes.c_void_p).value

class Info(ctypes.Structure):
    _fields_ = [('f0', ctypes.c_long * 5), ('rn', ctypes.c_ulong * 8), ('nn', ctypes.c_ulong * 8), ('mn', ctypes.c_ulong * 8),
                ('nwords', ctypes.c_long), ('flags', ctypes.c_ulong), ('ea_a', ctypes.c_ulong), ('ea_b', ctypes.c_ulong), ('ea_c', ctypes.c_ulong)]
lib.disassemble.restype = ctypes.c_long
lib.disassemble.argtypes = [ctypes.POINTER(ctypes.c_ulong), ctypes.c_char_p, ctypes.c_long, ctypes.c_long, ctypes.POINTER(Info)]
lib.dis_agu_addr.argtypes = [ctypes.c_ulong, ctypes.c_ulong, ctypes.c_ulong, ctypes.c_long, ctypes.POINTER(ctypes.c_ulong)]
INS = pe.alloc(16); TEXT = pe.alloc(256); INFO = pe.alloc(0x90); OUT = pe.alloc(16)

fails = {}
def chk(name, ok, msg):
    fails.setdefault(name, [0, 0]); fails[name][0] += 1
    if not ok:
        fails[name][1] += 1
        if fails[name][1] <= 4: print('DIFF', name, msg)

def rnd16():
    return random.choice([random.getrandbits(16), 0, 0xffff, 0x8000, 1, random.getrandbits(8), 0x7fff])

# dis_agu_addr
for _ in range(40000):
    cpu = random.choice([1, 4])
    rn, nn = rnd16(), rnd16()
    mn = random.choice([0, 0xffff, random.getrandbits(16), (1 << random.randint(0, 14)) - 1, 0x8000 | random.getrandbits(15), 0xc000 | random.getrandbits(14)])
    neg = random.choice([0, 1])
    pe.w32(0x4dbefc, cpu); ctypes.c_long.in_dll(lib, 'dis_cpu_level').value = cpu
    pe.w32(OUT, 0xdead)
    pe.call(0x423f90, [rn, nn, mn, neg, OUT])
    w = pe.r32(OUT)
    o = ctypes.c_ulong(0xdead)
    lib.dis_agu_addr(rn, nn, mn, neg, ctypes.byref(o))
    chk('dis_agu_addr', w == (o.value & 0xffffffff), 'rn %x nn %x mn %x neg %d cpu %d: %x vs %x' % (rn, nn, mn, neg, cpu, w, o.value))

# disassemble
words = []
for i in range(109):
    mask = pe.r32(0x4c45b0 + 16 * i); match = pe.r32(0x4c45b0 + 16 * i + 4)
    for _ in range(150): words.append((match | (random.getrandbits(24) & ~mask)) & 0xffffff)
for _ in range(15000): words.append(random.getrandbits(24))
random.shuffle(words)
for w in words:
    cpu = random.choice([1, 4])
    ext = random.getrandbits(24)
    rn = [rnd16() for _ in range(8)]; nn = [rnd16() for _ in range(8)]
    mn = [random.choice([0xffff, random.getrandbits(16), 0, (1 << random.randint(0, 14)) - 1]) for _ in range(8)]
    pe.w32(0x4dbefc, cpu); ctypes.c_long.in_dll(lib, 'dis_cpu_level').value = cpu
    pe.w32(INS, w); pe.w32(INS + 4, ext)
    for k in range(0x90): pe.uc.mem_write(INFO + k, b'\0')
    for k in range(8):
        pe.w32(INFO + 0x14 + 4 * k, rn[k]); pe.w32(INFO + 0x34 + 4 * k, nn[k]); pe.w32(INFO + 0x54 + 4 * k, mn[k])
    for k in range(256): pe.uc.mem_write(TEXT + k, b'\0')
    try:
        r = pe.call(0x423b10, [INS, TEXT, 0, 0, INFO])
    except RuntimeError:
        continue
    wt = pe.rbytes(TEXT, 128).split(b'\0')[0]
    wi = [pe.r32(INFO + 0x74 + 4 * k) for k in range(5)]
    info = Info()
    for k in range(8): info.rn[k] = rn[k]; info.nn[k] = nn[k]; info.mn[k] = mn[k]
    ins = (ctypes.c_ulong * 2)(w, ext)
    buf = ctypes.create_string_buffer(256)
    gr = lib.disassemble(ins, buf, 0, 0, ctypes.byref(info))
    gi = [info.nwords & 0xffffffff, info.flags & 0xffffffff, info.ea_a & 0xffffffff, info.ea_b & 0xffffffff, info.ea_c & 0xffffffff]
    # flags of the original for unused ea fields stay 0 in both
    chk('disassemble', wt == buf.value and (r & 0xffffffff) == (gr & 0xffffffff) and wi == gi,
        'word %06x ext %06x cpu %d: %r %s vs %r %s' % (w, ext, cpu, wt, wi, buf.value, gi))
tot = 0
for k, (n, b) in sorted(fails.items()):
    print('%-16s %6d cases %4d differences' % (k, n, b)); tot += b
sys.exit(1 if tot else 0)
