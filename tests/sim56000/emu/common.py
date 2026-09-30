"""Shared helpers of the emulator based tests: build the shared library, marshal nodes."""
import ctypes, os, subprocess, sys, random, struct
ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..'))
sys.path.insert(0, os.path.join(ROOT, 're', 'scripts'))
from emu import PE

EXE = os.path.join(ROOT, 're', 'bin', 'SIM56000.EXE')
BUILD = os.path.join(ROOT, 'build', 'emu')
SRC = os.path.join(ROOT, 'src', 'sim56000')


def build(name, sources, data=()):
    """Compile the given translation units (plus generated data files) with the test stubs into a shared
    library; symbols that are still undefined (functions of untranslated modules) get empty stand-ins."""
    os.makedirs(BUILD, exist_ok=True)
    out = os.path.join(BUILD, name + '.so')
    objs = []
    files = [os.path.join(os.path.dirname(__file__), 'stubs.c')] + [os.path.join(SRC, x) for x in list(sources) + list(data)]
    for f in files:
        o = os.path.join(BUILD, name + '_' + os.path.basename(f) + '.o')
        subprocess.check_call(['gcc', '-c', '-fPIC', '-O1', '-std=gnu89', '-w', '-I' + SRC, f, '-o', o])
        objs.append(o)
    defined, undefined = set(), set()
    for o in objs:
        for line in subprocess.check_output(['nm', '-g', o]).decode().splitlines():
            p = line.split()
            if len(p) == 3 and p[1] in 'TDBRVW':
                defined.add(p[2])
            elif len(p) == 2 and p[0] == 'U':
                undefined.add(p[1])
            elif len(p) == 3 and p[1] == 'U':
                undefined.add(p[2])
    missing = sorted(u for u in undefined - defined if not u.startswith('_') and u not in
                     ('memcpy', 'memset', 'memcmp', 'malloc', 'calloc', 'free', 'realloc', 'strlen', 'strcpy', 'strcmp',
                      'strncpy', 'strchr', 'sprintf', 'fprintf', 'fscanf', 'fopen', 'fclose', 'fseek', 'ftell', 'fread',
                      'fwrite', 'exit', 'strtod', 'fmod', 'ldexp', 'frexp', 'floor', 'sqrt', 'isalpha', 'isalnum',
                      'isupper', 'tolower', 'toupper', 'printf', 'puts', 'strtol', 'getenv', 'time', 'longjmp', 'setjmp',
                      'strcat', 'strrchr', 'strstr', 'fgets', 'fputs', 'fputc', 'fgetc', 'atoi', 'atol', 'abs', 'pow',
                      'sin', 'cos', 'atan', 'log', 'exp', 'strncmp', 'isdigit', 'isspace', 'islower', 'isxdigit', 'qsort'))
    if missing:
        st = os.path.join(BUILD, name + '_autostubs.c')
        open(st, 'w').write('/* generated stand-ins */\n' + ''.join('void %s(void) { }\n' % m for m in missing))
        o = st[:-2] + '.o'
        subprocess.check_call(['gcc', '-c', '-fPIC', '-w', st, '-o', o])
        objs.append(o)
    subprocess.check_call(['gcc', '-shared', '-o', out] + objs + ['-lm'])
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
