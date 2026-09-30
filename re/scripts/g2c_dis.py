#!/usr/bin/env python3
"""g2c_dis.py - mechanical Ghidra -> C89 conversion of the SIM56000 disfmt module (re/out/SIM56000/mod/disfmt.c):
the disassembler formatters `long dis_fmt_cN(unsigned long opw, long *tok)` that write token ids.
Writes /tmp/disfmt_auto.c; functions the converter cannot handle are reported."""
import re, sys, os

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
src = open(os.path.join(ROOT, 're/out/SIM56000/mod/disfmt.c')).read()
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

GLOBALS = {'_dis_effect_flags': 'dis_effect_flags', 'DAT_004dbebc': 'dis_val_c', 'DAT_004dbec0': 'dis_val_a',
           'DAT_004dbec4': 'dis_val_d', 'DAT_004dbec8': 'dis_val_e'}

def conv(name, body):
    b = re.sub(r'/\*.*?\*/', '', body, flags=re.S)
    b = re.sub(r'\(int\)\(opw \+ \(\(int\)opw >> 0x1f & 0xffU\)\) >> 8', '(opw >> 8)', b)
    def tbl(m):
        return table(int(m.group(1), 16), '(' + m.group(2) + ')')
    b = re.sub(r'\*\(\w+ \*\)\(&DAT_(0*[0-9a-f]{6,8}) \+ (.*?) \* 4\)', tbl, b)
    b = re.sub(r'\(int\)\(((?:[^()]|\([^()]*\))*)\) \+ \((0x[0-9a-f]+|\d+) - \(int\)tok\) >> 2',
               lambda m: '(long)((%s) - tok) + %d' % (m.group(1), int(m.group(2), 0) // 4), b)
    b = re.sub(r'\(int\)(\w+) - \(int\)tok >> 2', lambda m: '(long)(%s - tok)' % m.group(1), b)
    b = re.sub(r'\(int\)(\w+) \+ \((0x[0-9a-f]+|\d+) - \(int\)tok\) >> 2',
               lambda m: '(long)(%s - tok) + %d' % (m.group(1), int(m.group(2), 0) // 4), b)
    b = re.sub(r'\(uint\)CONCAT11\((0x[0-9a-f]+),\(char\)(\w+)\)', lambda m: '(((%s) << 8) | ((%s) & 0xff))' % (m.group(1), m.group(2)), b)
    for k, v in GLOBALS.items():
        b = b.replace(k, v)
    b = re.sub(r'\btrue\b', '1', b)
    b = re.sub(r'\bfalse\b', '0', b)
    b = re.sub(r'&(dis_hex_\w+)', r'\1', b)
    b = re.sub(r'\(uint\)\s*', '', b)
    b = re.sub(r'\(byte\)', '(unsigned char)', b)
    b = re.sub(r'\bbool\b', 'int', b)
    b = re.sub(r'\buint\b', 'unsigned long', b)
    b = re.sub(r'\bulong\b', 'unsigned long', b)
    b = re.sub(r'\bint \*', 'long *', b)
    b = re.sub(r'\bint\b', 'long', b)
    b = b.replace('long *long', 'long *')
    b = re.sub(r'unsigned long \*(\w+)', r'long *\1', b)
    b = re.sub(r'\((?:unsigned )?long \*\)\(', '(', b)
    # stores into the token array wrap to 32 bit
    def st(m):
        rhs = m.group(3)
        if re.fullmatch(r'-?(0x[0-9a-f]+|\d+)', rhs.strip()):
            v = int(rhs.strip(), 0)
            if v >= 0x80000000:
                return '%s%s = %d;' % (m.group(1), m.group(2), v - (1 << 32))
            return m.group(0)
        return '%s%s = S32(%s);' % (m.group(1), m.group(2), rhs)
    b = re.sub(r'(?m)^(\s*)(\*?\w+(?:\[\d+\])?) = (.*);$', lambda m: st(m) if (m.group(2).startswith('*') or '[' in m.group(2)) else m.group(0), b)
    return b

parts = re.split(r'(?m)^/\* ==== (\w+) @ ([0-9a-f]+) ==== \*/', src)
funcs = [(parts[i], parts[i + 1], parts[i + 2]) for i in range(1, len(parts), 3)]
out = []
bad = []
for name, addr, body in funcs:
    m = re.search(r'(?:void|int|long|undefined4)\s+(?:__cdecl\s+)?(\w+)\((.*?)\)\s*\{', body, re.S)
    if not m:
        bad.append(name); continue
    sig = m.group(2).replace('ulong', 'unsigned long').replace('undefined4 *param_2', 'long *tok').replace('param_1', 'opw')
    sig = re.sub(r'\buint\b', 'unsigned long', sig).replace('undefined4', 'long').replace('int *param_2', 'long *tok')
    sig = sig.replace('param_2', 'tok').replace('long *tok', 'long *tok')
    inner = body[m.end():]
    inner = inner[:inner.rindex('}')]
    inner = inner.replace('param_1', 'opw').replace('param_2', 'tok')
    inner = conv(name, inner)
    rt = 'long' if re.match(r'\s*(?:int|undefined4)', body[m.start():]) else 'void'
    if 'in_stack_0000000c' in inner:
        inner = re.sub(r'\n\s*long in_stack_0000000c;', '', inner).replace('in_stack_0000000c', 'sel')
        sig += ', long sel'
    out.append('/* %s @ %s */\n%s %s(%s)\n{%s}\n' % (name, addr, rt, name, sig, inner))
protos = ['long %s(unsigned long opw, long *tok, long sel);' % m for m in re.findall(r'\nlong (\w+)\(unsigned long opw,long \*tok, long sel\)', '\n'.join(out))]
HDR = '''/* disfmt.c - disassembler formatters: one per opcode class, each builds the token list of the
 * instruction text and sets the effective-address state (dis_effect_flags, dis_sel_*, dis_val_*)
 * (SIM56000.EXE 6.3.0, module disfmt 0x41fb70-0x423ae0, plus dis_fmt_h41fb60 in front of it).
 * Mechanically converted from the Ghidra export by re/scripts/g2c_dis.py; verified against the
 * original by tests/sim56000/emu/diff_disfmt.py.  Token ids: see dis_token_strings; 0x3f "U" prefix,
 * 0x99 ",", 0x9a " ", negative ids are pseudo tokens (-2 hex of dis_hex_ea, -3 dis_hex_b, ...). */
#include "sim56000.h"

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wparentheses"
#endif

/* token words are 32-bit signed in the original */
static long S32(unsigned long v)
{
    v &= MASK32;
    if (v & 0x80000000UL)
        return -(long)((~v & MASK32) + 1UL);
    return (long)v;
}

long dis_fmt_h41fb60(unsigned long opw, long *tok)
{
    tok[0] = 0x3f;
    return 1;
}

'''
open(os.path.join(ROOT, 'src/sim56000/disfmt.c'), 'w').write(HDR + '\n'.join(protos) + '\n\n' + '\n'.join(out))
print('converted', len(out), 'bad', bad)
