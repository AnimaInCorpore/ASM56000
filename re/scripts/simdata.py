"""Shared analysis of the initialized data of SIM56000.EXE (used by gentab_sim.py).

Builds, once (cached in re/out/SIM56000/simdata.cache):
  refs[addr]   -> set of access sizes (0 = address taken / unknown) seen in machine code
                  for every absolute operand that points into initialized data
  the linear sweep runs over the function bodies of re/out/SIM56000/functions.txt.
"""
import os, sys, struct, re, pickle
import capstone
from capstone.x86 import X86_OP_MEM, X86_OP_IMM

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.join(ROOT, "re", "scripts"))
from x86dis import load, reader   # noqa: E402

EXE = os.path.join(ROOT, "re", "bin", "SIM56000.EXE")
d, base, secs = load(EXE)
rd = reader(d, secs)
RDATA = (0x492000, 0x494600)
DATA = (0x495000, 0x4db200)
BSS = (0x4db200, 0x506c30)
TEXT = (0x401000, 0x483400)


def in_data(a):
    return RDATA[0] <= a < RDATA[1] or DATA[0] <= a < DATA[1]


def in_bss(a):
    return BSS[0] <= a < BSS[1]


def in_text(a):
    return TEXT[0] <= a < TEXT[1]


def u32(a):
    return struct.unpack("<I", rd(a, 4))[0]


def s32(a):
    return struct.unpack("<i", rd(a, 4))[0]


def cstr_at(a, maxlen=8192):
    b = rd(a, maxlen)
    if b is None:
        return None
    i = b.find(b"\0")
    if i < 0:
        return None
    return b[:i]


def printable(bs):
    return len(bs) > 0 and all(32 <= c < 127 or c in (9, 10, 13) for c in bs)


def sweep():
    cache = os.path.join(ROOT, "re", "out", "SIM56000", "simdata2.cache")
    fl = os.path.join(ROOT, "re", "out", "SIM56000", "functions.txt")
    if os.path.exists(cache) and os.path.getmtime(cache) > os.path.getmtime(fl):
        return pickle.load(open(cache, "rb"))
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    md.skipdata = True
    refs = {}

    def note(a, sz):
        if in_data(a) or in_bss(a):
            refs.setdefault(a, set()).add(sz)
    code = rd(TEXT[0], TEXT[1] - TEXT[0])
    for ins in md.disasm(code, TEXT[0]):
        if ins.id == 0:
            continue
        for op in ins.operands:
            if op.type == X86_OP_MEM:
                disp = op.mem.disp & 0xffffffff
                sz = op.size
                # absolute or base+disp/index*scale into data
                note(disp, sz * 16 + (op.mem.scale if op.mem.index else 0) + (4096 if ins.mnemonic == "movsx" else 0))
            elif op.type == X86_OP_IMM:
                note(op.imm & 0xffffffff, 0)
    pickle.dump(refs, open(cache, "wb"))
    return refs


if __name__ == "__main__":
    r = sweep()
    print(len(r), "referenced data addresses")
