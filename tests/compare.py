r"""Run an original CLAS56 tool and its rebuilt counterpart on the same input
and compare exit status, stdout, stderr and every file they write.

usage: compare.py [--stdin FILE] [--ignore REGEX] <tool> [args...]
   e.g. compare.py cldinfo t1.cld
        compare.py asm56000 -a -b -l t1.asm
        compare.py --stdin cmds.txt dsplib
        compare.py --ignore "^s[0-9a-z]+\.?$" strip t2.cln

--stdin FILE    feed FILE (relative to the current directory) to both tools
--ignore REGEX  ignore written files whose names match (e.g. tmpnam names);
                may be given more than once
--time          fixed clock: run the time()-patched originals in re/bin_ft
                (see re/scripts/patchtime.py) and give the rebuilt tool
                SOURCE_DATE_EPOCH=931953600

Each side runs in its own scratch copy of the current directory, so output
files do not clash.  Exit status 0 means identical behaviour.
"""
import os, re, sys, shutil, subprocess, tempfile, filecmp

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ORIG = os.path.join(ROOT, "re", "bin")
NEW = os.path.join(ROOT, "build")

FIXED_TIME = "931953600"

def run(exe, args, src, stdin=None, env=None):
    work = tempfile.mkdtemp(prefix="cmp_")
    for f in os.listdir(src):
        p = os.path.join(src, f)
        if os.path.isfile(p):
            shutil.copy2(p, work)
    before = set(os.listdir(work))
    r = subprocess.run([exe] + args, cwd=work, capture_output=True,
                       input=stdin if stdin is not None else b"", env=env)
    files = {f: os.path.join(work, f) for f in os.listdir(work)
             if f not in before or not filecmp.cmp(os.path.join(src, f), os.path.join(work, f), shallow=False)}
    return r, files, work

def main():
    argv = sys.argv[1:]
    stdin, ignore, orig, env = None, [], ORIG, None
    while argv and argv[0] in ("--stdin", "--ignore", "--time"):
        if argv[0] == "--time":
            orig = ORIG + "_ft"
            env = dict(os.environ, SOURCE_DATE_EPOCH=FIXED_TIME)
            argv = argv[1:]
            continue
        if argv[0] == "--stdin":
            stdin = open(argv[1], "rb").read()
        else:
            ignore.append(re.compile(argv[1], re.I))
        argv = argv[2:]
    tool, args = argv[0].lower(), argv[1:]
    src = os.getcwd()
    ro, fo, wo = run(os.path.join(orig, tool.upper() + ".EXE"), args, src, stdin)
    rn, fn, wn = run(os.path.join(NEW, tool + ".exe"), args, src, stdin, env)
    fo = {k: v for k, v in fo.items() if not any(r.search(k) for r in ignore)}
    fn = {k: v for k, v in fn.items() if not any(r.search(k) for r in ignore)}
    ok = True
    if ro.returncode != rn.returncode:
        print("exit status: orig %d new %d" % (ro.returncode, rn.returncode)); ok = False
    notes = []
    for what, a, b in (("stdout", ro.stdout, rn.stdout), ("stderr", ro.stderr, rn.stderr)):
        if a != b and what == "stderr" and sorted(a.splitlines()) == sorted(b.splitlines()):
            # MSVC buffers stderr when it is a pipe while perror() writes
            # directly, so the original's lines come out of order there
            notes.append("stderr line order differs (MSVC pipe buffering)")
        elif a != b:
            ok = False
            print("%s differs:\n--- orig\n%s\n--- new\n%s" % (what, a.decode("latin-1"), b.decode("latin-1")))
    names = {f.lower() for f in fo} | {f.lower() for f in fn}
    fo = {k.lower(): v for k, v in fo.items()}
    fn = {k.lower(): v for k, v in fn.items()}
    for f in sorted(names):
        if f not in fo or f not in fn:
            print("file %s written by %s only" % (f, "orig" if f in fo else "new")); ok = False
        elif not filecmp.cmp(fo[f], fn[f], shallow=False):
            print("file %s differs (kept in %s and %s)" % (f, wo, wn)); ok = False
    if ok:
        shutil.rmtree(wo, ignore_errors=True); shutil.rmtree(wn, ignore_errors=True)
        print("OK %s %s%s" % (tool, " ".join(args), "".join("  [%s]" % n for n in notes)))
    sys.exit(0 if ok else 1)

if __name__ == "__main__":
    main()
