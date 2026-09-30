"""Tiny DSPLNK COFF (.cln) model: parse an assembler object, edit, re-emit.

Layout (all big endian 32 bit): file header 0x1c | optional (linker) header
0x38 | section headers 0x34 each | per section raw words, relocations 0xc
each, line numbers 0xc each | symbol table 0x20 per slot | string table
(4 byte size + bytes).  Pointers in the headers are recomputed on emit()."""
import struct, sys

def be(d, o): return struct.unpack(">I", d[o:o+4])[0]
def sbe(d, o): return struct.unpack(">i", d[o:o+4])[0]

class Sec:
    pass

class Sym:
    pass

class Coff:
    def __init__(self, data=None):
        if data is not None:
            self.parse(data)

    @staticmethod
    def load(path):
        return Coff(open(path, "rb").read())

    def parse(self, d):
        self.magic, self.nscns, self.timdat, symptr, self.nsyms, opthdr, self.flags = struct.unpack(">IiiiiiI", d[:28])
        self.opthdr_size = opthdr
        self.lh = [sbe(d, 28 + 4*i) for i in range(opthdr // 4)]
        o = 28 + opthdr
        self.secs = []
        for i in range(self.nscns):
            s = Sec()
            s.name = d[o:o+8]
            (s.paddr, s.pmem, s.vaddr, s.vmem, s.size, scnptr, relptr, lnnoptr,
             nreloc, nlnno) = struct.unpack(">iiiiiiiiii", d[o+8:o+48])
            s.flags = be(d, o+48)
            s.raw = [be(d, scnptr + 4*k) for k in range(s.size)] if scnptr and s.flags & 0x60 != 0 or False else None
            self._ptr = getattr(self, "_ptr", [])
            s._scnptr, s._relptr, s._lnnoptr, s._nreloc, s._nlnno = scnptr, relptr, lnnoptr, nreloc, nlnno
            self.secs.append(s)
            o += 0x34
        # raw data: the linker header datasize words are shared: read per section by pointer
        for s in self.secs:
            s.raw = None
            s.reloc = [struct.unpack(">iii", d[s._relptr + 12*k: s._relptr + 12*k + 12]) for k in range(s._nreloc)]
            s.lines = [struct.unpack(">iii", d[s._lnnoptr + 12*k: s._lnnoptr + 12*k + 12]) for k in range(s._nlnno)]
        # raw data words in file order
        self.datawords = self.lh[1] if len(self.lh) > 1 else 0
        rawstart = 28 + opthdr + 0x34 * self.nscns
        self.rawdata = [be(d, rawstart + 4*k) for k in range(self.datawords)]
        self.rawstart = rawstart
        for s in self.secs:
            s.rawoff = (s._scnptr - rawstart) // 4
        # all reloc / lines are stored contiguously; keep global lists too
        self.relocs = []
        for s in self.secs:
            self.relocs.extend(s.reloc)
        self.symbols = []
        p = symptr
        n = 0
        while n < self.nsyms:
            y = Sym()
            y.name = d[p:p+8]
            y.value, y.mem, y.scnum, y.type, y.sclass, y.numaux = struct.unpack(">iiiiii", d[p+8:p+32])
            y.aux = []
            p += 32; n += 1
            for k in range(y.numaux):
                y.aux.append(list(struct.unpack(">8i", d[p:p+32]))); p += 32; n += 1
            self.symbols.append(y)
        ssz = be(d, p)
        self.strtab = d[p+4:p+ssz]
        self.tail = d[p+ssz:]

    def emit(self):
        nsl = sum(1 + len(y.aux) for y in self.symbols)
        # recompute layout
        nsec = len(self.secs)
        off = 28 + 0x38 * 0 + self.opthdr_size + 0x34 * nsec
        rawbytes = b"".join(struct.pack(">I", w & 0xffffffff) for w in self.rawdata)
        rel_off = off + len(rawbytes)
        secbytes = b""
        relbytes = b""
        lnbytes = b""
        nrel = sum(len(s.reloc) for s in self.secs)
        lnn_off = rel_off + 12 * nrel
        nl = sum(len(s.lines) for s in self.secs)
        sym_off = lnn_off + 12 * nl
        ro = rel_off; lo = lnn_off
        for s in self.secs:
            scnptr = (off + 4 * s.rawoff) if s._scnptr else 0
            secbytes += s.name + struct.pack(">iiiiiiiiii", s.paddr, s.pmem, s.vaddr, s.vmem, s.size,
                                             scnptr, ro if (s.reloc or s._relptr) else 0, lo, len(s.reloc), len(s.lines)) + struct.pack(">I", s.flags)
            for r in s.reloc:
                relbytes += struct.pack(">iii", *r)
            for l in s.lines:
                lnbytes += struct.pack(">iii", *l)
            ro += 12 * len(s.reloc); lo += 12 * len(s.lines)
        symbytes = b""
        for y in self.symbols:
            symbytes += y.name + struct.pack(">iiiiii", y.value, y.mem, y.scnum, y.type, y.sclass, len(y.aux))
            for a in y.aux:
                symbytes += struct.pack(">8i", *a)
        strb = struct.pack(">I", len(self.strtab) + 4) + self.strtab
        lh = list(self.lh)
        lh[5] = nrel
        body_len = sym_off + len(symbytes) + len(strb)
        lh[0] = body_len
        lh[1] = len(self.rawdata)
        hdr = struct.pack(">IiiiiiI", self.magic, nsec, self.timdat, sym_off, nsl, self.opthdr_size, self.flags)
        opt = b"".join(struct.pack(">i", v) for v in lh)
        opt += b"\0" * (self.opthdr_size - len(opt))
        return hdr + opt + secbytes + rawbytes + relbytes + lnbytes + symbytes + strb + self.tail

    def add_string(self, s):
        if isinstance(s, str): s = s.encode("latin-1")
        off = len(self.strtab) + 4
        self.strtab += s + b"\0"
        return off

    def sec_reloc_add(self, si, vaddr, text):
        self.secs[si].reloc.append((vaddr, self.add_string(text), 0))
        # global reloc index of this entry
        idx = sum(len(s.reloc) for s in self.secs[:si]) + len(self.secs[si].reloc) - 1
        return idx

def name8(n):
    # in-file name bytes for a short name: 8 bytes, byte reversed per 4-byte group? see name_get in util.c
    b = n.encode("latin-1")[:8].ljust(8, b"\0")
    return bytes([b[3], b[2], b[1], b[0], b[7], b[6], b[5], b[4]])

def name_str(n):
    b = bytes([n[3], n[2], n[1], n[0], n[7], n[6], n[5], n[4]])
    return b.split(b"\0")[0].decode("latin-1")

def longname(off):
    return b"\0\0\0\0" + struct.pack("<I", off)

if __name__ == "__main__":
    # round trip test
    for f in sys.argv[1:]:
        d = open(f, "rb").read()
        c = Coff(d)
        e = c.emit()
        print(f, "roundtrip", "OK" if e == d else "DIFF %d %d" % (len(e), len(d)))
