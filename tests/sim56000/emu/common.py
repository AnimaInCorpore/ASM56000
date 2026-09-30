"""Shared helpers of the emulator based tests: build the shared library, marshal nodes."""
import ctypes, os, subprocess, sys, random, struct
ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..'))
sys.path.insert(0, os.path.join(ROOT, 're', 'scripts'))
from emu import PE

EXE = os.path.join(ROOT, 're', 'bin', 'SIM56000.EXE')
BUILD = os.path.join(ROOT, 'build', 'emu')
SRC = os.path.join(ROOT, 'src', 'sim56000')


def build(name, sources):
    os.makedirs(BUILD, exist_ok=True)
    out = os.path.join(BUILD, name + '.so')
    cmd = ['gcc', '-shared', '-fPIC', '-O1', '-std=gnu89', '-w', '-I' + SRC,
           os.path.join(os.path.dirname(__file__), 'stubs.c')] + [os.path.join(SRC, s) for s in sources] + ['-lm', '-o', out]
    subprocess.check_call(cmd)
    return ctypes.CDLL(out)


class Val(ctypes.Structure):
    """host layout of struct val (unsigned long members)"""
    _fields_ = [('d', ctypes.c_double), ('lo', ctypes.c_ulong), ('hi', ctypes.c_ulong), ('ext', ctypes.c_ulong),
                ('addr', ctypes.c_ulong), ('id', ctypes.c_ulong), ('flags', ctypes.c_ulong),
                ('f20', ctypes.c_ulong), ('idx', ctypes.c_long)]


def pe_node_write(pe, a, v):
    pe.wdbl(a, v.d)
    pe.w32(a + 8, v.lo); pe.w32(a + 0xc, v.hi); pe.w32(a + 0x10, v.ext)
    pe.w32(a + 0x14, v.addr); pe.w32(a + 0x18, v.id); pe.w32(a + 0x1c, v.flags)
    pe.w32(a + 0x20, v.f20); pe.w32(a + 0x24, v.idx & 0xffffffff)


def pe_node_read(pe, a):
    v = Val()
    v.d = pe.rdbl(a)
    v.lo = pe.r32(a + 8); v.hi = pe.r32(a + 0xc); v.ext = pe.r32(a + 0x10)
    v.addr = pe.r32(a + 0x14); v.id = pe.r32(a + 0x18); v.flags = pe.r32(a + 0x1c)
    v.f20 = pe.r32(a + 0x20); v.idx = pe.r32(a + 0x24)
    return v


def same_double(a, b):
    return (a != a and b != b) or a == b


def val_eq(a, b, skip_d=False):
    if not skip_d and not same_double(a.d, b.d):
        return False
    return all(getattr(a, f) == getattr(b, f) for f in ('lo', 'hi', 'ext', 'addr', 'id', 'flags', 'f20', 'idx'))


def show(v):
    return 'd=%r lo=%x hi=%x ext=%x fl=%x' % (v.d, v.lo, v.hi, v.ext, v.flags)
