"""Corrected module split of SIM56000.EXE (supersedes splitsim.py's approximate ranges).
The ranges come from the eight naming-group notes (re/notes/SIM56000/*.md section 0);
SIM56000 has no RCS $Id strings, so module names are descriptive (real names only where a
string proves them: cdbutil.c, cdbbt.c, cdbeval.c).
usage: splitsim2.py -> re/out/SIM56000/mod/<module>.c, re/out/SIM56000/modules.txt,
                       re/notes/SIM56000/filemap.txt
"""
import re, os, glob
RE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
# start, module, content
R = [
 (0x401000, "main",     "main loop (per-device command dispatch)"),
 (0x401140, "igrp",     "instruction-group statistics methods (igrp_*)"),
 (0x401a50, "emi1",     "EMI #1 peripheral (56004 DRAM controller)"),
 (0x403ae0, "core",     "DSP core: register access, reset, core_clock, AGU, interrupts, memory bus"),
 (0x40a0a0, "dax",      "DAX digital audio transmitter (56011/56012)"),
 (0x40ad60, "gpio",     "GPIO peripheral"),
 (0x40b280, "emi2",     "EMI #2 peripheral (56007/56009)"),
 (0x40d5a0, "shi",      "SHI serial host interface (SPI/I2C)"),
 (0x40fb00, "sai",      "pin-drive helper + SAI serial audio interface"),
 (0x4132b0, "timer",    "TIMER peripheral"),
 (0x413f70, "pwm",      "PWM peripheral"),
 (0x414e90, "wdog",     "watchdog / COP"),
 (0x4155b0, "simvar",   "simvar pseudo peripheral"),
 (0x4159b0, "port",     "parallel PORT peripherals"),
 (0x416190, "sci",      "SCI async serial"),
 (0x418010, "ssi",      "SSI synchronous serial"),
 (0x41a300, "hi",       "HI host interface"),
 (0x41c140, "devreg",   "device registry (device_install) + licence key generator"),
 (0x41c750, "insstat",  "per-instruction statistics records, eval_cc, mnemonic_name"),
 (0x41cfb0, "decode",   "instruction word decoder (110 class handlers) + decode_insn driver"),
 (0x41fb70, "disfmt",   "disassembler formatters (one per opcode class)"),
 (0x423b10, "disasm",   "disassemble (token list -> text), display EA calculator"),
 (0x4240d0, "asm",      "inline assembler (same source family as ASM56000 amode/encode/procop)"),
 (0x42c4c0, "memacc",   "memory/register access engine, region lookup, OMR remap hooks"),
 (0x42eec0, "insattr",  "per-instruction attribute lookups (timing/class/EA/validate handler tables)"),
 (0x430850, "alu",      "56-bit ALU primitives, ALU op handlers, dispatch, peripheral reset/name lookup"),
 (0x4340f0, "state",    "device create/destroy, chip cycle hooks, save/load state, path search"),
 (0x439000, "cmdloop",  "interactive line editor, command completion, command stack, prompt"),
 (0x43a470, "macro",    "macro file reader, overwrite prompt, memory tags, disassembly line formatter"),
 (0x43b5a0, "cmdexec",  "command dispatcher cmd_execute, address range maps, register value formatting"),
 (0x43c2f0, "console",  "register/memory display painter, output/log path, Win32 console, scrollback, arena"),
 (0x43e080, "snap",     "device-state snapshot relocation/restore; where/frame handlers"),
 (0x43e9b0, "watch",    "WATCH window"),
 (0x43f010, "dispval",  "watch value formatting, source-line helpers, wait command"),
 (0x440030, "dbinfo",   "debug info database, code window, address<->symbol/line, step helpers"),
 (0x445030, "cmdh1",    "command handlers: view list next until finish type up trace step system streams reset save redirect quit radix path"),
 (0x448740, "iochan",   "INPUT/OUTPUT back end: channel objects, value parsers, log/load commands, more"),
 (0x44d140, "help",     "history handler, help command, topic lookup"),
 (0x44d670, "cmdh2",    "command handlers: help/go/frame/evaluate/down/display/disassemble/device/copy/change"),
 (0x4523c0, "run",      "change syntax matcher, breakpoint list free, stop-condition check, Break #%d report"),
 (0x453100, "cmdh3",    "command handlers: break, asm; asm parse"),
 (0x454630, "profrpt",  "profiler report generator (metrics.log, coverage, stats, source lines)"),
 (0x456f60, "radix",    "device thunks, radix formatting, access trace ring, dsp_alloc allocator, mdisk_free_all"),
 (0x458060, "mdisk",    "memory disk emulation (m_gdisk/m_pdisk)"),
 (0x458c10, "profhook", "per-instruction profiler hook (sim_profile_step)"),
 (0x459030, "oprefs",   "instruction operand reference recording"),
 (0x459250, "expr",     "simulator expression evaluator"),
 (0x45d120, "miscx",    "decimal split helpers, allocator stubs, sim_error"),
 (0x45e5a0, "hostio",   "host I/O service for the simulated C program (hio_step)"),
 (0x45efe0, "cdbutil",  "cdbutil.c: C-debugger value access, formatting, register tables, arch params"),
 (0x464e30, "cdbsym",   "cdbsym: COFF symbol table walking, scope lookup, source/function lookup"),
 (0x466950, "cmdparse", "command argument syntax classifier (parse_command_line)"),
 (0x46a700, "avltree",  "generic AVL tree + iterator"),
 (0x46b090, "profdata", "profiler data model, MAJOR PROFILING ERROR handler"),
 (0x46c000, "cdbbt",    "cdbbt.c: back trace / frame unwinding"),
 (0x46e1a0, "cdbpro",   "prologue scanners (saved registers per target)"),
 (0x46e870, "cdbeval",  "cdbeval.c: C expression tree evaluator"),
 (0x47a900, "cdbhost",  "target host I/O (__send/__receive breakpoints, file I/O emulation)"),
 (0x47b670, "profps",   "profiler PostScript writer + listing writer"),
 (0x47c2c0, "profdir",  "profiler '; call' directive parsing, call graph building"),
 (0x47d160, "profcg",   "profiler call graph reports"),
 (0x47dc80, "cofscan",  "second COFF reader for profiler/coverage (Failed to handle COFF file)"),
 (0x47f090, "cdbparse", "yacc parser for C expressions + node allocator"),
 (0x4804c0, "cdblex",   "parser support + flex-style lexer"),
 (0x481d50, "profgraph","profiler dependency tree / call graph PostScript output"),
]
CRT = 0x483400
txt = open(os.path.join(RE, "out/SIM56000/decomp.c"), encoding="latin1").read()
parts = re.split(r'(/\* ==== \S+ @ [0-9a-f]+ ==== \*/)', txt)
outd = os.path.join(RE, "out/SIM56000/mod"); os.makedirs(outd, exist_ok=True)
for f in glob.glob(os.path.join(outd, "*.c")): os.remove(f)
def modof(a):
    m = "crt"
    if a < CRT:
        for s, n, _ in R:
            if a >= s: m = n
    return m
mods = {}
for i in range(1, len(parts), 2):
    a = int(re.search(r'@ ([0-9a-f]+)', parts[i]).group(1), 16)
    mods.setdefault(modof(a), []).append((a, parts[i] + parts[i+1]))
fm = open(os.path.join(RE, "notes/SIM56000/filemap.txt"), "w")
fm.write("# SIM56000.EXE corrected module map (re/scripts/splitsim2.py; from the group notes, supersedes splitsim.py)\n")
fm.write("# start\tmodule\tfunctions\tbytes-of-decomp\tcontent\n")
for s, n, e in R + [(CRT, "crt", "MSVC CRT, from 0x483400")]:
    fs = mods.get(n, [])
    open(os.path.join(outd, n + ".c"), "w", encoding="latin1").write("".join(b for _, b in fs))
    fm.write("%08x\t%s\t%d\t%d\t%s\n" % (s, n, len(fs), sum(len(b) for _, b in fs), e))
with open(os.path.join(RE, "out/SIM56000/modules.txt"), "w") as o:
    for l in open(os.path.join(RE, "out/SIM56000/functions.txt")):
        p = l.split('\t'); a = int(p[0], 16)
        o.write("%08x\t%s\t%s\t%s\t\n" % (a, p[1], re.search(r'size=(\d+)', p[2]).group(1), modof(a)))
print(len(R), "modules,", sum(len(v) for v in mods.values()), "functions")
