/*
 * dsplnk.h - shared declarations of the DSPLNK reconstruction
 * (Motorola DSP Linker 6.3.7, DSPLNK.EXE of CLAS56 v6.3; lnkglb.c v1.15).
 *
 * Every structure, constant, shared global (defined in lnkglb.c) and every
 * function called from another source file is declared here.  Offsets in
 * the comments are the ORIGINAL 32-bit byte offsets; the C layout is free
 * (structures are never read or written raw - COFF is decoded byte by byte
 * by the util.c codecs), but field order follows the original offsets.
 *
 * Portability: ANSI C89 only; int may be 16 bits, so every value that can
 * exceed 16 bits (addresses, DSP words, counts, file offsets, memory space
 * codes, flag words) is long / unsigned long.  Where the original relies on
 * 32-bit wraparound, mask with M32().
 *
 * Name map of the architecture notes (p1..p6) to the names used here:
 *   TERM (p1) = EXPR;  PIECE (p5) = SECTION;  class node / "SECTION" of p5 =
 *   SECNODE;  SECMAP (p1/p2) = MODSEC;  EXTSYM (p5) / EXT (p1) = XREF;
 *   OBJSYM (p5) = SYMSLOT;  KWENT (p5) = KEYWORD;  REGSEC (p5) = SECREF;
 *   SECSTK (p2) = SECNEST;  XREC (p1) = FILEEXT;  XREFNAME (p2) = STRNODE.
 *   42c8ba ext_lookup = sym_lookup (GLOBAL symbols); 42cd0d = xref_lookup;
 *   42cae9 ext_add = xref_add; 42ceac sym_dedup_locals = xref_purge;
 *   42a38f sec_piece_new = sdi_add; 42a767 sec_class_iter_next = sdi_next_form;
 *   42fc54 mem_map_normalize = map_to_space; 42f2b0 mem_space_from_index =
 *   index_mem_space; 42f22f get_mem_space = mem_space_index; 42f1ca
 *   (old) mem_space_index = mem_bits_space; 42c373 file_name_intern =
 *   region_get; 40a571 eval_line = eval_expr; 40ca80 term_stack_pop =
 *   free_expr; 427ebb obj_write_section = obj_write_module; 429641/429716/
 *   429811/429870 sym_wrt_rec/str/name/all = obj_add_syment/obj_add_string/
 *   obj_add_comment/obj_write_set_syms; 42944b sym_wrt_init =
 *   obj_add_file_secsyms; 426437 obj_reserve_entry_get = memctl_reserve_piece;
 *   419ff9 find_overlay_record = find_buffer_record; 41a425 get_alloc_record
 *   = get_overlay_record; 41999e select_counter_block = select_counters.
 */
#ifndef DSPLNK_H
#define DSPLNK_H

#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define M32(x)  ((unsigned long)(x) & 0xffffffffUL)   /* 32-bit wraparound */

/* ======================================================================
 * Constants
 * ====================================================================== */

/* sizes */
#define HASHSIZE        2003        /* 0x7d3: sym_hash, sec_hash, xref_hash (hash_name % 2003) */
#define NAMEBUF_SIZE    520         /* namebuf, title_name, ctl_token (0x208) */
#define ERRSYM_SIZE     516         /* err_symbol 0x461b40 */
#define CFORM_BUFSIZE   520         /* eval.c cform_buf 0x461938 (port: may be larger) */
#define NTARGETS        8           /* target_tab entries (plus zero terminator) */
#define NMEMIDX         8           /* memory space indices MI_* */
#define MAXSYMLEN       0x200       /* get_symbol limit */
#define IOBUFSIZE       0x800       /* set_file_buffer setvbuf size */
#define NFUNCS          14          /* func_tab entries */
#define NBINOPS         24          /* binop_tab slots */
#define NMEMCTL_KW      17          /* memctl_kw_tab */
#define NMAP_OPT        12          /* memctl_mapopt_tab */
#define NXOPT           33          /* memctl_xopt_tab */

/* COFF magic numbers (FILHDR.f_magic, TARGET.magic); target index = order */
#define M_DSP56000      0x2c5L
#define M_DSP96000      0x2c6L
#define M_DSP56100      0x2c7L
#define M_DSP56300      0x2c8L
#define M_DSP56800      0x2c9L
#define M_DSP56600      0x2caL
#define M_SC100         0x2cbL      /* table name "100"; -c makes an ELF debug file */
#define M_DSP56700      0x2ccL
#define TGT_56000       0           /* target_index values */
#define TGT_96000       1
#define TGT_56100       2
#define TGT_56300       3
#define TGT_56800       4
#define TGT_56600       5
#define TGT_SC100       6
#define TGT_56700       7

/* FILHDR.f_flags */
#define F_RELFLG        0x1L        /* absolute file (input: fatal; library member: skipped) */
#define F_EXEC          0x2L
#define F_LNNO          0x4L
#define F_LSYMS         0x8L
#define F_CC            0x10000L    /* C compiler object / linker option -c */
#define F_SDI           0x20000L    /* span-dependent instructions */

/* SCNHDR.s_flags */
#define STYP_PAD        0x8L
#define STYP_TEXT       0x20L
#define STYP_DATA       0x40L
#define STYP_BSS        0x80L
#define STYP_DEBUG      0x100L
#define STYP_BLOCK      0x400L      /* s_vaddr = block length */

/* storage classes (SYMENT.n_sclass) */
#define C_EFCN          (-1L)
#define C_NULL          0L
#define C_EXT           2L
#define C_STAT          3L
#define C_LABEL         6L
#define C_STRTAG        10L
#define C_UNTAG         12L
#define C_ENTAG         15L
#define C_BLOCK         100L        /* ".bb"/".eb" */
#define C_FCN           101L
#define C_EOS           102L
#define C_FILE          103L
#define C_HIDDEN        106L        /* old objects: XDEF class */
#define C_SECT          128L
#define C_SDI           129L
#define A_FILE          200L
#define A_SECT          201L
#define A_MACRO         203L
#define A_GLOBAL        210L
#define A_XDEF          211L
#define A_XREF          212L
#define A_SLOCAL        213L
#define A_ULOCAL        214L
#define A_MLOCAL        215L
#define T_INT           4L
#define T_LONG          5L
#define T_FLOAT         6L
#define DT_PTR          0x10L
#define N_ABS           (-1L)

/* object format version tests (obj_major/obj_minor/obj_rev of the module) */
#define OBJ_OLD()    (obj_major < 5 && (obj_major != 4 || obj_minor < 2))  /* < 4.2 */
#define OBJ_PRE533() (obj_major < 6 && (obj_major != 5 || obj_minor < 4) && \
                      (obj_major != 5 || obj_minor != 3 || obj_rev < 3))   /* < 5.3.3 */

/* section aux flags (input set_current_section) */
#define SA_RUNLOAD      0x20L
#define SA_NEST         0x100L
#define SA_BYTEADDR     0x200L
#define SA_BYTEPACK     0x800L
#define SA_RELOC        0x1000L
#define SA_BUFFER       0x2000L
#define SA_OVERLAY      0x4000L
#define SA_OVLRELOC     0x8000L
#define SA_10000        0x10000L
#define SA_20000        0x20000L
#define SA_40000        0x40000L
#define SA_CLEAR_MASK   0xfffaf48fUL

/* memory spaces (MEMSPEC.mspace, EXPR.space) */
#define MS_P            0L
#define MS_X            1L
#define MS_Y            2L
#define MS_L            3L
#define MS_N            4L          /* none / absolute */
#define MS_E            0x1cL       /* EMI */
#define MS_D            0x11dL
#define MS_U            0x11fL
#define MS_BAD          0xa2c2aL    /* error / incompatible (all mapping helpers) */
/* memory maps (MEMSPEC.mmap = COFF space code) */
#define MM_LAA          5L
#define MM_LAB          6L
#define MM_LBA          7L
#define MM_LBB          8L
#define MM_LE           9L
#define MM_LI           10L
#define MM_PA           0x0bL       /* PB 0xc PE 0xd PI 0xe PR 0xf */
#define MM_XA           0x10L       /* XB..XR 0x11..0x14 */
#define MM_YA           0x15L       /* YB..YR 0x16..0x19 */
#define MM_PT           0x1aL
#define MM_PF           0x1bL
#define MM_EM           0x1cL
#define MM_E0           0x1dL       /* E0..E255 = 0x1d..0x11c */
#define MM_DM           0x11dL
#define MM_P8           0x11eL
#define MM_U            0x11fL
#define MM_U8           0x120L
#define MM_U16          0x121L
/* memory space index (mem_space_index): " XYLPEDU" */
#define MI_NONE         0
#define MI_X            1
#define MI_Y            2
#define MI_L            3
#define MI_P            4
#define MI_E            5
#define MI_D            6
#define MI_U            7
/* location counters */
#define MC_DEFAULT      0L
#define MC_LOW          1L
#define MC_HIGH         2L

/* INFILE.flags */
#define IF_LIBRARY      2L
#define LIB_MAGIC       "!<H>"      /* lnkglb 0x457f98 */
#define LIB_MAGIC_LEN   4           /* lnkglb 0x457fa0 */

/* SYM.flags */
#define SYM_LOCAL       0x20L
#define SYM_GLOBAL      0x40L
#define SYM_XDEF        0x80L
#define SYM_INT         0x100L
#define SYM_FLOAT       0x200L
#define SYM_FRAC        0x400L
#define SYM_LONG        0x800L
#define SYM_REL         0x1000L
#define SYM_BUFFER      0x2000L
#define SYM_OVERLAY     0x4000L
#define SYM_OUTPUT      0x10000L    /* memctl SET/SYMBOL: written by obj_write_set_syms */
#define SYM_SPECIAL     0x20000L    /* memctl SIZSYM/ALIGNSYM */
/* XREF.flags */
#define XREF_GLOBAL     0x40L
#define XREF_XREF       0x80L
#define XREF_DONE       0x100L

/* SECNAME.num */
#define SN_GLOBAL_NUM   0L
#define SN_RESERVE_NUM  (-1L)
/* SECNODE.flags */
#define SN_F40000       0x40000UL
#define SN_SECSIZE      0x200000UL
#define SN_REMAP        0x1000000UL
#define SN_SECPCT       0x2000000UL
/* SECTION.flags */
#define SF_REL          0x1000UL
#define SF_BUF          0x2000UL
#define SF_OVL          0x4000UL
#define SF_LOADRUN      0x8000UL
#define SF_OVLNEW       0x10000UL
#define SF_ALIGNED      0x20000UL
#define SF_SBALIGN      0x800000UL
#define SF_MATCH        0x27000UL
/* SECTION.state */
#define SS_LISTED       0x100UL
#define SS_ADDR         0x200UL
#define SS_MODBUF       0x400UL
#define SS_REVBUF       0x800UL
#define SS_ACTIVE       0x1000UL
#define SS_NOLALIGN     0x2000UL
/* MEMREG.flags / flags2 */
#define MR_BALIGN       0x20000UL
#define MR_SBALIGN      0x800000UL
#define MR_REMAP        0x1000000UL
#define MR2_LISTED      0x100UL
#define MR2_ADDR        0x200UL
#define MR2_OVLLOC      0x1000UL
#define MR2_OVL         0x4000UL
#define MR2_BASE        0x100000UL
#define MR2_SIZE        0x200000UL
#define MR2_HIGH        0x400000UL
#define MR2_BALIGN      0x800000UL
/* SDI flags (SDIPIECE.flags / SDIREC.flags) */
#define SDI_REL         0x1UL
#define SDI_ABS         0x2UL
#define SDI_LONG        0x100UL
#define SDI_MED         0x200UL
#define SDI_NOEXPR      0x2000UL
#define SDI_UNRES       0x10000UL
#define SDI_OVLLR       0x20000UL
#define SDI_MARK        0x40000UL
/* opsize codes (opsize_fits) */
#define OPSZ_U8         8L
#define OPSZ_U12        0xcL
#define OPSZ_S9W        0x45L
#define OPSZ_S7         (-0x4dL)
#define OPSZ_S6         (-0x37L)
#define OPSZ_S15        (-0xfL)
#define OPSZ_S8         (-0x58L)
#define OPSZ_S15X       (-0x5ebL)

/* EXPR */
#define EXPR_INT        0x100L
#define EXPR_FLT        0x200L
#define EXPR_SZCK       0x4000000L
#define EXPR_REL        0x1000L
#define EXPR_OVL        0x4000L
#define EXPR_FWD        0x8000000L
#define EXPR_SIZE_FLT   8L
#define EXPR_STACK_INIT 16L
#define PREC_START      99
#define BIGINT_LIMBS    13
/* operator codes (get_op_code, binop_tab index) */
#define OP_NONE         0
#define OP_ADD          1
#define OP_SUB          2
#define OP_MUL          3
#define OP_DIV          4
#define OP_AND          5
#define OP_OR           6
#define OP_XOR          7
#define OP_MOD          8
#define OP_SHL          9
#define OP_SHR          0xa
#define OP_LT           0xb
#define OP_GT           0xc
#define OP_EQ           0xd
#define OP_LE           0xe
#define OP_GE           0xf
#define OP_NE           0x10
#define OP_LAND         0x11
#define OP_LOR          0x12
#define OP_SIZE         0x13
#define OP_SPACE        0x14
#define OP_MAP          0x15
#define OP_LINE         0x16
/* @-function ids (func_tab) */
#define FN_FBF          1
#define FN_LRF          2
#define FN_ENC          3
#define FN_FB2          4
#define FN_BYT          5
#define FN_SDI          6
#define FN_SDI2         7
#define FN_IMAX         8
#define FN_IMIN         9
#define FN_CEIL2        0xa
#define FN_SZCK         0xb
#define FN_AENC         0xc
#define FN_LB           0xd
#define FN_HB           0xe

/* memory control file keywords (memctl_kw_tab) */
#define KW_START        1
#define KW_SECTION      2
#define KW_SET          3           /* "set" and "symbol" */
#define KW_BASE         5
#define KW_MAP          6
#define KW_MEMORY       7
#define KW_RESERVE      9
#define KW_BALIGN       10
#define KW_IDENT        11
#define KW_SECSIZE      12
#define KW_REGION       13
#define KW_ENDR         14
#define KW_INCLUDE      15
#define KW_SBALIGN      16
#define KW_SIZSYM       17
#define KW_ALIGNSYM     18
/* MAP OPT keywords (memctl_mapopt_tab) */
#define MO_NOCONST      1
#define MO_NOLOCAL      2
#define MO_NOSECADDR    3
#define MO_NOSECNAME    4
#define MO_NOSYMNAME    5
#define MO_NOSYMVAL     6
#define MO_NOBUFFER     7
#define MO_NOOVERLAY    8
#define MO_NOUNUSED     9
#define MO_GLOBMAP      10
#define MO_NOGLOBSYM    11
#define MO_SYMLEN       12
/* -x options (memctl_xopt_tab); the "no" form is id+1 where it exists */
#define XO_ABC          1
#define XO_AEC          3
#define XO_RO           5
#define XO_ASC          7
#define XO_ESO          9
#define XO_WEX          11
#define XO_OVLP         13
#define XO_SVO          15
#define XO_RSC          16
#define XO_FF           18
#define XO_CSL          20
#define XO_SDI          22
#define XO_SBM          24
#define XO_WVR          26
#define XO_OSP          28
#define XO_ISW          29
#define XO_WDG          30
#define XO_MCM          32
/* memctl_get_token modes */
#define TOK_WORD        0
#define TOK_LINE        4
#define TOK_NEXTLINE    10

/* map layout defaults */
#define MAP_WIDTH_DEF   132
#define MAP_PAGELEN_DEF 66
#define MAP_TOPMARGIN_DEF 3
#define MAP_BOTMARGIN_DEF 3
#define MAP_NAMELEN     16
#define MAP_MAXPAGE     512

/* object file layout */
#define OBJ_FHDRSZ      0x1c
#define OBJ_AOUTSZ      0x3c
#define OBJ_LNKSZ       0x38
#define OBJ_LNKSZ_OLD   0x28
#define OBJ_SCNSZ       0x34
#define OBJ_SYMSZ       0x20
#define OBJ_RELSZ       0xc
#define OBJ_LNNOSZ      0xc
#define OBJ_TEXTDATA_OFF 0x58
#define OBJ_SCN0_ABS    0xc0
#define OBJ_SCN0_INC    0x54

/* option string of dsp_getopt */
#define OPTSTRING "AaB?b?CcE::e::F:f:GgIiL:l:M?m?NnO:o:P:p:QqR?r?SsTtU:u:V?v?X:x:Zz"

/* ======================================================================
 * Structures
 * ====================================================================== */

struct section;
struct secnode;
struct secname;
struct modsec;
struct module;
struct infile;
struct ovlent;
struct sdistat;
struct sdipiece;
struct symlist;
struct memreg;

/* ---- COFF records as held in memory ---------------------------------
 * Numeric fields are decoded big-endian into longs.  Name fields
 * (SYMENT.n_name, SCNHDR.s_name) hold EXACTLY the bytes the x86 original
 * has in memory after its word swap: each 4-byte group of the file bytes
 * reversed (n[0..3] = f[3],f[2],f[1],f[0]; n[4..7] = f[7..4]); the writer
 * reverses them again.  Wherever the original calls swap_words(p,4,2) on
 * a name, the port calls name_swap(p).  "Long name": first 4 bytes zero;
 * the string table offset is then name_off(n) (bytes 4..7 little-endian).
 * AUX entries are 8 plain longs.  The util.c codecs implement this. */

typedef struct filhdr {             /* COFF file header, 0x1c on disk */
    unsigned long f_magic;          /* +0x00 M_* */
    long f_nscns;                   /* +0x04 */
    long f_timdat;                  /* +0x08 */
    long f_symptr;                  /* +0x0c relative to the module start */
    long f_nsyms;                   /* +0x10 symbol slots incl. aux */
    long f_opthdr;                  /* +0x14 0x38 (0x28 old form) / 0x3c absolute */
    unsigned long f_flags;          /* +0x18 F_* */
} FILHDR;

typedef struct lnkhdr {             /* relocatable "linker header", 0x38 (old 0x28) */
    long modsize;                   /* +0x00 */
    long datasize;                  /* +0x04 raw data words (+1 per SDI long form) */
    long endstr;                    /* +0x08 strtab offset of the END expression, <=3/-1 none */
    long secnt;                     /* +0x0c assembler sections (MODULE.secmap size) */
    long ctrcnt;                    /* +0x10 counters = COFF sections (sectref size) */
    long relocnt;                   /* +0x14 */
    long lnocnt;                    /* +0x18 */
    long bufcnt;                    /* +0x1c buffers (buftab size-1) */
    long ovlcnt;                    /* +0x20 overlays (ovltab size-1) */
    long majver;                    /* +0x24 (absent in the 0x28 form -> 4.0.0) */
    long minver;                    /* +0x28 */
    long revno;                     /* +0x2c */
    long unused;                    /* +0x30 */
    long sditot;                    /* +0x34 extra SDI words */
} LNKHDR;

typedef struct aouthdr {            /* absolute optional header, 0x3c (object.c) */
    long magic;                     /* +0x00 0 */
    long vstamp;                    /* +0x04 0 */
    long tsize;                     /* +0x08 */
    long dsize;                     /* +0x0c */
    long bsize;                     /* +0x10 */
    long entry;                     /* +0x14 */
    long entry_mem;                 /* +0x18 */
    long text_start;                /* +0x1c */
    long text_start_mem;            /* +0x20 */
    long data_start;                /* +0x24 */
    long data_start_mem;            /* +0x28 */
    long text_end;                  /* +0x2c */
    long text_end_mem;              /* +0x30 */
    long data_end;                  /* +0x34 */
    long data_end_mem;              /* +0x38 */
} AOUTHDR;

typedef struct scnhdr {             /* section header, 0x34 */
    char s_name[8];                 /* +0x00 name rule above */
    long s_paddr;                   /* +0x08 */
    long s_pmem;                    /* +0x0c memory space of paddr */
    long s_vaddr;                   /* +0x10 STYP_BLOCK: block length */
    long s_vmem;                    /* +0x14 */
    long s_size;                    /* +0x18 words */
    long s_scnptr;                  /* +0x1c */
    long s_relptr;                  /* +0x20 */
    long s_lnnoptr;                 /* +0x24 */
    long s_nreloc;                  /* +0x28 (object.c reads it as 16 bit) */
    long s_nlnno;                   /* +0x2c (16 bit, likewise) */
    unsigned long s_flags;          /* +0x30 STYP_* */
} SCNHDR;

typedef struct syment {             /* symbol table main entry, 0x20 */
    char n_name[8];                 /* +0x00 name rule above */
    long n_value;                   /* +0x08 (low word of a double) */
    long n_mem;                     /* +0x0c memory space (high word of a double) */
    long n_scnum;                   /* +0x10 >0 section, 0 undefined, -1 abs, -2 debug */
    long n_type;                    /* +0x14 */
    long n_sclass;                  /* +0x18 C_* / A_* */
    long n_numaux;                  /* +0x1c */
} SYMENT;

typedef struct auxent {             /* aux entry, 0x20: 8 decoded words */
    long x[8];
} AUXENT;

typedef union symslot {             /* one 0x20 slot: main entry or aux by position */
    SYMENT s;
    AUXENT a;
} SYMSLOT;

typedef struct relent {             /* relocation entry, 0xc */
    long r_vaddr;                   /* +0x00 */
    long r_symndx;                  /* +0x04 strtab offset of the expression text */
    long r_unused;                  /* +0x08 */
} RELENT;

typedef struct lineno {             /* line number entry, 0xc */
    long l_addr;                    /* +0x00 (l_symndx when l_lnno == 0) */
    long l_mem;                     /* +0x04 */
    long l_lnno;                    /* +0x08 */
} LINENO;

/* ---- memory specification ------------------------------------------ */
typedef struct memspec {            /* 4 longs, filled by get_mem_spec (defaults {4,4,0,0}) */
    long mspace;                    /* +0x00 MS_* (key: compared) */
    long mmap;                      /* +0x04 MM_* (raw COFF space code) */
    long mcntr;                     /* +0x08 location counter MC_* or "(n)" (key: compared) */
    long mclass;                    /* +0x0c EMI class bits (>>4 width code, &0xf packing) */
} MEMSPEC;

/* ---- small list nodes ---------------------------------------------- */
typedef struct strnode {            /* 8 bytes: arg lists, libpath list, dup list, section XREF names */
    char *str;                      /* +0 */
    struct strnode *next;           /* +4 */
} STRNODE;

typedef struct secnest {            /* 8 bytes, section nesting stack (input track_section_nesting) */
    long id;                        /* +0 A_SECT aux section number (index into mod_secmap) */
    struct secnest *next;           /* +4 */
} SECNEST;

typedef struct symlist {            /* 8 bytes, map.c per-section symbol list (SECTION.msyms) */
    struct sym *sym;                /* +0 */
    struct symlist *next;           /* +4 */
} SYMLIST;

/* ---- input files and modules --------------------------------------- */
typedef struct infile {             /* xmalloc(0x14), open_next_input_file */
    char *name;                     /* +0x00 own copy; error.c "File %s" */
    unsigned long flags;            /* +0x04 IF_LIBRARY */
    struct module *module;          /* +0x08 object: its MODULE; library: current member */
    struct module *members;         /* +0x0c library: first pulled member (chain MODULE.next) */
    struct infile *next;            /* +0x10 */
} INFILE;

typedef struct sectref {            /* MODULE.sectref[n_scnum-1], 8 bytes */
    SCNHDR *hdr;                    /* +0 */
    SYMSLOT *sym;                   /* +4 section symbol entry */
} SECTREF;

typedef struct bufref {             /* MODULE.buftab[buffer#], 8 bytes */
    struct section *sec;            /* +0 buffer SECTION */
    unsigned long addr;             /* +4 buffer address/offset at creation */
} BUFREF;

typedef struct ovlent {             /* MODULE.ovltab[overlay#], 0x24 bytes (index 1..ovlcnt) */
    struct module *module;          /* +0x00 owning module (cur_infile->module) = "stamp" */
    struct section *sec;            /* +0x04 overlay piece (get_overlay_record) */
    struct section *lsec;           /* +0x08 load section (cur_section) */
    struct section *rsec;           /* +0x0c run section (cur_rsection) */
    struct section *grp;            /* +0x10 group leader piece (self, or set by fixup_ovl_*) */
    unsigned long maxbuf;           /* +0x14 largest buffer (alignment of the overlay) */
    long sdioff;                    /* +0x18 SDI growth before this overlay in its group */
    struct sdipiece *marker;        /* +0x1c marker piece of the run section */
    char *baseexpr;                 /* +0x20 strtab + ovlstr: base address expression, or 0 */
} OVLENT;

typedef struct module {             /* xmalloc(0x98), new_module */
    char *name;                     /* +0x00 library member name, or 0 */
    long unk_04;                    /* +0x04 always 0 */
    long size;                      /* +0x08 byte size */
    long offset;                    /* +0x0c file offset of the COFF header */
    struct modsec **secmap;         /* +0x10 [lh.secnt] MODSEC chains */
    SECTREF *sectref;               /* +0x14 [lh.ctrcnt] */
    BUFREF *buftab;                 /* +0x18 [lh.bufcnt+1] */
    OVLENT *ovltab;                 /* +0x1c [lh.ovlcnt+1] */
    FILHDR fh;                      /* +0x20 */
    LNKHDR lh;                      /* +0x3c */
    SCNHDR *scnhdr;                 /* +0x74 [fh.f_nscns] */
    unsigned long *raw;             /* +0x78 [lh.datasize] */
    unsigned long *sdibuf;          /* +0x7c pass 2 with mod_sdi */
    unsigned long *sdiptr;          /* +0x80 write cursor into sdibuf */
    RELENT *reloc;                  /* +0x84 [lh.relocnt] */
    LINENO *lines;                  /* +0x88 [lh.lnocnt] */
    SYMSLOT *syms;                  /* +0x8c [fh.f_nsyms] */
    char *strtab;                   /* +0x90 string table incl. the 4-byte length word, or 0 */
    struct module *next;            /* +0x94 next pulled library member */
} MODULE;

/* ---- sections, regions --------------------------------------------- */
typedef struct secname {            /* xmalloc(0x14), secname_new; chained in sec_hash */
    char *name;                     /* +0x00 own copy (lower-cased with -n) */
    long num;                       /* +0x04 0 GLOBAL, -1 RESERVE, else ++sec_num_seed */
    struct secnode *nodes;          /* +0x08 SECNODE list (prepended) */
    STRNODE *xrefs;                 /* +0x0c XREF names of the section (input reference_symbol) */
    struct secname *hnext;          /* +0x10 hash chain */
} SECNAME;

typedef struct secnode {            /* output section (name,mspace,mcntr); xmalloc(0x78), secnode_get */
    SECNAME *sname;                 /* +0x00 */
    unsigned long flags;            /* +0x04 SN_* */
    MEMSPEC spec;                   /* +0x08..+0x14 */
    struct section *secs;           /* +0x18 primary SECTION list (RESERVE: ranges) */
    struct section *abss;           /* +0x1c absolute pieces */
    struct section *bufs;           /* +0x20 buffer pieces */
    struct section *ovls;           /* +0x24 overlay pieces */
    long nsecs;                     /* +0x28 */
    long nabss;                     /* +0x2c */
    long nbufs;                     /* +0x30 */
    long novls;                     /* +0x34 */
    unsigned long bufsz;            /* +0x38 pass-1 buffer/pad space */
    unsigned long bufsz_al;         /* +0x3c same after load alignment */
    unsigned long sv_bufsz;         /* +0x40 saved +0x38 */
    unsigned long sv_bufsz_al;      /* +0x44 saved +0x3c */
    unsigned long sbalign;          /* +0x48 SBALIGN address */
    unsigned long totlen;           /* +0x4c sum of SECTION.len */
    unsigned long totovl;           /* +0x50 sum of SECTION.ovlsize */
    unsigned long totsize;          /* +0x54 sum of SECTION.size */
    unsigned long sdigrow;          /* +0x58 pass-2 long SDI forms into a load!=run section */
    long unk_5c;                    /* +0x5c unused */
    unsigned long secsize;          /* +0x60 SECSIZE count */
    double secpct;                  /* +0x60/+0x64 as double factor when SN_SECPCT (port: own field) */
    struct section *ovl_last;       /* +0x68 last overlay piece with SF_LOADRUN */
    struct module *ovl_stamp;       /* +0x6c module of that piece */
    struct memreg *memreg;          /* +0x70 region/memory record assigned */
    struct secnode *next;           /* +0x74 next node of the same SECNAME */
} SECNODE;

typedef struct section {            /* section piece, xmalloc(0x48)+zero, sec_alloc */
    SECNODE *node;                  /* +0x00 */
    long index;                     /* +0x04 buffer/overlay number, 0 else */
    unsigned long flags;            /* +0x08 SF_* (low bits = input aux flags) */
    unsigned long state;            /* +0x0c SS_* */
    unsigned long lo;               /* +0x10 start address */
    unsigned long hi;               /* +0x14 end (exclusive) = location counter while reading */
    unsigned long len;              /* +0x18 hi-lo latched by fixup_sec_length */
    unsigned long size;             /* +0x1c */
    unsigned long ovlsize;          /* +0x20 */
    unsigned long align;            /* +0x24 buffer size / max buffer size */
    unsigned long sv_lo;            /* +0x28 */
    unsigned long sv_hi;            /* +0x2c */
    unsigned long bufaddr;          /* +0x30 buffer: original input address */
    unsigned long bufspan;          /* +0x34 buffer: pad + buffer size */
    struct sdistat *sdi;            /* +0x38 */
    OVLENT *ovl;                    /* +0x3c overlay pieces: their OVLENT */
    SYMLIST *msyms;                 /* +0x3c reused by map.c (port: own field) */
    struct section *run;            /* +0x40 run/relocation section (primary: self) */
    struct section *next;           /* +0x44 */
} SECTION;

typedef struct modsec {             /* per-module section map node, xmalloc(0x18) */
    SECTION *sec;                   /* +0x00 primary SECTION */
    unsigned long base;             /* +0x04 module base offset in the section */
    unsigned long base_raw;         /* +0x08 base without buffer alignment */
    unsigned long base2;            /* +0x0c pass-2 base */
    SYMSLOT *fsym;                  /* +0x10 file symbol entry (cur_file_ent) that last used it */
    struct modsec *next;            /* +0x14 */
} MODSEC;

typedef struct region {             /* xmalloc(0x10), region_get; list region_head ("DEFAULT") */
    char *name;                     /* +0x00 */
    long nmem;                      /* +0x04 */
    struct memreg *mems;            /* +0x08 MEMREG list (prepended) */
    struct region *next;            /* +0x0c */
} REGION;

typedef struct secref {             /* 8 bytes, MEMREG.secs list (memctl_assign_region) */
    SECTION *sec;                   /* +0 */
    struct secref *next;            /* +4 */
} SECREF;

typedef struct memreg {             /* region x memory record, xmalloc(0x3c), memreg_new */
    REGION *region;                 /* +0x00 */
    unsigned long flags;            /* +0x04 MR_* */
    unsigned long flags2;           /* +0x08 MR2_* */
    MEMSPEC spec;                   /* +0x0c..+0x18 */
    unsigned long base;             /* +0x1c */
    unsigned long high;             /* +0x20 highest address (inclusive) */
    unsigned long size;             /* +0x24 */
    unsigned long balign;           /* +0x28 */
    unsigned long ovlcur;           /* +0x2c overlay placement cursor */
    SECREF *secs;                   /* +0x30 appended in assignment order */
    long nsecs;                     /* +0x34 */
    struct memreg *next;            /* +0x38 */
} MEMREG;

typedef struct range {              /* used address range [lo,hi), xmalloc(0x14) */
    long unk_0;                     /* +0x00 never written */
    unsigned long lo;               /* +0x04 */
    unsigned long hi;               /* +0x08 exclusive */
    struct range *prev;             /* +0x0c */
    struct range *next;             /* +0x10 */
} RANGE;

typedef struct ctrgroup {           /* xmalloc(0x28), fixup_get_counter_group */
    long mcntr;                     /* +0x00 */
    RANGE *lists[NMEMIDX];          /* +0x04..+0x20 */
    struct ctrgroup *next;          /* +0x24 */
} CTRGROUP;

/* ---- span-dependent instructions (sdi.c) --------------------------- */
typedef struct sdistat {            /* xmalloc(0x2c), sdi_stats_new */
    long n;                         /* +0x00 pieces (pass 1) / read cursor (pass 2) */
    long n_saved;                   /* +0x04 */
    long growth;                    /* +0x08 */
    long maxgrowth;                 /* +0x0c */
    long mod_first;                 /* +0x10 n at the first piece of the current module */
    long mod_count;                 /* +0x14 pieces read for the current module */
    long unk_18;                    /* +0x18 */
    SECTION *owner;                 /* +0x1c */
    MODULE *stamp;                  /* +0x20 module (cur_infile->module) of mod_first */
    struct sdipiece *pieces;        /* +0x24 prepended */
    struct sdirec *recs;            /* +0x28 array of n+1 */
} SDISTAT;

typedef struct sdipiece {           /* xmalloc(0x44), sdi_add */
    char *expr;                     /* +0x00 target expression (own copy) or 0 */
    unsigned long addr;             /* +0x04 */
    unsigned long addr2;            /* +0x08 */
    unsigned long orig;             /* +0x0c */
    unsigned long bufoff;           /* +0x10 */
    long opsz;                      /* +0x14 */
    long opsz2;                     /* +0x18 (marker: growth base) */
    unsigned long flags;            /* +0x1c SDI_* */
    long alt1;                      /* +0x20 */
    long alt2;                      /* +0x24 */
    char *text;                     /* +0x28 into the module string table */
    INFILE *infile;                 /* +0x2c cur_infile at creation */
    SECTION *lsec;                  /* +0x30 cur_section */
    SECNEST *nest;                  /* +0x34 private copy of the nesting stack */
    MODSEC *msec;                   /* +0x38 cur_rmsec */
    OVLENT *ovl;                    /* +0x3c */
    struct sdipiece *next;          /* +0x40 */
} SDIPIECE;

typedef struct sdirec {             /* sdi_build array element, stride 0x2c */
    unsigned long addr;             /* +0x00 */
    unsigned long orig;             /* +0x04 */
    unsigned long value;            /* +0x08 */
    unsigned long disp;             /* +0x0c */
    long opsz;                      /* +0x10 */
    long opsz2;                     /* +0x14 */
    unsigned long flags;            /* +0x18 */
    long growth;                    /* +0x1c */
    long alt1;                      /* +0x20 */
    long alt2;                      /* +0x24 */
    char *text;                     /* +0x28 */
} SDIREC;

/* ---- symbols ------------------------------------------------------- */
typedef struct sym {                /* xmalloc(0x68), sym_enter copies a caller template */
    char *name;                     /* +0x00 own copy (folded with -n) */
    long unk_04;                    /* +0x04 */
    double fval;                    /* +0x08 SYM_FLOAT value (port: separate from hi) */
    unsigned long hi;               /* +0x0c SYM_LONG high word / raw COFF mem word */
    unsigned long lo;               /* +0x10 integer value / low word */
    long unk_14;                    /* +0x14 */
    double sfval;                   /* +0x18 saved copy of +0x08..+0x14 as defined */
    unsigned long shi;              /* +0x1c */
    unsigned long slo;              /* +0x20 */
    long sunk_14;                   /* +0x24 */
    unsigned long flags;            /* +0x28 SYM_* */
    MEMSPEC mem;                    /* +0x2c..+0x38 */
    long scnum;                     /* +0x3c defining n_scnum; -1 memctl, 0 internal */
    long sdi_cnt;                   /* +0x40 1-based SDI record index */
    unsigned long cls_off;          /* +0x44 rsec->node->bufsz at definition */
    SECTION *sec;                   /* +0x48 defining section piece; NULL = special */
    SECTION *rsec;                  /* +0x4c relocation section piece */
    SECTION *osec;                  /* +0x50 rsec->node->ovl_last (SDI, space P, REL) */
    MODSEC *smap;                   /* +0x54 cur_rmsec */
    BUFREF *buf;                    /* +0x58 &mod_buftab[cur_buffer] or 0 */
    OVLENT *ovl;                    /* +0x5c &mod_ovltab[cur_overlay] or 0 */
    struct sym *next;               /* +0x60 hash chain */
    long unk_64;                    /* +0x64 */
} SYM;

typedef struct xref {               /* external reference, xmalloc(0x1c), xref_add */
    char *name;                     /* +0x00 own copy (folded with -n) */
    unsigned long flags;            /* +0x04 XREF_* */
    INFILE *infile;                 /* +0x08 0 = command line (-u) */
    MODULE *module;                 /* +0x0c */
    SECTION *sec;                   /* +0x10 */
    struct xref *prev;              /* +0x14 */
    struct xref *next;              /* +0x18 */
} XREF;

/* ---- expressions --------------------------------------------------- */
typedef struct expr {               /* xmalloc(0x48), new_expr; expression stack entry */
    unsigned long hi;               /* +0x00 top word (FLT: low dword of the double) */
    unsigned long mid;              /* +0x04 (FLT: high dword) */
    unsigned long lo;               /* +0x08 */
    long unk_0c;                    /* +0x0c */
    long type;                      /* +0x10 EXPR_INT / EXPR_FLT / EXPR_SZCK */
    long size;                      /* +0x14 fmt_word / fmt_dword / 8 / string length */
    unsigned long flags;            /* +0x18 EXPR_REL / EXPR_OVL / EXPR_FWD */
    long space;                     /* +0x1c MS_* (4 none) */
    long map;                       /* +0x20 */
    long ctr;                       /* +0x24 */
    long attr;                      /* +0x28 */
    long sect;                      /* +0x2c section number; < 0 external/unresolved */
    long rsect;                     /* +0x30 relocation section index (new_expr: -1) */
    long buf;                       /* +0x34 buffer number = index+1 into mod_buftab (8-byte
                                       entries); '*': cur_buffer.  (p4 called this "ovl") */
    long ovl;                       /* +0x38 overlay number = index+1 into mod_ovltab (0x24-byte
                                       entries); '*': cur_overlay.  (p4 called this "buf") */
    long unk_3c;                    /* +0x3c new_expr: -1; SYM.scnum */
    long sdi;                       /* +0x40 SDI sequence number, 0 none */
    long unk_44;                    /* +0x44 */
    double fval;                    /* port only: EXPR_FLT value */
} EXPR;

typedef EXPR *(*BINOP_FN)(EXPR *, EXPR *);

/* ---- tables -------------------------------------------------------- */
typedef struct keyword {            /* memctl keyword tables, sorted, 8 bytes */
    char *name;                     /* +0 */
    int id;                         /* +4 */
} KEYWORD;

typedef struct functab {            /* @-function table, 12 bytes */
    char *name;                     /* +0x00 matched as a prefix */
    long id;                        /* +0x04 FN_* */
    long unused;                    /* +0x08 */
} FUNCTAB;

typedef struct target {             /* target table entry, 0x4c bytes */
    char *name;                     /* +0x00 */
    unsigned long magic;            /* +0x04 */
    long word_bytes;                /* +0x08 */
    unsigned long addr_mask;        /* +0x0c */
    unsigned long ext_addr_mask;    /* +0x10 */
    unsigned long io_base;          /* +0x14 */
    unsigned long io_base2;         /* +0x18 never copied (io_base2 stays 0) */
    unsigned long word_mask;        /* +0x1c */
    unsigned long sign_bit;         /* +0x20 */
    long unk_24;                    /* +0x24 -> tgt_unk24 */
    long unk_28;                    /* +0x28 */
    long word_digits;               /* +0x2c */
    long unk_30;                    /* +0x30 */
    long unk_34;                    /* +0x34 */
    long unk_38;                    /* +0x38 */
    char *word_fmt;                 /* +0x3c */
    char *addr_fmt;                 /* +0x40 */
    char *unk_44;                   /* +0x44 */
    char *value_fmt;                /* +0x48 */
} TARGET;

/* ---- object file bookkeeping --------------------------------------- */
typedef struct fileext {            /* per input file .text/.data extents, xmalloc(0x38) */
    unsigned long text_lo;          /* +0x00 */
    unsigned long text_hi;          /* +0x04 */
    MEMSPEC text_mem;               /* +0x08 (init {4,4,0,0}) */
    unsigned long data_lo;          /* +0x18 */
    unsigned long data_hi;          /* +0x1c */
    MEMSPEC data_mem;               /* +0x20 */
    long symidx;                    /* +0x30 index of ".text" in the output symbols (init -1) */
    struct fileext *next;           /* +0x34 */
} FILEEXT;

/* ---- ELF (elfout.c / cof2elf.c) ------------------------------------ */
typedef struct elfbuf {             /* growable byte buffer, 0xc */
    char *data;                     /* +0x00 */
    long len;                       /* +0x04 */
    long cap;                       /* +0x08 */
} ELFBUF;

typedef struct elfsec {             /* ELF section record, xmalloc(0x40) */
    unsigned long name;             /* +0x00 sh_name */
    unsigned long type;             /* +0x04 */
    unsigned long flags;            /* +0x08 */
    unsigned long addr;             /* +0x0c */
    unsigned long offset;           /* +0x10 */
    unsigned long size;             /* +0x14 */
    unsigned long link;             /* +0x18 */
    unsigned long info;             /* +0x1c */
    unsigned long align;            /* +0x20 */
    unsigned long entsize;          /* +0x24 */
    ELFBUF *data;                   /* +0x28 */
    char *sname;                    /* +0x2c */
    long index;                     /* +0x30 */
    long unk_34;                    /* +0x34 */
    struct elfsec *prev;            /* +0x38 */
    struct elfsec *next;            /* +0x3c */
} ELFSEC;

/* ======================================================================
 * Globals (defined in lnkglb.c)
 * ====================================================================== */

/* -- initialized data of the original lnkglb.c (.data 0x457b10..) -- */
extern long stack_mspace;           /* 457b48 = 2 */
extern char map_buffer;             /* 457b4c = 1  MAP OPT nobuffer */
extern char map_const;              /* 457b50 = 1 */
extern char map_local;              /* 457b54 = 1 */
extern char map_overlay;            /* 457b58 = 1 */
extern char map_secaddr;            /* 457b5c = 1 */
extern char map_secname;            /* 457b60 = 1 */
extern char map_symname;            /* 457b64 = 1 */
extern char map_symval;             /* 457b68 = 1 */
extern char map_unused;             /* 457b6c = 1 */
extern char map_globsym;            /* 457b70 = 1 */
extern char nested_secs;            /* 457b74 = 1  module section flag SA_NEST */
extern char opt_abc;                /* 457b78 = 1 */
extern char opt_aec;                /* 457b7c = 1 */
extern char opt_rsc;                /* 457b80 = 1 */
extern char opt_wvr;                /* 457b84 = 1 */
extern long run_reloc;              /* 457b88 = 1 */
extern long load_reloc;             /* 457b8c = 1 */
extern char map_need_hdr;           /* 457b90 = 1 */
extern char opt_sdi;                /* 457b94 = 1 */
extern char load_aligned;           /* 457b98 = 1 */
extern long addr_bytes;             /* 457b9c = 1  (@BYT overwrites it) */
extern long verbose_level;          /* 457ba0 = 100 */
extern long radix;                  /* 457ba4 = 10 */
extern long start_mem;              /* 457ba8 = 4 */
extern long text_lo_mem;            /* 457bac = 4 */
extern long data_lo_mem;            /* 457bb0 = 4 */
extern long text_hi_mem;            /* 457bb4 = 4 */
extern long data_hi_mem;            /* 457bb8 = 4 */
extern long map_col;                /* 457bbc = 1 */
extern long map_lcol;               /* 457bc0 = 1 */
extern long map_width;              /* 457bc4 = 132 */
extern long map_lmargin;            /* 457bc8 = 1 */
extern long map_line;               /* 457bcc = 1 */
extern long map_lastline;           /* 457bd0 = 66 */
extern long map_pagelen;            /* 457bd4 = 66 */
extern char map_hdr_on;             /* 457bd8 = 1 */
extern long map_topmargin;          /* 457bdc = 3 */
extern long map_botmargin;          /* 457be0 = 3 */
extern char ident_none[8];          /* 457be8 "NONE" */
extern char *base_fname;            /* 457bf0 -> empty_str: default output base name */
extern char *cform_prefix;          /* 457bf4 -> empty_str */
extern long ctl_level;              /* 457bfc = 1 */
extern long cur_scnum;              /* 457c00 = -1 */
extern long obj_strsize;            /* 457c04 = 4 */
extern FILE *msg_fp;                /* 457c08 = stderr (set in main: not a constant in C89) */
extern long tgt_unk24;              /* 457c0c = 1 */
extern TARGET target_tab[NTARGETS + 1];  /* 457c18 */
extern char *progname;              /* 457ed0 -> "dsplnk" */
extern char lnk_name[];             /* 457ed8 "Linker" */
extern char lnk_version[];          /* 457ee0 "6.3.7 " */
extern char lnk_copyright[];        /* 457ee8 */
extern char env_name[];             /* 457f28 "DSPLNKOPT" */
extern char optstring[];            /* 457f38 OPTSTRING */
extern char default_region[];       /* 457f80 "DEFAULT" */
extern char global_secname[];       /* 457f88 "GLOBAL" */
extern char reserve_secname[];      /* 457f90 "RESERVE" */
extern char lib_magic[];            /* 457f98 "!<H>" */
extern long lib_magic_len;          /* 457fa0 = 4 */
extern char *ident_name;            /* 457fa4 -> ident_none */
extern char *ident_comment;         /* 457fa8 -> empty_str */
extern char mem_idx_char[];         /* 457ff0 " XYLPEDU" (index MI_*) */
extern KEYWORD memctl_kw_tab[NMEMCTL_KW];     /* 458010 */
extern int memctl_kw_cnt;                     /* 458098 */
extern KEYWORD memctl_mapopt_tab[NMAP_OPT];   /* 4580a0 */
extern int memctl_mapopt_cnt;                 /* 458100 */
extern KEYWORD memctl_xopt_tab[NXOPT];        /* 458108 */
extern int memctl_xopt_cnt;                   /* 458210 */
extern BINOP_FN binop_tab[NBINOPS];           /* 458218 */
extern FUNCTAB func_tab[NFUNCS];              /* 458278 */
extern long func_count;                       /* 458320 = 14 */
extern long mon_days[12];                     /* 458328 */
extern long mon_days_leap[12];                /* 458358 */
extern unsigned long emi_max_addr[256];       /* 458388 = [mmap - MM_E0] */
#define EMI_MAX_ADDR(mmap) emi_max_addr[(mmap) - MM_E0]

/* -- program, files, options -- */
extern FILE *err_fp;                /* 461f34 error.c stream (stdout) */
extern FILE *obj_fp;                /* 461f38 */
extern FILE *map_fp;                /* 461f3c */
extern FILE *ctl_fp;                /* 461f40 -r memory control file */
extern FILE *in_fp;                 /* 461db4 current input (object/library/ctl/include) */
extern char *obj_name;              /* 461d64 */
extern char namebuf[NAMEBUF_SIZE];  /* 461528 shared scratch name buffer */
extern char title_name[NAMEBUF_SIZE]; /* 461730 -r then -m file name */
extern char empty_str[4];           /* 46131c "" */
extern long link_time;              /* 461d44 */
extern char date_str[16];           /* 461d48 */
extern char time_str[12];           /* 461d58 */
extern char opt_mcm;                /* 4611d8 */
extern char map_symlen_on;          /* 4611e0 */
extern long map_symlen;             /* 4611e4 */
extern char opt_wdg;                /* 4611e8 */
extern char opt_s;                  /* 4611ec */
extern char suppress_errors;        /* 4611f0 */
extern char no_argv_mode;           /* 4611f4 dead (always 0) */
extern char lib_rescan;             /* 4611fc set by xref_add */
extern char in_brace;               /* 461200 */
extern char map_globmap;            /* 461208 */
extern char opt_c;                  /* 46120c */
extern char cc_objects;             /* 461210 */
extern char opt_n;                  /* 461214 */
extern char opt_asc;                /* 461228 */
extern char opt_ro;                 /* 46122c */
extern char opt_eso;                /* 461230 */
extern char opt_wex;                /* 461234 */
extern char opt_ovlp;               /* 461238 */
extern char opt_svo;                /* 46123c */
extern char opt_ff;                 /* 461240 */
extern char opt_csl;                /* 461244 */
extern char opt_i;                  /* 461248 */
extern char opt_g;                  /* 46124c */
extern char opt_z;                  /* 461250 */
extern char start_given;            /* 461254 */
extern char opt_v;                  /* 46125c */
extern char opt_t;                  /* 461260 */
extern char opt_q;                  /* 461264 */
extern char colon_short;            /* 461268 */
extern char opt_a;                  /* 46126c */
extern char mod_sdi;                /* 461270 */
extern char sdi_active;             /* 461274 SDI relaxation loop (retry) */
extern char sdi_seen;               /* 461278 */
extern char sdi_changed;            /* 46127c */
extern char two_words;              /* 461280 */
extern char addr_cancel;            /* 461284 */
extern char opt_sbm;                /* 461288 */
extern char opt_osp;                /* 46128c */
extern char opt_isw;                /* 461290 */
extern int pass;                    /* 461294 1 or 2 */
extern long sec_num_seed;           /* 461298 */
extern long num_secs;               /* 46129c SECTION records */
extern long cur_rsecno;             /* 4612a0 */
extern long cur_secid;              /* 4612a4 */
extern long cur_rsecid;             /* 4612a8 */
extern long cur_buffer;             /* 4612ac */
extern long num_buffers;            /* 4612b0 */
extern long buf_seq;                /* 4612b4 buffer records (lnkhdr bufcnt) */
extern unsigned long buf_type;      /* 4612b8 */
extern long buf_base;               /* 4612c4 */
extern long cur_overlay;            /* 4612c8 */
extern long num_overlays;           /* 4612cc (lnkhdr ovlcnt) */
extern long ovl_seq;                /* 4612d0 */
extern long ovl_base;               /* 4612d8 */
extern long num_syms;               /* 4612dc */
extern long num_xrefs;              /* 4612e0 */
extern long num_xrefs_done;         /* 4612e4 */
extern long block_depth;            /* 4612e8 */
extern long error_count;            /* 4612ec */
extern long warning_count;          /* 4612f0 */
extern long suppressed_errors;      /* 4612f4 */
extern unsigned long start_addr;    /* 4612fc */
extern unsigned long text_lo;       /* 461300 */
extern unsigned long data_lo;       /* 461304 */
extern unsigned long text_hi;       /* 461308 */
extern unsigned long data_hi;       /* 46130c */
extern long map_pageno;             /* 461310 */
extern long src_line;               /* 461314 */
extern long ctl_lineno;             /* 461318 */
extern char ctl_token[NAMEBUF_SIZE];/* 461320 */
extern char err_symbol[ERRSYM_SIZE];/* 461b40 last identifier; error suffix */
extern char *input_cursor;          /* 461d68 shared parse cursor */
extern char *cform_ptr;             /* 461d6c */
extern MEMSPEC run_spec;            /* 461d70..461d7c */
extern MEMSPEC load_spec;           /* 461d80..461d8c */
extern unsigned long *run_ctr;      /* 461d90 */
extern unsigned long *load_ctr;     /* 461d94 */
extern long cur_argc;               /* 461da0 */
extern char **cur_argv;             /* 461da4 */
extern INFILE *infile_head;         /* 461db8 */
extern INFILE *cur_infile;          /* 461dbc error context */
extern char *start_name;            /* 461dc4 START expression text */
extern long (*sort_cmp)(void *, void *);  /* 461dc8 */
extern REGION *region_head;         /* 461dcc "DEFAULT" */
extern REGION *cur_region;          /* 461dd0 */
extern MEMREG *cur_memreg;          /* 461dd4 */
extern SECTION *cur_section;        /* 461ddc */
extern SECTION *cur_rsection;       /* 461de0 */
extern SECTION *cur_alloc;          /* 461de4 */
extern MODSEC **mod_secmap;         /* 461de8 */
extern MODSEC *cur_rmsec;           /* 461df0 */
extern RANGE *used_ranges[NMEMIDX]; /* 461df8 */
extern CTRGROUP *ctr_groups;        /* 461e24 */
extern RANGE **ctr_lists;           /* 461e28 */
extern BUFREF *mod_buftab;          /* 461e5c */
extern OVLENT *mod_ovltab;          /* 461e60 */
extern SYMSLOT *cur_file_ent;       /* 461e68 */
extern long cur_symidx;             /* 461e7c */
extern REGION *region_last;         /* 461e80 */
extern SECTREF *cur_sectref;        /* 461e90 */
extern long obj_nscns;              /* 461e98 */
extern unsigned long obj_nwords;    /* 461ea8 */
extern unsigned long obj_nreloc;    /* 461eb4 */
extern unsigned long obj_lnnoptr0;  /* 461ec0 */
extern unsigned long obj_lnnoptr;   /* 461ec4 */
extern unsigned long obj_nlnno;     /* 461ec8 */
extern long sdi_total;              /* 461ef0 */
extern long out_nsdi;               /* 461ef4 */
extern long obj_sditot;             /* 461ef8 */
extern long num_set_syms;           /* 461efc */
extern SECNEST *sec_nest;           /* 461f00 */
extern FILEEXT *obj_fext_head;      /* 461f04 */
extern FILEEXT *obj_fext_cur;       /* 461f08 */
extern long obj_nlnno_file;         /* 461f0c */
extern STRNODE *libpath_head;       /* 461f10 */
extern STRNODE *libpath_tail;       /* 461f14 */
extern void **sort_array;           /* 461f18 */
extern SYM **map_syms;              /* 461f1c */
extern SECTION **map_secs;          /* 461f20 */
extern XREF **map_xrefs;            /* 461f24 */
extern char in_eval;                /* 461f30 */
extern jmp_buf eval_jmpbuf;         /* 46c300 */
extern SYM *sym_found;              /* 4611dc last sym_lookup result */

/* -- target (set_target_cpu) -- */
extern TARGET *cur_target;          /* 461fc0 0 until the first module */
extern long target_index;           /* 461f44 TGT_* */
extern char *target_name;           /* 461f48 */
extern long word_bytes;             /* 461f4c */
extern long word_hexdig;            /* 461f50 2*word_bytes */
extern long dword_hexdig;           /* 461f54 4*word_bytes */
extern long word_bits;              /* 461f58 8*word_bytes */
extern long dword_bits;             /* 461f5c 16*word_bytes */
extern long fmt_word;               /* 461f60 word_bytes */
extern long fmt_dword;              /* 461f64 2*word_bytes */
extern unsigned long word_mask;     /* 461f6c */
extern unsigned long sign_bit;      /* 461f70 */
extern unsigned long addr_mask;     /* 461f74 */
extern unsigned long ext_addr_mask; /* 461f78 */
extern unsigned long io_base;       /* 461f7c */
extern unsigned long io_base2;      /* 461f80 never written */
extern unsigned long io_base_neg;   /* 461f84 */
extern unsigned long io_short_max;  /* 461f88 */
extern unsigned long io_base2_neg;  /* 461f8c */
extern unsigned long io_short2_max; /* 461f90 */
extern unsigned long frac_min;      /* 461f98 */
extern unsigned long frac_max;      /* 461f9c */
extern unsigned long target_magic;  /* 461fa0 */
extern long word_digits;            /* 461fa4 */
extern char *word_fmt;              /* 461fb4 */
extern char *value_fmt;             /* 461fb8 */
extern char *addr_fmt;              /* 461fbc */
extern long global_secno;           /* 461fc4 never written (0) */
extern long ident_ver;              /* 461fc8 */
extern long ident_rev;              /* 461fcc */
extern long out_major;              /* 461fd0 */
extern long out_minor;              /* 461fd4 */
extern long out_rev;                /* 461fd8 */
extern long lnk_major;              /* 461fdc */
extern long lnk_minor;              /* 461fe0 */
extern long lnk_rev;                /* 461fe4 */
extern long obj_major;              /* 461fe8 */
extern long obj_minor;              /* 461fec */
extern long obj_rev;                /* 461ff0 */

/* -- hash tables -- */
extern SYM *sym_hash[HASHSIZE];     /* 461ff8 */
extern SECNAME *sec_hash[HASHSIZE]; /* 463f48 */
extern XREF *xref_hash[HASHSIZE];   /* 465e98 */

/* -- misc -- */
extern SYMSLOT obj_auxbuf;          /* 46c080 */
extern SYMSLOT obj_symbuf;          /* 46c140 */
extern MEMSPEC ovl_mem;             /* 46c2e0 overlay run spec; mspace 4 = none */
extern LNKHDR obj_lnkhdr;           /* 46c340 (finish_link writes endstr) */
extern void *abi_modules;           /* 46c604 ABI module array */

/* ======================================================================
 * Functions called across files
 * ====================================================================== */

/* dsplnk.c */
int main(int argc, char **argv);
void finish_link(int abort);
void lnk_signal_handler(int sig);
char *set_default_ext(char *ext);
void set_target_cpu(unsigned long magic);
long peek_long(long *p);
int set_file_type(char *name, char *type, char *creator);

/* error.c */
void lnk_fatal1(char *msg);
void lnk_error1(char *msg);
void lnk_error2(char *msg, char *arg);
void lnk_warning1(char *msg);
void lnk_warning2(char *msg, char *arg);
void lnk_cmdline_fatal1(char *msg);
void lnk_cmdline_fatal2(char *msg, char *arg);
void lnk_cmdline_warn1(char *msg);

/* arith.c (binary operators: binop_tab) */
EXPR *op_add(EXPR *a, EXPR *b);
EXPR *op_sub(EXPR *a, EXPR *b);
EXPR *op_mul(EXPR *a, EXPR *b);
EXPR *op_div(EXPR *a, EXPR *b);
EXPR *op_mod(EXPR *a, EXPR *b);
EXPR *op_and(EXPR *a, EXPR *b);
EXPR *op_or(EXPR *a, EXPR *b);
EXPR *op_xor(EXPR *a, EXPR *b);
EXPR *op_shl(EXPR *a, EXPR *b);
EXPR *op_shr(EXPR *a, EXPR *b);
EXPR *op_land(EXPR *a, EXPR *b);
EXPR *op_lor(EXPR *a, EXPR *b);
EXPR *op_lt(EXPR *a, EXPR *b);
EXPR *op_gt(EXPR *a, EXPR *b);
EXPR *op_eq(EXPR *a, EXPR *b);
EXPR *op_le(EXPR *a, EXPR *b);
EXPR *op_ge(EXPR *a, EXPR *b);
EXPR *op_ne(EXPR *a, EXPR *b);
EXPR *op_size_check(EXPR *val, EXPR *code);
EXPR *op_space(EXPR *a, EXPR *b);
EXPR *op_mapping(EXPR *a, EXPR *b);
EXPR *op_line(EXPR *a, EXPR *b);
unsigned long expr_as_int32(EXPR *e);
void negate_value(EXPR *e);
void complement_value(EXPR *e);
void op_not(EXPR *e);
double int_to_double(unsigned long v);
double long_to_double(unsigned long hi, unsigned long lo);
void float_to_fixed_frac(double v, long fmt, EXPR *out);
unsigned long double_to_frac(double v);
unsigned long double_to_frac_n(double v, unsigned long mask);
void double_to_frac2(double v, unsigned long *hi, unsigned long *lo);
unsigned long float_bits(double v);      /* 408b90: IEEE single bits of (float)v */
double words_to_double(unsigned long hi, unsigned long lo);
void double_to_words(double d, unsigned long *hi, unsigned long *lo);

/* eval.c */
EXPR *eval_int(void);
EXPR *eval_abs(void);
long eval_nonneg(void);
long eval_nonneg_resolved(void);
EXPR *eval_expr(void);
EXPR *parse_expr(void);
EXPR *op_bad(EXPR *lhs, EXPR *rhs);
void classify_value(EXPR *e);
EXPR *new_expr(void);
void free_expr(EXPR *e);
void free_expr_stack_all(void);

/* fixup.c */
void fixup_relocate(void);
void fixup_check_secsizes(void);

/* func.c */
EXPR *func_call_eval(EXPR *e);

/* input.c */
void process_input_files(void);
MODULE *new_module(char *name, long size, long offset);
int process_module(MODULE *mod);
SYMSLOT *read_symbol_entries(unsigned long n);
char *read_string_table(void);
SECTION *find_section_record(unsigned long flags, unsigned long addr);
SECTION *find_buffer_record(unsigned long flags, unsigned long addr);
SECTION *get_overlay_record(void);

/* lib.c */
void free_dup_globals_list(void);
int is_library_arg(void);
void check_library_magic(char *libname);
void scan_library(void);

/* map.c */
void map_write(void);
void map_check_overlap(void);
void map_sort_pieces_size(SECTION **arr, long n);
void map_sort_pieces_num(SECTION **arr, long n);
void map_sort_memregs(MEMREG **arr, long n);
void map_unresolved_stderr(void);
int mem_order(long a, long b);
int mem_order_l(long a, long b);

/* memctl.c */
int memctl_process_file(int pass);
void memctl_assign_region(MEMREG *mr, SECTION *sec, long how);
int set_x_options(char *list);
SECTION *memctl_reserve_piece(MEMSPEC *spec, unsigned long lo, unsigned long hi);

/* object.c */
void obj_layout_offsets(void);
void obj_write_file(void);
void obj_write_module(MODULE *m);
void obj_add_file_secsyms(void);
long obj_add_syment(SYMSLOT *e);
long obj_add_string(char *s);
void obj_add_comment(char *text, long scnum);

/* sdi.c */
void sdi_stats_new(SECTION *sec);
void sdi_add(unsigned long addr, unsigned long orig, char *expr, long opsz,
             long opsz2, unsigned long flags, long alt1, long alt2);
int sdi_next_form(void);
void sdi_resolve_all(void);
void sdi_free(SECTION *sec);
void sdi_reset_all(void);
int opsize_fits(unsigned long v, long opsz);

/* symtab.c */
SECTION *sec_lookup_create(char *name, long secno, MEMSPEC *spec, int add_map);
SECTION *sec_alloc(SECNODE *node, unsigned long flags);
SECTION *sec_find(char *name, MEMSPEC *spec);
SECNAME *secname_new(char *name, long num);
SECNAME *secname_lookup(char *name);
SECNODE *secnode_get(SECNAME *sn, MEMSPEC *spec);
SECNODE *secnode_find(SECNAME *sn, MEMSPEC *spec);
REGION *region_get(char *name);
REGION *region_find(char *name);
MEMREG *memreg_get(REGION *rg, MEMSPEC *spec, int remap);
MEMREG *memreg_new(REGION *rg, MEMSPEC *spec);
MEMREG *memreg_find(REGION *rg, MEMSPEC *spec);
SYM *sym_enter(SYM *tmpl);
SYM *sym_lookup(char *name, int defining);
XREF *xref_add(char *name, int force, int is_xref);
XREF *xref_lookup(char *name);
void xref_purge(void);
void xref_remove(XREF *x);
void free_sort_arrays(void);
void free_memmaps(void);
void free_sections(void);
void sym_free_all(void);
void xref_free_all(void);
void free_section_xrefs(void);
void free_module_tables(void);
void free_input_files(void);
void free_ranges(RANGE *r);
void free_ctr_groups(void);
KEYWORD *find_memctl_kw(char *name);
KEYWORD *find_map_opt(char *name);
KEYWORD *find_xopt(char *name);
int name_cmp(void *key, void *entry);
int sec_has_xref(char *name);

/* util.c */
void *xmalloc(unsigned long size);
void *xrealloc(void *p, unsigned long size);
void xfree(void *p);
void *tab_search(void *key, void *base, long count, long size,
                 int (*cmp)(void *key, void *elem));
void sort_ptrs(long lo, long hi);
unsigned long hash_name(char *s);
char *base_name(char *path);
char *get_string(char *src, char *dst);
char *get_symbol(void);
int get_mem_spec(MEMSPEC *ms);
int mem_space_char(long space);
long mem_bits_space(long bits);
int mem_space_index(long space);
long index_mem_space(int idx);
int mem_bits_counter(long bits);
long char_to_mem_space(int c);
int char_to_counter(int c);
long char_to_mem_map(int c1, int c2, long space);
long map_to_space(long map);
long mem_bits_map(long space, long bits);
char *str_upper(char *s);
char *str_lower(char *s);
void set_file_buffer(FILE *fp, int which);
int tok_is_digits(void);
long merge_mem_space(long space, long space2);
char *fmt_double(char *buf, char *fmt, double val);
void clear_coff_sym(void);
long tm_to_secs(struct tm *tm);
unsigned long buf_align(unsigned long addr, unsigned long bufsize, unsigned long mask);
unsigned long round_up_pow2(unsigned long n);
/* util.c port helpers (replace fread_swapped/fwrite_swapped/swap_words and
   the obj_fread/obj_fwrite family): big-endian codecs.  The read_* functions
   return the number of whole records read (callers compare with n), the
   write_* functions the number written; none modifies its argument. */
unsigned long get_be32(unsigned char *p);
void put_be32(unsigned char *p, unsigned long v);
void name_swap(char *n);                      /* = swap_words(n,4,2) */
unsigned long name_off(char *n);              /* strtab offset of a long name */
void set_name_off(char *n, unsigned long v);
unsigned long read_filhdr(FILHDR *h, FILE *fp);
unsigned long write_filhdr(FILHDR *h, FILE *fp);
unsigned long read_lnkhdr(LNKHDR *h, long nbytes, FILE *fp);  /* consumes nbytes, fills <= 14 fields */
unsigned long write_lnkhdr(LNKHDR *h, FILE *fp);
unsigned long write_aouthdr(AOUTHDR *h, FILE *fp);
unsigned long read_scnhdrs(SCNHDR *s, unsigned long n, FILE *fp);
unsigned long write_scnhdrs(SCNHDR *s, unsigned long n, FILE *fp);
unsigned long read_symslots(SYMSLOT *s, unsigned long n, FILE *fp);   /* main/aux by position */
unsigned long write_symslots(SYMSLOT *s, unsigned long n, FILE *fp);
unsigned long read_relents(RELENT *r, unsigned long n, FILE *fp);
unsigned long write_relents(RELENT *r, unsigned long n, FILE *fp);
unsigned long read_linenos(LINENO *l, unsigned long n, FILE *fp);
unsigned long write_linenos(LINENO *l, unsigned long n, FILE *fp);
unsigned long read_words(unsigned long *w, unsigned long n, FILE *fp);
unsigned long write_words(unsigned long *w, unsigned long n, FILE *fp);

/* elfout.c / cof2elf.c (low priority) */
long elf_tell(void);
void elf_seek(long pos, FILE *fp);
void elf_write_sections(FILE *fp);
void elf_write_data(void *buf, unsigned long size, unsigned long n, FILE *fp);
void elf_write_field(void *p, unsigned long size, unsigned long n, FILE *fp);
ELFSEC *elf_new_section(char *name);
void elf_init(void);
int coff_to_elf(char *coff_path, char *elf_path);

/* ABI expression parser (abi*.c; may be stubbed) */
EXPR *abi_expr_eval(MODULE *mod, long flag, char *text);       /* 43a260: 0 = not ABI */
EXPR *abi_expr_eval_impl(MODULE *mod, long flag, char *text);  /* 43a289 */
void abi_free_all(void);                                       /* 43a394 */
void *abimparr_create(long init, long blk, void (*freefn)(void *));  /* 43457a */
void abi_mp_sym_free_with_arr(void *elem);                     /* 434c30 */
void abi_mp_symtbl_dispatch(void *arr, MODULE *mod);           /* 43a3e3 */

/* added by util.c: plain fread/fwrite (43055b / 4306a1), e.g. string table bytes */
unsigned long obj_fread(void *buf, unsigned long size, unsigned long n, FILE *fp);
unsigned long obj_fwrite(void *buf, unsigned long size, unsigned long n, FILE *fp);

/* added by eval.c: expression stack (461f28/461f2c); an EXPR built outside
   new_expr is registered with *expr_sp++ = e (ABI re-push); new_expr grows it */
extern EXPR **expr_stack;
extern EXPR **expr_sp;

#endif /* DSPLNK_H */
