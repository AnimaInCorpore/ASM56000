# SIM56000 group 'misc': profile, source, stats, radix, mdisk, expr, misc (0x454000-0x45d3ff)

Names: re/names/SIM56000/misc.names.txt (189 lines: 165 F, 24 D... see file). Confidence H/M/L per line.
Ghidra `local_NN` are offset by 4. `sim` = DAT_0050578c (per-device simulator state, chosen by cur_dev_index from
sim_table 0x4a8d98), `cur_dev` = DAT_00505798 (device instance, from dev_table 0x4aab10), `cur_devtype` = DAT_00505790
(device type descriptor, = devtype_table[cur_dev[0]]), `cur_isa` = DAT_00505794 (instruction-set/ops descriptor).

Module boundaries: the filemap boundaries are mostly right, but the modules are really:
* 0x454630-0x456fb0 is ONE thing: the **profiler report generator** (metrics.log / "Code Coverage Report" etc.; the
  filemap names profile/source/stats are only parts of it). 0x456f60/0x456fb0 are unrelated 2 tiny device helpers.
* 0x457000-0x457fb0 "radix" is a mixture: device-dispatch thunks, value formatting (radix), memory access trace ring,
  dsp_alloc/free/realloc (memory allocator with "spill to disk" fallback), and mdisk_free_all.
* 0x458060-0x458a80 mdisk proper; **0x458c10 is not mdisk**: it is the per-instruction profiler hook (sim_profile_step).
* 0x459030-0x45d0c0 expr: expression evaluator (0x459030-0x459140 + 0x4591c0 are instruction operand reference
  recording, not expression code).
* 0x45d120-0x45d350 "misc": two decimal-split helpers, allocator stubs, sim_error.

## Shared conventions

### Expression mode word (expr_mode, DAT_005029dc, passed as `mode`/param_1 everywhere)
Bits (from expr.c/radix.c tests): 0x80 IEEE-float device (32-bit words; the `*32` op variants and ieee_single_*
conversion); 0x1000 (56000 "double/long" move-in-32 flag: values 24+24 split at 16); 0x10000000 = 16-bit word device
(561xx style), 0x4000000 = 24-bit word device (56000), else 32-bit; 0x1000000 = accumulator has 8 extension bits
(56-bit) instead of 4; 0x800 = 16-bit address (mask 0xffff), 0x400 = 19-bit? address ((0xfff80000 mask), 0x200 = 24-bit
address (0xff000000 mask), 0x8 = 16-bit addr default; 0x10000 = "no register parsing" ; 0x14000000 = word masks used by
node_word. The exact meaning is derived from cur_devtype+0xc (mode word) or the hook at cur_devtype+0x4e8.

### Value node (expression result), 0x28 bytes, `dsp_alloc(0x28,1)`
| off | type | meaning |
|---|---|---|
| 0x00 | double | floating value (valid when flags&0x200) |
| 0x08 | ulong | integer limb 0 (low word; e.g. 24 bits) |
| 0x0c | ulong | limb 1 (mid / "high word") |
| 0x10 | ulong | limb 2 (extension, e.g. accumulator ext byte) |
| 0x14 | ulong | address / raw copy (for symbol/register nodes) |
| 0x18 | ulong | memory space id or register id (pdVar+3) |
| 0x1c | ulong | flags: 0x100 integer valid, 0x200 float, 0x2000 boolean-result mark (0x2101 = "boolean int"), 0x4000 register value,
|      |       | 1/2/4 size class of the integer (1 = single word, 2 = double 48-bit, 4 = long/accumulator 96-bit), 0x10/0x20/0x40
|      |       | set by '>' '<' '<<' prefix in eval_int_addr/eval_data_word (high/low/... byte select) |
| 0x20 | ulong | (unused/ext) |
| 0x24 | short | index into cur_devtype space table (register/memory group) for symbol/register nodes |

`node_normalize` (0x45bc50) propagates carries between limb0/limb1/limb2 with the word-width masks.

### Device type descriptor `cur_devtype` (0x4aaac8 ... per type; only the fields used here)
+0x04 id (0x2c8/0x2ca compared in sim_profile_step), +0x0c mode word, +0x14 nspaces_alt (used in dev_spaces_call_*),
+0x18 pointer to table with entries of 0x48 bytes (fn ptr tables) at +0x2c, +0x1c number of memory/register groups,
+0x20 pointer to **group table**, entries 0x2c bytes: +0x00 name (char *), +0x04 id, +0x08 class mask,
+0x0c low address, +0x10 high address, +0x18 flags (bit 0x1000000 = space backed by "memory disk" mdisk),
+0x20 word mask, +0x24 format/kind flags (bit 2 = 96-bit long value, bits 0x80000000..0x4000000 = size code of word:
0x80000000->4 bits, 0x40000000->8, 0x20000000->12, 0x10000000->16, 0x8000000->20, 0x4000000->24 bits, else 32;
low byte & 0xff400003 copied into node flags), +0x24 also bit 1/2 kinds.
+0x24 (of type desc) = short name string (used to build the MEM file name), +0x28 = **ops table** (fn ptrs):
[0] mem_read(space,addr,&val) [used by dev_mem_read, expr symbol/reg reads], [1] write, [2] (4 args),
[0xa..0xf] other dev services (dev_call_slot10..15), [0xb] alternate read used by display (fmt_read_word,
parse_primary use it when non-NULL), [3] address canonicalize (used by mem_addr_check); +0x4e8 = optional
function returning the current mode word.
`cur_dev` (instance): [0]=type index, [1]=dev number, [3]=array of mdisk containers (16 bytes per group),
[4]=FILE * m_pdisk swap file, [5]=free-slot list (mdisk), +0x58 path buffer for the swap file, +0x1c/+0x20 = current
pc range (used by sim_profile_step).
`sim`+4 = per-group access statistic table, 300 (0x12c) bytes per group: +0x14 read ring, +0xa0 write ring;
ring header {total,idx,count}, 16 addresses at +3.. and 16 values at +0x13.. (mem_trace_access).

## profile.c (0x454630-0x454fc0) -- metrics.log "Code Coverage Report" (sim log P)

Profiler state lives in `prof` = sim+0x490 (DAT_00505b64 is set to it; some functions compute sim+0x188+0x308).
* +0x34e0 flags (bit0 COFF not read properly, bit3 P memory has undecoded instructions, bit4 "Profiler file not
  generated"), +0x3504 source line limit (-1 = report by address), +0x37a0 mode (1 = no instructions executed,
  3 = dynamic data present), +0x37f0 = 20000-byte pool of file/alloc arena (prof_start inits via 43dcb0), +0x34e8 string pool.
* sim+0x3c30 profiler state: 0 off, 1 = armed, 2 = running, 4 = complete (prof_reset only cleans when non-zero).
* Arrays indexed by instruction id (cur_isa[1] = number of instruction kinds): +0x708 dynamic count, +0x3e8 (1000)
  static count, +0x16a8/+0x1328.. loop-nesting max counters, +0x19c8 "no loop" counters, +0x2008.. paired move counters,
  +0x2648/+0x2968/+0x2c88 move type breakdown, +0x2fa8 (2x4 = ref counters by class), +0x2fe0 addressing mode counters.
* +0x14 ring of last 8 fetched (category,addr) pairs, +0x54 ring index (mod 8), +0x58 source name, +0x5c output file
  (default "metrics.log" 0x4d1cac), +0x60 second name, +0x68 title, +0x70..0x8c static sizes X/Y/P (init/uninit),
  +0xac words executed, +0xb0/+0xb4 instruction counts (all / conditional), +0xc0 cycles.

| addr | name | notes |
|---|---|---|
| 454630 | prof_reset | if sim+0x3c30 != 0: prof=sim+0x490; (state!=4 -> 47b8b0 close); 43dd40(prof+0xd3a*4) frees pool; zeroes 0xde9 dwords; state=0 |
| 454690 | prof_record_insn(insn) | setjmp (DAT_00505b20) guard. Records one executed instruction: find/create symbol record (46bac0/46b8b0), updates cycle/stall/pass counts (insn+0x37..0x3a), loop nesting counters (sim+0x470/0x474), dynamic count, words (+0xac), calls isa ops [0x24],[0x10],[0x20],[0x1c],[0x38]; calls prof_flush_refs; returns 1 |
| 454990 | prof_flush_refs(insn) | walks the 20 operand-reference slots at insn+0xf4 (stride 0x14: [0]cat,[1]class,[2]addr,[3],[4]kind); per ref updates symbol counts; kind 0 = instruction fetch (ring of last 8 addresses) |
| 454b50 | prof_start(symfile,outfile,title) | setjmp guard, prof_reset, init pool, fields +0x37a0=1, +0x3504=-1, copies names, default output "metrics.log", 47dc80 |
| 454c50 | prof_report(arg) | driver: 47b670 open report; if flag 0x10: message "Profiler file not generated"; if mode==1: "No instructions executed..." ; else sections in order: basic profile (456d60), data memory refs (456440), symbol refs (455a50), occurrence reports (456530), moves (455db0), addr modes (4561f0), 47d680, coverage (454d50); finally prof_reset |
| 454d50 | prof_coverage_report | "Code Coverage Report" header (columns "address", "cyc/stall", "passes:", "source", "all/cond"); by address (sorted syms via 46ade0/46aec0 list iterator) or by source (4551a0/4557a0); "Note: new instructions were created"; "Code coverage report aborted"; "Coff file did not read properly" |
| 454fc0 | prof_print_cov_line | prints one line: "[%04u]%2s" line number, "%06lX" address or "<join>", counts (uses stack varargs: extra 2 args = line no, source text) |

Interfaces: 46b0a0 (message/error printer with level), 46bac0/46b8b0/46b770/46b700 (profiler symbol/line record
lookup+create: profrep/cdb group), 46aec0/46ade0 (sorted list iterate/open), 47bdf0/47bad0/47b8f0 (report printf,
title, attribute), 43ddd0 (pool strdup), 43dcb0/43dd40 (pool init/free), 47ca00/47b670/47d2e0/47d680 (report helpers).

## source.c (0x4551a0-0x455db0) -- source listing part of the coverage report and symbol/moves reports

| addr | name | notes |
|---|---|---|
| 4551a0 | prof_cov_by_source | coverage when +0x3504<0: groups consecutive symbols with same source file/line and prints one line via prof_print_cov_line; ends with "{end}" (0x4d1f10) |
| 4553c0 | src_get_line(pf,&failed,&name,&line,fname,want,&text) | reads source `fname` line by line (fgets 400 into DAT_00502718); messages: "File %s, C sources not supported." (only .c files rejected via src_is_c_file), "Source file %s more recent than executable", "Failed to read from file %s"; prints "----- %s file %s ------" / "END file" banners; handles `include` lines (src_include_name) |
| 455670 | src_include_name | parses `include 'file'` (quote chars in 0x4d1f5c = `'"`): returns file name in DAT_005028b0 or NULL |
| 455750 | src_is_c_file | name ends with ".c"/".C" |
| 4557a0 | prof_cov_source_file(name) | recursive over includes: per-file source listing with coverage |
| 455a50 | prof_symbol_mem_refs | "Symbol memory references" table (columns "symbol+offset", "%5s%5s"), per symbol; then "unnamed memory references: X=%ld Y=%ld" |
| 455bd0 | prof_symbol_mem_refs_sym | one symbol: up to 100 words in rows of 5 ("%c\x83N4%4u\x83|" uses line-drawing bytes), run-length compressed |
| 455db0 | prof_moves_breakdown | "Instruction moves breakdown" (paired/unpaired/single/double, "L space", "Parallel move instruction dynamic breakdown"; qsort by name comparator LAB_004561b0) |

## stats.c (0x4561f0-0x456fb0)

| addr | name | notes |
|---|---|---|
| 4561f0 | prof_addr_mode_breakdown | "Dynamic addressing mode breakdown" per instruction group (cur_isa[+8]/[+0xc] name tables) sorted (qsort 0x10 entries) |
| 456440 | prof_data_mem_refs | "Data memory references": Internal/External/ROM x Memory/Write rows (sim counters +0x2fa8..); "%lu locations were written without..." |
| 456530 | prof_occurrence_reports | calls occurrence reports twice: alphabetical then by percentage; note "P memory undecoded instructions" if flag 8 |
| 4565a0 | cmp_insn_name | qsort comparator by mnemonic (isa op [0x14](id)); LAB_00456640 = percentage comparator |
| 456690 | prof_insn_occurrence(cmp,title) | "Instruction Occurrence Breakdown (%s)": "# occur", "% of 100", static+dynamic; marker "*" for cond instructions, note "instructions marked with '*' ..." |
| 4569f0 | prof_doloop_occurrence(cmp,title) | "Do-Loops Instruction Occurrence Breakdown (%s)": columns "no loop", "nesting" |
| 456d60 | prof_basic_profile | "Basic Profile": Static/Dynamic; "Initialized data size", "Uninitialized data size", "Code size" (X=,Y=,P=), Instructions, Function calls, Max loop nesting (sim+0x478), Total cycle count, Stall cycle count |
| 456f60/456fb0 | dev_spaces_call_c/_8 | iterate cur_devtype+0x14 spaces, call function pointer [3] resp. [2] of each 0x48-byte space record; callers scattered (404ad0,403c50,409b40...): memory-space dispatch helpers |

## radix.c (0x457000-0x457fb0)

Device-dispatch thunks (457000,457060,4570c0,457120,457180,4571e0,457240,4572a0,457300): all identical:
save cur_dev/cur_devtype, select `dev`, call ops[slot](a,b,c[,d]) (0 if the device slot is empty), restore.
Slot -> function: 457180=[0] mem_read, 457000=[1], 457300=[2], 4571e0=[0xa], 457240=[0xb], 4572a0=[0xc], 457120=[0xd],
457060=[0xe], 4570c0=[0xf].

| addr | name | notes |
|---|---|---|
| 457370 | dev_find_space(dev,name,&id) | case-insensitive search of group table (0x2c entries) by name; returns id (+4) |
| 457420 | stricmp_ci | inlined _stricmp (also 45a7b0 in expr) |
| 4574d0 | space_notify | for each group whose class matches: 43b8c0(sim[4]+8+i*300,...) (breakpoint/watch check) |
| 457560 | mem_addr_check | ops[3] -> group index (439080) -> 43ba40 |
| 4575c0 | fmt_addr(addr,buf) | address to hex: %04lx (16-bit / 19-bit modes), %06lx (0x200), %08lx (32-bit), masked with 0xffff if flag 0x800 |
| 457630 | fmt_read_word(space,addr,radix,out,nanfmt) | reads via ops[0xb]/[0] then formats. radix codes: 0 binary, 1 signed decimal, 2 fraction (float), 3 hex, 4 unsigned. Uses fmt tables 4d2758 (16-bit), 4d2770 (24-bit), 4d2788 (32-bit) indexed by radix: "$%04lx","%05ld",-,"$%04lx","%05lu" etc.; long values: "$%06lx%06lx", "$%08lx%08lx", "$%04lx%04lx", decimal "%06lu%09lu" via val_to_dec_parts; fraction "%10.7f" (single word) / "%18.15f" (double), NaN via "%14.14s"/"%25.25s" from 43bd90 |
| 457950 | fmt_word(space_idx,addr,radix,out,value) | same for an already-read value; tables 4d27e8/4d2800/4d2818 (without '$'); "%15.15s","%18.18s", "%06ld%09ld"; radix 0 emits binary digits using bit_mask_tab 0x4aab14 (24/16/32 digits) |
| 457cc0 | mem_trace_access(space,addr,is_write,value) | record access in 16-entry rings (sim[4] + i*300 + 0x14 reads / +0xa0 writes) for groups whose class/range include addr |
| 457de0 | mem_trace_fetch(addr) | mem_trace_access(0x13,addr,0,0) |
| 457e00 | dsp_alloc(size,zero) | malloc (+memset if zero); on failure tries mdisk_spill and retries; else "Insufficient memory: dsp_alloc" via 43d3a0; if DAT_004aaa90 (never set) calls 45d2a0 stub |
| 457ed0 | dsp_free | free (or 45d280 stub) |
| 457f00 | dsp_realloc | realloc + spill retry; "Insufficient memory: dsp_realloc" |
| 457fb0 | mdisk_free_all(dev) | frees all block lists of all mdisk groups of a device |

## mdisk.c (0x458060-0x458a80): sparse memory with disk spill ("m_gdisk"/"m_pdisk")

Memory groups flagged 0x1000000 keep their words in a sparse structure so huge address spaces (56300 etc.) fit:
per group a container of 16 bytes {cursor(mru node), prev-cursor, -, -} at cur_dev[3]+i*16 pointing into a circular
doubly linked list of 20-byte nodes: [0]next,[1]prev,[2]upper bound (block covers [prev.bound, bound)), [3]state
(1 = block swapped out; [4] = file offset in swap file; 2 = constant fill; [4] = fill value; 4 = resident;
[4] = pointer to 0x400 bytes = 256 words), [4] as above. Sentinel node initial state 2 with bound 0.
Block size = mdisk_block_bytes (0x400 = 256 x 4 bytes). Word index = addr & 0xff.
Swap file: name = sprintf("%s%d", cur_devtype+0x24, cur_dev[1]) ".MEM" placed in dir cur_dev+0x58 (438d70), opened "w+b"
(cur_dev[4]); free-slot list cur_dev[5] = {next,offset} pairs.

| addr | name | notes |
|---|---|---|
| 458060 | mdisk_save_all(dev,fp) | for each flagged group: mdisk_save_space; used by save state (4348a0) |
| 4580d0 | mdisk_close(dev) | free lists, fclose swap file, free slot list (caller 436620) |
| 458180 | mdisk_init | allocate sentinel node per flagged group (state 2) |
| 458210 | mdisk_load_all(dev,fp) | load state (caller 436f90) |
| 458280 | mdisk_read(dev,space,addr,&val) | find node; state 2 = fill value; state 1 = page in; returns 1 on flagged groups else 0; MRU update |
| 458340 | mdisk_find_node(list,addr) | walk from cursor |
| 458380 | mdisk_page_in(node) | reads block from swap file; errors "Error seeking in m_gdisk", "Error reading in m_gdisk." (exit(1)) |
| 458480 | mdisk_write(dev,space,addr,val) | splits constant-fill nodes into (up to 3) nodes + resident block, then stores word |
| 4585f0 | mdisk_clear_list | free all nodes, leave sentinel |
| 458660 | mdisk_save_space(list,fp) | text dump via fprintf: "\n%ld" node count, per node "\n%lx" bound, "\n%d\n" state, 256 words "%lx " (newline every 8) |
| 458770 | mdisk_load_space(list,fp) | inverse with fscanf-like 4839d0 ("%ld ","%d ","%lx ") |
| 458870 | mdisk_spill | low-memory handler: tries mdisk_spill_lru over all devices/groups, else mdisk_spill_mru; returns 1 if a block was freed |
| 458a10/458a50 | mdisk_spill_lru/mru | pick the resident node not equal to the cursor (or the cursor) |
| 458a80 | mdisk_spill_node | writes block to swap file (create "w+b" if needed): "Error opening in m_pdisk", "Error seeking in m_pdisk", "Error writing block in m_pdisk." exit(1); node becomes state 1 |
| 458c10 | sim_profile_step(dev) | (caller 4388f0, the step loop) per executed instruction: builds local instruction record (0xa1 dwords), calls isa op [0x3c] decode, updates sim+0x424.. do-loop tracking state (sim+0x428: 1 start, 2 running, 3 last), reads SR-like registers via 433f60/433f10 (register lookup/read), maintains loop counter stats (sim+0x474 nesting, +0x478 max), then calls prof_record_insn(local rec) |

## expr.c (0x459030-0x45d0c0): simulator expression evaluator

Recursive descent, precedence climbing. Cursor = expr_ptr (0x5029e0), mode = expr_mode.
Errors: expr_error sets errmsg (0x4a8dd0)=msg and expr_err_flag(0x5059e0)=-1 (returned to caller who prints).
Messages: "Expression result too large", "Expression result must be integer", "Extra characters beyond expression",
"Missing expression", "sv_optr pointing to NULL address", "Binary constant expected", "Hex constant expected",
"Invalid expression", "Address too large", "Address offset expected", "Invalid register name", "Missing ')' in expression",
"Divide by 0", "Illegal operator for floating point element", "Cannot apply '~' operator to floating point value",
"Invalid shift amount".

Grammar (parse_primary 0x459a70): unary `+ - ~ !`, `( expr )`, `space:value` (e.g. `x:$100`, 1..3-char space name + ':';
looked up case-insensitively in group table; reads memory and returns node with 0x4100 flags), `reg:name` /
register name (via 440730 register lookup, else 444d50 symbol lookup), symbols `name`, `@name` (C/scoped), `name+off`/`name-off`,
`*` = current pc/`sim+0xc`, constants: `%bin`, `$hex`, `` `decimal `` (radix default: sim+0x30 = 0..4 selects default radix for bare
numbers: 3 hex, 1/2/4 decimal, else binary), `0x..` no; floating `d.ddd`/`e` via strtod (parse_float). Bare digits use
default radix (sim+0x30).
Binary operators (peek_binop 0x459810 returns code; precedence in binop_prec 0x4599c0):
1 '+', 2 '-', 3 '*', 4 '/', 5 '|', 6 '&', 7 '%', 8 '^', 9 '<<', 10 '>>', 11 '<', 12 '>', 13 '==', 14 '<=', 15 '>=',
16 '!=', 17 '&&', 18 '||', 19 '=' (single, same as ==).
Precedence (high first): {* / %}=1,{+ -}=2,{<< >>}=3,{< > <= >=}=4,{== != =}=5,'&'=6,'^'=7,'|'=8,'&&'=9,'||'=10.
parse_binop_rhs (0x459530) dispatches by opcode to op_* (96-bit limb versions when mode&0x80==0, the *32 versions for IEEE devices).
Top-level: eval_expr (0x459480) requires end at NUL , ) or ;. eval_int_addr / eval_int_masked / eval_data_word additionally
check integer-ness and range, and handle prefix '<' '>' '<<'. node_word(node) = limb0 | limb1 << 24/16.
Operand recording: ref_record (0x459140) stores up to 10 pending operand references at sim+0x294 (stride 0x14:
[0]category from ref_kind_info, [1] access mode 0/1/2, [2] addr, [3], [4]); ref_prune (0x4591c0) clears category-3 refs if the
instruction has no memory operand of that kind. ref_kind_info maps a reference-kind code (0..0x123) to
category (0..4) and access mode.
Multi precision helpers (mp_*) work on 8 byte-wide limbs stored in dwords (mp_unpack/mp_pack: 3-dword value <-> up to 7
byte limbs; limb count depends on 16-bit mode): mp_mul_digit, mp_sub, mp_ge, mp_cmp, mp_len, mp_div_digit (schoolbook divide),
mp_divmod(num,den,&quot,&rem). op_mul (0x45acd0) multiplies by convolution on byte limbs with sign handling.
Float conversions: word_to_frac (int -> fraction word/2^(bits-1)), dword_to_frac, long_to_frac (56-bit etc.), inverse frac_to_word (round
to nearest even, saturate), frac_to_dword, frac_to_long; IEEE: ieee_single_to_double, double_to_ieee_single, ext_to_double,
double_to_ext. node_to_double/node_get_double/node_from_double select by size class flags (1/2/4).
Quirks: comparison op_compare handles sign by top bit of limb2 (or bit 0x80/0x8 depending on accumulator size); op_compare32
returns 2 (unordered) for NaN operands; shifts: op_shl limit = 24 bits (or 32/16 by mode) else "Invalid shift amount", op_shl32/op_shr32
limit 96 (>0x60) ; op_shr arithmetic fill uses shr_fill_bit 0x80000000 for 32-bit variant.
Callers outside the group: 426410/426370 (asm operand evaluation), 469c30 (cdb), 4524d0 (run), 43f010, 43bec0.

## misc.c (0x45d0c0-0x45d350)

| addr | name | notes |
|---|---|---|
| 45d0c0 | double_to_ext | (belongs to expr): double -> 96002 extended limbs |
| 45d120/45d1b0 | val_to_dec_parts2/val_to_dec_parts | splits a 2-limb value into two decimal halves via mp_divmod by 10^9 (const 4d2978 for 16-bit limbs 0x3b9aca00, 4d2988 for 24-bit limbs); result = hi*0x1000000 + lo... used for "%06lu%09lu" |
| 45d280 | dsp_free_ext | no-op stub (external allocator, never active) |
| 45d290/45d2a0 | ret_true/ret_false | trivial |
| 45d2b0 | sim_error(msg) | copies msg (<=255) to errmsg_buf (0x4a8dd4), sets last error, prints "{%s}" (highlighted) via 43d3a0(text,1) + 43d9f0 (flush); if script_active && quit_on_error_en: sets flag and runs command "quit ;on error" (43b5a0(cur_dev_index,...)) |
| 45d350 | ret_99 | returns 'c'(99); caller 43a7c0 |

## Open questions
* Exact bit meanings of expr_mode (see above; medium confidence) and the ops-table slot semantics beyond [0] read.
* Names of 43b8c0/43ba40/439080/433f10/433f60 and profiler list functions (46aec0 etc.) belong to other groups.
* 458c10 loop tracking state machine (sim+0x424..0x488) only sketched.
