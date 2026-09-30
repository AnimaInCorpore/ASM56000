# SIM56000.EXE (MOTOROLA DSP56000 SIMULATOR: VERSION 6.3.0 01-15-1999) - command set

Key finding: the original is a full-screen **Win32 console program**. It reads keys with
`ReadConsoleInputA` on the console input handle (FUN_0043d840), draws into a private screen
buffer it creates itself (`CreateConsoleScreenBuffer` + `SetConsoleActiveScreenBuffer`,
`WriteConsoleOutputA`, FUN_0043cd00 / FUN_0043d0b0 ...), and `DAT_004aab9c` (the "no console"
flag) is 0 and never written.  Consequences:
* stdin/stdout redirection does nothing (with stdin redirected the process spins forever in
  FUN_0043d840; nothing is written to stdout/stderr, ever).  `tests/compare.py --stdin` cannot be used.
* argv[1], if present, is passed to FUN_0043b5a0(0, argv[1]) as one command line (e.g. `SIM56000.EXE quit`).
* Oracle: `tests/sim56000/condrive.py` starts the EXE in a new console, injects the script lines as key
  events (`WriteConsoleInputW`) and waits for exit.  Every script opens a **session log**
  (`LOG S file` ... `LOG OFF`): the log file is a byte-exact text transcript (commands, output; the
  highlighted parts of the screen are wrapped in `{ }`, e.g. `{decimal}`, `{$0044}`).  The
  transcript does not contain the `log ...` command lines themselves.
* `tests/sim56000/simtest.py gold` stores the logs (and any other written files) of the original in
  `tests/sim56000/golden/<session>/`; `simtest.py check` runs the rebuilt tool with the script on stdin and
  compares files.  The rebuilt tool therefore needs a plain line-oriented (stdin/stdout) front end that
  produces the same transcript text as the log (portable C89; no console API).

## Top-level command list (help banner 0x4aabd8..0x4aad60, abbreviations in braces)

asm break change copy device disassemble display down evaluate finish frame go help history input
list load log more next output path quit radix redirect reset save step streams system trace type
unlock until up view wait watch where

Usage lines (strings 0x4c5xxx-0x4d3xxx, each command has the same help layout
`{----------- NAME: title -----------}`, examples, usage; error strings around them):

    {A}SM [{B}(byte wide)] [(beginning at) addr] [assembly instruction]
    {B}REAK ...                  (break [r|w|rw|i|...] expr [s|h|note|...], `break off`, `break test.asm@9`, `break main`)
    {C}HANGE [reg[_block]/addr[_block] [expression]]...
    {CO}PY (from) addr[_block] (to) addr
    {DE}VICE {DVn} [device_type/{ON}/{OFF}/{X}]
    {DI}SASSEMBLE [{B}(byte wide)] [addr[_block]]
    {D}ISPLAY [{ON}/{OFF}/{R}/{W}/{RW}] [reg[_block/_group]/addr[_block]]...
    {D}ISPLAY {L}(labels) [{OFF}]      {D}ISPLAY {V}(version)
    {DO}WN [n]                  {UP} [n]          {FR}AME [{#}fn]      {WH}ERE [[+/-]n]
    {E}VALUATE [{B}/{D}/{F}/{H}/{U}] expression | ${c_expression$}
    {F}INISH                    {N}EXT [count][{LI}/{IN}] [{H}]
    {G}O [(from)location/{R}(reset)] [(to break number){#}bn] [(occurrence){:}count]
    {H}ELP [command/reg/topic]  (topics: mem, map, io, macros, comments, groups, display modes...)
    {HI}STORY
    {I}NPUT [#n] [{T}(timed)] addr/port/pin[_group] {OFF}/{TERM}/file [{-RD}/{-RF}/{-RH}/{-RU}]
    {I}NPUT [#n] addr [{DVn:}]addr      {I}NPUT [#n] pin [{DVn:}]pin
    {O}UTPUT [#n] [{T}] addr/port/pin[_group]|history|ehistory {OFF}/{TERM}/file [{-RD}..{-RS}] [{-A}/{-O}/{-C}]
    {LI}ST [{+}/{-}/{.}/addr]
    {L}OAD [{S}(state)|{M}(memory-only)|{D}(debug symbols-only)] (from) filename
    {LO}G [{OFF}] [{C}(commands)/{S}(session)/{P}(profile) [filename [{-A}/{-O}/{-C}]]]     {LO}G [{OFF}] {V}
    {M}ORE [{OFF}]              {P}ATH [pathname] | + [p[,p...]] | -
    {Q}UIT [{E}/{D}]            {R}ADIX [{B}/{D}/{F}/{H}/{U}] [reg[_block]/addr[_block]]...
    {RED}IRECT [{OFF}] | {STDIN} {OFF}/file | {STDOUT}/{STDERR} {OFF}/file [{-A}/{-O}/{-C}]
    {RE}SET {S}(state)/{D}(device) [{M}n]
    {S}AVE {S}(state)/addr_block... filename [{-A}/{-O}/{-C}]
    {ST}EP / {T}RACE [count] [{CY}/{LI}/{IN}] [{H}]     {STR}EAMS [{E}/{D}]
    {SY}STEM [[{-c}] cmd [params]]   {TY}PE ${c_expression$}   {UN}LOCK device_type password
    {U}NTIL line/addr [{H}]     {V}IEW [{A}/{S}/{R}]
    {W}AIT [count(seconds)]     {WAT}CH [{#}wn] [radix] reg/addr/expression
    ;comment lines; macro files (`Macro filename` entries, "Error opening macro file")

Interactive line editor keys (help text 0x4c5dbc..): ^I tab, ^E eol, ^Z del-eol, ^H del-left, ^K del-right,
^O overwrite/insert, ^B/^F command stack back/forward, ^T/^V page up/down, ^W toggle window, ESC clear, ? help.

## Devices ("unlock"/"device")
Device types in the tables: 56000, 56001 (default, `FUN_00435d40(0,"56001")`), 56002, 56004, 56004rom,
56005, 56007, 56009, 56011, 56012, 56000..; 68356 (host bus ?); up to 32 simulated DSPs
(`DAT_004aab0c = 32`), each with its own memory (DSPMEM), on-chip peripherals (porta, horeq, extal, plock,
pinit, timer, count, reset ... register tables with bit-field diagrams for `help <reg>`),
memory map help (`help map`), emi (external memory interface, ~80 variants), interrupt vector tables.

## Code layout
See filemap.txt and re/scripts/splitsim.py.  Roughly (1330 user functions, 2.1 MB of Ghidra C):
exec 0x401140 (154 fn, 390 KB: DSP56000-family instruction execution, one function per opcode family,
statistics in DAT_00505b64+0x3060..), devinit/disasm 0x41c140, inline assembler 0x424000-0x433fff (210 fn),
save/load state 0x434000 (fprintf/fscanf), command loop/line editor 0x439000, console 0x43c000, COFF/CLD
reader 0x440000, I/O + history 0x448000, help 0x44d000, run loop 0x452000, profiler 0x454000-0x456000,
value formatting 0x457000, memory disk 0x458000, expression evaluator 0x459000, and a C debugger core
("cdb": cdbutil.c 0x45e000, cdbbt.c 0x46c000, cdbeval.c 0x46e000, symbol/type handling) 0x45e000-0x47b000.
