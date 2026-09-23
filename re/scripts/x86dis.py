"""Disassemble a range of a PE32 image by virtual address.

usage: x86dis.py <exe> <start-va hex> [<end-va hex> | +<len hex>]
Annotates pushes/moves of addresses that point at C strings.
"""
import sys, struct, capstone

def load(path):
    d = open(path, "rb").read()
    pe = struct.unpack_from("<I", d, 0x3c)[0]
    nsec = struct.unpack_from("<H", d, pe + 6)[0]
    optsz = struct.unpack_from("<H", d, pe + 20)[0]
    base = struct.unpack_from("<I", d, pe + 52)[0]
    secs = []
    o = pe + 24 + optsz
    for i in range(nsec):
        name = d[o:o + 8].rstrip(b"\0").decode()
        vsz, va, rsz, roff = struct.unpack_from("<IIII", d, o + 8)
        secs.append((base + va, max(vsz, rsz), roff, rsz, name))
        o += 40
    return d, base, secs

def reader(d, secs):
    def rd(va, n):
        for sva, sz, roff, rsz, _ in secs:
            if sva <= va < sva + sz:
                off = va - sva
                b = d[roff + off: roff + min(off + n, rsz)]
                return b + b"\0" * (n - len(b))
        return None
    return rd

def cstr(rd, va):
    b = rd(va, 200)
    if not b:
        return None
    s = b.split(b"\0")[0]
    if len(s) >= 2 and all(32 <= c < 127 or c in (9, 10, 13) for c in s):
        return s.decode()
    return None

def main():
    d, base, secs = load(sys.argv[1])
    rd = reader(d, secs)
    start = int(sys.argv[2], 16)
    if len(sys.argv) > 3:
        a = sys.argv[3]
        end = start + int(a[1:], 16) if a.startswith("+") else int(a, 16)
    else:
        end = start + 0x100
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    for ins in md.disasm(rd(start, end - start), start):
        note = ""
        for tok in ins.op_str.replace(",", " ").replace("[", " ").replace("]", " ").split():
            if tok.startswith("0x") and len(tok) >= 8:
                v = int(tok, 16)
                s = cstr(rd, v)
                if s is not None:
                    note = "  ; " + repr(s)
        print("%08x  %-8s %s%s" % (ins.address, ins.mnemonic, ins.op_str, note))

if __name__ == "__main__":
    main()
