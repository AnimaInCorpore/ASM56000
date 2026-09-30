#!/usr/bin/env python3
"""Regenerate the inputs of tests/dsplnk/cases_elf.txt (prefix elf*).

The COFF->ELF debug file converter of DSPLNK only runs for target "100"
(magic 0x2cb) with -c, and it only copies sections flagged STYP_DEBUG
(0x100).  This script assembles small programs with the original
assembler, patches the object magic to 0x2cb and flips the flags of
selected sections to STYP_DEBUG, so the linker carries them into the .cld
and the converter has something to copy.

usage: python mkelf.py [path-to-ASM56000.EXE]   (run in tests/dsplnk)
"""
import os, struct, subprocess, sys, tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
ASM = sys.argv[1] if len(sys.argv) > 1 else os.path.join(ROOT, "re", "bin_ft", "ASM56000.EXE")


def parse(d):
    magic, nscns, tim, symptr, nsyms, opt, flags = struct.unpack(">7I", d[:28])
    stroff = symptr + nsyms * 32
    strlen = struct.unpack(">I", d[stroff:stroff + 4])[0] if stroff + 4 <= len(d) else 0
    secs = []
    o = 28 + opt
    for i in range(nscns):
        name = d[o:o + 8]
        if name[:4] == b"\0\0\0\0":
            off = struct.unpack(">I", name[4:])[0]
            e = d.index(b"\0", stroff + off)
            nm = d[stroff + off:e].decode()
        else:
            nm = name.split(b"\0")[0].decode()
        f = struct.unpack(">11I", d[o + 8:o + 52])
        secs.append(dict(name=nm, hdr=o, size=f[4 - 0 + 0] if False else f[4], flags=f[10],
                         paddr=f[0], scnptr=f[5]))
        o += 52
    return secs


def assemble(src, opts, out):
    with tempfile.TemporaryDirectory() as t:
        p = os.path.join(t, "x.asm")
        open(p, "w").write(src)
        r = subprocess.run([ASM, "-q"] + opts + ["-bx.cln", "x.asm"], cwd=t,
                           capture_output=True)
        if not os.path.exists(os.path.join(t, "x.cln")):
            sys.exit("assembling %s failed: %s%s" % (out, r.stdout.decode(errors="replace"), r.stderr.decode(errors="replace")))
        return open(os.path.join(t, "x.cln"), "rb").read()


def build(name, src, pred=None, opts=(), magic=0x2cb, setflags=None):
    """assemble src, mark sections for which pred(sec, idx) is true as
    STYP_DEBUG (index 0 is the first header)"""
    d = bytearray(assemble(src, list(opts), name))
    struct.pack_into(">I", d, 0, magic)
    for i, s in enumerate(parse(bytes(d))):
        if setflags is not None:
            fl = setflags(s, i)
            if fl is not None:
                struct.pack_into(">I", d, s["hdr"] + 48, fl)
        elif pred is not None and pred(s, i):
            struct.pack_into(">I", d, s["hdr"] + 48, 0x100)
    open(os.path.join(HERE, name + ".cln"), "wb").write(bytes(d))


def gen_sections(prefix, names, spaces="pxyl", size=3, org=False):
    out = []
    for i, n in enumerate(names):
        sp = spaces[i % len(spaces)]
        out.append("        section %s\n" % n)
        out.append("        xdef    sym%s%d\n" % (prefix, i))
        if org:
            out.append("        org     %s:$%x\n" % (sp, 0x100 + i * 16))
        else:
            out.append("        org     %s:\n" % sp)
        out.append("sym%s%d  dc      %s\n" % (prefix, i, ",".join(str(i * 7 + j + 1) for j in range(size + (i % 4)))))
        out.append("        endsec\n")
    return "".join(out)


alldbg = lambda s, i: s["name"] != "GLOBAL" and s["size"] > 0 or False

# 1. basic: one section name in two memory spaces (main + sub record)
build("elf01", """        section s1
        xdef    f1
        org     p:$100
f1      move    #1,x0
        move    #2,x1
        rts
        org     x:
xv      dc      1,2,3
        endsec
        end
""", lambda s, i: s["name"] == "s1")

# 2. several distinct sections, all four spaces, one with data of 24-bit
#    words whose bytes differ (low byte survives)
build("elf02", "".join([
    "        section dbga\n        xdef sa1\n        org p:$10\nsa1     dc $123456,$abcdef,$fedcba,$000001\n        endsec\n",
    "        section dbgb\n        xdef sb1\n        org x:$20\nsb1     dc $111111,$222222\n        endsec\n",
    "        section dbgc\n        xdef sc1\n        org y:$30\nsc1     dc $333333\n        endsec\n",
    "        section dbgd\n        xdef sd1\n        org l:$40\nsd1     dc $444444,$555555\n        endsec\n",
    "        end\n"]),
    lambda s, i: s["name"].startswith("dbg"))

# 3. many sections (40), half debug, some names reused in other spaces
names = ["sec%02d" % i for i in range(40)]
build("elf03", gen_sections("m", names) + "        end\n",
      lambda s, i: s["name"].startswith("sec") and int(s["name"][3:]) % 2 == 0)

# 4. long names (string table), 7/8/9 chars, absolute origin addresses so
#    that the paddr bytes follow an 8 character name
lnames = ["abcdefg", "abcdefgh", "abcdefghi", "a_very_long_section_name_number_one",
          "a_very_long_section_name_number_two", "x" * 40, "y" * 31, "Z1234567", "Z12345678"]
build("elf04", gen_sections("l", lnames, org=True) + "        end\n",
      lambda s, i: s["name"] != "GLOBAL" and s["size"] > 0)

# 5. 8 character name with a nonzero paddr high byte pattern: strlen of
#    the original continues into the (byte reversed) paddr field
n8 = ["abcdefgh", "ijklmnop", "qrstuvwx", "m2345678", "ABCDEFGH"]
src5 = ""
for i, n in enumerate(n8):
    src5 += "        section %s\n        xdef n8_%d\n        org x:$%x\nn8_%d   dc %d\n        endsec\n" % (
        n, i, [0x41, 0x4142, 0x4344, 0x1, 0x101][i], i, i + 1)
build("elf05", src5 + "        end\n", lambda s, i: s["name"] != "GLOBAL" and s["size"] > 0)

# 6. empty sections (size 0) marked debug: skipped by the converter
build("elf06", """        section e1
        org     p:$100
        endsec
        section e2
        org     x:
        endsec
        section e3
        xdef    v3
        org     x:
v3      dc      5
        endsec
        end
""", lambda s, i: s["name"] in ("e1", "e2", "e3"))

# 7. data section kinds: dc, ds, bsc
build("elf07", """        section data
        xdef    d1,d2,d3,d4
        org     x:
d1      dc      1,2,3,4,5,6,7,8
d2      ds      4
d3      bsc     5,$abcdef
d4      dc      'abc','defg'
        org     y:
        dc      $ffffff,$800000
        ds      3
        dc      $7fffff
        org     p:
        dc      $aaaaaa
        endsec
        end
""", lambda s, i: s["name"] == "data")

# 8. big section: exceeds one 0x400 shstrtab block growth via many names
names8 = ["s%03d_%s" % (i, "n" * (i % 23)) for i in range(120)]
build("elf08", gen_sections("b", names8) + "        end\n", lambda s, i: s["name"] != "GLOBAL" and s["size"] > 0)

# 9. two modules with same debug section names (merged in the .cld?)
build("elf09a", gen_sections("p", ["dbg1", "dbg2"], spaces="px") + "        end\n",
      lambda s, i: s["name"].startswith("dbg"))
build("elf09b", gen_sections("q", ["dbg1", "dbg3"], spaces="xp") + "        end\n",
      lambda s, i: s["name"].startswith("dbg"))

# 10. symbols with -g line numbers plus debug sections
build("elf10", """        section code
        xdef    main
        xref    ext1
        org     p:
main    move    #1,x0
        jsr     ext1
        do      #4,lend
        nop
lend    rts
        endsec
        section dbgx
        xdef    dd
        org     x:
dd      dc      1,2,3
        endsec
        end
""", lambda s, i: s["name"] == "dbgx", opts=["-g"])
build("elf10x", """        section code2
        xdef    ext1
        org     p:
ext1    rts
        endsec
        end
""", None, opts=["-g"])

# 12. no debug sections at all (tiny ELF)
build("elf12", """        section nodbg
        xdef    z
        org     p:
z       nop
        endsec
        end
""", None)

# 13. overlays / same-name sections in one space
build("elf13", """        section ov
        xdef    o1
        org     x:
o1      dc      1,2
        endsec
        section ov
        xdef    o2
        org     x:
o2      dc      3,4,5
        endsec
        section other
        xdef    o3
        org     y:
o3      dc      6
        endsec
        end
""", lambda s, i: s["name"] in ("ov", "other"))

# 14. module without any global symbols and only debug data
build("elf14", """        section only
        org     x:$50
        dc      $010203,$040506
        endsec
        end
""", lambda s, i: s["name"] == "only")

# 15. non-DSP56000 magics are copied through: the converter accepts
#     0x2c5..0x2cc but only 0x2cb reaches it; keep one input with 0x2cc
build("elf15", """        section s15
        xdef    q15
        org     x:
q15     dc      1
        endsec
        end
""", lambda s, i: s["name"] == "s15", magic=0x2cc)

# 16. flags: section that is both data and debug (0x140), and text|debug
build("elf16", """        section fl
        xdef    f16
        org     p:
f16     dc      1,2,3
        org     x:
        dc      4,5
        endsec
        end
""", None, setflags=lambda s, i: {True: 0x140}.get(s["name"] == "fl" and s["size"] > 0))

# 17. large data section (many words)
build("elf17", "        section big\n        xdef bigv\n        org x:\nbigv    dc 1\n        ds 3000\n        dc 2\n        endsec\n        end\n",
      lambda s, i: s["name"] == "big")

# read-only elf file: the converter cannot open its output ("Cannot open ro.elf")
p = os.path.join(HERE, "ro.elf")
if os.path.exists(p):
    os.chmod(p, 0o666)
open(p, "wb").write(b"old elf")
os.chmod(p, 0o444)

print("ok")
