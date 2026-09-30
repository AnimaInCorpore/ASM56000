"""Scripted-session tests for SIM56000.

  simtest.py gold  NAME...   run the ORIGINAL (console driven, Windows only) on NAME.sim and
                             store every file it writes into golden/NAME/ (+ rc)
  simtest.py check NAME...   run the REBUILT build/sim56000[.exe] with the script on stdin
                             and compare the written files with golden/NAME/
Scripts must open a session log (LOG S file, ... LOG OFF) - the log is the transcript oracle.
With no NAME all *.sim files are used.  Prints OK / DIFF per session; exit status 1 on any DIFF."""
import os, sys, shutil, subprocess, tempfile, filecmp, glob
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))
ORIG = os.path.join(ROOT, "re", "bin", "SIM56000.EXE")
NEW = os.path.join(ROOT, "build", "sim56000.exe")
if not os.path.exists(NEW): NEW = os.path.join(ROOT, "build", "sim56000")

def scratch(name):
    w = tempfile.mkdtemp(prefix="sim_")
    for f in os.listdir(HERE):
        p = os.path.join(HERE, f)
        if os.path.isfile(p) and not f.endswith((".sim", ".py", ".sh")): shutil.copy2(p, w)
    before = {f: open(os.path.join(w, f), "rb").read() for f in os.listdir(w)}
    return w, before

def written(w, before):
    out = {}
    for f in sorted(os.listdir(w)):
        d = open(os.path.join(w, f), "rb").read()
        if before.get(f) != d: out[f] = d
    return out

def gold(name):
    sys.path.insert(0, HERE)
    import condrive
    w, before = scratch(name)
    rc = condrive.run_session(ORIG, open(os.path.join(HERE, name + ".sim")).read().splitlines(), w)
    g = os.path.join(HERE, "golden", name); shutil.rmtree(g, ignore_errors=True); os.makedirs(g)
    for f, d in written(w, before).items(): open(os.path.join(g, f), "wb").write(d)
    open(os.path.join(g, "_rc"), "w").write(str(rc))
    shutil.rmtree(w, ignore_errors=True)
    print("gold %s rc=%d" % (name, rc))

def check(name):
    w, before = scratch(name)
    r = subprocess.run([NEW], cwd=w, input=open(os.path.join(HERE, name + ".sim"), "rb").read(),
                       capture_output=True, timeout=120)
    got = written(w, before); g = os.path.join(HERE, "golden", name)
    want = {f: open(os.path.join(g, f), "rb").read() for f in os.listdir(g) if f != "_rc"}
    rc = int(open(os.path.join(g, "_rc")).read())
    bad = []
    if r.returncode != rc: bad.append("rc %d != %d" % (r.returncode, rc))
    for f in sorted(set(got) | set(want)):
        if got.get(f) != want.get(f): bad.append("file differs: " + f)
    shutil.rmtree(w, ignore_errors=True)
    print(("OK   " if not bad else "DIFF ") + name + ("" if not bad else "  " + "; ".join(bad)))
    return not bad

if __name__ == "__main__":
    mode, names = sys.argv[1], sys.argv[2:]
    if not names: names = [os.path.basename(f)[:-4] for f in sorted(glob.glob(os.path.join(HERE, "*.sim")))]
    if mode == "gold":
        for n in names: gold(n)
    else:
        if not os.path.exists(NEW): print("SKIP: no rebuilt sim56000 in build/"); sys.exit(0)
        sys.exit(0 if all([check(n) for n in names]) else 1)
