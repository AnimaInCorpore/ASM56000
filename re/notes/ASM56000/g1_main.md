# g1_main notes: asmglb, mchglb, dspasm.c, error.c, input.c

Modules covered (per BRIEF.md group assignment `g1_main`):
- `asmglb` - data-only module (global tables) **plus** 18 expression-function math
  wrappers at 0x401000-0x40116d (physically at the front of .text, credited to
  asmglb by the brief even though the address-range heuristic in `modules.txt`
  lists them under `dspasm`).
- `mchglb` - data-only module (machine/instruction tables). No functions.
- `dspasm.c` - main program, command line parsing, pass control.
- `error.c` - error/warning reporting, **plus** a family of opcode dual-operand
  field encoders that live in the same source file (see below).
- `input.c` - source input: line reading, include/macro-file stack, DO-loop
  body replay.

All addresses quoted are in `re/bin/ASM56000.EXE`'s image (.text 0x401000,
.rdata 0x44d000, .data 0x44e000, BSS from ~0x45d800 to 0x466d24).

---

## 1. Global tables owned by mchglb (0x44e000-0x44f668) and asmglb (0x44f668-0x450be8)

This is this group's "special responsibility" per BRIEF.md. Tables were found by
dumping bytes with `re/notes/ASM56000/scratch_g1_main/dd.py <start> <end> [dw|hex] [N]`
and by reading the generic binary-search helpers in util.c
(`FUN_004398cc(key, base, count, elemsize, cmpfunc)`, a `bsearch`-style routine)
to find each table's base/count/element-size arguments.

### 1.1 Instruction mnemonic table - `InstrTab` @ 0x0044e0b0 (mchglb)

- 142 entries (`InstrTabCount` @ 0x0044ebc8 = 0x8e), 20 bytes each, sorted
  alphabetically by mnemonic (binary-searched).
- Element layout (evidence: `FUN_00438f1a` in util.c does
  `FUN_004398cc(name, 0x44e0b0, DAT_0044ebc8, 0x14, FUN_00438f5a)` after
  lower-casing the candidate mnemonic via `FUN_00438f9c`):
  ```
  struct instr_entry {           /* 20 bytes */
      char        *mnemonic;     /* +0x00, lower case, e.g. "abs","add","do" */
      unsigned long f1;          /* +0x04 */
      unsigned long f2;          /* +0x08 */
      unsigned long f3;          /* +0x0c */
      unsigned long f4;          /* +0x10, mostly 2; 4 for bit-manipulation
                                     and DEBUG* mnemonics - looks like an
                                     addressing-mode-variant/operand count. */
  };
  ```
  Example entries (name, f1, f2, f3, f4): `abs 3 1 0x26 2`, `add 0x22 1 0 2`,
  `bclr 5 0 0xa0000 4`, `cmpm 7 1 7 2`, `debug 0x29 0 0x200 4`.
  The 16 `debug*` condition-code variants (`debugcc`, `debugeq`, `debugge`, ...)
  each get their own row rather than being generated from a condition-code
  table.
  The exact bit-meaning of f1..f4 (opcode class / addressing-mode set) is the
  province of `procop.c`/`encode.c` (other groups); we only establish address,
  count and gross layout here, confirmed by the bsearch call signature.
- High-bit-of-f2 note: `FUN_00438f5a`, the compare callback, returns
  `(*(char*)(entry+4) & 0x80) != 0` when the strcmp matches - i.e. bit 7 of f1
  flags some subset of mnemonics as "not found" for lookup purposes (parallel
  to the pseudo-op table's hidden-entry mechanism, see 1.4).

### 1.2 Register name / value-mask table - `RegNameTab` / `RegMaskTab` @ 0x0044ed44 (mchglb)

- 2396 bytes total (0x0044ed44-0x0044f6a0), two parts:
  - Names: 28 pointers (112 bytes, 0x0044ed44-0x0044edb4) to the strings
    `n0..n7`? -- actually first table entry text is `n1` (see string dump,
    `n0` string exists nearby too, used for the "n" addressing register set)
    -- `n1..n7, m0..m7, ab, ba, a10, b10, omr, sr, la, lc, ssh, ssl, sp, mr, ccr`
    (28 names). The literal register-name string pool is at 0x0044f5b0-0x0044f660
    and also holds `a0,a1,a2,b0,b1,b2,r0..r7,n0..n7,m0..m7,ab,ba,a10,b10,omr,
    sr,la,lc,ssh,ssl,sp,mr,ccr` - more names than the 28-entry pointer table
    references, i.e. it is a shared string pool also used by amode.c/symtab.c
    for direct register recognition (not fully mine to resolve).
  - Value masks: array of `unsigned long`, one word per name, mostly
    `0x00007fff`/`0x0000ffff`/`0x0001ffff`/`0x0003ffff` etc. - these look like
    "maximum legal value" bit-masks for each register's immediate/offset field
    (used when checking e.g. `Nn:xxxx` short-offset syntax range). Ownership of
    the *use* of this table is amode.c (other group); we only fix its address
    here.

### 1.3 Processor and revision tables (mchglb)

- `ProcTab` @ 0x0044eca8, 7 entries x 8 bytes (`ProcTabCount` @ 0x0044ece0 = 7):
  `{char *name; unsigned long id;}`:
  `"56000"=0, "56001"=0, "56001c"=1, "56002"=2, "56004"=3, "56007"=4, "68356"=0x2000`.
  Looked up (case-folded) via `util.c:FUN_0043915a` -> `FUN_004398cc(name,
  0x44eca8, DAT_0044ece0, 8, FUN_0043917d)`, called from `pseudo.c:FUN_0042fb7e`
  (the handler for the `-p<proc>` command line option, see section 2). If the
  matched id is `0x2000` (the 68356 host-cpu-embedded-DSP variant) the code
  additionally records `DAT_0044fa00 = 0x2000`.
- `RevTab` @ 0x0044ec70, 4 entries x 12 bytes (`RevTabCount` @ 0x0044eca0 = 4):
  `{char *name; unsigned long value; unsigned long pad0;}`:
  `"2"->2, "4"->3, "7"->4, "c"->1`. Looked up via `util.c:FUN_00439120` ->
  `FUN_004398cc(name, 0x44ec70, DAT_0044eca0, 0xc, FUN_00439143)`, called from
  `pseudo.c:FUN_0042f9fb` (handler for the `-r<rev>` option). The matched
  `value` is stored (minus one) into the same `CpuVariant`
  (`DAT_0044f9fc`) that `-p` writes - i.e. `-r` is a legacy alternate spelling
  of the processor-variant selector using single-letter/digit revision codes
  instead of full chip names, predating `-p`.
- `AModeTab` @ 0x0044ece8, 92 bytes - amode.c's own addressing-mode table
  (other group's territory; flagged here only because it falls in mchglb's
  address range).

### 1.4 Pseudo-op table - `PseudoTab` @ 0x0044fab0 (asmglb)

- 75 entries x 8 bytes (`PseudoTabCount` @ 0x0044fd08 = 0x4b), sorted
  alphabetically, binary-searched from `util.c:FUN_0043903f` ->
  `FUN_004398cc(name, 0x44fab0, DAT_0044fd08, 8, FUN_004390ac)` (name is
  lower-cased first via `util.c:FUN_00438f9c`). Called from `input.c`'s
  `proc_line1`/`proc_line2` (this module) when a mnemonic is not found in the
  instruction table, and from `pseudo.c:FUN_0042fd1e` for directive names.
  ```
  struct pseudo_entry {          /* 8 bytes */
      char        *name;         /* lower case pseudo-op name */
      unsigned long code;        /* dispatch id, used in pseudo.c's switch */
  };
  ```
  All 75 names (address order): `= align baddr baddrr bsb bsc bscb bscl bscw
  bsm bsmr bsr buffer cobj comment dc dcb dcl dcw define ds dsb dsm dsmr dsr
  dup dupa dupc dupf else end endbuf endif endm endsec equ exitm fail force
  global gset himem ident if include list local lomem lstcol maclib macro mode
  msg nolist opt org page pmacro prctl proc radix rdirect rev scsjmp scsreg
  section set stitle symobj tabs title undef warn xdef xref`.
  (`=` is a synonym for `set`, same code 0x132; `bsr` and `bsb` share code
  0x103; `dsr` and `dsb` share code 0x10c - i.e. those are documented
  aliases.)
  **Quirk:** `FUN_0043903f` additionally checks
  `*(char*)(entry+4) == '0'` (the low byte of `code`, read as ASCII) and, if
  true, treats the entry as *not found* **unless** `OptT` (the hidden `-t`
  command line flag, see section 2.3) is set. The only pseudo-op whose `code`
  has low byte `'0'` (0x30) is **`rev`** (code 0x30). So the in-source `REV`
  pseudo-op is silently disabled unless the undocumented `-t` switch is given
  on the command line - reproduce this exactly.

### 1.5 OPT / `-o` suboption name table - `OptNameTab` @ 0x0044fd10 (asmglb)

- 92 entries x 8 bytes (`OptNameCount` @ 0x0044fff0 = 0x5c), sorted
  alphabetically, binary-searched from `util.c:FUN_004390e6` ->
  `FUN_004398cc(name, 0x44fd10, DAT_0044fff0, 8, FUN_00439109)`. This is the
  table shared by the in-source `OPT` pseudo-op and the `-o<opt>[,<opt>...]`
  command line option (both eventually call `pseudo.c:FUN_0042ec12`, which
  looks each comma-separated token up in this table and switches on the id).
  ```
  struct opt_entry { char *name; unsigned long id; };   /* 8 bytes */
  ```
  Full name -> id list (id in hex; every option below and its `no`-prefixed
  negation form its own row - `pseudo.c`'s switch is keyed on `id`, not name):
  ```
  cc=1 cl=2 cm=3 contc=4 cre=5 cex=6 mc=7 md=8 mex=9 nocc=0xa nocl=0xb
  nocm=0xc nocex=0xd nomc=0xe nomd=0xf nomex=0x10 nou=0x11 now=0x12 s=0x13
  u=0x14 w=0x15 fc=0x16 nofc=0x17 il=0x18 mu=0x19 loc=0x1a so=0x1b rc=0x1c
  norc=0x1d intr=0x1e nointr=0x1f xr=0x20 mi=0x22 nomi=0x23 ps=0x24
  nops=0x25 lun=0x26 lng=0x27 ic=0x28 lb=0x29 lbx=0x2a dex=0x2b nodex=0x2c
  mxp=0x2d nomsw=0x2e gs=0x2f nogs=0x30 nl=0x31 nonl=0x32 ns=0x33 nons=0x34
  pp=0x35 nopp=0x36 scl=0x3f noscl=0x40 ur=0x41 nour=0x42 ck=0x43 nock=0x44
  contck=0x45 fm=0x46 nofm=0x47 const=0x48 noconst=0x49 ae=0x4a noae=0x4b
  wex=0x4c gl=0x4d xll=0x4e dxl=0x4f nodxl=0x50 hdr=0x51 nohdr=0x52 svo=0x53
  sco=0x54 ldb=0x55 dld=0x5a nodld=0x5b nde=0x5c nonde=0x5d psb=0x62
  nopsb=0x63 al=0x66 noal=0x67 sms=0x6a nosms=0x6b aec=0x70 noaec=0x71
  si=0x3b nosi=0x3c rp=0x39 norp=0x3a fld=0x30(overlaps? see note) ff=0x58
  noff=0x59
  ```
  (this list was read off the live table; a handful of ids referenced by
  `pseudo.c`'s switch beyond `case 0x4e` were not individually cross-checked
  against a name - the table itself is complete and authoritative, see the
  raw dump reproduced with `dd.py 44fd10 44fff0 dw 2`.)
  Several of these ids write into **asmglb-owned** scalar flags (see 2.4),
  confirming asmglb also holds the *state* for the OPT/-o system, not just its
  name table.

### 1.6 Error-class code table - `ClassCodeTab` @ 0x0044f6a0 (asmglb)

- 43 pointers (`ClassCodeCount` @ 0x0044f74c = 0x2b), to short strings:
  `all gg1 gg2 gg3 gg4 gg5 gp1 gp3 gp4 gp5 gs r2 v1 v2 v3 v4 a1 a2 d1 d3 t1 sr2
  ln1 ln2 ln3 ln4 ll1 ll2 ld1 ld2 ld3 ld4 ld5 ld6 lc1 lc2 lc3 lc4 lc5 lc6 lc7
  lc8 lc9`.
  Sorted by `qsort()` in `init_globals` (`dspasm.c`). Consumed by the
  **undocumented `-s<code>[,<code>...]` command line option** (section 2.3):
  each comma-separated token is checked for membership in this list, fatal
  `"Illegal %s option"` otherwise. No further use of the validated list was
  found inside dspasm.c/error.c/input.c; the naming convention (`gg#`, `gp#`,
  `ld#`, `lc#`...) strongly resembles Motorola/Freescale silicon-errata IDs, so
  this is most likely a hardware-errata-workaround selector, but the actual
  effect is implemented elsewhere (procop/encode/pseudo groups) - open
  question for those groups.

### 1.7 Expression function table - `ExprFuncTab` @ 0x00450048 (asmglb)

Exactly the table BRIEF.md calls out. 54 entries x 16 bytes (owner-confirmed
by `globals.txt`: `0x00450048 864 asmglb func`, and 864/16 = 54).
```
struct expr_func_entry {           /* 16 bytes */
    char         *name;            /* 3-letter (usually) function name  */
    unsigned long code;            /* dispatch id used by eval.c        */
    void         *func1;           /* 1-argument double(double) wrapper, or 0 */
    void         *func2;           /* 2-argument double(double,double) wrapper, or 0 */
};
```
All 54 entries (name=code; a function pointer column shows which of asmglb's
18 math wrappers, section 3, backs it):
```
abs=0x18 -> mth_abs        acs=0xc  -> mth_acos       arg=0x2b (internal)
asn=0xd  -> mth_asin       at2=0x16 -> mth_atan2 (func2) atn=0xe -> mth_atan
byte_address=0x36 (internal)         ccc=0x28 (internal)
cel=0x20 -> mth_ceil       chk=0x2c (internal)         cnt=0x2a (internal)
coh=0x1d -> mth_cosh       cos=0xf  -> mth_cos          ctr=0x29 (internal)
cvf=0x9  (internal)        cvi=0x8  (internal)          cvs=0xa (internal)
def=0x1  (internal)        exp=0x2  (internal, "get exponent" - NOT math exp())
fld=0x30 (internal)        flr=0x1f -> mth_floor        frc=0xb (internal)
int=0x3  (internal)        l10=0x11 -> mth_log10        lcv=0x4 (internal)
len=0x2e (internal)        lfr=0x25 (internal)          lng=0x27 (internal)
log=0x10 -> mth_log        long_address=0x38 (internal) lst=0x1a (internal)
lun=0x26 (internal)        mac=0x6  (internal)          max=0x22 (internal)
min=0x21 (internal)        mjv=0x31 (internal)          mnv=0x32 (internal)
msp=0x5  (internal)        mxp=0x2d (internal)          pos=0x2f (internal)
pow=0x17 -> mth_pow (func2) rel=0x23 (internal)         rnd=0x24 (internal)
rvb=0x33 (internal)        scp=0x7  (internal)          sgn=0x19 (internal)
sin=0x12 -> mth_sin        snh=0x1c -> mth_sinh         sqt=0x13 -> mth_sqrt
tan=0x14 -> mth_tan        tnh=0x1e -> mth_tanh         unf=0x1b (internal)
word_address=0x37 (internal)         xpn=0x15 -> mth_exp
```
All 18 asmglb math wrappers are referenced exactly once each - confirms the
table is complete and that "xpn" (not "exp") is the expression-language name
for the real `exp()` math call, because `exp`/id 2 is already taken by an
internal "extract exponent of a floating value" function. This is a genuine
Motorola-assembler quirk worth preserving: `EXP()` in a `.asm` source file is
**not** `e^x`; use `XPN()` for that.

### 1.8 Other scalars in the asmglb range

A block of default-enabled (`init_globals` sets them to 1) single-byte OPT
state flags lives contiguously in asmglb's data, each one paired with an id
from the OPT table (1.5) that writes it from `pseudo.c:FUN_0042ec12`:
`OptCl`(0x44f778, id `cl`/`nocl`), `OptMd`(0x44f77c, `md`/`nomd`),
`OptMc`(0x44f780, `mc`/`nomc`), `OptCm`(0x44f784, `cm`/`nocm`),
`OptWarn`(0x44f788, `w`/`now` - enables/disables `warn()`/`warn_s()` output),
`OptDxl`(0x44f78c, `dxl`/`nodxl`), `OptPs`(0x44f79c, `ps`/`nops`),
`OptMsw`(0x44f7a4, `mxp`? see below), `OptPp`(0x44f7a8, `pp`/`nopp`),
`OptNs`(0x44f7ac, `ns`/`nons`), `OptAe`(0x44f7b4, `ae`/`noae`),
`OptFlagF7b0`(0x44f7b0, id not individually confirmed),
`OptPsb`(0x44f7bc, `psb`/`nopsb`), `OptAl`(0x44f7c0, `al`/`noal`),
`OptSms`(0x44f7c4, `sms`/`nosms`), `OptNde`(0x44f774, `nde`/`nonde`).
(`OptMsw` was matched to id 0x2d/0x2e which the table lists as `mxp`/(no
matching `nomxp` string found next to it) - flag as `med` confidence, table
transcription may have a 1-off; not critical to dspasm/error/input
functionality.)

Three copies of the `-a` (absolute mode) flag are kept in sync:
`AbsMode`/`AbsMode2`/`AbsMode3` (0x44f790/0x44f794/0x44f798) - `dspasm.c`
writes all three identically at startup and in `init_pass1`/`init_pass`;
presumably each is read by a different downstream module (object.c,
listing.c, section.c) and the redundancy is inherited from the original
source rather than a bug.

`CurFileName`/`LabelField`/`MnemField`/`Op1Field`/`Op2Field`/`Op3Field`/
`Op4Field` (0x44f80c/10/14/18/1c/20/24) are the six pointers `input.c`'s
`parse_line` fills in on every line (current source file name is separate,
written by `set_curfile`); every other module reads them to see "what is the
current line".

`ErrFilePtr` (0x44f9a4) is the `FILE *` used for banner/usage/diagnostic
output; defaults to stderr (`&DAT_0045a470`), redirectable to a real file by
`-ea`/`-ew` (`errfile_open`).

`CpuVariant` (0x44f9fc) holds the selected processor/revision id (written by
`-p`/`-r`, defaults to `0x1fff` = "no restriction").

---

## 2. Command line semantics

### 2.1 Usage banner (verbatim, from `usage()` @ 0x00401437 / string @ 0x00450cac)

```
Motorola DSP56000 Assembler  Version 6.3.0
Copyright Motorola, Inc. 1987-1998.  All rights reserved.
Usage:  ASM56000 [-a] [-b[<objfil>]] [-d<symbol> <string>] [-e<a|w> <errfil>] [-f<argfil>] [-g] [-i<ipath>] [-l[<lstfil>]] [-m<mpath>] [-o<opt>[,<opt>...]] [-p<proc>] [-q] [-r<rev>] [-v] [-z] <srcfil>...
where:
  -a  absolute mode                     -l  listing file
  -b  object file                           <lstfil>  listing file name
      <objfil>  object file name        -m  macro library
  -d  define symbol                         <mpath>  library path name
      <symbol>  symbol name             -o  assembler option
      <string>  value of symbol             <opt>  option argument
  -ea append to error file              -p  processor revision
      <errfil>  error file name             <proc>  processor designation
  -ew write to error file               -q  suppress banner
      <errfil>  error file name         -r  suppress revision
  -f  command file                          <rev>  revision designation
      <argfil>  command file name       -v  verbose mode
  -g  debug mode                        -z  strip absolute object
  -i  include path                      <srcfil>  assembler source file(s)
Assembler command environment variable:  DSPASMOPT
```
(Reproduced verbatim from a live run of `re/bin/ASM56000.EXE`; must match
byte-for-byte in the rebuild, including the two-column layout, which is built
from many separate `fprintf` calls each holding one physical line - see
`usage()`.)

### 2.2 Option scanner

Options are recognised via a private `getopt`-style routine,
`getopt_asm(argc, argv, optstring)` (`dspasm.c` @ 0x00403d70), called with the
literal optstring (found at 0x0044fa08):
```
AaB?b?CcD::d::E::e::F:f:GgI:i:JjL?l?M:m:O:o:P:p:QqR:r:Ss:TtV?v?ZzW?w?Y?y?
```
Both the upper- and lower-case spelling of every letter are listed
separately (each with its own arg-spec) - `parse_cmdline_opts` (`dspasm.c` @
0x00402025) subsequently `tolower()`s whatever letter came back before
switching on it, so options are effectively case-insensitive.
Per-letter arg convention (read directly off the optstring):
- *(no suffix)* - flag only, no argument (`A a C c G g J j Q q S T t Z z`).
- `?` - optional argument, only taken if attached to the same token
  (`-l<lstfil>`) or, if nothing is attached, the *next* token **only when it
  does not itself look like another option** (`B b L l V v W w Y y`).
- `:` - one required argument, taken from the remainder of the same token if
  present, else the next token (`F f I i M m O o P p R r s`).
- `::` - **two** required arguments: the remainder of the same token (or the
  whole next token if nothing follows the letter) *and* the token after that
  (`D d E e`) - this is exactly `-d<symbol> <string>` and `-e<a|w> <errfil>`.

`getopt_asm` fatally errors (`"Illegal command line option"`) on an unknown
letter, and (`"Missing command line option argument"`) if a required argument
is absent.

### 2.3 All single-letter options, including undocumented ones

Handled in `parse_cmdline_opts` (`dspasm.c` @ 0x00402025); the switch is on
the lower-cased letter:

| opt | documented? | effect |
|---|---|---|
| `-a` | yes | absolute mode (no-op in the switch itself - the effect is read from `AbsMode`, which `main`/`init_globals` set from `opt_find('a',...)` *before* `parse_cmdline_opts` runs) |
| `-b[<objfil>]` | yes | selects an object file name; without an explicit name, derives one from the source file (via `ensure_ext`/`add_ext_if_empty`, extension `.cld` absolute / `.hex`? - exact default extension owned by object.c) |
| `-c` | **no** | hidden. Read in `main` before the option scanner even runs (`opt_find('c',...)`); selects the alternate top-level driver `run_cmode` instead of `run_default`. Message `"Options for both absolute and C module..."` if combined with `-a`. No-op inside `parse_cmdline_opts`'s switch itself. Best guess: a legacy "C-callable module" / incremental-object mode. |
| `-d<symbol> <string>` | yes | defines a textual substitution symbol (`FUN_0042bba2`, pseudo.c) - same effect as an in-source `DEFINE`. |
| `-ea` / `-ew` | yes | redirect the diagnostic stream (`ErrFilePtr`) to a file, append or (over)write; letter after `-e` must be `a` or `w` exactly, else fatal `"Illegal command line -E option..."`. |
| `-f<argfil>` | yes | reads `<argfil>` as more command line arguments (recursively - a command file may itself contain `-f`); also the mechanism used to fold the `DSPASMOPT` environment variable in (`build_argv`, `tokenize_str`, `read_cmdfile`). |
| `-g` | yes | debug mode (`OptG`/`DAT_0045eadc`); mutually exclusive with `-z` (`"Options for both debug and strip..."`). |
| `-i<ipath>` | yes | adds an include search path (`FUN_0042c542`, pseudo.c). |
| `-j` | **no** | hidden. Read in `main` (`opt_find('j',...)`). Only effect seen in this group's modules: when set, `get_line` (input.c) invokes `sdi_optimize` (`FUN_00434430`, sdi.c) right after the pre-pass. Likely an internal "short-distance-instruction optimisation" debug switch; no-op in `parse_cmdline_opts`'s own switch. |
| `-l[<lstfil>]` | yes | listing file, same optional-name convention as `-b`. |
| `-m<mpath>` | yes | macro library search path (`FUN_0042c457`, pseudo.c). |
| `-o<opt>[,<opt>...]` | yes | queues one or more comma-separated OPT names (table 1.5); actual validation/application is deferred to `apply_o_options`, which walks the queue calling `pseudo.c:FUN_0042ec12` (fatal `"Illegal command line %s option"` on an unknown name). |
| `-p<proc>` | yes | selects a processor by name (table 1.3, `ProcTab`). |
| `-q` | yes | suppress the startup banner (checked directly in `main`, not in the switch). |
| `-r<rev>` | yes | legacy revision-code form of processor selection (table 1.3, `RevTab`). |
| `-s<code>[,<code>...]` | **no** | hidden (uppercase `-S` alone is accepted as a flag with **no** argument per the optstring but is not separately handled). Validates a comma list against the 43-entry `ClassCodeTab` (1.6); effect beyond validation not found in this group's modules. |
| `-t` | **no** | hidden. Sets `OptT`; the only confirmed effect is unhiding the `rev` pseudo-op in the pseudo-op table lookup (1.4) and enabling tab-expansion of source lines before further processing (`FUN_0043b836`, called from `set_curfile` when `OptT` is set). |
| `-v[<N>]` | yes | verbose mode; optional numeric argument sets `VerboseInterval` (progress messages every `<N>` lines instead of the default), read with `strtol(...,10)`. |
| `-w<file>` | **no** | hidden (`Lint`-style secondary warning-input file: `"Lint input warning file already s..."` on reuse). Not documented in the usage banner at all. |
| `-y` | **no** | hidden, sets a single BSS flag (`DAT_0045d828`); no further effect found in this group's modules. |
| `-z` | yes | strip absolute object (mutually exclusive with `-g`, and refused in relocatable/non-absolute mode: `"Strip not valid in relocatable mode"`). |

`-q`/`-c`/`-j` and the file-name arguments themselves are consumed via the
*separate* single-shot helpers `opt_find`/`opt_index` (0x00403aa7/0x00403b78)
directly in `main`, **before** `parse_cmdline_opts`'s full getopt pass runs -
this is why `-c`/`-j`/`-q` have no visible case body (their value was already
read into a flag).

After the switch, `parse_cmdline_opts` also cross-checks that no source file
name collides with the chosen object or listing file name
(`"Source file name same as object/listing file"`).

### 2.4 `DSPASMOPT` environment variable

Read once in `main` via `getenv("DSPASMOPT")`. If set, `build_argv`
(`dspasm.c` @ 0x00402dfa) is invoked to construct a *new* `argv`:
`argv[0]`, then the tokens of `DSPASMOPT` (`tokenize_str`, honouring quotes),
then, for each of the process's real command line arguments: if it is
`-f<file>` (any case), expand `<file>`'s contents as more tokens
(`read_cmdfile`, recursive), otherwise keep the argument verbatim. The
combined vector replaces `argc`/`argv` for the rest of the run. This lets
`DSPASMOPT` supply default options that behave exactly as if typed first on
the command line (and can itself be overridden by explicit `-f` command
files).

### 2.5 Every `-o` / `OPT` option name

See table 1.5 for the full 92-name/id table (both positive and `NO`-prefixed
forms of every switch). Options whose id triggers an early-defined-content
guard, requiring they appear *before* any label/section/symbol/macro
definition, print a dedicated message (see `pseudo.c:FUN_0042ec12`):
`CRE, GL, GS, NOGS, IC, LB, LBX, LDB, LOC, MU, SCO, SVO, XLL, XR`. All others
take effect immediately, purely as one-shot boolean/state toggles.

---

## 3. Pass structure

Global `Pass` (`DAT_0045f8fc`) is the single source of truth for "which pass
are we in": **0** = pre-pass/uninitialised, **1** = pass 1, **2** = pass 2.
Checked pervasively throughout the codebase (`if (Pass == 2) ...` gates most
real error/warning output and object-file writes so pass-1 forward references
don't spuriously fail).

The **default** driver is `run_default` (`dspasm.c` @ 0x00401c97), used
whenever the hidden `-c` flag is *not* given (the normal case):

1. **Pre-pass** (`pre_pass` @ 0x00401b35 opens the first source file just to
   sanity-check it exists; `process_file` @ 0x004197d0 scans the *entire*
   file once calling `get_line`/`parse_line`/`proc_line1`-style dispatch with
   `Pass == 0`; `end_prepass` @ 0x004059f6 then closes/rewinds everything
   *silently* - no "unexpected EOF" diagnostics, since at `Pass==0` nothing is
   semantically final yet). Purpose: establish source-file existence/basic
   structure and process any pre-pass-only bookkeeping (e.g. section list)
   before pass 1 "for real" begins.
2. `init_pass1` (`dspasm.c` @ 0x004047e0) resets per-run counters
   (`ErrorCount`, `WarningCount`, `LineNo`, ...), OPT-flag defaults, the
   section/DO-loop bookkeeping, and sets `Pass = 1`.
3. `apply_o_options` re-applies the queued `-o` options (they must be
   re-applied per pass because `init_pass1`/`init_pass` just reset several of
   the flags they set).
4. Source file is reopened from scratch, `process_file` drives pass 1 across
   every line (`proc_line1`, this module, does label/pseudo-op/mnemonic
   dispatch; real code generation and symbol-table definition happen in the
   modules that own those pseudo-ops/mnemonics).
5. `init_pass` (`dspasm.c` @ 0x00404ef2, shared with the alternate driver) is
   called again; since `Pass` is already 1 (not 0) it sets `Pass = 2` this
   time, and performs a very similar reset (line/error counters, DO-loop
   stack, section rewind via `sect_rewind`, OPT-flag defaults) - **not**
   reset: the symbol table, macro definitions, or anything pass-1 is supposed
   to have permanently learned.
6. Source reopened a second time, `process_file` drives pass 2
   (`proc_line2`, this module, additionally produces listing/cross-reference
   output and expands `DO`-loop bodies via `do_replay_line`).
7. `end_pass(0)` (`dspasm.c` @ 0x00405b98) finalises: closes any still-open
   include/macro nesting *with* diagnostics this time (`"Unexpected end of
   file - missing ..."`), writes the object-file trailer, closes object and
   listing files, deletes a half-written object file if the run ended in
   error.

The alternate driver `run_cmode` (`dspasm.c` @ 0x004015e3, used only when the
hidden `-c` option is set) loops the same pre-pass/pass-1/pass-2 sequence
**per source file** in a `do { ... } while (more files)` loop, re-opening a
fresh listing/object file set for each one - i.e. it treats each of the
`<srcfil>...` arguments as an independent one-file assembly rather than one
combined multi-file assembly. `init_pass1`/`init_pass` overlap: `run_cmode`
uses `init_pass1` explicitly for the first pass of each file and `init_pass`
for the second, whereas `run_default` uses `init_pass` for both transitions
(0->1 and 1->2) since it is written to be driver-agnostic.

Between the two passes, what is **reset**: line number and per-file line
totals, error/warning counters, section program-counters (`sect_rewind`),
`DO`-loop/macro-call nesting stacks, listing column/page state, default radix
and tab width, and every OPT boolean back to its command-line-line default.
What **carries over** pass 1 -> pass 2: the symbol table, macro definitions,
the list of files touched (`OpenFileList`, checked against on pass 2's file
opens - `"File not encountered on pass 1"` if a `-f`/env-supplied file list
differs between passes), and the object/listing default filenames derived
from the first source file's name.

---

## 4. Structures encountered

### 4.1 DO-loop stack frame (input.c)

Linked list at `DoStack` (`DAT_0045fc30`), pushed/managed by pseudo.c (owner)
but read/written by this module's DO-loop helpers:
```
struct do_frame {
    unsigned long end_pc;      /* +0x00 (implied by *DAT_0045fc30 use) */
    void         *saved_text;  /* +0x04, malloc'd copy of a source line, set
                                   by do_save_line / freed by do_stack_unwind */
    unsigned long saved_pc;    /* +0x08, PC at which saved_text was recorded */
    void         *next;        /* +0x0c, next (outer) frame                 */
};
```
Evidence: `do_save_line` (`FUN_0041b3c7`) does
`malloc(strlen(line)+1); frame[1]=that; strcpy(frame[1], line);
frame[2] = *CurPC;`; `do_stack_unwind` (`FUN_0041b43f`) walks
`frame[3]` (`next`) and pops while `frame[0] <= PC`; `do_replay_line`
(`FUN_0041b4d3`) restores `*CurPC = frame[2]`, `strcpy(linebuf, frame[1])`
then re-runs `parse_line`+`proc_line2`.
Allocation: 
`FUN_00439857` (util.c malloc wrapper) sized to `strlen(text)+1`
for the text; the frame node itself is allocated by pseudo.c (not this
module).

### 4.2 Macro/include "input mode" stack (input.c)

Small list at `InputModeStack` (`DAT_0045fc28`), each node:
```
struct input_mode_node {
    void *saved_curfilename;   /* +0x00 -> restored into CurFileName       */
    void *saved_fp;            /* +0x04 -> restored into CurSrcFp          */
    unsigned long saved_open_count; /* +0x08                               */
    unsigned long saved_lineno_base;/* +0x0c -> restored into LineNoBase   */
    void *pending_free;        /* +0x10, malloc'd string freed on pop, and
                                   (if in macro-capture context) also copied
                                   into a macro-node field                 */
    void *next;                /* +0x14                                   */
};
```
(offsets read off `input_pop`, `FUN_00419ba2`; node size 24 bytes, freed with
`FUN_004398b5`, util.c's free wrapper). Popped by `input_pop`, which
`fatal("Input mode stack out of sequence")`s if `mstate_pop`
(a tiny 1-word auxiliary stack, `MacroStateStack`/`DAT_0045fc2c`) doesn't
agree the mode really is a nested one.

### 4.3 Parsed-line fields (input.c `parse_line`)

Not a struct but six independent globals, all pointing into the 512-byte
line/scratch buffers `RawLineBuf`/`LineBuf` and their per-field copy area
(`0x0045ee10`+): `LabelField`, then (after `.` special-case dispatch via
`FUN_004317e0`, another module's pseudo-op-prefix handler)
`MnemField`, `Op1Field`, `Op2Field`, `Op3Field`, `Op4Field` (the last one
also swallows any trailing comment text verbatim once no more `;` is seen).
Each is NUL-terminated in place; absence of a field is an empty string, not
NULL.

### 4.4 Table element structs

See section 1 for `instr_entry` (20 bytes), `pseudo_entry`/`opt_entry`/
`proc_entry` (8 bytes each), `rev_entry` (12 bytes), `expr_func_entry`
(16 bytes).

---

## 5. Function reference

### asmglb (18 functions, 0x401000-0x40116d)

All 18 are trivial `__cdecl` wrappers taking one or two `double` arguments
(passed as two/four stack dwords, per MSVC's cdecl double-passing) and
returning `double`, calling straight into the matching CRT `<math.h>`
function. High confidence throughout (Ghidra recovered the CRT call in every
case). See `re/names/ASM56000/g1_main.names.txt` for the address list; they
are `mth_atan`, `mth_abs`(fabs), `mth_acos`, `mth_asin`, `mth_ceil`,
`mth_cosh`, `mth_cos`, `mth_floor`, `mth_log10`, `mth_log`, `mth_sin`,
`mth_sinh`, `mth_sqrt`, `mth_tan`, `mth_tanh`, `mth_exp`, `mth_pow`(2 args),
`mth_atan2`(2 args). They are the function-pointer targets of the
`ExprFuncTab` (1.7) and are called by eval.c (another group) when the
assembler's expression language evaluates e.g. `SIN(x)`.

### dspasm.c (33 functions)

- **`main`** (0x00401190): installs `sig_handler` for SIGINT/SIGFPE/SIGSEGV;
  derives the program's own base name (for `%s:` message prefixes) from
  `argv[0]`; reads `DSPASMOPT` and calls `build_argv` if set; pulls `-f`,
  `-a`, `-c`, `-q`, `-j` and `-ea`/`-ew` out of the raw argument list directly
  (see 2.3); prints the startup banner unless quiet; calls `usage()` if no
  arguments were given; computes the default object base name
  (`default_obj_basename`); dispatches to `run_default` or `run_cmode`
  depending on `OptC`; `exit()`s with the accumulated error count (optionally
  folded together with the warning count if `ScaleErrByWarn` is set).
- **`usage`** (0x00401437): prints (optionally) the banner, then the full
  usage text (section 2.1) to `ErrFilePtr`, then `exit(-1)`.
- **`run_cmode`** (0x004015e3): per-file `do`/`while` driver, see section 3.
- **`open_source`** (0x00401a16): opens a named source file for reading;
  falls back to appending a default extension (`has_ext`/basename helper) if
  the bare name doesn't open; fatal `"Cannot open source file"` if that also
  fails.
- **`strip_ext`** (0x00401ad4): truncates a path at its last `.`.
- **`has_ext`** (0x00401af9): `strcmp`s a path's last-`.` suffix against a
  given extension string.
- **`pre_pass`** (0x00401b35): opens the *first* source-file argument (trying
  bare name, then with a default extension) purely to validate it exists and
  run the `Pass==0` prescan; fatal `"Missing source filename"` if none given.
- **`run_default`** (0x00401c97): the normal one-shot driver, see section 3
  step-by-step.
- **`cur_src_basename`** (0x00401ffb): basename (no extension) of
  `*SrcArgv`, the current source argument.
- **`parse_opts_wrap`** (0x0040201b): thin wrapper calling
  `parse_cmdline_opts`; kept distinct because it is the entry point used from
  `pre_pass`'s call graph versus the main option-application sites.
- **`parse_cmdline_opts`** (0x00402025): the getopt-driven per-run option
  dispatcher, section 2.3.
- **`noop_argsrc`** (0x004029fe): literally `{ return; }` - used as the
  "consume command line options" stand-in when `AltSrcMode` selects the
  alternate/host-supplied source-list invocation path instead of argv.
- **`altsrc_more`** (0x00402a03): `return *param_1;` - tests whether the
  alternate source-file list (`&DAT_00465a88`, host-supplied, see below) has
  another entry.
- **`apply_o_options`** (0x00402a0d): walks the linked list of raw `-o`
  argument strings (`OOptList`/`DAT_0045fc6c`) built by `parse_cmdline_opts`'s
  `-o` case, and calls `pseudo.c:FUN_0042ec12` on each, exiting fatally on
  the first rejected one.
- **`default_obj_basename`** (0x00402a99): strips extension and directory off
  `argv[first source file]`, used as the seed for default object/listing
  names.
- **`ensure_ext`** (0x00402b5e): appends a given extension to the path buffer
  if it doesn't already end with (exactly) that extension; returns
  pointer-or-0 depending on whether it changed anything.
- **`add_ext_if_empty`** (0x00402bfa): same idea, but only fires if the
  current extension is completely empty (used for the fallback "no explicit
  `-b`/`-l` name" case after `ensure_ext`'s primary attempt).
- **`ensure_path_sep`** (0x00402c7c): appends a trailing `\` to a path buffer
  if it doesn't already end in `\` or `:`.
- **`set_curfile`** (0x00402cde): registers/looks-up the "currently open
  source file" name in `OpenFileList` (`DAT_0045fc24`); on pass > 0 this is a
  *lookup* that must match what pass 1 recorded (`fatal("File not encountered
  on pass 1")` otherwise) - this is how the assembler detects a `-f`/env-var
  argument list that differs between invocations of the two passes (should
  never happen in a single run, but the check exists). Also expands tabs
  in-place if `OptT` is set.
- **`build_argv`** (0x00402dfa): merges `DSPASMOPT` and `-f` command files
  into a fresh `argv`, section 2.4.
- **`tokenize_str`** (0x00403070): splits a string into whitespace-separated
  (quote-aware) words, appending each to the linked list `build_argv` is
  assembling.
- **`read_cmdfile`** (0x004033a1): opens a `-f`/`DSPASMOPT`-referenced command
  file and tokenizes its contents the same way (recursive: a command file's
  own `-f` references are expanded too).
- **`opt_find`** (0x00403aa7): one-shot scan of `argv` for `-<letter>`
  (case-folded), returning the matching `argv[i]` pointer or 0; used for the
  handful of options read directly in `main` before the full getopt pass.
- **`opt_index`** (0x00403b78): same scan, but returns the 1-based `argv`
  index instead of the pointer (used only for the `-e` handling in `main`,
  which then dereferences the found index directly).
- **`errfile_open`** (0x00403c50): implements `-ea`/`-ew`: validates the
  `a`/`w` sub-letter and that an argument follows, fatally rejecting a
  missing/`-`-looking argument, then (re)opens `ErrFilePtr`.
- **`getopt_asm`** (0x00403d70): the private getopt core, section 2.2.
- **`init_globals`** (0x004040b4): one-time (per invocation) global reset:
  zeroes counters, `qsort()`s `ClassCodeTab`, sets every OPT boolean to its
  documented default (mostly "on"), computes section/PC bookkeeping defaults,
  calls `sect_rewind`.
- **`init_pass1`** (0x004047e0): sets `Pass = 1` and resets the same
  per-pass counters as `init_pass` (used by `run_cmode`'s explicit two-call
  style instead of `init_pass`'s implicit 0->1/1->2 toggle).
- **`init_pass`** (0x00404ef2): shared pass-1/pass-2 initialiser used by
  `run_default`, see section 3 step 5; advances `Pass` itself (0->1 or ->2).
- **`sect_rewind`** (0x00405611): walks the section list resetting each
  section's PC/pad bookkeeping for the next pass, recomputing per-section
  padding/alignment overflow and forcing sections that end up empty to a
  "skip" flag; also clears the six paged-memory-map range trackers
  (`0x0044f838`.. region) between passes.
- **`end_prepass`** (0x004059f6): silent cleanup after the throwaway
  `Pass==0` prescan - closes any nested include/macro state without
  complaint, closes and frees a stray lint-warning-input file if one was
  opened, resets several linked-list heads.
- **`end_pass`** (0x00405b98): real pass-end cleanup; `final==0` additionally
  emits `"Unexpected end of file - missing ..."` diagnostics for any
  still-open `IF`/`DO`/macro nesting, writes the object trailer
  (`FUN_004212f9`) and deletes the object file if the run is erroring out;
  always closes object/listing/lint files it owns.
- **`sig_handler`** (0x00405db4): SIGINT (2) and SIGSEGV (11) print a message
  and `exit()` with the accumulated error count (or -1 if none yet);
  SIGFPE (8) re-arms itself, reports `"Arithmetic exception"`, and either
  `longjmp`s back to a recovery point (`0x0045b80`, if one is registered via
  `setjmp` elsewhere - not in this module) or is fatal if not.

### error.c (24 functions)

Core error/warning reporters (high confidence, the actual "error.c" purpose):
- **`fatal(msg)`** (0x00412fa0): formats `"***%2ld %s%5ld*** FATAL ***%s"`
  (line/file/... prefix + message) into the shared line buffer, writes it to
  `ErrFilePtr` (unless suppressed) and to the listing (`FUN_00413999`) if
  listing is open, calls the listing module's close/flush hooks, removes a
  half-written object file, then unconditionally `exit(-1)`.
- **`err(msg)`** (0x00413085) / **`err_s(msg, arg)`** (0x004131f9): the normal
  (non-fatal) error path - only fires when `Pass == 2` and the run isn't in a
  suppressed-diagnostics window (`DAT_0045ea50`, set around internal
  self-checks). Formats a `"*** ... ERROR ***"` line, optionally appends
  " field <name>" (looked up from the instruction table's field-name side
  table `PTR_DAT_0044f960`) or "See instruction at P:XXXX" depending on
  context, then increments `ErrorCount` and a per-line error counter. `err_s`
  additionally `strncat`s a caller-supplied string (max 256 bytes) into the
  message before the field/location suffix - used for `"Unrecognized
  mnemonic: %s"` etc.
- **`warn(msg)`** (0x004133a9) / **`warn_s(msg, arg)`** (0x0041351d): same
  shape as `err`/`err_s` but gated additionally on `OptWarn`, and increments
  `WarningCount` instead of `ErrorCount`.

Opcode dual-operand/parallel-move field encoders (the rest of the file - low
confidence on exact instruction-format correspondence, which is really
procop.c/encode.c territory; documented here only because the Ghidra
module-vote/`$Id` evidence places them in error.c, presumably because each
one's failure path calls straight into `fatal`/`err` above):
- **`y_code(class)`** (0x0041290b), **`lll_code(class)`** (0x004129d7),
  **`qq_code(class)`** (0x00412f33): pure lookup tables mapping a small
  operand-class integer to a 1/4/2-bit opcode field value; each calls
  `fatal("Y/LLL/QQ encoding failure")` on an operand class it doesn't
  recognise. High confidence (clean switch statements, message strings name
  the exact field).
- **`enc_ea_dual`** (0x00412822), **`enc_ea_dual2`** (0x00412ac3),
  **`enc_ea_dual3`** (0x00412ce3), **`enc_ea_pair_raw`** (0x00412c72),
  **`enc_acc_ea`** (0x00412e4f): pack a pair of "effective address" operand
  fields (register number + offset-class, via util.c's `FUN_00410b29`/
  `FUN_00410c5c`) plus (for the `_dual*` variants) a `y_code`/`lll_code`
  result into fixed bit positions of the object opcode word using the
  generic bit-field setter `util.c:FUN_0043bd1e(word, value, start_bit,
  width)`; each has a `_pm` counterpart (`enc_ea_dual_pm` 0x00412941,
  `enc_ea_dual2_pm` 0x00412b7b, `enc_ea_dual3_pm` 0x00412da0) that first sets
  a single "parallel move present" bit (bit 15) then delegates.
- **`enc_lll`** (0x0041297d) / **`enc_lll_flag`** (0x00412a8f),
  **`enc_l_field`** (0x00412dd4) / **`enc_l_field_pm`** (0x00412e1b): pack a
  single `lll_code`-derived (or util.c `FUN_00410d97`-derived "L") field.
- **`enc_acc_field`** (0x00412baf), **`enc_acc_pair`** (0x00412c09): pack one
  or two accumulator-class fields (via util.c's `FUN_00410ec7`) - `enc_acc_pair`
  has no trailing `Fun_0043bdfb` call, suggesting it's used where the caller
  does its own follow-up validation.
- **`enc_qq_reg`** (0x00412ecb): packs a register-class field
  (`FUN_00410a2b`) plus a `qq_code` field.
- **`enc_pm_flag1`** (0x004127e6): sets the parallel-move-present bit then
  delegates to `util.c`/`encode.c`'s `FUN_004126b2` directly (not one of the
  `enc_ea_*` helpers above) - lowest confidence in the file, only the
  "set flag bit, delegate" shape is clear.

### input.c (20 functions)

- **`process_file`** (0x004197d0): outer per-source-file loop - repeatedly
  `get_line` + (pass-dependent) `parse_line`/`proc_line1`/`proc_line2` +
  listing-column reset, until `get_line` reports no more input.
- **`get_line`** (0x0041983e): the "give me the next source line, spanning
  file/argument boundaries" entry point. Increments `LineNo`
  (fatal `"Too many lines in source file"` on overflow), calls `read_line`;
  on end-of-current-file pops nested input state via `input_pop` and retries;
  if truly out of input and not in `OptC` mode, opens the *next* remaining
  command-line source file argument and continues from there (multi-file
  concatenation - all `<srcfil>...` arguments are assembled as one logical
  unit, not run separately, except under `run_cmode`).
- **`input_pop`** (0x00419ba2): pops one saved input-mode node (section 4.2)
  when a nested macro/include-like read context ends; fatal `"Input mode
  stack out of sequence"` if the auxiliary 1-word stack (`mstate_pop`)
  disagrees.
- **`read_line`** (0x00419caf): low-level line reader - pulls characters via
  `input_getc`, expands tabs, honours quoted strings (so `;`/blanks inside
  `'...'`/`"..."` don't end a token early), backslash-newline continuation,
  and calls `subst_symbol` on each identifier-shaped run of characters
  outside quotes when `-d`/`DEFINE` substitution is active; fatal `"Line too
  long"` past 0x45ee08 (the fixed-size line buffer's end).
- **`input_getc`** (0x0041a0a7): the actual character source - ordinary
  `getc`-equivalent buffered file read when not inside a macro expansion;
  inside a macro body it additionally recognises escape codes for macro
  parameter substitution (numeric formatting via `%s`/`%d`-style
  `sprintf` depending on the parameter's stored type, `0x100` flagging a
  string-valued parameter) and injects the substituted text character by
  character before resuming the macro body.
- **`mstate_push`** (0x0041a3ce) / **`mstate_pop`** (0x0041a3ff): trivial
  1-word linked-list push/pop, used to remember why an input-mode nesting was
  entered so `input_pop` can sanity-check it.
- **`chk_line_end`** (0x0041a444): scans to the first "blank-class" character
  or NUL in the freshly-read line; in the current binary this always returns
  1 regardless of what it finds - looks like the remnant of a trailing-quote
  validation that has been optimised down to a no-op (possible latent
  quirk/bug, harmless).
- **`parse_line`** (0x0041a4bc): splits the raw line buffer into
  label/mnemonic/operand1-4 fields (section 4.3); recognises a label ending
  in `:` versus a column-1 label without one, hands off to another module's
  `.`-prefixed-directive handler (`FUN_004317e0`) when the mnemonic field
  starts with `.`.
- **`scan_token`** (0x0041a92e): advances a pointer to the next
  blank/tab/NUL, skipping over `'...'`/`"..."` quoted runs so quoted
  whitespace doesn't end the token.
- **`subst_symbol`** (0x0041a9e9): in-place textual substitution of a
  `-d`/`DEFINE`d symbol's replacement string into the line being read, with
  `DEFINE`/`UNDEF` themselves specially exempted so their own keyword isn't
  substituted; also exempts any identifier whose first character is `_`
  (`NoSubstChar`). Looks the identifier up via `FUN_0043012d` (another
  module's symbol table).
- **`proc_line1`** (0x0041ad75): pass-1 per-line dispatch - periodic
  `"Processing line N in file F"` progress message every `VerboseInterval`
  lines; label lookup (as a macro name) falling through to the pseudo-op
  table (1.4) then the instruction table (1.1); `fatal("Unrecognized
  mnemonic")`-equivalent via `err_s` if neither matches.
- **`proc_line2`** (0x0041af7e): pass-2 counterpart of `proc_line1`; same
  dispatch, plus listing-line emission, cross-reference recording
  (`FUN_0042433e`), and (once, on the first call) recognises the special
  `.file` mnemonic that another module's pseudo-op reuses for compiler-driver
  file markers.
- **`do_line_reset`** (0x0041b339): clears per-line DO-loop/listing
  bookkeeping (word counts, "was this a repeated/duplicated line" flags) at
  the start of each new line; carries the *previous* line's word count
  forward into a one-line-lookback slot first (used by the "cannot appear in
  last/next-to-last word of a DO loop" checks).
- **`do_save_line`** (0x0041b3c7), **`do_stack_unwind`** (0x0041b43f),
  **`do_replay_line`** (0x0041b4d3): DO-loop body capture/replay, section
  4.1.
- **`do_check_end_range`** (0x0041b615) / **`do_check_end_range_err`**
  (0x0041b685): boolean test (resp. test-and-error) for "is the current PC
  within the last `n` words of the innermost open DO loop" - backs the
  "Instruction cannot appear within last 2..6 words of a DO loop" family of
  restrictions (DSP56000 pipeline/looping hardware limitation).
- **`do_check_end_word_err`** (0x0041b7c9): same idea but for an *exact* word
  offset from the loop end (0=last, 1=next-to-last, 2=second-to-last,
  3=third-to-last) - backs "Instruction cannot appear in last/next-to-
  last/second-to-last/third-to-last word of a DO loop".

---

## 6. Cross-module interfaces (functions of other modules this group's code calls)

- `pseudo.c:FUN_0042ec12` - applies one OPT/-o suboption id (table 1.5);
  called by `apply_o_options` (dspasm.c) and internally by pseudo.c's own
  `OPT` pseudo-op handler.
- `pseudo.c:FUN_0042fb7e` / `FUN_0042f9fb` - `-p`/`-r` processor/revision
  selection (tables 1.3); called from `parse_cmdline_opts`.
- `pseudo.c:FUN_0042c542` / `FUN_0042c457` / `FUN_0042bba2` - `-i`/`-m`/`-d`
  option application; called from `parse_cmdline_opts`.
- `util.c:FUN_004398cc` - generic `bsearch`; the mechanism behind every table
  lookup in section 1.
- `util.c:FUN_00438f9c`/`FUN_00439109` etc. - lower-case-and-compare
  callbacks paired with the bsearch calls above.
- `util.c:FUN_0043bd1e` / `FUN_0043bdfb` - generic opcode-word bit-field
  setter/getter, used throughout error.c's `enc_*` helpers.
- `sdi.c:FUN_00434430` (`sdi_optimize`) - invoked from `get_line` when the
  hidden `-j` option is set.
- `object.c` (`FUN_00405f6a`, `FUN_004212f9`, ...) - object file
  open/trailer-write helpers called from the pass drivers.
- `listing.c`/`macro.c`/`section.c`/`symtab.c` cleanup hooks
  (`FUN_00435924`, `FUN_004375e6`, `FUN_00433b90`, `FUN_00439547`, ...) -
  called from `end_prepass`/`end_pass` to flush/close each subsystem.
- Expression evaluation (`eval.c`) is the consumer of `ExprFuncTab` (1.7) and
  of asmglb's 18 `mth_*` wrappers.
- `procop.c`/`encode.c` are the consumers of the instruction table (1.1) and
  (indirectly, as callers) of error.c's `enc_*` field encoders.

---

## 7. Quirks / bugs worth reproducing

1. **`EXP()` is not `e^x`.** The expression-function table (1.7) assigns
   plain `exp` (id 2) to an *internal* "extract exponent of a value"
   operation; the real `exp()` math call is exposed under the name `XPN()`
   instead. Any expression evaluator must replicate this exact name mapping.
2. **`REV` pseudo-op is hidden by default.** `PseudoTab`'s `rev` entry has
   its dispatch code's low byte equal to ASCII `'0'`, which `util.c`'s
   pseudo-op lookup treats as "not found" unless the undocumented `-t`
   command line flag is given (section 1.4/2.3). A source file using `REV`
   without `-t` gets `"Unrecognized mnemonic: REV"`, not a parse of the
   directive.
3. **Six undocumented command line options** (`-c`, `-j`, `-s`, `-t`, `-w`,
   `-y`) are fully wired into the getopt table and (mostly) into
   `parse_cmdline_opts`'s switch, but never appear in `usage()`'s printed
   text. Must be preserved (accepted, and behave identically) for
   byte-identical output, even though nothing advertises them.
4. **Y2K-style date quirk (observed, not owned by this group).** A test
   run on this machine (whose clock reads 2026) produced a listing header
   dated `126-09-23` (see `re/notes/ASM56000/scratch_g1_main/out.txt`, line 1:
   `... Version 6.3.0   126-09-23  14:42:45 ...`). The century digit is
   simply missing (`year - 1900` printed without a `+ 1900`/`% 100` fixup).
   The date-formatting code itself is in listing.c (another group's module);
   flagged here because it was discovered incidentally while exercising this
   group's command line/pass-control code with `re/bin/ASM56000.EXE` and
   must be reproduced byte-for-byte by whichever group owns listing.c's date
   routine.
5. **Triplicated `AbsMode` flag.** `-a` is mirrored into three separate bytes
   (`AbsMode`/`AbsMode2`/`AbsMode3`, section 1.8) that are always written
   together; looks like straightforward (if redundant) original-source
   behaviour rather than a bug, but must be kept as three separate globals
   (each may be read by a different other module) rather than collapsed into
   one, in case some module's initialisation order depends on all three
   existing independently.
6. **`chk_line_end` is a no-op.** `input.c`'s `chk_line_end` (0x0041a444)
   scans for a blank character but always returns 1 regardless of outcome -
   likely a vestige of a stricter check in an earlier revision; reproduce the
   scan (it has no side effects either way) but do not add new validation
   behaviour, to keep output identical.
7. **`-s`'s effect is unresolved.** The 43-entry `ClassCodeTab` (1.6) is
   validated against but never consumed anywhere in dspasm.c/error.c/input.c;
   flagged as an open question for whichever group's code (most likely
   procop/encode, given the errata-ID-like naming) turns out to read it.

---

## 8. Open questions for other groups / centralized resolution

- Exact bit-level meaning of the instruction table's `f1..f4` fields (1.1) -
  procop.c/encode.c territory.
- Exact bit-level meaning of `error.c`'s 14 `enc_*` dual-operand encoders -
  same.
- Whether `ClassCodeTab` (`-s` option, 1.6) is consumed anywhere at all, and
  if so by which module.
- `OptFlagF7b0` (0x0044f7b0) and `OptMsw` (0x0044f7a4) - OPT ids `0x2d`/`0x2e`
  vs `0x37`/`0x38` weren't both nailed down with full certainty against the
  table dump; worth a second pass if another group needs the exact OPT name.
- Confirm final naming for `AbsMode2`/`AbsMode3` once the modules that
  actually read them (object.c/listing.c/section.c) are analysed by their
  owning groups.

---

## Summary

- **Functions named:** 18 (asmglb math wrappers) + 33 (dspasm.c) + 24
  (error.c) + 20 (input.c) = **95** functions, all in
  `re/names/ASM56000/g1_main.names.txt`.
- **Globals named:** 9 mchglb-owned table bases/counts + ~40 asmglb-owned
  table bases/counts/scalars + ~35 shared/bss pass-and-I/O-state globals =
  **~84** entries (a curated subset of the hundreds referenced by these
  modules; the ones central to command line parsing, pass control, error
  reporting and line input were prioritised per BRIEF.md's "work carefully
  rather than exhaustively" guidance).
- **Major tables fully documented:** instruction mnemonic table (142x20B),
  register name/mask table, processor table (7x8B), revision table (4x12B),
  pseudo-op table (75x8B), OPT/-o name table (92x8B), error-class code table
  (43 pointers), expression function table (54x16B).
- **Structs found:** DO-loop stack frame, input-mode stack node, table
  element layouts for all eight tables above.
- **Command line:** full usage banner, getopt-string-driven option scanner
  documented letter-by-letter (including 6 undocumented options: `-c -j -s
  -t -w -y`), `DSPASMOPT`/`-f` command-file expansion mechanism, and all 92
  `-o`/`OPT` suboption names with their dispatch ids.
- **Pass structure:** documented end-to-end for both the default and
  hidden-`-c`-mode drivers, including precisely what state resets between
  pre-pass/pass 1/pass 2 and what carries over.
- **Open questions:** left in section 8 for centralized resolution.
