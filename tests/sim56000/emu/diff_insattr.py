#!/usr/bin/env python3
"""insattr.c / insexec.c (instruction attribute handlers, opclass_lookup, insn_validate): translation vs original."""
from common import *
import random

lib = build('insattr', ['insattr.c', 'insexec.c', 'alu.c'], ['simd_dec.c', 'simd_e.c'])
pe = PE(EXE)
random.seed(51)
fails = {}
def chk(name, ok, msg):
    fails.setdefault(name, [0, 0]); fails[name][0] += 1
    if not ok:
        fails[name][1] += 1
        if fails[name][1] <= 6: print('DIFF', name, msg)

def rnd_opw():
    r = random.random()
    if r < 0.3: return random.getrandbits(24)
    if r < 0.6: return random.getrandbits(24) & random.getrandbits(24)
    if r < 0.8: return random.getrandbits(24) | random.getrandbits(24)
    return random.choice([0, 0xffffff, 0x8000, 0x400, 0x40, 0x3400 << 0, 0x3400 << 8 >> 8])

ptr = ctypes.c_void_p
def mine(name, n):
    return (ptr * n).in_dll(lib, name)
def mycall(fp, nargs, args):
    f = ctypes.CFUNCTYPE(ctypes.c_long, *([ctypes.c_ulong] * nargs))(fp)
    return f(*args)

# the original handler tables: address -> compare with mine (identified by calling)
tables = [('insn_exec_handlers', 0x4c36f0, 110, 4), ('insn_move_handlers', 0x4c3ad0, 110, 4),
          ('insn_class_handlers', 0x4c3c88, 110, 4), ('insn_valid_handlers', 0x4c4c90, 109, 1)]
for name, base, n, nargs in tables:
    m = mine(name, n)
    for i in range(n):
        wa = pe.r32(base + 4 * i)
        for _ in range(300):
            opw = rnd_opw()
            dev = random.randint(0, 6)
            mode = random.choice([0, 0, 1, 2, 3])
            sel = random.choice([0, 1, 2, 3])
            args = [opw, dev, mode, sel][:nargs]
            w = pe.call(wa, args) & 0xffffffff
            g = mycall(m[i], nargs, args) & 0xffffffff
            chk(name, w == g, 'idx %d addr %x args %s: %x vs %x' % (i, wa, [hex(a) for a in args], w, g))

# opclass_lookup / lookup_any
lib.opclass_lookup.restype = ctypes.c_long
lib.opclass_lookup.argtypes = [ctypes.c_ulong, ctypes.c_ulong]
lib.opclass_lookup_any.restype = ctypes.c_long
lib.opclass_lookup_any.argtypes = [ctypes.c_ulong]
for _ in range(20000):
    opw = rnd_opw(); cpu = random.randint(0, 6)
    w = pe.call(0x430740, [opw, cpu]) & 0xffffffff
    g = lib.opclass_lookup(opw, cpu) & 0xffffffff
    chk('opclass_lookup', w == g, '%x cpu %d: %x vs %x' % (opw, cpu, w, g))
    w = pe.call(0x4307d0, [opw]) & 0xffffffff
    g = lib.opclass_lookup_any(opw) & 0xffffffff
    chk('opclass_lookup_any', w == g, '%x: %x vs %x' % (opw, w, g))
    w = pe.call(0x430850, [opw, cpu]) & 0xffffffff
    lib.insn_validate.restype = ctypes.c_long
    lib.insn_validate.argtypes = [ctypes.c_ulong, ctypes.c_ulong]
    g = lib.insn_validate(opw, cpu) & 0xffffffff
    chk('insn_validate', w == g, '%x cpu %d: %x vs %x' % (opw, cpu, w, g))
    w = pe.call(0x42ff20, [opw]) & 0xffffffff
    lib.ea_mode_index.restype = ctypes.c_long
    lib.ea_mode_index.argtypes = [ctypes.c_ulong]
    g = lib.ea_mode_index(opw) & 0xffffffff
    chk('ea_mode_index', w == g, '%x: %x vs %x' % (opw, w, g))

# top level info functions (records compared by index)
REC = pe.alloc(16)
ER, MR = 0x4c2bb0, 0x4c38a8
lib.insn_exec_info.argtypes = [ctypes.c_ulong, ctypes.c_ulong, ctypes.c_long, ctypes.c_long, ctypes.POINTER(ctypes.c_void_p)]
lib.insn_move_info.argtypes = [ctypes.c_ulong, ctypes.c_long, ctypes.c_long, ctypes.POINTER(ctypes.c_void_p), ctypes.c_ulong]
lib.insn_class_code.restype = ctypes.c_ulong
lib.insn_class_code.argtypes = [ctypes.c_ulong, ctypes.c_long, ctypes.c_long, ctypes.c_ulong]
lib.insn_ea_class.argtypes = [ctypes.c_ulong, ctypes.c_long, ctypes.POINTER(ctypes.c_ulong), ctypes.c_ulong]
er = ctypes.addressof(ctypes.c_long.in_dll(lib, 'insn_exec_records'))
mr = ctypes.addressof(ctypes.c_long.in_dll(lib, 'insn_move_records'))
for _ in range(30000):
    opw = rnd_opw(); dev = random.randint(0, 6); mode = random.choice([0, 0, 1, 2]); sel = random.randint(0, 0x10)
    p = ptr(0)
    pe.w32(REC, 0xdead)
    pe.call(0x42eec0, [dev, opw, mode, sel, REC])
    lib.insn_exec_info(dev, opw, mode, sel, ctypes.byref(p))
    w = pe.r32(REC)
    chk('insn_exec_info', w == 0xdead and False or (w != 0xdead and w - ER == (p.value - er) // 2) or False, '%x dev %d mode %d sel %d: %x vs %x' % (opw, dev, mode, sel, w, p.value))
    pe.w32(REC, 0xdead)
    pe.call(0x42f2a0, [opw, mode, sel, REC, dev])
    lib.insn_move_info(opw, mode, sel, ctypes.byref(p), dev)
    w = pe.r32(REC)
    chk('insn_move_info', w - MR == (p.value - mr) // 2, '%x dev %d mode %d sel %d: %x vs %x' % (opw, dev, mode, sel, w, p.value))
    w = pe.call(0x42fdb0, [opw, mode, sel, dev]) & 0xffffffff
    g = lib.insn_class_code(opw, mode, sel, dev) & 0xffffffff
    chk('insn_class_code', w == g, '%x dev %d mode %d sel %d: %x vs %x' % (opw, dev, mode, sel, w, g))
    fl = random.randint(0, 1)
    pe.w32(REC, 0xdead)
    pe.call(0x42fe10, [opw, fl, REC, dev])
    o = ctypes.c_ulong(0xdead)
    lib.insn_ea_class(opw, fl, ctypes.byref(o), dev)
    chk('insn_ea_class', pe.r32(REC) == (o.value & 0xffffffff), '%x fl %d dev %d: %x vs %x' % (opw, fl, dev, pe.r32(REC), o.value))

bad = 0
for k, (n, f) in sorted(fails.items()):
    print('%-20s %6d cases, %d differences' % (k, n, f)); bad += f
sys.exit(1 if bad else 0)
