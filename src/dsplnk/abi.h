/*
 * abi.h - shared declarations of the DSPLNK "ABI expression" subsystem
 * (DSPLNK.EXE of CLAS56 v6.3, address range 0x433620-0x43a40d):
 *   InfArray containers (longarr.c symarr.c mparr.c formarr.c),
 *   symbol/module/form tables and the op/func/conv library
 *   (symtbl.c mpsym.c formtbl.c abiops.c abiutil.c abiform.c abifunc.c
 *   abiconv.c abiglue.c), the flex scanner (abilex.c) and the yacc parser
 *   (abiparse.c).
 *
 * Portability conventions of this subsystem:
 *   - The original passes 32-bit `int`/`uint` values.  Here every such value is
 *     an `unsigned long` holding the 32-bit pattern (always masked with
 *     M32() before it is stored, compared or passed on).  Where the original
 *     uses the SIGNED interpretation (div, mod, <, <=, >, >=, sign checks) the
 *     op_* functions convert with ABI_S32().
 *   - 64-bit values (Ghidra longlong, edx:eax) are passed as two 32-bit halves
 *     (lo, hi) and returned as an ABI64 structure.
 *   - Original function names are those of re/names/DSPLNK/l4_util.names.txt.
 *     Several of those names are misleading (e.g. op_uplus is a+b); every
 *     prototype below carries the true semantics as verified from the
 *     disassembly.
 *
 * NOTE for the lexer/parser owner: the following globals are DEFINED in
 * abiglue.c (declared extern below): abi_expr_text, abi_expr_text_end,
 * g_symtblarr, g_formarr, abi_parse_ctx, abi_errbuf.  yyin and the flex/yacc
 * state (0x46ad00..0x46c05c region, 0x46c07c, 0x46c040, ...) are owned by
 * abilex.c/abiparse.c.  abi_modules (46c604) is defined in lnkglb.c.
 */
#ifndef ABI_H
#define ABI_H

#include "dsplnk.h"

/* ---- 32-bit helpers ------------------------------------------------- */
/* signed interpretation of a masked 32-bit pattern, as a (64-bit safe) long */
#define ABI_S32(x)  ((long)((((unsigned long)(x) & 0xffffffffUL) ^ 0x80000000UL) - 0x80000000UL))

typedef struct abi64 {              /* a Win32 `longlong` result (edx:eax) */
    unsigned long lo;               /* eax, 32-bit pattern */
    unsigned long hi;               /* edx, 32-bit pattern */
} ABI64;

/* ---- InfArray -------------------------------------------------------
 * Generic growable array; hand-instantiated four times in the original
 * (LONGInfArray.c, symtableInfArray.c, ABI_mp_symtblInfArray.c,
 * formtableInfArray.c).  The header is 0x40 bytes; the C layout follows the
 * original offsets.  `flags` is the parallel array of `int` (1 = element
 * added with `add`, i.e. owned: `freefn` is applied to it by free_storage).
 *
 * Slot map (verified from the four create functions, identical in all):
 *   +0x00 blocksz    growth quantum (0 -> 0x32)
 *   +0x04 init_sz    initial size as requested
 *   +0x08 array_size allocated capacity (elements)
 *   +0x0c remove     1 once an element was added with `add` (owned elements)
 *   +0x10 max_index  highest index ever set (-1 empty)
 *   +0x14 last_index last index set (-1 empty)
 *   +0x18 flags      long-sized flag per element (the original: int)
 *   +0x1c data       element storage
 *   +0x20 get(arr, idx)             bounds checked, asserts on violation
 *   +0x24 insert(arr, idx, val)     store at idx (grows), no owner flag
 *   +0x28 append(arr, idx, val)     store at idx (grows), owner flag = 1
 *   +0x2c compact(arr)              free_storage + reinit (empty again)
 *   +0x30 add_plain(arr, val)       = insert(arr, last_index + 1, val)
 *                                     (original names it *_is_full)
 *   +0x34 add(arr, val)             = append(arr, last_index + 1, val)
 *                                     (original names it *_is_empty)
 *   +0x38 dump(arr)                 debug dump to stdout
 *   +0x3c freefn(elem)              element destructor (default: no-op *_count)
 */
#define INFARRAY_DECL(NAME, ELEM)                                          \
typedef struct NAME NAME;                                                  \
struct NAME {                                                              \
    long blocksz;                                                          \
    long init_sz;                                                          \
    long array_size;                                                       \
    long remove;                                                           \
    long max_index;                                                        \
    long last_index;                                                       \
    long *flags;                                                           \
    ELEM *data;                                                            \
    ELEM (*get)(NAME *, long);                                             \
    void (*insert)(NAME *, long, ELEM);                                    \
    void (*append)(NAME *, long, ELEM);                                    \
    void (*compact)(NAME *);                                               \
    void (*add_plain)(NAME *, ELEM);                                       \
    void (*add)(NAME *, ELEM);                                             \
    void (*dump)(NAME *);                                                  \
    void (*freefn)(ELEM);                                                  \
}

/* LONGInfArray (0x433620): elements are longs */
INFARRAY_DECL(LONGArr, long);
/* symtableInfArray (0x433d00): elements are ABISYM * */
struct abisym;
INFARRAY_DECL(SymArr, struct abisym *);
/* ABI_mp_symtblInfArray (0x434550): elements are ABIMPENT * (void * so that
   the prototypes of dsplnk.h, which use void *, stay compatible) */
INFARRAY_DECL(MpArr, void *);
/* formtableInfArray (0x434e80): elements are ABIFORM * */
struct abiform;
INFARRAY_DECL(FormArr, struct abiform *);

/* The 12 functions of one instantiation; PFX = longarr / symtblarr /
   abimparr / formarr (original names <PFX>_destroy ... <PFX>_count).
   *_is_full / *_is_empty are the add_plain / add slots; *_count is the
   default freefn (no-op, takes an element). */
#define INFARRAY_PROTOS(PFX, NAME, ELEM)                                   \
void PFX ## _destroy(NAME *arr);                                           \
NAME *PFX ## _create(long init_sz, long blocksz, void (*freefn)(ELEM));    \
void PFX ## _dump(NAME *arr);                                              \
void PFX ## _free_storage(NAME *arr);                                      \
void PFX ## _compact(NAME *arr);                                           \
void PFX ## _grow(NAME *arr, long need);                                   \
void PFX ## _append(NAME *arr, long idx, ELEM val);                        \
void PFX ## _insert(NAME *arr, long idx, ELEM val);                        \
ELEM PFX ## _get(NAME *arr, long idx);                                     \
void PFX ## _is_empty(NAME *arr, ELEM val);                                \
void PFX ## _is_full(NAME *arr, ELEM val);                                 \
void PFX ## _count(ELEM val)

INFARRAY_PROTOS(longarr, LONGArr, long);       /* longarr.c  433620-433bc0 */
INFARRAY_PROTOS(symtblarr, SymArr, struct abisym *);   /* symarr.c 433d00 */
/* mparr.c 434550: abimparr_create/abi_mp_sym_free_with_arr keep the
   prototypes declared in dsplnk.h (void *), the rest is typed here */
void abimparr_destroy(MpArr *arr);
void abimparr_dump(MpArr *arr);
void abimparr_free_storage(MpArr *arr);
void abimparr_compact(MpArr *arr);
void abimparr_grow(MpArr *arr, long need);
void abimparr_append(MpArr *arr, long idx, void *val);
void abimparr_insert(MpArr *arr, long idx, void *val);
void *abimparr_get(MpArr *arr, long idx);
void abimparr_is_empty(MpArr *arr, void *val);
void abimparr_is_full(MpArr *arr, void *val);
void abimparr_count(void *val);
INFARRAY_PROTOS(formarr, FormArr, struct abiform *);   /* formarr.c 434e80 */

/* ---- symbols, module tables, forms ----------------------------------- */
/* abi_mp_sym_alloc (0x434435): xmalloc(0x18); symbol of the ABI scratch
   table (g_symtblarr), created by abi_assign_op with type 3 */
typedef struct abisym {
    char *name;                     /* +0x00 strdup */
    long unused;                    /* +0x04 */
    unsigned long lo;               /* +0x08 64-bit value, low word */
    unsigned long hi;               /* +0x0c high word */
    long type;                      /* +0x10 (3 = 64-bit; 4 = owned pointer in lo) */
} ABISYM;

/* abi_mp_sym_build (0x434c8f): element of abi_modules (MpArr) */
typedef struct abimpent {
    char *name;                     /* +0 strdup(sprintf("%#0lx", module)) */
    LONGArr *offs;                  /* +4 strtab offset of each symbol, by index */
} ABIMPENT;

/* form_define (0x43559d): element of g_formarr (FormArr) */
struct abictx;
typedef unsigned long (*ABIPACKFN)(struct abictx *ctx);
typedef struct abiform {
    char *name;                     /* +0 strdup("F#W#[O#]") */
    ABIPACKFN fn;                   /* +4 abi_pack_NN */
} ABIFORM;

/* ---- ABI context (abi_ctx_new 0x435d2d, 0x70 bytes) -----------------
 * One per abi_expr_eval_impl call, referenced through abi_parse_ctx
 * (0x46c378).  Offsets are the original ones. */
typedef struct abictx {
    char *symname;                  /* +0x00 strdup'd name of the last symbol (abi_func_sym); freed */
    unsigned long symval;           /* +0x04 cached abi_func_sym result: (sym+0x0c hi word << 16) | (+0x10) */
    MODULE *mod;                    /* +0x08 module being evaluated (param a) */
    long symidx;                    /* +0x0c cached symbol index (-1) */
    unsigned long val;              /* +0x10 value being packed (read by abi_pack_NN) */
    char fill;                      /* +0x14 0x20 */
    long unk_18;                    /* +0x18 0 */
    short type;                     /* +0x1c -1 */
    MEMSPEC mem;                    /* +0x20..+0x2c mspace, mmap, mcntr, mclass of the last symbol */
    EXPR *result;                   /* +0x30 result expression (index 0xc) */
    long cur_rsecno;                /* +0x34 = cur_rsecno (4612a0) */
    OVLENT *ovltab;                 /* +0x38 = mod_ovltab */
    BUFREF *buftab;                 /* +0x3c = mod_buftab */
    MODSEC **secmap;                /* +0x40 = mod_secmap */
    long ovl_base;                  /* +0x44 = ovl_base (4612d8) */
    SECTION *rsection;              /* +0x48 = cur_rsection */
    MODSEC *rmsec;                  /* +0x4c = cur_rmsec */
    char opt_i;                     /* +0x50 = opt_i (461248) */
    unsigned long *load_ctr;        /* +0x54 = load_ctr (461d94) */
    SECTION *alloc;                 /* +0x58 = cur_alloc (461de4) */
    unsigned long *arg;             /* +0x5c param b: the original stores the flag argument and the
                                       parser dereferences it (tokens 0x13); callers always pass 0 */
    unsigned long *run_ctr;         /* +0x60 = run_ctr (461d90) */
    unsigned long *run_ctr2;        /* +0x64 = run_ctr (461d90), read by tokens 0x14 */
    unsigned long word_mask;        /* +0x68 = word_mask (461f6c) */
    short word_bytes;               /* +0x6c = (short) word_bytes (461f4c); abi_mp_sym_set_type */
} ABICTX;
/* NB: tokens 0x13/0x14/0x15 of the grammar read *ctx+0x5c, *ctx+0x64, *ctx+0x60. */

/* ---- 64-bit / 32-bit values of the parser (ABIVAL) --------------------
 * 16 bytes: the yacc value stack element as handled by abi_lnk_extract_val
 * and abi_lnk_convert_type.  type: 0 = 16-bit, 1 = 32-bit signed, 2 = 32-bit
 * unsigned, 3 = 64-bit; status: 0 unchanged, 1 conversion error, 2 converted. */
typedef struct abival {
    unsigned long lo;               /* +0  low word (32-bit pattern) */
    unsigned long hi;               /* +4  high word */
    long type;                      /* +8  0..3 */
    long status;                    /* +0xc */
} ABIVAL;

/* ---- globals (defined in abiglue.c unless noted) ---------------------- */
extern char *abi_expr_text;         /* 46c070 start of the text being parsed */
extern char *abi_expr_text_end;     /* 46c074 end (NUL) */
extern SymArr *g_symtblarr;         /* 46c06c ABI scratch symbols (abi_assign_op) */
extern FormArr *g_formarr;          /* 46c078 form table (F#W#[O#] names) */
extern ABICTX *abi_parse_ctx;       /* 46c378 current context */
extern char abi_errbuf[516];        /* 46c400 message buffer of abi_func_* */
/* abi_modules (46c604, MpArr *) is defined in lnkglb.c (void *) */

/* lexer/parser entry points (abilex.c / abiparse.c) used by abiglue.c */
extern FILE *yyin;                  /* 46ad18 (abilex.c) */
void yyrestart(FILE *input_file);   /* 4398f9 (abilex.c) */
int yyparse(void);                  /* 43a40d (abiparse.c) */
int yylex(void);                    /* 438b60 (abilex.c) */

/* ---- symtbl.c / mpsym.c ------------------------------------------------ */
ABISYM *abi_mp_sym_alloc(char *name, long v1, long v2, long v3);    /* 434435: lo=v1 hi=v2 type=v3 */
void abi_mp_sym_free_elem(ABISYM *elem);                             /* 4343e0 (symtable freefn) */
ABISYM *symtbl_find_by_name(SymArr *arr, char *name);                /* 43447d, NULL name: message */
ABIMPENT *abi_mp_sym_build(MODULE *mod);                             /* 434c8f */
ABIMPENT *abi_mp_sym_find(MpArr *arr, MODULE *mod);                  /* 434d4d */
char *abi_mp_sym_name(MODULE *mod, MpArr *tab, long idx);            /* 435e58: strdup'd name or NULL */
unsigned long abi_mp_sym_get_mask(ABICTX *ctx, unsigned long m);     /* 438203 */
unsigned long abi_mp_sym_shift_field(ABICTX *ctx, unsigned long v);  /* 43825a: mask_then_shift(v, range(8,15), 8, '>') */
long abi_mp_sym_set_type(ABICTX *ctx, int type);                     /* 43834c: ctx->word_bytes = type; 0 */

/* ---- formtbl.c ---------------------------------------------------------- */
void form_elem_free(ABIFORM *elem);                                  /* 435560 (formtable freefn) */
ABIFORM *form_define(char *name, ABIPACKFN fn);                      /* 43559d */
ABIFORM *form_find_by_name(FormArr *arr, char *name);                /* 4355d6 */
void abi_form_table_init(FormArr *arr);                              /* 436210: adds the 50 F#W#O# forms */
/* abi_pack_01 .. abi_pack_50 (0x436855..0x437427): F1W1 F2W3 F2W2 F2W1 F3W1 F3W2
   F4W1O1 F4W1O2 F4W2O2 F4W3O1 F5W1O1 F5W1O2 F5W2O2 F5W3O1 F6W1O1 F6W1O2 F6W2O2
   F6W3O1 F7W1 F7W2 F8W1 F9W2O2 F9W2O1 F10W1 F10W2 F11W1 F11W2 F11W3 F12W1 F13W1
   F13W2 F14W1 F14W2 F15W1 F16W1O1 F16W1O2 F16W2O1 F17W1O1 F17W1O2 F17W2O1 F18W1O1
   F18W1O2 F18W2O1 F19W1 F19W2 F20W1 F21W1 F22W1 F22W2 F23W1 (in that order) */
unsigned long abi_pack_01(ABICTX *ctx);
unsigned long abi_pack_02(ABICTX *ctx);
unsigned long abi_pack_03(ABICTX *ctx);
unsigned long abi_pack_04(ABICTX *ctx);
unsigned long abi_pack_05(ABICTX *ctx);
unsigned long abi_pack_06(ABICTX *ctx);
unsigned long abi_pack_07(ABICTX *ctx);
unsigned long abi_pack_08(ABICTX *ctx);
unsigned long abi_pack_09(ABICTX *ctx);
unsigned long abi_pack_10(ABICTX *ctx);
unsigned long abi_pack_11(ABICTX *ctx);
unsigned long abi_pack_12(ABICTX *ctx);
unsigned long abi_pack_13(ABICTX *ctx);
unsigned long abi_pack_14(ABICTX *ctx);
unsigned long abi_pack_15(ABICTX *ctx);
unsigned long abi_pack_16(ABICTX *ctx);
unsigned long abi_pack_17(ABICTX *ctx);
unsigned long abi_pack_18(ABICTX *ctx);
unsigned long abi_pack_19(ABICTX *ctx);
unsigned long abi_pack_20(ABICTX *ctx);
unsigned long abi_pack_21(ABICTX *ctx);
unsigned long abi_pack_22(ABICTX *ctx);
unsigned long abi_pack_23(ABICTX *ctx);
unsigned long abi_pack_24(ABICTX *ctx);
unsigned long abi_pack_25(ABICTX *ctx);
unsigned long abi_pack_26(ABICTX *ctx);
unsigned long abi_pack_27(ABICTX *ctx);
unsigned long abi_pack_28(ABICTX *ctx);
unsigned long abi_pack_29(ABICTX *ctx);
unsigned long abi_pack_30(ABICTX *ctx);
unsigned long abi_pack_31(ABICTX *ctx);
unsigned long abi_pack_32(ABICTX *ctx);
unsigned long abi_pack_33(ABICTX *ctx);
unsigned long abi_pack_34(ABICTX *ctx);
unsigned long abi_pack_35(ABICTX *ctx);
unsigned long abi_pack_36(ABICTX *ctx);
unsigned long abi_pack_37(ABICTX *ctx);
unsigned long abi_pack_38(ABICTX *ctx);
unsigned long abi_pack_39(ABICTX *ctx);
unsigned long abi_pack_40(ABICTX *ctx);
unsigned long abi_pack_41(ABICTX *ctx);
unsigned long abi_pack_42(ABICTX *ctx);
unsigned long abi_pack_43(ABICTX *ctx);
unsigned long abi_pack_44(ABICTX *ctx);
unsigned long abi_pack_45(ABICTX *ctx);
unsigned long abi_pack_46(ABICTX *ctx);
unsigned long abi_pack_47(ABICTX *ctx);
unsigned long abi_pack_48(ABICTX *ctx);
unsigned long abi_pack_49(ABICTX *ctx);
unsigned long abi_pack_50(ABICTX *ctx);

/* ---- abiops.c: the operator library.  All arguments/results are 32-bit
 * patterns in unsigned long.  The names of l4_util.names.txt for these
 * addresses (op_uplus, op_shl, ...) are wrong and clash with the linker's
 * own EXPR operators (op_add ... in dsplnk.h), so the port names them
 * abi_op_<meaning>; the table gives address, l4_util name, meaning. -------- */
unsigned long abi_op_add(unsigned long a, unsigned long b);   /* 4356a0 op_uplus  a + b */
unsigned long abi_op_sub(unsigned long a, unsigned long b);   /* 4356ab op_uminus a - b */
unsigned long abi_op_mul(unsigned long a, unsigned long b);   /* 4356b6 op_bitnot a * b */
unsigned long abi_op_div(unsigned long a, unsigned long b);   /* 4356c2 op_div    signed a / b; b==0: 0 */
unsigned long abi_op_mod(unsigned long a, unsigned long b);   /* 4356e5 op_mod    signed a % b; b==0: 0 */
ABI64 abi_op_add64(unsigned long a_lo, unsigned long a_hi, unsigned long b_lo, unsigned long b_hi); /* 43570a */
ABI64 abi_op_sub64(unsigned long a_lo, unsigned long a_hi, unsigned long b_lo, unsigned long b_hi); /* 43571b */
ABI64 abi_op_mul64(unsigned long a_lo, unsigned long a_hi, unsigned long b_lo, unsigned long b_hi); /* 43572c */
ABI64 abi_op_div64(unsigned long a_lo, unsigned long a_hi, unsigned long b_lo, unsigned long b_hi); /* 435746 signed; b==0: 0 */
ABI64 abi_op_mod64(unsigned long a_lo, unsigned long a_hi, unsigned long b_lo, unsigned long b_hi); /* 43577d signed; b==0: 0 */
unsigned long abi_op_shr(unsigned long a, unsigned long n);   /* 4357b4 op_shl    a >> (n & 31), logical */
unsigned long abi_op_shl(unsigned long a, unsigned long n);   /* 4357c1 op_shr    a << (n & 31) */
unsigned long abi_op_compl(unsigned long a);                  /* 4357ce op_neg    ~a */
unsigned long abi_op_neg(unsigned long a);                    /* 4357d8 op_compl  -a */
unsigned long abi_op_lnot(unsigned long a);                   /* 4357e2 op_not    a == 0 */
unsigned long abi_op_land(unsigned long a, unsigned long b);  /* 4357f0 op_and    a && b */
unsigned long abi_op_lor(unsigned long a, unsigned long b);   /* 435817 op_or     a || b */
unsigned long abi_op_gt(unsigned long a, unsigned long b);    /* 43583e op_eq     signed a >  b */
unsigned long abi_op_ge(unsigned long a, unsigned long b);    /* 435850 op_ne     signed a >= b */
unsigned long abi_op_lt(unsigned long a, unsigned long b);    /* 435862 op_lt     signed a <  b */
unsigned long abi_op_le(unsigned long a, unsigned long b);    /* 435874 op_le     signed a <= b */
unsigned long abi_op_eq(unsigned long a, unsigned long b);    /* 435886 op_gt     a == b */
unsigned long abi_op_ne(unsigned long a, unsigned long b);    /* 435898 op_ge     a != b */
unsigned long abi_op_and(unsigned long a, unsigned long b);   /* 4358aa op_uadd   a & b */
unsigned long abi_op_or(unsigned long a, unsigned long b);    /* 4358b5 op_usub   a | b */
unsigned long abi_op_xor(unsigned long a, unsigned long b);   /* 4358c0 op_uxor   a ^ b */
unsigned long abi_op_cond(unsigned long cond, unsigned long a, unsigned long b); /* 4358cb op_cond cond ? a : b */
/* abi_assign_op: op is '=' (0x3d), 0x101 (+=), 0x102 (-=), 0x103 (*=),
   0x104 (/=), 0x105 (%=); creates the symbol (type 3) when missing;
   any other op: "Not A Recognized Assign Operator!" to stderr, exit(1) */
ABI64 abi_assign_op(SymArr *tab, char *name, int op, unsigned long v_lo, unsigned long v_hi); /* 4358ea */
void abi_expr_error_stub(char *msg);                        /* 43a408 no-op ("Divide by Zero\n") */

/* ---- abiutil.c ---------------------------------------------------------- */
char *abi_strdup(const char *s);                                     /* _strdup (449310) on malloc */
void abi_assert_fail(char *expr, char *file, int line);              /* _assert (43ec00) + abort */
void abi_ctx_free(ABICTX *ctx);                                     /* 435d00 */
ABICTX *abi_ctx_new(MODULE *mod, long flag);                        /* 435d2d */
unsigned long abi_mask_then_shift(unsigned long v, unsigned long mask, int pos, int dir); /* 435f5a: dir '<' or '>' */
unsigned long abi_bit_range_mask(int lo, int hi);                   /* 435f9f: mask of bits lo..hi, 0 if lo or hi < 0 (16-bit args) */
unsigned long abi_pack_dispatch(unsigned long v, int form);         /* 436012: arithmetic v >> form (shift in copies of bit 31) */
void abi_report_error(char *msg, char *loc, ABICTX *last);          /* 436090: lnk_error1(" %s at Location %s[; last ...]") */

/* ---- abiform.c ---------------------------------------------------------- */
/* abi_map_lookup 437950: address of a section-map expression; see abiform.c */
long abi_map_lookup(ABICTX *ctx, long a2, long a3, long a4, long a5, long a6, long a7, long a8, long a9);

/* ---- abifunc.c ---------------------------------------------------------- */
long abi_func_sym(ABICTX *ctx, MpArr *tab, long idx);               /* 437e46 */
unsigned long abi_func_pack(unsigned long v, int form, int pos, int width); /* 437fc0: form 'n' none, 's'/'u' checked */
unsigned long abi_func_check(unsigned long v, int sign, int lo, int hi);    /* 438042: low 16 bits nonzero = error */
long abi_func_memcheck(ABICTX *ctx, long unused, long idx, int space);      /* 4382c9 */
long set_cur_opt_char(long c);                                      /* 43833c: cur_opt_char = c */

/* ---- abiconv.c ---------------------------------------------------------- */
ABIVAL *abi_lnk_extract_val(ABIVAL *dst, ABIVAL *val, long type);   /* 4385f0 (type 1 or 2 accepted) */
ABIVAL *abi_lnk_convert_type(ABIVAL *dst, ABIVAL *val, long totype);/* 438679 */
ABIVAL *abi_conv_case1(ABIVAL *dst, ABIVAL *val);                   /* 4387f2 to type 0 */
ABIVAL *abi_conv_case2(ABIVAL *dst, ABIVAL *val);                   /* 438889 to type 2 */
ABIVAL *abi_conv_case3(ABIVAL *dst, ABIVAL *val);                   /* 43891b to type 1 */
ABIVAL *abi_conv_case4(ABIVAL *dst, ABIVAL *val);                   /* 4389ab to type 3 */

/* ---- glue (abiglue.c) -------------------------------------------------- */
/* abi_expr_eval, abi_expr_eval_impl, abi_free_all, abimparr_create,
   abi_mp_sym_free_with_arr and abi_mp_symtbl_dispatch keep the prototypes
   of dsplnk.h. */

#endif /* ABI_H */
