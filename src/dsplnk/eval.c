/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7, DSPLNK.EXE), eval.c
 * Original module: "$Id: eval.c,v 1.34 1999/03/19 20:11:23 jay Exp $"
 * Reconstructed from 0040a370-0040caf6.
 *
 * Expression evaluator: eval_expr is the top level (setjmp for the SIGFPE
 * handler), parse_expr/parse_binop_rhs do precedence climbing over
 * binop_tab, parse_term handles unary operators, brackets, constants,
 * '*', strings, @functions and symbols.  Every EXPR is allocated by
 * new_expr and recorded on the expression stack so that the longjmp path
 * can release it.
 *
 * cform_buf/cform_ptr keep a canonical text of the expression as the
 * original does; the text is never read in DSPLNK.  The port uses a larger
 * buffer and restarts it when it runs full (the original overflowed into
 * err_symbol).
 */
#include "dsplnk.h"

#define CFORM_PORT_SIZE 4096
#define CFORM_RESERVE   1200    /* room for one name or formatted value */

EXPR **expr_stack;                      /* 461f28 */
EXPR **expr_sp;                         /* 461f2c next free slot */
static long expr_stack_max = EXPR_STACK_INIT;   /* 455e84 */
static char cform_buf[CFORM_PORT_SIZE]; /* 461938 */

static EXPR *parse_binop_rhs(EXPR *lhs, int min_prec, char *cpos);
static int get_op_code(void);
static int op_precedence(int op);
static char *cform_fold(EXPR *e, char *pos);
static EXPR *parse_term(void);
static void emit_value_text(EXPR *e);

/* port: keep the canonical-text cursor inside cform_buf */
static void cf_room(void)
{
    if (cform_ptr == NULL || cform_ptr < cform_buf ||
        cform_ptr >= cform_buf + CFORM_PORT_SIZE - CFORM_RESERVE) {
        cform_ptr = cform_buf;
        *cform_ptr = 0;
    }
}

/* copy the current input character to the canonical text and advance */
static void cf_copy(void)
{
    cf_room();
    *cform_ptr++ = *input_cursor++;
}

/* 0040a370 */
EXPR *eval_int(void)
{
    EXPR *e;
    unsigned long v;

    e = eval_expr();
    if (e != NULL) {
        if (e->type == EXPR_INT) {
            v = expr_as_int32(e);
            e->hi = 0;
            e->mid = 0;
            e->lo = v;
        } else {
            free_expr(e);
            lnk_error1("Expression result must be integer");
            e = NULL;
        }
    }
    return e;
}

/* 0040a3e6 */
EXPR *eval_abs(void)
{
    EXPR *e;
    unsigned long v;

    e = eval_expr();
    if (e != NULL) {
        if (e->type != EXPR_INT) {
            free_expr(e);
            lnk_error1("Expression result must be integer");
            e = NULL;
        } else if (e->flags & EXPR_REL) {
            free_expr(e);
            lnk_error1("Expression result must be absolute");
            e = NULL;
        } else if (e->sect < 0) {
            free_expr(e);
            lnk_error1("External reference not allowed in expression");
            e = NULL;
        } else {
            v = expr_as_int32(e);
            e->hi = 0;
            e->mid = 0;
            e->lo = v;
        }
    }
    return e;
}

/* signed interpretation of a 32-bit value */
static long sx32(unsigned long v)
{
    v = M32(v);
    if (v & 0x80000000UL)
        return -(long)(~v & 0x7fffffffUL) - 1L;
    return (long)v;
}

/* 0040a4ae */
long eval_nonneg(void)
{
    EXPR *e;
    long v;

    e = eval_abs();
    if (e == NULL)
        return -1;
    v = sx32(e->lo);
    if (v < 0) {
        lnk_error1("Expression cannot have a negative value");
        v = -1;
    }
    free_expr(e);
    return v;
}

/* 0040a4fd */
long eval_nonneg_resolved(void)
{
    EXPR *e;
    long v;

    e = eval_abs();
    if (e == NULL)
        return -1;
    v = sx32(e->lo);
    if (v < 0) {
        lnk_error1("Expression cannot have a negative value");
        v = -1;
    } else if (e->flags & EXPR_FWD) {
        lnk_error1("Expression contains forward references");
        v = -1;
    }
    free_expr(e);
    return v;
}

/* 0040a571 */
EXPR *eval_expr(void)
{
    EXPR *e;

    if (*input_cursor == 0) {
        lnk_error1("Missing expression");
        return NULL;
    }
    if (setjmp(eval_jmpbuf) != 0) {
        addr_cancel = 0;
        in_eval = 0;
        err_symbol[0] = 0;
        cform_buf[0] = 0;
        cform_ptr = NULL;
        src_line = 0;
        free_expr_stack_all();
        return NULL;
    }
    in_eval = 1;
    cform_ptr = cform_buf;
    cform_buf[0] = 0;
    src_line = 0;
    e = parse_expr();
    if (e == NULL) {
        src_line = 0;
        cform_buf[0] = 0;
        err_symbol[0] = 0;
        cform_ptr = NULL;
        in_eval = 0;
        return NULL;
    }
    if (e->sect < 0 || (e->flags & EXPR_FWD)) {
        if (e->type == EXPR_INT) {
            e->lo = 0;
            e->mid = 0;
            e->hi = 0;
            e->hi = 0;
            e->mid = 0;
        } else if (e->type == EXPR_FLT) {
            e->hi = 0;
            e->mid = 0;
            e->fval = 0.0;
        }
    }
    if (*input_cursor == 0 || *input_cursor == ',' || *input_cursor == ')' ||
        (*input_cursor == '.' && input_cursor[1] == '.')) {
        in_eval = 0;
        cf_room();
        *cform_ptr = 0;
    } else {
        lnk_error1("Extra characters beyond expression");
        free_expr(e);
        in_eval = 0;
        cform_buf[0] = 0;
        cform_ptr = NULL;
        e = NULL;
    }
    err_symbol[0] = 0;
    src_line = 0;
    return e;
}

/* 0040a772 */
EXPR *parse_expr(void)
{
    char *pos;
    EXPR *e;

    cf_room();
    pos = cform_ptr;
    e = parse_term();
    if (e == NULL)
        return NULL;
    e = parse_binop_rhs(e, PREC_START, pos);
    if (e != NULL && (e->flags & EXPR_REL) && e->type != EXPR_INT) {
        lnk_error1("Relative expression must be integer");
        free_expr(e);
        e = NULL;
    }
    return e;
}

/* 0040a7ed: precedence climbing */
static EXPR *parse_binop_rhs(EXPR *lhs, int min_prec, char *cpos)
{
    int op, prec, nxt;
    EXPR *rhs;

    for (;;) {
        op = get_op_code();
        if (op == 0)
            return lhs;
        prec = op_precedence(op);
        if (min_prec <= prec)
            return lhs;
        cf_copy();
        if (op == OP_SHR || op == OP_SHL || op == OP_EQ || op == OP_LE ||
            op == OP_GE || op == OP_NE || op == OP_LAND || op == OP_LOR)
            cf_copy();
        if ((lhs->flags & EXPR_REL) || lhs->sect < 0)
            cpos = cform_ptr;
        if (op == OP_LINE)
            src_line = (long)expr_as_int32(lhs);
        rhs = parse_term();
        if (rhs == NULL) {
            free_expr(lhs);
            return NULL;
        }
        nxt = get_op_code();
        if (nxt != 0 && op_precedence(nxt) < prec) {
            rhs = parse_binop_rhs(rhs, prec, cpos);
            if (rhs == NULL) {
                free_expr(lhs);
                return NULL;
            }
        }
        if (in_brace && opt_aec && !opt_c && op != OP_ADD && op != OP_SUB &&
            (lhs->space != MS_N || rhs->space != MS_N)) {
            free_expr(lhs);
            free_expr(rhs);
            lnk_error1("Operation not allowed with address term");
            return NULL;
        }
        addr_cancel = 0;
        if (rhs->sect >= 0 && binop_tab[op](lhs, rhs) == NULL) {
            addr_cancel = 0;
            return NULL;
        }
        if (!addr_cancel) {
            if (!(lhs->flags & EXPR_REL) && (rhs->flags & EXPR_REL)) {
                lhs->flags |= EXPR_REL;
                lhs->sect = rhs->sect;
                lhs->rsect = rhs->rsect;
                lhs->buf = rhs->buf;
                lhs->ovl = rhs->ovl;
                lhs->unk_3c = rhs->unk_3c;
                lhs->sdi = rhs->sdi;
            }
            lhs->space = merge_mem_space(lhs->space, rhs->space);
            if (lhs->space == MS_BAD) {
                lhs->map = MS_N;
                lhs->space = MS_N;
            }
        } else {
            addr_cancel = 0;
            lhs->flags &= ~(unsigned long)EXPR_REL;
            lhs->map = MS_N;
            lhs->space = MS_N;
            lhs->ctr = 0;
            lhs->attr = 0;
        }
        if (rhs->flags & EXPR_FWD)
            lhs->flags |= EXPR_FWD;
        if (rhs->sect < 0)
            lhs->sect = rhs->sect;
        free_expr(rhs);
        if (opt_i && op != OP_MAP)
            cpos = cform_fold(lhs, cpos);
    }
}

/* 0040ab66: peek at the operator under input_cursor (not consumed) */
static int get_op_code(void)
{
    int op;
    char c1;

    op = 0;
    if (*input_cursor == 0)
        return 0;
    c1 = input_cursor[1];
    switch (*input_cursor) {
    case '!':
        op = c1 == '=' ? OP_NE : OP_LINE;
        break;
    case '#':
        op = OP_SIZE;
        break;
    case '%':
        op = OP_MOD;
        break;
    case '&':
        op = c1 == '&' ? OP_LAND : OP_AND;
        break;
    case '*':
        op = OP_MUL;
        break;
    case '+':
        op = OP_ADD;
        break;
    case '-':
        op = OP_SUB;
        break;
    case '/':
        op = OP_DIV;
        break;
    case ':':
        op = OP_MAP;
        /* the original reads p[4] even past the end of the text */
        if (input_cursor[1] == 0 || input_cursor[2] == 0 || input_cursor[3] == 0)
            colon_short = 1;
        else
            colon_short = !isxdigit((unsigned char)input_cursor[4]);
        break;
    case '<':
        if (c1 == '<')
            op = OP_SHL;
        else if (c1 == '=')
            op = OP_LE;
        else
            op = OP_LT;
        break;
    case '=':
        if (c1 == '=')
            op = OP_EQ;
        break;
    case '>':
        if (c1 == '>')
            op = OP_SHR;
        else if (c1 == '=')
            op = OP_GE;
        else
            op = OP_GT;
        break;
    case '@':
        op = OP_SPACE;
        break;
    case '^':
        op = OP_XOR;
        break;
    case '|':
        op = c1 == '|' ? OP_LOR : OP_OR;
        break;
    }
    return op;
}

/* 0040ade2: smaller binds tighter */
static int op_precedence(int op)
{
    switch (op) {
    case OP_ADD:
    case OP_SUB:
        return 2;
    case OP_MUL:
    case OP_DIV:
    case OP_MOD:
        return 1;
    case OP_AND:
    case OP_OR:
    case OP_XOR:
        return 6;
    case OP_SHL:
    case OP_SHR:
        return 3;
    case OP_LT:
    case OP_GT:
    case OP_LE:
    case OP_GE:
        return 4;
    case OP_EQ:
    case OP_NE:
        return 5;
    case OP_LAND:
    case OP_LOR:
        return 7;
    default:
        return 0;
    }
}

/* 0040ae82: binop_tab[0] */
EXPR *op_bad(EXPR *lhs, EXPR *rhs)
{
    lnk_fatal1("Expression operator failure");
    return NULL;
}

/* 0040ae96: replace the text from pos with the value of an absolute term */
static char *cform_fold(EXPR *e, char *pos)
{
    char *r;

    r = cform_ptr;
    if (!(e->flags & EXPR_REL) && e->sect >= 0) {
        if (pos == NULL || pos < cform_buf ||
            pos >= cform_buf + CFORM_PORT_SIZE - CFORM_RESERVE)
            pos = cform_buf;
        if (e->type == EXPR_FLT)
            fmt_double(pos, "%-.15E", e->fval);
        else if (e->size == fmt_word)
            sprintf(pos, "%s%lX", cform_prefix, e->lo & word_mask);
        else
            sprintf(pos, "%s%lX%0*lX", cform_prefix, e->mid & word_mask,
                    (int)word_digits, e->lo & word_mask);
        cform_ptr = pos + strlen(pos);
        r = pos;
    }
    return r;
}

/* 0040af6e helper: the '[' term (section relative address) */
static EXPR *parse_bracket(void)
{
    int nv;
    long idx, k;
    EXPR *e;
    SECTION *sec;
    MODSEC *ms;
    SECNAME *sn;
    SECNODE *n;
    SECTION *p;
    unsigned long adj;
    MEMSPEC spec;
    SDISTAT *sd;

    nv = !(obj_major < 6 && (obj_major != 5 || obj_minor < 1) &&
           (obj_major != 5 || obj_minor != 0 || obj_rev < 0xb));
    cf_copy();
    e = parse_expr();
    if (e == NULL)
        return NULL;
    if (e->type != EXPR_INT || run_spec.mspace == MS_N) {
        free_expr(e);
        lnk_error1("Invalid relative expression");
        return NULL;
    }
    idx = e->rsect < 0 ? cur_rsecno : e->rsect;
    if ((nv && e->ovl != 0) || (!nv && run_ctr != load_ctr)) {
        k = nv ? ovl_base + e->ovl : cur_overlay;
        e->lo = M32(e->lo + mod_ovltab[k].grp->lo);
    } else {
        if (e->buf == 0 || !(mod_buftab[buf_base + e->buf].sec->flags & 0x20000UL)) {
            if ((nv && e->rsect == cur_rsecno && e->space == load_spec.mspace &&
                 e->ctr == load_spec.mcntr) ||
                (!nv && e->space == load_spec.mspace && e->ctr == load_spec.mcntr)) {
                sec = cur_rsection;
                ms = cur_rmsec;
            } else {
                sec = NULL;
                sn = cur_rsection->node->sname;
                for (n = sn->nodes; n != NULL; n = n->next) {
                    if (n->spec.mspace == e->space && n->spec.mcntr == e->ctr) {
                        sec = n->secs;
                        break;
                    }
                }
                ms = mod_secmap[idx];
                while (ms != NULL && (ms->sec->node->spec.mspace != e->space ||
                                      ms->sec->node->spec.mcntr != e->ctr))
                    ms = ms->next;
                if (ms == NULL) {
                    spec.mspace = e->space;
                    spec.mmap = e->map;
                    spec.mcntr = e->ctr;
                    spec.mclass = e->attr;
                    sec_lookup_create(mod_secmap[idx]->sec->node->sname->name, idx,
                                      &spec, 1);
                    e->space = spec.mspace;
                    e->map = spec.mmap;
                    e->ctr = spec.mcntr;
                    e->attr = spec.mclass;
                    ms = mod_secmap[idx];
                    while (ms != NULL && (ms->sec->node->spec.mspace != e->space ||
                                          ms->sec->node->spec.mcntr != e->ctr))
                        ms = ms->next;
                }
            }
        } else {
            sec = mod_buftab[buf_base + e->buf].sec;
            ms = cur_rmsec;
        }
        if (sec == NULL || ms == NULL) {
            lnk_fatal1("Section map lookup failure");
            return NULL;
        }
        e->lo = M32(e->lo + sec->lo);
        if (!opt_i || (sec->flags & 0x20000UL)) {
            if (!(sec->flags & 0x2000UL)) {
                adj = 0;
                if (sec->flags & 0x20000UL) {
                    for (p = sec->node->bufs; p != NULL; p = p->next)
                        if (p->bufaddr <= e->lo)
                            adj = M32(adj + p->bufspan);
                }
                e->lo = M32(e->lo + M32(ms->base2 - adj));
            } else {
                e->lo = M32(e->lo - mod_buftab[buf_base + e->buf].addr);
            }
        } else {
            e->lo = M32(e->lo + ms->base2);
        }
    }
    if (run_ctr == load_ctr)
        e->lo = M32(e->lo + cur_rsection->node->sdigrow);
    else
        e->lo = M32(e->lo + (unsigned long)mod_ovltab[ovl_base + e->ovl].sdioff);
    if (cur_alloc != NULL && cur_alloc->sdi != NULL && e->sdi != 0) {
        sd = cur_alloc->sdi;
        e->lo = M32(e->lo + (unsigned long)sd->recs[sd->mod_first - 1 + e->sdi].growth);
    }
    e->flags |= EXPR_REL;
    if (*input_cursor != ']') {
        free_expr(e);
        lnk_error1("Missing ']' in expression");
        return NULL;
    }
    cf_copy();
    return e;
}

/* 0040af6e helper: decimal integer or floating constant */
static EXPR *parse_decimal(EXPR *e)
{
    unsigned long l44, l14, lc, l48, lim;
    long ndig;
    char *start, *cstart, *end;
    int save;

    lim = word_mask >> 4;
    l44 = l14 = lc = l48 = 0;
    ndig = 0;
    if (*input_cursor == '`')
        cf_copy();
    start = input_cursor;
    cf_room();
    cstart = cform_ptr;
    while (isdigit((unsigned char)*input_cursor)) {
        ndig++;
        l44 = M32(l44 * 10 - 0x30 + (unsigned long)(long)*input_cursor);
        l14 = M32(l14 * 10);
        lc = M32(lc * 10);
        l48 = M32(l48 * 10);
        if (lim < l44) {
            l14 = M32(l14 + (l44 >> (int)((word_bits - 4) & 31)));
            l44 &= lim;
        }
        if (lim < l14) {
            lc = M32(lc + (l14 >> (int)((word_bits - 4) & 31)));
            l14 &= lim;
        }
        if (lim < lc) {
            l48 = M32(l48 + (lc >> (int)((word_bits - 4) & 31)));
            lc &= lim;
        }
        cf_copy();
    }
    if ((*input_cursor == '.' && input_cursor[1] != '.') ||
        *input_cursor == 'e' || *input_cursor == 'E') {
        input_cursor = start;
        cform_ptr = cstart;
        e->fval = strtod(start, &end);
        if (end == input_cursor) {
            free_expr(e);
            lnk_error1("Floating point constant expected");
            return NULL;
        }
        input_cursor = end;
        save = *end;
        *end = 0;
        if (cform_ptr + strlen(start) >= cform_buf + CFORM_PORT_SIZE - 1) {
            cform_ptr = cform_buf;
            *cform_ptr = 0;
        }
        strcpy(cform_ptr, start);
        cform_ptr += strlen(cform_ptr);
        *input_cursor = (char)save;
        e->size = EXPR_SIZE_FLT;
        e->type = EXPR_FLT;
    } else if (ndig == 0) {
        free_expr(e);
        lnk_error1("Decimal constant expected");
        return NULL;
    }
    if (e->type == EXPR_INT) {
        e->lo = M32(l44 | (l14 << (int)((word_bits - 4) & 31))) & word_mask;
        l14 >>= 4;
        e->mid = M32(l14 | (lc << (int)((word_bits - 8) & 31))) & word_mask;
        lc >>= 8;
        e->hi = M32(lc | (l48 << (int)((word_bits - 12) & 31))) & word_mask;
        classify_value(e);
    }
    return e;
}

/* 0040af6e helper: symbol reference */
static EXPR *parse_symbol(EXPR *e)
{
    char *name;
    SYM *s;

    name = get_symbol();
    if (name == NULL) {
        free_expr(e);
        return NULL;
    }
    strcpy(err_symbol, name);
    s = sym_lookup(name, 0);
    if (s == NULL) {
        if (pass == 1) {
            free_expr(e);
            return NULL;
        }
        e->sect = -1;
        e->flags |= EXPR_FWD;
        cf_room();
        strcpy(cform_ptr, name);
        cform_ptr += strlen(cform_ptr);
        xref_add(name, 0, 0);
        return e;
    }
    if (s->flags & SYM_INT) {
        e->hi = 0;              /* original: low half of the (unused) double */
        e->mid = s->hi;
        e->lo = s->lo;
    } else if (s->flags & SYM_FLOAT) {
        e->fval = s->fval;
        e->type = EXPR_FLT;
    }
    e->space = s->mem.mspace;
    e->map = s->mem.mmap;
    e->ctr = s->mem.mcntr;
    e->attr = s->mem.mclass;
    if (s->flags & SYM_LONG)
        e->size = fmt_dword;
    e->flags |= s->flags & EXPR_REL;
    e->flags |= s->flags & EXPR_OVL;
    e->sect = s->sec == NULL ? 0 : s->sec->node->sname->num;
    e->rsect = s->rsec == NULL ? 0 : s->rsec->node->sname->num;
    /* the binary computes TABLE minus POINTER here */
    e->buf = s->buf == NULL ? 0 : (long)(mod_buftab - s->buf) + 1;
    e->ovl = s->ovl == NULL ? 0 : (long)(mod_ovltab - s->ovl) + 1;
    e->unk_3c = s->scnum;
    e->sdi = s->sdi_cnt;
    if (!(e->flags & EXPR_REL) ||
        (e->sect == cur_rsecid && run_ctr == load_ctr && buf_type == 0)) {
        emit_value_text(e);
    } else {
        cf_room();
        strcpy(cform_ptr, name);
        cform_ptr += strlen(cform_ptr);
    }
    return e;
}

/* 0040af6e */
static EXPR *parse_term(void)
{
    EXPR *e;
    unsigned long l44, l14, lc;
    long ndig, len, i;
    int d;
    char *p;

    cf_room();
    if (*input_cursor == '+') {
        cf_copy();
        e = parse_term();
        if (e != NULL)
            return e;
        return NULL;
    }
    if (*input_cursor == '-') {
        cf_copy();
        e = parse_term();
        if (e == NULL)
            return NULL;
        negate_value(e);
        return e;
    }
    if (*input_cursor == '~') {
        cf_copy();
        e = parse_term();
        if (e == NULL)
            return NULL;
        if (e->type == EXPR_INT) {
            complement_value(e);
            return e;
        }
        lnk_error1("Illegal operator for floating point element");
        free_expr(e);
        return NULL;
    }
    if (*input_cursor == '!') {
        cf_copy();
        e = parse_term();
        if (e == NULL)
            return NULL;
        op_not(e);
        return e;
    }
    if (*input_cursor == '(') {
        cf_copy();
        e = parse_expr();
        if (e == NULL)
            return NULL;
        if (*input_cursor != ')') {
            free_expr(e);
            lnk_error1("Missing ')' in expression");
            return NULL;
        }
        cf_copy();
        return e;
    }
    if (*input_cursor == '[')
        return parse_bracket();
    if (*input_cursor == '{') {
        cf_copy();
        err_symbol[0] = 0;
        in_brace = 1;
        e = parse_expr();
        in_brace = 0;
        if (e == NULL) {
            in_brace = 0;
            return NULL;
        }
        if (*input_cursor != '}') {
            free_expr(e);
            lnk_error1("Missing '}' in expression");
            return NULL;
        }
        cf_copy();
        return e;
    }

    e = new_expr();
    ndig = 0;
    l44 = 0;
    l14 = 0;
    lc = 0;

    /* binary constant */
    if (*input_cursor == '%' ||
        (radix == 2 && (*input_cursor == '0' || *input_cursor == '1'))) {
        if (*input_cursor == '%')
            cf_copy();
        for (; *input_cursor == '0' || *input_cursor == '1'; input_cursor++) {
            ndig++;
            if (dword_bits < ndig) {
                lc = M32(lc * 2);
                if (l14 & sign_bit)
                    lc = M32(lc + 1);
                l14 = l14 & ~sign_bit & word_mask;
            }
            if (word_bits < ndig) {
                l14 = M32(l14 * 2);
                if (l44 & sign_bit)
                    l14 = M32(l14 + 1);
                l44 = l44 & ~sign_bit & word_mask;
            }
            l44 = M32((unsigned long)(*input_cursor - '0') + l44 * 2);
            cf_room();
            *cform_ptr++ = *input_cursor;
        }
        lc &= word_mask;
        if (word_bits < ndig) {
            e->size = fmt_dword;
        } else if (ndig == 0) {
            free_expr(e);
            lnk_error1("Binary constant expected");
            return NULL;
        }
        e->hi = lc;
        e->mid = l14;
        e->lo = l44;
        return e;
    }

    /* hexadecimal constant */
    if (*input_cursor == '$' ||
        (radix == 16 && isxdigit((unsigned char)*input_cursor))) {
        if (*input_cursor == '$' || *input_cursor == '0')
            cf_copy();
        if (tolower((unsigned char)*input_cursor) == 'x')
            cf_copy();
        while (isxdigit((unsigned char)*input_cursor)) {
            ndig++;
            if (dword_hexdig < ndig)
                lc = M32(lc << 4 | (l14 >> (int)((word_bits - 4) & 31)));
            if (word_hexdig < ndig)
                l14 = M32(l14 << 4 | (l44 >> (int)((word_bits - 4) & 31)));
            l44 = M32(l44 << 4);
            if (*input_cursor < ':')
                d = *input_cursor - '0';
            else
                d = tolower((unsigned char)*input_cursor) - 0x57;
            l44 = M32(l44 + (unsigned long)(long)d);
            cf_copy();
        }
        lc &= word_mask;
        if (word_hexdig < ndig) {
            e->size = fmt_dword;
        } else if (ndig == 0) {
            free_expr(e);
            lnk_error1("Hex constant expected");
            return NULL;
        }
        e->hi = lc;
        e->mid = l14;
        e->lo = l44;
        return e;
    }

    /* decimal / floating constant */
    if (*input_cursor == '`' ||
        (radix == 10 && (isdigit((unsigned char)*input_cursor) || *input_cursor == '.')))
        return parse_decimal(e);

    /* location counter */
    if (*input_cursor == '*') {
        input_cursor++;
        e->lo = *run_ctr;
        e->space = run_spec.mspace;
        e->map = run_spec.mmap;
        e->ctr = run_spec.mcntr;
        e->attr = run_spec.mclass;
        if (!in_brace && two_words)
            e->lo = M32(e->lo + 1);
        if (target_index == TGT_56800 && run_spec.mspace == 0) {
            e->mid = ((M32(e->lo & ~word_mask)) >> (int)(word_bits & 31)) & 0xf;
            e->lo &= word_mask;
            e->size = fmt_dword;
        }
        if (target_index == TGT_SC100 && run_spec.mspace == 0) {
            e->mid = ((M32(e->lo & ~word_mask)) >> (int)(word_bits & 31)) & word_mask;
            e->lo &= word_mask;
            e->size = fmt_dword;
        }
        e->flags |= EXPR_REL;
        e->sect = cur_secid;
        e->rsect = cur_rsecid;
        e->buf = buf_type != 0 ? cur_buffer : 0;
        e->ovl = ovl_mem.mspace != MS_N ? cur_overlay : 0;
        e->sdi = (mod_sdi && run_spec.mspace == 0) ? out_nsdi : 0;
        emit_value_text(e);
        return e;
    }

    /* quoted string constant */
    if (*input_cursor == '\'' || *input_cursor == '"') {
        input_cursor = get_string(input_cursor, namebuf);
        if (input_cursor == NULL) {
            free_expr(e);
            return NULL;
        }
        len = (long)strlen(namebuf);
        if (fmt_dword < len) {
            len = fmt_dword;
            lnk_warning1("String truncated in expression evaluation");
        }
        cf_room();
        *cform_ptr++ = '\'';
        memcpy(cform_ptr, namebuf, (size_t)len);
        cform_ptr += len;
        *cform_ptr++ = '\'';
        p = namebuf;
        for (i = 0; i < len; i++) {
            if (fmt_word < i) {
                l14 = M32(l14 << 8 | (l44 >> (int)((word_bits - 8) & 31)));
                l44 &= word_mask >> 8;
            }
            l44 = M32(l44 * 0x100 + (unsigned long)(long)(signed char)*p);
            p++;
        }
        if (fmt_dword < len)
            e->size = fmt_dword;
        else
            e->size = len;
        e->hi = 0;
        e->mid = l14;
        e->lo = l44;
        return e;
    }

    /* @function */
    if (*input_cursor == '@') {
        cf_copy();
        return func_call_eval(e);
    }

    return parse_symbol(e);
}

/* 0040c749: canonical text of a value: [$HHHHHH:$MMMMCCCC] */
static void emit_value_text(EXPR *e)
{
    char *buf;

    cf_room();
    if (e->flags & EXPR_REL)
        *cform_ptr++ = '[';
    if (e->type == EXPR_INT) {
        *cform_ptr = '$';
        buf = cform_ptr + 1;
        if (e->size == fmt_word)
            sprintf(buf, word_fmt, e->lo & word_mask);
        else
            sprintf(buf, "%0*lX%0*lX", (int)word_digits, e->mid & word_mask,
                    (int)word_digits, e->lo & word_mask);
        sprintf(buf + strlen(buf), ":$%08lX",
                M32(((unsigned long)e->map << 16) | (unsigned long)e->ctr));
    } else {
        /* the original passes the text "-.15E" (no '%') as the format */
        fmt_double(cform_ptr, "-.15E", e->fval);
    }
    cform_ptr += strlen(cform_ptr);
    if (e->flags & EXPR_REL)
        *cform_ptr++ = ']';
}

/* 0040c8ab */
void classify_value(EXPR *e)
{
    if (e->type == EXPR_FLT)
        e->size = EXPR_SIZE_FLT;
    else if (e->mid == 0 || e->mid == word_mask ||
             (e->space != MS_N &&
              ((target_index != TGT_56800 && target_index != TGT_SC100) || e->space != 0)))
        e->size = fmt_word;
    else
        e->size = fmt_dword;
}

/* 0040c91d */
EXPR *new_expr(void)
{
    EXPR *e;
    long used;

    if (expr_stack == NULL) {
        expr_stack = (EXPR **)xmalloc((unsigned long)expr_stack_max * sizeof(EXPR *));
        expr_sp = expr_stack;
    }
    if (expr_sp >= expr_stack + expr_stack_max) {
        used = (long)(expr_sp - expr_stack);
        expr_stack_max <<= 1;
        expr_stack = (EXPR **)xrealloc(expr_stack,
                                       (unsigned long)expr_stack_max * sizeof(EXPR *));
        expr_sp = expr_stack + used;
    }
    e = (EXPR *)xmalloc((unsigned long)sizeof(EXPR));
    e->lo = 0;
    e->mid = 0;
    e->hi = 0;
    e->unk_0c = 0;
    e->type = EXPR_INT;
    e->map = MS_N;
    e->space = MS_N;
    e->ctr = 0;
    e->attr = 0;
    e->size = fmt_word;
    e->flags = 0;
    e->sect = 0;
    e->rsect = -1;
    e->buf = 0;
    e->ovl = 0;
    e->unk_3c = -1;
    e->sdi = 0;
    e->unk_44 = 0;
    e->fval = 0.0;
    *expr_sp++ = e;
    return e;
}

/* 0040ca80.  The original only decrements expr_sp; the port removes the
   given entry so the stack never holds stale pointers (no visible change). */
void free_expr(EXPR *e)
{
    EXPR **p;

    if (e == NULL)
        return;
    if (expr_sp == expr_stack)
        lnk_fatal1("Expression stack underflow");
    for (p = expr_sp - 1; p >= expr_stack; p--) {
        if (*p == e) {
            *p = expr_sp[-1];
            break;
        }
    }
    expr_sp--;
    xfree(e);
}

/* 0040cac2: longjmp path of eval_expr */
void free_expr_stack_all(void)
{
    while (expr_sp != expr_stack) {
        expr_sp--;
        xfree(*expr_sp);
    }
}
