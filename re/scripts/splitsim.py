"""Split re/out/SIM56000/decomp.c into re/notes... no: re/out/SIM56000/mod/<module>.c
using the address-range table below (module boundaries are approximate; they come from
string clusters in .rdata / call-graph neighbourhood, SIM56000 has no RCS $Id strings).
usage: splitsim.py   -> writes mod/*.c and filemap.txt into re/notes/SIM56000/
"""
import re, os
RE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
# start address, module, evidence
R = [
 (0x401000, "simmain",  "main loop: per-device command dispatch; calls cmdloop 439410"),
 (0x401140, "exec",     "instruction execution cores + per-class statistics (DAT_00505b64 counters)"),
 (0x41c140, "devinit",  "device tables (56000..56012 memory maps, DSPMEM, internal/external memory names), mnemonic/operand tables"),
 (0x424000, "asm",      "inline assembler: 'Unrecognized mnemonic', '* encoding failure' strings"),
 (0x42d000, "asmtab",   "operand/field encoders tail, tables (approx)"),
 (0x434000, "state",    "save/load state file: fprintf/fscanf formats '[breakpoint info]' etc."),
 (0x439000, "cmdloop",  "command line editor and dispatcher (439410), 'assemble','change' keywords"),
 (0x43a000, "macro",    "macro files, 'A file with the same name currently exists'"),
 (0x43b000, "fmt",      "value/number formatting (%-26.24e, $%01lx%04lx%04lx)"),
 (0x43c000, "console",  "Win32 console screen (CreateConsoleScreenBuffer, ReadConsoleInput), paging 'More:'"),
 (0x43e000, "cdbglue",  "C-expression glue: 'Error evaluating C expression', scope"),
 (0x43f000, "dispval",  "register/memory value display"),
 (0x440000, "coffrd",   "COFF/CLD reader: string table, line numbers, section headers, symbols"),
 (0x446000, "symdisp",  "symbol/line display"),
 (0x448000, "iohist",   "history, io file display, pin/port input"),
 (0x44d000, "help",     "help command text and topic table"),
 (0x452000, "run",      "run/step/trace loop: 'Break #%d', 'Illegal Op-Code Encountered'"),
 (0x454000, "profile",  "metrics.log, Code Coverage Report"),
 (0x455000, "source",   "source files, 'C sources not supported', include"),
 (0x456000, "stats",    "dynamic addressing mode breakdown report"),
 (0x457000, "radix",    "number radix output ($%04lx%04lx ...)"),
 (0x458000, "mdisk",    "m_gdisk/m_pdisk memory disk emulation"),
 (0x459000, "expr",     "simulator expression evaluator: 'Expression result must be integer', 'Divide by 0'"),
 (0x45d000, "misc",     "'quit ;on error' etc"),
 (0x45e000, "cdbutil",  "cdbutil.c ($Id-free; file name string at 0x4d30a4)"),
 (0x465000, "cdbsym",   "C symbol lookup/parse glue ('undeclared identifier', frame commands)"),
 (0x46b000, "profrep",  "'MAJOR PROFILING ERROR'"),
 (0x46c000, "cdbbt",    "cdbbt.c backtrace (string 0x4d4060)"),
 (0x46e000, "cdbeval",  "cdbeval.c C expression evaluator (string 0x4d413c)"),
 (0x47b000, "misc2",    "Error reading memory/register, PostScript font names, banner"),
 (0x47c000, "dirs",     "'Directive %s not allowed here'"),
 (0x47d000, "cofload",  "'Failed to handle COFF file'"),
 (0x47f000, "cdbcall",  "dummy_call, F__send/F__receive host-I/O (C streams)"),
 (0x480000, "tail",     "remaining user code up to 0x4833fa (approx)"),
]
CRT = 0x483400
txt = open(os.path.join(RE, "out/SIM56000/decomp.c"), encoding="latin1").read()
parts = re.split(r'(/\* ==== \S+ @ [0-9a-f]+ ==== \*/)', txt)
outd = os.path.join(RE, "out/SIM56000/mod"); os.makedirs(outd, exist_ok=True)
mods = {}
for i in range(1, len(parts), 2):
    a = int(re.search(r'@ ([0-9a-f]+)', parts[i]).group(1), 16)
    m = "crt"
    if a < CRT:
        for s, n, _ in R:
            if a >= s: m = n
    mods.setdefault(m, []).append((a, parts[i] + parts[i+1]))
fm = open(os.path.join(RE, "notes/SIM56000/filemap.txt"), "w")
fm.write("# SIM56000.EXE module map (approximate; no $Id strings; see re/scripts/splitsim.py)\n")
fm.write("# start\tmodule\tfunctions\tbytes-of-decomp\tevidence\n")
ev = {n: e for _, n, e in R}; ev["crt"] = "MSVC CRT, from 0x483400"
for s, n, _ in R + [(CRT, "crt", "")]:
    fs = mods.get(n, [])
    open(os.path.join(outd, n + ".c"), "w", encoding="latin1").write("".join(b for _, b in fs))
    fm.write("%08x\t%s\t%d\t%d\t%s\n" % (s, n, len(fs), sum(len(b) for _, b in fs), ev[n]))
