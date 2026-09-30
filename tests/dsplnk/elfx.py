#!/usr/bin/env python3
"""Deep test of the COFF->ELF converter of DSPLNK on hand-crafted COFF files.

DSPLNK's converter reads the .cld the linker has just written, so its
error paths cannot be reached with real linker output.  This script makes
private test builds of both sides in which the converter reads the fixed
file "cx.cld" of the current directory instead:
  - original: re/bin_ft/DSPLNK.EXE with the argument of the coff_to_elf call
    (0x401d7c) redirected to the string "cx.cld" (written over the -v
    message format at 0x453b3c; do not use -v),
  - port: src/dsplnk/dsplnk.c compiled with coff_to_elf("cx.cld", ...).
Both run `dsplnk -q -c -bo.cld elf12.cln` (target "100") in scratch dirs that
hold a crafted cx.cld; stdout, stderr, exit code and all written files
(o.elf!) must be identical.

usage: python elfx.py [-k]     (run in tests/dsplnk; -k keeps the scratch dirs)
Needs the MSYS2 gcc of CLAUDE.md and the fixed-clock original in re/bin_ft.
"""
import os, re, shutil, struct, subprocess, sys, tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
BLD = os.path.join(ROOT, "build_elf")
ORIG_X = os.path.join(BLD, "DSPLNK_X.EXE")
NEW_X = os.path.join(BLD, "dsplnk_x.exe")


def prepare():
    os.makedirs(BLD, exist_ok=True)
    d = bytearray(open(os.path.join(ROOT, "re", "bin_ft", "DSPLNK.EXE"), "rb").read())
    assert d[0x117c:0x1182] == bytes.fromhex("8b0d641d4600")
    d[0x117c:0x1182] = bytes.fromhex("b93c3b450090")
    s = 0x453b3c - 0x453b3c
    # file offset of 0x453b3c (.rdata): find the format string
    i = d.index(b"%s: Creating ELF debug information file: %s\n")
    d[i:i + 7] = b"cx.cld\0"
    open(ORIG_X, "wb").write(d)
    src = open(os.path.join(ROOT, "src", "dsplnk", "dsplnk.c")).read()
    assert "coff_to_elf(obj_name, elfname)" in src
    open(os.path.join(BLD, "dsplnk_x.c"), "w").write(
        src.replace("coff_to_elf(obj_name, elfname)", 'coff_to_elf("cx.cld", elfname)'))
    stub = os.path.join(BLD, "abistub_x.c")
    a = open(os.path.join(ROOT, "src", "dsplnk", "abistub.c")).read()
    if "int coff_to_elf" in a:
        i = a.index("int coff_to_elf")
        j = a.index("EXPR *abi_expr_eval(")
        a = a[:i] + a[j:]
    open(stub, "w").write(a)
    files = " ".join("src/dsplnk/%s.c" % n for n in
                     "arith error eval fixup func input lib lnkglb map memctl object sdi symtab util elfout cof2elf abidbg".split())
    cmd = ("cd %s && gcc -O2 -std=c89 -pedantic -Wall -Isrc/dsplnk -o build_elf/dsplnk_x.exe "
           "build_elf/dsplnk_x.c build_elf/abistub_x.c %s" % (ROOT.replace("\\", "/").replace("C:", "/c"), files))
    env = dict(os.environ, MSYSTEM="MINGW64", CHERE_INVOKING="1")
    r = subprocess.run([r"C:\msys64\usr\bin\bash.exe", "-lc", cmd], env=env,
                       capture_output=True)
    if r.returncode:
        sys.exit(r.stdout.decode() + r.stderr.decode())


# ---- crafted COFF ------------------------------------------------------

def be(*v):
    return b"".join(struct.pack(">I", x & 0xffffffff) for x in v)


def coff(sections, strtab=None, magic=0x2cb, flags=0x10003, opt=0x3c, nsyms=3,
         opt_bytes=None, nsyms_real=None, strtab_raw=None, symptr=None, nscns=None, trunc=None,
         sec_flags_fix=None):
    """sections: list of dict(name=str|bytes8|('off',n), paddr, size, scnptr,
    flags, data=bytes|None).  Sections with data get scnptr assigned after the
    symbol table unless given."""
    hdr_end = 28 + opt + 52 * len(sections)
    body = bytearray()
    heads = []
    pos = hdr_end
    # data first (keeps scnptr simple)
    for s in sections:
        s = dict(s)
        if "scnptr" not in s:
            if s.get("data"):
                s["scnptr"] = pos + len(body)
                body += s["data"]
            else:
                s["scnptr"] = 0
        heads.append(s)
    symoff = pos + len(body)
    body += b"\0" * (32 * (nsyms if nsyms_real is None else nsyms_real))
    if strtab_raw is not None:
        body += strtab_raw
    elif strtab is not None:
        body += struct.pack(">I", len(strtab) + 4) + strtab
    if symptr is None:
        symptr = symoff
    out = bytearray(be(magic, len(sections) if nscns is None else nscns, 931960800, symptr,
                       nsyms, opt, flags))
    out += opt_bytes if opt_bytes is not None else b"\0" * opt
    for s in heads:
        nm = s["name"]
        if isinstance(nm, tuple):
            nb = be(0, nm[1])
        else:
            if isinstance(nm, str):
                nm = nm.encode()
            nb = nm.ljust(8, b"\0")[:8]
        out += nb + be(s.get("paddr", 0), 0, 0, 0, s.get("size", 0), s.get("scnptr", 0),
                       0, 0, 0, 0, s.get("flags", 0x100), 0, 0)[:44]
    # section header is 0x34 bytes: 8 + 11 longs; be(...) above gave 13 longs, cut to 44
    out += body
    if trunc is not None:
        out = out[:trunc]
    return bytes(out)


def words(n, seed=1):
    return b"".join(struct.pack(">I", ((seed * 0x010101 * (i + 1)) ^ (i * 0x0f0f0f)) & 0xffffff) for i in range(n))


def dbg(name, size, paddr=0, **kw):
    d = dict(name=name, size=size, paddr=paddr, flags=0x100, data=words(min(size, 30000), len(str(name)) + size % 97))
    d.update(kw)
    return d


def strtab_names(names):
    """string table content and the offsets (from the table start, i.e. 4 + pos)"""
    t = b""
    offs = []
    for n in names:
        offs.append(4 + len(t))
        t += n.encode() + b"\0"
    return t + bytes(4), offs


CASES = []


def case(name, data, files=None, opts=None):
    CASES.append((name, data, files or {}, opts))


def build_cases():
    st, of = strtab_names(["long_section_name_1", "another_quite_long_name", "x"])
    case("valid_basic", coff([dbg(".dbg", 3, 0x100), dbg("other", 5, 7)], strtab=b"\0"))
    case("valid_longnames", coff([dbg(("off", of[0]), 2, 1), dbg(("off", of[1]), 4, 2),
                                   dbg(("off", of[2]), 1, 3)], strtab=st))
    case("valid_dupnames", coff([dbg(".d", 2, 1), dbg(".e", 1, 2), dbg(".d", 3, 3),
                                  dbg(".d", 1, 4), dbg(".e", 2, 5)], strtab=b"\0"))
    case("valid_nodbgflag", coff([dict(name=".t", size=3, paddr=1, flags=0x20, data=words(3)),
                                   dbg(".d", 2)], strtab=b"\0"))
    case("valid_zero_size", coff([dbg(".z", 0), dbg(".d", 2)], strtab=b"\0"))
    case("valid_nosections", coff([], strtab=b"\0"))
    case("valid_allflagbits", coff([dict(name=".fl", size=2, paddr=9, flags=0xffffffff, data=words(2))],
                                    strtab=b"\0"))
    case("valid_8char", coff([dbg("abcdefgh", 2, 0x41), dbg("ijklmnop", 1, 0x4142)], strtab=b"\0"))
    case("valid_8char_hi", coff([dbg("abcdefgh", 2, 0x41414141), dbg("ijklmnop", 1, 0x7f7f7f7f),
                                  dbg("qrstuvwx", 1, 0x80808080), dbg("ABCDEFGH", 1, -1)],
                                 strtab=b"\0"))
    case("valid_1char", coff([dbg("a", 1), dbg("b", 1), dbg("a", 2)], strtab=b"\0"))
    case("valid_name_dot", coff([dbg(".debug_info", 4, 0), dbg(".debug_line", 3, 0), dbg(".debug_info", 2, 0)],
                                 strtab=b"\0"))
    case("valid_name_empty", coff([dict(name=b"", size=2, paddr=1, flags=0x100, data=words(2))], strtab=b"\0"))
    case("valid_name_empty_off", coff([dbg(("off", 4), 2)], strtab=b"\0" + b"z\0"))
    case("valid_name_dup_long_short", coff([dbg(("off", of[2]), 2, 1), dbg("x", 3, 2)], strtab=st))
    case("valid_paddr_big", coff([dbg("p1", 2, 0xfffffff0), dbg("p2", 2, 0x80000000), dbg("p3", 1, 0x7fffffff)],
                                  strtab=b"\0"))
    case("valid_optzero", coff([dbg("d", 2)], strtab=b"\0", opt=0))
    case("valid_opt56", coff([dbg("d", 2)], strtab=b"\0", opt=56, flags=0x10002))
    case("valid_opt60abs", coff([dbg("d", 2)], strtab=b"\0", opt=60, flags=0x10003))
    case("valid_opt100abs", coff([dbg("d", 2)], strtab=b"\0", opt=100, flags=0x10003))
    case("valid_opt8", coff([dbg("d", 2)], strtab=b"\0", opt=8, flags=0x2))
    case("valid_flags2", coff([dbg("d", 2)], strtab=b"\0", flags=2))
    case("valid_flags_hi", coff([dbg("d", 2)], strtab=b"\0", flags=0xfffffffe))
    for m in range(0x2c5, 0x2cd):
        case("magic_%x" % m, coff([dbg("d", 2)], strtab=b"\0", magic=m))
    for m in (0x2c4, 0x2cd, 0, 0x2cb00, 0x82cb):
        case("badmagic_%x" % m, coff([dbg("d", 2)], strtab=b"\0", magic=m))
    case("noexec_flag", coff([dbg("d", 2)], strtab=b"\0", flags=0x10001))
    case("noexec_flag0", coff([dbg("d", 2)], strtab=b"\0", flags=0))
    # header truncation
    full = coff([dbg("d", 2)], strtab=b"\0")
    for n in (0, 1, 27, 28):
        case("trunc_hdr_%d" % n, full[:n])
    case("trunc_opt_abs", full[:28 + 30], )
    case("trunc_opt_rel", coff([dbg("d", 2)], strtab=b"\0", flags=2)[:28 + 30])
    case("trunc_opt_exact", full[:28 + 60])
    case("trunc_sec0", full[:28 + 60 + 10])
    case("trunc_sec_full", full[:28 + 60 + 52])
    # string table
    case("nsyms0", coff([dbg("d", 2)], strtab=b"\0", nsyms=0))
    case("strtab_len1", coff([dbg("d", 2)], strtab_raw=be(1)))
    case("strtab_len3", coff([dbg("d", 2)], strtab_raw=be(3)))
    case("strtab_len4", coff([dbg("d", 2)], strtab_raw=be(4)))
    case("strtab_len5", coff([dbg("d", 2)], strtab_raw=be(5) + b"x"))
    case("strtab_len0", coff([dbg("d", 2)], strtab_raw=be(0)))
    case("strtab_neg", coff([dbg("d", 2)], strtab_raw=be(0xffffffff)))
    case("strtab_bigger_than_file", coff([dbg("d", 2)], strtab_raw=be(0x2000) + b"abc"))
    case("strtab_missing", coff([dbg("d", 2)]))
    case("strtab_len_partial", coff([dbg("d", 2)])[:] + b"\0\0")
    case("strtab_noNUL", coff([dbg(("off", 4), 2)], strtab_raw=be(8) + b"abcd"))
    case("symptr_beyond", coff([dbg("d", 2)], strtab=b"\0", symptr=0x1000))
    case("symptr_negative", coff([dbg("d", 2)], strtab=b"\0", symptr=0xfffffff0))
    case("nsyms_negative", coff([dbg("d", 2)], strtab=b"\0", nsyms=0xfffffff0, nsyms_real=3))
    case("nsyms_huge", coff([dbg("d", 2)], strtab=b"\0", nsyms=0x7fffffff, nsyms_real=3))
    # long-name offsets
    for o in (0, 1, 3, 4, 5, 6, 0x7fffffff, 0xffffffff, 0x80000000):
        case("nameoff_%x" % o, coff([dbg(("off", o), 2)], strtab=b"abcdef\0"))
    case("nameoff_len", coff([dbg(("off", 4 + 6), 2)], strtab=b"abcdef\0"))
    case("nameoff_len_plus1", coff([dbg(("off", 4 + 7), 2)], strtab=b"abcdef\0"))
    case("nameoff_end", coff([dbg(("off", 4 + 6), 2)], strtab=b"abcdef\0"))
    case("nameoff_second_bad", coff([dbg(("off", 4), 2), dbg(("off", 99), 2)], strtab=b"abcdef\0"))
    case("nameoff_nodbg_bad", coff([dict(name=("off", 99), size=2, paddr=0, flags=0x20, data=words(2)),
                                     dbg("d", 2)], strtab=b"abcdef\0"))
    # section headers
    case("nscns_beyond", coff([dbg("d", 2)], strtab=b"\0", nscns=5))
    case("nscns_huge", coff([dbg("d", 2)], strtab=b"\0", nscns=0x100000))
    case("nscns_neg", coff([dbg("d", 2)], strtab=b"\0", nscns=0xffffffff))
    case("nscns_zero", coff([dbg("d", 2)], strtab=b"\0", nscns=0))
    # data pointers
    case("scnptr_beyond", coff([dbg("d", 4, scnptr=0x5000)], strtab=b"\0"))
    case("scnptr_partial", coff([dbg("d", 4)], strtab=b"\0")[:] , )
    full2 = coff([dbg("d", 4)], strtab=b"\0")
    case("scnptr_eofcut", full2[:-40])
    case("scnptr_zero", coff([dbg("d", 4, scnptr=0)], strtab=b"\0"))
    case("scnptr_negative", coff([dbg("d", 4, scnptr=0xfffffff0)], strtab=b"\0"))
    case("scnptr_negative_2", coff([dbg("d", 4, scnptr=0xfffffff0), dbg("e", 2)], strtab=b"\0"))
    case("size_1", coff([dbg("d", 1)], strtab=b"\0"))
    case("size_big", coff([dbg("d", 20000)], strtab=b"\0"))
    case("size_bigger_than_file", coff([dbg("d", 300000, data=words(4))], strtab=b"\0"))
    case("size_multi", coff([dbg("d", 3), dbg("d", 0x1000), dbg("d", 1), dbg("d", 2)], strtab=b"\0"))
    case("overlap_data", coff([dbg("d", 4, scnptr=28 + 60 + 104 + 8), dbg("e", 4, scnptr=28 + 60 + 104 + 8)],
                              strtab=b"\0"))
    # many sections
    many = [dbg("s%d" % i, i % 7 + 1, i) for i in range(300)]
    case("many_300", coff(many, strtab=b"\0"))
    names = ["section_with_a_rather_long_name_%04d" % i for i in range(500)]
    st2, of2 = strtab_names(names)
    case("many_long_500", coff([dbg(("off", of2[i]), i % 5 + 1, i) for i in range(500)], strtab=st2))
    case("many_dup_names", coff([dbg("d%d" % (i % 9), i % 4 + 1, i) for i in range(90)], strtab=b"\0"))
    big = ["n" * (i % 60 + 20) + "%d" % i for i in range(2000)]
    st3, of3 = strtab_names(big)
    case("huge_strtab", coff([dbg(("off", of3[i]), 1, i) for i in range(2000)], strtab=st3))
    # shstrtab growth: one name of 5000 chars (larger than block growth)
    bn = "L" * 5000
    st4, of4 = strtab_names([bn])
    case("name_5000", coff([dbg(("off", of4[0]), 2)], strtab=st4))
    bn = "M" * 1030
    st5, of5 = strtab_names([bn, bn + "x"])
    case("name_1030", coff([dbg(("off", of5[0]), 2), dbg(("off", of5[1]), 2)], strtab=st5))
    for L in (300, 400, 500, 509, 510, 511, 512, 513, 600, 1000, 1010, 1019, 1020, 1021, 1022, 1023, 1024,
              1025, 1100):
        nm = "N" * L
        stx, ofx = strtab_names([nm])
        case("name_%d" % L, coff([dbg(("off", ofx[0]), 2)], strtab=stx))
    # missing input file
    case("no_cx_cld", None)
    # unwritable output: read-only o.elf
    case("readonly_elf", coff([dbg("d", 2)], strtab=b"\0"), files={"o.elf": b"old"}, opts="ro")
    case("existing_elf", coff([dbg("d", 2)], strtab=b"\0"), files={"o.elf": b"x" * 5000})
    case("elf_is_dir", coff([dbg("d", 2)], strtab=b"\0"), opts="dir")
    case("elf_name_long", coff([dbg("d", 2)], strtab=b"\0"), opts="longname")


LINK_IN = "elf12.cln"


def runside(exe, work, case_opts, args):
    env = dict(os.environ, SOURCE_DATE_EPOCH="931953600")
    r = subprocess.run([exe] + args, cwd=work, capture_output=True, input=b"", env=env)
    return r


def main():
    keep = "-k" in sys.argv
    prepare()
    build_cases()
    bad = 0
    for name, data, files, opts in CASES:
        res = []
        for exe in (ORIG_X, NEW_X):
            w = tempfile.mkdtemp(prefix="elfx_")
            shutil.copy(os.path.join(HERE, LINK_IN), w)
            if data is not None:
                open(os.path.join(w, "cx.cld"), "wb").write(data)
            for f, c in files.items():
                open(os.path.join(w, f), "wb").write(c)
            args = ["-q", "-c", "-bo.cld", LINK_IN]
            if opts == "ro":
                os.chmod(os.path.join(w, "o.elf"), 0o444)
            if opts == "dir":
                os.mkdir(os.path.join(w, "o.elf"))
            if opts == "longname":
                args = ["-q", "-c", "-b" + "n" * 200 + ".cld", LINK_IN]
            r = runside(exe, w, opts, args)
            fs = {}
            for f in sorted(os.listdir(w)):
                p = os.path.join(w, f)
                if os.path.isfile(p):
                    fs[f] = open(p, "rb").read()
                else:
                    fs[f] = b"<dir>"
            res.append((r.returncode, r.stdout, r.stderr, fs, w))
        (rc1, o1, e1, f1, w1), (rc2, o2, e2, f2, w2) = res
        norm = lambda b: b.replace(b"dsplnk_x.exe", b"X").replace(b"DSPLNK_X.EXE", b"X")
        ok = rc1 == rc2 and o1 == o2 and e1 == e2 and f1 == f2
        elf = f1.get("o.elf")
        info = "elf=%s rc=%d" % ("none" if elf is None else len(elf), rc1)
        msg = (e1 + o1).decode(errors="replace").strip().replace("\r", "").replace("\n", " | ")[:90]
        if ok:
            print("OK  %-28s %s %s" % (name, info, msg))
        else:
            bad += 1
            print("DIFF %-28s orig rc=%d new rc=%d" % (name, rc1, rc2))
            if o1 != o2:
                print("  stdout:", o1[:200], o2[:200])
            if e1 != e2:
                print("  stderr:", e1[:300], e2[:300])
            for f in sorted(set(f1) | set(f2)):
                if f1.get(f) != f2.get(f):
                    print("  file differs:", f, len(f1.get(f) or b""), len(f2.get(f) or b""))
        if not keep:
            for w in (w1, w2):
                for root, ds, fl in os.walk(w):
                    for f in fl:
                        try:
                            os.chmod(os.path.join(root, f), 0o666)
                        except OSError:
                            pass
                shutil.rmtree(w, ignore_errors=True)
    print("cases: %d  failures: %d" % (len(CASES), bad))
    sys.exit(bad)


main()
