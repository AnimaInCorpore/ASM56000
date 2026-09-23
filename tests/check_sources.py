"""Check that every C source under src/ depends only on the ANSI C89 library.

Reports #include of any header that is neither a C89 standard header nor a
project header ("..."), plus // comments and a few C99-only constructs.
Exit status 0 means clean.
"""
import os, re, sys

ANSI = {"assert.h", "ctype.h", "errno.h", "float.h", "limits.h", "locale.h",
        "math.h", "setjmp.h", "signal.h", "stdarg.h", "stddef.h", "stdio.h",
        "stdlib.h", "string.h", "time.h"}
C99 = re.compile(r"\b(long\s+long|_Bool|inline|restrict|snprintf|vsnprintf|"
                 r"uint\d+_t|int\d+_t|intptr_t|__func__)\b")

def strip_strings(line):
    return re.sub(r'"(\\.|[^"\\])*"|\'(\\.|[^\'\\])*\'', '""', line)

root = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "src")
bad = 0
for d, _, files in os.walk(root):
    for f in files:
        if not f.endswith((".c", ".h")):
            continue
        p = os.path.join(d, f)
        incomment = False
        for n, line in enumerate(open(p, encoding="latin-1"), 1):
            m = re.match(r'\s*#\s*include\s*<([^>]+)>', line)
            if m and m.group(1) not in ANSI:
                print("%s:%d: non-ANSI header <%s>" % (p, n, m.group(1))); bad += 1
            code = strip_strings(line)
            # drop /* */ comments, tracking multi-line ones
            out = ""
            i = 0
            while i < len(code):
                if incomment:
                    j = code.find("*/", i)
                    if j < 0:
                        i = len(code)
                    else:
                        incomment = False; i = j + 2
                elif code.startswith("/*", i):
                    incomment = True; i += 2
                else:
                    out += code[i]; i += 1
            if "//" in out:
                print("%s:%d: // comment" % (p, n)); bad += 1
            m = C99.search(out)
            if m:
                print("%s:%d: C99 construct '%s'" % (p, n, m.group(1))); bad += 1
print("%s: %d problem(s)" % ("FAIL" if bad else "OK", bad))
sys.exit(1 if bad else 0)
