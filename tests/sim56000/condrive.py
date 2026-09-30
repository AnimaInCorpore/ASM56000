"""Drive the original console-mode SIM56000.EXE (it uses ReadConsoleInput and a private
console screen buffer, so stdin redirection does not work): start it in a new console,
inject the script's lines as key events, wait for exit.  Windows only (ctypes).

usage: condrive.py [--screen] EXE SCRIPT [workdir]
  --screen   also print the console screen after each line (debugging aid)
The scripts should open a session log (LOG S file ... LOG OFF, QUIT); the log file is
the byte-exact oracle for the transcript."""
import ctypes, subprocess, sys, time, os
from ctypes import wintypes as W
k = ctypes.WinDLL("kernel32", use_last_error=True)
class COORD(ctypes.Structure): _fields_=[("X",ctypes.c_short),("Y",ctypes.c_short)]
class SMALL_RECT(ctypes.Structure): _fields_=[("L",ctypes.c_short),("T",ctypes.c_short),("R",ctypes.c_short),("B",ctypes.c_short)]
class CSBI(ctypes.Structure): _fields_=[("size",COORD),("cur",COORD),("attr",W.WORD),("win",SMALL_RECT),("max",COORD)]
class KEY(ctypes.Structure):
    _fields_=[("bKeyDown",W.BOOL),("rep",W.WORD),("vk",W.WORD),("sc",W.WORD),("ch",W.WCHAR),("ctl",W.DWORD)]
class REC(ctypes.Structure):
    class U(ctypes.Union): _fields_=[("k",KEY)]
    _anonymous_=("u",); _fields_=[("type",W.WORD),("u",U)]
k.CreateFileW.restype = W.HANDLE
INV = W.HANDLE(-1).value

def open_con(name):
    h = k.CreateFileW(name, 0xC0000000, 3, None, 3, 0, None)
    if h == INV or h is None: raise OSError(ctypes.get_last_error())
    return h

def send(hin, text):
    recs=[]
    for c in text:
        for d in (1,0):
            r=REC(); r.type=1; r.k.bKeyDown=d; r.k.rep=1
            r.k.vk = 0x0D if c=="\n" else 0
            r.k.ch = "\r" if c=="\n" else c
            recs.append(r)
    arr=(REC*len(recs))(*recs); n=W.DWORD()
    k.WriteConsoleInputW(hin, arr, len(recs), ctypes.byref(n))

def screen(hout):
    i=CSBI(); k.GetConsoleScreenBufferInfo(hout, ctypes.byref(i))
    w,h=i.size.X,i.size.Y
    buf=ctypes.create_unicode_buffer(w*h); n=W.DWORD()
    k.ReadConsoleOutputCharacterW(hout, buf, w*h, COORD(0,0), ctypes.byref(n))
    s=buf.value
    return "\n".join(s[y*w:(y+1)*w].rstrip() for y in range(h)).rstrip()

def run_session(exe, lines, cwd, show=False, per_line=0.25, timeout=60):
    p = subprocess.Popen([exe], cwd=cwd, creationflags=0x10)   # CREATE_NEW_CONSOLE
    time.sleep(1.0)
    k.FreeConsole()
    if not k.AttachConsole(p.pid): raise OSError(ctypes.get_last_error())
    hin=open_con("CONIN$"); hout=open_con("CONOUT$")
    t0=time.time()
    for line in lines:
        send(hin, line+"\n")
        t1=time.time()
        while time.time()-t1 < per_line and p.poll() is None: time.sleep(0.02)
        if show: print("> "+line); print(screen(hout)); print("=====")
        if p.poll() is not None or time.time()-t0 > timeout: break
    while p.poll() is None and time.time()-t0 < timeout: time.sleep(0.05)
    rc = p.poll()
    if rc is None: p.kill(); rc = -1
    k.FreeConsole()
    return rc

if __name__ == "__main__":
    a = sys.argv[1:]; show = False
    if a and a[0] == "--screen": show = True; a = a[1:]
    cwd = a[2] if len(a) > 2 else os.getcwd()
    print("rc=%d" % run_session(os.path.abspath(a[0]), open(a[1]).read().splitlines(), cwd, show))
