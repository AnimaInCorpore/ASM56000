#!/usr/bin/env python3
"""g2c_alu.py - mechanical Ghidra -> C89 conversion of the SIM56000 alu module (re/out/SIM56000/mod/alu.c): the 56-bit
ALU primitives and instruction handlers that work on the core register file `alu_core` (32-bit word array; the original
addresses it by byte offset).  Writes the C text to stdout; functions listed in HAND are written by hand."""
import re, sys, os
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
src = open(os.path.join(ROOT, 're/out/SIM56000/mod/alu.c')).read()
parts = re.split(r'/\* ==== (\w+) @ ([0-9a-f]+) ==== \*/', src)
HAND = {'insn_validate', 'alu_shift1', 'alu_load_src', 'alu_execute', 'alu_decode', 'sign_ext_word', 'hid_4325c1',
        'periph_reset', 'periph_call', 'periph_find_reg'}

def match_paren(s, i):
    d = 0
    for j in range(i, len(s)):
        if s[j] == '(':
            d += 1
        elif s[j] == ')':
            d -= 1
            if d == 0:
                return j
    raise ValueError

def cast_int(b):
    """(int)X -> SI(X) for X an identifier or a parenthesised expression"""
    out = ''
    i = 0
    while True:
        m = re.search(r'\(int\)', b[i:])
        if not m:
            return out + b[i:]
        s = i + m.start()
        e = s + 5
        out += b[i:s]
        if b[e] == '(':
            j = match_paren(b, e)
            out += 'SI(' + cast_int(b[e + 1:j]) + ')'
            i = j + 1
        else:
            m2 = re.match(r'\w+', b[e:])
            out += 'SI(%s)' % m2.group(0)
            i = e + m2.end()

def conv(name, body, newname=None):
    m = re.match(r'\s*(?:void\s+)?(?:__cdecl\s+)?' + name + r'\((.*?)\)\s*\{(.*)\}\s*$', body, re.S)
    b = m.group(2)
    b = re.sub(r'/\*.*?\*/', '', b, flags=re.S)
    def store(mm):
        return 'W(%s) = ST(%s);' % (mm.group(1), mm.group(2))
    b = re.sub(r'\*\((?:int|uint|undefined4) \*\)\(alu_core \+ (0x[0-9a-f]+)\)\s*=(?!=)\s*([^;]*?);', store, b, flags=re.S)
    b = re.sub(r'\*\(int \*\)\(alu_core \+ (0x[0-9a-f]+)\)', r'SI(W(\1))', b)
    b = re.sub(r'\*\((?:uint|undefined4) \*\)\(alu_core \+ (0x[0-9a-f]+)\)', r'W(\1)', b)
    b = re.sub(r'\*\(byte \*\)\(alu_core \+ (0x[0-9a-f]+)\)', r'(W(\1) & 0xff)', b)
    b = re.sub(r'\*\(char \*\)\(alu_core \+ (0x[0-9a-f]+)\)', r'SC(W(\1))', b)
    b = re.sub(r'\(byte\)W\((0x[0-9a-f]+)\)', r'(W(\1) & 0xff)', b)
    b = re.sub(r'\(byte\)(\w+)', r'(\1 & 0xff)', b)
    b = re.sub(r'\*\(uint \*\)\(cur_dtype \+ 8\)', 'cur_dtype->family', b)
    b = b.replace("== '\\0'", '== 0')
    b = b.replace('((int)(char)alu_ccr & 1U)', '(alu_ccr & 1UL)')
    b = cast_int(b)
    b = re.sub(r'\(uint\)', '', b)
    b = re.sub(r'\btrue\b', '1', b)
    b = re.sub(r'\bfalse\b', '0', b)
    b = re.sub(r'\bbool\b', 'int', b)
    b = re.sub(r'\buint\b', 'unsigned long', b)
    b = re.sub(r'\bulong\b', 'unsigned long', b)
    b = re.sub(r'\bint\b', 'long', b)
    # stores into locals and alu_ccr keep 32-bit semantics
    def loc(mm):
        v, rhs = mm.group(1), mm.group(2)
        if v.startswith('uVar') or v == 'alu_ccr':
            return '%s = ST(%s);' % (v, rhs)
        return mm.group(0)
    b = re.sub(r'\b(uVar\d+|alu_ccr) = ([^;]*?);', loc, b, flags=re.S)
    b = re.sub(r'\n\s*\n\s*\n', '\n\n', b)
    return 'void %s(void)\n{%s}\n' % (newname or name, b.rstrip() + '\n')

out = []
for i in range(1, len(parts), 3):
    name, addr, body = parts[i], parts[i + 1], parts[i + 2]
    if name in HAND:
        continue
    try:
        if name in ('alu_op_h432120', 'alu_op_h432140'):
            # Ghidra fused the guard with the function it tail calls (0x4325f0 / 0x432a70)
            first = re.search(r'\n  if \(\*\(int \*\)\(alu_core \+ 0x1bc\) == 1\) \{\n    alu_load_src\(1\);\n    return;\n  \}', body)
            body2 = body[:first.start()] + body[first.end():]
            nn = 'alu_h_4325f0' if name.endswith('2120') else 'alu_h_432a70'
            na = '4325f0' if name.endswith('2120') else '432a70'
            out.append('/* %s @ %s */' % (nn, na))
            out.append(conv(name, body2, nn))
            continue
        out.append('/* %s @ %s */' % (name, addr))
        out.append(conv(name, body))
    except Exception as e:
        sys.stderr.write('FAIL %s %r\n' % (name, e))
print('\n'.join(out))
