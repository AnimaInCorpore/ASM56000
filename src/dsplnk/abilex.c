/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), abilex.c
 * The flex generated scanner of the ABI expression language
 * (original 00438b60-00439dbb; flex 2.5.x skeleton, compressed tables with
 * base/def/nxt/chk/meta).  The tables are generated from the EXE into
 * abilextb.h by re/scripts/gentab_abi.py.  Scanner input is not read from a
 * file: YY_INPUT (yy_copy_buffer) copies from the memory buffer that
 * abi_expr_eval_impl points abi_expr_text/abi_expr_text_end at.
 *
 * Function names follow flex; the names of the original binary in
 * re/names are: yy_get_previous_state = "yyunput" (00439743),
 * yy_try_NUL_trans = "input" (00439839), yywrap = "yy_more_flag" (00439dbb).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abi.h"
#include "abiyy.h"
#include "abilextb.h"

#define YY_END_OF_BUFFER_CHAR 0
#define YY_END_OF_BUFFER 58
#define YY_BUF_SIZE 16384L
#define YY_READ_BUF_SIZE 8192L

#define YY_BUFFER_NEW 0
#define YY_BUFFER_NORMAL 1
#define YY_BUFFER_EOF_PENDING 2

#define EOB_ACT_CONTINUE_SCAN 0
#define EOB_ACT_END_OF_FILE 1
#define EOB_ACT_LAST_MATCH 2

typedef struct yy_buffer_state {
    FILE *yy_input_file;            /* +0x00 */
    char *yy_ch_buf;                /* +0x04 */
    char *yy_buf_pos;               /* +0x08 */
    long yy_buf_size;               /* +0x0c */
    long yy_n_chars;                /* +0x10 */
    int yy_is_our_buffer;           /* +0x14 */
    int yy_is_interactive;          /* +0x18 */
    int yy_at_bol;                  /* +0x1c */
    int yy_fill_buffer;             /* +0x20 */
    int yy_buffer_status;           /* +0x24 */
} YY_BUFFER_STATE;

YYSTYPE yylval;                     /* 46b430 */
char *yytext;                       /* 46c058 */
long yyleng;                        /* 46c048 */
FILE *yyin;                         /* 46ad18 */
FILE *yyout;                        /* 46ad1c */
long yylineno = 1;                  /* 45ceb8 */

static int yy_init = 1;             /* 45bf68 */
static int yy_start = 0;            /* 46ad14 */
static YY_BUFFER_STATE *yy_current_buffer = NULL;   /* 46ad0c */
static char yy_hold_char;           /* 46acfc */
static long yy_n_chars;             /* 46ad00 */
static char *yy_c_buf_p = NULL;     /* 46ad10 */
static int yy_did_buffer_switch_on_eof; /* 46acf8 */
static int yy_last_accepting_state; /* 46ad08 */
static char *yy_last_accepting_cpos;/* 46ad04 */

static void yy_load_buffer_state(void);
static YY_BUFFER_STATE *yy_create_buffer(FILE *file, long size);
static void yy_init_buffer(YY_BUFFER_STATE *b, FILE *file);
static void yy_flush_buffer(YY_BUFFER_STATE *b);
static int yy_get_next_buffer(void);
static int yy_get_previous_state(void);
static int yy_try_NUL_trans(int yy_current_state);
static void yy_fatal_error(char *msg);
static void *yy_flex_alloc(unsigned long size);
static void *yy_flex_realloc(void *p, unsigned long size);
static void yy_flex_free(void *p);
static long yy_copy_buffer(char *dst, long n);
static int yywrap(void);

/* strtoul of the Microsoft C runtime: 32 bit result, ERANGE gives 0xffffffff */
#define YY_EINVAL 0x16
#define YY_ERANGE 0x22

static unsigned long yy_strtoul(char *s, int base, int *err)
{
    unsigned long number = 0, maxval = 0xffffffffUL;
    int c, neg = 0, overflow = 0, any = 0, digit;

    *err = 0;
    while (*s == ' ' || (*s >= 9 && *s <= 13))
        s++;
    c = (unsigned char)*s;
    if (c == '-') {
        neg = 1;
        s++;
    } else if (c == '+') {
        s++;
    }
    c = (unsigned char)*s;
    if (base == 0) {
        if (c != '0')
            base = 10;
        else if (s[1] == 'x' || s[1] == 'X')
            base = 16;
        else
            base = 8;
    }
    if (base == 16 && c == '0' && (s[1] == 'x' || s[1] == 'X'))
        s += 2;
    for (;; s++) {
        c = (unsigned char)*s;
        if (c >= '0' && c <= '9')
            digit = c - '0';
        else if (c >= 'a' && c <= 'z')
            digit = c - 'a' + 10;
        else if (c >= 'A' && c <= 'Z')
            digit = c - 'A' + 10;
        else
            break;
        if (digit >= base)
            break;
        any = 1;
        if (number < maxval / (unsigned long)base ||
            (number == maxval / (unsigned long)base &&
             (unsigned long)digit <= maxval % (unsigned long)base))
            number = number * (unsigned long)base + (unsigned long)digit;
        else
            overflow = 1;
    }
    if (!any)
        return 0UL;
    if (overflow) {
        *err = YY_ERANGE;
        return maxval;
    }
    if (neg)
        number = (0UL - number) & maxval;
    return number;
}

/* number rule actions: convert yytext into yylval, report conversion errors */
static void yy_numconv(int base, char *msg_range)
{
    int err;

    yylval.v.u = yy_strtoul(yytext, base, &err);
    if (err == YY_EINVAL && yylval.v.u == 0)
        dbg_print_str("STRTOUL can not perform this conversion", yytext);
    if (err == YY_ERANGE && yylval.v.u == 0xffffffffUL)
        dbg_print_str(msg_range, yytext);
}

static char *yy_strdup(char *s)
{
    char *p;

    if (s == NULL)
        return NULL;
    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

int yylex(void)
{
    int yy_current_state;
    char *yy_cp, *yy_bp;
    int yy_act;
    int yy_c;

    if (yy_init) {
        yy_init = 0;
        if (!yy_start)
            yy_start = 1;
        if (yyin == NULL)
            yyin = stdin;
        if (yyout == NULL)
            yyout = stdout;
        if (yy_current_buffer == NULL)
            yy_current_buffer = yy_create_buffer(yyin, YY_BUF_SIZE);
        yy_load_buffer_state();
    }

    for (;;) {
        yy_cp = yy_c_buf_p;
        *yy_cp = yy_hold_char;
        yy_bp = yy_cp;
        yy_current_state = yy_start;

yy_match:
        do {
            yy_c = yy_ec[(unsigned char)*yy_cp];
            if (yy_accept[yy_current_state]) {
                yy_last_accepting_state = yy_current_state;
                yy_last_accepting_cpos = yy_cp;
            }
            while (yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state) {
                yy_current_state = yy_def[yy_current_state];
                if (yy_current_state > YY_LAST_DFA)
                    yy_c = yy_meta[yy_c];
            }
            yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
            ++yy_cp;
        } while (yy_base[yy_current_state] != YY_JAM_BASE);

yy_find_action:
        yy_act = yy_accept[yy_current_state];
        if (yy_act == 0) {
            yy_cp = yy_last_accepting_cpos;
            yy_current_state = yy_last_accepting_state;
            yy_act = yy_accept[yy_current_state];
        }

        yytext = yy_bp;                     /* YY_DO_BEFORE_ACTION */
        yyleng = (long)(yy_cp - yy_bp);
        yy_hold_char = *yy_cp;
        *yy_cp = '\0';
        yy_c_buf_p = yy_cp;

do_action:
        switch (yy_act) {
        case 0:                             /* must back up */
            *yy_cp = yy_hold_char;
            yy_cp = yy_last_accepting_cpos;
            yy_current_state = yy_last_accepting_state;
            goto yy_find_action;

        case 1:                             /* binary number */
            yy_numconv(2, "binary number is outside the range \t\t\t\t\t\t\tof representable value for unsigned long 32bit");
            return 0x119;
        case 2:                             /* hex number */
            yy_numconv(0, "hex number is outside the range 							of representable value for unsigned long 32bit");
            return 0x119;
        case 3:                             /* octal number */
            yy_numconv(0, "octal number is outside the range 							of representable value for unsigned long 32bit");
            return 0x119;
        case 4:                             /* decimal number */
            yy_numconv(0, "decimal number is outside the range 								of representable value for unsigned long 32bit");
            return 0x119;
        case 5:
            yylval.v.s = yy_strdup(yytext);
            return 0x121;
        case 6: return 0x101;
        case 7: return 0x102;
        case 8: return 0x103;
        case 9: return 0x104;
        case 10: return 0x105;
        case 11: return 0x10c;
        case 12: return 0x10d;
        case 13: return 0x107;
        case 14: return 0x106;
        case 15: return 0x10a;
        case 16: return 0x10b;
        case 17: return 0x108;
        case 18: return 0x109;
        case 19: return ',';
        case 20: return '=';
        case 21: return '(';
        case 22: return ')';
        case 23: return '.';
        case 24: return '&';
        case 25: return '!';
        case 26: return '~';
        case 27: return '-';
        case 28: return '+';
        case 29: return '*';
        case 30: return '/';
        case 31: return '%';
        case 32: return '<';
        case 33: return '>';
        case 34: return '^';
        case 35: return '|';
        case 36: return '?';
        case 37: return ':';
        case 38: return 0x110;
        case 39: return 0x111;
        case 40: return 0x112;
        case 41: return 0x113;
        case 42: return 0x114;
        case 43: return 0x115;
        case 44: return 0x116;
        case 45: return 0x117;
        case 46: return 0x118;
        case 47:
            yylval.v.s = yy_strdup(yytext);
            return 0x11f;
        case 48: return 0x11a;
        case 49: return 0x11b;
        case 50: return 0x11c;
        case 51:
            yylval.v.u = (yylval.v.u & ~0xffUL) | (unsigned char)yytext[0];
            return 0x11d;
        case 52:
            yylval.v.u = (yylval.v.u & ~0xffUL) | (unsigned char)yytext[0];
            return 0x11e;
        case 53:
            yylval.v.s = yy_strdup(yytext);
            return 0x120;
        case 54:                            /* newline */
            yylineno++;
            break;
        case 55:                            /* white space */
            break;
        case 56:                            /* any other character */
            yy_c = (unsigned char)yytext[0];
            return yy_c >= 128 ? yy_c - 256 : yy_c;
        case 57:                            /* ECHO */
            fwrite(yytext, (size_t)yyleng, 1, yyout);
            break;

        case YY_END_OF_BUFFER: {
            long yy_amount_of_matched_text = (long)(yy_cp - yytext) - 1;

            *yy_cp = yy_hold_char;
            if (yy_current_buffer->yy_buffer_status == YY_BUFFER_NEW) {
                yy_n_chars = yy_current_buffer->yy_n_chars;
                yy_current_buffer->yy_input_file = yyin;
                yy_current_buffer->yy_buffer_status = YY_BUFFER_NORMAL;
            }
            if (yy_c_buf_p <= &yy_current_buffer->yy_ch_buf[yy_n_chars]) {
                int yy_next_state;

                yy_c_buf_p = yytext + yy_amount_of_matched_text;
                yy_current_state = yy_get_previous_state();
                yy_next_state = yy_try_NUL_trans(yy_current_state);
                yy_bp = yytext;
                if (yy_next_state) {
                    yy_cp = ++yy_c_buf_p;
                    yy_current_state = yy_next_state;
                    goto yy_match;
                } else {
                    yy_cp = yy_c_buf_p;
                    goto yy_find_action;
                }
            } else {
                switch (yy_get_next_buffer()) {
                case EOB_ACT_END_OF_FILE:
                    yy_did_buffer_switch_on_eof = 0;
                    if (yywrap()) {
                        yy_c_buf_p = yytext;
                        yy_act = YY_END_OF_BUFFER + ((yy_start - 1) / 2) + 1;
                        goto do_action;
                    } else {
                        if (!yy_did_buffer_switch_on_eof)
                            yyrestart(yyin);
                    }
                    break;
                case EOB_ACT_CONTINUE_SCAN:
                    yy_c_buf_p = yytext + yy_amount_of_matched_text;
                    yy_current_state = yy_get_previous_state();
                    yy_cp = yy_c_buf_p;
                    yy_bp = yytext;
                    goto yy_match;
                case EOB_ACT_LAST_MATCH:
                    yy_c_buf_p = &yy_current_buffer->yy_ch_buf[yy_n_chars];
                    yy_current_state = yy_get_previous_state();
                    yy_cp = yy_c_buf_p;
                    yy_bp = yytext;
                    goto yy_find_action;
                }
            }
            break;
        }

        case YY_END_OF_BUFFER + 1:          /* <<EOF>> (yyterminate) */
            return 0;

        default:
            yy_fatal_error("fatal flex scanner internal error--no action found");
        }
    }
}

static int yy_get_next_buffer(void)
{
    char *dest = yy_current_buffer->yy_ch_buf;
    char *source = yytext;
    long number_to_move, i;
    int ret_val;

    if (yy_c_buf_p > &yy_current_buffer->yy_ch_buf[yy_n_chars + 1])
        yy_fatal_error("fatal flex scanner internal error--end of buffer missed");

    if (yy_current_buffer->yy_fill_buffer == 0) {
        if (yy_c_buf_p - yytext == 1)
            return EOB_ACT_END_OF_FILE;
        else
            return EOB_ACT_LAST_MATCH;
    }

    number_to_move = (long)(yy_c_buf_p - yytext) - 1;
    for (i = 0; i < number_to_move; ++i)
        *(dest++) = *(source++);

    if (yy_current_buffer->yy_buffer_status == YY_BUFFER_EOF_PENDING) {
        yy_current_buffer->yy_n_chars = yy_n_chars = 0;
    } else {
        long num_to_read = yy_current_buffer->yy_buf_size - number_to_move - 1;

        while (num_to_read <= 0) {
            YY_BUFFER_STATE *b = yy_current_buffer;
            long yy_c_buf_p_offset = (long)(yy_c_buf_p - b->yy_ch_buf);

            if (b->yy_is_our_buffer) {
                long new_size = b->yy_buf_size * 2;

                if (new_size <= 0)
                    b->yy_buf_size += b->yy_buf_size / 8;
                else
                    b->yy_buf_size *= 2;
                b->yy_ch_buf = (char *)yy_flex_realloc((void *)b->yy_ch_buf,
                                                       (unsigned long)(b->yy_buf_size + 2));
            } else
                b->yy_ch_buf = NULL;
            if (!b->yy_ch_buf)
                yy_fatal_error("fatal error - scanner input buffer overflow");
            yy_c_buf_p = &b->yy_ch_buf[yy_c_buf_p_offset];
            num_to_read = yy_current_buffer->yy_buf_size - number_to_move - 1;
        }
        if (num_to_read > YY_READ_BUF_SIZE)
            num_to_read = YY_READ_BUF_SIZE;
        yy_n_chars = yy_copy_buffer(&yy_current_buffer->yy_ch_buf[number_to_move], num_to_read);
        yy_current_buffer->yy_n_chars = yy_n_chars;
    }

    if (yy_n_chars == 0) {
        if (number_to_move == 0) {
            ret_val = EOB_ACT_END_OF_FILE;
            yyrestart(yyin);
        } else {
            ret_val = EOB_ACT_LAST_MATCH;
            yy_current_buffer->yy_buffer_status = YY_BUFFER_EOF_PENDING;
        }
    } else
        ret_val = EOB_ACT_CONTINUE_SCAN;

    yy_n_chars += number_to_move;
    yy_current_buffer->yy_ch_buf[yy_n_chars] = YY_END_OF_BUFFER_CHAR;
    yy_current_buffer->yy_ch_buf[yy_n_chars + 1] = YY_END_OF_BUFFER_CHAR;
    yytext = &yy_current_buffer->yy_ch_buf[0];
    return ret_val;
}

static int yy_get_previous_state(void)
{
    int yy_current_state;
    char *yy_cp;
    int yy_c;

    yy_current_state = yy_start;
    for (yy_cp = yytext; yy_cp < yy_c_buf_p; ++yy_cp) {
        yy_c = (*yy_cp ? yy_ec[(unsigned char)*yy_cp] : 1);
        if (yy_accept[yy_current_state]) {
            yy_last_accepting_state = yy_current_state;
            yy_last_accepting_cpos = yy_cp;
        }
        while (yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state) {
            yy_current_state = yy_def[yy_current_state];
            if (yy_current_state > YY_LAST_DFA)
                yy_c = yy_meta[yy_c];
        }
        yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
    }
    return yy_current_state;
}

static int yy_try_NUL_trans(int yy_current_state)
{
    int yy_is_jam;
    int yy_c = 1;

    if (yy_accept[yy_current_state]) {
        yy_last_accepting_state = yy_current_state;
        yy_last_accepting_cpos = yy_c_buf_p;
    }
    while (yy_chk[yy_base[yy_current_state] + yy_c] != yy_current_state) {
        yy_current_state = yy_def[yy_current_state];
        if (yy_current_state > YY_LAST_DFA)
            yy_c = yy_meta[yy_c];
    }
    yy_current_state = yy_nxt[yy_base[yy_current_state] + yy_c];
    yy_is_jam = (yy_current_state == YY_LAST_DFA);
    return yy_is_jam ? 0 : yy_current_state;
}

void yyrestart(FILE *input_file)
{
    if (yy_current_buffer == NULL)
        yy_current_buffer = yy_create_buffer(yyin, YY_BUF_SIZE);
    yy_init_buffer(yy_current_buffer, input_file);
    yy_load_buffer_state();
}

void yy_switch_to_buffer(YY_BUFFER_STATE *new_buffer)
{
    if (yy_current_buffer == new_buffer)
        return;
    if (yy_current_buffer) {
        *yy_c_buf_p = yy_hold_char;
        yy_current_buffer->yy_buf_pos = yy_c_buf_p;
        yy_current_buffer->yy_n_chars = yy_n_chars;
    }
    yy_current_buffer = new_buffer;
    yy_load_buffer_state();
    yy_did_buffer_switch_on_eof = 1;
}

static void yy_load_buffer_state(void)
{
    yy_n_chars = yy_current_buffer->yy_n_chars;
    yytext = yy_c_buf_p = yy_current_buffer->yy_buf_pos;
    yyin = yy_current_buffer->yy_input_file;
    yy_hold_char = *yy_c_buf_p;
}

static YY_BUFFER_STATE *yy_create_buffer(FILE *file, long size)
{
    YY_BUFFER_STATE *b;

    b = (YY_BUFFER_STATE *)yy_flex_alloc(sizeof(YY_BUFFER_STATE));
    if (!b)
        yy_fatal_error("out of dynamic memory in yy_create_buffer()");
    b->yy_buf_size = size;
    b->yy_ch_buf = (char *)yy_flex_alloc((unsigned long)(b->yy_buf_size + 2));
    if (!b->yy_ch_buf)
        yy_fatal_error("out of dynamic memory in yy_create_buffer()");
    b->yy_is_our_buffer = 1;
    yy_init_buffer(b, file);
    return b;
}

void yy_delete_buffer(YY_BUFFER_STATE *b)
{
    if (!b)
        return;
    if (b == yy_current_buffer)
        yy_current_buffer = NULL;
    if (b->yy_is_our_buffer)
        yy_flex_free((void *)b->yy_ch_buf);
    yy_flex_free((void *)b);
}

static void yy_init_buffer(YY_BUFFER_STATE *b, FILE *file)
{
    yy_flush_buffer(b);
    b->yy_input_file = file;
    b->yy_fill_buffer = 1;
    b->yy_is_interactive = 0;       /* isatty(): never used, input comes from memory */
}

static void yy_flush_buffer(YY_BUFFER_STATE *b)
{
    if (!b)
        return;
    b->yy_n_chars = 0;
    b->yy_ch_buf[0] = YY_END_OF_BUFFER_CHAR;
    b->yy_ch_buf[1] = YY_END_OF_BUFFER_CHAR;
    b->yy_buf_pos = &b->yy_ch_buf[0];
    b->yy_at_bol = 1;
    b->yy_buffer_status = YY_BUFFER_NEW;
    if (b == yy_current_buffer)
        yy_load_buffer_state();
}

YY_BUFFER_STATE *yy_scan_buffer(char *base, unsigned long size)
{
    YY_BUFFER_STATE *b;

    if (size < 2 || base[size - 2] != YY_END_OF_BUFFER_CHAR ||
        base[size - 1] != YY_END_OF_BUFFER_CHAR)
        return NULL;
    b = (YY_BUFFER_STATE *)yy_flex_alloc(sizeof(YY_BUFFER_STATE));
    if (!b)
        yy_fatal_error("out of dynamic memory in yy_scan_buffer()");
    b->yy_buf_size = (long)size - 2;
    b->yy_buf_pos = b->yy_ch_buf = base;
    b->yy_is_our_buffer = 0;
    b->yy_input_file = 0;
    b->yy_n_chars = b->yy_buf_size;
    b->yy_is_interactive = 0;
    b->yy_at_bol = 1;
    b->yy_fill_buffer = 0;
    b->yy_buffer_status = YY_BUFFER_NEW;
    yy_switch_to_buffer(b);
    return b;
}

YY_BUFFER_STATE *yy_scan_bytes(char *bytes, long len)
{
    YY_BUFFER_STATE *b;
    char *buf;
    unsigned long n;
    long i;

    n = (unsigned long)len + 2;
    buf = (char *)yy_flex_alloc(n);
    if (!buf)
        yy_fatal_error("out of dynamic memory in yy_scan_bytes()");
    for (i = 0; i < len; ++i)
        buf[i] = bytes[i];
    buf[len] = buf[len + 1] = YY_END_OF_BUFFER_CHAR;
    b = yy_scan_buffer(buf, n);
    if (!b)
        yy_fatal_error("bad buffer in yy_scan_bytes()");
    b->yy_is_our_buffer = 1;
    return b;
}

YY_BUFFER_STATE *yy_scan_string(char *s)
{
    long len;

    for (len = 0; s[len]; ++len)
        ;
    return yy_scan_bytes(s, len);
}

static void yy_fatal_error(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(2);
}

static void *yy_flex_alloc(unsigned long size)
{
    return xmalloc(size);
}

static void *yy_flex_realloc(void *p, unsigned long size)
{
    return xrealloc(p, size);
}

static void yy_flex_free(void *p)
{
    xfree(p);
}

/* YY_INPUT: copy up to n bytes of the expression text (00439d55) */
static long yy_copy_buffer(char *dst, long n)
{
    long avail = (long)(abi_expr_text_end - abi_expr_text);

    if (n < avail)
        avail = n;
    if (avail > 0) {
        memcpy(dst, abi_expr_text, (size_t)avail);
        abi_expr_text += avail;
    }
    return avail;
}

static int yywrap(void)
{
    return 1;
}
