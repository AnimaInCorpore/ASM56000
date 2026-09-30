#!/usr/bin/env python3
"""g2c_dec.py - mechanical Ghidra -> C89 conversion of the SIM56000 decode module (re/out/SIM56000/mod/decode.c).
The decoded instruction record DEC is a `long dec[]` array (word index = byte offset / 4); table
references become the generated d_XXXXXX arrays.  Functions that Ghidra rewrote with reused parameter
variables are listed as MANUAL and must be written by hand (decode_manual.inc)."""
import re, sys, os

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
src = open(os.path.join(ROOT, 're/out/SIM56000/mod/decode.c')).read()

# data objects: start, size, name
objs = []
for l in open(os.path.join(ROOT, 're/notes/SIM56000/datamap.txt')):
    p = l.split()
    if len(p) >= 3 and re.match(r'^[0-9a-f]{8}$', p[0]):
        objs.append((int(p[0], 16), int(p[1]), p[2]))
objs.sort()

def table(addr, idx):
    for s, sz, n in objs:
        if s <= addr < s + sz:
            off = (addr - s) // 4
            return '%s[%s%s]' % (n, idx, ('+%d' % off) if off else '') if sz > 4 else n
    raise KeyError(hex(addr))

parts = re.split(r'(?m)^/\* ==== (\w+) @ ([0-9a-f]+) ==== \*/', src)
funcs = [(parts[i], parts[i + 1], parts[i + 2]) for i in range(1, len(parts), 3)]

def conv_body(name, body):
    b = body
    b = re.sub(r'/\*.*?\*/', '', b, flags=re.S)
    b = b.replace('param_1', 'opw').replace('param_2', 'dec')
    b = b.replace('opw_00', 'opw').replace('dec_00', 'dec')
    # table lookups
    def tbl(m):
        addr = int(m.group(1), 16)
        return table(addr, '(' + m.group(2) + ')')
    b = re.sub(r'\*\(\w+ \*\)\(&DAT_(0*[0-9a-f]{6,8}) \+ (.*?) \* 4\)', tbl, b)
    b = re.sub(r'\*\(\w+ \*\)&DAT_(0*[0-9a-f]{6,8})', lambda m: table(int(m.group(1), 16), '0'), b)
    # record fields
    def fld(m):
        n = m.group(2)
        off = int(n, 0)
        return 'dec[%d]' % (off // 4)
    b = re.sub(r'\*\((\w+) \*\)\(\(int\)dec \+ (0x[0-9a-f]+|\d+)\)', fld, b)
    b = re.sub(r'\*\((\w+) \*\)dec\b', 'dec[0]', b)
    b = re.sub(r'\*dec\b', 'dec[0]', b)
    b = re.sub(r'\(\(long \*\)\(\(int\)dec \+ (0x[0-9a-f]+|\d+)\)\)', lambda m: '(dec + %d)' % (int(m.group(1), 0) // 4), b)
    b = re.sub(r'\(long \*\)\(\(int\)dec \+ (0x[0-9a-f]+|\d+)\)', lambda m: '(dec + %d)' % (int(m.group(1), 0) // 4), b)
    b = re.sub(r'\(\w+ \*\)\(\(int\)dec \+ (0x[0-9a-f]+|\d+)\)', lambda m: '(dec + %d)' % (int(m.group(1), 0) // 4), b)
    b = re.sub(r'\bdec\[(0x[0-9a-f]+)\]', lambda m: 'dec[%d]' % int(m.group(1), 16), b)
    b = re.sub(r'\bparam_2\[(0x[0-9a-f]+)\]', r'dec[\1]', b)
    b = re.sub(r'\bdec\[(0x[0-9a-f]+)\]', lambda m: 'dec[%d]' % int(m.group(1), 16), b)
    # types
    b = re.sub(r'\((?:uint|ulong|int|undefined4|long)\)\s*', '', b)
    b = b.replace('(byte)', '(unsigned char)').replace('ulong', 'unsigned long')
    b = re.sub(r'\buint\b', 'unsigned long', b)
    b = re.sub(r'\bundefined4\b', 'long', b)
    b = re.sub(r'\bint\b', 'long', b)
    b = b.replace('long *long', 'long *')
    return b

MANUAL = set()
def is_manual(name, body):
    if name in ('dec_init', 'decode_insn', 'swap_ptrs', 'dec_ea6'):
        return True
    if 'swap_ptrs' in body or 'CONCAT' in body:
        return True
    if re.search(r'\b(opw|dec|param_1|param_2) = \(?(void|undefined4|int|long)?[ *]*\)?\(?\(?int\)', body):
        return True
    return False

def header(name, sig):
    # normalise the parameter list
    sig = sig.replace('undefined4 *param_2', 'long *dec').replace('int *param_2', 'long *dec').replace('void *param_2', 'long *dec')
    sig = sig.replace('param_1', 'opw').replace('void *dec', 'long *dec')
    sig = re.sub(r'\bulong\b', 'unsigned long', sig)
    sig = re.sub(r'\buint\b', 'unsigned long', sig)
    sig = re.sub(r'\bundefined4\b', 'long', sig)
    if sig.strip() == 'unsigned long opw,long *dec' or sig.strip() == 'unsigned long opw, long *dec':
        sig = 'unsigned long opw, long *dec'
    return sig

def s32wrap(line):
    m = re.match(r'^(\s*)(dec\[\d+\]) = (.*);$', line)
    if m and not re.fullmatch(r'-?(0x[0-9a-f]+|\d+)', m.group(3).strip()) and 'dec[' not in m.group(3).split('?')[0][:0]:
        return '%s%s = S32(%s);' % (m.group(1), m.group(2), m.group(3))
    return line

out = []
for name, addr, body in funcs:
    if is_manual(name, body):
        MANUAL.add(name)
        continue
    m = re.search(r'(?:void|int|long)\s+(?:__cdecl\s+)?(\w+)\((.*?)\)\s*\{', body, re.S)
    if not m:
        print('no header', name); continue
    sig = header(name, m.group(2))
    inner = body[m.end():]
    inner = inner[:inner.rindex('}')]
    inner = conv_body(name, inner)
    inner = '\n'.join(s32wrap(l) for l in inner.split('\n'))
    # drop leftover temp declarations lines of Ghidra (keep: they are valid) and blank noise
    inner = re.sub(r'\n\s*return;\s*$', '\n', inner.rstrip() + '\n')
    out.append('/* %s @ %s */\nvoid %s(%s)\n{%s}\n' % (name, addr, name, sig, inner))
open('/tmp/decode_auto.c', 'w').write('\n'.join(out))
print('auto:', len(out), 'manual:', len(MANUAL))
print(sorted(MANUAL))
