#!/usr/bin/env python3
"""decode_insn and all its class handlers: translation vs original, over many opcode words."""
from common import *
import random

lib = build('decode', ['decode.c'], ['simd_dec.c'])
pe = PE(EXE)
random.seed(11)

OPCL = ctypes.CFUNCTYPE(ctypes.c_long, ctypes.c_ulong, ctypes.c_ulong)
def _opclass(opw, cpu):
    return pe.call(0x430740, [opw & 0xffffffff, cpu & 0xffffffff]) & 0xffffffff
def _validate(opw, fam):
    return pe.call(0x430850, [opw & 0xffffffff, fam & 0xffffffff]) & 0xffffffff
cb1 = OPCL(_opclass); cb2 = OPCL(_validate)
ctypes.c_void_p.in_dll(lib, 'cb_opclass_lookup').value = ctypes.cast(cb1, ctypes.c_void_p).value
ctypes.c_void_p.in_dll(lib, 'cb_insn_validate').value = ctypes.cast(cb2, ctypes.c_void_p).value

# fake device type for both worlds: family word at +8
DT = pe.alloc(0x100)
pe.w32(0x505790, DT)
class DT_(ctypes.Structure):
    _fields_ = [('pad', ctypes.c_char * 0x200)]
dtype = ctypes.create_string_buffer(0x2000)
# struct dev_type of the host: place family via the real struct offsets: use a helper exported by stubs
lib.set_family.argtypes = [ctypes.c_long]
lib.decode_insn.restype = ctypes.c_long
lib.decode_insn.argtypes = [ctypes.POINTER(ctypes.c_long), ctypes.c_long, ctypes.c_long, ctypes.POINTER(ctypes.c_ulong)]
DEC = pe.alloc(0xc0)
FLAGS = pe.alloc(16)
dec_cpu = pe.r32(0x4bfc78)
cpu_c = ctypes.c_long.in_dll(lib, 'dec_cpu_level')
cpu_c.value = dec_cpu

def s32(v): return v - (1 << 32) if v & 0x80000000 else v

def opcodes():
    ws = set()
    for i in range(109):
        mask = pe.r32(0x4c45b0 + 16 * i); match = pe.r32(0x4c45b0 + 16 * i + 4)
        for _ in range(300):
            ws.add((match | (random.getrandbits(24) & ~mask)) & 0xffffff)
    # structured: every class prefix plus random low bits
    for hi in range(0, 256):
        for _ in range(40):
            ws.add((hi << 16) | random.getrandbits(16))
    for _ in range(60000):
        ws.add(random.getrandbits(24))
    for hi in range(0, 0x100):        # parallel move space
        for lo in (0, 0x80, 0xff):
            ws.add((hi << 16) | (random.getrandbits(8) << 8) | lo)
    return sorted(ws)

bad = n = 0
hist = {}
ws = opcodes()
random.shuffle(ws)
FAM = [1, 2, 4, 8, 0x200, 0x400, 0x1000, 0x2000, 0x80, 0x800, 0x44, 0x108]
for w in ws:
    fam = random.choice(FAM)
    ext = random.getrandbits(24)
    pc = random.getrandbits(16)
    pe.w32(DT + 8, fam)
    lib.set_family(fam)
    for i in range(0x30):
        pe.w32(DEC + 4 * i, 0)
    pe.w32(DEC + 0xb8, w); pe.w32(DEC + 0xbc, ext)
    pe.w32(FLAGS, 0)
    r = pe.call(0x41f9e0, [DEC, pc, 0, FLAGS])
    want = [pe.r32(DEC + 4 * i) for i in range(0x30)]
    wflags = pe.r32(FLAGS)
    wglob = (pe.r32(0x4dbe78), pe.r32(0x4dbe7c), pe.r32(0x4dbe80))
    d = (ctypes.c_long * 0x30)()
    d[0x2e] = w; d[0x2f] = ext
    fl = ctypes.c_ulong(0)
    gr = lib.decode_insn(d, pc, 0, ctypes.byref(fl))
    got = [x & 0xffffffff for x in d]
    gglob = tuple(ctypes.c_long.in_dll(lib, s).value & 0xffffffff for s in ('dec_uses_extword', 'dec_extword', 'dec_pc'))
    n += 1
    hist[want[0]] = hist.get(want[0], 0) + 1
    if want != got or wflags != (fl.value & 0xffffffff) or (r & 0xffffffff) != (gr & 0xffffffff) or wglob != gglob:
        bad += 1
        if bad <= 6:
            print('DIFF word %06x ext %06x fam %x' % (w, ext, fam))
            print('  want ret=%d fl=%x glob=%s' % (r, wflags, wglob))
            print('  got  ret=%d fl=%x glob=%s' % (gr, fl.value, gglob))
            for i in range(0x30):
                if want[i] != got[i]:
                    print('    dec[%d] want %x got %x' % (i, want[i], got[i]))
print('mnemonic classes seen: %d, illegal %d' % (len(hist), hist.get(0x19, 0)))
print('decode_insn: %d opcodes, %d differences' % (n, bad))
sys.exit(1 if bad else 0)
