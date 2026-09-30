/*
 * abifunc.c - DSPLNK.EXE (CLAS56 v6.3, DSP Linker 6.3.7), ABI expression
 * subsystem: the built-in functions of the grammar (0x437e46-0x438201,
 * 0x4382c9-0x43833b).
 */
#include "abi.h"

/* 437e46: value of the symbol with table index idx of the current module:
   (high word << 16) | low word of its linker symbol; also remembers the
   symbol's memory space in ctx->mem.  0 when the symbol is unknown. */
long abi_func_sym(ABICTX *ctx, MpArr *tab, long idx)
{
    char *name;
    SYM *sym;

    if (idx == ctx->symidx)
        return (long)ctx->symval;
    name = abi_mp_sym_name(ctx->mod, tab, idx);
    if (name == NULL) {
        if (pass > 1) {
            abi_errbuf[0] = '\0';
            sprintf(abi_errbuf, "A Symbol is Not Found at Given Symbol Index=%ld", idx);
            abi_report_error(abi_errbuf, "abi_func_sym()", NULL);
        }
        ctx->symval = 0;
        ctx->symidx = idx;
        return 0;
    }
    sym = sym_lookup(name, 0);
    if (sym == NULL) {
        ctx->symval = 0;
        ctx->symidx = idx;
        free(name);
        return 0;
    }
    sym_found = sym;
    ctx->mem = sym->mem;
    if (ctx->symname != NULL)
        free(ctx->symname);
    ctx->symname = name;
    ctx->symval = 0;
    ctx->symval |= sym->hi;
    ctx->symval = (ctx->symval << 16) & 0xffffffffUL;
    ctx->symval |= sym->lo;
    ctx->symval &= 0xffffffffUL;
    ctx->symidx = idx;
    return (long)ctx->symval;
}

/* 437fc0 */
unsigned long abi_func_pack(unsigned long v, int form, int pos, int width)
{
    if ((char)form == 'n')
        return abi_bit_range_mask(0, (short)pos - 1) & v;
    if ((short)abi_func_check(v, form, pos, width) == 0)
        return abi_pack_dispatch(v, width);
    abi_report_error("Unable to Pack Value", "abi_func_pack", abi_parse_ctx);
    return 0;
}

/* 438042: 0 when v is `width'-bit aligned and fits `pos' bits with the given
   sign letter ('s' or 'u'), else 1 after reporting the error */
unsigned long abi_func_check(unsigned long v, int sign, int pos, int width)
{
    unsigned long m, t;

    v &= 0xffffffffUL;
    m = abi_bit_range_mask(0, (short)width - 1);
    if ((m & v) != 0) {
        abi_errbuf[0] = '\0';
        sprintf(abi_errbuf, "Value=%#0lx Must be %dbit-aligned", v, (int)(short)width);
        abi_report_error(abi_errbuf, "abi_func_check", abi_parse_ctx);
        return 1;
    }
    t = abi_pack_dispatch(v, width);
    m = abi_bit_range_mask(0, (int)((short)pos - 1));
    m = ~m & 0xffffffffUL;
    t = t & m;
    if ((char)sign == 's') {
        if (t != 0 && t != m) {
            abi_errbuf[0] = '\0';
            sprintf(abi_errbuf, "Signed Value=%#0lx is Out of Range", v);
            abi_report_error(abi_errbuf, "abi_func_check", abi_parse_ctx);
            return 1;
        }
    } else if ((char)sign == 'u') {
        if (t != 0) {
            abi_errbuf[0] = '\0';
            sprintf(abi_errbuf, "Unsigned Value=%#0lx is Out of Range", v);
            abi_report_error(abi_errbuf, "abi_func_check", abi_parse_ctx);
            return 1;
        }
    } else {
        abi_errbuf[0] = '\0';
        sprintf(abi_errbuf, "No Sign Specified (s/u) for Checking Value=%#0lx", v);
        abi_report_error(abi_errbuf, "abi_func_check", abi_parse_ctx);
        abi_report_error("No Sign specified", "abi_func_check", abi_parse_ctx);
        return 1;
    }
    return 0;
}

/* 4382c9: memory constraint check of the symbol idx against space `space' */
long abi_func_memcheck(ABICTX *ctx, long unused, long idx, int space)
{
    long sp;

    (void)unused;
    abi_func_sym(ctx, (MpArr *)abi_modules, idx);
    sp = index_mem_space((short)space);
    if (opt_aec != '\0' && merge_mem_space(ctx->mem.mspace, sp) == 0xa2c2aL) {
        abi_report_error("Memory Constraint Violation!", "abi_func_memcheck", ctx);
        return 1;
    }
    return 0;
}

/* 43833c: stores its argument in the global at 0x461314 (src_line) */
long set_cur_opt_char(long c)
{
    src_line = c;
    return c;
}
