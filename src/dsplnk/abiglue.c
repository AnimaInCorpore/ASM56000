/*
 * abiglue.c - DSPLNK.EXE (CLAS56 v6.3, DSP Linker 6.3.7), ABI expression
 * subsystem: entry points and shared state (0x43a260-0x43a40c).
 *
 * abi_expr_eval_impl re-initialises the lexer on the relocation text, sets up
 * (first call) or clears the ABI scratch symbol table, runs the parser with a
 * fresh context and returns the resulting expression, or NULL when the text
 * is not an ABI expression (the callers then fall back to eval_expr).
 */
#include "abi.h"

char *abi_expr_text;                    /* 46c070 */
char *abi_expr_text_end;                /* 46c074 */
SymArr *g_symtblarr;                    /* 46c06c */
FormArr *g_formarr;                     /* 46c078 */
ABICTX *abi_parse_ctx;                  /* 46c378 */
char abi_errbuf[516];                   /* 46c400 */

static int abi_inited;                  /* 46ad2c */

/* 43a260 */
EXPR *abi_expr_eval(MODULE *mod, long flag, char *text)
{
    return abi_expr_eval_impl(mod, flag, text);
}

/* 43a289 */
EXPR *abi_expr_eval_impl(MODULE *mod, long flag, char *text)
{
    EXPR *r;

    abi_expr_text = text;
    abi_expr_text_end = abi_expr_text + strlen(text);
    yyrestart(yyin);
    if (!abi_inited) {
        g_symtblarr = symtblarr_create(0x14L, 0x14L, abi_mp_sym_free_elem);
        g_formarr = formarr_create(0x14L, 0x14L, form_elem_free);
        abi_form_table_init(g_formarr);
        abi_inited = 1;
    } else {
        (*g_symtblarr->compact)(g_symtblarr);
    }
    abi_parse_ctx = abi_ctx_new(mod, flag);
    if (yyparse() != 0) {
        abi_ctx_free(abi_parse_ctx);
        return NULL;
    }
    /* the original also bumps expr_sp by one slot here (a stale entry, never
       read); the port keeps the expression stack balanced instead */
    r = abi_parse_ctx->result;
    abi_ctx_free(abi_parse_ctx);
    return r;
}

/* 43a394 */
void abi_free_all(void)
{
    symtblarr_destroy(g_symtblarr);
    g_symtblarr = NULL;
    formarr_destroy(g_formarr);
    g_formarr = NULL;
    abimparr_destroy((MpArr *)abi_modules);
    abi_modules = NULL;
}

/* 43a3e3 */
void abi_mp_symtbl_dispatch(void *arr, MODULE *mod)
{
    MpArr *a = (MpArr *)arr;

    if (a != NULL)
        (*a->add)(a, abi_mp_sym_build(mod));
}
