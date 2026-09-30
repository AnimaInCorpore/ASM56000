# Motorola DSP COFF (CLAS56 v6.3) - file layout

Recovered while reconstructing COFDMP (src/cofdmp/cofdmp.c prints every field).
All fields are 32-bit big-endian words; names are 8 raw bytes. If the first 4 bytes of a
name are 0, the next word is a string table offset.

## File header (0x1c bytes)

| off | field |
|---|---|
| 0 | f_magic: 0x2c5 DSP56000, 0x2c6 DSP96000, 0x2c7 DSP56100, 0x2c8 DSP56300, 0x2c9 DSP56800, 0x2ca DSP56600, 0x2cb "100", 0x2cc DSP56700 |
| 4 | f_nscns |
| 8 | f_timdat (seconds since 1970; cofdmp shows it as UTC) |
| 0xc | f_symptr |
| 0x10 | f_nsyms |
| 0x14 | f_opthdr |
| 0x18 | f_flags: F_RELFLG 1 (absolute file), F_EXEC 2, F_LNNO 4, F_LSYMS 8, F_MINMAL 0x10, F_UPDATE 0x20, F_CC 0x10000, F_SDI 0x20000 |

## Optional header, absolute file (0x3c bytes)

magic 0, vstamp 4, tsize 8, dsize 0xc, bsize 0x10, then five CORE_ADDR pairs
(address word first, memory space second): entry 0x14/0x18, text_start 0x1c/0x20,
data_start 0x24/0x28, text_end 0x2c/0x30, data_end 0x34/0x38.

## Linker header, relocatable file (0x38 bytes; an old 0x28-byte form exists)

modsize 0, datasize 4, endstr 8 (string table offset or -1), secnt 0xc, ctrcnt 0x10,
relocnt 0x14, lnocnt 0x18, bufcnt 0x1c, ovlcnt 0x20, majver 0x24, minver 0x28,
revno 0x2c, unused 0x30, sditot 0x34 (only when F_SDI is set).
(Readers such as CLDLOD keep it in a 40-byte buffer, so the extra words overwrite the
variables that follow; the ports reproduce that.)

## Section header (0x34 bytes)

| off | field |
|---|---|
| 0 | s_name[8] |
| 8 / 0xc | s_paddr: address / memory space |
| 0x10 / 0x14 | s_vaddr: address / memory space (STYP_BLOCK: the address is the block length) |
| 0x18 | s_size (in words) |
| 0x1c | s_scnptr |
| 0x20 | s_relptr |
| 0x24 | s_lnnoptr |
| 0x28 | s_nreloc |
| 0x2c | s_nlnno |
| 0x30 | s_flags: DSECT 1, NOLOAD 2, GROUP 4, PAD 8, COPY 0x10, TEXT 0x20, DATA 0x40, BSS 0x80, DEBUG 0x100, BLOCK 0x400, OVERLAY 0x800, MACRO 0x1000, BW 0x2000, OVERLAYP 0x4000 |

Raw data: one 32-bit word per DSP word.

Memory space numbers: 0 P, 1 X, 2 Y, 3 L, 4 none (N), 5-10 LAA LAB LBA LBB LE LI,
11-15 PA PB PE PI PR, 16-20 XA XB XE XI XR, 21-25 YA YB YE YI YR, 26 PT, 27 PF,
28 EMI/EM, 29-284 E0-E255, 285 D/DM, 286 P8, 287 U, 288 U8, 289 U16.

## Relocation entry (12 bytes)

r_vaddr 0, r_symndx 4 (string table offset of a `{{sym}}@n#m`-style expression string),
unused 8.

## Line number entry (12 bytes)

address 0 (l_symndx when l_lnno == 0), memory space 4, l_lnno 8.

## Symbol entry (0x20 bytes)

| off | field |
|---|---|
| 0 | n_name[8] |
| 8 | n_value (address, or low word of a double) |
| 0xc | memory space (or high word of a double) |
| 0x10 | n_scnum: -2 N_DEBUG, -1 N_ABS, 0 N_UNDEF |
| 0x14 | n_type |
| 0x18 | n_sclass |
| 0x1c | n_numaux |

- Base type: `(type & 0xf) | ((type >> 12) & 0x10)` -> T_NULL ... T_LACCUM (22 names);
  for .file symbols 0 = T_NULL, 1 = T_MOD. Derived types: 2-bit groups from bit 4
  (1 PTR, 2 FCN, 3 ARY).
- T_FLOAT (`type & 0x1000f == 6`): n_value is an IEEE double, low word at 8, high word
  at 0xc. T_LONG (5) prints as two words.
- Storage classes: C_EFCN -1, C_* 0-20, 100-106, C_SECT 128, C_SDI 129; assembler
  classes A_FILE 200, A_SECT 201, A_BLOCK 202, A_MACRO 203, A_GLOBAL 210, A_XDEF 211,
  A_XREF 212, A_SLOCAL 213, A_ULOCAL 214, A_MLOCAL 215.

## Aux entries (0x20 bytes)

| kind | layout |
|---|---|
| file (C_FILE/A_FILE) | 16-byte inline name, or string table offset at 0x10; x_ftype 0x14 |
| section aux 0 (C_STAT, base type 0) | scnlen 0, nreloc 4, nlinno 8 |
| section aux 1 (new) | secno 0, rsecno 4, flags 8, mspace 0xc, mmap 0x10, mcntr 0x14, mclass 0x18 |
| section aux 1 (old 0x28 header) | secno, rsecno, mem 8, flags 0xc, bufcnt/ovlcnt 0x10, buftyp/ovlmem 0x14, buflim/ovlstr 0x18 |
| section aux 2 (buffer, flags 0x2000) | bufcnt 0, buftyp 4, buflim 8 |
| section aux 2/3 (overlay, flags 0x4000) | ovlmem.mspace/mmap/mcntr/mclass 0-0xc, ovlcnt 0x10, ovlstr 0x14, ovloff 0x18 |
| tag (STRTAG/UNTAG/ENTAG) | size 8, endndx 0x10 |
| C_EOS | tagndx 0, size 8 |
| C_FCN / C_BLOCK | lnno 4, endndx 0x10, x_type 0x14 |
| A_SECT | tagndx 0, lnno 4, endndx 0x10 |
| A_MACRO | lnno 4, endndx 0x10 |
| C_FIELD | size 8 |
| function | tagndx 0, fsize 4, lnnoptr 0xc, endndx 0x10 |
| array | tagndx 0, lnno 4, size 8, dimen[4] at 0xc |
| struct/union/enum (types 8/9/10) | tagndx 0, size 8 |

## String table

A big-endian length word (counting itself), then NUL-terminated strings; offsets are
counted from the start of the length word (the first string is at offset 4).

## Other file formats

- DSPLIB libraries: concatenated members, each `!<H> <name> <size> <time>\r\n` followed
  by `<size>` bytes (old format `-h- ...` with one pad byte). See src/dsplib/dsplib.c.
