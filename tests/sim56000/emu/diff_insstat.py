#!/usr/bin/env python3
"""insstat.c (eval_cc, mnemonic_name, insn_stat_classify/operands, stat_lmove_class): translation vs original."""
from common import *
import random

lib = build('insstat', ['insstat.c', 'decode.c'], ['simd_dec.c', 'simd_e.c'])
pe = PE(EXE)
random.seed(21)
OPCL = ctypes.CFUNCTYPE(ctypes.c_long, ctypes.c_ulong, ctypes.c_ulong)
cb1 = OPCL(lambda o, c: pe.call(0x430740, [o & 0xffffffff, c & 0xffffffff]))
cb2 = OPCL(lambda o, f: pe.call(0x430850, [o & 0xffffffff, f & 0xffffffff]))
ctypes.c_void_p.in_dll(lib, 'cb_opclass_lookup').value = ctypes.cast(cb1, ctypes.c_void_p).value
ctypes.c_void_p.in_dll(lib, 'cb_insn_validate').value = ctypes.cast(cb2, ctypes.c_void_p).value
DT = pe.alloc(0x100); pe.w32(0x505790, DT)
cpu = pe.r32(0x4bfc78); ctypes.c_long.in_dll(lib, 'dec_cpu_level').value = cpu

fails = {}
def chk(name, ok, msg):
    fails.setdefault(name, [0, 0])
    fails[name][0] += 1
    if not ok:
        fails[name][1] += 1
        if fails[name][1] <= 4:
            print('DIFF', name, msg)

# eval_cc
lib.eval_cc.restype = ctypes.c_ulong
lib.eval_cc.argtypes = [ctypes.c_ulong, ctypes.c_long]
for ccr in range(0, 256):
    for cc in range(0, 17):
        w = pe.call(0x41cb60, [ccr, cc]) & 0xffffffff
        g = lib.eval_cc(ccr, cc) & 0xffffffff
        chk('eval_cc', w == g, 'ccr %x cc %d: %x vs %x' % (ccr, cc, w, g))

# mnemonic_name
lib.mnemonic_name.restype = ctypes.c_char_p
lib.mnemonic_name.argtypes = [ctypes.c_long]
for i in range(0, 0x70):
    r = pe.call(0x41cd00, [i])
    w = None
    if r:
        w = pe.rbytes(r, 32).split(b'\0')[0]
    g = lib.mnemonic_name(i)
    chk('mnemonic_name', w == g, 'id %d: %r vs %r' % (i, w, g))

class Op(ctypes.Structure):
    _fields_ = [('w', ctypes.c_long * 7)]
class Link(ctypes.Structure):
    pass
Link._fields_ = [('f0', ctypes.c_long), ('next', ctypes.POINTER(Link)), ('ops', ctypes.POINTER(Op))]
class Stat(ctypes.Structure):
    _fields_ = [('f0', ctypes.c_long), ('word0', ctypes.c_long), ('word1', ctypes.c_long), ('flags', ctypes.c_long),
                ('cat', ctypes.c_long), ('op', Op * 4), ('link', ctypes.POINTER(Link)), ('aux', ctypes.c_long)]

def s32(v): return v - (1 << 32) if v & 0x80000000 else v
DEC = pe.alloc(0xc0); STAT = pe.alloc(0xa0); FLAGS = pe.alloc(16)
lib.insn_stat_classify.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_long)]
lib.insn_stat_operands.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_long)]
lib.stat_lmove_class.restype = ctypes.c_long
lib.stat_lmove_class.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_long), ctypes.POINTER(ctypes.c_long)]

def stat_snapshot_orig():
    words = [pe.r32(STAT + 4 * i) for i in range(33)] + [0, pe.r32(STAT + 0x88)]
    lst = []
    p = pe.r32(STAT + 0x84)
    guard = 0
    while p and guard < 4:
        guard += 1
        ops = pe.r32(p + 8)
        lst.append((pe.r32(p), [pe.r32(ops + 4 * i) for i in range(14)] if ops else None))
        p = pe.r32(p + 4)
    return words, lst

def stat_snapshot_host(st):
    words = [st.f0, st.word0, st.word1, st.flags, st.cat]
    for o in st.op:
        words += list(o.w)
    words = [x & 0xffffffff for x in words] + [0, st.aux & 0xffffffff]
    lst = []
    p = st.link
    while p:
        ops = p.contents.ops
        arr = ctypes.cast(ops, ctypes.POINTER(ctypes.c_long * 14)).contents if ops else None
        lst.append((p.contents.f0 & 0xffffffff, [x & 0xffffffff for x in arr] if arr else None))
        p = p.contents.next
    return words, lst

def rand_stat():
    words = [0] * 35
    words[3] = random.getrandbits(11)
    for i in range(5, 33):
        words[i] = random.choice([0, 1, 2, 3, 9, 10, 0xc, 0xe])
    words[34] = random.getrandbits(8)
    return words

CATS = [0x28, 8, 9, 10, 0xb, 0x16, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x27, 0x29]
ndec = 0
for it in range(6000):
    w = random.getrandbits(24)
    if random.random() < 0.4:
        mask = pe.r32(0x4c45b0 + 16 * (it % 109)); match = pe.r32(0x4c45b0 + 16 * (it % 109) + 4)
        w = (match | (random.getrandbits(24) & ~mask)) & 0xffffff
    fam = random.choice([1, 2, 4, 8, 0x200])
    pe.w32(DT + 8, fam)
    lib.set_family(fam)
    for i in range(0x30): pe.w32(DEC + 4 * i, 0)
    pe.w32(DEC + 0xb8, w); pe.w32(DEC + 0xbc, random.getrandbits(24)); pe.w32(FLAGS, 0)
    pe.call(0x41f9e0, [DEC, 0x100, 0, FLAGS])
    decw = [pe.r32(DEC + 4 * i) for i in range(0x30)]
    if random.random() < 0.3:
        decw[0] = random.choice(CATS)                 # exercise the category specific tail
        decw[0x2b] = random.getrandbits(9)
    for i in range(0x30): pe.w32(DEC + 4 * i, decw[i])
    hd = (ctypes.c_long * 0x30)(*[s32(x) for x in decw])
    nops = sum(1 for i in range(4) if decw[2 + 5 * i] != 0)
    nmov = sum(1 for i in range(4) if decw[22 + 5 * i] != 0)
    if not (decw[0x2b] & 0x80) and nops + nmov > 4:
        continue                       # the original would overwrite the link field there
    sw = rand_stat()
    for name, addr, fn in (('insn_stat_classify', 0x41c750, lib.insn_stat_classify), ('insn_stat_operands', 0x41c8b0, lib.insn_stat_operands)):
        for i, x in enumerate(sw): pe.w32(STAT + 4 * i, x)
        pe.w32(STAT + 0x84, 0)
        st = Stat()
        st.f0 = sw[0]; st.word0 = sw[1]; st.word1 = sw[2]; st.flags = sw[3]; st.cat = sw[4]
        for i in range(4):
            for j in range(7): st.op[i].w[j] = s32(sw[5 + 7 * i + j])
        st.aux = sw[34]
        if name == 'insn_stat_operands':
            st.cat = s32(decw[0]); pe.w32(STAT + 0x10, decw[0])
        pe.call(addr, [STAT, DEC])
        fn(ctypes.byref(st), hd)
        a = stat_snapshot_orig(); b = stat_snapshot_host(st)
        chk(name, a == b, 'word %06x cat %x\n  want %s\n  got  %s' % (w, decw[0], a, b))
    # stat_lmove_class on the record produced by operands
    if pe.r32(STAT + 0x84):
        co = pe.alloc(16); f1 = pe.alloc(16)
        for x in (co, f1): pe.w32(x, 0xdead)
        r = pe.call(0x41cd40, [STAT, co, f1])
        c1 = ctypes.c_long(0xdead); c2 = ctypes.c_long(0xdead)
        g = lib.stat_lmove_class(ctypes.byref(st), ctypes.byref(c1), ctypes.byref(c2))
        want = (r & 0xffffffff, pe.r32(co), pe.r32(f1)); got = (g & 0xffffffff, c1.value & 0xffffffff, c2.value & 0xffffffff)
        chk('stat_lmove_class', want == got, 'want %s got %s' % (want, got))
tot = 0
for k, (n, b) in sorted(fails.items()):
    print('%-22s %6d cases %4d differences' % (k, n, b)); tot += b
sys.exit(1 if tot else 0)
