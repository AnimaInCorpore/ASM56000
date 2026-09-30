/*
 * ASM56000 source-input primitives recovered from input.c.
 *
 * This slice covers the ordinary-file reader, continuation/tab handling,
 * quote-aware token scanning, include-file nesting, macro-line replay, and
 * the auxiliary macro-state stack.  The driver owns the higher-level macro
 * definition records while this module provides the input transport.
 */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "asm56000.h"

extern void fatal(char *msg);
extern char InLineReplay;

static char ParsedFields[ASM56000_INPUT_LINE_CAP * 2];
static void *MacroLineStack;

struct mstate_node {
    unsigned long value;
    struct mstate_node *next;
};

struct macro_line_node {
    char *line;
    struct macro_line_node *next;
};

struct input_mode_node {
    char *saved_curfilename;
    FILE *saved_fp;
    char *opened_filename;
    unsigned long saved_open_count;
    unsigned long saved_lineno_base;
    unsigned long saved_line_total;
    char *pending_text;
    struct input_mode_node *next;
};

static int input_is_blank(int c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f';
}

unsigned long input_getc(void)
{
    int c;

    /* The original takes the buffered-file path when no macro expansion
       context is active.  The macro-context path is added with macro.c. */
    c = CurSrcFp == (FILE *)0 ? EOF : fgetc(CurSrcFp);
    if (c == EOF)
        return 0xffffffffUL;
    return (unsigned long)(unsigned char)c;
}

void mstate_push(unsigned long value)
{
    struct mstate_node *node;

    node = (struct mstate_node *)xmalloc((unsigned long)sizeof(*node));
    if (node == (struct mstate_node *)0)
        return;
    node->value = value;
    node->next = (struct mstate_node *)MacroStateStack;
    MacroStateStack = (void *)node;
}

unsigned long mstate_pop(void)
{
    struct mstate_node *node;
    unsigned long value;

    node = (struct mstate_node *)MacroStateStack;
    if (node == (struct mstate_node *)0)
        return 0UL;
    value = node->value;
    MacroStateStack = (void *)node->next;
    xfree((void *)node);
    return value;
}

unsigned long input_pop(void)
{
    struct input_mode_node *node;
    unsigned long state;

    node = (struct input_mode_node *)InputModeStack;
    if (node == (struct input_mode_node *)0)
        return 0UL;

    CurFileName = node->saved_curfilename;
    CurSrcFp = node->saved_fp;
    OpenFileCount = node->saved_open_count;
    LineNoBase = node->saved_lineno_base;
    LineTotal = node->saved_line_total;
    if (node->pending_text != (char *)0) {
        strcpy(RawLineBuf, node->pending_text);
        PendingLine = 1;
        xfree((void *)node->pending_text);
        node->pending_text = (char *)0;
    }
    InputModeStack = (void *)node->next;
    if (node->opened_filename != (char *)0)
        xfree((void *)node->opened_filename);
    xfree((void *)node);
    state = mstate_pop();
    if (state != 1UL)
        fatal("Input mode stack out of sequence");
    return 1UL;
}

int input_push_file(char *path)
{
    struct input_mode_node *node;
    FILE *fp;

    if (path == (char *)0 || *path == '\0')
        return 0;
    fp = fopen(path, "rb");
    if (fp == (FILE *)0)
        return 0;
    node = (struct input_mode_node *)xmalloc(
        (unsigned long)sizeof(*node));
    if (node == (struct input_mode_node *)0) {
        fclose(fp);
        return 0;
    }
    node->saved_curfilename = CurFileName;
    node->saved_fp = CurSrcFp;
    node->opened_filename = str_dupcat(path, (char *)0);
    node->saved_open_count = OpenFileCount;
    node->saved_lineno_base = LineNoBase;
    node->saved_line_total = LineTotal;
    node->pending_text = (char *)0;
    node->next = (struct input_mode_node *)InputModeStack;
    InputModeStack = (void *)node;
    mstate_push(1UL);
    CurSrcFp = fp;
    CurFileName = node->opened_filename;
    OpenFileCount = node->saved_open_count + 1UL;
    LineNoBase = LineNo;
    LineTotal = 0UL;
    PendingLine = 0;
    NoMoreInput = 0;
    return 1;
}

void input_push_lines(char **lines, int count)
{
    struct macro_line_node *node;
    struct macro_line_node *sentinel;
    int i;

    if (lines == (char **)0)
        return;
    sentinel = (struct macro_line_node *)xmalloc(
        (unsigned long)sizeof(*sentinel));
    sentinel->line = (char *)0;
    sentinel->next = (struct macro_line_node *)MacroLineStack;
    MacroLineStack = (void *)sentinel;
    for (i = count - 1; i >= 0; --i) {
        node = (struct macro_line_node *)xmalloc(
            (unsigned long)sizeof(*node));
        node->line = lines[i];
        node->next = (struct macro_line_node *)MacroLineStack;
        MacroLineStack = (void *)node;
    }
    xfree((void *)lines);
}

void input_skip_macro_lines(void)
{
    struct macro_line_node *node;

    while (MacroLineStack != (void *)0) {
        node = (struct macro_line_node *)MacroLineStack;
        MacroLineStack = (void *)node->next;
        if (node->line == (char *)0) {
            xfree((void *)node);
            return;
        }
        xfree((void *)node->line);
        xfree((void *)node);
    }
}

void input_clear_macro_lines(void)
{
    struct macro_line_node *node;

    while (MacroLineStack != (void *)0) {
        node = (struct macro_line_node *)MacroLineStack;
        MacroLineStack = (void *)node->next;
        if (node->line != (char *)0)
            xfree((void *)node->line);
        xfree((void *)node);
    }
}

unsigned long chk_line_end(void)
{
    char *p;

    /* The original scans this way but returns success unconditionally. */
    p = RawLineBuf;
    while (*p != '\0' && !input_is_blank((unsigned char)*p))
        ++p;
    return 1UL;
}

char *scan_token(char *p)
{
    char quote;

    if (p == (char *)0)
        return p;
    for (;;) {
        if (*p == '\0' || input_is_blank((unsigned char)*p))
            return p;
        if (*p == '\'' || *p == '"') {
            quote = *p++;
            while (*p != '\0' && *p != quote)
                ++p;
            if (*p != '\0')
                ++p;
        } else {
            ++p;
        }
    }
}

static char *copy_field(char *dst, char *begin, char *end)
{
    while (begin != end)
        *dst++ = *begin++;
    *dst++ = '\0';
    return dst;
}

static char *skip_blanks(char *p)
{
    while (*p != '\0' && input_is_blank((unsigned char)*p))
        ++p;
    return p;
}

unsigned long parse_line(void)
{
    char *p;
    char *end;
    char *next;
    char *fields[6];
    int i;
    int column_one;

    next = ParsedFields;
    for (i = 0; i < 6; ++i)
        fields[i] = (char *)0;
    p = RawLineBuf;
    if (*p == '\0' || *p == ';') {
        for (i = 0; i < 6; ++i) {
            fields[i] = next;
            *next++ = '\0';
        }
        LabelField = fields[0];
        MnemField = fields[1];
        Op1Field = fields[2];
        Op2Field = fields[3];
        Op3Field = fields[4];
        Op4Field = fields[5];
        return 0UL;
    }
    if (*skip_blanks(p) == ';') {
        for (i = 0; i < 6; ++i) {
            fields[i] = next;
            *next++ = '\0';
        }
        LabelField = fields[0];
        MnemField = fields[1];
        Op1Field = fields[2];
        Op2Field = fields[3];
        Op3Field = fields[4];
        Op4Field = fields[5];
        return 0UL;
    }

    column_one = !input_is_blank((unsigned char)*p);
    p = skip_blanks(p);
    end = scan_token(p);
    if (column_one && p != end) {
        char *colon;

        colon = end;
        if (end > p && end[-1] == ':')
            --colon;
        fields[0] = next;
        next = copy_field(next, p, colon);
        p = skip_blanks(end);
        if (p == end)
            p = end;
    }

    if (!column_one) {
        end = scan_token(p);
        fields[1] = next;
        next = copy_field(next, p, end);
        p = skip_blanks(end);
    } else if (*fields[0] != '\0') {
        end = scan_token(p);
        fields[1] = next;
        next = copy_field(next, p, end);
        p = skip_blanks(end);
    } else {
        end = scan_token(p);
        fields[1] = next;
        next = copy_field(next, p, end);
        p = skip_blanks(end);
    }

    for (i = 2; i < 6 && *p != '\0' && *p != ';'; ++i) {
        end = scan_token(p);
        fields[i] = next;
        next = copy_field(next, p, end);
        p = skip_blanks(end);
    }

    for (i = 0; i < 6; ++i) {
        if (fields[i] == (char *)0) {
            fields[i] = next;
            *next++ = '\0';
        }
    }

    LabelField = fields[0];
    MnemField = fields[1];
    Op1Field = fields[2];
    Op2Field = fields[3];
    Op3Field = fields[4];
    Op4Field = fields[5];
    return *MnemField == '\0' ? 0UL : 1UL;
}

unsigned long read_line(void)
{
    unsigned long used;
    unsigned long tab;
    unsigned long c;

    used = 0UL;
    tab = 0UL;
    for (;;) {
        c = input_getc();
        if (c == 0xffffffffUL) {
            if (used == 0UL)
                return 0UL;
            break;
        }
        if (c == '\r')
            continue;
        if (c == '\n') {
            if (used != 0UL && RawLineBuf[used - 1UL] == '\\') {
                --used;
                tab = 0UL;
                continue;
            }
            break;
        }
        if (c == '\t') {
            unsigned long width;

            width = TabWidth == 0UL ? 8UL : TabWidth;
            do {
                if (used + 1UL >= ASM56000_INPUT_LINE_CAP) {
                    fatal("Line too long");
                    RawLineBuf[used] = '\0';
                    return 1UL;
                }
                RawLineBuf[used++] = ' ';
                ++tab;
            } while ((tab % width) != 0UL);
            continue;
        }
        if (used + 1UL >= ASM56000_INPUT_LINE_CAP) {
            fatal("Line too long");
            RawLineBuf[used] = '\0';
            return 1UL;
        }
        RawLineBuf[used++] = (char)c;
        ++tab;
    }
    RawLineBuf[used] = '\0';
    chk_line_end();
    return 1UL;
}

unsigned long get_line(void)
{
    struct macro_line_node *macro_line;

    for (;;) {
        if (NoMoreInput)
            return 0UL;
        macro_line = (struct macro_line_node *)MacroLineStack;
        if (macro_line != (struct macro_line_node *)0) {
            if (macro_line->line == (char *)0) {
                MacroLineStack = (void *)macro_line->next;
                xfree((void *)macro_line);
                continue;
            }
            InLineReplay = 1;
            ++LineNo;
            if (LineNo == 0UL) {
                fatal("Too many lines in source file");
                return 0UL;
            }
            strncpy(RawLineBuf, macro_line->line,
                    ASM56000_INPUT_LINE_CAP - 1);
            RawLineBuf[ASM56000_INPUT_LINE_CAP - 1] = '\0';
            MacroLineStack = (void *)macro_line->next;
            xfree((void *)macro_line->line);
            xfree((void *)macro_line);
            return 1UL;
        }
        if (read_line()) {
            InLineReplay = 0;
            ++LineNo;
            if (LineNo == 0UL) {
                fatal("Too many lines in source file");
                return 0UL;
            }
            ++LineTotal;
            return 1UL;
        }
        if (CurSrcFp != (FILE *)0) {
            fclose(CurSrcFp);
            CurSrcFp = (FILE *)0;
        }
        if (input_pop())
            continue;
        NoMoreInput = 1;
        return 0UL;
    }
}

void process_file(void)
{
    while (get_line()) {
        if (parse_line()) {
            if (proc_line1() != 0UL && Pass != 0UL)
                proc_line2(Pass == 2UL, 1);
        }
    }
}

unsigned long *subst_symbol(unsigned long *tok, unsigned long *dst,
                            int context)
{
    (void)context;
    if (tok == (unsigned long *)0 || dst == (unsigned long *)0)
        return (unsigned long *)0;
    *dst = *tok;
    return dst;
}

unsigned long proc_line1(void)
{
    if (MnemField == (char *)0 || *MnemField == '\0')
        return 0UL;
    if (find_directive(MnemField, 0) != (void *)0) {
        pseudo_dispatch(MnemField);
        return 1UL;
    }
    if (find_mnemonic(MnemField, 0) != (void *)0)
        return 1UL;
    return 0UL;
}

unsigned long proc_line2(int pass2, int emit)
{
    (void)pass2;
    (void)emit;
    return proc_line1();
}

void do_line_reset(void)
{
}

void do_save_line(int kind)
{
    (void)kind;
}

void do_stack_unwind(int *frame)
{
    (void)frame;
}

void do_replay_line(int *frame)
{
    (void)frame;
}

unsigned long do_check_end_range(int n)
{
    (void)n;
    return 1UL;
}

int do_check_end_word_err(int n)
{
    (void)n;
    return 0;
}
