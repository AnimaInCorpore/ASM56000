r"""DSPLIB regression tests: original (time()-patched re/bin_ft/DSPLIB.EXE)
against build/dsplib.exe.

Unlike tests/compare.py this runner
  - starts both programs with the same argv[0] ("dsplib"), because DSPLIB
    prints its program name (and argv[0] itself in getopt messages);
  - copies the whole fix/ tree (libraries in a subdirectory, too);
  - reports files that were removed as well as written;
  - always uses the fixed clock (bin_ft + SOURCE_DATE_EPOCH), since DSPLIB
    stamps new members with the current time.
Temporary file names (lb + letter + digits) differ by design (the original
uses its process id); files matching ^lb[a-z]\d+$ are ignored and such
names in messages are replaced by "lbTEMP" before comparing.

usage: python run.py [-v] [name-filter]
"""
import os, re, sys, shutil, subprocess, tempfile, filecmp

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
ORIG = os.path.join(ROOT, "re", "bin_ft", "DSPLIB.EXE")
NEW = os.path.join(ROOT, "build", "dsplib.exe")
FIX = os.path.join(HERE, "fix")
FIXED_TIME = "931953600"
TMPNAME = re.compile(r"^lb[a-z]\d+$", re.I)

# (name, args, stdin or None)
CASES = [
    # usage / options
    ("noargs-eof", [], b""),
    ("usage-q", ["-q"], None),
    ("version", ["-v"], None),
    ("version-q", ["-q", "-v"], None),
    ("help-opt", ["-?"], None),
    ("unknown-opt", ["-z", "lib12"], None),
    ("f-missing-arg", ["-q", "-f"], None),
    ("lib-missing", ["-q", "-l"], None),
    ("dashdash", ["-q", "--", "lib12"], None),
    ("e-illegal", ["-ez", "x.err", "-l", "lib12"], None),
    ("e-syntax", ["-eww", "x.err", "-l", "lib12"], None),
    ("e-noarg", ["-ew", "-l", "lib12"], None),
    ("e-last", ["-ew"], None),
    ("e-plain", ["-e"], None),
    ("ew-list", ["-ew", "err.txt", "-x", "lib12", "nosuch.cln"], None),
    ("ea-usage", ["-ea", "err.txt", "-z"], None),
    ("ew-openfail", ["-ew", "nodir\\err.txt", "-l", "lib12"], None),
    ("EW-upper", ["-EW", "err.txt", "-Q", "-L", "lib12"], None),
    # list
    ("list-default", ["lib12"], None),
    ("list-l", ["-l", "lib12"], None),
    ("list-q", ["-q", "-l", "lib123.clb"], None),
    ("list-named", ["-q", "-l", "lib123", "mod3.cln", "nosuch", "sub\\mod1.cln"], None),
    ("list-old", ["-q", "-l", "old"], None),
    ("list-empty", ["-q", "-l", "empty"], None),
    ("list-bad", ["-q", "-l", "bad"], None),
    ("list-trunc", ["-q", "-l", "trunc"], None),
    ("list-short", ["-q", "-l", "short"], None),
    ("list-lf", ["-q", "-l", "lf"], None),
    ("list-nolib", ["-q", "-l", "nolib"], None),
    ("list-upper", ["-q", "-l", "LIB12"], None),
    ("list-ext", ["-q", "-l", "lib12.xyz"], None),
    ("list-sub", ["-q", "-l", "sub\\sublib"], None),
    ("list-clustered", ["-ql", "lib12"], None),
    # create
    ("create", ["-q", "-c", "new", "mod1.cln", "mod2.cln", "mod3.cln"], None),
    ("create-upper", ["-q", "-c", "NEW", "MOD4.CLN"], None),
    ("create-sub", ["-q", "-c", "sub\\new", "sub\\mod3.cln", "mod1.cln"], None),
    ("create-empty", ["-q", "-c", "new"], None),
    ("create-exists", ["-q", "-c", "lib12", "mod3.cln"], None),
    ("create-dup", ["-q", "-c", "new", "mod1.cln", "mod2.cln", "mod1.cln"], None),
    ("create-missing", ["-q", "-c", "new", "mod1.cln", "nosuch.cln", "mod2.cln"], None),
    ("create-vms", ["-q", "-c", "new", "mod1.cln;3"], None),
    ("create-f", ["-q", "-c", "-f", "cmds.txt", "new"], None),
    ("create-f2", ["-q", "-f", "cmds2.txt", "-c", "new", "mod1.cln"], None),
    ("create-f-missing", ["-q", "-c", "-f", "nocmds.txt", "new"], None),
    # add
    ("add", ["-q", "-a", "lib12", "mod3.cln"], None),
    ("add-exists", ["-q", "-a", "lib12", "mod1.cln"], None),
    ("add-nonames", ["-q", "-a", "lib12"], None),
    ("add-nolib", ["-q", "-a", "nolib", "mod1.cln"], None),
    ("add-old", ["-q", "-a", "old", "mod3.cln"], None),
    ("add-sub", ["-q", "-a", "lib12", "sub\\mod3.cln"], None),
    # replace / update
    ("replace", ["-q", "-r", "lib123", "mod2.cln"], None),
    ("replace-new", ["-q", "-r", "lib123", "sub\\mod2.cln"], None),
    ("update-new", ["-q", "lib123", "sub\\mod2.cln", "mod1.cln"], None),
    ("replace-missing", ["-q", "-r", "lib12", "mod3.cln"], None),
    ("replace-upper", ["-q", "-r", "lib12", "MOD1.CLN"], None),
    ("replace-nonames", ["-q", "-r", "lib12"], None),
    ("update", ["-q", "-u", "lib12", "mod2.cln", "mod3.cln"], None),
    ("update-default", ["lib12", "mod3.cln"], None),
    ("update-nonames", ["-q", "-u", "lib12"], None),
    ("update-q-only", ["-q", "lib12"], None),
    ("update-empty-lib", ["-q", "-u", "empty"], None),
    ("update-old", ["-q", "-u", "old", "mod2.cln"], None),
    ("update-old-noop", ["-q", "-u", "old", "mod3.cln"], None),
    ("update-upper", ["-q", "-u", "lib12", "MOD4.CLN"], None),
    ("update-bad", ["-q", "-u", "bad", "mod1.cln"], None),
    ("update-short", ["-q", "-u", "short", "mod3.cln"], None),
    ("update-nolib", ["-q", "-u", "nolib", "mod1.cln"], None),
    # delete
    ("delete", ["-q", "-d", "lib123", "mod2.cln"], None),
    ("delete-all", ["-q", "-d", "lib12", "mod1.cln", "mod2.cln"], None),
    ("delete-missing", ["-q", "-d", "lib12", "mod3.cln"], None),
    ("delete-nonames", ["-q", "-d", "lib12"], None),
    ("delete-nolib", ["-q", "-d", "nolib", "mod1.cln"], None),
    ("delete-old", ["-q", "-d", "old", "mod1.cln"], None),
    ("delete-dup", ["-q", "-d", "lib12", "mod1.cln", "mod1.cln"], None),
    # extract
    ("extract-all", ["-q", "-x", "lib123"], None),
    ("extract-other", ["-q", "-x", "other"], None),
    ("extract-other-named", ["-x", "other", "b.cln", "sub\\a.cln", "c.cln"], None),
    ("extract-dir", ["-q", "-x", "sub\\sublib"], None),
    ("extract-named", ["-q", "-x", "lib123", "mod2.cln", "nosuch.cln"], None),
    ("extract-old", ["-q", "-x", "old"], None),
    ("extract-nolib", ["-q", "-x", "nolib", "mod1.cln"], None),
    ("extract-nolib-f", ["-q", "-x", "-f", "cmds.txt", "nolib"], None),
    ("extract-f", ["-q", "-f", "cmds.txt", "-x", "lib123"], None),
    ("extract-short", ["-q", "-x", "short"], None),
    ("extract-optarg", ["-q", "-xlib12", "lib123"], None),
    ("extract-eats-lib", ["-q", "-x", "lib12", "-l"], None),
    ("extract-bad", ["-q", "-x", "bad"], None),
    # members larger than the 8 KB copy buffer
    ("big-create", ["-q", "-c", "new", "big.cln", "mod3.cln"], None),
    ("big-extract", ["-q", "-x", "biglib", "big.cln"], None),
    ("big-delete", ["-q", "-d", "biglib", "mod1.cln"], None),
    ("big-update", ["-q", "-u", "biglib", "sub\\mod2.cln", "mod3.cln"], None),
    ("big-list", ["-q", "-l", "biglib"], None),
    # interactive
    ("i-help", [], b"help\n?\nh\nversion\nquit\n"),
    ("i-list", [], b"list lib12\nl lib123 mod2.cln nosuch\nLIST old\n"),
    ("i-cmds", [], b"foo\ne lib12\nex lib12\nxtract\nlist\n  \n\nadd\nq\nlist lib12\n"),
    ("i-exit", [], b"exi\nlist lib12\n"),
    ("i-create", [], b"create new MOD1.CLN mod2.cln\nlist new\n"),
    ("i-create-exists", [], b"create lib12 mod3.cln\nlist lib12\n"),
    ("i-errors", [], b"list nolib\nadd lib12\ndelete lib12\nreplace lib12 mod3.cln\nlist lib12\n"),
    ("i-add-dup", [], b"add lib12 mod3.cln mod3.cln\nlist lib12\n"),
    ("i-update", [], b"update lib12 mod3.cln\nupdate lib12 mod1.cln\nlist lib12\n"),
    ("i-delete", [], b"delete lib123 mod1.cln mod3.cln\nlist lib123\n"),
    ("i-extract", [], b"extract lib123 mod1.cln\nx lib12\n"),
    ("i-update-nonames", [], b"update lib12\nlist lib12\n"),
    ("i-update-empty", [], b"update empty\nlist empty\n"),
    ("i-sub", [], b"create sub\\new sub\\mod3.cln\nlist sub\\new\ncreate new2 mod1.cln\n"),
    ("i-noeol", [], b"list lib12"),
    ("i-bad", [], b"list bad\nlist lib12\n"),
    ("i-extract-old", [], b"extract old mod2.cln\n"),
    ("i-extract-other", [], b"extract other B.CLN\nx other\n"),
    ("i-replace", [], b"replace lib123 sub\\mod2.cln\nlist lib123\n"),
    ("i-fatal-then-ok", [], b"list bad\ncreate lib12 x\nlist nolib\ndelete lib123 mod2.cln\nlist lib123\n"),
    ("i-add-upper", [], b"add lib12 MOD4.CLN\nlist lib12\n"),
    ("i-help-lib", [], b"help sub\\x\ncreate new mod1.cln\n"),
    ("i-long", [], b"list " + b"a" * 400 + b"\nlist lib12\n"),
    # the stream left open by a failed "create" makes the later rename fail
    # (Windows); the message names the temporary file, which differs
    ("i-create-leak", [], b"create lib12 mod3.cln\nadd lib12 mod3.cln\nlist lib12\n"),
]

def snapshot(root):
    out = {}
    for d, _, files in os.walk(root):
        for f in files:
            p = os.path.join(d, f)
            out[os.path.relpath(p, root).lower()] = p
    return out

def run(exe, args, stdin, env):
    work = tempfile.mkdtemp(prefix="dsplib_")
    shutil.rmtree(work)
    shutil.copytree(FIX, work)
    r = subprocess.run(["dsplib"] + args, executable=exe, cwd=work, capture_output=True,
                       input=stdin if stdin is not None else b"", env=env)
    before = snapshot(FIX)
    after = snapshot(work)
    changed = {}
    for k, p in after.items():
        if TMPNAME.match(os.path.basename(k)):
            continue
        if k not in before or not filecmp.cmp(before[k], p, shallow=False):
            changed[k] = p
    removed = sorted(k for k in before if k not in after)
    return r, changed, removed, work

def main():
    verbose = "-v" in sys.argv
    filt = [a for a in sys.argv[1:] if a != "-v"]
    env_new = dict(os.environ, SOURCE_DATE_EPOCH=FIXED_TIME)
    env_orig = dict(os.environ)
    env_orig.pop("SOURCE_DATE_EPOCH", None)
    bad = 0
    for name, args, stdin in CASES:
        if filt and not any(f in name for f in filt):
            continue
        ro, co, xo, wo = run(ORIG, args, stdin, env_orig)
        rn, cn, xn, wn = run(NEW, args, stdin, env_new)
        msgs = []
        if ro.returncode != rn.returncode:
            msgs.append("exit status: orig %d new %d" % (ro.returncode, rn.returncode))
        for what, a, b in (("stdout", ro.stdout, rn.stdout), ("stderr", ro.stderr, rn.stderr)):
            # temporary file names in messages differ by design
            a = re.sub(rb"\blb[a-z]\d{5}\b", b"lbTEMP", a)
            b = re.sub(rb"\blb[a-z]\d{5}\b", b"lbTEMP", b)
            if a != b:
                msgs.append("%s differs:\n--- orig\n%s--- new\n%s" % (what, a.decode("latin-1"), b.decode("latin-1")))
        if xo != xn:
            msgs.append("removed files: orig %s new %s" % (xo, xn))
        for f in sorted(set(co) | set(cn)):
            if f not in co or f not in cn:
                msgs.append("file %s written by %s only" % (f, "orig" if f in co else "new"))
            elif not filecmp.cmp(co[f], cn[f], shallow=False):
                msgs.append("file %s differs (%s, %s)" % (f, wo, wn))
        if msgs:
            bad += 1
            print("FAIL %s %s" % (name, " ".join(args)))
            for m in msgs:
                print("  " + m)
        else:
            print("OK   %-18s rc=%d files=%s%s" % (name, ro.returncode, ",".join(sorted(co)) or "-",
                                                    (" removed=" + ",".join(xo)) if xo else ""))
            if verbose:
                sys.stdout.write(ro.stdout.decode("latin-1") + ro.stderr.decode("latin-1"))
            shutil.rmtree(wo, ignore_errors=True)
            shutil.rmtree(wn, ignore_errors=True)
    print("%d case(s) failed" % bad if bad else "all OK")
    sys.exit(1 if bad else 0)

if __name__ == "__main__":
    main()
