/*
 * Compact expression evaluator for the recovered assembler core.
 *
 * The shipped evaluator stores fixed values as three words (8+24+24 bits)
 * and IEEE values as two words.  This implementation preserves that record
 * format and the original precedence table while keeping the parser usable
 * without the unfinished command-line driver.
 */
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "asm56000.h"

#define EXPR_WORDS 23
#define EXPR_INTEGER 0x100UL
#define EXPR_FLOAT 0x200UL
#define EXPR_RELOC 0x1000UL
#define EXPR_UNRESOLVED 0x08000000UL

#define EXPR_ERR_NONE           0
#define EXPR_ERR_SYMBOL         1
#define EXPR_ERR_EXTRA          2
#define EXPR_ERR_PAREN          3
#define EXPR_ERR_FUNCTION       4
#define EXPR_ERR_FLOAT_OPERATOR 5
#define EXPR_ERR_SPACE          6
#define EXPR_ERR_MISSING        7

static int ExprLastError;

/* Relocation expression text.  The original evaluator copies the source
   text of every expression into a side buffer while it parses (symbols as
   "{name}", absolute symbols and location counters as "@LRF(...)" terms) and
   uses it as the relocation string when the value is relocatable. */
#define EXPR_RELOC_FLAG 0x1000UL
#define EXPR_TEXT_MAX 1024
static char ExprText[EXPR_TEXT_MAX];
static int ExprLen;
static char LastRelocText[EXPR_TEXT_MAX];
static char LastAnyText[EXPR_TEXT_MAX];
static int LastRelocValid;
static int LastValueRel;

struct expr_parser {
    char *text;
    char *pos;
    int error;
};

static unsigned long word(void *value, int n)
{
    return ((unsigned long *)value)[n];
}

static void set_word(void *value, int n, unsigned long x)
{
    ((unsigned long *)value)[n] = x;
}

static int text_on(void)
{
    return Pass == 2UL && !AbsoluteMode;
}

static int value_is_rel(void *v)
{
    return (word(v, 6) & EXPR_RELOC_FLAG) != 0UL || (long)word(v, 15) < 0L;
}

static void tx_putc(int c)
{
    if (!text_on() || ExprLen >= EXPR_TEXT_MAX - 2)
        return;
    ExprText[ExprLen++] = (char)c;
    ExprText[ExprLen] = '\0';
}

static void tx_puts(char *s)
{
    while (*s != '\0')
        tx_putc(*s++);
}

static void set_integer(void *value, unsigned long x);
static double double_value(void *value);

/* Text form of a constant value (original FUN_00416453): absolute symbols,
   location counters and function results are written as @LRF terms, in
   brackets when the value is relocatable. */
static void tx_lrf(void *v)
{
    char buf[160];
    int rel;

    if (!text_on())
        return;
    rel = (word(v, 6) & EXPR_RELOC_FLAG) != 0UL;
    if (rel)
        tx_putc('[');
    if (word(v, 4) == EXPR_FLOAT) {
        sprintf(buf, "%-.15E", double_value(v));
        tx_puts(buf);
    } else {
        tx_puts("@LRF($");
        if (word(v, 5) == 6UL) {
            sprintf(buf, "%06lX", word(v, 1) & 0xffffffUL);
            tx_puts(buf);
        }
        sprintf(buf, "%06lX", word(v, 2) & 0xffffffUL);
        tx_puts(buf);
        sprintf(buf, ",%d,%ld,%d,%d,%d,%d,%d)", (int)word(v, 8),
                (long)word(v, 9), (int)word(v, 15), (int)word(v, 16),
                (int)word(v, 17), (int)word(v, 18), (int)word(v, 20));
        tx_puts(buf);
    }
    if (rel)
        tx_putc(']');
}

/* Original FUN_004150bf: once an operation produced a constant, its text
   (from POS on) is replaced by the folded value.  Returns the new POS. */
static int tx_fold(void *v, int pos)
{
    char buf[64];

    if (!text_on())
        return pos;
    if (value_is_rel(v))
        return ExprLen;
    ExprLen = pos;
    ExprText[pos] = '\0';
    if (word(v, 4) == EXPR_FLOAT)
        sprintf(buf, "%-.15E", double_value(v));
    else if (word(v, 5) == 3UL)
        sprintf(buf, "$%lX", word(v, 2) & 0xffffffUL);
    else
        sprintf(buf, "$%lX%06lX", word(v, 1) & 0xffffffUL,
                word(v, 2) & 0xffffffUL);
    tx_puts(buf);
    return pos;
}

static void set_integer(void *value, unsigned long x)
{
    set_word(value, 0, (x & 0x80000000UL) != 0UL ? 0xffUL : 0UL);
    if ((x & 0x80000000UL) != 0UL)
        set_word(value, 1, 0xff000000UL | ((x >> 24) & 0xffUL));
    else
        set_word(value, 1, (x >> 24) & 0xffUL);
    set_word(value, 2, x & 0xffffffUL);
    set_word(value, 4, EXPR_INTEGER);
    set_word(value, 5, (x > 0xffffffUL && x < 0xff000000UL) ? 6UL : 3UL);
}

static unsigned long integer_value(void *value)
{
    return ((word(value, 1) & 0xffUL) << 24) | (word(value, 2) & 0xffffffUL);
}

static void set_double(void *value, double x)
{
    union {
        double d;
        unsigned long w[2];
    } bits;

    bits.d = x;
    set_word(value, 0, bits.w[0]);
    set_word(value, 1, bits.w[1]);
    set_word(value, 2, 0UL);
    set_word(value, 4, EXPR_FLOAT);
    set_word(value, 5, 8UL);
}

static double double_value(void *value)
{
    union {
        double d;
        unsigned long w[2];
    } bits;

    bits.w[0] = word(value, 0);
    bits.w[1] = word(value, 1);
    return bits.d;
}

void *new_expr_value(void)
{
    unsigned long *value;
    int i;

    value = (unsigned long *)xmalloc((unsigned long)(EXPR_WORDS * 4));
    for (i = 0; i < EXPR_WORDS; ++i)
        value[i] = 0UL;
    value[4] = EXPR_INTEGER;
    value[5] = 3UL;
    value[7] = 4UL;
    value[8] = 4UL;
    value[21] = 0xffffffffUL;
    return (void *)value;
}

void free_expr(void *value)
{
    xfree(value);
}

unsigned long expr_as_int32(void *value)
{
    double x;

    if (value == (void *)0)
        return 0UL;
    if (word(value, 4) == EXPR_FLOAT) {
        x = double_value(value) * 8388608.0;
        if (x >= 0.0)
            x = floor(x + 0.5);
        else
            x = ceil(x - 0.5);
        return (unsigned long)(long)x;
    }
    return integer_value(value);
}

int expr_is_unresolved(void *value)
{
    /* The original record stores this tag at byte offset 0x18, i.e. word 6.
       word() takes a word index, not a byte offset. */
    return value != (void *)0 && word(value, 6) == EXPR_UNRESOLVED;
}

char *expr_unresolved_name(char *text)
{
    static char name[128];
    char *p;
    char *out;

    p = text == (char *)0 ? (char *)"" : text;
    while (*p == ' ' || *p == '\t' || *p == '#' || *p == '<' || *p == '>')
        ++p;
    out = name;
    while ((isalnum((unsigned char)*p) || *p == '_' || *p == '.') &&
           (unsigned)(out - name) + 1U < sizeof(name))
        *out++ = *p++;
    *out = '\0';
    return name;
}

double expr_as_double(void *value)
{
    if (value == (void *)0)
        return 0.0;
    if (word(value, 4) == EXPR_FLOAT)
        return double_value(value);
    return (double)(long)expr_as_int32(value);
}

static void skip_space(struct expr_parser *p)
{
    while (*p->pos != '\0' && isspace((unsigned char)*p->pos))
        ++p->pos;
}

static void copy_integer_result(void *dst, void *lhs, void *rhs,
                                int op)
{
    unsigned long a0;
    unsigned long a1;
    unsigned long a2;
    unsigned long b0;
    unsigned long b1;
    unsigned long b2;
    unsigned long out;
    unsigned long carry;

    if (expr_is_unresolved(lhs) || expr_is_unresolved(rhs)) {
        set_word(dst, 6, EXPR_UNRESOLVED);
        return;
    }

    if (word(lhs, 7) != 4UL && word(rhs, 7) != 4UL &&
        word(lhs, 7) != word(rhs, 7)) {
        ExprLastError = EXPR_ERR_SPACE;
        return;
    }

    if (word(lhs, 4) == EXPR_FLOAT || word(rhs, 4) == EXPR_FLOAT) {
        double da;
        double db;

        da = expr_as_double(lhs);
        db = expr_as_double(rhs);
        if (op == 1)
            set_double(dst, da + db);
        else if (op == 2)
            set_double(dst, da - db);
        else if (op == 3)
            set_double(dst, da * db);
        else if (op == 4)
            set_double(dst, db == 0.0 ? 0.0 : da / db);
        else if (op == 5) {
            ExprLastError = EXPR_ERR_FLOAT_OPERATOR;
            set_integer(dst, ((unsigned long)da) & ((unsigned long)db));
        } else if (op == 6) {
            ExprLastError = EXPR_ERR_FLOAT_OPERATOR;
            set_integer(dst, ((unsigned long)da) | ((unsigned long)db));
        } else if (op == 7) {
            ExprLastError = EXPR_ERR_FLOAT_OPERATOR;
            set_integer(dst, ((unsigned long)da) ^ ((unsigned long)db));
        }
        return;
    }

    a0 = word(lhs, 0) & 0xffUL;
    a1 = word(lhs, 1) & 0xffffffUL;
    a2 = word(lhs, 2) & 0xffffffUL;
    b0 = word(rhs, 0) & 0xffUL;
    b1 = word(rhs, 1) & 0xffffffUL;
    b2 = word(rhs, 2) & 0xffffffUL;
    if (op == 9 || op == 10) {
        unsigned long shift;

        shift = integer_value(rhs) & 63UL;
        if (shift >= 32UL) {
            if (op == 9)
                set_integer(dst, 0UL);
            else
                set_integer(dst, (integer_value(lhs) & 0x80000000UL) != 0UL ?
                            0xffffffffUL : 0UL);
        } else if (op == 9) {
            set_integer(dst, integer_value(lhs) << shift);
        } else {
            set_integer(dst, (unsigned long)((long)integer_value(lhs) >> shift));
        }
        return;
    } else if (op == 1) {
        out = a2 + b2;
        carry = out >> 24;
        a2 = out & 0xffffffUL;
        out = a1 + b1 + carry;
        carry = out >> 24;
        a1 = out & 0xffffffUL;
        a0 = (a0 + b0 + carry) & 0xffUL;
    } else if (op == 2) {
        carry = a2 < b2 ? 1UL : 0UL;
        a2 = (a2 - b2) & 0xffffffUL;
        out = a1 - b1 - carry;
        carry = a1 < b1 + carry ? 1UL : 0UL;
        a1 = out & 0xffffffUL;
        a0 = (a0 - b0 - carry) & 0xffUL;
    } else if (op == 5) {
        a0 &= b0;
        a1 &= b1;
        a2 &= b2;
    } else if (op == 6) {
        a0 |= b0;
        a1 |= b1;
        a2 |= b2;
    } else if (op == 7) {
        a0 ^= b0;
        a1 ^= b1;
        a2 ^= b2;
    } else if (op == 3) {
        set_integer(dst, integer_value(lhs) * integer_value(rhs));
        return;
    } else if (op == 4) {
        if (integer_value(rhs) == 0UL)
            set_integer(dst, 0UL);
        else
            set_integer(dst, integer_value(lhs) / integer_value(rhs));
        return;
    }
    set_word(dst, 0, a0);
    set_word(dst, 1, a1);
    set_word(dst, 2, a2);
    set_word(dst, 4, EXPR_INTEGER);
    set_word(dst, 5, 3UL);
    if (word(lhs, 7) == word(rhs, 7) && word(lhs, 7) != 4UL) {
        set_word(dst, 7, word(lhs, 7));
        set_word(dst, 8, word(lhs, 8));
    }
}

static int get_operator(struct expr_parser *p, int *length)
{
    char *s;

    s = p->pos;
    *length = 1;
    if (s[0] == '\0')
        return 0;
    if (s[0] == '<' && s[1] == '<') { *length = 2; return 9; }
    if (s[0] == '>' && s[1] == '>') { *length = 2; return 10; }
    if (s[0] == '=' && s[1] == '=') { *length = 2; return 13; }
    if (s[0] == '!' && s[1] == '=') { *length = 2; return 14; }
    if (s[0] == '<' && s[1] == '=') { *length = 2; return 15; }
    if (s[0] == '>' && s[1] == '=') { *length = 2; return 16; }
    if (s[0] == '&' && s[1] == '&') { *length = 2; return 17; }
    if (s[0] == '|' && s[1] == '|') { *length = 2; return 18; }
    if (s[0] == '+') return 1;
    if (s[0] == '-') return 2;
    if (s[0] == '*') return 3;
    if (s[0] == '/') return 4;
    if (s[0] == '&') return 5;
    if (s[0] == '|') return 6;
    if (s[0] == '^') return 7;
    if (s[0] == '%') return 8;
    if (s[0] == '<') return 11;
    if (s[0] == '>') return 12;
    return 0;
}

static int precedence(int op)
{
    if ((op >= 3 && op <= 4) || op == 8)
        return 7;
    if (op == 1 || op == 2)
        return 6;
    if (op == 9 || op == 10)
        return 5;
    if ((op >= 11 && op <= 12) || (op >= 15 && op <= 16))
        return 4;
    if (op == 13 || op == 14)
        return 3;
    if (op >= 5 && op <= 7)
        return 2;
    if (op >= 17)
        return 1;
    return 0;
}

static void apply_compare(void *out, void *lhs, void *rhs, int op)
{
    double a;
    double b;
    int result;

    a = expr_as_double(lhs);
    b = expr_as_double(rhs);
    result = 0;
    if (op == 11) result = a < b;
    else if (op == 12) result = a > b;
    else if (op == 13) result = a == b;
    else if (op == 14) result = a != b;
    else if (op == 15) result = a <= b;
    else if (op == 16) result = a >= b;
    else if (op == 17) result = expr_as_int32(lhs) != 0UL &&
                                      expr_as_int32(rhs) != 0UL;
    else if (op == 18) result = expr_as_int32(lhs) != 0UL ||
                                      expr_as_int32(rhs) != 0UL;
    set_integer(out, result ? 1UL : 0UL);
}

static void *parse_expression(struct expr_parser *p, int min_prec, int start);
static void *parse_at_function(struct expr_parser *p);

static int function_name_equal(char *a, char *b)
{
    int ca;
    int cb;

    while (*a != '\0' && *b != '\0') {
        ca = tolower((unsigned char)*a++);
        cb = tolower((unsigned char)*b++);
        if (ca != cb)
            return 0;
    }
    return *a == '\0' && *b == '\0';
}

static void *parse_at_function(struct expr_parser *p)
{
    char name[32];
    unsigned long n;
    void *a;
    void *b;
    void *cval;
    void *dval;
    void *out;
    int c;
    int width;
    int pos;
    double da;
    double db;
    char symbol_name[64];
    char *symbol_start;
    unsigned long symbol_len;

    ++p->pos;
    n = 0UL;
    while (isalpha((unsigned char)*p->pos) && n + 1UL < sizeof(name))
        name[n++] = (char)tolower((unsigned char)*p->pos++);
    name[n] = '\0';
    skip_space(p);
    if (*p->pos != '(') {
        p->error = 1;
        ExprLastError = EXPR_ERR_FUNCTION;
        return (void *)0;
    }
    if (function_name_equal(name, "def")) {
        ++p->pos;
        skip_space(p);
        symbol_start = p->pos;
        while (isalnum((unsigned char)*p->pos) || *p->pos == '_' ||
               *p->pos == '.')
            ++p->pos;
        symbol_len = (unsigned long)(p->pos - symbol_start);
        if (symbol_len >= sizeof(symbol_name))
            symbol_len = sizeof(symbol_name) - 1UL;
        memcpy(symbol_name, symbol_start, symbol_len);
        symbol_name[symbol_len] = '\0';
        skip_space(p);
        if (*p->pos != ')' || symbol_name[0] == '\0') {
            p->error = 1;
            return (void *)0;
        }
        ++p->pos;
        out = new_expr_value();
        set_integer(out, sym_lookup(symbol_name, 2) != (void *)0 ? 1UL : 0UL);
        return out;
    }
    ++p->pos;
    skip_space(p);
    a = (void *)0;
    b = (void *)0;
    cval = (void *)0;
    dval = (void *)0;
    if (*p->pos != ')') {
        a = parse_expression(p, 1, ExprLen);
        if (a == (void *)0)
            return (void *)0;
        skip_space(p);
        if (*p->pos == ',') {
            ++p->pos;
            b = parse_expression(p, 1, ExprLen);
            if (b == (void *)0) {
                free_expr(a);
                return (void *)0;
            }
            skip_space(p);
            if (*p->pos == ',') {
                ++p->pos;
                cval = parse_expression(p, 1, ExprLen);
                if (cval == (void *)0) {
                    free_expr(a); free_expr(b); return (void *)0;
                }
                skip_space(p);
                if (*p->pos == ',') {
                    ++p->pos;
                    dval = parse_expression(p, 1, ExprLen);
                    if (dval == (void *)0) {
                        free_expr(a); free_expr(b); free_expr(cval);
                        return (void *)0;
                    }
                }
            }
        }
        skip_space(p);
    }
    if (*p->pos != ')') {
        free_expr(a);
        free_expr(b);
        p->error = 1;
        ExprLastError = EXPR_ERR_PAREN;
        return (void *)0;
    }
    ++p->pos;

    if (function_name_equal(name, "len")) {
        if (a == (void *)0 || b != (void *)0 || cval != (void *)0 ||
            dval != (void *)0) {
            free_expr(a); free_expr(b); free_expr(cval); free_expr(dval);
            p->error = 1;
            return (void *)0;
        }
        set_integer(a, word(a, 13));
        return a;
    }
    if (function_name_equal(name, "scp")) {
        if (a == (void *)0 || b == (void *)0 || cval != (void *)0 ||
            dval != (void *)0) {
            free_expr(a); free_expr(b); free_expr(cval); free_expr(dval);
            p->error = 1;
            return (void *)0;
        }
        set_integer(a, word(a, 13) == word(b, 13) &&
                    expr_as_int32(a) == expr_as_int32(b) ? 1UL : 0UL);
        free_expr(b);
        return a;
    }

    if (function_name_equal(name, "abs") ||
        function_name_equal(name, "acs") ||
        function_name_equal(name, "asn") ||
        function_name_equal(name, "atn") ||
        function_name_equal(name, "cos") ||
        function_name_equal(name, "coh") ||
        function_name_equal(name, "flr") ||
        function_name_equal(name, "l10") ||
        function_name_equal(name, "log") ||
        function_name_equal(name, "sin") ||
        function_name_equal(name, "snh") ||
        function_name_equal(name, "sqt") ||
        function_name_equal(name, "tan") ||
        function_name_equal(name, "tnh") ||
        function_name_equal(name, "cel") ||
        function_name_equal(name, "xpn")) {
        if (a == (void *)0 || b != (void *)0 || cval != (void *)0 ||
            dval != (void *)0) {
            free_expr(a); free_expr(b); free_expr(cval); free_expr(dval);
            p->error = 1; return (void *)0;
        }
        da = expr_as_double(a);
        if (function_name_equal(name, "abs")) da = mth_abs(da);
        else if (function_name_equal(name, "acs")) da = mth_acos(da);
        else if (function_name_equal(name, "asn")) da = mth_asin(da);
        else if (function_name_equal(name, "atn")) da = mth_atan(da);
        else if (function_name_equal(name, "cos")) da = mth_cos(da);
        else if (function_name_equal(name, "coh")) da = mth_cosh(da);
        else if (function_name_equal(name, "flr")) da = mth_floor(da);
        else if (function_name_equal(name, "l10")) da = mth_log10(da);
        else if (function_name_equal(name, "log")) da = mth_log(da);
        else if (function_name_equal(name, "sin")) da = mth_sin(da);
        else if (function_name_equal(name, "snh")) da = mth_sinh(da);
        else if (function_name_equal(name, "sqt")) da = mth_sqrt(da);
        else if (function_name_equal(name, "tan")) da = mth_tan(da);
        else if (function_name_equal(name, "tnh")) da = mth_tanh(da);
        else if (function_name_equal(name, "cel")) da = mth_ceil(da);
        else da = mth_exp(da);
        set_double(a, da);
        return a;
    }
    if (function_name_equal(name, "at2") || function_name_equal(name, "pow")) {
        if (a == (void *)0 || b == (void *)0 || cval != (void *)0 ||
            dval != (void *)0) {
            free_expr(a); free_expr(b); free_expr(cval); free_expr(dval);
            p->error = 1; return (void *)0;
        }
        da = expr_as_double(a);
        db = expr_as_double(b);
        set_double(a, function_name_equal(name, "at2") ?
                   mth_atan2(da, db) : mth_pow(da, db));
        free_expr(b);
        return a;
    }
    if (function_name_equal(name, "int") || function_name_equal(name, "cvi")) {
        if (a == (void *)0 || b != (void *)0 || cval != (void *)0 ||
            dval != (void *)0) {
            free_expr(a); free_expr(b); free_expr(cval); free_expr(dval);
            p->error = 1; return (void *)0;
        }
        if (word(a, 4) == EXPR_FLOAT)
            set_integer(a, (unsigned long)(long)expr_as_double(a));
        else
            set_integer(a, expr_as_int32(a));
        return a;
    }
    if (function_name_equal(name, "cvf")) {
        if (a == (void *)0 || b != (void *)0 || cval != (void *)0 ||
            dval != (void *)0) {
            free_expr(a); free_expr(b); free_expr(cval); free_expr(dval);
            p->error = 1; return (void *)0;
        }
        set_double(a, expr_as_double(a));
        return a;
    }
    if (function_name_equal(name, "sgn")) {
        if (a == (void *)0 || b != (void *)0 || cval != (void *)0 ||
            dval != (void *)0) {
            free_expr(a); free_expr(b); free_expr(cval); free_expr(dval);
            p->error = 1; return (void *)0;
        }
        da = expr_as_double(a);
        set_integer(a, da < 0.0 ? 0xffffffffUL : da > 0.0 ? 1UL : 0UL);
        return a;
    }
    if (function_name_equal(name, "min") || function_name_equal(name, "max")) {
        if (a == (void *)0 || b == (void *)0 || cval != (void *)0 ||
            dval != (void *)0) {
            free_expr(a); free_expr(b); free_expr(cval); free_expr(dval);
            p->error = 1; return (void *)0;
        }
        da = expr_as_double(a);
        db = expr_as_double(b);
        set_double(a, function_name_equal(name, "min") ?
                   (da < db ? da : db) : (da > db ? da : db));
        free_expr(b);
        return a;
    }
    if (function_name_equal(name, "fld")) {
        if (a == (void *)0 || b == (void *)0 || cval == (void *)0) {
            free_expr(a); free_expr(b); free_expr(cval); free_expr(dval);
            p->error = 1; return (void *)0;
        }
        width = (int)expr_as_int32(cval);
        pos = dval == (void *)0 ? 0 : (int)expr_as_int32(dval);
        if (width < 0 || width > 24) {
            free_expr(a); free_expr(b); free_expr(cval); free_expr(dval);
            p->error = 1; return (void *)0;
        }
        set_integer(a, insert_bits(expr_as_int32(a), expr_as_int32(b),
                                   pos, width));
        free_expr(b);
        free_expr(cval);
        free_expr(dval);
        return a;
    }
    if (function_name_equal(name, "lng")) {
        if (a == (void *)0 || b == (void *)0 || cval != (void *)0 ||
            dval != (void *)0) {
            free_expr(a); free_expr(b); free_expr(cval); free_expr(dval);
            p->error = 1; return (void *)0;
        }
        out = new_expr_value();
        set_word(out, 1, expr_as_int32(a) & 0xffffffUL);
        set_word(out, 2, expr_as_int32(b) & 0xffffffUL);
        set_word(out, 5, 6UL);
        free_expr(a); free_expr(b);
        return out;
    }
    if (function_name_equal(name, "byte_address") ||
        function_name_equal(name, "word_address") ||
        function_name_equal(name, "long_address")) {
        if (a == (void *)0 || b != (void *)0 || cval != (void *)0 ||
            dval != (void *)0) {
            free_expr(a); free_expr(b); free_expr(cval); free_expr(dval);
            p->error = 1; return (void *)0;
        }
        c = function_name_equal(name, "word_address") ? 1 :
            function_name_equal(name, "long_address") ? 2 : 0;
        set_integer(a, expr_as_int32(a) >> c);
        return a;
    }
    free_expr(a);
    free_expr(b);
    free_expr(cval);
    free_expr(dval);
    p->error = 1;
    ExprLastError = EXPR_ERR_FUNCTION;
    return (void *)0;
}

static void *parse_primary(struct expr_parser *p)
{
    unsigned long n;
    char *start;
    char *end;
    char name[64];
    unsigned long len;
    unsigned long packed;
    void *value;
    void *sym;
    double d;
    int c;

    skip_space(p);
    if (*p->pos == '@') {
        int save;

        save = ExprLen;
        value = parse_at_function(p);
        if (text_on()) {
            ExprLen = save;
            ExprText[ExprLen] = '\0';
            if (value != (void *)0 && (long)word(value, 15) >= 0L)
                tx_lrf(value);
        }
        return value;
    }
    if (*p->pos == '*') {
        ++p->pos;
        value = new_expr_value();
        set_integer(value, CurrentAddress);
        if (EvalCounterReloc)
            set_word(value, 6, EXPR_RELOC_FLAG);
        set_word(value, 7, EvalCounterSpace);
        set_word(value, 8, EvalCounterMap);
        set_word(value, 9, EvalCounterIndex);
        set_word(value, 15, EvalSection);
        set_word(value, 16, EvalCounterSection);
        tx_lrf(value);
        return value;
    }
    if (*p->pos == '(') {
        ++p->pos;
        tx_putc('(');
        value = parse_expression(p, 1, ExprLen);
        skip_space(p);
        if (*p->pos != ')') {
            p->error = 1;
            ExprLastError = EXPR_ERR_PAREN;
        } else {
            ++p->pos;
            tx_putc(')');
        }
        return value;
    }
    if (*p->pos == '\'' || *p->pos == '"') {
        c = (unsigned char)*p->pos++;
        packed = 0UL;
        len = 0UL;
        tx_putc('\'');
        while (*p->pos != '\0' && *p->pos != c) {
            if (len < 6UL)
                tx_putc(*p->pos);
            packed = ((packed << 8) | (unsigned char)*p->pos++) & 0xffffffUL;
            ++len;
        }
        tx_putc('\'');
        if (*p->pos == c)
            ++p->pos;
        value = new_expr_value();
        set_integer(value, packed);
        set_word(value, 13, len);
        return value;
    }
    if (*p->pos == '$' || (*p->pos == '0' &&
                          (p->pos[1] == 'x' || p->pos[1] == 'X'))) {
        start = p->pos;
        if (*p->pos == '$')
            ++p->pos;
        else
            p->pos += 2;
        n = strtoul(p->pos, &end, 16);
        if (end == p->pos) {
            p->error = 1;
            ExprLastError = EXPR_ERR_MISSING;
            return (void *)0;
        }
        p->pos = end;
        while (start < end)
            tx_putc(*start++);
        value = new_expr_value();
        set_integer(value, n);
        return value;
    }
    if (*p->pos == '%') {
        ++p->pos;
        n = 0UL;
        start = p->pos;
        while (*p->pos == '0' || *p->pos == '1')
            n = (n << 1) | (unsigned long)(*p->pos++ - '0');
        if (p->pos == start) {
            p->error = 1;
            ExprLastError = EXPR_ERR_MISSING;
            return (void *)0;
        }
        tx_putc('%');
        for (end = start; end < p->pos; ++end)
            tx_putc(*end);
        value = new_expr_value();
        set_integer(value, n);
        return value;
    }
    if (isdigit((unsigned char)*p->pos) || *p->pos == '.') {
        start = p->pos;
        d = strtod(start, &end);
        if (end == start) {
            p->error = 1;
            ExprLastError = EXPR_ERR_MISSING;
            return (void *)0;
        }
        p->pos = end;
        for (n = 0UL; start + n < end; ++n)
            tx_putc(start[n]);
        value = new_expr_value();
        for (n = 0UL, c = 0; start + n < end; ++n)
            if (start[n] == '.' || start[n] == 'e' || start[n] == 'E')
                c = 1;
        if (c)
            set_double(value, d);
        else
            set_integer(value, (unsigned long)d);
        return value;
    }
    if (isalpha((unsigned char)*p->pos) || *p->pos == '_' || *p->pos == '.') {
        start = p->pos;
        while (isalnum((unsigned char)*p->pos) || *p->pos == '_' ||
               *p->pos == '.')
            ++p->pos;
        len = (unsigned long)(p->pos - start);
        if (len >= sizeof(name))
            len = sizeof(name) - 1UL;
        memcpy(name, start, len);
        name[len] = '\0';
        sym = sym_lookup(name, 2);
        value = new_expr_value();
        if (sym == (void *)0) {
            sym_note_unresolved(name);
            set_word(value, 6, EXPR_UNRESOLVED);
            if (text_on()) {
                /* Relocatable mode: an undefined symbol is an external
                   reference resolved by the linker. */
                set_word(value, 15, 0xffffffffUL);
                tx_putc('{');
                tx_puts(name);
                tx_putc('}');
                obj_note_extern(name);
            } else if (Pass == 1UL) {
                tx_putc('{');
                tx_puts(name);
                tx_putc('}');
            }
            return value;
        }
        if (Pass == 1UL)
            sym_add_ref(sym, 1);
        sym_copy_value(sym, value);
        if ((word(value, 6) & EXPR_RELOC_FLAG) == 0UL ||
            (sym_flags(sym) & 0x30UL) != 0UL)
            tx_lrf(value);
        else {
            tx_putc('{');
            tx_puts(name);
            tx_putc('}');
        }
        return value;
    }
    p->error = 1;
    ExprLastError = *p->pos == '\0' ? EXPR_ERR_MISSING : EXPR_ERR_SYMBOL;
    return (void *)0;
}

static void *parse_unary(struct expr_parser *p)
{
    void *value;
    unsigned long x;

    skip_space(p);
    if (*p->pos == '+') {
        ++p->pos;
        tx_putc('+');
        return parse_unary(p);
    }
    if (*p->pos == '-') {
        ++p->pos;
        tx_putc('-');
        value = parse_unary(p);
        if (value != (void *)0) {
            if (word(value, 4) == EXPR_FLOAT)
                set_double(value, -double_value(value));
            else
                set_integer(value, 0UL - integer_value(value));
        }
        return value;
    }
    if (*p->pos == '~') {
        ++p->pos;
        tx_putc('~');
        value = parse_unary(p);
        if (value != (void *)0) {
            x = ~integer_value(value);
            set_integer(value, x);
        }
        return value;
    }
    if (*p->pos == '!') {
        ++p->pos;
        tx_putc('!');
        value = parse_unary(p);
        if (value != (void *)0)
            set_integer(value, expr_as_int32(value) == 0UL ? 1UL : 0UL);
        return value;
    }
    return parse_primary(p);
}

/* Relocation state of the result of "lhs op rhs" (original FUN_00414aa1
   and FUN_004099d3): a sum or difference of two typed terms is absolute;
   otherwise the relocatable term carries over. */
static void combine_reloc(void *res, void *lhs, void *rhs, int op)
{
    unsigned long lspace;
    unsigned long rspace;

    lspace = word(lhs, 7);
    rspace = word(rhs, 7);
    if (word(res, 4) == EXPR_INTEGER && (op == 1 || op == 2) &&
        lspace != 4UL && rspace != 4UL && !expr_is_unresolved(lhs) &&
        !expr_is_unresolved(rhs)) {
        set_word(res, 6, word(res, 6) & ~EXPR_RELOC_FLAG);
        set_word(res, 7, 4UL);
        set_word(res, 8, 4UL);
        return;
    }
    if (value_is_rel(lhs) && (word(lhs, 6) & EXPR_RELOC_FLAG) != 0UL) {
        set_word(res, 6, word(res, 6) | EXPR_RELOC_FLAG);
        set_word(res, 15, word(lhs, 15));
        set_word(res, 16, word(lhs, 16));
    } else if ((word(rhs, 6) & EXPR_RELOC_FLAG) != 0UL) {
        set_word(res, 6, word(res, 6) | EXPR_RELOC_FLAG);
        set_word(res, 15, word(rhs, 15));
        set_word(res, 16, word(rhs, 16));
    }
    if ((long)word(lhs, 15) < 0L)
        set_word(res, 15, word(lhs, 15));
    if ((long)word(rhs, 15) < 0L)
        set_word(res, 15, word(rhs, 15));
    if (word(res, 4) == EXPR_INTEGER) {
        if (lspace != 4UL) {
            set_word(res, 7, lspace);
            set_word(res, 8, word(lhs, 8));
            set_word(res, 9, word(lhs, 9));
        } else if (rspace != 4UL) {
            set_word(res, 7, rspace);
            set_word(res, 8, word(rhs, 8));
            set_word(res, 9, word(rhs, 9));
        }
    }
}

static void *parse_expression(struct expr_parser *p, int min_prec, int start)
{
    void *lhs;
    void *rhs;
    void *result;
    int op;
    int length;
    int prec;
    int fold;
    int i;

    fold = start;
    lhs = parse_unary(p);
    if (lhs == (void *)0)
        return (void *)0;
    for (;;) {
        skip_space(p);
        op = get_operator(p, &length);
        prec = precedence(op);
        if (op == 0 || prec < min_prec)
            break;
        for (i = 0; i < length; ++i)
            tx_putc(p->pos[i]);
        p->pos += length;
        if (value_is_rel(lhs))
            fold = ExprLen;
        rhs = parse_expression(p, prec + 1, fold);
        if (rhs == (void *)0) {
            free_expr(lhs);
            return (void *)0;
        }
        result = new_expr_value();
        if (op >= 11)
            apply_compare(result, lhs, rhs, op);
        else {
            copy_integer_result(result, lhs, rhs, op);
            combine_reloc(result, lhs, rhs, op);
        }
        free_expr(lhs);
        free_expr(rhs);
        lhs = result;
        fold = tx_fold(lhs, fold);
    }
    return lhs;
}

void *eval_expr_text(char *text)
{
    struct expr_parser parser;
    void *value;
    char *p;
    unsigned long space;

    ExprLastError = EXPR_ERR_NONE;
    p = text == (char *)0 ? (char *)"" : text;
    while (*p == ' ' || *p == '\t')
        ++p;
    LastRelocValid = 0;
    space = 4UL;
    if ((p[0] == 'p' || p[0] == 'P') && p[1] == ':')
        space = 0UL;
    else if ((p[0] == 'x' || p[0] == 'X') && p[1] == ':')
        space = 1UL;
    else if ((p[0] == 'y' || p[0] == 'Y') && p[1] == ':')
        space = 2UL;
    else if ((p[0] == 'l' || p[0] == 'L') && p[1] == ':')
        space = 3UL;
    if (space != 4UL) {
        value = eval_expr_text(p + 2);
        if (value != (void *)0) {
            set_word(value, 7, space);
            set_word(value, 8, space);
        }
        return value;
    }
    parser.text = text;
    parser.pos = text == (char *)0 ? (char *)"" : text;
    parser.error = 0;
    ExprText[0] = '{';
    ExprText[1] = '\0';
    ExprLen = 1;
    value = parse_expression(&parser, 1, ExprLen);
    skip_space(&parser);
    if (parser.error || *parser.pos != '\0' ||
        ExprLastError != EXPR_ERR_NONE) {
        if (!parser.error) {
            if (ExprLastError != EXPR_ERR_NONE)
                ;
            else if (*parser.pos >= '0' && *parser.pos <= '9')
                ExprLastError = EXPR_ERR_EXTRA;
            else
                ExprLastError = EXPR_ERR_SYMBOL;
        }
        free_expr(value);
        return (void *)0;
    }
    if (text_on() && value != (void *)0) {
        tx_putc('}');
        strcpy(LastAnyText, ExprText);
        if (value_is_rel(value)) {
            strcpy(LastRelocText, ExprText);
            LastRelocValid = 1;
        }
    }
    return value;
}

/* True when the value carries a relocation (relocatable term or external
   reference) and eval_reloc_text() holds its expression string. */
int expr_is_reloc(void *value)
{
    return value != (void *)0 && value_is_rel(value);
}

char *eval_reloc_text(void)
{
    return LastRelocValid ? LastRelocText : (char *)0;
}

/* Expression text of the last successful evaluation (pass 2, relocatable
   mode), whether or not it is relocatable. */
char *eval_last_text(void)
{
    return LastAnyText;
}

int expr_last_error(void)
{
    return ExprLastError;
}

/* Small compatibility helpers used by the recovered diagnostics layer. */
int op_precedence(int opcode)
{
    return 8 - precedence(opcode);
}

