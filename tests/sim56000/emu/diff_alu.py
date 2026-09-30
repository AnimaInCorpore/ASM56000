#!/usr/bin/env python3
"""alu.c (56-bit ALU primitives, handlers, decode, peripheral lookup): translation vs original."""
from common import *
import random, re
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EIP, UC_X86_REG_ESP

lib = build('alu', ['alu.c', 'insattr.c'], ['simd_dec.c', 'simd_e.c', 'simd_a.c', 'simd_b.c', 'simd_c.c', 'simd_f.c', 'simbss.c', 'simd_dev.c'])
pe = PE(EXE)
random.seed(61)
fails = {}
def chk(name, ok, msg):
    fails.setdefault(name, [0, 0]); fails[name][0] += 1
    if not ok:
        fails[name][1] += 1
        if fails[name][1] <= 6: print('DIFF', name, msg)

# the core register helpers are not translated yet: log their calls in both worlds
orig_log = []
def hook(uc, addr, size, ud):
    esp = uc.reg_read(UC_X86_REG_ESP)
    ret = pe.r32(esp)
    a, b = pe.r32(esp + 4), pe.r32(esp + 8)
    kind = {0x404690: 1, 0x404900: 2, 0x404920: 3, 0x404940: 4}[addr]
    orig_log.append((kind, a if kind != 1 else a, b if kind != 1 else 0))
    uc.reg_write(UC_X86_REG_EIP, ret)
    uc.reg_write(UC_X86_REG_ESP, esp + 4)
for a in (0x404690, 0x404900, 0x404920, 0x404940):
    pe.uc.hook_add(UC_HOOK_CODE, hook, begin=a, end=a)

NW = 0x200
CORE = pe.alloc(NW * 4 + 16)
mycore = (ctypes.c_ulong * NW)()
ctypes.c_void_p.in_dll(lib, 'alu_core').value = ctypes.addressof(mycore)
myccr = ctypes.c_ulong.in_dll(lib, 'alu_ccr')
myflag = ctypes.c_long.in_dll(lib, 'alu_flag')
calllog = ((ctypes.c_long * 3) * 4096).in_dll(lib, 'call_log')
calln = ctypes.c_long.in_dll(lib, 'call_n')
DT = pe.alloc(0x100); pe.w32(0x505790, DT)
lib.set_family.argtypes = [ctypes.c_long]

def rnd24():
    r = random.random()
    if r < 0.1: return 0
    if r < 0.2: return 0xffffff
    if r < 0.3: return 0x800000
    if r < 0.4: return 0x7fffff
    return random.getrandbits(24)
def rnd8():
    return random.choice([0, 0xff, 0x80, 0x7f, random.getrandbits(8), random.getrandbits(8)])

def setup(ext_mode=None):
    """random core image (word list of NW) + ccr + family"""
    w = [random.getrandbits(32) if random.random() < 0.5 else 0 for _ in range(NW)]
    wild = random.random() < 0.15
    for o in (0x45c, 0x468, 0x474, 0x480, 0x48c):
        w[o // 4] = random.getrandbits(32) if wild else rnd24()
        w[o // 4 + 1] = random.getrandbits(32) if wild else rnd24()
    for o in (0x464, 0x470, 0x47c, 0x488, 0x494):
        w[o // 4] = random.getrandbits(32) if wild else rnd8()
    w[0x9c // 4] = random.getrandbits(16) if random.random() < 0.8 else random.getrandbits(32)
    w[0xb8 // 4] = rnd24()
    w[0x184 // 4] = random.getrandbits(24)
    w[0x1bc // 4] = ext_mode if ext_mode is not None else random.choice([0, 0, 0, 1])
    w[0x1c0 // 4] = random.choice([0x2b, 0x2c, 0x2e, 0x2f, 2, 6, 300, 0x12d, 0x130, 0x131, 7, 0x100, 1])
    w[0x1c4 // 4] = random.choice([0x2b, 0x2c, 0x2e, 0x2f, 2, 6, 300, 0x12d, 0x100])
    w[0x1c8 // 4] = random.choice([300, 0x12d, 2, 6])
    w[0x1cc // 4] = random.choice([0, 1])
    w[0x1b8 // 4] = random.choice([i for i in range(1, 40) if i != 22])
    return w

def run(fn_addr, fn_mine, args, w, fam, ccr, flag, name):
    for i, v in enumerate(w):
        pe.w32(CORE + 4 * i, v)
        mycore[i] = v
    pe.w32(0x4dc144, CORE); pe.w32(0x4dc13c, ccr); pe.w32(0x4dc140, flag)
    pe.w32(DT + 8, fam); lib.set_family(fam)
    myccr.value = ccr; myflag.value = flag
    calln.value = 0
    del orig_log[:]
    pe.call(fn_addr, [CORE if a == 'core' else a for a in args])
    mine_args = [ctypes.addressof(mycore) if a == 'core' else a for a in args]
    fn_mine(*mine_args)
    wa = [pe.r32(CORE + 4 * i) for i in range(NW)]
    ga = [mycore[i] & 0xffffffff for i in range(NW)]
    ok = wa == ga
    msg = ''
    if not ok:
        d = [i * 4 for i in range(NW) if wa[i] != ga[i]]
        msg = 'words differ at %s: %s vs %s' % ([hex(x) for x in d[:4]], [hex(wa[x // 4]) for x in d[:4]], [hex(ga[x // 4]) for x in d[:4]])
    if ok and pe.r32(0x4dc13c) != (myccr.value & 0xffffffff):
        ok = False; msg = 'ccr %x vs %x' % (pe.r32(0x4dc13c), myccr.value)
    if ok and pe.r32(0x4dc140) != (myflag.value & 0xffffffff):
        ok = False; msg = 'flag %x vs %x' % (pe.r32(0x4dc140), myflag.value)
    if ok:
        mylog = [tuple(calllog[i]) for i in range(calln.value)]
        if [tuple(x) for x in orig_log] != mylog:
            ok = False; msg = 'calls %s vs %s' % (orig_log, mylog)
    chk(name, ok, '%s (ccr %x fam %x core 1bc %d)' % (msg, ccr, fam, w[0x1bc // 4]))

src = open(os.path.join(SRC, 'alu.c')).read()
funcs = re.findall(r'/\* (\w+) @ ([0-9a-f]+)', src)
funcs = [(n, int(a, 16)) for n, a in funcs if n not in ('alu_shift1',)]
funcs += [('alu_op_h432120', 0x432120), ('alu_op_h432140', 0x432140), ('alu_h_432160', 0x432160)]
N = int(os.environ.get('N', '200'))
for name, addr in funcs:
    fn = getattr(lib, name)
    args = ()
    for _ in range(N):
        fam = random.choice([1, 2, 4, 8, 0x400, 0x1000])
        ccr = random.choice([random.getrandbits(16), random.getrandbits(16) | 0x4000, random.getrandbits(32)])
        run(addr, fn, [], setup(), fam, ccr, random.choice([0, 1]), name)
# functions with arguments
for _ in range(N * 2):
    run(0x4337c0, lib.alu_load_src, [random.choice([0, 1])], setup(), 4, random.getrandbits(16), 1, 'alu_load_src')
lib.alu_load_src.argtypes = [ctypes.c_long]
for _ in range(N * 2):
    run(0x433c50, lib.sign_ext_word, [random.randint(0x100, 0x130), random.randint(0x100, 0x130)], setup(), 4, 0, 1, 'sign_ext_word')
for _ in range(N * 4):
    w = setup(); w[0x1bc // 4] = 0
    run(0x433360, lib.alu_shift1, ['core'], w, 4, random.getrandbits(16), 1, 'alu_shift1')
lib.alu_shift1.argtypes = [ctypes.c_void_p]
for _ in range(N * 8):
    w = setup()
    run(0x433c80, lib.alu_execute, ['core'], w, random.choice([1, 4, 0x400]), random.getrandbits(16), 0, 'alu_execute')

# alu_decode
lib.alu_decode.argtypes = [ctypes.c_ulong, ctypes.POINTER(ctypes.c_long)]
OUT = pe.alloc(32)
for _ in range(60000):
    opw = random.getrandbits(24)
    if random.random() < 0.3: opw &= 0xff
    fam = random.choice([1, 2, 4, 8, 0x400])
    pe.w32(DT + 8, fam); lib.set_family(fam)
    pe.call(0x433ce0, [opw, OUT])
    o = (ctypes.c_long * 6)()
    lib.alu_decode(opw, o)
    w = [pe.r32(OUT + 4 * i) for i in range(6)]
    g = [x & 0xffffffff for x in o]
    chk('alu_decode', w == g, '%x fam %x: %s vs %s' % (opw, fam, [hex(x) for x in w], [hex(x) for x in g]))

# ---- peripheral helpers ----
import struct as _st
CT = pe.r32(0x4aaac8 + 0) if False else None
ct_tab = 0x4aaac8   # chiptype_tab slots (13, first 10 filled)
def ct(t): return pe.r32(pe.r32(0x4aab08) + 4 * t) if pe.r32(0x4aab08) else pe.r32(ct_tab + 4 * t)
def cstr(a): return pe.rbytes(a, 64).split(b'\0')[0]
# collect register names of all types from the emulated image
names = set()
for t in range(10):
    d = ct(t)
    n_p, pp = pe.r32(d + 0x14), pe.r32(d + 0x18)
    for i in range(n_p):
        de = pe.r32(pp + 0x48 * i + 0x2c)
        nreg, regs = pe.r32(de + 0x28), pe.r32(de + 0x2c)
        for j in range(nreg):
            names.add(cstr(pe.r32(regs + 0x1c * j)))
names = sorted(x for x in names if x)
print('%d register names' % len(names))
PER = ctypes.c_long * 1
lib.periph_find_reg.restype = ctypes.c_long
lib.periph_find_reg.argtypes = [ctypes.c_long, ctypes.c_char_p, ctypes.POINTER(ctypes.c_long), ctypes.POINTER(ctypes.c_long)]
OP, OR_, NM = pe.alloc(16), pe.alloc(16), pe.alloc(64)
devbuf = [ctypes.create_string_buffer(0x400) for _ in range(1)]
dtab = (ctypes.c_void_p * 32).in_dll(lib, 'dev_tab') if False else None
# dev_tab of the library: array of struct dev_inst pointers behind the generated pointer
dtp = ctypes.c_void_p.in_dll(lib, 'dev_tab')
mydevs = (ctypes.c_void_p * 32).from_address(dtp.value)
mydev0 = ctypes.create_string_buffer(0x400)
mydevs[0] = ctypes.addressof(mydev0)
origdev = pe.alloc(0x400)
dtp_o = pe.r32(0x4aab10)
pe.w32(dtp_o, origdev)
def cand_names(t):
    c = []
    for n in random.sample(names, min(60, len(names))):
        c.append(n)
        c.append(n.lower())
        c.append(n[:-1])
        c.append(n[:-1] + b'0'); c.append(n[:-1] + b'1'); c.append(n[:-1] + b'a'); c.append(n[:-1] + b'A')
        c.append(n + b'x')
    c += [b'nosuchreg', b'a', b'']
    return [x for x in c if len(x) > 0]
import struct as st
for t in range(10):
    pe.w32(origdev, t); st.pack_into('<i', mydev0, 0, t)
    # dev_inst.type is the first member (long): write it in host order
    ctypes.c_long.from_address(ctypes.addressof(mydev0)).value = t
    for name in cand_names(t):
        pe.wbytes(NM, name + b'\0'); pe.w32(OP, 0xdead); pe.w32(OR_, 0xbeef)
        w = pe.call(0x433f60, [0, NM, OP, OR_]) & 0xffffffff
        p, r = ctypes.c_long(0xdead), ctypes.c_long(0xbeef)
        g = lib.periph_find_reg(0, name, ctypes.byref(p), ctypes.byref(r)) & 0xffffffff
        chk('periph_find_reg', w == g and (w == 0 or (pe.r32(OP) == p.value and pe.r32(OR_) == r.value)),
            't%d %r: %d (%x,%x) vs %d (%x,%x)' % (t, name, w, pe.r32(OP), pe.r32(OR_), g, p.value & 0xffffffff, r.value & 0xffffffff))

# periph_reset
lib.tst_periph_setup.restype = ctypes.c_long
lib.tst_periph_setup.argtypes = [ctypes.c_long, ctypes.POINTER(ctypes.c_ulong), ctypes.c_long, ctypes.POINTER(ctypes.c_ulong)]
for t in range(10):
    for _ in range(5):
        d = ct(t)
        n_map, n_p, pp = pe.r32(d + 0x1c), pe.r32(d + 0x14), pe.r32(d + 0x18)
        nregs = [pe.r32(pe.r32(pp + 0x48 * i + 0x2c) + 0x28) for i in range(n_p)]
        cnt = 2 + 2 * n_map + sum(nregs)
        rnd = [random.getrandbits(32) for _ in range(cnt + 8)]
        # original layout
        dev, sim, rst, rf = pe.alloc(0x200), pe.alloc(0x100), pe.alloc(0x12c * max(n_map, 1)), pe.alloc(8 * max(n_p, 1))
        pe.w32(0x505790, d); pe.w32(0x505798, dev); pe.w32(0x50578c, sim)
        pos = 0
        pe.w32(dev + 0x44, rnd[pos]); pos += 1
        pe.w32(sim + 0x24, rnd[pos]); pos += 1
        pe.w32(sim + 4, rst); pe.w32(sim + 8, rf)
        for i in range(n_map):
            pe.w32(rst + 0x12c * i + 0x14, rnd[pos]); pos += 1
            pe.w32(rst + 0x12c * i + 0xa0, rnd[pos]); pos += 1
        fls = []
        for i in range(n_p):
            f = pe.alloc(4 * nregs[i] + 16); fls.append(f)
            pe.w32(rf + 8 * i + 4, f)
            for j in range(nregs[i]):
                pe.w32(f + 4 * j, rnd[pos]); pos += 1
        pe.call(0x433e80, [])
        w = [pe.r32(dev + 0x44), pe.r32(sim + 0x24)]
        for i in range(n_map):
            w += [pe.r32(rst + 0x12c * i + 0x14), pe.r32(rst + 0x12c * i + 0xa0)]
        for i in range(n_p):
            w += [pe.r32(fls[i] + 4 * j) for j in range(nregs[i])]
        arr = (ctypes.c_ulong * (len(rnd) + 8))(*rnd)
        lib.tst_periph_setup(t, arr, 0, None)
        lib.periph_reset()
        out = (ctypes.c_ulong * (len(rnd) + 8))()
        n = lib.tst_periph_setup(t, arr, 1, out)
        g = list(out[:n])
        chk('periph_reset', w == g, 'type %d: %s vs %s' % (t, w[:8], g[:8]))

bad = 0
for k, (n, f) in sorted(fails.items()):
    print('%-20s %6d cases, %d differences' % (k, n, f)); bad += f
sys.exit(1 if bad else 0)
