/*
 * ASM56000.EXE (CLAS56 v6.3.0) - amode.c 1.18: operand / addressing mode
 * parser, with the small util.c helpers it depends on (get_force,
 * get_mem_space, check_extra_operand, skip_symbol, merge_mem_space).
 *
 * The operand scan pointer is CurInstrFieldMsg (the original "optr"); the
 * error routines derive the "(... field)" suffix from where it points.
 * OPERAND is 8 words plus the relocation-expression pointer (see
 * asm56000.h): mode, space, fwd, force, value, reg, sect, (unused), cform.
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "asm56000.h"

extern void fatal(char *msg);
extern char NoErrors;
extern char InLineReplay;
extern unsigned long ErrOnThisLine;
extern int ErrMultiple;

#define optr CurInstrFieldMsg

#define OP_MODE  ASM56000_OP_MODE
#define OP_SPACE ASM56000_OP_SPACE
#define OP_FWD   ASM56000_OP_FWD
#define OP_FORCE ASM56000_OP_FORCE
#define OP_VALUE ASM56000_OP_VALUE
#define OP_REG   ASM56000_OP_REG
#define OP_SECT  ASM56000_OP_SECT
#define OP_CFORM ASM56000_OP_CFORM

#define FORCE_LONG  0x1000000UL
#define FORCE_SHORT 0x2000000UL
#define FORCE_IO    0x4000000UL

#define SPACE_ERROR 0xa2c2aUL

/* state shared with procop.c / procxy.c */
unsigned long HazardCur;
unsigned long HazardPrev;
unsigned long DestRegMask;
unsigned long AregWritten;
unsigned long AregWrittenPrev;
long LastSrcReg;
unsigned long AregWritePc;
int CtrlRegAccessed;
long PrevInstrWords;
int OptMsw;
int OptPsb = 1;
int InsertingNop;
unsigned long RtAddrMask = 0xffffUL;
int CModeFlag;
void (*RegNoteHook)(void);

static int OptRp;

struct forward_expression {
    char *text;
    unsigned long line;
};

static struct forward_expression ForwardExpressions[256];
static unsigned long ForwardExpressionCount;

static int forward_expression_seen(char *text)
{
    unsigned long i;

    if (text == (char *)0)
        return 0;
    for (i = 0UL; i < ForwardExpressionCount; ++i)
        if (ForwardExpressions[i].line == LineNo &&
            strcmp(ForwardExpressions[i].text, text) == 0)
            return 1;
    return 0;
}

static void remember_forward_expression(char *text)
{
    if (text == (char *)0 || *text == '\0' ||
        forward_expression_seen(text) || ForwardExpressionCount >= 256UL)
        return;
    ForwardExpressions[ForwardExpressionCount].text =
        (char *)xmalloc((unsigned long)strlen(text) + 1UL);
    strcpy(ForwardExpressions[ForwardExpressionCount].text, text);
    ForwardExpressions[ForwardExpressionCount].line = LineNo;
    ++ForwardExpressionCount;
}

static unsigned long opword(void *op, unsigned offset)
{
    return *(unsigned long *)((char *)op + offset);
}

static void putop(void *op, unsigned offset, unsigned long value)
{
    *(unsigned long *)((char *)op + offset) = value;
}

static void free_cform(void *op)
{
    char **c;

    c = (char **)((char *)op + OP_CFORM);
    if (*c != (char *)0) {
        xfree(*c);
        *c = (char *)0;
    }
}

/* ------------------------------------------------------------------ */
/* util.c helpers                                                      */

static int is_scs_temporary(char *name)
{
    return !AbsoluteMode && name != (char *)0 && strncmp(name, "Z_L", 3) == 0;
}

/* 0043ae13: parse a '<', '<<' or '>' force prefix at optr. */
unsigned long get_force(unsigned long allowed)
{
    char *save;

    save = optr;
    if (*optr == '<') {
        if (optr[1] == '<') {
            if ((allowed & FORCE_IO) == 0UL) {
                optr = optr + 1;
                err("I/O short addressing mode not allowed");
                optr = save;
                return 0xffffffffUL;
            }
            optr += 2;
            return FORCE_IO;
        }
        optr = optr + 1;
        return FORCE_SHORT;
    }
    if (*optr == '>') {
        ++optr;
        return FORCE_LONG;
    }
    return ForceMode;
}

/* 0043a807: memory space letter to space code. */
static unsigned long space_from_char(int c)
{
    switch (tolower(c)) {
    case 'l': return 3UL;
    case 'n': return 4UL;
    case 'p': return 0UL;
    case 'x': return 1UL;
    case 'y': return 2UL;
    default: return SPACE_ERROR;
    }
}

/* 0043baf1 */
unsigned long merge_mem_space(unsigned long a, unsigned long b)
{
    switch (a) {
    case 0:
        return b == 0UL || b == 4UL ? 0UL : SPACE_ERROR;
    case 1:
        return b == 2UL || b == 0UL ? SPACE_ERROR : 1UL;
    case 2:
        return b == 1UL || b == 0UL ? SPACE_ERROR : 2UL;
    case 3:
        if (b == 0UL)
            return SPACE_ERROR;
        if (b == 1UL || b == 2UL)
            return b;
        return 3UL;
    default:
        return b;
    }
}

/* 00439c56: parse an optional "x:" style prefix at optr into op.space and
   check it against the allowed set. */
int get_mem_space(void *op, int allowed)
{
    unsigned long space;

    space = 4UL;
    if (optr != (char *)0 && *optr != '\0' && optr[1] == ':') {
        space = space_from_char((unsigned char)*optr);
        optr += 2;
        if (space == SPACE_ERROR) {
            err("Illegal memory space specified");
            return 0;
        }
    }
    putop(op, OP_SPACE, space);
    switch (allowed) {
    case 0: if (space == 4UL) return 1; break;
    case 1: if (space == 1UL) return 1; break;
    case 2: if (space == 2UL) return 1; break;
    case 3: if (space == 3UL) return 1; break;
    case 4: if (space == 0UL) return 1; break;
    case 5: if (space == 1UL || space == 2UL) return 1; break;
    case 6:
        if (space == 1UL || space == 2UL || space == 3UL ||
            space == 0UL || space == 4UL)
            return 1;
        break;
    case 7: if (space == 1UL || space == 2UL || space == 4UL) return 1; break;
    case 8: if (space == 2UL || space == 4UL) return 1; break;
    case 9:
        if (space == 1UL || space == 2UL || space == 0UL ||
            space == 4UL)
            return 1;
        break;
    default: break;
    }
    switch (space) {
    case 0: err("Illegal memory space specified - P:"); break;
    case 1: err("Illegal memory space specified - X:"); break;
    case 2: err("Illegal memory space specified - Y:"); break;
    case 3: err("Illegal memory space specified - L:"); break;
    default: err("Missing or illegal memory space specifier");
    }
    return 0;
}

/* 0043bccb: the Y field must be empty. */
int check_extra_operand(void)
{
    char *save;
    char c;

    save = optr;
    c = *Op3Field;
    if (c != '\0') {
        optr = Op3Field;
        err("Too many fields specified for instruction");
        err("Possible invalid white space between operands or arguments");
    }
    optr = save;
    return c == '\0';
}

/* 0043bc1b */
void skip_symbol(void)
{
    if (optr != (char *)0) {
        while (*optr != '\0' && (isalnum((unsigned char)*optr) ||
                                 *optr == '_'))
            ++optr;
        if (*optr == ',')
            ++optr;
    }
}

/* ------------------------------------------------------------------ */
/* expression evaluation at optr                                       */

struct ev {
    unsigned long value;
    unsigned long flags;   /* W6: 0x8000000 forward, 0x1000 reloc, 0x100000 float */
    unsigned long unres;   /* value still unresolved (W6 & 0x8000000 only) */
    long sect;
    unsigned long space;
    int is_float;
    double dval;
};

#define EV_FWD    0x8000000UL
#define EV_RELOC  0x1000UL
#define EV_FROMFLT 0x100000UL

/* Scan the extent of the expression at optr: it ends at a ',' or an
   unmatched ')' / ']' outside parentheses and quotes. */
static char *expr_end(char *p)
{
    int depth;
    char quote;

    depth = 0;
    quote = '\0';
    for (; *p != '\0'; ++p) {
        if (quote != '\0') {
            if (*p == quote)
                quote = '\0';
            continue;
        }
        if (*p == '\'' || *p == '"')
            quote = *p;
        else if (*p == '(')
            ++depth;
        else if (*p == ')') {
            if (depth == 0)
                break;
            --depth;
        } else if (*p == ']')
            break;
        else if (*p == ',' && depth == 0)
            break;
    }
    return p;
}

static void report_expr_error(char *text)
{
    char function_name[64];
    char *p;
    char *q;
    unsigned long n;

    switch (expr_last_error()) {
    case 2:
        err("Extra characters beyond expression");
        break;
    case 3:
        err("Missing ')' in expression");
        break;
    case 4:
        p = text;
        while (*p != '\0' && *p != '@')
            ++p;
        if (*p == '@')
            ++p;
        q = p;
        while (isalpha((unsigned char)*q))
            ++q;
        n = (unsigned long)(q - p);
        if (n >= sizeof(function_name))
            n = sizeof(function_name) - 1UL;
        memcpy(function_name, p, n);
        function_name[n] = '\0';
        err_s("Invalid function name", function_name);
        break;
    case 5:
        err("Illegal operator for floating point element");
        break;
    case 6:
        err("Expression involves incompatible memory spaces");
        break;
    default:
        err("Symbols must start with alphabetic character");
        break;
    }
}

/* Find the next symbol reference in an expression text: numbers, "$"/"%"
   constants, @functions and quoted strings are skipped.  Returns the
   position after the symbol (its text in name) or NULL. */
static char *scan_symbol(char *p, char *name, unsigned size, char **start)
{
    char quote;
    unsigned n;

    quote = '\0';
    while (*p != '\0') {
        if (quote != '\0') {
            if (*p == quote)
                quote = '\0';
            ++p;
        } else if (*p == '\'' || *p == '"') {
            quote = *p++;
        } else if (*p == '$' || *p == '%' || *p == '@' || *p == '`') {
            ++p;
            while (isalnum((unsigned char)*p) || *p == '_')
                ++p;
        } else if (isdigit((unsigned char)*p)) {
            while (isalnum((unsigned char)*p) || *p == '.')
                ++p;
        } else if (isalpha((unsigned char)*p) || *p == '_') {
            *start = p;
            n = 0U;
            while (isalnum((unsigned char)*p) || *p == '_' || *p == '.') {
                if (n + 1U < size)
                    name[n++] = *p;
                ++p;
            }
            name[n] = '\0';
            return p;
        } else {
            ++p;
        }
    }
    return (char *)0;
}

/* "Reserved name used for symbol name": a register name used as a symbol
   (get_symbol_name, 0043b448/0043b5bb). */
static int reserved_symbol_used(char *text, char **where)
{
    char name[130];
    char *p;
    char *sym_start;
    char *q;

    p = text;
    while ((p = scan_symbol(p, name, sizeof name, &sym_start)) != (char *)0) {
        q = name;
        if (match_register_name(&q) != -1 && *q == '\0') {
            *where = sym_start;
            return 1;
        }
    }
    return 0;
}

/* first symbol of the expression text that is undefined (pass 2) */
static char *first_undefined(char *text, char *name)
{
    char *p;
    char *sym_start;

    p = text;
    while ((p = scan_symbol(p, name, 130U, &sym_start)) != (char *)0)
        if (sym_lookup(name, 0) == (void *)0)
            return sym_start;
    return (char *)0;
}

/* eval_expr (00414862): evaluate the expression at optr, advance optr
   past it.  Returns the raw evaluator value or NULL (error reported). */
static void *eval_here(char **textp)
{
    char *start;
    char *end;
    char *buf;
    void *v;
    unsigned long n;

    start = optr;
    if (*start == '\0') {
        err("Missing expression");
        err("Possible invalid white space between operands or arguments");
        return (void *)0;
    }
    end = expr_end(start);
    n = (unsigned long)(end - start);
    buf = (char *)xmalloc(n + 1UL);
    memcpy(buf, start, n);
    buf[n] = '\0';
    {
        char *where;

        if (reserved_symbol_used(buf, &where)) {
            char sname[130];
            char *q;
            unsigned k;

            k = 0U;
            for (q = where; (isalnum((unsigned char)*q) || *q == '_' ||
                             *q == '.') && k < 129U; ++q)
                sname[k++] = *q;
            sname[k] = '\0';
            optr = start + (where - buf);
            err_s("Reserved name used for symbol name", sname);
            optr = start;
            xfree(buf);
            return (void *)0;
        }
    }
    v = eval_expr_text(buf);
    if (v == (void *)0) {
        char uname[130];
        char *upos;

        if (n == 0UL) {
            err("Symbols must start with alphabetic character");
        } else if (Pass == 2UL && AbsoluteMode &&
                   (upos = first_undefined(buf, uname)) != (char *)0 &&
                   !is_scs_temporary(uname)) {
            optr = start + (upos - buf);
            err_s("Symbol undefined on pass 2", uname);
            optr = start;
        } else {
            report_expr_error(buf);
        }
        xfree(buf);
        return (void *)0;
    }
    if (Pass == 2UL && expr_is_unresolved(v)) {
        char *name;

        name = expr_unresolved_name(buf);
        if (name[0] == '\0') {
            free_expr(v);
            xfree(buf);
            return (void *)0;
        }
        if (!is_scs_temporary(name) && AbsoluteMode) {
            /* relocatable mode: an undefined symbol is an external
               reference resolved by the linker */
            err_s("Symbol undefined on pass 2", name);
            free_expr(v);
            xfree(buf);
            return (void *)0;
        }
    }
    if (Pass == 1UL && expr_is_unresolved(v))
        remember_forward_expression(buf);
    optr = end;
    if (textp != (char **)0)
        *textp = buf;
    else
        xfree(buf);
    return v;
}

/* Relocation string of the expression evaluated last (original DAT_0045f428
   text); kept for the operand under construction. */
static char *EvReloc;

static void save_reloc(void *v)
{
    char *t;

    xfree(EvReloc);
    EvReloc = (char *)0;
    if (Pass != 2UL || AbsoluteMode || !expr_is_reloc(v))
        return;
    t = eval_reloc_text();
    if (t == (char *)0)
        return;
    EvReloc = (char *)xmalloc((unsigned long)strlen(t) + 1UL);
    strcpy(EvReloc, t);
}

/* 004094bb: relocation string of an address or immediate operand,
   "[line!]expression@space#mode". */
static char *make_cform(void *op, unsigned long mode)
{
    char *buf;
    int kind;
    int sp;
    unsigned long space;

    if (EvReloc == (char *)0)
        return (char *)0;
    space = opword(op, OP_SPACE);
    sp = space == 0UL ? 4 : space == 1UL ? 1 : space == 2UL ? 2 :
         space == 3UL ? 3 : 0;
    switch (mode) {
    case 10UL: kind = 12; break;
    case 11UL: kind = 8; break;
    case 12UL: kind = 1; break;
    case 13UL: kind = -1; break;
    case 15UL: kind = 12; break;
    case 16UL: kind = 6; break;
    case 17UL: kind = 0x56; break;
    default: kind = 0; break;
    }
    buf = (char *)xmalloc((unsigned long)strlen(EvReloc) + 64UL);
    if (kind == 0)
        sprintf(buf, "%s@%d#%d", EvReloc, sp, 0);
    else
        sprintf(buf, "%ld!%s@%d#%d", (long)LineNo, EvReloc, sp, kind);
    return buf;
}

static void ev_fill(struct ev *e, void *v, char *text)
{
    unsigned long *w;

    save_reloc(v);
    w = (unsigned long *)v;
    e->flags = w[ASM56000_EXPR_W6 / 4];
    e->unres = e->flags & EV_FWD;
    if (Pass == 2UL && forward_expression_seen(text))
        e->flags |= EV_FWD;
    e->sect = (long)w[ASM56000_EXPR_W15 / 4];
    e->space = w[ASM56000_EXPR_W7 / 4];
    e->is_float = w[ASM56000_EXPR_W4 / 4] == 0x200UL;
    e->dval = 0.0;
    if (e->is_float)
        e->dval = expr_as_double(v);
    e->value = expr_as_int32(v);
}

/* 0040b6bf: double to 24 bit fraction. */
static unsigned long float_to_frac24(double d)
{
    double t;
    long l;

    if (d >= -1.0) {
        if (d < 1.0) {
            t = d * 8388608.0;
            l = (long)(t >= 0.0 ? t + 0.5 : t - 0.5);
            if ((t >= 0.0 ? t + 0.5 : t - 0.5) - (double)l == 0.0)
                l &= ~1L;
            if (l > 0x7fffffL)
                l = 0x7fffffL;
            return (unsigned long)l & 0xffffffUL;
        }
        warn("Expression value outside fractional domain");
        return 0x7fffffUL;
    }
    warn("Expression value outside fractional domain");
    return 0xff800000UL;
}

/* 004141b1 expr_to_int24 + the float part of get_imm_expr (00407462).
   Returns 1 with *e filled, 0 on error. */
static int get_imm_expr_ev(int immclass, struct ev *e)
{
    void *v;
    char *text;
    long sv;
    unsigned long mag;
    int bad;

    v = eval_here(&text);
    if (v == (void *)0)
        return 0;
    ev_fill(e, v, text);
    xfree(text);
    free_expr(v);
    if (!e->is_float) {
        sv = (long)e->value;
        mag = sv < 0L ? (unsigned long)(-sv) : (unsigned long)sv;
        if (OptPsb == 0)
            bad = sv < -0x1000000L || mag > 0xffffffUL;
        else
            bad = sv < -0x800000L || mag > 0xffffffUL;
        if (bad) {
            err("Expression result too large");
            return 0;
        }
        if (sv < 0L && immclass != 5 && immclass != 1 && immclass != 6) {
            err("Negative immediate value not allowed");
            return 0;
        }
        return 1;
    }
    if (immclass == 1 || immclass == 6) {
        e->value = float_to_frac24(e->dval);
        e->flags |= EV_FROMFLT;
        e->is_float = 0;
        return 1;
    }
    err("Floating point value not allowed");
    return 0;
}

void *get_imm_expr(int immclass)
{
    (void)immclass;
    return (void *)0;
}

/* 00413c50 expr_to_uint_bits */
static int get_uint_expr_ev(unsigned long mask, struct ev *e)
{
    void *v;
    char *text;

    v = eval_here(&text);
    if (v == (void *)0)
        return 0;
    ev_fill(e, v, text);
    xfree(text);
    free_expr(v);
    if (e->is_float) {
        err("Expression result must be integer");
        return 0;
    }
    if (!CModeFlag) {
        if (mask < e->value) {
            err("Expression result too large");
            return 0;
        }
    } else
        e->value &= mask;
    return 1;
}

/* ------------------------------------------------------------------ */
/* register parsing                                                    */

int parse_addr_reg(void)
{
    int reg;

    reg = match_register_name(&optr);
    if (reg == -1)
        return -1;
    if (reg < 14 || reg > 21)
        return -1;
    return reg;
}

int parse_offset_reg(int areg)
{
    int reg;

    reg = match_register_name(&optr);
    if (reg == -1) {
        if (*optr == 'N' || *optr == 'n') {
            ++optr;
            return 1;
        }
        return 0;
    }
    if (reg < 22 || reg > 29) {
        err("Invalid register specified for offset");
        return 0;
    }
    if (reg - 22 == areg - 14)
        return 1;
    err("Offset register number must be the same as address register number");
    return 0;
}

static char *RegNames[] = {
    "x", "y", "a", "b", "x0", "y0", "x1", "y1", "a0", "b0", "a1", "b1",
    "a2", "b2", "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
    "n0", "n1", "n2", "n3", "n4", "n5", "n6", "n7",
    "m0", "m1", "m2", "m3", "m4", "m5", "m6", "m7",
    "ab", "ba", "a10", "b10", "omr", "sr", "la", "lc", "ssh", "ssl", "sp",
    "mr", "ccr"
};

char *register_name(int id)
{
    if (id < 0 || id > 50)
        return (char *)"";
    return RegNames[id];
}

/* 0040641c */
int amode_register(int regclass, void *op)
{
    int r;
    int ok;

    r = match_register_name(&optr);
    if (r == -1)
        return 0;
    switch (regclass) {
    case 1: ok = r == 2 || r == 3; break;
    case 2: ok = r == 5 || r == 7; break;
    case 3: ok = r == 4 || r == 6 || r == 2 || r == 3; break;
    case 4: ok = r == 5 || r == 7 || r == 2 || r == 3; break;
    case 5: ok = r == 0 || r == 1 || r == 2 || r == 3 ||
                 (r > 0x25 && r < 0x2a); break;
    case 6: ok = (r >= 2 && r <= 0x25) || (r >= 0x2a && r <= 0x30); break;
    case 7: ok = r >= 0x2a && r <= 0x30; break;
    case 8: ok = r == 0x1e || r == 0x1f; break;
    case 9: ok = (r >= 2 && r <= 7) || (r >= 0xe && r <= 0x1d); break;
    case 10: ok = r == 0 || r == 1; break;
    case 0xb: ok = r >= 4 && r <= 7; break;
    case 0xc: ok = r == 0 || r == 1 || (r > 3 && r < 8); break;
    case 0xd: ok = r == 2; break;
    case 0xe: ok = r == 3; break;
    case 0xf: ok = r >= 2 && r <= 7; break;
    case 0x10: ok = r >= 0xe && r <= 0x15; break;
    case 0x11: ok = (r >= 2 && r <= 0x25) || (r >= 0x2a && r <= 0x30); break;
    case 0x12: ok = r >= 0 && r <= 0x30; break;
    case 0x13: ok = r == 0x31 || r == 0x32 || r == 0x2a; break;
    case 0x14: ok = r >= 0xe && r <= 0x1d; break;
    case 0x15: ok = r >= 0 && r <= 7; break;
    case 0x16: ok = r == 4 || r == 2 || r == 3; break;
    case 0x17: ok = r == 4 || r == 5 || r == 7 || r == 2 || r == 3; break;
    case 0x18:
        ok = r == 2 || r == 3 || r == 10 || r == 0xb;
        if (r == 10)
            r = 2;
        else if (r == 0xb)
            r = 3;
        break;
    default: ok = 0; break;
    }
    if (ok) {
        putop(op, OP_MODE, 1UL);
        putop(op, OP_REG, (unsigned long)r);
        return 1;
    }
    if (regclass == 0)
        err("Register direct addressing not allowed");
    else
        err_s("Invalid register specified", register_name(r));
    return -1;
}

/* 00406aaf */
static int check_dup_dest(int regclass, int reg)
{
    unsigned long m;

    switch (reg) {
    case 2: m = regclass != 0x18 ? 7UL : 2UL; break;
    case 3: m = regclass != 0x18 ? 0x70UL : 0x20UL; break;
    case 8: m = 1UL; break;
    case 9: m = 0x10UL; break;
    case 10: m = 2UL; break;
    case 11: m = 0x20UL; break;
    case 12: m = 4UL; break;
    case 13: m = 0x40UL; break;
    case 0x26: m = 0x66UL; break;
    case 0x27: m = 0x66UL; break;
    case 0x28: m = 3UL; break;
    case 0x29: m = 0x30UL; break;
    default: return 0;
    }
    if ((m & DestRegMask) == 0UL) {
        DestRegMask |= m;
        return 0;
    }
    err("Duplicate destination register not allowed");
    return 1;
}

/* 00406938 */
static int note_reg_direct(unsigned long flags, int regclass, int reg)
{
    if (!CtrlRegAccessed)
        CtrlRegAccessed = (reg >= 0x1e && reg <= 0x25) ||
                          (reg >= 0x2a && reg <= 0x32);
    if ((flags & 2UL) == 0UL) {
        LastSrcReg = reg;
    } else {
        if (reg > 13 && reg < 0x26 && reg != LastSrcReg) {
            AregWritten |= 1UL << (unsigned)((reg - 14) & 31);
            AregWritePc = CurrentAddress;
        }
        if (check_dup_dest(regclass, reg))
            return 0;
    }
    return 1;
}

/* 004069eb */
void check_areg_stall(int reg, int mode)
{
    unsigned long bit;
    unsigned long m;

    bit = 1UL << (unsigned)((reg - 14) & 31);
    m = bit;
    if (mode > 4 && mode < 8)
        m = bit | (bit << 8);
    if (mode > 2 && mode < 9)
        m |= bit << 16;
    if ((AregWrittenPrev & m) != 0UL &&
        (CurrentAddress == AregWritePc + (unsigned long)PrevInstrWords ||
         InLineReplay)) {
        if (!OptRp || InLineReplay || ErrOnThisLine != 0UL)
            err("Contents of register written in previous instruction not available");
        else if (RegNoteHook != (void (*)(void))0)
            RegNoteHook();
    }
}

/* ------------------------------------------------------------------ */
/* indirect addressing                                                 */

/* 00406bfa */
int amode_indirect(int eaclass, void *op)
{
    char *save;
    char c;
    int reg;
    int r;

    save = optr;
    if (*optr == '-' && optr[1] == '(') {
        optr += 2;
        reg = parse_addr_reg();
        putop(op, OP_REG, (unsigned long)reg);
        if (reg == -1) {
            optr = save;
            return 0;
        }
        c = *optr;
        ++optr;
        if (c == ')') {
            if (eaclass == 1) {
                putop(op, OP_MODE, 8UL);
                return 1;
            }
            err("Pre-decrement addressing mode not allowed");
            return -1;
        }
        err("Address mode syntax error - expected ')'");
        return -1;
    }
    if (*optr != '(') {
        optr = save;
        return 0;
    }
    ++optr;
    reg = parse_addr_reg();
    putop(op, OP_REG, (unsigned long)reg);
    if (reg == -1) {
        optr = save;
        return 0;
    }
    if (*optr == '+') {
        ++optr;
        r = parse_offset_reg(reg);
        if (r == -1) {
            err("Address mode syntax error - probably missing ')'");
            return -1;
        }
        c = *optr;
        ++optr;
        if (c == ')') {
            if (*optr == ',' || *optr == '\0') {
                if (eaclass == 1) {
                    putop(op, OP_MODE, 7UL);
                    return 1;
                }
                err("Indexed address mode not allowed");
                return -1;
            }
            err("Address mode syntax error - expected comma or end of field");
            return -1;
        }
        err("Address mode syntax error - expected ')'");
        return -1;
    }
    {
        char *next;

        next = optr + 1;
        if (*optr == ')') {
            if (*next == '\0' || *next == ',') {
                if (eaclass == 1 || eaclass == 2) {
                    optr = next;
                    putop(op, OP_MODE, 2UL);
                    return 1;
                }
                optr = next;
                err("No-update mode not allowed");
                return -1;
            }
            if (*next == '+' || *next == '-') {
                c = *next;
                optr = optr + 2;
                if (*optr == '\0' || *optr == ',') {
                    putop(op, OP_MODE, c == '+' ? 3UL : 4UL);
                    return 1;
                }
                if (parse_offset_reg(reg) == 0) {
                    err("Address mode syntax error - probably missing ')'");
                    return -1;
                }
                if (*optr == '\0' || *optr == ',') {
                    if (c == '+') {
                        putop(op, OP_MODE, 5UL);
                        return 1;
                    }
                    if (eaclass == 1 || eaclass == 3) {
                        putop(op, OP_MODE, 6UL);
                        return 1;
                    }
                    err("Post-decrement by offset addressing mode not allowed");
                    return -1;
                }
                err("Address mode syntax error - expected comma or end of field");
                return -1;
            }
            optr = next;
            err("Address mode syntax error - expected '+' or '-'");
            return -1;
        }
        optr = next;
        err("Address mode syntax error - expected ')'");
        return -1;
    }
}

/* ------------------------------------------------------------------ */
/* immediate                                                           */

/* 00407511: is the next operand (after the comma) an ALU destination? */
static int imm_dest_is_alu(void)
{
    char saved_no_errors;
    char *save;
    unsigned long dummy[10];
    int r;
    char c;

    saved_no_errors = NoErrors;
    save = optr;
    NoErrors = 1;
    c = *optr;
    ++optr;
    if (c == ',') {
        r = amode_register(0xf, dummy);
        if (r != 1)
            r = 0;
    } else
        r = 0;
    optr = save;
    NoErrors = saved_no_errors;
    return r;
}

/* 00406f87 */
int amode_immediate(int immclass, void *op)
{
    struct ev e;
    unsigned long force;
    unsigned long v0;
    int from_float;
    int changed;
    int reloc;
    unsigned long mode;
    unsigned long value;
    unsigned long fwd;

    if (*optr != '#')
        return 0;
    if (immclass == 0) {
        err("Immediate addressing mode not allowed");
        while (*optr != '\0' && *optr != ',')
            ++optr;
        return -1;
    }
    ++optr;
    force = get_force(0x3000000UL);
    if (force == 0xffffffffUL)
        return -1;
    if (!get_imm_expr_ev(immclass, &e))
        return -1;
    from_float = (e.flags & EV_FROMFLT) != 0UL;
    v0 = e.value;
    if (*Op3Field == '\0' && (e.flags & EV_FWD) == 0UL &&
        force != FORCE_LONG && imm_dest_is_alu()) {
        if (!OptSi || v0 > 0xffUL || immclass != 6 || force == FORCE_SHORT) {
            if ((v0 & 0xffffUL) == 0UL)
                e.value = (unsigned long)((long)v0 >> 16) & 0xffUL;
        } else
            force = FORCE_LONG;
    }
    changed = !(v0 == e.value && v0 != 0UL);
    putop(op, OP_FORCE, force);
    putop(op, OP_VALUE, e.value);
    fwd = e.flags & EV_FWD;
    putop(op, OP_FWD, fwd);
    putop(op, 0x1cU, 0UL);
    reloc = (e.flags & EV_RELOC) != 0UL || e.sect < 0L;
    putop(op, OP_SECT, (unsigned long)e.sect);
    value = e.value;
    switch (immclass) {
    case 1:
        if (force == FORCE_SHORT)
            warn("Short immediate cannot be forced");
        mode = 9UL;
        break;
    case 2:
        if (force == FORCE_LONG)
            warn("Long immediate cannot be forced");
        mode = 10UL;
        if ((fwd == 0UL || Pass == 2UL) && value > 0xfffUL) {
            putop(op, OP_MODE, mode);
            err("Immediate value too large");
            return -1;
        }
        break;
    case 3:
        if (force == FORCE_LONG)
            warn("Long immediate cannot be forced");
        mode = 11UL;
        if ((fwd == 0UL || Pass == 2UL) && value > 0xffUL) {
            putop(op, OP_MODE, mode);
            err("Immediate value too large");
            return -1;
        }
        break;
    case 4:
        if (force == FORCE_LONG)
            warn("Long immediate cannot be forced");
        mode = 12UL;
        if ((fwd == 0UL || Pass == 2UL) && value > 0x17UL) {
            putop(op, OP_MODE, mode);
            err("Immediate value too large");
            return -1;
        }
        break;
    case 5: {
        unsigned long mag;

        if (force == FORCE_LONG)
            warn("Long immediate cannot be forced");
        mode = 13UL;
        mag = (long)value < 0L ? (unsigned long)(-(long)value) : value;
        if ((fwd == 0UL || Pass == 2UL) && mag > 0x17UL) {
            putop(op, OP_MODE, mode);
            err("Immediate value too large");
            return -1;
        }
        break;
    }
    case 6:
        if (force == FORCE_LONG) {
            mode = 9UL;
        } else if (force == FORCE_SHORT) {
            mode = 11UL;
            if (fwd == 0UL) {
                if (value > 0xffUL || (from_float && !changed)) {
                    mode = 9UL;
                    warn("Immediate value too large to use short - long substituted");
                }
            } else if (Pass == 2UL && value > 0xffUL) {
                putop(op, OP_MODE, mode);
                err("Immediate value too large to use short");
                return -1;
            }
        } else if (fwd != 0UL || reloc) {
            mode = 9UL;
        } else if (value > 0xffUL || (from_float && !changed)) {
            mode = 9UL;
        } else {
            mode = 11UL;
        }
        break;
    default:
        fatal("Immediate mode select failure");
        mode = 0UL;
        break;
    }
    putop(op, OP_MODE, mode);
    *(char **)((char *)op + OP_CFORM) = make_cform(op, mode);
    return 1;
}

/* ------------------------------------------------------------------ */
/* absolute                                                            */

static int in_io_range(unsigned long v)
{
    return v >= 0xffc0UL && v <= 0xffffUL;
}

/* 0040758c */
int amode_absolute(int absclass, void *op)
{
    struct ev e;
    unsigned long force;
    unsigned long value;
    unsigned long fwd;
    unsigned long mode;
    unsigned long space;
    int reloc;
    char *text;
    char *start;

    if (absclass == 0) {
        err("Absolute addressing mode not allowed");
        return -1;
    }
    force = get_force(0x7000000UL);
    if (force == 0xffffffffUL)
        return -1;
    putop(op, OP_FORCE, force);
    start = optr;
    if (!get_uint_expr_ev(RtAddrMask, &e))
        return -1;
    if (OptMsw && merge_mem_space(e.space, opword(op, OP_SPACE)) ==
        SPACE_ERROR)
        warn("Absolute address involves incompatible memory spaces");
    space = opword(op, OP_SPACE);
    if (e.space != 4UL && space == 4UL)
        putop(op, OP_SPACE, e.space);
    if (force == FORCE_IO && e.sect < 0L)
        value = 0xffc0UL;
    else
        value = e.value;
    putop(op, OP_VALUE, value);
    fwd = e.flags & EV_FWD;
    reloc = (e.flags & EV_RELOC) != 0UL || e.sect < 0L;
    if (!AbsoluteMode && !SectionGlobalCounters && force == 0UL) {
        /* relocatable code: an address inside a section is relocatable */
        char saved;
        char *end;

        end = optr;
        saved = *end;
        *end = '\0';
        if (sym_is_sectioned_name(start))
            reloc = 1;
        *end = saved;
    }
    putop(op, OP_FWD, fwd);
    putop(op, 0x1cU, 0UL);
    putop(op, OP_SECT, (unsigned long)e.sect);
    (void)text;
    switch (absclass) {
    case 1:
        if (force == FORCE_SHORT)
            warn("Short absolute address cannot be forced");
        else if (force == FORCE_IO)
            warn("I/O short absolute address cannot be forced");
        mode = 14UL;
        break;
    case 2:
        if (force == FORCE_LONG)
            warn("Long absolute address cannot be forced");
        else if (force == FORCE_SHORT)
            warn("Short absolute address cannot be forced");
        mode = 17UL;
        if ((fwd == 0UL || Pass == 2UL) && !InLineReplay &&
            !in_io_range(value)) {
            putop(op, OP_MODE, mode);
            err("Short I/O absolute address too small");
            return -1;
        }
        break;
    case 3:
        if (force == FORCE_LONG)
            warn("Long absolute address cannot be forced");
        else if (force == FORCE_IO)
            warn("I/O short absolute address cannot be forced");
        mode = 15UL;
        if ((fwd == 0UL || Pass == 2UL) && value > 0xfffUL) {
            putop(op, OP_MODE, mode);
            err("Short absolute address too large");
            return -1;
        }
        break;
    case 4:
        if (force == FORCE_LONG)
            warn("Long absolute address cannot be forced");
        else if (force == FORCE_IO)
            warn("I/O short absolute address cannot be forced");
        mode = 16UL;
        if ((fwd == 0UL || Pass == 2UL) && value > 0x3fUL) {
            putop(op, OP_MODE, mode);
            err("Short absolute address too large");
            return -1;
        }
        break;
    case 5:
        if (force == FORCE_LONG) {
            mode = 14UL;
        } else if (force == FORCE_SHORT) {
            mode = 15UL;
            if (fwd == 0UL) {
                if (value > 0xfffUL) {
                    mode = 14UL;
                    warn("Absolute address too large to use short - long substituted");
                }
            } else if (Pass == 2UL && value > 0xfffUL) {
                putop(op, OP_MODE, mode);
                err("Absolute address too large to use short");
                return -1;
            }
        } else if (fwd != 0UL || reloc) {
            mode = 14UL;
        } else if (value < 0x1000UL) {
            mode = 15UL;
        } else {
            mode = 14UL;
        }
        break;
    case 6:
        if (force == FORCE_LONG) {
            mode = 14UL;
        } else if (force == FORCE_IO) {
            mode = 17UL;
            if (value > 0x3fUL && value < 0x80UL) {
                value |= 0xffc0UL;
                putop(op, OP_VALUE, value);
            }
            if (fwd == 0UL) {
                if (!InLineReplay && !in_io_range(value)) {
                    mode = 14UL;
                    warn("Absolute address too small to use I/O short - long substituted");
                }
            } else if (Pass == 2UL && !InLineReplay && !in_io_range(value)) {
                putop(op, OP_MODE, mode);
                err("Absolute address too small to use I/O short");
                return -1;
            }
        } else if (force == FORCE_SHORT) {
            mode = 16UL;
            if (fwd == 0UL) {
                if (value > 0x3fUL) {
                    mode = 14UL;
                    warn("Absolute address too large to use short - long substituted");
                }
            } else if (Pass == 2UL && value > 0x3fUL) {
                putop(op, OP_MODE, mode);
                err("Absolute address too large to use short");
                return -1;
            }
        } else if (fwd != 0UL || reloc) {
            mode = 14UL;
        } else if (value < 0x40UL) {
            mode = 16UL;
        } else if (!InLineReplay && !in_io_range(value)) {
            mode = 14UL;
        } else {
            mode = 17UL;
        }
        break;
    case 7:
        if (force == FORCE_LONG) {
            if (fwd == 0UL) {
                if (value < 0x40UL) {
                    warn("Long absolute address cannot be forced - substituting short addressing");
                    mode = 16UL;
                } else {
                    if (!InLineReplay && !in_io_range(value)) {
                        putop(op, OP_MODE, 14UL);
                        err("Long absolute address cannot be used");
                        return -1;
                    }
                    warn("Long absolute address cannot be forced - substituting I/O short addressing");
                    mode = 17UL;
                }
            } else {
                mode = 16UL;
                if (Pass == 2UL) {
                    if (value > 0x3fUL) {
                        putop(op, OP_MODE, mode);
                        err("Long absolute cannot be used - force short or I/O short");
                        return -1;
                    }
                    warn("Long absolute address cannot be forced - substituting short addressing");
                }
            }
        } else if (force == FORCE_IO) {
            mode = 17UL;
            if (value > 0x3fUL && value < 0x80UL) {
                value |= 0xffc0UL;
                putop(op, OP_VALUE, value);
            }
            if (fwd == 0UL) {
                if (!InLineReplay && !in_io_range(value)) {
                    putop(op, OP_MODE, mode);
                    err("Absolute address too small to use I/O short");
                    return -1;
                }
            } else if (Pass == 2UL && !InLineReplay && !in_io_range(value)) {
                putop(op, OP_MODE, mode);
                err("Absolute address too small to use I/O short");
                return -1;
            }
        } else if (force == FORCE_SHORT) {
            mode = 16UL;
            if (fwd == 0UL) {
                if (value > 0x3fUL) {
                    putop(op, OP_MODE, mode);
                    err("Absolute address too large to use short");
                    return -1;
                }
            } else if (Pass == 2UL && value > 0x3fUL) {
                putop(op, OP_MODE, mode);
                err("Absolute address too large to use short");
                return -1;
            }
        } else if (fwd != 0UL || reloc) {
            mode = 16UL;
            if (Pass == 2UL && value > 0x3fUL) {
                putop(op, OP_MODE, mode);
                err("Absolute address contains forward reference - force short or I/O short address");
                return -1;
            }
        } else if (value < 0x40UL) {
            mode = 16UL;
        } else {
            if (!InLineReplay && !in_io_range(value)) {
                putop(op, OP_MODE, 17UL);
                err("Absolute address must be either short or I/O short");
                return -1;
            }
            mode = 17UL;
        }
        break;
    case 8:
        if (force == FORCE_LONG) {
            mode = 14UL;
        } else if (force == FORCE_IO) {
            mode = 17UL;
            if (value > 0x3fUL && value < 0x80UL) {
                value |= 0xffc0UL;
                putop(op, OP_VALUE, value);
            }
            if (fwd == 0UL) {
                if (!InLineReplay && !in_io_range(value)) {
                    mode = 14UL;
                    warn("Absolute address too small to use I/O short - long substituted");
                }
            } else if (Pass == 2UL && !InLineReplay && !in_io_range(value)) {
                putop(op, OP_MODE, mode);
                err("Absolute address too small to use I/O short");
                return -1;
            }
        } else if (force == FORCE_SHORT) {
            mode = 14UL;
            warn("Short absolute address cannot be forced - long substituted");
        } else if (fwd != 0UL || reloc) {
            mode = 14UL;
        } else if (!InLineReplay && !in_io_range(value)) {
            mode = 14UL;
        } else {
            mode = 17UL;
        }
        break;
    case 9:
        if (force == FORCE_LONG) {
            mode = 14UL;
        } else if (force == FORCE_SHORT) {
            mode = 16UL;
            if (fwd == 0UL) {
                if (value > 0x3fUL) {
                    mode = 14UL;
                    warn("Absolute address too large to use short - long substituted");
                }
            } else if (Pass == 2UL && value > 0x3fUL) {
                putop(op, OP_MODE, mode);
                err("Absolute address too large to use short");
                return -1;
            }
        } else if (force == FORCE_IO) {
            mode = 14UL;
            warn("I/O short absolute address cannot be forced - long substituted");
        } else if (fwd != 0UL || reloc) {
            mode = 14UL;
        } else if (value < 0x40UL) {
            mode = 16UL;
        } else {
            mode = 14UL;
        }
        break;
    default:
        fatal("Absolute mode select failure");
        mode = 0UL;
        break;
    }
    putop(op, OP_MODE, mode);
    *(char **)((char *)op + OP_CFORM) = make_cform(op, mode);
    return 1;
}

/* ------------------------------------------------------------------ */
/* get_amode / parse_operand                                           */

static void operand_reset(void *op, unsigned long flags)
{
    putop(op, OP_MODE, 0UL);
    if ((flags & 4UL) != 0UL)
        putop(op, OP_SPACE, 4UL);
    putop(op, OP_FWD, 0UL);
    putop(op, OP_FORCE, 0UL);
    putop(op, OP_VALUE, 0UL);
    putop(op, OP_REG, 0xffffffffUL);
    putop(op, OP_SECT, 0UL);
    putop(op, 0x1cU, 0UL);
    *(char **)((char *)op + OP_CFORM) = (char *)0;
}

/* 004061ae */
int get_amode(unsigned long flags, void *op, int regclass, int eaclass,
              int absclass, int immclass)
{
    int r;

    operand_reset(op, flags);
    if (optr == (char *)0 || *optr == '\0') {
        err("Syntax error - missing address mode specifier");
        err("Possible invalid white space between operands or arguments");
        return 0;
    }
    if (regclass != 0) {
        r = amode_register(regclass, op);
        if (r == -1)
            return 0;
        if (r == 1) {
            if (!note_reg_direct(flags, regclass, (int)opword(op, OP_REG)))
                return 0;
            return 1;
        }
    }
    if (immclass == 0 && eaclass == 0 && absclass == 0) {
        err("Only register direct addressing allowed");
        return 0;
    }
    if (immclass != 0) {
        r = amode_immediate(immclass, op);
        if (r == -1)
            return 0;
        if (r == 1)
            return 1;
    }
    if (eaclass == 0 && absclass == 0) {
        if (regclass == 0) {
            err("Only immediate addressing allowed");
            return 0;
        }
        if (immclass == 0) {
            err("Only register direct addressing allowed");
            return 0;
        }
        err("Only immediate and register direct addressing allowed");
        return 0;
    }
    if (eaclass != 0) {
        r = amode_indirect(eaclass, op);
        if (r == -1)
            return 0;
        if (r == 1) {
            check_areg_stall((int)opword(op, OP_REG),
                             (int)opword(op, OP_MODE));
            return 1;
        }
    }
    if (absclass != 0) {
        r = amode_absolute(absclass, op);
        if (r == -1)
            return 0;
        if (r == 1)
            return 1;
        err("Invalid addressing mode");
        return 0;
    }
    if (regclass == 0) {
        err("Only register indirect addressing allowed");
        return 0;
    }
    if (immclass == 0) {
        err("Only register direct and indirect addressing allowed");
        return 0;
    }
    err("Only immediate and register direct and indirect addressing allowed");
    return 0;
}

/* 004060d8 */
int parse_operand(unsigned long flags, void *op, int regclass, int eaclass,
                  int absclass, int immclass)
{
    char c;

    if (!get_amode(flags, op, regclass, eaclass, absclass, immclass)) {
        free_cform(op);
        return 0;
    }
    if ((flags & 1UL) == 0UL) {
        if (*optr == '\0')
            return 1;
        err("Address mode syntax error - extra characters");
        free_cform(op);
        return 0;
    }
    c = *optr;
    ++optr;
    if (c == ',')
        return 1;
    err("Address mode syntax error - expected comma");
    return 0;
}

/* 00405fe0 */
int parse_xfield_src(void *op)
{
    char c;

    if (!get_amode(0UL, op, 0x12, 1, 6, 6)) {
        free_cform(op);
        return 0;
    }
    if (opword(op, OP_SPACE) == 4UL && opword(op, OP_MODE) > 2UL &&
        opword(op, OP_MODE) < 7UL) {
        if (*optr != '\0') {
            err("Address mode syntax error - extra characters");
            free_cform(op);
            return 0;
        }
    } else {
        c = *optr;
        ++optr;
        if (c != ',') {
            err("Address mode syntax error - expected comma");
            free_cform(op);
            return 0;
        }
    }
    return 1;
}

/* Test/driver convenience: parse an operand string. */
int asm56000_parse_operand_text(char *text, unsigned long flags, void *op,
                                int regclass, int eaclass, int absclass,
                                int immclass)
{
    char *save;
    int r;

    if (op == (void *)0)
        return 0;
    save = optr;
    optr = text == (char *)0 ? (char *)"" : text;
    r = parse_operand(flags | 4UL, op, regclass, eaclass, absclass,
                      immclass);
    optr = save;
    return r;
}

void set_opt_rp(int on)
{
    OptRp = on != 0;
}

int get_opt_rp(void)
{
    return OptRp;
}

long get_date_time(char *date, char *time_text)
{
    time_t now;
    struct tm *tm_value;

    now = time((time_t *)0);
    tm_value = localtime(&now);
    if (tm_value == (struct tm *)0)
        return 0L;
    sprintf(date, "%02d-%02d-%02d", tm_value->tm_year,
            tm_value->tm_mon + 1, tm_value->tm_mday);
    sprintf(time_text, "%02d:%02d:%02d", tm_value->tm_hour,
            tm_value->tm_min, tm_value->tm_sec);
    return (long)now;
}

int set_file_type(char *fname, char *type, char *creator)
{
    (void)fname;
    (void)type;
    (void)creator;
    return 1;
}

void free_str_list(void *list)
{
    struct string_node {
        char *text;
        struct string_node *next;
    };
    struct string_node *node;
    struct string_node *next;

    node = (struct string_node *)list;
    while (node != (struct string_node *)0) {
        next = node->next;
        xfree(node->text);
        xfree(node);
        node = next;
    }
}
