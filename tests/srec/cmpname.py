"""compare.py for srec with the same program name on both sides.

SREC prints the name it was started under (argv[0] without directory and
extension) in its error and usage messages, and getopt errors print argv[0]
itself.  compare.py starts the original as ...\\re\\bin\\SREC.EXE and the
rebuilt tool as ...\\build\\srec.exe, so those messages can never agree.
This wrapper starts both as plain "SREC.EXE", found through PATH, and
otherwise behaves exactly like compare.py (same arguments, same output).

usage: python cmpname.py [--stdin FILE] [--ignore REGEX] srec [args...]
"""
import os, sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import compare

_run = compare.run

def run(exe, args, src, stdin=None, env=None):
    d, f = os.path.split(exe)
    old = os.environ.get("PATH", "")
    os.environ["PATH"] = d + os.pathsep + old
    try:
        # the file system is case-insensitive: build\SREC.EXE is srec.exe
        return _run(f.upper(), args, src, stdin, env)
    finally:
        os.environ["PATH"] = old

compare.run = run

if __name__ == "__main__":
    compare.main()
