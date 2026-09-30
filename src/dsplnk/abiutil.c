/*
 * abiutil.c - DSPLNK.EXE (CLAS56 v6.3, DSP Linker 6.3.7), ABI expression
 * subsystem: context, bit-field helpers, error reporting
 * (0x435d00-0x436107).
 */
#include "abi.h"

/* _strdup on the C library malloc (0x449310) */
char *abi_strdup(const char *s)
{
    char *p;

    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* the failed assert() of the original (_assert 0x43ec00, then abort) */
void abi_assert_fail(char *expr, char *file, int line)
{
    fprintf(stderr, "Assertion failed: %s, file %s, line %d\n", expr, file, line);
    fflush(stderr);
    abort();
}

/* 435d00 */
void abi_ctx_free(ABICTX *ctx)
{
    if (ctx->symname != NULL)
        free(ctx->symname);
    if (ctx != NULL)
        free(ctx);
}

/* 435d2d: snapshot of the linker state the ABI functions need.  `flag' is
   stored in +0x5c, where the parser reads it as a pointer (tokens 0x13); the
   callers always pass 0, which the port keeps as a null pointer. */
ABICTX *abi_ctx_new(MODULE *mod, long flag)
{
    ABICTX *c;

    (void)flag;
    c = (ABICTX *)malloc(sizeof(ABICTX));
    memset(c, 0, sizeof(ABICTX));       /* the original leaves +0x24..+0x2c undefined */
    c->symname = NULL;
    c->symval = 0;
    c->mod = mod;
    c->symidx = -1L;
    c->val = 0;
    c->fill = 0x20;
    c->unk_18 = 0;
    c->type = -1;
    c->mem.mspace = 4L;
    c->cur_rsecno = cur_rsecno;
    c->ovltab = mod_ovltab;
    c->buftab = mod_buftab;
    c->secmap = mod_secmap;
    c->ovl_base = ovl_base;
    c->rsection = cur_rsection;
    c->rmsec = cur_rmsec;
    c->opt_i = opt_i;
    c->load_ctr = load_ctr;
    c->alloc = cur_alloc;
    c->arg = NULL;
    c->run_ctr = run_ctr;
    c->result = NULL;
    c->run_ctr2 = run_ctr;
    c->word_mask = word_mask;
    c->word_bytes = (short)word_bytes;
    return c;
}

/* 435f5a */
unsigned long abi_mask_then_shift(unsigned long v, unsigned long mask, int pos, int dir)
{
    v &= mask & 0xffffffffUL;
    if ((char)dir == '>')
        return (v & 0xffffffffUL) >> (pos & 0x1f);
    if ((char)dir == '<')
        return (v << (pos & 0x1f)) & 0xffffffffUL;
    fprintf(stderr, "abi_mask_then_shift   shift_direction   error\n");
    return 0;
}

/* 435f9f: bits lo..hi set (lo, hi are 16-bit in the original) */
unsigned long abi_bit_range_mask(int lo, int hi)
{
    unsigned long m;
    long i;
    long l = (short)lo;
    long h = (short)hi;

    m = 0;
    if (l < 0 || h < 0)
        return 0;
    for (i = 0; i <= h - l; i++)
        m = ((m << 1) | 1UL) & 0xffffffffUL;
    return (m << (l & 0x1f)) & 0xffffffffUL;
}

/* 436012: v >> form with the vacated bits filled from bit 31 */
unsigned long abi_pack_dispatch(unsigned long v, int form)
{
    unsigned long r;
    long f = (short)form;

    v &= 0xffffffffUL;
    if ((v & abi_bit_range_mask(0x1f, 0x1f)) != 0) {
        r = abi_bit_range_mask((int)(0x20 - f), 0x1f);
        r = (v >> (f & 0x1f)) | r;
    } else {
        r = v >> (f & 0x1f);
    }
    return r & 0xffffffffUL;
}

/* 436090 */
void abi_report_error(char *msg, char *loc, ABICTX *last)
{
    char buf[516];

    buf[0] = '\0';
    if (last == NULL)
        sprintf(buf, " %s at Location %s", msg, loc);
    else
        sprintf(buf, " %s at Location %s; last referenced symbol=%s, val=%#0lx, index=%ld",
                msg, loc, last->symname != NULL ? last->symname : "(null)",
                (unsigned long)last->symval, (long)ABI_S32(last->symidx));
    lnk_error1(buf);
}
