#!/usr/bin/env python3
"""disfmt.c (117 disassembler formatters, plus dis_ea_tokens and the hex helpers of asm.c): translation vs original."""
from common import *
import random

lib = build('disfmt', ['disfmt.c', 'asm.c'], ['simd_dec.c', 'simd_e.c', 'simd_a.c', 'simd_b.c', 'simd_c.c', 'simd_f.c'])
pe = PE(EXE)
random.seed(31)
OPCL = ctypes.CFUNCTYPE(ctypes.c_long, ctypes.c_ulong, ctypes.c_ulong)
cb1 = OPCL(lambda o, c: pe.call(0x430740, [o & 0xffffffff, c & 0xffffffff]))
ctypes.c_void_p.in_dll(lib, 'cb_opclass_lookup').value = ctypes.cast(cb1, ctypes.c_void_p).value

TOK = pe.alloc(0x200)
G = [('dis_effect_flags', 0x4dbea0), ('dis_sel_a', 0x4dbea4), ('dis_sel_b', 0x4dbea8), ('dis_sel_c', 0x4dbeac),
     ('dis_sel_d', 0x4dbeb0), ('dis_sel_e', 0x4dbeb4), ('dis_val_b', 0x4dbeb8), ('dis_val_c', 0x4dbebc),
     ('dis_val_a', 0x4dbec0), ('dis_val_d', 0x4dbec4), ('dis_val_e', 0x4dbec8)]
HEX = [('dis_hex_ea', 0x4dbe88), ('dis_hex_b', 0x4dbed0), ('dis_hex_c', 0x4dbee8)]
def s32(v): return v - (1 << 32) if v & 0x80000000 else v

handlers = (ctypes.c_void_p * 110).in_dll(lib, 'dis_fmt_handlers')
FN = ctypes.CFUNCTYPE(ctypes.c_long, ctypes.c_ulong, ctypes.POINTER(ctypes.c_long))
bad = n = 0
seen = set()
words = []
for i in range(109):
    mask = pe.r32(0x4c45b0 + 16 * i); match = pe.r32(0x4c45b0 + 16 * i + 4)
    for _ in range(250):
        words.append((match | (random.getrandbits(24) & ~mask)) & 0xffffff)
for _ in range(20000):
    words.append(random.getrandbits(24))
random.shuffle(words)
for w in words:
    cpu = random.choice([1, 4])
    cls = pe.call(0x430740, [w, cpu]) & 0xffffffff
    if cls >= 110:
        continue
    haddr = pe.r32(0x4c1298 + 4 * cls)
    for name, a in G: pe.w32(a, 0x5a5a5a5a)
    for name, a in HEX: pe.wbytes(a, b'\0' * 16)
    for i in range(64): pe.w32(TOK + 4 * i, 0x7e7e7e7e)
    pe.w32(0x4dbefc, cpu)
    try:
        r = pe.call(haddr, [w, TOK])
    except RuntimeError as e:
        continue
    wtok = [pe.r32(TOK + 4 * i) for i in range(64)]
    wg = [pe.r32(a) for _, a in G]
    wh = [pe.rbytes(a, 16).split(b'\0')[0] for _, a in HEX]
    for name, a in G: ctypes.c_ulong.in_dll(lib, name).value = 0x5a5a5a5a
    for name, a in HEX: ctypes.memset(ctypes.addressof(ctypes.c_char.in_dll(lib, name)), 0, 16)
    ctypes.c_long.in_dll(lib, 'dis_cpu_level').value = cpu
    tok = (ctypes.c_long * 64)(*([0x7e7e7e7e] * 64))
    fn = FN(handlers[cls])
    gr = fn(w, tok)
    gtok = [x & 0xffffffff for x in tok]
    gg = [ctypes.c_ulong.in_dll(lib, name).value & 0xffffffff for name, _ in G]
    gh = [ctypes.string_at(ctypes.addressof(ctypes.c_char.in_dll(lib, name))).split(b'\0')[0] for name, _ in HEX]
    n += 1
    seen.add(cls)
    if (r & 0xffffffff) != (gr & 0xffffffff) or wtok != gtok or wg != gg or wh != gh:
        bad += 1
        if bad <= 5:
            print('DIFF class %d word %06x cpu %d: len %d vs %d' % (cls, w, cpu, r, gr))
            print('  tok  want %s\n       got  %s' % ([hex(x) for x in wtok[:r + 1]], [hex(x) for x in gtok[:gr + 1]]))
            print('  glob want %s\n       got  %s' % ([hex(x) for x in wg], [hex(x) for x in gg]))
            print('  hex  want %s got %s' % (wh, gh))
print('disfmt: %d cases over %d classes, %d differences' % (n, len(seen), bad))
sys.exit(1 if bad else 0)
