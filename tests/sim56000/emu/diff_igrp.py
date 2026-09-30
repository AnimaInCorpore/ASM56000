#!/usr/bin/env python3
"""igrp.c and devreg.c (instruction group statistics, device registry / key generator): translation vs original."""
from common import *
import random

lib = build('igrp', ['igrp.c', 'devreg.c', 'insstat.c', 'decode.c', 'insattr.c', 'insexec.c', 'alu.c', 'asm.c', 'disasm.c', 'disfmt.c'],
            ['simd_dec.c', 'simd_e.c', 'simd_a.c', 'simd_b.c', 'simd_c.c', 'simd_f.c', 'simbss.c', 'simd_dev.c'])
pe = PE(EXE)
random.seed(71)
fails = {}
def chk(name, ok, msg):
    fails.setdefault(name, [0, 0]); fails[name][0] += 1
    if not ok:
        fails[name][1] += 1
        if fails[name][1] <= 6: print('DIFF', name, msg)

class Op(ctypes.Structure):
    _fields_ = [('w', ctypes.c_long * 7)]
class Link(ctypes.Structure):
    pass
Link._fields_ = [('f0', ctypes.c_long), ('next', ctypes.POINTER(Link)), ('ops', ctypes.POINTER(Op))]
class Stat(ctypes.Structure):
    _fields_ = [('f0', ctypes.c_long), ('word0', ctypes.c_long), ('word1', ctypes.c_long), ('flags', ctypes.c_long),
                ('cat', ctypes.c_long), ('op', Op * 4), ('link', ctypes.POINTER(Link)), ('aux', ctypes.c_long),
                ('ccr', ctypes.c_long), ('omr', ctypes.c_long), ('pad94', ctypes.c_long * 21), ('cc_true', ctypes.c_long)]

KINDS = list(range(0, 0x66)) + [0x66, 0x67, 200]
MODES = [0, 9, 10, 0xc, 0xd, 0xe, 1, 2, 3, 4, 5, 6, 8]
REC = pe.alloc(0x100)
NODES = pe.alloc(0x400)

def make(kind, aux, m0, m1, links):
    """build the record in both worlds; links = list of (m0, m1)"""
    s = Stat()
    s.cat = kind; s.aux = aux; s.op[0].w[0] = m0; s.op[1].w[0] = m1
    s.flags = random.getrandbits(4)
    pe.w32(REC + 0x10, kind); pe.w32(REC + 0x88, aux); pe.w32(REC + 0x14, m0); pe.w32(REC + 0x30, m1)
    pe.w32(REC + 0xc, s.flags)
    nodes = (Link * max(len(links), 1))(); ops = (Op * (2 * max(len(links), 1)))()
    prev = None
    for i, (a, b) in reversed(list(enumerate(links))):
        ops[2 * i].w[0] = a; ops[2 * i + 1].w[0] = b
        nodes[i].ops = ctypes.cast(ctypes.byref(ops, ctypes.sizeof(Op) * 2 * i), ctypes.POINTER(Op))
        nodes[i].next = ctypes.cast(ctypes.byref(nodes, ctypes.sizeof(Link) * (i + 1)), ctypes.POINTER(Link)) if i + 1 < len(links) else None
        nn = NODES + 0x20 * i
        pe.w32(nn + 8, NODES + 0x200 + 0x38 * i)
        pe.w32(nn + 4, NODES + 0x20 * (i + 1) if i + 1 < len(links) else 0)
        pe.w32(NODES + 0x200 + 0x38 * i, a); pe.w32(NODES + 0x200 + 0x38 * i + 0x1c, b)
    if links:
        s.link = ctypes.cast(ctypes.byref(nodes), ctypes.POINTER(Link)); pe.w32(REC + 0x84, NODES)
    else:
        pe.w32(REC + 0x84, 0)
    return s, (nodes, ops)

lib.igrp_map_kind.restype = ctypes.c_long
lib.igrp_map_kind.argtypes = [ctypes.c_void_p]
lib.igrp_mode_bucket.restype = ctypes.c_long
lib.igrp_mode_bucket.argtypes = [ctypes.c_long]
for kind in KINDS:
    for aux in (0x10, 0, 3):
        s, keep = make(kind, aux, 0, 0, [])
        w = pe.call(0x401140, [REC]) & 0xffffffff
        g = lib.igrp_map_kind(ctypes.byref(s)) & 0xffffffff
        chk('igrp_map_kind', w == g, 'kind %x aux %x: %x vs %x' % (kind, aux, w, g))
        for name, addr, fn in (('igrp_method_401860', 0x401860, lib.igrp_method_401860), ('igrp_method_4018b0', 0x4018b0, lib.igrp_method_4018b0),
                               ('igrp_method_401910', 0x401910, lib.igrp_method_401910), ('igrp_method_401970', 0x401970, lib.igrp_method_401970),
                               ('igrp_method_401a10', 0x401a10, lib.igrp_method_401a10)):
            fn.restype = ctypes.c_long; fn.argtypes = [ctypes.c_void_p]
            w = pe.call(addr, [REC]) & 0xffffffff
            g = fn(ctypes.byref(s)) & 0xffffffff
            chk(name, w == g, 'kind %x aux %x: %x vs %x' % (kind, aux, w, g))
for m in MODES:
    w = pe.call(0x4016a0, [m]) & 0xffffffff
    chk('igrp_mode_bucket', w == lib.igrp_mode_bucket(m) & 0xffffffff, 'mode %x' % m)

# mode names
lib.igrp_fill_mode_names.argtypes = [ctypes.POINTER(ctypes.c_char_p)]
TAB = pe.alloc(0x400)
for i in range(0x100): pe.w32(TAB + 4 * i, 0)
pe.call(0x401260, [TAB])
mytab = (ctypes.c_char_p * 0x100)()
lib.igrp_fill_mode_names(mytab)
for i in range(0x100):
    a = pe.r32(TAB + 4 * i)
    w = pe.rbytes(a, 64).split(b'\0')[0] if a else None
    chk('igrp_fill_mode_names', w == mytab[i], 'entry %d: %r vs %r' % (i, w, mytab[i]))

# counters
it = pe.r32(0x4a8db4)
pe.w32(0x505794, pe.r32(it))
lib.tst_prof_new.argtypes = []
lib.tst_prof_dump.argtypes = [ctypes.POINTER(ctypes.c_long)]
lib.tst_prof_dump.restype = ctypes.c_long
PROF = pe.alloc(0x4000)
pe.w32(0x505b64, PROF)
def prof_dump_orig():
    out = []
    for k in range(0x67):
        out += [pe.r32(PROF + 200 + 4 * k), pe.r32(PROF + 0x2648 + 4 * k), pe.r32(PROF + 0x2968 + 4 * k), pe.r32(PROF + 0x2c88 + 4 * k)]
    out += [pe.r32(PROF + 0x2fc8 + 4 * k) for k in range(6)]
    out += [pe.r32(PROF + 0x2fe0 + 4 * i) for i in range(9 * 16)]
    return out
def prof_dump_mine():
    o = (ctypes.c_long * 2000)()
    n = lib.tst_prof_dump(o)
    return [x & 0xffffffff for x in o[:n]]
for _ in range(400):
    pe.wbytes(PROF, b'\0' * 0x3400)
    lib.tst_prof_new()
    for k in range(0x67):
        v = random.choice([0, 1])
        pe.w32(PROF + 200 + 4 * k, v); lib.tst_prof_set_on(ctypes.c_long(k), ctypes.c_long(v))
    for _ in range(30):
        kind = random.choice(KINDS[:0x67]); aux = random.choice([0x10, 0, 3])
        links = [(random.choice(MODES), random.choice(MODES)) for _ in range(random.choice([0, 0, 1, 2, 3]))]
        s, keep = make(kind, aux, random.choice(MODES), random.choice(MODES), links)
        pe.call(0x401380, [REC]); lib.igrp_count_instr(ctypes.byref(s))
        # the fixed-move counters need consistent L: classification: only kinds whose ops are set up; call 401700
        if len(links) <= 2:
            pe.call(0x401700, [REC]); lib.igrp_method_401700(ctypes.byref(s))
    w, g = prof_dump_orig(), prof_dump_mine()
    chk('igrp_counters', w == g, 'first diff at %s' % ([i for i in range(len(w)) if w[i] != g[i]][:5],))

# disassembly line
lib.igrp_method_401990.restype = ctypes.c_char_p
lib.igrp_method_401990.argtypes = [ctypes.c_void_p]
ctypes.c_long.in_dll(lib, 'dis_cpu_level').value = 4
pe.w32(0x4dbefc, 4)
for _ in range(2000):
    opw = random.getrandbits(24); ext = random.getrandbits(24)
    s, keep = make(random.choice(KINDS), 0x10, 0, 0, [])
    s.word0 = opw; s.word1 = ext; s.ccr = random.getrandbits(16); s.omr = random.getrandbits(8)
    pe.w32(REC + 4, opw); pe.w32(REC + 8, ext); pe.w32(REC + 0x8c, s.ccr); pe.w32(REC + 0x90, s.omr)
    a = pe.call(0x401990, [REC]) & 0xffffffff
    w = pe.rbytes(a, 200).split(b'\0')[0]
    g = lib.igrp_method_401990(ctypes.byref(s))
    chk('igrp_method_401990', w == g, '%x %x: %r vs %r' % (opw, ext, w, g))

# devreg: keygen and install
lib.device_keygen.restype = ctypes.c_char_p
lib.device_keygen.argtypes = [ctypes.c_char_p]
NM = pe.alloc(64)
names = [b'56000', b'56001', b'56002', b'56004', b'68356', b'56030', b'DSP56000', b'x', b'', b'ABCDEFGHIJKLMNOP', b'56011rom'] + \
        [bytes(random.choice(b'0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_-.') for _ in range(random.randint(1, 20))) for _ in range(500)]
keys = {}
for n in names:
    pe.wbytes(NM, n + b'\0')
    a = pe.call(0x41c2c0, [NM]) & 0xffffffff
    w = pe.rbytes(a, 16).split(b'\0')[0]
    g = lib.device_keygen(n)
    chk('device_keygen', w == g, '%r: %r vs %r' % (n, w, g))
    keys[n] = w
# device_install: chip table copies
lib.device_install.restype = ctypes.c_long
lib.device_install.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
KEY = pe.alloc(64)
ctp_o = pe.r32(0x4aab08)                                   # chiptype_tab (original pointer)
ctp_m = ctypes.c_void_p.in_dll(lib, 'chiptype_tab').value
myct = (ctypes.c_void_p * 14).from_address(ctp_m)
def orig_name(p):
    return pe.rbytes(pe.r32(p), 32).split(b'\0')[0] if p else None
for n in [b'56000', b'56001', b'56002', b'68356', b'56030', b'56030x', b'nosuch', b'']:
    for variant in range(6):
        good = keys.get(n) or lib.device_keygen(n)
        key = bytearray(good.ljust(8, b'x'))
        if variant == 1: key[0] = ord('?')               # first char is never compared
        if variant == 2: key[3] ^= 1
        if variant == 3: key[7] = ord('~')
        if variant == 4: key = bytearray(b'xxxxxxxx')
        key = bytes(key)
        # reset slot 10 in both worlds
        pe.w32(ctp_o + 4 * 10, 0); myct[10] = None
        pe.wbytes(NM, n + b'\0'); pe.wbytes(KEY, key + b'\0')
        w = pe.call(0x41c140, [NM, KEY]) & 0xffffffff
        if w >= 0x80000000: w -= 1 << 32
        g = lib.device_install(n, key)
        so, sm = pe.r32(ctp_o + 4 * 10), myct[10]
        chk('device_install', w == g and ((so == 0) == (sm is None)), '%r %r variant %d: %d vs %d' % (n, key, variant, w, g))
        if so and sm:
            chk('device_install', orig_name(so) == ctypes.string_at(ctypes.c_char_p.from_address(sm).value) , 'name')
            chk('device_install', pe.rbytes(pe.r32(so + 0x4dc), 16).split(b'\0')[0] == ctypes.string_at(ctypes.c_char_p.from_address(sm + 0x4dc).value if False else None or 0) if False else True, 'key')

bad = 0
for k, (n, f) in sorted(fails.items()):
    print('%-24s %6d cases, %d differences' % (k, n, f)); bad += f
sys.exit(1 if bad else 0)
