/*
 * ASM56000 assembler, error.c (CLAS56 v6.3.0).
 *
 * This is the first portable reconstruction of the assembler proper.  The
 * address comments in the original Ghidra export put the bit-field helpers in
 * error.c, although they are really part of the instruction encoder.  They
 * are kept here because that is where the executable's entry points live.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asm56000.h"

#ifndef __cdecl
# define __cdecl
#endif

/* State owned by asmglb/dspasm/input/listing in the eventual full port. */
extern char *CurFileName;             /* 0044f80c */
extern FILE *ErrFilePtr;              /* 0044f9a4 */
extern char *ObjFileName;             /* 0045f854 */
extern FILE *LstFilePtr;              /* 0045fcac */
extern char LineBuf[512];             /* 0045f220 */
extern char *CurInstrFieldMsg;        /* 0045f860 */
extern void *DoStack;                 /* 0045fc30 */
extern char *FieldNames[];             /* 0044f960 */

extern unsigned long LineTotal;       /* 0045eb78 */
extern unsigned long LineNo;          /* 0045eb80 */
extern unsigned long ErrorCount;      /* 0045eb84 */
extern unsigned long WarningCount;    /* 0045eb88 */
extern unsigned long ErrOnThisLine;   /* 0045eb98 */
extern int ErrMultiple;               /* 1 = original semantics (no per-line suppression) */
extern unsigned long SuppressedErrors;/* 0045eb9c */
extern unsigned long Pass;            /* 0045f8fc */

extern char NoErrors;                 /* 0045ea50 */
extern char InLineReplay;             /* 0045ea70 */
extern char AbsModeShadow;            /* 0045ea9c */
extern char ListingOpen;              /* 0045eb04 */
extern char OptWarn;                  /* 0044f788 */

/* The helper routines are reconstructed in eval/listing/encode/util.c. */
extern int which_field(char *pos);
extern void wrap_message(int indent, char *msg);
extern void lst_putstr(char *s);
extern void lst_newline(void);

int __cdecl y_code(int reg);
int __cdecl lll_code(int reg);
int __cdecl qq_code(int reg);
void __cdecl fatal(char *msg);

static unsigned long word_at(void *p, unsigned offset)
{
    return *(unsigned long *)((char *)p + offset);
}

static void put_word(void *p, unsigned offset, unsigned long value)
{
    *(unsigned long *)((char *)p + offset) = value;
}

static long long_at(void *p, unsigned offset)
{
    return (long)word_at(p, offset);
}

static FILE *diagnostic_stream(void)
{
    /* ErrFilePtr is initialized by dspasm.c.  The fallback makes the module
       useful in a small unit harness before the command-line driver exists. */
    if (ErrFilePtr != (FILE *)0)
        return ErrFilePtr;
    return stdout;
}

static void append_location_suffix(void)
{
    int field;
    unsigned long pc;

    if (CurInstrFieldMsg == (char *)0)
        return;
    field = which_field(CurInstrFieldMsg);
    if (field == 0)
        return;
    if (InLineReplay && DoStack != (void *)0) {
        pc = word_at(DoStack, 8);
        sprintf(LineBuf + strlen(LineBuf),
                " (See instruction at P:%0*lX)", 4, pc);
    } else {
        sprintf(LineBuf + strlen(LineBuf), " (%s field)",
                FieldNames[field]);
    }
}

static void write_diagnostic(unsigned long prefix_len)
{
    fprintf(diagnostic_stream(), "%s\n", LineBuf);
    if (ListingOpen && LstFilePtr != diagnostic_stream()) {
        listing_prepare_diagnostic();
        wrap_message((int)prefix_len, LineBuf);
    }
}

/* 004127e6: set the parallel-move bit and encode a Y-register/Y-memory pair. */
void __cdecl enc_pm_ry_w(void *insn, void *s1, void *d1, void *ymem,
                         void *yreg)
{
    put_word(insn, 4, insert_bits(word_at(insn, 4), 1, 15, 1));
    enc_pm_ry(insn, s1, d1, yreg, ymem);
}

/* 00412822 */
void __cdecl enc_pm_xr(void *insn, void *xreg, void *xmem, void *s2,
                       void *d2)
{
    unsigned long word;


    word = word_at(insn, 4);
    word = insert_bits(word, (unsigned long)rrr_code((int)word_at(xmem, 0),
                                                       (int)word_at(xmem, 20)),
                       8, 3);
    word = insert_bits(word, (unsigned long)mmm_code((int)word_at(xmem, 0)),
                       11, 3);
    word = insert_bits(word, (unsigned long)y_code((int)word_at(d2, 20)),
                       16, 1);
    word = insert_bits(word, (unsigned long)d_code((int)word_at(s2, 20)),
                       17, 1);
    word = insert_bits(word, (unsigned long)xx_code((int)long_at(xreg, 20)),
                       18, 2);
    word = insert_bits(word, 1, 20, 1);
    put_word(insn, 4, word);
    set_ext_word(insn, xmem, 0);
}

/* 0041290b */
int __cdecl y_code(int reg)
{
    if (reg == 5)
        return 0;
    if (reg == 7)
        return 1;
    fatal("Y encoding failure");
    return 0;
}

/* 00412941 */
void __cdecl enc_pm_xr_w(void *insn, void *xmem, void *xreg, void *s2,
                         void *d2)
{
    put_word(insn, 4, insert_bits(word_at(insn, 4), 1, 15, 1));
    enc_pm_xr(insn, xreg, xmem, s2, d2);
}

/* 0041297d */
void __cdecl enc_pm_l_abs(void *insn, void *reg, void *abs)
{
    unsigned long word;

    word = insert_bits(word_at(insn, 4),
                       (unsigned long)lll_code((int)word_at(reg, 20)),
                       16, 4);
    word = insert_bits(word, 1, 22, 1);
    put_word(insn, 4, word);
    encode_field(insn, abs, 8, 6);
}

/* 004129d7 */
int __cdecl lll_code(int reg)
{
    switch (reg) {
    case 0: return 2;
    case 1: return 3;
    case 2: return 8;
    case 3: return 9;
    case 0x26: return 10;
    case 0x27: return 11;
    case 0x28: return 0;
    case 0x29: return 1;
    default:
        fatal("LLL encoding failure");
        return 0;
    }
}

/* 00412a8f */
void __cdecl enc_pm_l_abs_w(void *insn, void *abs, void *reg)
{
    put_word(insn, 4, insert_bits(word_at(insn, 4), 1, 15, 1));
    enc_pm_l_abs(insn, reg, abs);
}

/* 00412ac3 */
void __cdecl enc_pm_l_ea(void *insn, void *reg, void *mem)
{
    unsigned long word;

    word = word_at(insn, 4);
    word = insert_bits(word, (unsigned long)rrr_code((int)word_at(mem, 0),
                                                       (int)word_at(mem, 20)),
                       8, 3);
    word = insert_bits(word, (unsigned long)mmm_code((int)word_at(mem, 0)),
                       11, 3);
    word = insert_bits(word, 1, 14, 1);
    word = insert_bits(word, (unsigned long)lll_code((int)word_at(reg, 20)),
                       16, 4);
    word = insert_bits(word, 1, 22, 1);
    put_word(insn, 4, word);
    set_ext_word(insn, mem, 0);
}

/* 00412b7b */
void __cdecl enc_pm_l_ea_w(void *insn, void *mem, void *reg)
{
    put_word(insn, 4, insert_bits(word_at(insn, 4), 1, 15, 1));
    enc_pm_l_ea(insn, reg, mem);
}

/* 00412baf */
void __cdecl enc_pm_imm(void *insn, void *imm, void *dst)
{
    unsigned long word;

    word = insert_bits(word_at(insn, 4),
                       (unsigned long)ddddd_code((int)word_at(dst, 20)),
                       16, 5);
    word = insert_bits(word, 1, 21, 1);
    put_word(insn, 4, word);
    encode_field(insn, imm, 8, 8);
}

/* 00412c09 */
void __cdecl enc_pm_reg(void *insn, void *src, void *dst)
{
    unsigned long word;

    word = insert_bits(word_at(insn, 4),
                       (unsigned long)ddddd_code((int)word_at(dst, 20)),
                       8, 5);
    word = insert_bits(word,
                       (unsigned long)ddddd_code((int)word_at(src, 20)),
                       13, 5);
    word = insert_bits(word, 1, 21, 1);
    put_word(insn, 4, word);
}

/* 00412c72 */
void __cdecl enc_pm_update(void *insn, void *op)
{
    unsigned long word;

    word = word_at(insn, 4);
    word = insert_bits(word, (unsigned long)rrr_code((int)word_at(op, 0),
                                                       (int)word_at(op, 20)),
                       8, 3);
    word = insert_bits(word, (unsigned long)mmm_code((int)word_at(op, 0)),
                       11, 2);
    word = insert_bits(word, 0x81, 14, 8);
    put_word(insn, 4, word);
}

/* 00412ce3 */
void __cdecl enc_movem_ea(void *insn, void *reg, void *mem)
{
    unsigned long word;

    word = insert_bits(word_at(insn, 4) | 0x70000UL,
                       (unsigned long)d6_code((int)word_at(reg, 20)), 0, 6);
    word = insert_bits(word, 1, 7, 1);
    word = insert_bits(word, (unsigned long)rrr_code((int)word_at(mem, 0),
                                                       (int)word_at(mem, 20)),
                       8, 3);
    word = insert_bits(word, (unsigned long)mmm_code((int)word_at(mem, 0)),
                       11, 3);
    word = insert_bits(word, 1, 14, 1);
    put_word(insn, 4, word);
    set_ext_word(insn, mem, 0);
}

/* 00412da0 */
void __cdecl enc_movem_ea_w(void *insn, void *mem, void *reg)
{
    put_word(insn, 4, insert_bits(word_at(insn, 4), 1, 15, 1));
    enc_movem_ea(insn, reg, mem);
}

/* 00412dd4 */
void __cdecl enc_movem_abs(void *insn, void *reg, void *abs)
{
    unsigned long word;

    word = insert_bits(word_at(insn, 4) | 0x70000UL,
                       (unsigned long)d6_code((int)word_at(reg, 20)), 0, 6);
    put_word(insn, 4, word);
    if (word_at(abs, 0) == 14UL &&
        (word_at(abs, 0x10) >= 0x40UL ||
         word_at(abs, ASM56000_OP_FORCE) == 0x1000000UL)) {
        word = insert_bits(word_at(insn, 4), 0x70UL, 8, 7);
        word = insert_bits(word, 1UL, 7, 1);
        put_word(insn, 4, word);
        set_ext_word(insn, abs, 0);
    } else {
        encode_field(insn, abs, 8, 6);
    }
}

/* 00412e1b */
void __cdecl enc_movem_abs_w(void *insn, void *abs, void *reg)
{
    put_word(insn, 4, insert_bits(word_at(insn, 4), 1, 15, 1));
    enc_movem_abs(insn, reg, abs);
}

/* 00412e4f */
void __cdecl enc_lua(void *insn, void *mem, void *dst)
{
    unsigned long word;

    word = insert_bits(word_at(insn, 4),
                       (unsigned long)ddddd_code((int)word_at(dst, 20)),
                       0, 4);
    word = insert_bits(word, (unsigned long)rrr_code((int)word_at(mem, 0),
                                                       (int)word_at(mem, 20)),
                       8, 3);
    word = insert_bits(word, (unsigned long)mmm_code((int)word_at(mem, 0)),
                       11, 2);
    put_word(insn, 4, word);
}

/* 00412ecb */
void __cdecl enc_mul_imm(void *insn, void *s1, void *imm, void *dst)
{
    unsigned long word;

    word = insert_bits(word_at(insn, 4),
                       (unsigned long)d_code((int)word_at(dst, 20)), 3, 1);
    word = insert_bits(word, (unsigned long)qq_code((int)word_at(s1, 20)),
                       4, 2);
    put_word(insn, 4, word);
    encode_field(insn, imm, 8, 5);
}

/* 00412f33 */
int __cdecl qq_code(int reg)
{
    switch (reg) {
    case 4: return 1;
    case 5: return 2;
    case 6: return 3;
    case 7: return 0;
    default:
        fatal("QQ encoding failure");
        return 0;
    }
}

/* 00412fa0 */
void __cdecl fatal(char *msg)
{
    unsigned long prefix_len;


    sprintf(LineBuf, "**** %ld [%s %ld]: FATAL --- ",
            (long)LineNo, CurFileName, (long)LineTotal);
    prefix_len = (unsigned long)strlen(LineBuf);
    strcpy(LineBuf + prefix_len, msg);
    fprintf(diagnostic_stream(), "%s\n", LineBuf);
    if (ListingOpen && LstFilePtr != diagnostic_stream())
        wrap_message(0, LineBuf);
    if (ObjFileName != (char *)0)
        remove(ObjFileName);
    exit(-1);
}

/* 00413085 */
void __cdecl err(char *msg)
{
    unsigned long prefix_len;

    if (NoErrors) {
        SuppressedErrors++;
        return;
    }
    if (Pass != 2)
        return;
    if (!ErrMultiple && ErrOnThisLine != 0UL)
        return;
    sprintf(LineBuf, "**** %ld [%s %ld]: ERROR --- ",
            (long)LineNo, CurFileName, (long)LineTotal);
    prefix_len = (unsigned long)strlen(LineBuf);
    strcpy(LineBuf + prefix_len, msg);
    append_location_suffix();
    write_diagnostic(prefix_len);
    ErrorCount++;
    ErrOnThisLine++;
}

/* 004131f9 */
void __cdecl err_s(char *msg, char *arg)
{
    unsigned long prefix_len;
    unsigned long end;

    if (NoErrors) {
        SuppressedErrors++;
        return;
    }
    if (Pass != 2)
        return;
    if (!ErrMultiple && ErrOnThisLine != 0UL)
        return;
    sprintf(LineBuf, "**** %ld [%s %ld]: ERROR --- ",
            (long)LineNo, CurFileName, (long)LineTotal);
    prefix_len = (unsigned long)strlen(LineBuf);
    strcpy(LineBuf + prefix_len, msg);
    strcat(LineBuf, ": ");
    end = (unsigned long)strlen(LineBuf);
    strncat(LineBuf + end, arg, 0x100);
    append_location_suffix();
    write_diagnostic(prefix_len);
    ErrorCount++;
    ErrOnThisLine++;
}

/* 004133a9 */
void __cdecl warn(char *msg)
{
    unsigned long prefix_len;

    if (NoErrors || Pass != 2 || !OptWarn)
        return;
    if (!ErrMultiple && ErrOnThisLine != 0UL)
        return;
    sprintf(LineBuf, "**** %ld [%s %ld]: WARNING --- ",
            (long)LineNo, CurFileName, (long)LineTotal);
    prefix_len = (unsigned long)strlen(LineBuf);
    strcpy(LineBuf + prefix_len, msg);
    append_location_suffix();
    write_diagnostic(prefix_len);
    WarningCount++;
    ErrOnThisLine++;
}

/* 0041351d */
void __cdecl warn_s(char *msg, char *arg)
{
    unsigned long prefix_len;
    unsigned long end;

    if (NoErrors || Pass != 2 || !OptWarn)
        return;
    if (!ErrMultiple && ErrOnThisLine != 0UL)
        return;
    sprintf(LineBuf, "**** %ld [%s %ld]: WARNING --- ",
            (long)LineNo, CurFileName, (long)LineTotal);
    prefix_len = (unsigned long)strlen(LineBuf);
    strcpy(LineBuf + prefix_len, msg);
    strcat(LineBuf, ": ");
    end = (unsigned long)strlen(LineBuf);
    strncat(LineBuf + end, arg, 0x100);
    append_location_suffix();
    write_diagnostic(prefix_len);
    WarningCount++;
    ErrOnThisLine++;
}
