"""Run all srec comparisons (original SREC.EXE against build/srec.exe).

Run from tests/srec after assembling the inputs:
    ..\\..\\re\\bin\\ASM56000.EXE -a -b t1.asm   (same for t2.asm, t3.asm)
    ..\\..\\re\\bin\\CLDLOD.EXE t2.cld > t2.lod     (same for t3)
    python mkcoff.py
    python run_tests.py

Each case goes through cmpname.py (compare.py with both programs started
as "SREC.EXE", see there).  KNOWN lists cases where the original has
undefined behaviour (heap overruns) and the outputs are not expected to
agree.
"""
import os, subprocess, sys

HERE = os.path.dirname(os.path.abspath(__file__))

OPTS = ["", "-r", "-m", "-s", "-b", "-w", "-l", "-l -b", "-x", "-x -u", "-u",
        "-c", "-a 2", "-a 3", "-a 4", "-t 2", "-t 3", "-t 4", "-o p:ff00",
        "-o y:10 -o L:fff00", "-p 96000", "-b -s", "-b -m", "-x -m",
        "-x -s -u", "-c -s", "-c -b", "-m -r -u", "-l -b -s", "-l -b -m",
        "-x -b -a 4", "-t 2 -m", "-t 4 -b -c"]

MACH = ["m96000", "m56100", "m56300", "m56800", "m56600", "m100", "m56700",
        "p56100", "e56600", "e56300", "dmem", "s96000", "blk3", "lodd",
        "noopt"]
MACHOPTS = ["", "-m", "-s", "-b", "-x", "-x -u", "-c", "-r -l -b",
            "-a 4 -t 2", "-o e:10 -o d:20 -b", "-m -x -t 4"]

BAD = ["badmagic", "badmem", "badmem2", "badmem3", "reloc", "nosec",
       "manysec", "hdronly", "short", "trunc", "badptr", "junk"]

LODS = ["l1", "l2", "l3", "l4", "l5", "l6", "l7", "l8", "l9", "l9b", "l10",
        "l11", "l12", "l13", "l13b", "l14", "l14b", "l14c", "l14d", "l14e",
        "l14f", "l15", "l16", "l17", "l18", "l19", "l20", "l21", "l22",
        "l23", "l24", "l25", "l26", "l27", "l28"]
LODOPTS = ["", "-x", "-x -u", "-x -m", "-x -s", "-m", "-s", "-b", "-l -b",
           "-c", "-r -u", "-a 3 -t 4", "-o x:100 -o P:fffff"]

MISC = [
    "t2.cld", "-k", "-Q", "-q", "",
    "-q t2.txt", "-q t2noext", "-q junk.xyz", "-q nodata.xyz", "-q t2",
    "-q t2.x", "-q nofile.lod", "-q nofile", "-q t2.lod nofile",
    "-q t2.cld t3", "-q t2.cld t3.x", "-q t1.cld t2.lod t3.cld",
    "-q -s t1.cld t2.lod t3.cld", "-q -m t1.cld t2.cld",
    "-q -s t2.cld t2.cld t2.cld", "-q t2.lod t2.lod", "-q l8.lod t2.cld",
    "-q t2.cld l17.lod", "-q e56600.cld l11.lod", "-q t1.cld t2.cld",
    "-q -s t1.cld t2.cld", "-q t2.lod t1.cld",
    "-q -p 56300 t2.cld", "-q -p 99 t2.cld", "-q -p5616 t2.cld",
    "-q -p 56800 t2.cld", "-q -p 56100 t2.cld", "-q -p 100 t2.cld",
    "-q -p 56700 t2.cld", "-q -p 56600 t2.cld", "-q -p 56000 e56600.cld",
    "-q -a 1 t2.cld", "-q -a 5 t2.cld", "-q -t 1 t2.cld", "-q -t 9 t2.cld",
    "-q -a x t2.cld", "-q -t x t2.cld", "-q -o z:1 t2.cld",
    "-q -o p1 t2.cld", "-q -o p:zz t2.cld", "-q -o p: t2.cld",
    "-q -s -m t2.cld", "-q -c -m t2.cld", "-q -b -w t2.cld",
    "-q -? t2.cld", "-q -W t2.cld", "-q -Q t2.cld", "-qx -R t2.cld",
    "-q -- t2.cld", "-q -", "-q -a", "-q -p", "-q -o", "-a", "-o",
    "-q t2.cld -q", "-q -x -l -b t3.cld", "-q -l -x t3.lod",
    "-q ./t2", "-q ./t2.cld", "-q .\\t2", "-q .\\t2.cld", "-q T2.LOD",
    "-q T2.CLD", "-q t2.Cld",
]

STDIN = [("t2.lod", "-q -"), ("t3.lod", "-q -"), ("t2.cld", "-q -"),
         ("l1.lod", "-q -"), ("t2.lod", "-q t1.cld -")]

KNOWN = {
    # 56600 -m: E memory / 0x4000 sections overrun the S-record structures
    "-q -m e56600.cld", "-q -m -x -t 4 e56600.cld",
    # address token of byte 0xfb: sscanf converts nothing, the original
    # uses an uninitialised variable (here 0; the -o sscanf left it set)
    "-q -o x:100 -o P:fffff l25.lod",
    # stdin after a .lod file: output names from uninitialised memory
    "--stdin t2.lod -q t2.lod -",
}

def cases():
    for f in ("t2.cld", "t2.lod", "t3.cld", "t3.lod"):
        for o in OPTS:
            yield None, "-q %s %s" % (o, f)
    for f in MACH:
        for o in MACHOPTS:
            yield None, "-q %s %s.cld" % (o, f)
    for f in BAD:
        yield None, "-q %s.cld" % f
    for f in LODS:
        for o in LODOPTS:
            yield None, "-q %s %s.lod" % (o, f)
    for a in MISC:
        yield None, a
    for s, a in STDIN:
        yield s, a
    yield "t2.lod", "-q t2.lod -"

def main():
    ok = bad = known = 0
    for stdin, args in cases():
        args = " ".join(args.split())
        cmd = [sys.executable, os.path.join(HERE, "cmpname.py")]
        key = args
        if stdin:
            cmd += ["--stdin", stdin]
            key = "--stdin %s %s" % (stdin, args)
        cmd += ["srec"] + args.split()
        r = subprocess.run(cmd, cwd=HERE, capture_output=True, text=True,
                           errors="replace", timeout=60)
        if r.returncode == 0:
            ok += 1
        elif key in KNOWN:
            known += 1
            print("known difference: %s" % key)
        else:
            bad += 1
            print("FAIL: %s\n%s" % (key, r.stdout))
    print("%d OK, %d known differences, %d failed" % (ok, known, bad))
    sys.exit(1 if bad else 0)

if __name__ == "__main__":
    main()
