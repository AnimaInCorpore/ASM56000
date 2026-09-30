#!/usr/bin/env python3
"""g2c_attr.py - mechanical Ghidra -> C89 conversion of the small handler functions of the SIM56000 insattr module
(re/out/SIM56000/mod/insattr.c): insn_move/exec/class/valid handlers.  Writes the result to stdout."""
import re, sys, os
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TAIL = len(sys.argv) > 1 and sys.argv[1] == '--tail'
if TAIL:
    src = open(os.path.join(ROOT, 're/out/SIM56000/mod/memacc.c')).read()
    src = src[src.index('/* ==== insn_exec_h42e5c0'):]
else:
    src = open(os.path.join(ROOT, 're/out/SIM56000/mod/insattr.c')).read()
parts = re.split(r'/\* ==== (\w+) @ ([0-9a-f]+) ==== \*/', src)
HAND = {'insn_exec_info', 'insn_move_info', 'insn_class_code', 'insn_ea_class', 'ea_mode_index',
        'opclass_lookup', 'opclass_lookup_any'}
TAB = {'004c41b0': 'd_4c41b0', '004c43b0': 'd_4c43b0', '004c3ff8': 'd_4c3ff8', '004c3670': 'd_4c3670', '004c36b0': 'd_4c36b0', '004c3e40': 'd_4c3e40'}

def conv(name, body):
    m = re.match(r'\s*(?:\w+\s+)*?(\w+)\s+(?:__cdecl\s+)?' + name + r'\((.*?)\)\s*\{(.*)\}\s*$', body, re.S)
    ret, params, code = m.group(1), m.group(2), m.group(3)
    code = re.sub(r'\s*\n\s*(undefined4|int|uint|bool|byte|char) \w+( = \d+)?;', lambda k: '', code) if False else code
    b = code
    b = re.sub(r'\*\((?:int|uint|undefined4) \*\)\(&DAT_(\w+) \+ (.*?) \* 4\)', lambda k: '%s[%s]' % (TAB[k.group(1)], k.group(2)), b)
    b = re.sub(r'in_stack_0000000c', 'a3', b)
    b = re.sub(r'in_stack_00000010', 'a4', b)
    b = re.sub(r'in_stack_00000008', 'a2', b)
    b = re.sub(r'in_stack_00000004', 'a1', b)
    for i in range(1, 5):
        b = b.replace('param_%d' % i, 'a%d' % i)
    b = re.sub(r'\(int\)a1 >> 8', '(a1 >> 8)', b)
    b = re.sub(r'\(int\)opw >> 8', '(opw >> 8)', b)
    b = re.sub(r'\n\s*(?:int|uint|undefined4|char|bool|byte) in_stack_\w+;', '', b)
    b = b.replace('(-cVar1 & 0x20U)', '((0 - (unsigned long)cVar1) & 0x20U)')
    b = b.replace('(char)opw', '(opw & 0xff)')
    b = re.sub(r'\(byte\)', '(unsigned char)', b)
    b = re.sub(r'\(uint\)', '(unsigned long)', b)
    b = re.sub(r'\btrue\b', '1', b)
    b = re.sub(r'\bfalse\b', '0', b)
    b = re.sub(r"'\\0'", '0', b)
    b = re.sub(r"'\\x01'", '1', b)
    b = re.sub(r'\buint\b', 'unsigned long', b)
    b = re.sub(r'\bbool\b', 'long', b)
    b = re.sub(r'\bbyte\b', 'unsigned long', b)
    b = re.sub(r'\bundefined4\b', 'long', b)
    b = re.sub(r'\bchar\b', 'long', b)
    b = re.sub(r'\bint\b', 'long', b)
    b = re.sub(r'return (.*?);', lambda k: 'return %s;' % k.group(1) if re.fullmatch(r'-?\w+|\(?\w+ [<!=]=? \w+\)?', k.group(1)) or 'unsigned long' in k.group(1) and False else 'return M32(%s);' % k.group(1), b)
    b = re.sub(r'\n\s*long a\d;', '', b)
    b = b.replace('  ea_mode_index(a1);\n  return;', '  return ea_mode_index(a1);')
    if name.startswith('insn_valid_pm'):
        sig = 'long %s(unsigned long opw)' % name
    elif name.startswith('insn_valid'):
        sig = 'long %s(unsigned long a1)' % name
    else:
        sig = 'long %s(unsigned long a1, unsigned long a2, long a3, long a4)' % name
    return sig + '\n{' + b.rstrip() + '\n}\n'

for i in range(1, len(parts), 3):
    name, addr, body = parts[i], parts[i + 1], parts[i + 2]
    if name in HAND:
        continue
    try:
        print('/* %s @ %s */' % (name, addr))
        print(conv(name, body))
    except Exception as e:
        sys.stderr.write('FAIL %s %s\n' % (name, e))
