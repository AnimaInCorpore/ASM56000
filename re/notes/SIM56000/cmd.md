# SIM56000.EXE - group "cmd": state, cmdloop, macro, fmt, console, dispval

Sources: `re/out/SIM56000/mod/{state,cmdloop,macro,fmt,console,dispval}.c`, names in
`re/names/SIM56000/cmd.names.txt`. Addresses are VAs. Ghidra `local_NN` are offset by 4.
The filemap module boundaries are approximate; the module names used here follow the real content:

| filemap module | real content |
|---|---|
| state 0x4340f0-0x438fff | device create/destroy, chip cycle hooks, **save/load state**, path search |
| cmdloop 0x439000-0x439f9f | interactive line editor (`cmd_read_line`), command completion, command stack, prompt |
| macro 0x43a470-0x43aff0 | macro (command) file reader, overwrite prompt, memory-tag add, **disassembly line formatter** |
| fmt 0x43b5a0-0x43c2ef | **command dispatcher `cmd_execute`**, address range maps, register value formatting |
| console 0x43c2f0-0x43df00 | **register/memory display painter**, **output/log path**, Win32 console, scrollback, arena |
| dispval 0x43f010-0x43fe20 | watch value formatting, two source-line helpers (`src_find_line`, `addr_to_srcline`) |

## 1. Program skeleton (main @ 0x401000, other group's file but needed to read this one)

```
sim_init_tables();                   /* 0x439000: console_open + build reg-index tables of all chip types */
dev_create(0, "56001");              /* device 0 is always a 56001 */
gui_mode = 0;  out_text(banner, 1);  /* "MOTOROLA DSP56000 SIMULATOR:  VERSION 6.3.0 01-15-1999" -> screen AND session log (none open yet) */
if (argc > 1) cmd_execute(0, argv[1]);         /* one command line, e.g. "quit" */
for (;;) {
    pick device iVar3 (current device if still alive & not stopped, else first live device not stopped;
                       dev_select-like: cur_dev_index=run_dev_index=i, scrollback_end(i))
    if (i < 32) {
        if (!macro_active || (macro_read_line(i, buf), !macro_active))   /* macro first */
            cmd_read_line(i, buf);                                        /* interactive editor */
        cmd_execute(i, buf);
    }
    for each live device whose dev+0x44 bit 0x20 is clear: dev_housekeeping(i);   /* per-cycle stage hooks */
}
```
There is no explicit "quit" test in main; the `quit` handler (0x447a00) ends the process. `dev_housekeeping`
(0x438a30) = `dev_cycle_begin`, `_stage1`, `_stage2`, `_end` which call the chip's peripheral hooks
(`chip+0x4e4` vtable: [+4] begin, [+8] stage1, [+0xc] stage2, [+0x10] end, [+0x18] misc(dev,phase)), copy the 0x25
peripheral words to the "previous" copy (`periph+0x94`), bump `dev+0x20` (cycle counter) and set `dev+0x44 |= 0x10`
when `FUN_004524d0` (run.c) reports something.

## 2. THE OUTPUT / LOG PATH (what the plain front end must reproduce)

Everything the user sees goes through three functions in console.c. All take a C string that may contain
`{` `}` highlight markers (produced by the *callers' format strings*, e.g. `"The current default radix is {%s}."`,
`" pc= {$0100}"`, `"{Error text}"`, `"Logging session to:{%s}"`; nothing else generates braces).

```
out_line(line, nocmdlog, plain)                         0x43d200   (the sink)
  out_text(line, nocmdlog)   = out_line(line, nocmdlog, 0)   0x43d3a0   normal output line (braces = highlight)
  log_echo(line, nocmdlog)   = out_line(line, nocmdlog, 1)   0x43d1e0   echo of a *command line* (braces are literal)
```
`out_line` does, in this order (only if `cur_state != 0`):
1. Append `line` (strncpy 0xff) to the per-device scrollback ring `state+0x3fbc` (100 lines x 256 bytes; head, scroll offset, buffer).
   If `!plain`: convert in the ring copy `$` followed by `{`/`}` -> literal brace (escape), `{` -> attribute byte 0x0f (bright), `}` -> 0x07;
   the ring/screen therefore show no braces, but **the log gets the raw `line`**.
2. If this device is the current one and view mode `state+0x4400 == 0`: repaint (`scrollback_move`), and if `more_flag` (`more on`):
   count lines in `more_line_count` (reset to 0 by `cmd_execute` for each command) and after `text_rows` (21) lines print
   `{More: Type any key to continue.}` + TAB (prompt on the bottom status line, key via `key_get`); key 3 (Ctrl-C) sets `abort_flag` (aborts the
   listing: `abort_check()` returns it and sets `dev+0x48=1`).  In the plain front end: `more` is a no-op unless you want to page.
3. **Command log** (`log c file`): `if (nocmdlog == 0 && cmdlog_fp) { fprintf(cmdlog_fp,"%s\n",line); fflush; }`
4. **Session log** (`log s file`): `if (state->session_fp) { fprintf(state->session_fp,"%s\n",line); fflush; }` - always, with the raw line
   (braces included, exactly as in the test transcripts, e.g. `  a=     {$00000000123456}`).
   `state+0x48` = session log FILE*, `state+0x4c` = its name (set by the `log` handler 0x449e90..0x44a550: cases 's'/'c'; strings
   "Logging session to:{%s}" @0x4cb918 / "Logging commands to:{%s}" @0x4cb930 are printed with `out_text(..,1)` right after the file
   was opened - which is why they are on the screen but *not* in the log being opened; `log off` prints `log off` echo before closing).
   `cmdlog_fp` is the global `DAT_004a90d8` (name buffer `004a90dc`).  Both files are opened with fopen (text), so `\r\n` on Windows.

Which callers pass `nocmdlog`: command echo `cmd_execute` -> `log_echo(line, macro_active ? 1 : 0)` (so *command log* records only typed commands,
never macro-driven ones); all normal output `out_text(x, 1)` (i.e. never into the command log). `out_line(...,0)` for output is essentially unused.

Consequences for the transcript (verified with condrive.py + golden logs):
* every executed command line is echoed first (`log_echo`) - **as it stands in the edit buffer after command completion** (see 3.2): a typed
  `eval $ff` becomes `evaluate $ff`?  Observed (fresh run): typing `eval $ff` + Enter logs `evaluate $ff`, and `ev f .5` logs `evaluate f .5`
  (space key triggers `cmd_complete`, which replaces the first word by the full command name).  The old golden `s01` shows `eval $ff`
  unexpanded - it was recorded with different timing/keys; re-record before trusting it.  **`abbrev` first words that exactly equal the
  abbreviation (e.g. `d`, `e`, `st`) are also expanded** (abbrev match is tried first, then unique-prefix over the full names, in table order).
  When a line comes from a macro file or argv[1] no completion happens: the text is echoed exactly as read (trimmed/filtered, see 5).
* The `log ...` command line that *opens* a log is not in that log (file did not exist yet); `log off`'s echo is (flushed before close).
* The prompt (`0>`), the help/status lines (2 rows below the prompt) and `{SIMULATION IN PROGRESS...}` are drawn with `screen_write`
  only - **never logged**.
* Errors: `FUN_0045d2b0` (expr/misc module) = error(text): `state+0x4400=0; copy text to status1_buf; out_text("{%s}", 1)` (so the log gets
  `{message}`), screen flush; if `macro_active && quit_on_error` it runs `cmd_execute(cur_dev_index,"quit ;on error")`.
* Sequence `text\n` per line, no trailing blank lines. The final `disasm_line` line of `display_all` (section 6) ends every `display`.

### 2.1 Screen model (only needed for the original UI; the retro port needs none of it)
80x24 (`screen_cols`=0x50, `screen_rows`=0x18, `text_rows`=`rows-3`=21): text area rows 0..20 (circular, `screen_top_row`),
row 21 = prompt/edit line, 22 = status line 1 (`status_line1`, command syntax hint), 23 = status line 2 (`status_line2`, key help).
Buffers: `screen_char_buf` (0x101 bytes/row: char + NUL), `screen_attr_buf` (0x100/row: attribute 7 normal, 0xf highlight),
`screen_charinfo_buf` (CHAR_INFO array for `WriteConsoleOutputA`). `screen_hold_cnt` = nesting counter of `screen_hold/release`;
`screen_flush` (0x43d9f0) converts buffers to CHAR_INFO (highlight attr = `DAT_004e9044`) and writes the whole screen. `screen_puts_attr(s, mode)`:
mode 1 = interpret `\a` (attr 7) and `\x0f` (attr 0xf) control chars, mode 2 = plain attr 7, mode 3 = interpret `{`/`}`/`$`-escapes, mode 0 = plain highlighted.
`console_open` (0x43cd00): needs NT (`GetVersionEx` platform 0 -> exit), title "Motorola DSP", creates a private screen buffer,
window size clamp 255x99, Ctrl handler + SIGFPE handler. `console_close` restores.  `no_console` (0x4aab9c) is never set.
`key_get` (0x43d840): blocks on `ReadConsoleInput`; KEY_EVENT down: if vk==0 or `vk_to_editkey[vk]==0` returns the ASCII char (`uChar`), else the
mapped edit code; WINDOW_BUFFER_SIZE event -> `console_set_size`; FOCUS event -> redraw. `vk_to_editkey` (0x4e8c40, index = VK code, filled lazily on
first call): BACK->8, TAB->9, CLEAR->0x1a, CANCEL(Ctrl-Break)->3, LEFT->0x0c, RIGHT->0x12, UP->0x14, DOWN->0x16, PRIOR(PgUp)->0x15, NEXT(PgDn)->0x0e,
INSERT->0x0f, DELETE->0x0b, ESC->0x1b, SPACE->0x20.  (Also VK 1,2 -> 0x0c,0x12.)

## 3. Command dispatcher

### 3.1 `cmd_execute(dev, line)` @ 0x43b5a0 (fmt.c) - the only place commands are run
```
cur_dev = dev_tab[dev]; cur_chipui = chipui_tab[cur_dev->chiptype]; cur_chip = chiptype_tab[cur_dev->chiptype]; cur_state = dev_state_tab[dev];
entry = cmd_parse(line, 0);          /* FUN_0046a2d1 (cdbsym.c): tokenise + look up + per-command parse; NULL = no/invalid command */
more_line_count = 0;  screen_hold();
log_echo(line, macro_active != 0);   /* transcript echo, see 2 */
if (entry) (*(void(*)(char*))entry[0])(line);    /* run the handler (handler re-reads the tokens from cmd_tokbuf) */
if (macro_active) screen_flush();
```
`cmd_parse(line, mode)` (Ghidra dropped `mode`): copies `line` into `cmd_tokbuf` (0x4a91e8: +0x000 lower-cased copy split into NUL separated tokens,
+0x100 original-case copy, +0x201.. token kind bytes `'e'` end, `';'` comment, `'u'` unknown/argument, +0x280 = token count, +0x284.. = token start offsets,
+0x4b0 = command index once recognised). Token rules: blanks separate; `"..."` quoted token; `{...}` block with `\` escapes and `'`/`"` inside;
`;` starts a comment.  `FUN_00467fa9(1)` matches token 1 against `command_table` (39 entries, exact abbreviation or unique prefix) and stores the index;
then it calls the **command's parse function** `entry[5]`, which validates the argument tokens (`FUN_004682ea(n)` = token n present,
`FUN_00469d42(n,str)` = token n equals str) and returns a pointer into the command's **handler table**
(`&handlers[variant*8]`, 8 bytes each = `{ void (*handler)(char *line); unsigned long flags; }`) or NULL on a syntax error.
Comment lines (`;...`) return `&PTR_FUN_004d3718` = {0x46a2cc (empty fn), 0}; a bare macro-file name (token matches a `.cmd` file) returns
`&PTR_LAB_004d3720` = {0x43a3f0 `macro_run_named`, 0}; that handler builds `<name>.cmd` via `path_search(name, ".cmd", out)` and calls `macro_push(out)` (and
`cmdstack_push(line)` when no macro is active).  Called with `mode==1` (Enter key in the editor) the same function only checks syntax; a NULL result means
"do not execute, keep editing" (see 4); invalid lines therefore never reach the transcript when typed interactively.  `flags` bit 0 of the returned entry:
handler is one of the "interactive" ones (asm/change with no operands) - `macro_read_line` returns to the main loop after such an entry only if bit 0 is clear.

### 3.2 Command table `command_table` (0x4a8c90, 39 pointers, count `num_commands`=0x27 @0x4a8db8)
Entry record (each in .data next to its help text): `{ char *name /*e0*/; char *abbrev /*e1*/; char *usage_name /*e2*/; char **help_lines /*e3, status-line-2 hints*/;
char **arg_help /*e4*/; int (*parse)() /*e5*/; int f1; int f2 }`. `f1` (0/1/2) and `f2` (0/1) are only used by the completion/help code (0=no operand hint,
2=operands expected; f2=1 the command accepts the plain first word without operands) - low confidence.
Handler variant tables lie immediately *before* each entry (`entry-8*n`), listed below. `module` = filemap module of that address (approximate; all
0x43e8b0-0x454590 handlers belong to other groups' files: cdbglue/dispval, iohist, help, run, profile, tail...).


Command purposes (from the help strings / usage; the handlers themselves are described by the groups that own those address ranges):
asm = inline assemble (`a [b] [addr] [instr]`); break = breakpoints (variants: set/clear/list/`off`/`test.asm@9` file:line/`main`); change = write registers/memory;
copy = memory copy; device = list/select/enable simulated devices `DVn`; disassemble; display = registers/memory display list (`on/off/r/w/rw`, `l` labels, `v` version);
down/up/frame/where = C call-stack navigation; evaluate (`e [b|d|f|h|u] expr | ${C expr$}`); finish; go; help; history; input/output = pin/port/memory I/O
streams; list; load (`s` state, `m` memory only, `d` debug symbols only); log; more; next/step/trace/until; path; quit (`q`, `qe`=quit on error on, `qd`=off:
handlers 0x4479e0 / 0x4479f0 set `quit_on_error` 1/0, 0x447a00 quits); radix; redirect; reset (`s` state -> `dev_reset`, `d` device -> `chip_reset_regs(1,..)`);
save (`s` state -> `save_state`, or memory blocks to an OMF `.lod`); streams; system; type; unlock (stub, handler 0x43ce80 = empty fn); view; wait (seconds);
watch (add/delete/list); `more` handlers: 0x449e20 sets `more_flag=1`, 0x449e30 sets `more_flag=0`; `streams`: 0x446580/0x446590 set/clear `state+0x404c` (hio enabled).
`more_flag` and `overwrite_mode` start at 0.  Handler table (`addr:flag`):

| # | command | abbrev | entry | parse fn (module) | f1 f2 | handler variants addr:flag (module) |
|---|---|---|---|---|---|---|
| 0 | asm | a | 4d18a0 | 454590 (profile) | 1 0 | 453ef0:1(run) 454400:0(profile) |
| 1 | break | b | 4d0708 | 453b30 (run) | 2 0 | 453100:0(run) 4534f0:0(run) 453820:0(run) 4539f0:0(run) 4538d0:0(run) 453960:0(run) |
| 2 | change | c | 4cfed8 | 4523c0 (run) | 2 0 | 451160:1(help) 451900:1(help) 452030:0(run) |
| 3 | copy | co | 4cfb28 | 451120 (help) | 1 0 | 450fd0:0(help) |
| 4 | device | de | 4cf668 | 450f00 (help) | 0 1 | 450b10:0(help) 450cd0:0(help) 450df0:0(help) 450d90:0(help) 450e70:0(help) 450e10:0(help) |
| 5 | disassemble | di | 4cf1f8 | 450ac0 (help) | 2 0 | 4507c0:0(help) |
| 6 | display | d | 4ce7e0 | 4506c0 (help) | 2 1 | 4506a0:0(help) 44fe90:0(help) 450210:0(help) 450550:0(help) 450650:0(help) 450680:0(help) 450690:0(help) |
| 7 | down | do | 4ce550 | 44fe50 (help) | 2 0 | 44fd30:0(help) |
| 8 | evaluate | e | 4cdea8 | 44fc60 (help) | 2 0 | 44f160:0(help) |
| 9 | finish | f | 4c70c8 | 4457f0 (coffrd) | 2 0 | 445750:0(coffrd) |
| 10 | frame | fr | 4cdc90 | 44f120 (help) | 2 0 | 44f020:0(help) 44f070:0(help) |
| 11 | go | g | 4cd718 | 44eee0 (help) | 2 0 | 44ed20:0(help) |
| 12 | help | h | 4cc8e8 | 44ec10 (help) | 1 1 | 44d670:0(help) 44eb90:0(help) 44e720:0(help) 44e9f0:0(help) 44ea70:0(help) |
| 13 | history | hi | 4cc4f8 | 44d140 (help) | 2 0 | 44ceb0:0(iohist) |
| 14 | input | i | 4cbf20 | 44cc80 (iohist) | 2 0 | 44acd0:0(iohist) 44ae80:0(iohist) 44c340:0(iohist) 44c8d0:0(iohist) |
| 15 | list | li | 4c7078 | 445500 (coffrd) | 0 0 | 445290:0(coffrd) 4452d0:0(coffrd) 445310:0(coffrd) 445350:0(coffrd) 445410:0(coffrd) |
| 16 | load | l | 4cba78 | 44abf0 (iohist) | 2 0 | 44a870:0(iohist) 44a7a0:0(iohist) 44ab00:0(iohist) 44aa20:0(iohist) |
| 17 | log | lo | 4cb4c8 | 44a560 (iohist) | 2 1 | 449e90:0(iohist) 44a1d0:0(iohist) 44a3b0:0(iohist) 44a540:0(iohist) 44a550:0(iohist) 449fe0:0(iohist) 449f80:0(iohist) |
| 18 | more | m | 4cb2d8 | 449e40 (iohist) | 0 1 | 449e20:0(iohist) 449e30:0(iohist) |
| 19 | next | n | 4c6ec0 | 444900 (coffrd) | 2 0 | 4447b0:0(coffrd) 444860:0(coffrd) 444880:0(coffrd) 4448a0:0(coffrd) 4448c0:0(coffrd) 4448e0:0(coffrd) |
| 20 | output | o | 4caaa0 | 449bb0 (iohist) | 2 0 | 447f50:0(symdisp) 4480b0:0(iohist) 4481a0:0(iohist) 448730:0(iohist) |
| 21 | path | p | 4ca720 | 447eb0 (symdisp) | 2 1 | 447ba0:0(symdisp) 447c70:0(symdisp) 447e90:0(symdisp) 447d30:0(symdisp) |
| 22 | quit | q | 4ca4f8 | 447b30 (symdisp) | 0 1 | 447a00:0(symdisp) 4479e0:0(symdisp) 4479f0:0(symdisp) |
| 23 | radix | r | 4ca118 | 447980 (symdisp) | 2 1 | 447720:0(symdisp) 447770:0(symdisp) |
| 24 | redirect | red | 4c9b80 | 447630 (symdisp) | 2 1 | 4472d0:0(symdisp) 4474c0:0(symdisp) 447560:0(symdisp) |
| 25 | reset | re | 4c9898 | 447270 (symdisp) | 2 1 | 447230:0(symdisp) |
| 26 | save | s | 4c9548 | 447170 (symdisp) | 1 0 | 446b50:0(symdisp) 446c50:0(symdisp) |
| 27 | step | st | 4c90b0 | 446910 (symdisp) | 2 0 | 4466a0:0(symdisp) 446760:0(symdisp) 4467c0:0(symdisp) 4467f0:0(symdisp) 446820:0(symdisp) 446850:0(symdisp) 4468b0:0(symdisp) 4468e0:0(symdisp) |
| 28 | streams | str | 4c8d58 | 446600 (symdisp) | 2 0 | 446580:0(symdisp) 446590:0(symdisp) 4465a0:0(symdisp) |
| 29 | system | sy | 4c89d8 | 446510 (symdisp) | 0 1 | 4462c0:0(symdisp) 446310:0(symdisp) 446440:0(symdisp) |
| 30 | trace | t | 4c83d8 | 446080 (symdisp) | 2 0 | 445e10:0(coffrd) 445ef0:0(coffrd) 445ed0:0(coffrd) 445fe0:0(coffrd) 446040:0(symdisp) 446060:0(symdisp) 446000:0(symdisp) 446020:0(symdisp) |
| 31 | type | ty | 4c8138 | 445dd0 (coffrd) | 2 0 | 4459e0:0(coffrd) |
| 32 | until | u | 4c6f50 | 444f00 (coffrd) | 2 0 | 444e10:0(coffrd) 444ee0:0(coffrd) |
| 33 | unlock | un | 4c7fc8 | 445970 (coffrd) | 0 1 | 43ce80:0(console) |
| 34 | up | up | 4c7e70 | 445930 (coffrd) | 2 0 | 445810:0(coffrd) |
| 35 | view | v | 4c6fc0 | 445030 (coffrd) | 0 0 | 444f60:0(coffrd) |
| 36 | wait | w | 4c6b28 | 43fdb0 (dispval) | 0 1 | 43fd20:0(dispval) |
| 37 | watch | wat | 4c6660 | 43fa30 (dispval) | 2 0 | 43e9e0:0(cdbglue) 43ebe0:0(cdbglue) 43ec30:0(cdbglue) |
| 38 | where | wh | 4c6408 | 43e8b0 (cdbglue) | 2 0 | 43e750:0(cdbglue) 43e7c0:0(cdbglue) |

Notes: the `quit` parse fn (0x447b30) shows the pattern: token 2 absent -> variant 0, token 2 == "e" -> variant 1, "d" -> variant 2, else NULL (syntax error).
`f`lag column: only `asm` (0x453ef0) and `change` (0x451160, 0x451900) have flag 1.

## 4. Interactive line editor (cmdloop.c) - not needed by the plain front end except for `cmd_complete`

* `cmd_read_line(dev, out)` @ 0x439410: sets cur_* from `dev`, `screen_hold_cnt=1`, `prompt_show()`, then loops on `key_get()`; edit buffer `cmd_linebuf`
  (0x4a8fd4, 256 bytes), cursor `iVar13`, max width = `screen_cols - strlen(prompt)-1`. Prompt text `"%d>"` (0x4c5fbc) with the *current device number*, in `prompt_text` (0x4aaa98).
  Keys (code -> action): 2 (^B)/6 (^F) command stack forward/back (`cmdstack_buf`, 10 lines x 256, `cmdstack_size`=10; recalled line copied to a temp then stuffed key by key: each
  char re-fed through the same switch as if typed, then it re-enters the loop with `bVar2`); 5 (^E) end of line; 8/0x7f backspace (does not delete into the auto-completed
  command word once `bVar3` set); 9 (^I) next word; 0x0b (^K) delete char at cursor; 0x0c (^L) cursor left; 0x12 (^R) right; 0x0e/0x14/0x15/0x16 scrollback
  (^N/^T/^U/^V: line/page up/down through `scrollback_move`, or `FUN_00442e10` in view modes 1/2); 0x0f (^O) toggle `overwrite_mode`; 0x17 (^W) cycle `state+0x4400` view mode
  (0 console / 1 / 2 windows); 0x1a (^Z) delete to eol; 0x1b (ESC) clear line; 0x20 (space): if line empty -> `prompt_help_cycle(1)` else first space triggers **`cmd_complete`**,
  later spaces insert (or cycle help if previous char was blank); 0x3f `?` : if the number of `{` before the cursor equals the number of `}` -> show help for the
  command (`FUN_0044d390(entry)` help.c) or generic (`FUN_0044d160`), otherwise insert `?` (inside `{ }` C expression); 0x0d (CR): `cmd_parse(line,1)`;
  NULL -> `cmd_error_position` (moves cursor to the failing token); else `cmdstack_push(line)`, `abort_flag=0`, `cur_dev+0x48=0`, copy line to `out`, return.
  Ctrl-C (3) handled inside `key_get` (returns 3, Ctrl-Break VK 3 too).  Printable chars: insert at cursor (or overwrite).
* `cmd_complete(line)` @ 0x4391f0: lower-cases a copy (`str_tolower`), scans `command_table`: exact match against `abbrev` (e1) first, else `strncmp(prefix, name)`
  against `name` (e0) in table order -> first hit wins; on hit **overwrites the buffer with the full `name`** and sets the status-line-2 help text
  (`help_lines_cur = entry[3]`), redraws; on miss uses pseudo entries `"comments"` (0x4c5d7c) if the line starts with `;` else `"macros"` (0x4c5d88) (help
  texts `{;}comment string entry`, `{Macro filename}`) and leaves the text unchanged. Returns `entry[2]` (usage hint string for status line 1). Ghidra shows the
  `strcpy`-style copy loops; the copy is of `entry[0]`.
* `cmdstack_push` @ 0x439360: no-op if equal to the newest entry, else shift entries down and store at slot 0 (`cmdstack_size`=10).
* `prompt_show` @ 0x439d80: resets help state (`help_mode=0, help_index=0, help_lines_cur=default_help_lines(0x4a8d30)`, alt list = key help `{^U}=ln-up...`
  strings 0x4c5cxx-0x4c5exx), prints prompt `n>` at row 21, clears status lines.  `status_line1/2` write the hint lines (screen only).
* `memmap_find(space, addr)` @ 0x439080: index of the chip memory *region record* (chip+0x20 array, 0x2c bytes each: +4 space id, +0xc lo, +0x10 hi, +0x18 flags
  (0x20000 = this space has more regions), +0x20 name/id, +0x30 space) that holds `addr` in `space`; first candidate `chip+0x4c + space*4` (filled by `sim_init_tables`),
  address masked to 16 bits when the chip flag word (`chip+0xc` or hook `chip+0x4e8()`) has bit 0x800.  Used by `disasm_line`, register/memory code.
* `sim_init_tables` @ 0x439000: `console_open()`; for every chip type: fill `chip+0x4c .. +0x4dc` (0x134 dwords) with -1, then for regions from last to first store
  region index at `chip+0x4c + region.space*4` so each space points to its *first* region.

## 5. Macro files (macro.c)

State: `macro_active` (0x4a91dc), `macro_fp` (0x4a91e0, FILE*), `macro_stack` (0x4a91e4): singly linked stack of nodes 0x108 bytes: `+0 char name[0x100]`,
`+0x100 long saved_ftell`, `+0x104 next`. Nested macros are supported (push saves ftell of the current one).
* `macro_push(name)` @ 0x43a6a0: save ftell/fclose current, alloc node, `fopen(name,"rb")` ("rb" 0x4c5ff4); failure -> error `"Error opening macro file"` (0x4c5ff8),
  `macro_abort_all`. 
* `macro_pop` @ 0x43a610: fclose; pop node; reopen previous (`"Error opening macro file:"` 0x4c5fd8 on failure), fseek to saved pos.
* `macro_read_line(dev, out)` @ 0x43a470 (called by main while `macro_active`): if `abort_check()` -> `macro_abort_all`. Otherwise read chars with `FUN_004842c0` (getc) into `out`:
  skips leading whitespace (`isspace`), keeps only printable/graph chars (ctype mask 0x157) and TAB, max `0x100 - strlen(prompt)` chars; on `\n` -> `cmd_parse(out)`
  (mode 0): NULL -> error `"Error in Macro"` (0x4c5fc8), `log_echo(out,1)`, `macro_abort_all`; else returns to main (the line is executed by `cmd_execute`)
  **unless the entry has flag bit0 set**, in which case it reads on. EOF -> `macro_pop`; empty stack -> return with `macro_active=0`.  Comment lines (`;`) are
  returned like commands (their handler is a no-op) and are echoed to the log.
* `confirm_overwrite(file, mode)` @ 0x43a7c0: if `access(file)==0` (does not exist) -> 0 (=overwrite/create); `mode`: 0 = ask (screen: status line
  `"A file with the same name currently exists - Enter a character:"` + `{a = append, o = overwrite, c = cancel command :}`, key 'a'/'o'/'c', echoed;
  gui: hook returns 'c'), 1 = append, 2 (`-o`) = overwrite, else (`-c`) = cancel. Returns 1 append, 0 overwrite/none, -1 cancel. Used by log/redirect/save/output -a/-o/-c options.
* `show_running_banner` @ 0x43a8b0: on the status line `{SIMULATION IN PROGRESS.} Enter Ctrl-C to Halt. dev:%d pc:%04lx cyc:%lu` (`%06lx` when chip flag 0x200): screen only.
* `memtag_add(flags, region, lo, hi, kind)` @ 0x43a930: adds `[lo,hi]` to the per-region range map list at `state+4 + region*300 + (0x10 if !(flags&1) else 0xc)`
  for every region that belongs to the same memory space as `region`.  Called from the input/output handlers.
* `disasm_line(space, addr, out, arg)` @ 0x43a9d0 - see 6.3.

## 6. Display / formatting (the text of the transcript)

### 6.1 `display_all(with_watch)` @ 0x43c2f0 (called by `display_refresh` 0x43bb50, itself called from run.c after step/go/`display`)
`display_refresh(full)` first recomputes each register's attr word bit 0x800 (visible): `if !(regdesc.flags & 0x10) { if (!(a&0x10) && (!(a&0x20)||!(a&0x40000)) && (!(a&0x40)||!(a&0x80000))) a &= ~0x800 else a |= 0x800 }`
(0x10 = never shown, 0x20/0x40 = display on read/write flag, 0x40000/0x80000 = "was read/written since last display" marks), then `memtag_rebuild` (build `state+4+bank*300+4` display range map from breakpoints/watches/last accessed addresses), then `display_all`.
`display_all`:
1. **Register panel** (for each bank `b` of the chip, `chipui[2][b]` = layout: `{ int nrows; ... ; cell *rows }`, cell = 12 bytes `{ long reg; long total_width; long name_width }`; `reg>=-1` valid, -1 = blank filler of `total_width` columns (tail of the blank string `0x4c5d48`), `reg<-1` ends a row; rows are `nrows` groups of cells; the cell text is right-justified in `total_width`, the name right-justified in `name_width`). For each visible register (attr bit 0x800): name right-justified in `width` (+1 column if the bank has a suffix char: `chipbank+0x30` first char),
   `=`, then value from `fmt_register` right-justified; if attr bit 0x80000 (changed) the value is wrapped in `{ }`.  Rows are trimmed (`rtrim_line`) and emitted with `out_text(row,1)`
   only if some register on the row was visible.  Radix code per register kind from attr bits: 0x4000 -> 3 (hex), 0x1000 -> 1 (decimal), else 4 or 2 (unsigned / fraction depending on 0x8000).
2. **Memory display list** (for each memory space, `state+4+space*300`, list at +4 = display range map): lines `"%s:$%s="`(0x4c6378: space name + address via `FUN_004575c0`) followed by words
   formatted with `FUN_00457630` (mdisk/radix module), wrapped by the mask `local_368`, `{ }` around locations flagged 2; each finished line `out_text(line,1)`; after every `text_rows`
   lines flushes the screen (`abort_check` may stop the listing).
3. if `with_watch` (param nonzero): `FUN_0043e9b0` prints the watch list (cdbglue.c/watch group).
4. **Current instruction line**: `disasm_line(0 /*P space*/, dev->pc /*dev+0x1c*/, buf, 0)` then `out_text(buf,1)` (and a second `out_text` of the tail when the text is longer than the screen width).
Expected text (golden s06): register rows exactly as in the log (`  a=     {$00000000123456}`, `cyc=000000  ictr= 000000 cnt1= ...`) then `p:$0100 000000        = nop`.
The panel geometry (row/column/width per register) is data in the chip descriptor tables (devinit group); see `re/notes/SIM56000/devinit*.md`.

### 6.2 `fmt_register(bank, reg, radix, out)` @ 0x43bec0 (register value text)
`attr = chipbank->regdesc[reg].flags` (`regdesc` = 0x1c bytes: `+0` name, `+8` word offset in the memory-mapped image, `+0xc` bits?, `+0x10` flags/attr, ...).
Reads the value with `FUN_00433f10(dev, bank, reg, long v[3])` (fail -> error `"Error reading register"` 0x4c6178, returns 0).
`radix` 2 = fractional/float (via `FUN_0045a950` -> double, then `"%18.15f"`/`"%13.10f"` (56-bit/48-bit), `"%10.7f"`/`"%6.3f"`/`"%8.5f"` for narrow regs; `"%22.22s"`/`"%12.12s"` of `fmt_float_exp` output when
chip flag bit 7 (0x80: IEEE-ish exponential) is set); `radix` 1 (signed) / 4 (unsigned) decimal: `"%011ld"/"%011lu"` (36-bit-class regs), `"%05ld"`, `"%06ld"`, `"%03ld"`, `"%06lu_%09lu"` for 56-bit accumulators (`FUN_0045d120/1b0` split
into two decimal halves); default (hex, radix 0/3): `"$%0Nlx"` families: `$%06lx`, `$%04lx`, `$%02lx`, `$%08lx`, `$%01lx`, `$%02lx%06lx%06lx` (a/b 56-bit: ext:hi:lo) `$%08lx%08lx%08lx`,
`$%02lx%04lx%04lx`, `$%01lx%04lx%04lx` (16-bit mode `chip flags bit 0x1c`), `$%04lx%04lx`, `$%06lx%06lx`, `$%08lx%08lx`, `$%02lx%06lx`... (selected by chip flags `chip+0xc` bits 0x1c (16-bit), 7 (32-bit),
0xc (extra ext bit), 0x18, and register attr bits 0x1, 0x2, 0x4000000, 0x10000000, 0x2000000, 0x2000, and 0x80000000/0x40000000 (narrow 3 bit / 2 bit regs)).  Output fully reproduced only by copying the branch tree
(`fmt.c` lines 579-790): the C source should copy it 1:1.  Returns 1.
`fmt_float_exp(fmt, dbl)` @ 0x43bd90: emits `NaN`/`Inf` (strings 0x4c621c/6220/6228/622c: signed variants) or `sprintf("%-26.24e")`, then fixes the exponent to 2 digits
(removes the third exponent digit when it is `0`) and returns a pointer to `float_fmt_buf`.

### 6.3 `disasm_line` @ 0x43a9d0
Builds `"%s:$%0<aw>lx %0<ww>lx [%0<ww>lx ...]"`: space name (`chip+0x20 region name`, "p"/"x"/"y"...), address (width `aw`= 4 if 16-bit-address chip flag 0x10000000 else 6; 8 for 32-bit `0x4000000` chips, mask
`uStack_1c8` 0xffff / 0xffffff), then up to 4 opcode words (word width `ww` 6 / 8 / 4, chosen from chip flags 0x8, 0x400, 0x10, 0x2000000) each `%0<ww>lx `, blank filled when the instruction has fewer words;
`(**(chip_disasm_hook+0x10))(words, buf, ...)` produces the mnemonic text; then ` = <text>` (`" ;"` separated comments as selected by `DAT_004dc380` display flags: 0x1 = label (`FUN_00441500(0,..)`), 0x2 = second label, 0x4/0x8/0x10/0x20/0x40/0x80 = source-line, cycle, operand values etc. - see
disasm option table copy at `0x4dc278` (35 dwords copied to `0x4dc308` at each call)).  If the memory read fails the line ends with `" ;*** MEMORY LOCATION DOESN'T EXIST"` (0x4c6150).
Returns the number of program words the instruction occupies (1-4; used by list/asm).  Reads words through `chip+0x28` (memory ops table: `[0]` read fn, `[5]`/`[9]` alternates with a 4th arg; `[0x24]` flag).

### 6.4 `watch_format_value(watch, out)` @ 0x43f010 (dispval.c)
Watch node: `+4` expression text (0x100), `+0x104` kind (2 = C/cdb expression, else simulator expression), `+0x108` radix code (-1 default, 0 = binary, 1 = signed decimal, 2 = fraction/float, 3 = hex, 4 = unsigned decimal;
same codes as `radix`/`evaluate` `B D F H U`: B=0, D=1, F=2, H=3, U=4).  Evaluates with the simulator expression evaluator (`FUN_00459480`, result struct: `+0x8` double? `+0xc,+0x1c` flags
`&2` fract, `&4` 56-bit; `Invalid Expression` (0x4c6ad8) written to `out` on failure) and produces: default/hex: `"$%06lx"`/`"$%08lx"`/`"$%04lx"`, `"$%06lx%06lx"`, `"$%02lx%06lx%06lx"`...; decimal: sign extended
`"%05ld"`/`"%05lu"` (sign bit chosen from result flags 0x80000000..0x4000000) or two-part `"%06lu_%09lu"`; float: `"%10.7g"`/`"%13.10g"` or `"%14.14s"`/`"%25.25s"` of `fmt_float_exp`; binary: nibble table `0x4c6608` ("0000".."1111") concatenated
per hex digit.  `out` gets the concatenation (it appends to `out` after `*out=0`).

## 7. Device / state structures (partial; enough for the port design)

Global tables (pointer *variables* hold the array addresses): `dev_state_tab` (PTR@0x4a8d98 -> 0x4dba88, 32 x `state*`), `dev_tab` (PTR@0x4aab10 -> 0x4dbb08, 32 x `dev*`), `chiptype_tab` (PTR@0x4aab08 -> 0x4aaac8, 13 slots, 10 filled:
56000,56001,56002,56004,56004rom,56005,56007,56009,56011,56012; `num_chiptypes`=13), `chipui_tab` (PTR@0x4a8db4 -> 0x4a8d50: per chip type UI/layout descriptor: `[0]` reg width table, `[2]` register layouts by bank).  `max_devices`=32 (0x4aab0c).
Current pointers: `cur_dev`, `cur_state`, `cur_chip`, `cur_chipui` (0x505798/0x50578c/0x505790/0x505794) set by `cmd_execute`, `dev_select`, etc.

`dev` (0x168 bytes, `FUN_00457e00(0x168,1)` = calloc): `+0` chip type index, `+4` device number, `+8` ptr array[nbanks] of register value arrays, `+0xc` ptr array[nspaces] x 16 bytes (`+8` memory words ptr `(nwords*4)`, `+0xc` disabled flag),
`+0x18` peripheral state array (`chip+0x30` x 0x128 bytes; first 5 dwords = mode words, `+0x14..` 32 aval values `+0x94..` snapshot copy), `+0x1c` pc / exec address, `+0x20` cycle counter, `+0x24` instruction counter, `+0x40` global signals array (`chip+0x2c` dwords), `+0x44` flags (0x20: skip housekeeping; 0x10; 3 = run bits), `+0x48` stop/abort flag,
`+0x58` device working directory (`".\"` default, `path` command), `+0x158` chip hook data.  `state` (0x4408 bytes, calloc): see 8. `chip` (0x4e8+ bytes, in `devinit`): `+0` name, `+0xc` mode flag word (or hook `+0x4e8`), `+0x14` nbanks, `+0x18` bank array (0x48 stride; `+0x2c` -> bank
desc with `+0x24` nvalues, `+0x28` nregs, `+0x2c` reg desc array (0x1c stride: `+0` name, `+8` image offset, `+0xc` size, `+0x10` attr flags, bit 0x80 = memory-mapped alias), `+0x30` suffix char ptr), `+0x1c` nregions, `+0x20` region array, `+0x28` memory ops, `+0x2c` nsignals, `+0x30` nperiph, `+0x34` peripheral init values,
`+0x4c` region index by space (0x134 dwords), `+0x4dc` chip type string saved in state files, `+0x4e0/+0x4e4` optional external-module hooks, `+0x4e8` mode flag hook.

`dev_create(dev, type)` @ 0x435d40: find chip type by name (case-insensitive `str_icmp` over `chiptype_tab`), destroy an existing device in that slot (`dev_destroy`), allocate `state` (0x4408) and `dev` (0x168),
scrollback ring (`state+0x3fbc`: {head,scroll,buf}, buf = `scrollback_lines`(100) x 256), history array (`state+0x3fc8`: `history_size`(32) x 0x2c), register banks (`dev_alloc_regbank`: value array `nvalues*4`, attr array `nregs*4`),
memory maps (`state+4`: `nregions` x 300 bytes; `dev+0xc`: `nregions` x 16 bytes with word arrays), peripherals, signals, and calls `dev_state_init` (0x436bb0: zeroes `state+0xc..+0x3c38`, defaults: `+0x30 = 1` default radix decimal, `+0x404c = 1` hio enabled,
redirect table, FOPEN_MAX flags `+0x43a4 = 1` x3, AFI/UFI table 3 entries `{0,0,..}{1,0..}{2,0..}` (stdin/stdout/stderr), working dir `".\"`, scrollback cleared, peripherals from `chip+0x34`, `chip_reset_regs(1, chip+0x10)`).  `dev_destroy` frees all of it (`fclose(state+0x48)` session log).
`dev_reset(dev,arg)` = clear memory tags, program info, io lists, cdb data, close the session log, `dev_state_init`, optional `**(dev+0x40) = arg` (the `M n` mode of `reset`).

## 8. State file format (`save s` / `load s`) - `save_state` @ 0x4348a0, `load_state` @ 0x436f90

Plain text, `fprintf`/`fscanf`, written with `fopen(name,"w+")` (0x4c59ec; truncates), read with `"r"`. **Section headers are ignored by the loader** (it skips them with `" [%[^\n] "`, i.e. one line beginning with `[`, so
the order is fixed; the loader does not compare header names).  Strings are stored as a line `^<text>` (a literal `^` prefix, read back with `" ^%[^\n]"`), empty string as `0\n^\n`? see below.  `%lx` values are unsigned hex without `0x`.
Reading fails (returns error = 1) if the first int is not 0x2c7 or a device/type index is out of range or a `malloc` fails; the dev/state of failed loads are destroyed and `dev_create(0,chiptype[0].name)` is recreated.

Layout (all `\n` separators as in the format strings; `%d\n` = 0x4c59d4, `\n%d` = 0x4c5740, `\n%lx` = 0x4c5934):
```
%d\n                       version 0x2c4 written first, at the end the file is rewound and overwritten with 0x2c7 ("%d") -> a truncated save is unloadable
\n[MOTOROLA DSP56000 SIMULATOR:  VERSION 6.3.0 01-15-1999]\n      "\n[%s]\n" with the banner string
\n[source_path]\n          then "%d\n^%s\n" (strlen, list) or "0\n^\n" when the source path list is empty
\n[profiler]\n             then "%s\n" of: profiler file name derived from the profiler hook (when profiler_hook != 0 and a free "pf" name), else "(null)\n"
\n[numdevices]\n%d\n       (last_dev-first_dev+1)
for each device i (first..last):
  \n[devindex devtype]\n   "%d %d\n" (index, chip type index)   or, when the chip type has +0x4dc string: "%d -2\n^%s\n^%s\n" (index; chip name; +0x4dc string)
  (skipped when the slot is empty; the loader then aborts after this header)
  \n[perattr]\n            per bank: "\n%lx" bank perattr word then "\n[regattr]" block, then "\n[regval]"  (the three section headers repeat for every bank)
     [perattr]: "\n%lx"  [regattr]: nregs x "\n%lx"   [regval]: nvalues x "\n%lx"
  chip mode hook is called (result unused)
  for each memory region (chip nregions):
     \n[mem disabled]\n "\n%lx"  (dev+0xc[region]+0xc)
     \n[memval]\n       nwords x "\n%lx"  (region+0x14 words of dev+0xc[..]+8)
     \n[memory display tags]\n  4 range lists written by save_maplist: state+4[region*300 + 0, 8, 0x10, 0xc]:
                           "\n%d" count, then count x "\n%d %lx %lx" (kind? , lo, hi; node = {int a, lo, hi, next}, 0x10 bytes)
  \n[global signals]\n     chip+0x2c x "\n%lx"
  \n[port values]\n        per peripheral (chip+0x30): "\n%lx x10" (mode words 0..4, +0x94.., +0x9c,+0xa0,+0xa4) "\n" then
                           \n[analog pc.aval values]\n 32 x "%lx "   \n[analog pp.aval values]\n 32 x "%lx "   (separator "\n"), (the loader reads them with " %lx")
  \n[reg_exec,reg_cycl,reg_icnt,flg_stat]\n   "\n%lx %lx %lx %d %d"  = dev+0x1c, +0x20, +0x24, +0x44, +0x48
  \n[sv_var.stat]\n        "\n%d %d %lx %lx %d %d %d %d %lx %d %d %d %d %d %d\n^%s\n" = state+0x3c34, +0x184, +0xc, +0x10, +0x18, +0x1c, +0x20, +0x24, +0x28, +0x2c, +0x30 (default radix), +0x34, +0x40, +0x44,
                           (state+0x48 != 0)  [session log open flag], then "^"+state+0x4c session log file name; the loader re-opens that log with fopen(name,"a+") when the flag is set
  \n[pathwork]\n           "^%s\n" dev+0x58
  \n[counters and history]\n  "\n%lx %lx %lx %lx %lx %d %d " = state+0x15c,+0x160,+0x164,+0x168,+0x3fc0,+0x3fc4,+0x4400
  \n[histsz and hist log]\n "\n%d\n" history_size(32) then per entry "\n%lx" + 10 x " %lx"  (0x2c-byte instruction history record)
  \n[breakpoint count]\n   "\n%d"
  \n[breakpoint info]\n    per breakpoint (list state+0x3e78, node 0x250 bytes, next at +0x240):
                           "\n%d %d %d %d\n^%s\n^%s\n%d %lx %lx %lx %d %d %d %d" + (+0x10 text, +0x110 text, ids +0..+0xc, +0x210.. ) then
                           " %hu %hu ..." variants; if node type (+4) == 12 (C-expression breakpoint): the expression tree via save_expr_tree + "\n%d %d" (+0x248,+0x24c)
  \n[watch list]\n         "\n%d" count then per watch (node 0x124, next +0x120): "\n%u\n^%s\n%d %d %lu %lu" (id, text, kind, radix, +0x10c, +0x110);
                           if kind == 0 the compiled expression tree follows (save_expr_tree) + "\n%d %d" (+0x11c,+0x118)
  \n[hio enabled]\n        "\n%d" state+0x404c
  \n[send buffer]\n        "\n%d %lu %lu" (+0x4050,+0x4054,+0x4058) then count x "\n%ld" ; \n[recv buffer]\n same for +0x4060..
  \n[send address recv address]\n  "\n%d %lu" x2 (+0x4074,+0x4070) (+0x407c,+0x4078)
  \n[afi ufi]\n            "\n%d %d" (+0x4088 count,+0x4084)  then per file (0x10 bytes at +0x4080): "\n%d %d" flags, then "\n0" or "\n^%s" name + "\n%ld" file position (lseek); files are re-opened on load with _open flags & ~0x200
  \n[redirect flag, filename, fileposition]\n   3 x { "\n%d" flag(+0x408c+4i), "\n^%s" name (+0x40a4+i*0x100), "\n%ld" ftell or "\n0" }; stdin/stdout/stderr redirection is re-established on load (fopen "r" for stdin, "a" for the others)
  \n[FOPEN_MAX]\n          20 x "\n%d" (state+0x43a4.. table of stream in-use flags)
  \n[state]\n              "\n%d" state+0x43f4
  \n[win next, head]\n     "\n%d %d\n" scrollback head, scroll offset ; \n[winsz]\n "%d\n" scrollback_lines(100) then 100 x "^%s\n" (the ring lines, 256 bytes each, full text buffer)
  \n[io files and external memory]\n  four io-file lists (`save_io_files`: state+0x14c/0x150/0x154/0x158): each node "1\n" + "^%s\n^%s\n%d %lx x9 %d" (name, name2, +0x154.. ) + " %lx %lx %d %d %ld %d \n" (+0x188,+0x1b0,+0x1d0,+0x1d4,+0x1d8, open flag) + range list "1\n%lx %lx %ld\n"...
                           "0\n" ends a list and "%d" 0; then FUN_00458060(dev, fp) (mdisk.c: memory disk state) ; then "1\n^%s" current source file (state+0x4018) or "0\n^\n"
\n[viewdev]\n %d\n         current device index (`cur_dev_index`)
```
(`save_expr_tree` @ 0x435b00 serialises the compiled expression trees of breakpoints/watches: per node `"\n%d " code`, `"\n%lu %lu"`, `"\n%hu %hu"`, `"\n%lu %lu"`, `"\n%d %lu %hu"`, `"\n%lu %ld %ld %lu %lu %lu %lu"` from the 0x40-byte info block
(`node+0x10`), children order left/middle/right encoded in `code` (3*code+1, +2, next (code+1)*3); `load_expr_tree` @ 0x438450 rebuilds it from a table indexed by code. Because the two GUI/cdb-specific parts (C expression trees, io file lists, mdisk) live in other groups'
areas, a first port can restrict itself to the register/memory/peripheral/scalar sections and treat trees as opaque - but the file must stay loadable by the original; note the loader uses `%d`/`%lx` scanning, so token layout is whitespace-insensitive except for the `^` string lines.)
Write path detail: each `fprintf` result is unchecked except the last (`rewind`; `"%d"` 0x2c7; `fseek(...,2)`), error text `"Error opening file."` / `"Error writing file"` via the error printer (so it is logged as `{Error ...}`). `load` of the old-format
mismatch returns 1 (caller prints its own message).  Devices are saved with a separate optional profiler-file name section (see `[profiler]`).
Confidence: section order and format strings are exact (taken from the fprintf/fscanf arguments); the *meaning* of some numeric fields (marked "?" above) is guessed.

## 9. Misc helpers

* `str_icmp`/`str_nicmp` (state.c) compare case-insensitively (ctype bit 1 = upper, tolower); `sorted_table_lookup(s, table, n)` scans a sorted char* table until `strcmp>0`.
* `path_combine(dir, name, ext, out)` @ 0x438d70: if `name` is absolute (`\` or `/` first char or contains `:`) out = "" else out = dir + (`\` if dir does not end in `\ / :`); then append name; convert `/` to `\`; append `ext` unless the last path component
  already has an extension (`.` found after last separator) or there is no room (256).  `path_search(name, defext, out)` @ 0x438eb0: try device dir (`dev+0x58`); then each element of `source_path_list` (`"%255[^,]"` scanning, comma separated);
  then strip the leading directory of `name` and recurse; returns 1 and `out` if the file can be opened for reading (`"r"`), else 0.
* Range map (`rangemap_set/get`, fmt.c) - a sorted singly linked list of `{ int value; unsigned lo; unsigned hi; node *next }` intervals (16 bytes) covering an address space: `rangemap_get(map, addr)` = value of the node with `hi >= addr` (0 if map empty);
  `rangemap_set(map, lo, hi, space_size, value)` inserts/overwrites an interval, splitting/merging neighbours; if `hi < lo` the interval wraps (set `[lo,space_size]` and `[0,hi]`).  Used for the per-region memory attribute maps (`state+4+region*300`: `+0` breakpoint kinds, `+4` display marks, `+8`, `+0xc` input tags,
  `+0x10` output tags, plus two 16-entry circular histories of last accessed addresses at `+0x14..`, `+0xa0..`).  `memtag_rebuild` builds the `+4` map: value 1 (from `+0` map entries == 1, i.e. breakpoints? read/write watch), history entries with kinds 2/3 -> 1, 3/4/1 -> 2 (used to highlight `{ }` cells in memory display).
* console arena (`pool_*`, console.c 0x43dcb0-0x43ddd0): bump allocator of 0x14-byte block headers `{size, kind, base, cur, next}`; `pool_alloc(pool,n)` rounds n up to 8; `pool_strdup`. Used by the cdb (C debugger) - `cdb_snapshot_write` (0x43deb0) writes a cdb symbol snapshot file
  (`fopen("wb")`, 0x3aac bytes of state + the arena chunks) - it belongs to the cdb group's saved data (`save` C-symbol state?), low confidence.
* `abort_check()` @ 0x43dbc0: `if (abort_flag) { run_dev_state.+0x48 = 1; abort_flag = 0; } return cur_dev->+0x48;` - polled by long listings.

## 10. Function index (see the names file for prototypes)

state.c: str_icmp 0x4340f0, str_nicmp 0x4341a0, dev_write_reg 0x434270 (writes a register through the bank's write fn `bank+4`, or through `FUN_00456f60` for memory-mapped alias regs), str_tolower 0x434300, sorted_table_lookup 0x434830, save_state_all 0x434880 (= save_state(all devices)), save_state 0x4348a0, save_maplist 0x4358d0,
save_io_files 0x435930, save_io_list 0x4359a0, save_expr_tree 0x435b00, expr_tree_size 0x435c20, devtype_find 0x435ce0, dev_create 0x435d40, dev_alloc_regbank 0x4360b0, dev_init_regbank 0x436150, dev_alloc_memmaps 0x4361f0, dev_init_memmaps 0x4362e0, dev_alloc_periph 0x4363e0,
dev_init_periph 0x436430 (copies template `0x4dc148` 0x4a dwords), dev_reset 0x436470, dev_free_program_info 0x4364f0, dev_clear_memory 0x436620, free_memtags 0x436640, free_io_lists 0x436730, dev_destroy 0x4367a0, dev_free_regbank 0x436a50, dev_free_memmaps 0x436ad0, chip_reset_regs 0x436b30,
dev_state_init 0x436bb0, load_state 0x436f90, load_maplist 0x4383d0, load_expr_tree 0x438450, dev_cycle_* 0x438690/0x438850/0x4388a0/0x4388f0, dev_housekeeping 0x438a30, load_io_files 0x438a80, load_io_list 0x438af0, path_combine 0x438d70, path_search 0x438eb0.
cmdloop.c: sim_init_tables 0x439000, memmap_find 0x439080, dev_select 0x439140 (creates the device with the same type as device 0 if the slot is empty; fails -> device marked stopped `+0x40=0`), cmd_complete 0x4391f0, cmdstack_push 0x439360, cmd_read_line 0x439410,
prompt_show 0x439d80, status_line1 0x439e50, cmd_error_position 0x439eb0 (appends a blank when the failing token is near the width limit, returns cursor position), help_line_edit 0x439f40 (mini editor used by help.c).
macro.c / fmt.c / console.c / dispval.c: see sections 2-6, 9.

## 11. Quirks / things to reproduce, open questions

* Transcript echo uses the edit buffer after completion; abbreviations are expanded only in the interactive path.  The port's line front end should apply `cmd_complete` (abbrev exact match first, then prefix, in table order: note `d` is "display", `de` device, `di` disassemble, `do` down; `e` evaluate) before echoing, or the transcripts of the tests will differ.  Confirm with a fresh golden of the same script (old golden `s01` shows `eval $ff`).
* Lines are truncated to 255 chars in the ring but written in full to the logs.  `{`/`}` in user command lines are NOT highlight markers (echo uses plain mode); command arguments like `${c_expr$}` use `$` as escape only in output (`$` immediately followed by `{` or `}` prints the brace literally).
* Log files are flushed after every line (`fflush`), the session log is per device (each device has its own `state+0x48`); command log (`cmdlog_fp`) is global.
* `more` paging: default off; when on, the bottom-line prompt asks for a key every 21 lines; not in the log (screen only).
* State file: `0x2c4` -> `0x2c7` overwritten at the end; strings prefixed with `^`; hex fields unsigned; loader ignores headers; `numdevices` may be less than the running devices (`save s` from a single device? `save_state_all` uses devices 0..max-1: `DAT_004aab0c-1` i.e. all 32 slots, empty ones produce a `-1` type entry and the loader stops at it).
* Open: the `f1/f2` flags of the command entries, meaning of a few state fields marked "?", exact `disasm_line` option bits (`DAT_004dc380`), `cdb_snapshot_write`. The remaining register formats are a branch tree that should be transcribed from fmt.c 579-790 / dispval.c 60-1090 rather than paraphrased.
