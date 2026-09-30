/* sim56000.h - shared definitions of the reconstructed DSP56000 simulator
 * (Motorola SIM56000.EXE, CLAS56 v6.3.0, 01-15-1999).
 *
 * Written from the naming-pass notes re/notes/SIM56000/ (the group .md files).  The original passes a handful of
 * "current" pointers around and reaches everything through raw byte offsets; the reconstruction keeps
 * the data flow but uses real struct members.  Struct layout is therefore NOT the original's; every
 * member carries a comment naming the original offset (+0x..) where it is known.
 *
 * Portability rules (see CLAUDE.md): C89 only, int may be 16 bits, so every value that can exceed
 * 16 bits is `long` / `unsigned long`; 24-bit DSP words, addresses and counters are `long`.
 *
 * Static tables (device types, register descriptors, opcode tables, ...) are declared in the
 * generated simdata.h (re/scripts/gentab_sim.py); function prototypes are in the generated
 * simproto.h (re/scripts/genproto_sim.py).  Uninitialized (BSS) globals are declared here.
 */
#ifndef SIM56000_H
#define SIM56000_H

#include <stdio.h>
#include <setjmp.h>
#include "simdata.h"

/* ------------------------------------------------------------------ word types */
typedef unsigned long uword;     /* one simulated 24/32-bit word, kept in 32 bits */

#define SIM_BANNER "MOTOROLA DSP56000 SIMULATOR:  VERSION 6.3.0 01-15-1999"
#define MAX_DEVICES     32       /* max_devices (0x4aab0c); DVn slots */
#define NUM_CHIPTYPES   13       /* chiptype_tab slots (10 filled) */
#define NUM_COMMANDS    39       /* command_entries[] */
#define HISTORY_SIZE    32       /* history_size default */
#define CMDSTACK_SIZE   10
#define SCROLLBACK_LINES 100
#define SCROLLBACK_WIDTH 256
#define LINE_MAX_CHARS  256      /* command line / text buffers */

/* ------------------------------------------------------------------ architecture / COFF magic */
#define MAGIC_DSP56000  0x2c5L
#define MAGIC_DSP96000  0x2c6L
#define MAGIC_DSP56100  0x2c7L
#define MAGIC_DSP56300  0x2c8L
#define MAGIC_DSP56800  0x2c9L
#define MAGIC_DSP56600  0x2caL
#define MAGIC_SC100     0x2cbL
#define STATE_FILE_VERSION_WRITING 0x2c4L  /* first int of a state file while being written */
#define STATE_FILE_VERSION         0x2c7L  /* final value; anything else is unloadable */

/* dev_type.family bit masks (device types) */
#define FAM_56000   0x0001L
#define FAM_56001   0x0002L
#define FAM_56002   0x0004L
#define FAM_56004   0x0008L
#define FAM_56004ROM 0x0108L
#define FAM_56005   0x0044L
#define FAM_56007   0x0200L
#define FAM_56009   0x0400L
#define FAM_56011   0x1000L
#define FAM_56012   0x2000L
#define FAM_68356   0x0080L
#define FAM_56030   0x0800L
#define FAM_OLD_CORE(f)   (((f) & 3L) != 0)          /* 56000/56001 class ((fam & 3), fam < 4) */
#define FAM_PIN_MODEL(f)  (((f) & 0x3618L) == 0)     /* has the X/Y/P pin model */
#define FAM_BOOTROM_RESET(f) (((f) & 0x3678L) == 0)  /* reset PC $E000 capable */

/* ------------------------------------------------------------------ memory spaces */
#define SPACE_P 0
#define SPACE_X 1
#define SPACE_Y 2
#define SPACE_L 3
/* region classes returned by region_of(): 0xd P internal RAM, 0xe P ROM/pi, 0xf P external,
   0x12 X internal, 0x13 X ROM/peripherals, 0x14 X external, 0x17 Y internal, 0x18 Y ROM, 0x19 Y external,
   0x1c memory-mapped register bank, 0x1d..0x5c EMI DRAM banks, 0x11d extended P */
/* mem_region.attr bits */
#define REGION_ROM       0x00000008L
#define REGION_PERIPH_IO 0x00010000L   /* memory mapped peripheral I/O */
#define REGION_HOLEY     0x00020000L
#define REGION_MDISK     0x01000000L   /* words live in the sparse "memory disk" (mdisk) */

/* ------------------------------------------------------------------ per-register flags (sim block, flags[reg]) */
#define RF_READ_TOUCHED   0x00050000L  /* 0x10000|0x40000 read since last display */
#define RF_WRITTEN        0x000a0000L  /* 0x20000|0x80000 written/changed (display refresh) */
#define RF_INPUT_INJECT   0x00400000L  /* input file/pin injection on read */
#define RF_WATCH_MASK     0x01800000L  /* watch / break on change set */
/* reg_desc.flags */
#define RD_WRITE_EFFECT   0x40L        /* write goes through the group's write_reg */
#define RD_READ_EFFECT    0x20L

/* ------------------------------------------------------------------ device event / stop flags (dev.flags @ +0x44) */
#define DEVF_INSN_BOUNDARY 0x01L
#define DEVF_REPEAT_BOUNDARY 0x02L
#define DEVF_ILLEGAL_OP    0x04L       /* 'Illegal Op-Code Encountered' */
#define DEVF_REG_WRITTEN   0x08L
#define DEVF_SPECIAL_INSN  0x10L       /* STOP/WAIT entry (56002+) */
#define DEVF_SKIP_HOUSEKEEP 0x20L
#define DEVF_ERROR_TEXT    0x40L

/* ------------------------------------------------------------------ pins */
#define PIN_BLOCK_WORDS 74             /* 0x128 bytes per pin block: 0 inputs, 1 enables, 2 outputs, 3 drive masks ... (see exec_a.md 1.3) */
#define PIN_BLOCK_CORE   0
#define PIN_BLOCK_ADDR   1
#define PIN_BLOCK_DATA   4
#define PIN_BLOCK_GPIO   6

/* ------------------------------------------------------------------ expression mode word (expr_mode) */
#define XM_IEEE_FLOAT     0x00000080L  /* 32-bit IEEE-float device */
#define XM_DOUBLE_MOVE    0x00001000L
#define XM_ADDR16_DEFAULT 0x00000008L
#define XM_ADDR24         0x00000200L
#define XM_ADDR19         0x00000400L
#define XM_ADDR16         0x00000800L
#define XM_NOREG          0x00010000L  /* no register parsing */
#define XM_ACC_EXT8       0x01000000L  /* 8 accumulator extension bits (56-bit) instead of 4 */
#define XM_WORD24         0x04000000L
#define XM_WORD16         0x10000000L
#define XM_WORD_MASKS     0x14000000L
/* value node flags (struct val.flags) */
#define VF_INT      0x0100L
#define VF_FLOAT    0x0200L
#define VF_BOOL     0x2000L
#define VF_REG      0x4000L
#define VF_SIZE1    0x01L              /* single word */
#define VF_SIZE2    0x02L              /* double 48 bit */
#define VF_SIZE4    0x04L              /* long / accumulator 96 bit */

/* value node of the expression evaluator (0x28 bytes in the original) */
struct val {
    double d;                          /* +0 floating value (flags & VF_FLOAT) */
    unsigned long lo, hi, ext;         /* +8 limb 0 (low word), +0xc limb 1, +0x10 limb 2 (accumulator extension) */
    unsigned long addr;                /* +0x14 address / raw copy */
    unsigned long id;                  /* +0x18 memory space id or register id */
    unsigned long flags;               /* +0x1c VF_* | size code bits copied from the region attribute */
    unsigned long f20;                 /* +0x20 */
    long idx;                          /* +0x24 index into the space table */
};
/* disassembler formatter state (asm.c): which effective addresses an instruction touches and their selectors */
extern unsigned long dis_effect_flags;             /* 0x4dbea0 bits: 1 a, 2 b, 4 c, 8 b, 0x10 e, 0x20 d */
extern unsigned long dis_sel_a, dis_sel_b, dis_sel_c, dis_sel_d, dis_sel_e;     /* 0x4dbea4.. */
extern unsigned long dis_val_b, dis_val_c, dis_val_a, dis_val_d, dis_val_e;     /* 0x4dbeb8.. */
extern char dis_hex_ea[16], dis_hex_b[16], dis_hex_c[16];                         /* 0x4dbe88, 0x4dbed0, 0x4dbee8 */
extern long dis_cpu_level;                         /* 0x4dbefc */
/* register/address information of a disassembled instruction (disasm.c; +0x14 rn, +0x34 nn, +0x54 mn in the original) */
struct dis_info {
    long f0[5];
    unsigned long rn[8], nn[8], mn[8];   /* address, offset and modifier registers */
    long nwords;                         /* +0x74 instruction words (0 for "dc") */
    unsigned long flags;                 /* +0x78 effective address effects (dis_effect_flags) */
    unsigned long ea_a, ea_b, ea_c;      /* +0x7c, +0x80, +0x84 computed addresses */
};
extern char *optr;                                 /* 0x5029e0 expression/assembler text cursor */
extern long asm_result[3];                         /* 0x5059e0 [0] = -1 after an expression error */
extern char *expr_err_msg;                         /* 0x5059f0 */
extern void dbl_unpack(double d, unsigned long *hi, unsigned long *lo);   /* IEEE bit halves (exprmp.c) */
extern double dbl_pack(unsigned long hi, unsigned long lo);
extern unsigned long expr_mode;                    /* 0x5029dc expression mode word (XM_*) */
/* mode word of the current device: cur_dtype->flags unless the type carries the +0x4e8 hook (radix.c) */
extern unsigned long dev_mode_word(void);

/* ------------------------------------------------------------------ chip descriptors (from simdata.h)
 * dev_type, periph_desc, group_def, reg_desc, mem_region, core_vtable are generated. */
/* chiptype_tab (struct dev_type **, -> the 13-slot array at 0x4aaac8, 10 filled) and num_chiptypes (13) are
 * generated in simdata.h together with dev_state_tab (struct sim_state **) and dev_tab (struct dev_inst **). */

/* ------------------------------------------------------------------ pin/peripheral runtime records */
struct pin_block {                     /* 0x128 bytes (dev+0x18 + n*0x128) */
    uword w[PIN_BLOCK_WORDS];
};

/* sorted interval map (memory tags: breakpoint kinds, display marks, input/output tags) */
struct range_node {
    long value;
    unsigned long lo, hi;
    struct range_node *next;
};

/* access history of a memory region: 16 last addresses/values, read and write ring (sim+4 + region*0x12c) */
struct access_ring {
    long total, idx, count;
    unsigned long addr[16];
    unsigned long val[16];
};
struct region_stat {                   /* 0x12c bytes per region */
    struct range_node *bp_map;         /* +0  breakpoint kinds */
    struct range_node *mark_map;       /* +4  display marks */
    struct range_node *map8;           /* +8 */
    struct range_node *in_tags;        /* +0xc input tags */
    struct range_node *out_tags;       /* +0x10 output tags */
    struct access_ring rd, wr;         /* +0x14 read ring, +0xa0 write ring */
};

/* memory disk (sparse memory with disk spill, mdisk.c) */
struct mdisk_list;
struct mdisk_node;
#define MDISK_BLOCK_WORDS 256L
#define MD_SWAPPED  1
#define MD_CONSTANT 2
#define MD_RESIDENT 4
struct mdisk_node {                    /* 20 bytes: circular doubly linked list; a node covers [start, next->start), the sentinel has start 0 */
    struct mdisk_node *next, *prev;
    unsigned long start;
    long state;                        /* MD_* */
    union { unsigned long fill; long file_off; uword *block; } u;   /* fill value / offset in swap file / 256 resident words */
};
struct mdisk_list {                    /* per flagged group: most recently used node and the one before */
    struct mdisk_node *cursor;
    struct mdisk_node *prev_cursor;
};
struct mdisk_slot {                    /* free block slot in the swap file */
    struct mdisk_slot *next;
    long offset;
};

/* memory region runtime block (dev+0xc + region*0x10) */
struct mem_block {
    struct mdisk_list md;              /* sparse/disk list when the region is REGION_MDISK (words == NULL then) */
    uword *words;                      /* +8: one word per address */
    long disabled;                     /* +0xc: OMR remap hooks flip this to alias blocks */
};

/* ------------------------------------------------------------------ device instance (`dev`, 0x168 bytes; cur_dev = dev_tab[n]) */
struct dev_inst {
    long type;                         /* +0 chip type index */
    long number;                       /* +4 device number (DVn) */
    uword **regs;                      /* +8 regs[group] -> register value array of that group */
    struct mem_block *mem;             /* +0xc one per region */
    struct pin_block *pins;            /* +0x18 one per pin block (chip periph 0x30 entries) */
    long pc;                           /* +0x1c PC of the instruction being executed */
    long cycles;                       /* +0x20 cycle counter */
    long icount;                       /* +0x24 instruction counter */
    uword *ctl;                        /* +0x40 cpu control block: [0] pin inputs, [2] ==1 stopped, [3] reset latch, [4] phase */
    long flags;                        /* +0x44 DEVF_* */
    long stop;                         /* +0x48 abort / suppress boundary events */
    FILE *swapfile;                    /* +0x10 mdisk swap (m_pdisk) */
    struct mdisk_slot *free_slots;     /* +0x14 free slots in the swap file */
    char workdir[LINE_MAX_CHARS];      /* +0x58 device working directory (".\" default) */
    void *hook_data;                   /* +0x158 chip hook data */
};

/* ------------------------------------------------------------------ breakpoints (node 0x250 bytes) */
#define BP_ADDRESS   0     /* pc match */
#define BP_MEM_R     2
#define BP_PIN1      3
#define BP_PIN2      4
#define BP_PIN3      5
#define BP_EXPR      6
#define BP_REGCMP    7
#define BP_PC_EQ     8
#define BP_MEM_RW9   9     /* 9..0xb add the space filter 0x80000 */
#define BP_CEXPR     12    /* C expression break */
#define BPA_HALT     0     /* action names: g_bp_action_names (h i1..i4 ...) */
#define BPA_COUNT1   1
#define BPA_STOP     6
#define BPA_COMMAND  7     /* x: execute command string */
struct breakpoint {
    long number;                       /* +0 */
    long type;                         /* +4 BP_* */
    long flags;                        /* +8 bit0 always, bit1 only when dev.flags bit 3 */
    long action;                       /* +0xc BPA_* */
    char text[256];                    /* +0x10 break expression/address text */
    char command[256];                 /* +0x110 command string for action x */
    long enabled;                      /* +0x210 */
    unsigned long param[10];           /* +0x218 parameters (+2 lo addr, +3 hi addr, +0x10 pin/space, +0x14 reg index) */
    unsigned short cmp_op;             /* +0x236 ne le lt ge gt eq */
    unsigned short space, index;       /* +0x23c/+0x238 for pin breaks */
    struct breakpoint *next;           /* +0x240 */
    struct cnode *cexpr;               /* +0x244 parsed C expression (BP_CEXPR) */
    long cexpr_a, cexpr_b;             /* +0x248/+0x24c saved with the tree */
};

/* watch list entry (node 0x124 bytes) */
struct watch {
    unsigned long id;
    char text[256];
    long kind;                         /* 0 = compiled expression tree follows in the state file */
    long radix;
    unsigned long v1, v2;              /* +0x10c/+0x110 */
    struct cnode *tree;
    long tree_a, tree_b;               /* +0x11c/+0x118 */
    struct watch *next;                /* +0x120 */
};

/* instruction history record (0x2c bytes, ring `history_size` entries) */
struct hist_rec {
    unsigned long w[11];               /* pc + 10 words (saved as "%lx" + 10 x " %lx") */
};

/* ------------------------------------------------------------------ I/O channels (input/output commands) */
#define IO_MEMORY   0
#define IO_REGGRP   1
#define IO_PERIPH   2
#define IO_PIN_S    4
#define IO_SPACE_OF_OTHER_DEV 7
#define IO_SCALAR   8
#define IO_PERIPH_BITS 9
#define RADIX_BINARY  0
#define RADIX_DECIMAL 1
#define RADIX_FLOAT   2
#define RADIX_HEX     3
#define RADIX_UNSIGNED 4
struct io_loop {                       /* repeat loop read from an input file: ( ... ) n */
    long fpos, started, remaining;
    struct io_loop *next;
};
struct io_chan {                       /* 0x1e8 bytes, calloc'ed by the input/output command */
    char name[256];                    /* +0x000 file / pin name */
    char text[80];                     /* +0x100 user visible name in reports */
    FILE *fp;                          /* +0x150 NULL = terminal */
    long type;                         /* +0x154 IO_* */
    long a;                            /* +0x158 space / peripheral index */
    long first;                        /* +0x15c address / pin index */
    long last;                         /* +0x160 */
    long serial;                       /* +0x164 */
    long b, c;                         /* +0x168, +0x16c */
    long peer_dev;                     /* +0x174 device for `input pin dvN:pin` */
    unsigned long cur[10];             /* +0x180 current value cell */
    unsigned long cur2[10];            /* +0x1a8 */
    long immediate;                    /* +0x1d0 timed value pending */
    long radix;                        /* +0x1d4 */
    long countdown;                    /* +0x1d8 cycles until next value, -1 = EOF */
    struct io_loop *loops;             /* +0x1dc */
    struct io_chan *next;              /* +0x1e0 */
    long id;                           /* +0x1e4 */
};

struct grp_rt {                        /* per peripheral group runtime record (sim_state.regflags) */
    long f0;
    unsigned long *flags;              /* +4 per register runtime flags (0x2000000 float, 0x2000 ...) */
};
/* pending operand references of the instruction being executed (oprefs.c) */
struct op_ref {                        /* 0x14 bytes */
    long cat;                          /* category from ref_kind_info (0 = free slot) */
    long rw;                           /* 0 write, 1 read, 2 read+write */
    long addr, a3, a4;
};
/* statistics record of one decoded instruction (insstat.c, igrp.c, oprefs.c) */
struct stat_op {                       /* 0x1c bytes: copy of a DEC operand {kind, value, aux, space} + 3 counters */
    long w[7];
};
struct stat_link {                     /* list of L: move operand pairs (static nodes in insstat.c) */
    long f0;
    struct stat_link *next;            /* +4 */
    struct stat_op *ops;               /* +8 two consecutive operands */
};
struct insn_stat {
    long f0;                           /* +0 */
    long word0, word1;                 /* +4, +8 instruction word and extension word */
    long flags;                        /* +0xc */
    long cat;                          /* +0x10 category (mnemonic id, or 0x63..0x65 for move forms) */
    struct stat_op op[4];              /* +0x14 operands */
    struct stat_link *link;            /* +0x84 L: move list */
    long aux;                          /* +0x88 condition code field of the instruction */
    long ccr, omr;                     /* +0x8c, +0x90 status registers when the record was taken */
    long pad94[21];
    long cc_true;                      /* +0xe8 condition evaluated true (eval_cc of ccr and aux) */
};

/* ------------------------------------------------------------------ simulator block (`state`, 0x4408 bytes; cur_sim = sim_tab[n])
 * Only members with documented meaning are listed (offsets from the original in comments). */
struct sim_state {
    struct region_stat *rstat;         /* +4  per region statistics/tags (nregions x 0x12c) */
    struct grp_rt *regflags;           /* +8  per group runtime record (8 bytes each): flags[reg] arrays */
    long version_word;                 /* +0xc.. sv_var.stat block */
    long var10, var18, var1c, var20, var24, var28, var2c;
    long default_radix;                /* +0x30 (1 = decimal) */
    long step_mode;                    /* +0x34 0 go, 1 step n, 2 trace, 3/4 counters, 5..0x15 source level step machine */
    long var40, var44;
    FILE *log_fp;                      /* +0x48 session log */
    char log_name[LINE_MAX_CHARS];     /* +0x4c session log file name */
    struct io_chan *in_list;           /* +0x14c inputs */
    struct io_chan *in_timed;          /* +0x150 */
    struct io_chan *out_delta;         /* +0x154 outputs (delta format) */
    struct io_chan *out_stamp;         /* +0x158 outputs (stamped format) */
    long stop_repeat, break_num;       /* +0x28 (repeat count), +0x2c (current break number) */
    struct watch *watches;             /* watch list */
    struct breakpoint *breakpoints;    /* +0x3e78 */
    long nbreak;
    long exec_stats[64];               /* +0x490 instruction statistics counters (stats_base) - size TBD, see exec_a.md 7 */
    struct hist_rec *history;          /* +0x3fc8 history_size entries */
    long hist_head, hist_count;        /* +0x3fc0, +0x3fc4 */
    long scroll_head, scroll_off;      /* +0x3fbc ring header {head, scroll} */
    char *scrollback;                  /* +0x3fc0 SCROLLBACK_LINES x 256 */
    long view_mode;                    /* +0x4400: 0 console, 1/2 windows */
    long prof_state;                   /* +0x3c30 profiler: 0 off 1 armed 2 running 4 complete */
    long hio_enabled;                  /* +0x404c */
    long hio_send[4], hio_recv[4];     /* +0x4050.., +0x4060.. host I/O buffers */
    long hio_send_addr, hio_recv_addr;
    long afi_count;                    /* +0x4088 host file table */
    struct { long flags; long fd; char *name; long pos; } afi[20];
    struct { long flag; char name[256]; } redirect[3];      /* +0x408c stdin/stdout/stderr redirection */
    long fopen_used[20];               /* +0x43a4 stream in-use flags (FOPEN_MAX table) */
    char *source_file;                 /* +0x4018 current source file */
    struct src_file *src_files;        /* +0x4020 source index (12-byte entries) */
    struct dbg_db *dbg;                /* debug information (symbols, lines, sections) */
    void *cdb;                         /* C-debugger data of this device (frames at +0x3fac/+0x3fb0/+0x3fb4) */
    struct prof_ctx *prof;             /* profiler context (+0x490 region) */
    struct op_ref refs[20];            /* +0x294 pending operand references */
    long regs_cached;                  /* +0x48c the run loop has cached SR/OMR in sr_cache/omr_cache */
    unsigned long sr_cache, omr_cache; /* +0x480, +0x484 */
    long flag_428;                     /* +0x428 set when a `dc`-style (kind 0x23) instruction was seen by the profiler */
};
/* dev_state_tab (0x4a8d98 -> 0x4dba88, 32 slots) and dev_tab (0x4aab10 -> 0x4dbb08, 32 slots): see simdata.h */
extern struct sim_state *cur_sim;                  /* 0x50578c */
extern struct dev_type  *cur_dtype;                /* 0x505790 */
extern void             *cur_itype;                /* 0x505794 instruction-set/ops descriptor */
extern struct dev_inst  *cur_dev;                  /* 0x505798 */
/* cur_dev_index (0x4a8dcc) is generated in simdata.h */

/* ------------------------------------------------------------------ COFF / debug information (big endian on disk, decoded byte by byte) */
struct coff_filhdr {                   /* 0x1c bytes */
    long magic, nscns, timdat, symptr, nsyms, opthdr, flags;
};
struct coff_scnhdr {                   /* 0x34 bytes on disk (13 dwords), see cofdmp */
    char name[9];
    long paddr, pspace, vaddr, vspace, size, scnptr, relptr, lnnoptr, nreloc, nlnno, flags;
};
struct dbg_section {                   /* 0x20-byte in-memory record per section (index = section number) */
    long line_addr, line_space;        /* +0 first line record */
    long paddr, pspace;                /* +8, +0xc */
    long size_or_vaddr;                /* +0x10 (vaddr when flags & 0x400) */
    long nlnno;                        /* +0x14 */
    long first_line;                   /* +0x18 running index of first line record */
    long sym_back;                     /* +0x1c class 0xca symbol back reference */
};
#define SCN_PADDR_IS_VADDR 0x400L
#define SCN_LINES_REMAP    0x800L
#define SCN_MACRO          0x1000L
struct dbg_symbol {                    /* 0x20-byte symbol record (expanded from the 18-byte COFF form) */
    char name[9];
    long strx;                         /* string table offset when name[0..3] == 0 */
    long value, space, scnum, type, sclass, numaux;
};
struct dbg_line {                      /* 12-byte line record */
    long addr, space, line;            /* line 0 = function marker */
};
struct src_file {                      /* 12-byte source file entry */
    long nlines;
    long *offset;                      /* offset[line] = ftell, 1-based */
    char *path;
};
/* storage classes of the debug symbols */
#define C_CEXT 2
#define C_LABEL_D2 0xd2L
#define C_LABEL_D3 0xd3L
#define C_LABEL_D5 0xd5L
#define C_LABEL_D6 0xd6L
#define C_LABEL_D7 0xd7L
#define C_FILE_67  0x67L
#define C_FILE_C8  0xc8L
#define C_SCOPE_C9 0xc9L
#define C_SECT_CA  0xcaL
#define C_MACRO_CB 0xcbL
struct dbg_db {
    struct coff_filhdr hdr;
    struct dbg_section *sections;
    struct dbg_symbol *syms; long nsyms;   /* +0x3fe0 / +0x3fd8 */
    char *strtab; long strtab_size;        /* +0x3fe4 / +0x3fe8 */
    struct dbg_line *lines; long nlines;   /* +0x3ff0 / +0x3fec (sorted by address; line word 0 = continuation) */
    long default_space;                    /* +0x3fb8 */
    long data_model;                       /* +0x30 data-model flag 1..4 */
};

/* ------------------------------------------------------------------ C debugger (cdb*) */
/* type kinds (low 4 bits), derived-type levels in 2-bit fields: 0x10 pointer, 0x20 function, 0x30 array */
#define K_VOID 1
#define K_CHAR 2
#define K_SHORT 3
#define K_INT 4
#define K_LONG 5
#define K_FLOAT 6
#define K_DOUBLE 7
#define K_STRUCT 8
#define K_UNION 9
#define K_ENUM 10
#define K_UCHAR 12
#define K_USHORT 13
#define K_UINT 14
#define K_ULONG 15
#define K_PTR   0x10L
#define K_FUNC  0x20L
#define K_ARRAY 0x30L
#define K_FRAC   0x10000L     /* 0x10000 fract .. 0x10005 3-word accumulator */
/* storage classes of a value */
#define SC_RVALUE 0
#define SC_AUTO 1
#define SC_EXTERN 2
#define SC_STATIC 3
#define SC_REGISTER 4
#define SC_ARG 9
#define SC_REGPARM 0x11
#define SC_FIELD 0x12
#define SC_DEVREG 0x80000000UL
struct cdb_val {                       /* 0x40 bytes, copied wholesale */
    unsigned long alt[3];              /* +0x00 float/double image halves */
    unsigned long w[3];                /* +0x0c low, mid/high, extended words */
    unsigned long addr;                /* +0x18 address / register number / symbol value */
    unsigned long space;               /* +0x1c memory space or register block index */
    unsigned long type;                /* +0x20 K_* kind word */
    unsigned long sclass;              /* +0x24 SC_* */
    unsigned long tag;                 /* +0x28 tag symbol index (struct/union/enum) or size info */
    unsigned long dim[4];              /* +0x2c dimensions (1 = scalar; bit width for bit-fields in dim[0]) */
    short valid;                       /* +0x3c lvalue read-in valid */
};
/* expression tree node of the C expression evaluator (0x1c bytes) */
struct cnode {
    struct cnode *l;                   /* +0 left child */
    struct cnode *m;                   /* +4 middle child / unary operand / called function / then of ?: */
    struct cnode *r;                   /* +8 right child */
    long op;                           /* +0xc 0 leaf, ASCII operator, or yacc token >= 0x123 */
    struct cdb_val *value;             /* +0x10 (0x40-byte block) */
    struct cnode_list *args;           /* +0x14 argument list of call nodes */
    long evaluated;                    /* +0x18 1 = already evaluated/constant */
};
struct cnode_list {                    /* 8-byte list cell */
    struct cnode *node;
    struct cnode_list *next;
};
#define OP_COND 0x123          /* ?: */
#define OP_MULEQ 0x124
#define OP_DIVEQ 0x125
#define OP_MODEQ 0x126
#define OP_ADDEQ 0x127
#define OP_SUBEQ 0x128
#define OP_ANDEQ 0x129
#define OP_XOREQ 0x12a
#define OP_OREQ  0x12b
#define OP_SHLEQ 0x12c
#define OP_SHREQ 0x12d
#define OP_OROR  0x12e
#define OP_ANDAND 0x12f
#define OP_EQ    0x130
#define OP_NE    0x131
#define OP_LE    0x132
#define OP_GE    0x133
#define OP_SHL   0x134
#define OP_SHR   0x135
#define OP_SIZEOF 0x138
#define OP_ARROW 0x139
#define OP_INTCONST 0x13b
#define OP_CHARCONST 0x13c
#define OP_FLOATCONST 0x13d
#define OP_SYMBOL 0x13e
#define OP_TYPEDEFNAME 0x10f
#define OP_CAST  0x13f
#define OP_PREINC_DEC_FIRST 0x140   /* 0x140..0x143 pre/post ++/-- */
#define OP_INDEX 0x144
#define OP_CALL  0x145
#define OP_COMMA 0x146
#define OP_ARRAY2PTR 0x148
#define OP_FUNC2PTR  0x149
struct saved_reg {                     /* 0x14 bytes, prologue scan result */
    char name[8];
    long stack_off;                    /* +8 */
    long regcode;                      /* +0xc */
    struct saved_reg *next;            /* +0x10 */
};
struct frame {                         /* back trace frame node (0x1c bytes) */
    char *text;                        /* "#%-2d p:0x%lx in %.50s (" args ")" */
    long pc, fp, sp;
    struct saved_reg *saved;
    struct frame *prev, *next;
};
/* generic AVL tree (profiler) */
struct avl_node {                      /* 0x10 bytes */
    long height;
    struct avl_node *left;
    void *item;
    struct avl_node *right;
};
struct avl_tree {                      /* 0xc bytes */
    struct avl_node *root;
    long count;
    long cmp_index;                    /* index into avl_cmp_tab */
};

/* ------------------------------------------------------------------ profiler context (sim+0x490; only documented members) */
#define PROF_FL_COFF_BAD    0x01L
#define PROF_FL_UNDECODED_P 0x08L
#define PROF_FL_NO_FILE     0x10L
struct prof_ctx {
    long flags;                        /* +0x34e0 */
    char *out_name;                    /* +0x5c default "metrics.log" */
    char *title;                       /* +0x68 */
    long words_executed;               /* +0xac */
    long insn_all, insn_cond;          /* +0xb0, +0xb4 */
    long cycles;                       /* +0xc0 */
    long alloc_mode;                   /* +0x3500 (1 = prof_malloc, else arena) */
    long src_limit;                    /* +0x3504 (-1 = report by address) */
    long mode;                         /* +0x37a0 (1 no instructions executed, 3 dynamic data) */
    struct avl_tree *addr_tree;        /* +8 */
    struct avl_tree *file_tree;        /* +0xc */
    void *pool;                        /* +0x34e8 string pool / arena */
    long kind_on[128];                 /* +0xc8 statistics enabled per instruction kind */
    long cnt_plain[200];               /* +0x2648 executed instructions per kind (no parallel move) */
    long cnt_pm1[200];                 /* +0x2968 ... with one parallel move */
    long cnt_pm2[200];                 /* +0x2c88 ... with two parallel moves */
    long cnt_pm[6];                    /* +0x2fc8 one move (no/other kind), two moves; L: move classes */
    long grp[9][16];                   /* +0x2fe0 per instruction group: [0] total, [mode bucket] (igrp.c) */
};
extern struct prof_ctx *prof_ctx;                  /* 0x505b64 */

/* ------------------------------------------------------------------ helpers implemented in util.c-style modules */
/* 24-bit words in state files are written with "%lx"; masks below reproduce 32-bit wraparound on wider longs */
#define MASK32 0xffffffffUL
#define MASK24 0xffffffUL

/* big-endian byte decode/encode of COFF/CLD fields (never read structs raw) */
#define BE16(p) ((((unsigned long)(unsigned char)(p)[0]) << 8) | (unsigned char)(p)[1])
#define BE32(p) (((unsigned long)(unsigned char)(p)[0] << 24) | ((unsigned long)(unsigned char)(p)[1] << 16) | \
                 ((unsigned long)(unsigned char)(p)[2] << 8) | (unsigned long)(unsigned char)(p)[3])

/* original getenv/time convention of the project: SOURCE_DATE_EPOCH overrides time(NULL) */

#include "simproto.h"

#endif /* SIM56000_H */
