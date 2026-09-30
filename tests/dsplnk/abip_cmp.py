r"""abip_cmp.py [-b N] FILE...   compare original and rebuilt DSPLNK on relocation
texts (one text per line of FILE; '#' lines and empty lines skipped; C escapes
\n \t \xNN understood).  Each text is linked alone, then all texts in batches
of N (default 50, one file per batch).  Needs CLAS_BUILD (rebuilt dsplnk.exe)."""
import os, sys, subprocess, shutil
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import abip_try

def unesc(s):
    return s.encode('latin-1').decode('unicode_escape').encode('latin-1')

def result(texts, port):
    r, w = abip_try.link(texts, port)
    p = os.path.join(w, 'o.cld')
    data = open(p, 'rb').read() if os.path.exists(p) else None
    shutil.rmtree(w, ignore_errors=True)
    out = r.stdout.replace(b'\r\n', b'\n')
    err = r.stderr.replace(b'\r\n', b'\n')
    return (r.returncode, out, err, data)

def main():
    a = sys.argv[1:]
    bs = 50
    if a and a[0] == '-b':
        bs = int(a[1]); a = a[2:]
    texts = []
    for f in a:
        for line in open(f, encoding='latin-1'):
            line = line.rstrip('\n')
            if line == '' or line.startswith('#'):
                continue
            texts.append(unesc(line))
    bad = 0
    for t in texts:
        o = result([t], False); n = result([t], True)
        if o != n:
            bad += 1
            print('DIFF single', repr(t)); print('  orig', o[0], o[1][:200], o[2][:200], None if o[3] is None else abip_try.__name__ and len(o[3]))
            print('  port', n[0], n[1][:200], n[2][:200], None if n[3] is None else len(n[3]))
    for i in range(0, len(texts), bs):
        b = texts[i:i + bs]
        if result(b, False) != result(b, True):
            bad += 1
            print('DIFF batch', i)
    print('texts', len(texts), 'differences', bad)
    return bad

sys.exit(main())
