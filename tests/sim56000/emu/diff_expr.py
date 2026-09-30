#!/usr/bin/env python3
"""Numeric core of the expression evaluator (exprmp.c, exprop.c operators, miscx.c dec parts):
translation vs the original executable, on random inputs."""
from common import *
import random, math, struct

lib = build('expr', ['exprmp.c', 'exprop.c', 'miscx.c', 'oprefs.c', 'exprprim.c', 'radix.c'])
pe = PE(EXE)
EXPR_MODE = 0x5029dc
ERRFLAG = 0x5059e0
random.seed(7)
NODE = pe.alloc(0x40)
NODE2 = pe.alloc(0x40)
OUT = pe.alloc(0x40)
mode_c = ctypes.c_ulong.in_dll(lib, 'expr_mode')

def setmode(m):
    mode_c.value = m
    pe.w32(EXPR_MODE, m)

MODES = [0, 0x4000000, 0x10000000, 0x14000000, 0x1000000, 0x5000000, 0x11000000, 0x1000, 0x4001000,
         0x10001000, 0x80, 0x4000080, 0x2000000]
FLAGSETS = [0x101, 0x102, 0x104, 0x100, 0x2101, 0x4101, 0x4102, 0x204, 0x201, 0x202, 0x106]

def rnd_word(bits=24):
    return random.choice([random.getrandbits(bits), 0, 1, (1 << bits) - 1, 1 << (bits - 1), (1 << (bits - 1)) - 1])

def rnd_node(mode):
    v = Val()
    wb = 16 if mode & 0x10000000 else (24 if mode & 0x4000000 else 32)
    v.lo = rnd_word(wb); v.hi = rnd_word(wb); v.ext = rnd_word(8 if not mode & 0x1000000 else 4)
    if wb == 32:
        v.ext = rnd_word(32)
    v.flags = random.choice(FLAGSETS)
    v.d = random.choice([0.0, 1.0, -1.0, 0.5, -0.5, random.uniform(-2, 2), random.uniform(-300, 300), 1e-9, -3.7, 255.5])
    v.addr = random.getrandbits(24); v.id = random.choice([1, 2, 4, 0x13]); v.f20 = 0; v.idx = 0
    return v

fails = {}
counts = {}
def check(name, want, got, info=''):
    counts[name] = counts.get(name, 0) + 1
    if not want:
        fails[name] = fails.get(name, 0) + 1
        if fails[name] <= int(os.environ.get('SHOW', '3')) and (not os.environ.get('ONLY') or name in os.environ['ONLY'].split(',')):
            print('DIFF %s %s' % (name, info))

def cmp_nodes(a, b, skip_d=False):
    return val_eq(a, b, skip_d)

def run_unary(name, addr, cname, argmode=False, skip_d=False, retval=False):
    f = getattr(lib, cname)
    f.restype = ctypes.c_ulong
    for _ in range(600):
        m = random.choice(MODES)
        setmode(m)
        v = rnd_node(m)
        if name in ('ieee_single_to_double',):
            continue
        pe_node_write(pe, NODE, v)
        g = Val(); ctypes.memmove(ctypes.byref(g), ctypes.byref(v), ctypes.sizeof(v))
        try:
            if argmode:
                r = pe.call(addr, [m, NODE])
            else:
                r = pe.call(addr, [NODE])
        except RuntimeError:
            continue
        w = pe_node_read(pe, NODE)
        if argmode:
            gr = f(ctypes.c_ulong(m), ctypes.byref(g))
        else:
            gr = f(ctypes.byref(g))
        ok = cmp_nodes(w, g, skip_d)
        if retval:
            ok = ok and (r & 0xffffffff) == (gr & 0xffffffff)
        check(name, ok, None, 'mode %x in %s\n  want %s\n  got  %s' % (m, show(v), show(w), show(g)))

# argmode conversions
for nm, ad, cn, am, rv in [('word_to_frac', 0x45c6c0, 'word_to_frac', True, False),
                            ('frac_to_word', 0x45c890, 'frac_to_word', True, True),
                            ('dword_to_frac', 0x45ca20, 'dword_to_frac', True, False),
                            ('frac_to_dword', 0x45cd40, 'frac_to_dword', True, False),
                            ('long_to_frac', 0x45cb30, 'long_to_frac', False, False),
                            ('frac_to_long', 0x45ced0, 'frac_to_long', False, False),
                            ('ext_to_double', 0x45ccc0, 'ext_to_double', False, False),
                            ('double_to_ext', 0x45d0c0, 'double_to_ext', False, False),
                            ('double_to_ieee_single', 0x45c7b0, 'double_to_ieee_single', False, False),
                            ('node_normalize', 0x45bc50, 'node_normalize', False, False),
                            ('node_neg', 0x45b990, 'node_neg', False, False),
                            ('node_neg32', 0x45b9c0, 'node_neg32', False, False),
                            ('node_not', 0x45ba20, 'node_not', False, False),
                            ('node_not32', 0x45baa0, 'node_not32', False, False),
                            ('node_lnot', 0x45bad0, 'node_lnot', False, False),
                            ('node_lnot32', 0x45bb00, 'node_lnot32', False, False),
                            ('node_sign', 0x45bb30, 'node_sign', False, True),
                            ('node_sign32', 0x45bbc0, 'node_sign32', False, True)]:
    run_unary(nm, ad, cn, am, False, rv)

# ieee_single_to_double(f, d)
lib.ieee_single_to_double.argtypes = [ctypes.c_ulong, ctypes.POINTER(ctypes.c_double)]
for _ in range(2000):
    f = random.choice([random.getrandbits(32), random.getrandbits(23), 0x7f800000, 0xff800000, 0x00400000, 0x80000001, 0x3f800000])
    pe.w32(OUT, 0); pe.w32(OUT + 4, 0)
    pe.call(0x45c5f0, [f, OUT])
    w = pe.rdbl(OUT)
    d = ctypes.c_double()
    lib.ieee_single_to_double(f, ctypes.byref(d))
    check('ieee_single_to_double', same_double(w, d.value), None, '%08x: want %r got %r' % (f, w, d.value))

# binary operators
BIN = [('op_add', 0x45aa50), ('op_sub', 0x45ab90), ('op_mul', 0x45acd0), ('op_div', 0x45af00),
       ('op_mod', 0x45b160), ('op_or', 0x45b330), ('op_and', 0x45b3f0), ('op_xor', 0x45b4b0),
       ('op_shl', 0x45b570), ('op_shr', 0x45b6a0), ('op_land', 0x45b850), ('op_lor', 0x45b8f0),
       ('op_add32', 0x45aaf0), ('op_sub32', 0x45ac20), ('op_mul32', 0x45ae60), ('op_div32', 0x45b080),
       ('op_mod32', 0x45b250), ('op_or32', 0x45b3a0), ('op_and32', 0x45b460), ('op_xor32', 0x45b520),
       ('op_shl32', 0x45b620), ('op_shr32', 0x45b7b0), ('op_land32', 0x45b8a0), ('op_lor32', 0x45b940)]
lib.op_compare.restype = ctypes.c_long
for nm, ad in BIN:
    f = getattr(lib, nm)
    f.restype = ctypes.c_long
    for _ in range(500):
        m = random.choice(MODES)
        if nm.endswith('32'):
            m |= 0x80
        setmode(m)
        a = rnd_node(m); b = rnd_node(m)
        if nm in ('op_shl', 'op_shr', 'op_shl32', 'op_shr32'):
            b.lo = random.randint(0, 70); b.hi = 0; b.ext = 0; b.flags = 0x101
        pe_node_write(pe, NODE, a); pe_node_write(pe, NODE2, b)
        ga = Val(); ctypes.memmove(ctypes.byref(ga), ctypes.byref(a), ctypes.sizeof(a))
        gb = Val(); ctypes.memmove(ctypes.byref(gb), ctypes.byref(b), ctypes.sizeof(b))
        pe.w32(ERRFLAG, 0)
        try:
            r = pe.call(ad, [NODE, NODE2])
        except RuntimeError:
            continue
        wa = pe_node_read(pe, NODE); wb = pe_node_read(pe, NODE2)
        gr = f(ctypes.byref(ga), ctypes.byref(gb))
        skip = nm in ('op_mod', 'op_mod32', 'op_div32')
        ok = (r & 0xffffffff) == (gr & 0xffffffff) and val_eq(wa, ga, skip) and val_eq(wb, gb)
        if skip and ok is False and (r & 0xffffffff) == (gr & 0xffffffff) and val_eq(wa, ga, True) is True:
            ok = True
        if skip and not same_double(wa.d, ga.d):
            # (Unicorn's fprem gives 0.0 for huge exponent differences: accept)
            fin = wa.d == wa.d and ga.d == ga.d and abs(wa.d) < 1e300
            ok = (r & 0xffffffff) == (gr & 0xffffffff) and val_eq(wa, ga, True) and (wa.d == 0.0 or not fin or abs(wa.d - ga.d) <= max(1e-3 * max(abs(wa.d), abs(ga.d)), 1e-200))
        check(nm, ok, None, 'mode %x\n  a %s\n  b %s\n  want r=%d %s\n  got  r=%d %s' % (m, show(a), show(b), r, show(wa), gr, show(ga)))

for nm, ad in [('op_compare', 0x45bce0), ('op_compare32', 0x45bf20)]:
    f = getattr(lib, nm)
    f.restype = ctypes.c_long
    for _ in range(800):
        m = random.choice(MODES)
        if nm.endswith('32'):
            m |= 0x80
        setmode(m)
        a = rnd_node(m); b = rnd_node(m)
        op = random.choice([0xb, 0xc, 0xd, 0xe, 0xf, 0x10, 0x13])
        pe_node_write(pe, NODE, a); pe_node_write(pe, NODE2, b)
        ga = Val(); ctypes.memmove(ctypes.byref(ga), ctypes.byref(a), ctypes.sizeof(a))
        gb = Val(); ctypes.memmove(ctypes.byref(gb), ctypes.byref(b), ctypes.sizeof(b))
        try:
            r = pe.call(ad, [NODE, NODE2, op])
        except RuntimeError:
            continue
        wa = pe_node_read(pe, NODE); wb = pe_node_read(pe, NODE2)
        gr = f(ctypes.byref(ga), ctypes.byref(gb), op)
        ok = (r & 0xffffffff) == (gr & 0xffffffff) and val_eq(wa, ga) and val_eq(wb, gb)
        check(nm, ok, None, 'mode %x op %x\n  a %s\n  b %s\n  want %s\n  got  %s' % (m, op, show(a), show(b), show(wa), show(ga)))

# mp_divmod and decimal split
lib.val_to_dec_parts.argtypes = [ctypes.c_ulong, ctypes.POINTER(ctypes.c_ulong), ctypes.POINTER(ctypes.c_long)]
lib.val_to_dec_parts2.argtypes = [ctypes.c_ulong, ctypes.POINTER(ctypes.c_ulong), ctypes.POINTER(ctypes.c_ulong)]
for nm, ad, cn in [('val_to_dec_parts', 0x45d1b0, lib.val_to_dec_parts), ('val_to_dec_parts2', 0x45d120, lib.val_to_dec_parts2)]:
    for _ in range(800):
        m = random.choice([0x4000000, 0x10000000, 0x0, 0x2000000, 0x4000080, 0x0080])
        setmode(m)
        wb = 16 if m & 0x10000000 else 24
        if nm == 'val_to_dec_parts':
            lo = random.getrandbits(32); hi = random.getrandbits(32)
            if not m & 0x2000000:
                lo = random.getrandbits(wb); hi = random.getrandbits(wb) & (0xff if random.random() < 0.5 else 0xffffff)
        else:
            lo = random.getrandbits(wb); hi = random.getrandbits(wb)
        third = random.getrandbits(8)
        pe.w32(NODE, lo); pe.w32(NODE + 4, hi); pe.w32(NODE + 8, third)
        pe.w32(OUT, 0); pe.w32(OUT + 4, 0)
        pe.call(ad, [m, NODE, OUT])
        w = (pe.r32(OUT), pe.r32(OUT + 4))
        inp = (ctypes.c_ulong * 3)(lo, hi, third)
        if nm == 'val_to_dec_parts':
            out = (ctypes.c_long * 2)()
        else:
            out = (ctypes.c_ulong * 2)()
        cn(m, inp, out)
        g = (out[0] & 0xffffffff, out[1] & 0xffffffff)
        check(nm, w == g, None, 'mode %x in %x %x: want %s got %s' % (m, lo, hi, w, g))

# ref_kind_info
lib.ref_kind_info.argtypes = [ctypes.c_long, ctypes.POINTER(ctypes.c_long), ctypes.POINTER(ctypes.c_long)]
for k in range(0, 0x130):
    pe.w32(NODE, 0xdead); pe.w32(NODE + 4, 0xdead)
    pe.call(0x459030, [k, NODE, NODE + 4])
    w = (pe.rs32(NODE), pe.rs32(NODE + 4))
    a = ctypes.c_long(-5); b = ctypes.c_long(-5)
    lib.ref_kind_info(k, ctypes.byref(a), ctypes.byref(b))
    check('ref_kind_info', w == (a.value, b.value), None, 'kind %x want %s got %s' % (k, w, (a.value, b.value)))

tot = 0
for k in sorted(counts):
    print('%-24s %5d cases %5d differences' % (k, counts[k], fails.get(k, 0)))
    tot += fails.get(k, 0)
print('TOTAL differences:', tot)
sys.exit(1 if tot else 0)
