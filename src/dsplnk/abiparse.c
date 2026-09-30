/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), abiparse.c
 * The yacc generated parser of the ABI expression language
 * (original yyparse 0043a40d-0043bc4e, AT&T yacc skeleton with the parser
 * state kept in globals; the tables are generated from the EXE into
 * abipartb.h by re/scripts/gentab_abi.py) and its semantic actions.
 *
 * The value stack holds 16 byte entries {value, high word, type, status}
 * (YYSTYPE, same layout as ABIVAL).  Rule number N of the tables is
 * "case N" of the action switch (Ghidra's case labels are the rule numbers).
 * yyerror (0043a408) is a no-op in the original: "syntax error" and
 * "yacc stack overflow" are never printed.
 *
 * Rule map (lhs numbers from yyr1; token numbers from abilex.c):
 *   1      list  : list ',' item             ($$ = last value)
 *   2      item  : expr           builds the result EXPR (ctx->result)
 *   3..18  primary constants (numbers, characters), type tag 1 = int, 2 = uint
 *   19..21 the values *ctx->arg, *ctx->run_ctr2, *ctx->run_ctr
 *   22,23  + -      24..29 assignments (=, +=, -=, *= ...)   30..32 & | ^
 *   33,34  mid-rule actions of  cond ? a : b  (skip flag), 35 the conditional
 *   36..39 == != && ||   40..42 * / %   43 '(' expr ')'   44..47 <= >= > <
 *   48,49  >> <<    50 !    51 ~    52 unary -
 *   53     F#W#O# form call  name(val,c,x,y)  (abi_pack_NN through g_formarr)
 *   63..66 check(...)/pack(...)   69 sym()   70 set type   71,72 set option char
 *   73,74  shift/mask fields   75 memcheck()   76 map lookup with 8 arguments
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abi.h"
#include "abiyy.h"
#include "abipartb.h"

#define YM32 0xffffffffUL

int abi_lex_inited;                 /* 46ad2c: first call of abi_expr_eval_impl done */

static int abi_skip;                /* 46ad28: evaluate nothing (untaken ?: branch) */
static int abi_cond_state = 2;      /* 45d5f4 */
static ABISYM *yy_sym;              /* 46c05c */
static ABIFORM *yy_form;            /* 46c07c */

#define YYINITDEPTH 150
static int yys0[YYINITDEPTH + 1];               /* 46b480 */
static YYSTYPE yyv0[YYINITDEPTH + 1];           /* 46b6e0 */
static int *yys = yys0;                         /* 45d5f8 */
static YYSTYPE *yyv = yyv0;                     /* 45d5fc */
static long yymaxdepth = YYINITDEPTH;           /* 45d600 */
static YYSTYPE yyval;                           /* 46b450 */

/* signed 8/16 bit interpretation of the low bits of a value word */
static long yy_s8(unsigned long x)
{
    return (long)(((x & 0xffUL) ^ 0x80UL) - 0x80UL);
}

static long yy_s16(unsigned long x)
{
    return (long)(((x & 0xffffUL) ^ 0x8000UL) - 0x8000UL);
}

/* abi_lnk_extract_val on a value stack entry */
static ABIVAL *yyx(ABIVAL *dst, YYSTYPE *e, long type)
{
    ABIVAL in;

    in.lo = e->v.u & YM32;
    in.hi = e->w1;
    in.type = e->type;
    in.status = e->w3;
    return abi_lnk_extract_val(dst, &in, type);
}

/* stack growth (the original doubles the stacks; the first growth moves the
 * static arrays to the heap) */
static int yygrow(void)
{
    long newsize = yymaxdepth << 1;
    int *ns;
    YYSTYPE *nv;

    if (yymaxdepth == YYINITDEPTH) {
        ns = (int *)xmalloc((unsigned long)(newsize + 1) * sizeof(int));
        nv = (YYSTYPE *)xmalloc((unsigned long)(newsize + 1) * sizeof(YYSTYPE));
        if (ns == NULL || nv == NULL)
            return 0;
        memcpy(ns, yys, (size_t)(yymaxdepth + 1) * sizeof(int));
        memcpy(nv, yyv, (size_t)(yymaxdepth + 1) * sizeof(YYSTYPE));
    } else {
        ns = (int *)xrealloc(yys, (unsigned long)(newsize + 1) * sizeof(int));
        nv = (YYSTYPE *)xrealloc(yyv, (unsigned long)(newsize + 1) * sizeof(YYSTYPE));
        if (ns == NULL || nv == NULL)
            return 0;
    }
    yys = ns;
    yyv = nv;
    yymaxdepth = newsize;
    return 1;
}

int yyparse(void)
{
    int yystate = 0;
    long ps = -1;                   /* index of the top of the state stack */
    long pv = -1;                   /* index of the top of the value stack */
    long pvt;                       /* yypvt: top of the value stack at a reduction */
    long yyn, yym, yyj, len;
    int yychar = -1;
    int yyerrflag = 0;
    int yynerrs = 0;
    long xi;
    ABIVAL xt;
    unsigned long a, b, c;
    ABIVAL v64;
    ABI64 r64;
    char *name;
    long op;

    (void)yynerrs;
#define YV(k) (yyv[pvt - (k)])
#define XV(k, ty) (yyx(&xt, &YV(k), (ty))->lo)

yystack:
    ps++;
    if (ps >= yymaxdepth) {
        if (!yygrow()) {
            abi_expr_error_stub("yacc stack overflow");
            return 1;
        }
    }
    yys[ps] = yystate;
    pv++;
    yyv[pv] = yyval;

yynewstate:
    yyn = yypact[yystate];
    if (yyn > YYFLAG) {
        if (yychar < 0) {
            yychar = yylex();
            if (yychar < 0)
                yychar = 0;
        }
        yyn += yychar;
        if (yyn >= 0 && yyn < YYLAST) {
            yyn = yyact[yyn];
            if (yychk[yyn] == yychar) {
                yychar = -1;
                yyval = yylval;
                yystate = (int)yyn;
                if (yyerrflag > 0)
                    yyerrflag--;
                goto yystack;
            }
        }
    }

    yyn = yydef[yystate];
    if (yyn == -2) {
        if (yychar < 0) {
            yychar = yylex();
            if (yychar < 0)
                yychar = 0;
        }
        for (xi = 0; yyexca[xi] != -1 || yyexca[xi + 1] != yystate; xi += 2)
            ;
        for (xi += 2; yyexca[xi] >= 0; xi += 2)
            if (yyexca[xi] == yychar)
                break;
        yyn = yyexca[xi + 1];
        if (yyn < 0)
            return 0;
    }

    if (yyn == 0) {                 /* error */
        switch (yyerrflag) {
        case 0:
            abi_expr_error_stub("syntax error");
            yynerrs++;
            /* fall through */
        case 1:
        case 2:
            yyerrflag = 3;
            for (;;) {
                if (ps < 0)
                    return 1;
                yyn = yypact[yys[ps]] + YYERRCODE;
                if (yyn >= 0 && yyn < YYLAST && yychk[yyact[yyn]] == YYERRCODE)
                    break;
                ps--;
                pv--;
            }
            yystate = yyact[yyn];
            goto yystack;
        case 3:
            if (yychar == 0)
                return 1;
            yychar = -1;
            goto yynewstate;
        }
    }

    /* reduce by rule yyn */
    yym = yyn;
    pvt = pv;
    len = yyr2[yyn] >> 1;
    if ((yyr2[yyn] & 1) == 0) {     /* rule without action */
        pv -= len;
        yyval = yyv[pv + 1];
        yyn = yyr1[yyn];
        ps -= len;
        yyj = yypgo[yyn] + 1 + yys[ps];
        if (yyj >= YYLAST || yychk[yystate = yyact[yyj]] != -yyn)
            yystate = yyact[yypgo[yyn]];
        goto yystack;
    }

    pv -= len;
    yyval = yyv[pv + 1];
    yyn = yyr1[yyn];
    ps -= len;
    yyj = yypgo[yyn] + 1 + yys[ps];
    if (yyj >= YYLAST || yychk[yystate = yyact[yyj]] != -yyn)
        yystate = yyact[yypgo[yyn]];

    switch (yym) {
    case 1:
        yyval.v = YV(0).v;
        break;
    case 2:
        yyval.v.u = XV(0, 2);
        abi_parse_ctx->result = new_expr();
        abi_parse_ctx->result->lo = yyval.v.u;
        break;
    case 3:
    case 4:
        break;
    case 5: case 6: case 8: case 10: case 11: case 12: case 13:
        yyval.type = 1;
        break;
    case 7: case 9: case 14: case 15: case 16: case 17:
        yyval.type = 2;
        break;
    case 18:
        name = YV(0).v.s;
        yy_sym = symtbl_find_by_name(g_symtblarr, name);
        if (yy_sym == NULL)
            return 1;
        yyval.v.u = yy_sym->lo & YM32;
        yyval.w1 = yy_sym->hi & YM32;
        yyval.type = 3;
        if (name != NULL)
            free(name);
        break;
    case 19:
        yyval.v.u = *abi_parse_ctx->arg & YM32;
        break;
    case 20:
        yyval.v.u = *abi_parse_ctx->run_ctr2 & YM32;
        break;
    case 21:
        yyval.v.u = *abi_parse_ctx->run_ctr & YM32;
        break;
    case 22:
        b = XV(0, 1);
        a = XV(2, 1);
        yyval.v.u = abi_op_add(a, b);
        break;
    case 23:
        b = XV(0, 1);
        a = XV(2, 1);
        yyval.v.u = abi_op_sub(a, b);
        break;
    case 24: case 25: case 26: case 27: case 28: case 29:
        if (yym == 24)
            op = 0x101;
        else if (yym == 25)
            op = 0x102;
        else if (yym == 29)
            op = 0x3d;
        else
            op = 0x103;
        name = YV(2).v.s;
        if (abi_skip == 0) {
            v64 = *yyx(&xt, &YV(0), 3);
            r64 = abi_assign_op(g_symtblarr, name, (int)op, v64.lo, v64.hi);
            yyval.v.u = r64.lo & YM32;
        }
        if (name != NULL)
            free(name);
        break;
    case 30:
        b = XV(0, 2);
        a = XV(2, 2);
        yyval.v.u = abi_op_and(a, b);
        break;
    case 31:
        b = XV(0, 2);
        a = XV(2, 2);
        yyval.v.u = abi_op_or(a, b);
        break;
    case 32:
        b = XV(0, 2);
        a = XV(2, 2);
        yyval.v.u = abi_op_xor(a, b);
        break;
    case 33:
        a = XV(1, 1);
        abi_cond_state = (a == 0) ? 3 : 2;
        abi_skip = (a == 0);
        break;
    case 34:
        abi_skip = (abi_cond_state == 2);
        break;
    case 35:
        abi_skip = 0;
        b = XV(0, 1);
        a = XV(3, 1);
        c = XV(6, 1);
        yyval.v.u = abi_op_cond(c, a, b);
        break;
    case 36:
        b = XV(0, 1);
        a = XV(2, 1);
        yyval.v.u = abi_op_eq(a, b);
        break;
    case 37:
        b = XV(0, 1);
        a = XV(2, 1);
        yyval.v.u = abi_op_ne(a, b);
        break;
    case 38:
        b = XV(0, 1);
        a = XV(2, 1);
        yyval.v.u = abi_op_land(a, b);
        break;
    case 39:
        b = XV(0, 1);
        a = XV(2, 1);
        yyval.v.u = abi_op_lor(a, b);
        break;
    case 40:
        b = XV(0, 1);
        a = XV(2, 1);
        yyval.v.u = abi_op_mul(a, b);
        break;
    case 41:
        b = XV(0, 1);
        a = XV(2, 1);
        yyval.v.u = abi_op_div(a, b);
        break;
    case 42:
        b = XV(0, 1);
        a = XV(2, 1);
        yyval.v.u = abi_op_mod(a, b);
        break;
    case 43:
        yyval = YV(1);
        break;
    case 44:
        b = XV(0, 1);
        a = XV(2, 1);
        yyval.v.u = abi_op_le(a, b);
        break;
    case 45:
        b = XV(0, 1);
        a = XV(2, 1);
        yyval.v.u = abi_op_ge(a, b);
        break;
    case 46:
        b = XV(0, 1);
        a = XV(2, 1);
        yyval.v.u = abi_op_gt(a, b);
        break;
    case 47:
        b = XV(0, 1);
        a = XV(2, 1);
        yyval.v.u = abi_op_lt(a, b);
        break;
    case 48:
        b = XV(0, 2) & 0xffUL;
        a = XV(2, 2);
        yyval.v.u = abi_op_shr(a, b);
        break;
    case 49:
        b = XV(0, 2) & 0xffUL;
        a = XV(2, 2);
        yyval.v.u = abi_op_shl(a, b);
        break;
    case 50:
        a = XV(0, 1);
        yyval.v.u = abi_op_lnot(a);
        yyval.type = 1;
        break;
    case 51:
        a = XV(0, 2);
        yyval.v.u = abi_op_compl(a);
        yyval.type = 2;
        break;
    case 52:
        a = XV(0, 1);
        yyval.v.u = abi_op_neg(a);
        yyval.type = 1;
        break;
    case 53:
        if (abi_skip == 0) {
            name = YV(9).v.s;
            yy_form = form_find_by_name(g_formarr, name);
            if (yy_form == NULL)
                return 1;
            abi_parse_ctx->val = XV(7, 2);
            abi_parse_ctx->fill = (char)(YV(5).v.u & 0xffUL);
            abi_parse_ctx->unk_18 = ABI_S32(XV(3, 1));
            abi_parse_ctx->type = (short)yy_s16(XV(1, 0));
            yyval.v.u = (*yy_form->fn)(abi_parse_ctx) & YM32;
        }
        if (YV(9).v.s != NULL)
            free(YV(9).v.s);
        break;
    case 56:
        yyval.v = YV(0).v;
        break;
    case 63:                        /* check(v, c, lo) */
        if (abi_skip == 0) {
            b = XV(1, 1);
            c = YV(3).v.u;
            a = XV(5, 2);
            yyval.v.u = (unsigned long)yy_s16(abi_func_check(a, (int)yy_s8(c),
                                                (int)ABI_S32(b), 0)) & YM32;
        }
        break;
    case 64:                        /* check(v, c, lo, hi) */
        if (abi_skip == 0) {
            long hi = yy_s16(XV(1, 0));
            long lo = ABI_S32(XV(3, 1));

            c = YV(5).v.u;
            a = XV(7, 2);
            yyval.v.u = (unsigned long)yy_s16(abi_func_check(a, (int)yy_s8(c),
                                                (int)lo, (int)hi)) & YM32;
        }
        break;
    case 65:                        /* pack(v, c, pos) */
        if (abi_skip == 0) {
            b = XV(1, 1);
            c = YV(3).v.u;
            a = XV(5, 2);
            yyval.v.u = abi_func_pack(a, (int)yy_s8(c), (int)ABI_S32(b), 0) & YM32;
        }
        break;
    case 66:                        /* pack(v, c, pos, width) */
        if (abi_skip == 0) {
            long width = yy_s16(XV(1, 0));
            long pos = ABI_S32(XV(3, 1));

            c = YV(5).v.u;
            a = XV(7, 2);
            yyval.v.u = abi_func_pack(a, (int)yy_s8(c), (int)pos, (int)width) & YM32;
        }
        break;
    case 67:
    case 68:
        yyval.v.u = (yyval.v.u & ~0xffUL) | (YV(0).v.u & 0xffUL);
        break;
    case 69:
        if (abi_skip == 0) {
            a = XV(1, 1);
            yyval.v.u = (unsigned long)abi_func_sym(abi_parse_ctx, (MpArr *)abi_modules,
                                                     ABI_S32(a)) & YM32;
        }
        break;
    case 70:
        if (abi_skip == 0) {
            a = XV(1, 1);
            yyval.v.u = (unsigned long)abi_mp_sym_set_type(abi_parse_ctx, (int)yy_s16(a)) & YM32;
        }
        break;
    case 71:
        if (abi_skip == 0) {
            a = XV(1, 1);
            yyval.v.u = (unsigned long)set_cur_opt_char(ABI_S32(a)) & YM32;
        }
        break;
    case 72:
        if (abi_skip == 0) {
            a = XV(3, 1);
            yyval.v.u = (unsigned long)set_cur_opt_char(ABI_S32(a)) & YM32;
        }
        break;
    case 73:
        if (abi_skip == 0) {
            a = XV(1, 2);
            /* abi_mp_sym_shift_field (43825a) returns its masked shift */
            yyval.v.u = abi_mask_then_shift(a, abi_bit_range_mask(8, 15), 8, '>') & YM32;
        }
        break;
    case 74:
        if (abi_skip == 0) {
            a = XV(1, 2);
            yyval.v.u = abi_mp_sym_get_mask(abi_parse_ctx, a) & YM32;
        }
        break;
    case 75:
        if (abi_skip == 0) {
            long space = yy_s16(XV(1, 0));

            a = XV(3, 1);
            yyval.v.u = (unsigned long)abi_func_memcheck(abi_parse_ctx, 0L, ABI_S32(a),
                                                          (int)space) & YM32;
        }
        break;
    case 76:
        if (abi_skip == 0) {
            a = XV(15, 2);
            yyval.v.u = (unsigned long)abi_map_lookup(abi_parse_ctx, (long)a,
                            (long)(YV(13).v.u & YM32), (long)(YV(11).v.u & YM32),
                            (long)(YV(9).v.u & YM32), (long)(YV(7).v.u & YM32),
                            (long)(YV(5).v.u & YM32), (long)(YV(3).v.u & YM32),
                            (long)(YV(1).v.u & YM32)) & YM32;
        }
        break;
    default:
        break;
    }
    goto yystack;
}
