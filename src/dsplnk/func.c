/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7, DSPLNK.EXE), func.c
 * Original module: "$Id: func.c,v 1.23 1999/03/19 20:11:26 jay Exp $"
 * Reconstructed from 004128e0-00413c2f.
 *
 * The @-functions of relocation expressions (@LB, @HB, @FBF, @FB2, @IMAX,
 * @IMIN, @CEIL2, @SZCK, @LRF, @ENC, @AENC, @BYT).  Each takes the EXPR that
 * parse_term allocated for the call, frees it and returns the result EXPR.
 * Note: @ENC and @AENC skip arguments textually and @ENC writes ")\0" into
 * the input text (input_cursor must point to writable memory).
 */
#include "dsplnk.h"

static EXPR *fn_lb(EXPR *e);
static EXPR *fn_hb(EXPR *e);
static EXPR *fn_fbf(EXPR *e);
static EXPR *fn_imax_imin(EXPR *e, int id);
static EXPR *fn_ceil2(EXPR *e);
static EXPR *fn_fb2(EXPR *e);
static EXPR *fn_szck(EXPR *e);
static EXPR *fn_lrf(EXPR *e);
static EXPR *fn_enc(EXPR *e);
static EXPR *fn_aenc(EXPR *e);
static EXPR *fn_byt(EXPR *e);
int func_name_cmp(void *key, void *ent);

/* signed interpretation of a 32-bit value */
static long sx32(unsigned long v)
{
    v = M32(v);
    if (v & 0x80000000UL)
        return -(long)(~v & 0x7fffffffUL) - 1L;
    return (long)v;
}

/* plain absolute integer result */
static void set_result(EXPR *e, unsigned long v)
{
    e->mid = 0;
    e->hi = 0;
    e->lo = v;
    e->type = EXPR_INT;
    e->map = MS_N;
    e->space = MS_N;
    e->ctr = 0;
    e->attr = 0;
    e->size = fmt_word;
}

/* 004128e0: after '@' */
EXPR *func_call_eval(EXPR *e)
{
    char name[8];
    int n;
    FUNCTAB *f;

    n = 0;
    while ((isalnum((unsigned char)*input_cursor) || *input_cursor == '_') && n <= 6) {
        name[n++] = (char)(isupper((unsigned char)*input_cursor)
                           ? tolower((unsigned char)*input_cursor) : *input_cursor);
        *cform_ptr++ = *input_cursor++;
    }
    name[n] = 0;
    if (*input_cursor != '(') {
        free_expr(e);
        lnk_error1("Missing '(' for function");
        return NULL;
    }
    *cform_ptr++ = *input_cursor++;
    f = (FUNCTAB *)tab_search(name, func_tab, func_count, 12L, func_name_cmp);
    if (f == NULL) {
        lnk_error2("Invalid function name", name);
        free_expr(e);
        return NULL;
    }
    switch ((signed char)f->id) {
    case FN_FBF:
        e = fn_fbf(e);
        if (e == NULL)
            return NULL;
        break;
    case FN_LRF:
        e = fn_lrf(e);
        if (e == NULL)
            return NULL;
        break;
    case FN_ENC:
        e = fn_enc(e);
        if (e == NULL)
            return NULL;
        break;
    case FN_FB2:
        e = fn_fb2(e);
        if (e == NULL)
            return NULL;
        break;
    case FN_BYT:
        e = fn_byt(e);
        if (e == NULL)
            return NULL;
        break;
    case FN_SDI:
    case FN_SDI2:
        lnk_fatal1("Branch optimization sequence failure");
        break;
    case FN_IMAX:
    case FN_IMIN:
        e = fn_imax_imin(e, (int)(signed char)f->id);
        if (e == NULL)
            return NULL;
        break;
    case FN_CEIL2:
        e = fn_ceil2(e);
        if (e == NULL)
            return NULL;
        break;
    case FN_SZCK:
        e = fn_szck(e);
        if (e == NULL)
            return NULL;
        break;
    case FN_AENC:
        e = fn_aenc(e);
        if (e == NULL)
            return NULL;
        break;
    case FN_LB:
        e = fn_lb(e);
        if (e == NULL)
            return NULL;
        break;
    case FN_HB:
        e = fn_hb(e);
        if (e == NULL)
            return NULL;
        break;
    default:
        lnk_fatal1("Invalid function type");
        break;
    }
    if (*input_cursor == ')') {
        *cform_ptr++ = *input_cursor++;
    } else {
        free_expr(e);
        lnk_error1("Extra characters in function argument or missing ')' for function");
        e = NULL;
    }
    return e;
}

/* 00412ce0: the table name is matched as a prefix of the key */
int func_name_cmp(void *key, void *ent)
{
    char *name;

    name = ((FUNCTAB *)ent)->name;
    return strncmp((char *)key, name, strlen(name));
}

/* 00412d06: @LB(x) */
static EXPR *fn_lb(EXPR *e)
{
    free_expr(e);
    e = parse_expr();
    if (e == NULL)
        return NULL;
    e->lo = M32(e->lo << 1);
    return e;
}

/* 00412d46: @HB(x) */
static EXPR *fn_hb(EXPR *e)
{
    free_expr(e);
    e = parse_expr();
    if (e == NULL)
        return NULL;
    e->lo = M32(e->lo << 1);
    e->lo = M32(e->lo + 1);
    return e;
}

/* 00412d95: @FBF(mask) */
static EXPR *fn_fbf(EXPR *e)
{
    unsigned long v, r;

    r = 0;
    free_expr(e);
    e = parse_expr();
    if (e == NULL)
        return NULL;
    e->mid = 0;
    e->hi = 0;
    v = e->lo;
    if (((v & 0xf000) == 0 || (v & 0xf) == 0) &&
        ((v & 0xf000) == 0 || (v & 0xf0) == 0) &&
        ((v & 0xf00) == 0 || (v & 0xf) == 0)) {
        if ((v & 0xf00) != 0 && (v & 0xf0) != 0)
            r = v >> 4 | 0x4000;
        else if ((v & 0xff00) != 0)
            r = v >> 8 | 0x8000;
        else if ((v & 0xff) != 0)
            r = v | 0x2000;
        else
            lnk_warning1("Empty bit mask field");
        set_result(e, r);
    } else {
        lnk_error1("Bit mask cannot span more than eight bits");
        free_expr(e);
        e = NULL;
    }
    return e;
}

/* 00412f0d: @IMAX(a,b,...) / @IMIN(a,b,...), unsigned */
static EXPR *fn_imax_imin(EXPR *e, int id)
{
    unsigned long r, v;

    free_expr(e);
    e = parse_expr();
    if (e == NULL)
        return NULL;
    if (e->flags & EXPR_REL) {
        lnk_error1("Relative expression not allowed");
        free_expr(e);
        return NULL;
    }
    if (e->type != EXPR_INT) {
        free_expr(e);
        lnk_error1("Expression result must be integer");
        return NULL;
    }
    r = e->lo;
    while (*input_cursor == ',') {
        input_cursor++;
        free_expr(e);
        e = parse_expr();
        if (e == NULL)
            return NULL;
        v = e->type == EXPR_INT ? e->lo : 0;
        if (id == FN_IMIN) {
            if (v < r)
                r = v;
        } else if (r < v) {
            r = v;
        }
    }
    set_result(e, r);
    e->flags &= ~(unsigned long)EXPR_REL;
    return e;
}

/* 004130a7: @CEIL2(a,b) */
static EXPR *fn_ceil2(EXPR *e)
{
    unsigned long a;
    char c;

    free_expr(e);
    e = parse_expr();
    if (e == NULL)
        return NULL;
    if (e->flags & EXPR_REL) {
        lnk_error1("Relative expression not allowed");
        free_expr(e);
        return NULL;
    }
    if (e->type != EXPR_INT) {
        free_expr(e);
        lnk_error1("Expression result must be integer");
        return NULL;
    }
    a = e->lo;
    free_expr(e);
    c = *input_cursor++;
    if (c != ',') {
        lnk_error1("Syntax error - expected comma");
        return NULL;
    }
    e = parse_expr();
    if (e == NULL)
        return NULL;
    if (e->flags & EXPR_REL) {
        lnk_error1("Relative expression not allowed");
        free_expr(e);
        return NULL;
    }
    if (e->type != EXPR_INT) {
        free_expr(e);
        lnk_error1("Expression result must be integer");
        return NULL;
    }
    e->mid = 0;
    e->hi = 0;
    if (e->lo != 0)
        a = buf_align(a, e->lo, 0xffffffffUL);
    set_result(e, a);
    e->flags &= ~(unsigned long)EXPR_REL;
    return e;
}

/* 00413290: @FB2(mask) */
static EXPR *fn_fb2(EXPR *e)
{
    unsigned long hb, lb, r;

    r = 0;
    free_expr(e);
    e = parse_expr();
    if (e == NULL)
        return NULL;
    e->mid = 0;
    e->hi = 0;
    hb = e->lo & 0xff00;
    lb = e->lo & 0xff;
    if (hb == 0 || lb == 0) {
        if (hb != 0)
            r = hb | 0x80;
        else if (lb != 0)
            r = lb << 8;
        else
            lnk_warning1("Empty bit mask field");
        set_result(e, r);
    } else {
        lnk_error1("Bit mask cannot span more than eight bits");
        free_expr(e);
        e = NULL;
    }
    return e;
}

/* 004133aa: @SZCK('kNNa') - nested evaluation */
static EXPR *fn_szck(EXPR *e)
{
    free_expr(e);
    e = eval_expr();
    if (e == NULL)
        return NULL;
    e->type = EXPR_SZCK;
    return e;
}

/* read one ',' (the cursor advances even when it is something else) */
static int want_comma(void)
{
    char c;

    c = *input_cursor++;
    return c == ',';
}

static EXPR *comma_error(EXPR *e)
{
    lnk_error1("Syntax error - expected comma");
    free_expr(e);
    return NULL;
}

/* 004133da: @LRF(v,map,ctr,sect,rsect,buf,ovl[,sdi]) */
static EXPR *fn_lrf(EXPR *e)
{
    free_expr(e);
    e = eval_expr();
    if (e == NULL)
        return NULL;
    if (e->type != EXPR_INT) {
        free_expr(e);
        lnk_error1("Expression result must be integer");
        return NULL;
    }
    if (!want_comma())
        return comma_error(e);
    e->map = eval_nonneg();
    if (e->map == -1) {
        free_expr(e);
        return NULL;
    }
    e->space = map_to_space(e->map);
    if (!want_comma())
        return comma_error(e);
    e->ctr = eval_nonneg();
    if (e->ctr == -1) {
        free_expr(e);
        return NULL;
    }
    if (!want_comma())
        return comma_error(e);
    e->sect = eval_nonneg();
    if (e->sect == -1) {
        free_expr(e);
        return NULL;
    }
    if (!want_comma())
        return comma_error(e);
    e->rsect = eval_nonneg();
    if (e->rsect == -1) {
        free_expr(e);
        return NULL;
    }
    if (!want_comma())
        return comma_error(e);
    e->buf = eval_nonneg();
    if (e->buf == -1) {
        free_expr(e);
        return NULL;
    }
    if (!want_comma())
        return comma_error(e);
    e->ovl = eval_nonneg();
    if (e->ovl == -1) {
        free_expr(e);
        return NULL;
    }
    if (*input_cursor == ',') {
        input_cursor++;
        e->sdi = eval_nonneg();
        if (e->sdi == -1) {
            free_expr(e);
            return NULL;
        }
    }
    return e;
}

/* 004136d0: @ENC(a,b,x,y) = b > a ? x : y (unsigned) */
static EXPR *fn_enc(EXPR *e)
{
    unsigned long a, b;
    char *p;

    free_expr(e);
    e = eval_int();
    if (e == NULL)
        return NULL;
    if (!want_comma())
        return comma_error(e);
    a = e->lo;
    free_expr(e);
    e = eval_abs();
    if (e == NULL)
        return NULL;
    if (!want_comma())
        return comma_error(e);
    b = e->lo;
    free_expr(e);
    if (b <= a) {
        p = strchr(input_cursor, ',');
        if (p == NULL) {
            /* the original also sets input_cursor to NULL here */
            lnk_error1("Syntax error - expected comma");
            /* the original frees the already freed EXPR here again */
            return NULL;
        }
        input_cursor = p + 1;
    }
    e = eval_int();
    if (e == NULL)
        return NULL;
    if (a < b) {
        input_cursor[0] = ')';
        input_cursor[1] = 0;
    }
    return e;
}

/* 00413832: @AENC(a,b,x,y,t) = a < b ? x : y (unsigned) */
static EXPR *fn_aenc(EXPR *e)
{
    unsigned long a, b;
    EXPR *t;
    char *p;

    free_expr(e);
    e = eval_int();
    if (e == NULL)
        return NULL;
    if (!want_comma())
        return comma_error(e);
    a = e->lo;
    free_expr(e);
    e = eval_int();
    if (e == NULL)
        return NULL;
    if (!want_comma())
        return comma_error(e);
    b = e->lo;
    free_expr(e);
    if (a < b) {
        e = eval_int();
        if (e == NULL)
            return NULL;
        p = strrchr(input_cursor, ',');
        if (p == NULL)
            return comma_error(e);
        input_cursor = p + 1;
    } else {
        p = strchr(input_cursor, ',');
        if (p == NULL) {
            lnk_error1("Syntax error - expected comma");
            /* the original frees the already freed EXPR here again */
            return NULL;
        }
        input_cursor = p + 1;
        e = eval_int();
        if (e == NULL)
            return NULL;
        p = strchr(input_cursor, ',');
        if (p == NULL)
            return comma_error(e);
        input_cursor = p + 1;
    }
    t = eval_abs();
    if (t == NULL)
        return NULL;
    if (*input_cursor == ')') {
        free_expr(t);
    } else {
        lnk_error1("Syntax error - expected terminating constant");
        free_expr(t);
        e = NULL;
    }
    return e;
}

/* 00413acf: @BYT(mode,v); sets addr_bytes = mode */
static EXPR *fn_byt(EXPR *e)
{
    EXPR *m;
    unsigned long v;
    long sv;

    free_expr(e);
    m = eval_abs();
    if (m == NULL)
        return NULL;
    if (!want_comma())
        return comma_error(m);
    addr_bytes = (long)m->lo;
    free_expr(m);
    e = eval_expr();
    if (e == NULL)
        return NULL;
    if (e->type == EXPR_INT) {
        if (e->size == fmt_dword || e->mid == word_mask || e->space == MS_N)
            v = expr_as_int32(e);
        else
            v = e->lo;
    } else {
        float_to_fixed_frac(e->fval, fmt_word, e);
        v = e->lo;
    }
    sv = sx32(v);
    if (addr_bytes == 2 && (sv < -0x8000L || sv > 0x7fffL)) {
        lnk_error1("Byte-addressable value too large");
        free_expr(e);
        e = NULL;
    } else {
        e->mid = 0;
        e->lo = v;
    }
    return e;
}
