"""abip_try.py [--port] EXPR...   patch abip_base.cln with the given relocation
texts, link with the original (or, with --port, the rebuilt tool from
$CLAS_BUILD) and print stdout/stderr/exit status and the linked words."""
import os, subprocess, sys, tempfile, shutil
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from abip_coff import Obj
HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(HERE))

def link(texts, port=False, extra=()):
    o = Obj(open(os.path.join(HERE, "abip_base.cln"), "rb").read())
    o.set_texts(texts)
    w = tempfile.mkdtemp(prefix="abip_")
    open(os.path.join(w, "x.cln"), "wb").write(o.bytes())
    if port:
        exe = os.path.join(os.environ.get("CLAS_BUILD", os.path.join(ROOT, "build")), "dsplnk.exe")
    else:
        exe = os.path.join(ROOT, "re", "bin_ft", "DSPLNK.EXE")
    env = dict(os.environ, SOURCE_DATE_EPOCH="931953600") if port else None
    r = subprocess.run([exe, "-q", "-bo.cld"] + list(extra) + ["x.cln"], cwd=w, capture_output=True, env=env)
    return r, w

if __name__ == "__main__":
    args = sys.argv[1:]
    port = False
    if args and args[0] == "--port":
        port = True; args = args[1:]
    r, w = link(args, port)
    print("exit", r.returncode)
    print("stdout", r.stdout.decode("latin-1"))
    print("stderr", r.stderr.decode("latin-1"))
    p = os.path.join(w, "o.cld")
    if os.path.exists(p):
        print(open(p, "rb").read().hex())
    shutil.rmtree(w, ignore_errors=True)

def cld_words(path):
    """the words of the first linked section that has data"""
    import struct
    d = open(path, "rb").read()
    be = lambda o: struct.unpack(">L", d[o:o + 4])[0]
    nscns = be(4); opt = be(20)
    o = 28 + opt
    for i in range(nscns):
        s = o + 52 * i
        size = be(s + 8 + 16); ptr = be(s + 8 + 20)
        if size and ptr:
            return [be(ptr + 4 * k) for k in range(size)]
    return []
