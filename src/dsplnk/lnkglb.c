/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), lnkglb.c
 * "$Id: lnkglb.c,v 1.15 1999/06/30 21:22:26 ra8614 Exp $"
 *
 * 1. The initialized globals of the original lnkglb.c (.data 0x457b10 ..
 *    0x458e38), decoded from DSPLNK.EXE.  String literals of that range that
 *    the code only uses as constants (".cln", ".txt", "%08lX" ...) are left
 *    to the modules as literals.
 * 2. The definitions of all other globals used by more than one source file
 *    (BSS in the original; addresses in the comments).
 * All declarations are in dsplnk.h, so compiling this file cross-checks them.
 */
#include "dsplnk.h"

/* ---- initialized data (.data 0x457b10..0x458e38) ---- */
long stack_mspace = 2;                  /* 457b48 */
char map_buffer = 1;                    /* 457b4c */
char map_const = 1;                     /* 457b50 */
char map_local = 1;                     /* 457b54 */
char map_overlay = 1;                   /* 457b58 */
char map_secaddr = 1;                   /* 457b5c */
char map_secname = 1;                   /* 457b60 */
char map_symname = 1;                   /* 457b64 */
char map_symval = 1;                    /* 457b68 */
char map_unused = 1;                    /* 457b6c */
char map_globsym = 1;                   /* 457b70 */
char nested_secs = 1;                   /* 457b74 */
char opt_abc = 1;                       /* 457b78 */
char opt_aec = 1;                       /* 457b7c */
char opt_rsc = 1;                       /* 457b80 */
char opt_wvr = 1;                       /* 457b84 */
long run_reloc = 1;                     /* 457b88 */
long load_reloc = 1;                    /* 457b8c */
char map_need_hdr = 1;                  /* 457b90 */
char opt_sdi = 1;                       /* 457b94 */
char load_aligned = 1;                  /* 457b98 */
long addr_bytes = 1;                    /* 457b9c */
long verbose_level = 100;               /* 457ba0 */
long radix = 10;                        /* 457ba4 */
long start_mem = 4;                     /* 457ba8 */
long text_lo_mem = 4;                   /* 457bac */
long data_lo_mem = 4;                   /* 457bb0 */
long text_hi_mem = 4;                   /* 457bb4 */
long data_hi_mem = 4;                   /* 457bb8 */
long map_col = 1;                       /* 457bbc */
long map_lcol = 1;                      /* 457bc0 */
long map_width = MAP_WIDTH_DEF;         /* 457bc4 */
long map_lmargin = 1;                   /* 457bc8 */
long map_line = 1;                      /* 457bcc */
long map_lastline = MAP_PAGELEN_DEF;    /* 457bd0 */
long map_pagelen = MAP_PAGELEN_DEF;     /* 457bd4 */
char map_hdr_on = 1;                    /* 457bd8 */
long map_topmargin = MAP_TOPMARGIN_DEF; /* 457bdc */
long map_botmargin = MAP_BOTMARGIN_DEF; /* 457be0 */
char ident_none[8] = "NONE";            /* 457be8 */
char *base_fname = empty_str;           /* 457bf0 */
char *cform_prefix = empty_str;         /* 457bf4 */
long ctl_level = 1;                     /* 457bfc */
long cur_scnum = -1;                    /* 457c00 */
long obj_strsize = 4;                   /* 457c04 */
FILE *msg_fp;                           /* 457c08 = stderr; main() sets it first
                                           (stderr is not a C89 constant) */
long tgt_unk24 = 1;                     /* 457c0c */

TARGET target_tab[NTARGETS + 1] = {   /* 457c18 */
    { "DSP56000", 0x2c5UL, 3L, 0xffffUL, 0x1fffffUL, 0xffc0UL, 0xffc0UL, 0xffffffUL, 0x800000UL, 1L, 0L, 6L, 4L, 8L, 5L, "%06lX", "%04lX", "%08lX", "%06lX" },
    { "DSP96000", 0x2c6UL, 4L, 0xffffffffUL, 0xffffffffUL, 0xffffff80UL, 0xffffff80UL, 0xffffffffUL, 0x80000000UL, 512L, 1023L, 8L, 8L, 8L, 10L, "%08lX", "%08lX", "%08lX", "%08lX" },
    { "DSP56100", 0x2c7UL, 2L, 0xffffUL, 0xffffUL, 0xffc0UL, 0xffc0UL, 0xffffUL, 0x8000UL, 1L, 0L, 4L, 4L, 8L, 5L, "%04lX", "%04lX", "%08lX", "%04lX" },
    { "DSP56300", 0x2c8UL, 3L, 0xffffffUL, 0x1fffffUL, 0xffff80UL, 0xffff80UL, 0xffffffUL, 0x800000UL, 1L, 0L, 6L, 6L, 8L, 8L, "%06lX", "%06lX", "%08lX", "%06lX" },
    { "DSP56800", 0x2c9UL, 2L, 0xffffUL, 0x7ffffUL, 0xff80UL, 0xffc0UL, 0xffffUL, 0x8000UL, 1L, 0L, 4L, 4L, 8L, 5L, "%04lX", "%06lX", "%08lX", "%04lX" },
    { "DSP56600", 0x2caUL, 3L, 0xffffUL, 0xffffffffUL, 0xff80UL, 0xffc0UL, 0xffffffffUL, 0x80000000UL, 1L, 0L, 6L, 4L, 8L, 5L, "%06lX", "%04lX", "%08lX", "%04lX" },
    { "100", 0x2cbUL, 2L, 0xffffffffUL, 0xffffffffUL, 0xffffff80UL, 0xffffffc0UL, 0xffffUL, 0x8000UL, 1L, 0L, 4L, 8L, 8L, 10L, "%04lX", "%08lX", "%08lX", "%04lX" },
    { "DSP56700", 0x2ccUL, 2L, 0x7ffffUL, 0x7ffffUL, 0xff80UL, 0xffc0UL, 0xffffffUL, 0x800000UL, 1L, 0L, 4L, 8L, 8L, 6L, "%04lX", "%08lX", "%08lX", "%04lX" },
    { 0, 0x0UL, 0L, 0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL, 0L, 0L, 0L, 0L, 0L, 0L, 0, 0, 0, 0 }
};

char *progname = "dsplnk";              /* 457ed0 -> 457ec8 */
char lnk_name[] = "Linker";             /* 457ed8 */
char lnk_version[] = "6.3.7 ";          /* 457ee0 */
char lnk_copyright[] =                  /* 457ee8 */
    "(C) Copyright Motorola, Inc. 1987-1998.  All rights reserved.";
char env_name[] = "DSPLNKOPT";          /* 457f28 */
char optstring[] = OPTSTRING;           /* 457f38 */
char default_region[] = "DEFAULT";      /* 457f80 */
char global_secname[] = "GLOBAL";       /* 457f88 */
char reserve_secname[] = "RESERVE";     /* 457f90 */
char lib_magic[] = LIB_MAGIC;           /* 457f98 */
long lib_magic_len = LIB_MAGIC_LEN;     /* 457fa0 */
char *ident_name = ident_none;          /* 457fa4 */
char *ident_comment = empty_str;        /* 457fa8 */
char mem_idx_char[] = " XYLPEDU";       /* 457ff0 */

KEYWORD memctl_kw_tab[NMEMCTL_KW] = {   /* 00458010 */
    { "alignsym", 18 }, { "balign", 10 }, { "base", 5 }, { "endr", 14 },
    { "ident", 11 }, { "include", 15 }, { "map", 6 }, { "memory", 7 },
    { "region", 13 }, { "reserve", 9 }, { "sbalign", 16 }, { "secsize", 12 },
    { "section", 2 }, { "set", 3 }, { "sizsym", 17 }, { "start", 1 },
    { "symbol", 3 }
};
KEYWORD memctl_mapopt_tab[NMAP_OPT] = {   /* 004580a0 */
    { "globmap", 10 }, { "nobuffer", 7 }, { "noconst", 1 }, { "noglobsym", 11 },
    { "nolocal", 2 }, { "nooverlay", 8 }, { "nosecaddr", 3 }, { "nosecname", 4 },
    { "nosymname", 5 }, { "nosymval", 6 }, { "nounused", 9 }, { "symlen", 12 }
};
KEYWORD memctl_xopt_tab[NXOPT] = {   /* 00458108 */
    { "abc", 1 }, { "aec", 3 }, { "asc", 7 }, { "csl", 20 },
    { "eso", 9 }, { "ff", 18 }, { "isw", 29 }, { "mcm", 32 },
    { "noabc", 2 }, { "noaec", 4 }, { "noasc", 8 }, { "nocsl", 21 },
    { "noeso", 10 }, { "noff", 19 }, { "nomcm", 33 }, { "noovlp", 14 },
    { "noro", 6 }, { "norsc", 17 }, { "nosbm", 25 }, { "nosdi", 23 },
    { "nowdg", 31 }, { "nowex", 12 }, { "nowvr", 27 }, { "osp", 28 },
    { "ovlp", 13 }, { "ro", 5 }, { "rsc", 16 }, { "sbm", 24 },
    { "sdi", 22 }, { "svo", 15 }, { "wdg", 30 }, { "wex", 11 },
    { "wvr", 26 }
};
int memctl_kw_cnt = NMEMCTL_KW;         /* 458098 */
int memctl_mapopt_cnt = NMAP_OPT;       /* 458100 */
int memctl_xopt_cnt = NXOPT;            /* 458210 */

BINOP_FN binop_tab[NBINOPS] = {         /* 458218 */
    op_bad, op_add, op_sub, op_mul, op_div, op_and, op_or, op_xor,
    op_mod, op_shl, op_shr, op_lt, op_gt, op_eq, op_le, op_ge,
    op_ne, op_land, op_lor, op_size_check, op_space, op_mapping, op_line, 0
};

FUNCTAB func_tab[NFUNCS] = {   /* 00458278 */
    { "aenc", 12L, 0L }, { "byt", 5L, 0L }, { "ceil2", 10L, 0L }, { "enc", 3L, 0L },
    { "fb2", 4L, 0L }, { "fbf", 1L, 0L }, { "hb", 14L, 0L }, { "imax", 8L, 0L },
    { "imin", 9L, 0L }, { "lb", 13L, 0L }, { "lrf", 2L, 0L }, { "sdi", 6L, 0L },
    { "sdi2", 7L, 0L }, { "szck", 11L, 0L }
};
long func_count = NFUNCS;               /* 458320 */
long mon_days[12] = { 31L, 28L, 31L, 30L, 31L, 30L, 31L, 31L, 30L, 31L, 30L, 31L };   /* 458328 */
long mon_days_leap[12] = { 31L, 29L, 31L, 30L, 31L, 30L, 31L, 31L, 30L, 31L, 30L, 31L };   /* 458358 */

unsigned long emi_max_addr[256] = {   /* 458388, index mmap - MM_E0 */
    0x7fffUL, 0x7fffUL, 0x7fffUL, 0x7fffUL, 0x7fffUL, 0x7fffUL,
    0x7fffUL, 0x7fffUL, 0x1ffffUL, 0x3ffffUL, 0xffffUL, 0x1ffffUL,
    0x7fffUL, 0xffffUL, 0x7fffUL, 0xffffUL, 0x1ffffUL, 0x3ffffUL,
    0xffffUL, 0x1ffffUL, 0x7fffUL, 0xffffUL, 0x7fffUL, 0xffffUL,
    0xffffUL, 0x1ffffUL, 0x7fffUL, 0xffffUL, 0x3fffUL, 0x7fffUL,
    0x3fffUL, 0x7fffUL, 0x7fffUL, 0xffffUL, 0x3fffUL, 0x7fffUL,
    0x1fffUL, 0x3fffUL, 0x1fffUL, 0x3fffUL, 0x1ffffUL, 0x3ffffUL,
    0xffffUL, 0x1ffffUL, 0x7fffUL, 0xffffUL, 0x7fffUL, 0xffffUL,
    0x7ffffUL, 0xfffffUL, 0x3ffffUL, 0x7ffffUL, 0x1ffffUL, 0x3ffffUL,
    0x1ffffUL, 0x3ffffUL, 0x1fffffUL, 0x3fffffUL, 0xfffffUL, 0x1fffffUL,
    0x7ffffUL, 0xfffffUL, 0x7ffffUL, 0xfffffUL, 0x0UL, 0x0UL,
    0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL,
    0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL,
    0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL,
    0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL,
    0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL,
    0xffffUL, 0xffffUL, 0xffffUL, 0xffffUL, 0xffffUL, 0xffffUL,
    0xffffUL, 0xffffUL, 0x3ffffUL, 0x3ffffUL, 0x3ffffUL, 0x3ffffUL,
    0x3ffffUL, 0x3ffffUL, 0x3ffffUL, 0x3ffffUL, 0xfffffUL, 0xfffffUL,
    0xfffffUL, 0xfffffUL, 0xfffffUL, 0xfffffUL, 0xfffffUL, 0xfffffUL,
    0x3fffffUL, 0x3fffffUL, 0x3fffffUL, 0x3fffffUL, 0x3fffffUL, 0x3fffffUL,
    0x3fffffUL, 0x3fffffUL, 0x0UL, 0x0UL, 0x7fffUL, 0x7fffUL,
    0x7fffUL, 0x7fffUL, 0x0UL, 0x0UL, 0x0UL, 0x0UL,
    0xffffUL, 0x1ffffUL, 0x7fffUL, 0xffffUL, 0x0UL, 0x0UL,
    0x0UL, 0x0UL, 0xffffUL, 0x1ffffUL, 0x7fffUL, 0xffffUL,
    0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x7fffUL, 0xffffUL,
    0x3fffUL, 0x7fffUL, 0x0UL, 0x0UL, 0x0UL, 0x0UL,
    0x3fffUL, 0x7fffUL, 0x1fffUL, 0x3fffUL, 0x0UL, 0x0UL,
    0x0UL, 0x0UL, 0xffffUL, 0x1ffffUL, 0x7fffUL, 0xffffUL,
    0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x3ffffUL, 0x7ffffUL,
    0x1ffffUL, 0x3ffffUL, 0x0UL, 0x0UL, 0x0UL, 0x0UL,
    0xfffffUL, 0x1fffffUL, 0x7ffffUL, 0xfffffUL, 0x0UL, 0x0UL,
    0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL,
    0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL,
    0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL,
    0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL,
    0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x0UL,
    0x0UL, 0x0UL, 0x0UL, 0x0UL, 0xffffUL, 0xffffUL,
    0xffffUL, 0xffffUL, 0x0UL, 0x0UL, 0x0UL, 0x0UL,
    0x3ffffUL, 0x3ffffUL, 0x3ffffUL, 0x3ffffUL, 0x0UL, 0x0UL,
    0x0UL, 0x0UL, 0xfffffUL, 0xfffffUL, 0xfffffUL, 0xfffffUL,
    0x0UL, 0x0UL, 0x0UL, 0x0UL, 0x3fffffUL, 0x3fffffUL,
    0x3fffffUL, 0x3fffffUL, 0x0UL, 0x0UL
};

/* ---- shared uninitialized globals ---- */
FILE *err_fp;                           /* 461f34 */
FILE *obj_fp;                           /* 461f38 */
FILE *map_fp;                           /* 461f3c */
FILE *ctl_fp;                           /* 461f40 */
FILE *in_fp;                            /* 461db4 */
char *obj_name;                         /* 461d64 */
char namebuf[NAMEBUF_SIZE];             /* 461528 */
char title_name[NAMEBUF_SIZE];          /* 461730 */
char empty_str[4];                      /* 46131c */
long link_time;                         /* 461d44 */
char date_str[16];                      /* 461d48 */
char time_str[12];                      /* 461d58 */
char opt_mcm;                           /* 4611d8 */
char map_symlen_on;                     /* 4611e0 */
long map_symlen;                        /* 4611e4 */
char opt_wdg;                           /* 4611e8 */
char opt_s;                             /* 4611ec */
char suppress_errors;                   /* 4611f0 */
char no_argv_mode;                      /* 4611f4 */
char lib_rescan;                        /* 4611fc */
char in_brace;                          /* 461200 */
char map_globmap;                       /* 461208 */
char opt_c;                             /* 46120c */
char cc_objects;                        /* 461210 */
char opt_n;                             /* 461214 */
char opt_asc;                           /* 461228 */
char opt_ro;                            /* 46122c */
char opt_eso;                           /* 461230 */
char opt_wex;                           /* 461234 */
char opt_ovlp;                          /* 461238 */
char opt_svo;                           /* 46123c */
char opt_ff;                            /* 461240 */
char opt_csl;                           /* 461244 */
char opt_i;                             /* 461248 */
char opt_g;                             /* 46124c */
char opt_z;                             /* 461250 */
char start_given;                       /* 461254 */
char opt_v;                             /* 46125c */
char opt_t;                             /* 461260 */
char opt_q;                             /* 461264 */
char colon_short;                       /* 461268 */
char opt_a;                             /* 46126c */
char mod_sdi;                           /* 461270 */
char sdi_active;                        /* 461274 */
char sdi_seen;                          /* 461278 */
char sdi_changed;                       /* 46127c */
char two_words;                         /* 461280 */
char addr_cancel;                       /* 461284 */
char opt_sbm;                           /* 461288 */
char opt_osp;                           /* 46128c */
char opt_isw;                           /* 461290 */
int pass;                               /* 461294 */
long sec_num_seed;                      /* 461298 */
long num_secs;                          /* 46129c */
long cur_rsecno;                        /* 4612a0 */
long cur_secid;                         /* 4612a4 */
long cur_rsecid;                        /* 4612a8 */
long cur_buffer;                        /* 4612ac */
long num_buffers;                       /* 4612b0 */
long buf_seq;                           /* 4612b4 */
unsigned long buf_type;                 /* 4612b8 */
long buf_base;                          /* 4612c4 */
long cur_overlay;                       /* 4612c8 */
long num_overlays;                      /* 4612cc */
long ovl_seq;                           /* 4612d0 */
long ovl_base;                          /* 4612d8 */
long num_syms;                          /* 4612dc */
long num_xrefs;                         /* 4612e0 */
long num_xrefs_done;                    /* 4612e4 */
long block_depth;                       /* 4612e8 */
long error_count;                       /* 4612ec */
long warning_count;                     /* 4612f0 */
long suppressed_errors;                 /* 4612f4 */
unsigned long start_addr;               /* 4612fc */
unsigned long text_lo;                  /* 461300 */
unsigned long data_lo;                  /* 461304 */
unsigned long text_hi;                  /* 461308 */
unsigned long data_hi;                  /* 46130c */
long map_pageno;                        /* 461310 */
long src_line;                          /* 461314 */
long ctl_lineno;                        /* 461318 */
char ctl_token[NAMEBUF_SIZE];           /* 461320 */
char err_symbol[ERRSYM_SIZE];           /* 461b40 */
char *input_cursor;                     /* 461d68 */
char *cform_ptr;                        /* 461d6c */
MEMSPEC run_spec;                       /* 461d70 */
MEMSPEC load_spec;                      /* 461d80 */
unsigned long *run_ctr;                 /* 461d90 */
unsigned long *load_ctr;                /* 461d94 */
long cur_argc;                          /* 461da0 */
char **cur_argv;                        /* 461da4 */
INFILE *infile_head;                    /* 461db8 */
INFILE *cur_infile;                     /* 461dbc */
char *start_name;                       /* 461dc4 */
long (*sort_cmp)(void *, void *);       /* 461dc8 */
REGION *region_head;                    /* 461dcc */
REGION *cur_region;                     /* 461dd0 */
MEMREG *cur_memreg;                     /* 461dd4 */
SECTION *cur_section;                   /* 461ddc */
SECTION *cur_rsection;                  /* 461de0 */
SECTION *cur_alloc;                     /* 461de4 */
MODSEC **mod_secmap;                    /* 461de8 */
MODSEC *cur_rmsec;                      /* 461df0 */
RANGE *used_ranges[NMEMIDX];            /* 461df8 */
CTRGROUP *ctr_groups;                   /* 461e24 */
RANGE **ctr_lists;                      /* 461e28 */
BUFREF *mod_buftab;                     /* 461e5c */
OVLENT *mod_ovltab;                     /* 461e60 */
SYMSLOT *cur_file_ent;                  /* 461e68 */
long cur_symidx;                        /* 461e7c */
REGION *region_last;                    /* 461e80 */
SECTREF *cur_sectref;                   /* 461e90 */
long obj_nscns;                         /* 461e98 */
unsigned long obj_nwords;               /* 461ea8 */
unsigned long obj_nreloc;               /* 461eb4 */
unsigned long obj_lnnoptr0;             /* 461ec0 */
unsigned long obj_lnnoptr;              /* 461ec4 */
unsigned long obj_nlnno;                /* 461ec8 */
long sdi_total;                         /* 461ef0 */
long out_nsdi;                          /* 461ef4 */
long obj_sditot;                        /* 461ef8 */
long num_set_syms;                      /* 461efc */
SECNEST *sec_nest;                      /* 461f00 */
FILEEXT *obj_fext_head;                 /* 461f04 */
FILEEXT *obj_fext_cur;                  /* 461f08 */
long obj_nlnno_file;                    /* 461f0c */
STRNODE *libpath_head;                  /* 461f10 */
STRNODE *libpath_tail;                  /* 461f14 */
void **sort_array;                      /* 461f18 */
SYM **map_syms;                         /* 461f1c */
SECTION **map_secs;                     /* 461f20 */
XREF **map_xrefs;                       /* 461f24 */
char in_eval;                           /* 461f30 */
jmp_buf eval_jmpbuf;                    /* 46c300 */
SYM *sym_found;                         /* 4611dc */

TARGET *cur_target;                     /* 461fc0 */
long target_index;                      /* 461f44 */
char *target_name;                      /* 461f48 */
long word_bytes;                        /* 461f4c */
long word_hexdig;                       /* 461f50 */
long dword_hexdig;                      /* 461f54 */
long word_bits;                         /* 461f58 */
long dword_bits;                        /* 461f5c */
long fmt_word;                          /* 461f60 */
long fmt_dword;                         /* 461f64 */
unsigned long word_mask;                /* 461f6c */
unsigned long sign_bit;                 /* 461f70 */
unsigned long addr_mask;                /* 461f74 */
unsigned long ext_addr_mask;            /* 461f78 */
unsigned long io_base;                  /* 461f7c */
unsigned long io_base2;                 /* 461f80 */
unsigned long io_base_neg;              /* 461f84 */
unsigned long io_short_max;             /* 461f88 */
unsigned long io_base2_neg;             /* 461f8c */
unsigned long io_short2_max;            /* 461f90 */
unsigned long frac_min;                 /* 461f98 */
unsigned long frac_max;                 /* 461f9c */
unsigned long target_magic;             /* 461fa0 */
long word_digits;                       /* 461fa4 */
char *word_fmt;                         /* 461fb4 */
char *value_fmt;                        /* 461fb8 */
char *addr_fmt;                         /* 461fbc */
long global_secno;                      /* 461fc4 */
long ident_ver;                         /* 461fc8 */
long ident_rev;                         /* 461fcc */
long out_major;                         /* 461fd0 */
long out_minor;                         /* 461fd4 */
long out_rev;                           /* 461fd8 */
long lnk_major;                         /* 461fdc */
long lnk_minor;                         /* 461fe0 */
long lnk_rev;                           /* 461fe4 */
long obj_major;                         /* 461fe8 */
long obj_minor;                         /* 461fec */
long obj_rev;                           /* 461ff0 */

SYM *sym_hash[HASHSIZE];                /* 461ff8 */
SECNAME *sec_hash[HASHSIZE];            /* 463f48 */
XREF *xref_hash[HASHSIZE];              /* 465e98 */

SYMSLOT obj_auxbuf;                     /* 46c080 */
SYMSLOT obj_symbuf;                     /* 46c140 */
MEMSPEC ovl_mem;                        /* 46c2e0 */
LNKHDR obj_lnkhdr;                      /* 46c340 */
void *abi_modules;                      /* 46c604 */
