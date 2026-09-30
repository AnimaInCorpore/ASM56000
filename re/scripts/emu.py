#!/usr/bin/env python3
"""emu.py - run functions of a Win32 PE (the original CLAS56 tools) in the Unicorn x86 emulator.

Only meant for self-contained functions (no Win32 imports): the sections are mapped at their
virtual addresses, arguments are pushed cdecl style and the call returns to a stop address.
    from emu import PE
    pe = PE('re/bin/SIM56000.EXE')
    r = pe.call(0x42c7f0, [0x30, 0x1234, 1])          # eax
    pe.w32(addr, v); pe.r32(addr); pe.wbytes(addr, b); pe.rbytes(addr, n)
    pe.alloc(n) -> address of scratch memory
Floating point results are read with pe.st0().
"""
import struct, sys
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, UcError
from unicorn.x86_const import *

STACK_TOP = 0x7ff00000
STACK_SIZE = 0x100000
HEAP = 0x60000000
STOP = 0x7fd00000


class PE:
    def __init__(self, path):
        d = open(path, 'rb').read()
        pe = struct.unpack_from('<I', d, 0x3c)[0]
        n = struct.unpack_from('<H', d, pe + 6)[0]
        opt = struct.unpack_from('<H', d, pe + 20)[0]
        self.base = struct.unpack_from('<I', d, pe + 24 + 28)[0]
        img_size = struct.unpack_from('<I', d, pe + 24 + 56)[0]
        self.uc = Uc(UC_ARCH_X86, UC_MODE_32)
        uc = self.uc
        top = (self.base + img_size + 0xfff) & ~0xfff
        uc.mem_map(self.base, top - self.base)
        hdr = struct.unpack_from('<I', d, pe + 24 + 60)[0]
        uc.mem_write(self.base, d[:hdr])
        o = pe + 24 + opt
        for i in range(n):
            vs, va, rs, ro = struct.unpack_from('<IIII', d, o + 8 + i * 40)
            uc.mem_write(self.base + va, d[ro:ro + min(rs, vs)])
        uc.mem_map(STACK_TOP - STACK_SIZE, STACK_SIZE)
        uc.mem_map(HEAP, 0x1000000)
        uc.mem_map(STOP, 0x1000)
        uc.mem_write(STOP, b'\x90' * 16)
        self.heap_ptr = HEAP
        uc.reg_write(UC_X86_REG_FPCW, 0x27f)      # Win32 default: 53-bit precision, round to nearest
        self.count = 0

    # memory helpers
    def w32(self, a, v): self.uc.mem_write(a, struct.pack('<I', v & 0xffffffff))
    def r32(self, a): return struct.unpack('<I', bytes(self.uc.mem_read(a, 4)))[0]
    def rs32(self, a): return struct.unpack('<i', bytes(self.uc.mem_read(a, 4)))[0]
    def wdbl(self, a, v): self.uc.mem_write(a, struct.pack('<d', v))
    def rdbl(self, a): return struct.unpack('<d', bytes(self.uc.mem_read(a, 8)))[0]
    def wbytes(self, a, b): self.uc.mem_write(a, bytes(b))
    def rbytes(self, a, n): return bytes(self.uc.mem_read(a, n))
    def alloc(self, n):
        a = self.heap_ptr
        self.heap_ptr += (n + 15) & ~15
        return a

    def call(self, va, args=(), maxinsn=2000000):
        uc = self.uc
        sp = STACK_TOP - 0x1000
        for a in reversed(args):
            sp -= 4
            uc.mem_write(sp, struct.pack('<I', a & 0xffffffff))
        sp -= 4
        uc.mem_write(sp, struct.pack('<I', STOP))
        uc.reg_write(UC_X86_REG_ESP, sp)
        uc.reg_write(UC_X86_REG_EBP, 0)
        try:
            uc.emu_start(va, STOP, count=maxinsn)
        except UcError as e:
            raise RuntimeError('emulation error at eip=%08x: %s' % (uc.reg_read(UC_X86_REG_EIP), e))
        if uc.reg_read(UC_X86_REG_EIP) != STOP:
            raise RuntimeError('did not return (eip=%08x)' % uc.reg_read(UC_X86_REG_EIP))
        return uc.reg_read(UC_X86_REG_EAX)

    def eax(self): return self.uc.reg_read(UC_X86_REG_EAX)
    def edx(self): return self.uc.reg_read(UC_X86_REG_EDX)

    def st0(self):
        # value of ST(0) after a call returning a double (fld from the FPU stack)
        uc = self.uc
        raw = uc.reg_read(UC_X86_REG_ST0)
        return raw
