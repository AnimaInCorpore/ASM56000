"""Build/patch DSP COFF (CLAS56 relocatable object) files for the ABI
expression parser tests.  All fields are big-endian 32 bit words.

  file header      7 words (magic, nscns, timdat, symptr, nsyms, opthdr, flags)
  linker header    opthdr bytes (14 words), word 5 = relocation count,
                   word 2 = strtab offset of the END expression
  section headers  8 byte name + 11 words each (paddr pmem vaddr vmem size
                   scnptr relptr lnnoptr nreloc nlnno flags), 52 bytes
  raw data, relocation records (3 words: r_vaddr, r_symndx = strtab offset of
  the expression text, unused), line numbers, symbol table (32 byte entries),
  string table (4 byte length word, offsets count from the length word).

usage as a module:
    o = Obj(open('abip_base.cln','rb').read())
    o.set_texts(['1+2', ...])         # one text per relocation record
    o.set_magic(0x2cb)
    open('x.cln','wb').write(o.bytes())
usage as a script:
    abip_coff.py info FILE           dump header, relocations and their texts
    abip_coff.py patch IN OUT TEXT.. patch the relocation texts (first N)
"""
import struct
import sys


def be(d, o):
    return struct.unpack(">L", d[o:o + 4])[0]


def put(d, o, v):
    d[o:o + 4] = struct.pack(">L", v & 0xffffffff)


class Obj:
    def __init__(self, data):
        self.d = bytearray(data)
        d = self.d
        self.nscns = be(d, 4)
        self.symptr = be(d, 12)
        self.nsyms = be(d, 16)
        self.opthdr = be(d, 20)
        self.lh = 28
        self.sh = 28 + self.opthdr
        self.nreloc = be(d, self.lh + 5 * 4)
        self.relptr = be(d, self.sh + 8 + 6 * 4)
        self.stpos = self.symptr + self.nsyms * 32
        n = be(d, self.stpos)
        self.strtab = bytearray(d[self.stpos + 4:self.stpos + n])

    def reloc_off(self, i):
        return self.relptr + 12 * i

    def reloc(self, i):
        o = self.reloc_off(i)
        return be(self.d, o), be(self.d, o + 4)

    def text(self, i):
        off = self.reloc(i)[1]
        s = off - 4
        e = self.strtab.index(b"\0", s)
        return bytes(self.strtab[s:e])

    def set_magic(self, m):
        put(self.d, 0, m)

    def add_string(self, s):
        """append a string, return its strtab offset (counted from the length word)"""
        if isinstance(s, str):
            s = s.encode("latin-1")
        off = len(self.strtab) + 4
        self.strtab += s + b"\0"
        return off

    def set_texts(self, texts, start=0):
        for k, t in enumerate(texts):
            i = start + k
            if i >= self.nreloc:
                raise ValueError("only %d relocations" % self.nreloc)
            put(self.d, self.reloc_off(i) + 4, self.add_string(t))

    def bytes(self):
        d = bytearray(self.d[:self.stpos])
        d += struct.pack(">L", len(self.strtab) + 4) + self.strtab
        return bytes(d)


def info(path):
    o = Obj(open(path, "rb").read())
    print("magic %#x nscns %d symptr %d nsyms %d nreloc %d relptr %d" % (
        be(o.d, 0), o.nscns, o.symptr, o.nsyms, o.nreloc, o.relptr))
    for i in range(o.nreloc):
        print(i, o.reloc(i), repr(o.text(i)))


if __name__ == "__main__":
    if len(sys.argv) >= 3 and sys.argv[1] == "info":
        info(sys.argv[2])
    elif len(sys.argv) >= 4 and sys.argv[1] == "patch":
        o = Obj(open(sys.argv[2], "rb").read())
        o.set_texts(sys.argv[4:])
        open(sys.argv[3], "wb").write(o.bytes())
    else:
        print(__doc__)
