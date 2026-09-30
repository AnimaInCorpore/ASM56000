"""Generate hand-made DSP COFF files that exercise the corners of cofdmp.

Run from tests/cofdmp; writes the x_*.cl? files (and a few non-COFF inputs)
into the current directory.  Some are derived from the files the original
assembler/linker produced (r1.cln, r3.cln, t2g.cld, t2g.cln, lnkg.cld).
"""
import struct

def w(*v):
    return b"".join(struct.pack(">I", x & 0xffffffff) for x in v)

def name8(s):
    b = s.encode("latin-1") if isinstance(s, str) else s
    return (b + b"\0" * 8)[:8]

def fword(x):
    return struct.unpack(">II", struct.pack(">d", x))

class Coff:
    def __init__(self, magic=0x2c5, timdat=0x12345678, flags=0, opt=b""):
        self.magic, self.timdat, self.flags, self.opt = magic, timdat, flags, opt
        self.scns = []          # dicts
        self.syms = []          # raw 32-byte entries
        self.strs = b""
        self.strtab = True
        self.strlen = None      # override for the length word

    def string(self, s):
        off = 4 + len(self.strs)
        self.strs += s.encode("latin-1") + b"\0"
        return off

    def nm(self, s):
        if isinstance(s, int):
            return w(0, s)
        if len(s) > 8:
            return w(0, self.string(s))
        return name8(s)

    def scn(self, name, pmem=0, paddr=0, vmem=0, vaddr=0, data=(), flags=0x20,
            relocs=(), lnnos=(), size=None, nreloc=None, nlnno=None):
        self.scns.append(dict(name=self.nm(name), pmem=pmem, paddr=paddr, vmem=vmem,
                              vaddr=vaddr, data=list(data), flags=flags,
                              relocs=list(relocs), lnnos=list(lnnos), size=size,
                              nreloc=nreloc, nlnno=nlnno))

    def sym(self, name, value=0, mem=0, scnum=0, type=0, sclass=2, aux=()):
        self.syms.append(self.nm(name) + w(value, mem, scnum, type, sclass, len(aux)))
        for a in aux:
            if isinstance(a, bytes):
                self.syms.append((a + b"\0" * 32)[:32])
            else:
                self.syms.append(w(*(list(a) + [0] * 8)[:8]))

    def build(self):
        nscns = len(self.scns)
        pos = 28 + len(self.opt) + 52 * nscns
        body = b""
        for s in self.scns:
            s["scnptr"] = pos + len(body) if s["data"] else 0
            body += w(*s["data"])
            s["relptr"] = pos + len(body) if s["relocs"] else 0
            for r in s["relocs"]:
                body += w(*r)
            s["lnnoptr"] = pos + len(body) if s["lnnos"] else 0
            for l in s["lnnos"]:
                body += w(*l)
        symptr = pos + len(body) if self.syms else 0
        hdr = w(self.magic, nscns, self.timdat, symptr, len(self.syms),
                len(self.opt), self.flags)
        sh = b""
        for s in self.scns:
            size = s["size"] if s["size"] is not None else len(s["data"])
            sh += s["name"] + w(s["paddr"], s["pmem"], s["vaddr"], s["vmem"], size,
                                s["scnptr"], s["relptr"], s["lnnoptr"],
                                s["nreloc"] if s["nreloc"] is not None else len(s["relocs"]),
                                s["nlnno"] if s["nlnno"] is not None else len(s["lnnos"]),
                                s["flags"])
        out = hdr + self.opt + sh + body + b"".join(self.syms)
        if self.strtab and (self.strs or self.strlen is not None):
            n = self.strlen if self.strlen is not None else len(self.strs) + 4
            out += w(n) + self.strs
        return out

def save(name, data):
    open(name, "wb").write(data)

def rd(name):
    return bytearray(open(name, "rb").read())

def get(d, off):
    return struct.unpack_from(">I", d, off)[0]

def put(d, off, v):
    struct.pack_into(">I", d, off, v & 0xffffffff)

def lnkhdr(**kw):
    f = dict(modsize=0, datasize=0, endstr=-1, secnt=1, ctrcnt=1, relocnt=0,
             lnocnt=0, bufcnt=0, ovlcnt=0, majver=6, minver=3, revno=0, x=0, sditot=0)
    f.update(kw)
    return w(*f.values())

def aouthdr(mems=(0, 0, 0, 0, 0), addrs=(0x100, 0, 0, 0x200, 0)):
    v = [0x2c5, 1, 10, 20, 30]
    for a, m in zip(addrs, mems):
        v += [a, m]
    return w(*v)

def shift_ptrs(d, at, delta):
    """insert/remove bytes at 'at': fix every file pointer behind it"""
    opthdr = get(d, 20)
    nscns = get(d, 4)
    if get(d, 12) >= at:
        put(d, 12, get(d, 12) + delta)
    base = 28 + opthdr
    for i in range(nscns):
        o = base + 52 * i
        for f in (0x1c, 0x20, 0x24):
            p = get(d, o + f)
            if p and p >= at:
                put(d, o + f, p + delta)

def main():
    # --- not COFF / short files
    save("x_text.txt", b"this is not a COFF file\r\nat all\r\n")
    save("x_short.bin", b"\0\0\2\xc5\0\0")
    save("x_empty.bin", b"")

    # --- other processors: magic numbers 0x2c6 .. 0x2cc
    for m in range(0x2c6, 0x2cd):
        d = rd("t2g.cln")
        put(d, 0, m)
        save("x_m%x.cln" % m, d)

    # --- old 40-byte linker header (no majver/minver/revno), fed from r1/r3
    for src, dst in (("r1.cln", "x_old1.cln"), ("r3.cln", "x_old3.cln")):
        d = rd(src)
        at = 28 + 0x28
        del d[at:at + 16]
        put(d, 20, 0x28)
        shift_ptrs(d, at, -16)
        save(dst, d)

    # --- optional header longer than the original's buffer (absolute file):
    # overwrites the F_RELFLG flag and the file header
    d = rd("t2g.cld")
    opt = get(d, 20)
    at = 28 + opt
    extra = w(0, 0x2c6, 99, 0x7fffffff, get(d, 12) + 0x20, get(d, 16), opt + 0x20, 0x20000)
    d[at:at] = extra
    put(d, 20, opt + len(extra))
    shift_ptrs(d, at, len(extra))
    save("x_ovfa.cld", d)

    # --- linker header longer than its buffer: overwrites nsyms and symptr
    d = rd("r1.cln")
    at = 28 + 0x38
    nsyms, symptr = get(d, 16), get(d, 12)
    extra = w(nsyms, 0x11111111, symptr + 16, 0x22222222)
    d[at:at] = extra
    put(d, 20, 0x38 + 16)
    shift_ptrs(d, at, 16)
    put(d, 16, 0)               # only the overwritten value finds the symbols
    save("x_ovfl.cln", d)

    # --- string table corner cases
    d = rd("r1.cln")
    stpos = get(d, 12) + 32 * get(d, 16)
    e = bytearray(d); put(e, stpos, 4); del e[stpos + 4:]; save("x_st4.cln", e)
    e = bytearray(d); put(e, stpos, 2); save("x_st2.cln", e)
    e = bytearray(d); put(e, stpos, 0); save("x_st0.cln", e)
    e = bytearray(d); del e[stpos:]; save("x_stnone.cln", e)
    e = bytearray(d); del e[stpos + 2:]; save("x_stpart.cln", e)
    e = bytearray(d); put(e, stpos, 0x7ffffff0); save("x_stbig.cln", e)
    e = bytearray(d); put(e, stpos, 0x100); save("x_stshrt.cln", e)
    e = bytearray(d); put(e, stpos, 0x80000002); save("x_stwrap.cln", e)
    e = bytearray(d); e += b"no terminator"; put(e, stpos, get(e, stpos) + 13)
    save("x_stnoz.cln", e)
    e = bytearray(d); put(e, 12, 0x80000000); save("x_symneg.cln", e)
    # truncated in the symbol table / aux entries / section data
    e = bytearray(d); del e[get(d, 12) + 32 * 3 + 5:]; save("x_trsym.cln", e)
    e = bytearray(d); del e[get(d, 12) + 32 + 7:]; save("x_traux.cln", e)
    e = bytearray(d); del e[28 + 56 + 52 * 3 + 10:]; save("x_trscn.cln", e)
    e = bytearray(d); del e[28 + 20:]; save("x_tropt.cln", e)
    d3 = rd("lnkg.cld")
    for i in range(get(d3, 4)):
        o = 28 + get(d3, 20) + 52 * i
        if get(d3, o + 0x1c) and get(d3, o + 0x18) > 1:
            break
    e = bytearray(d3); del e[get(d3, o + 0x1c) + 5:]; save("x_trraw.cld", e)

    # --- hand-made files
    c = Coff(timdat=0)
    c.scn("abcdefgh", pmem=0, paddr=0x41424344, vmem=0, vaddr=0x107, data=[1, 2, 3, 4, 5])
    c.scn("tabcdefgh_long", pmem=1, paddr=0x10, vmem=1, vaddr=0x10, data=[0xffffff] * 9,
          flags=0x40, relocs=[(1, c.string("{{sym1}}@0#0"), 0), (2, 4, 0)],
          lnnos=[(0x10, 1, 0), (0x11, 1, 5), (0x12, 0x125, 6), (5, -1, 7)])
    c.scn("blk", pmem=3, paddr=0x100, vmem=3, vaddr=40, data=[0x123, 0x456], flags=0x440)
    c.scn("bss", pmem=2, paddr=0, vmem=2, vaddr=0, flags=0x80, size=100)
    for i, f in enumerate((1, 2, 4, 8, 0x10, 0x20 | 0x1000 | 0x2000 | 0x100 | 0x4000 | 0x800,
                           0x7fff0000)):
        c.scn("f%d" % i, pmem=4 + i, vmem=0x11c + i, flags=f)
    c.scn("mem", pmem=0x11d, paddr=1, vmem=0x121, vaddr=2, flags=0x40)
    c.scn("mem2", pmem=0x122, paddr=1, vmem=0, vaddr=2, flags=0)
    c.scn("mem3", pmem=-1, paddr=1, vmem=0, vaddr=2, flags=0)
    c.sym(".file", scnum=-2, type=1, sclass=0x67, aux=[b"C:\\dsp\\mod.asm"])
    c.sym(".file", scnum=-2, type=0, sclass=200, aux=[w(0, 0, 0, 0, c.string("[usr.dsp.src]mod.asm"), 7)])
    c.sym(".file", scnum=-2, type=1, sclass=200, aux=[w(0, 0, 0, 0, c.string(":mac:dsp:mod.asm"), 0)])
    c.sym(".file", scnum=-2, type=1, sclass=200, aux=[b"a:b\\c.d[e]f.g"])
    c.sym(".sect", value=0x100, mem=0, scnum=1, type=0, sclass=3,
          aux=[(5, 2, 3), (1, 2, 0x2000, 0, 0, 0, 0), (4, 0x400, 16), (1, 2, 3, 4, 5, 6, 7)])
    c.sym(".sect2", value=0x100, mem=1, scnum=2, type=0, sclass=3,
          aux=[(5, 2, 3), (1, 2, 0x4000, 1, 1, 0, 0), (0, 1, 0, 0, 3, -1, 0x10)])
    c.sym(".sect3", value=0, mem=2, scnum=3, type=0x10000, sclass=3, aux=[(1, 2, 3)])
    c.sym("strtag", sclass=10, type=8, aux=[(0, 0, 12, 0, 20)])
    c.sym("untag", sclass=12, type=9, aux=[(0, 0, 4, 0, 30)])
    c.sym("entag", sclass=15, type=10, aux=[(0, 0, 2, 0, 40)])
    c.sym(".eos", sclass=0x66, aux=[(7, 0, 12)])
    c.sym(".bf", sclass=0x65, aux=[(0, 33, 0, 0, 9, 0x24)])
    c.sym(".ef", sclass=0x65, aux=[(0, 34, 0, 0, 9, 0)])
    c.sym(".bb", sclass=0x64, aux=[(0, 35, 0, 0, 11, 0x5)])
    c.sym(".bs", sclass=0xc9, scnum=-1, aux=[(3, 12, 0, 0, 44)])
    c.sym("mac", sclass=0xcb, scnum=-1, aux=[(3, 13, 0, 0, 45)])
    c.sym("fld", sclass=0x12, type=4, aux=[(0, 0, 7)])
    c.sym("func", value=0x100, scnum=1, sclass=2, type=0x24, aux=[(5, 50, 0, 1000, 60)])
    c.sym("array", value=0x10, mem=1, scnum=2, sclass=2, type=0x34, aux=[(1, 2, 30, 5, 6, 0, 0)])
    c.sym("array2", value=0x10, mem=1, scnum=2, sclass=2, type=0x3d4,
          aux=[(1, 2, 30, 5, 6, 7, 8)])
    c.sym("ptrfn", value=0x10, mem=1, scnum=2, sclass=2, type=0x10015)
    c.sym("struct", value=0x10, mem=1, scnum=2, sclass=2, type=8, aux=[(4, 0, 12)])
    c.sym("union", value=0x10, mem=1, scnum=2, sclass=2, type=9, aux=[(4, 0, 12)])
    c.sym("enum", value=0x10, mem=1, scnum=2, sclass=2, type=10, aux=[(4, 0, 12)])
    c.sym("other", value=0x10, mem=1, scnum=2, sclass=2, type=4, aux=[(4, 0, 12)])
    for i, (hi, lo) in enumerate((fword(1.5), fword(-3.0e-10), fword(1e300), fword(-1e-300),
                                  (0, 1), (0x80000000, 0), (0x7ff00000, 0), (0xfff00000, 0),
                                  (0x7ff80000, 0), (0xfff80000, 0), (0x7ff00000, 1),
                                  (0x7ff80000, 5), (0xfff00000, 3), (0, 0),
                                  fword(123456789.0), fword(9.9999995e-1))):
        c.sym("flt%d" % i, value=lo, mem=hi, scnum=-1, sclass=2, type=6 | (0x20 if i & 1 else 0))
    c.sym("dbl", value=5, mem=6, scnum=-1, sclass=2, type=5)
    c.sym("ldbl", value=5, mem=6, scnum=-1, sclass=2, type=0x10005)
    for i, m in enumerate((0, 3, 4, 27, 28, 29, 284, 285, 289, 290, 0x123, 0x124, -1)):
        c.sym("m%d" % m, value=i, mem=m, scnum=1 + i % 3, sclass=2, type=i)
    for i, s in enumerate(list(range(-2, 22)) + [99, 100, 106, 107, 127, 128, 129, 130, 199,
                                                 200, 203, 204, 209, 210, 215, 216, 0x10000]):
        c.sym("sc%d" % i, value=i, mem=0, scnum=[-3, -2, -1, 0, 1, 70000][i % 6], sclass=s,
              type=[0, 15, 16, 21, 22, 23, 0x40, 0xffff0][i % 8] if s not in (0x67, 200) else i % 2)
    c.sym("verylongsymbolname_in_strtab", value=0x55, mem=1, scnum=1, sclass=2, type=4)
    save("x_misc.cln", c.build())

    c = Coff(timdat=0x7fffffff)
    c.sym("typ22", value=1, mem=1, scnum=1, sclass=2, type=0x10006)
    save("x_typ22.cln", c.build())
    c = Coff(timdat=-0x80000000)
    c.sym(".file", scnum=-2, type=2, sclass=0x67, aux=[b"f.asm"])
    save("x_ftyp2.cln", c.build())

    # time stamps
    for i, t in enumerate((0, -1, 86399, 86400, 951782400, 951868800, 1234567890,
                           -0x80000000, 0x7fffffff, 68169600, 4107542399 - 2**32,
                           -2208988800 + 2**32)):
        c = Coff(timdat=t)
        save("x_t%d.cln" % i, c.build())

    # sections without symbols: no string table, section name offset fails
    c = Coff()
    c.scn(4, data=[1])
    c.strtab = False
    save("x_nostr.cln", c.build())

    # linker header with the SDI flag and an end expression string
    c = Coff(flags=0x20000 | 0x10000 | 0x3e, opt=None)
    c.opt = lnkhdr(endstr=4, sditot=77)
    c.string("entry+1")
    c.scn("sec", data=[7, 8], relocs=[(0, 4, 0)])
    c.sym("x", scnum=1)
    save("x_sdi.cln", c.build())
    c.opt = lnkhdr(endstr=2)
    save("x_endbad.cln", c.build())
    c.opt = lnkhdr(endstr=1000)
    save("x_endbig.cln", c.build())
    c.opt = lnkhdr(endstr=-1)
    c.scns[0]["relocs"] = [(0, 3, 0)]
    save("x_relbad.cln", c.build())

    # absolute files: optional header memory spaces
    c = Coff(flags=0x103, opt=aouthdr())
    c.scn(".text", data=[1, 2])
    save("x_aout.cld", c.build())
    c.opt = aouthdr(mems=(0, 1, 2, 289, 3))
    save("x_aout2.cld", c.build())
    c.opt = aouthdr(mems=(0, 1, 2, 290, 3))
    save("x_aout3.cld", c.build())
    c.opt = aouthdr(mems=(-1, 1, 2, 3, 3))
    save("x_aout4.cld", c.build())
    c.opt = aouthdr()[:40]      # short optional header
    save("x_aout5.cld", c.build())

    # bad values in section headers
    c = Coff()
    c.scn("neg", data=[1], size=-5)
    save("x_rawneg.cln", c.build())
    c = Coff()
    c.scn(2, data=[1])
    save("x_scnbad.cln", c.build())
    c = Coff()
    c.scn("seek", data=[1])
    d = bytearray(c.build())
    put(d, 28 + 0x1c, 0x80000000)
    save("x_rawsk.cln", d)
    c = Coff()
    c.scn("big", data=[1], size=0x40000001)
    save("x_rawbig.cln", c.build())
    c = Coff()
    c.scn("rel", data=[1], relocs=[(0, 4, 0)], nreloc=5)
    save("x_reltr.cln", c.build())
    c = Coff()
    c.scn("lnno", data=[1], lnnos=[(0, 0, 1)], nlnno=3)
    save("x_lnotr.cln", c.build())
    c = Coff()
    c.scn("relneg", data=[1], relocs=[(0, 4, 0)], nreloc=-1, lnnos=[(0, 0, 1)], nlnno=-1)
    save("x_neg.cln", c.build())
    c = Coff()
    c.sym(2, value=1)
    save("x_symbad.cln", c.build())
    c = Coff()
    c.sym(".file", scnum=-2, sclass=0x67, aux=[w(0, 0, 0, 0, 2, 0)])
    save("x_fnbad.cln", c.build())
    c = Coff()
    c.sym("naux", value=1, aux=[(1,)] * 3)
    d = bytearray(c.build())
    put(d, get(d, 12) + 0x1c, -1)
    save("x_nauxng.cln", d)
    c = Coff()
    c.scn("sk", data=[1])
    d = bytearray(c.build())
    put(d, 4, 0x7fffffff)
    save("x_nscns.cln", d)
    put(d, 4, -3)
    save("x_nscneg.cln", d)

if __name__ == "__main__":
    main()
