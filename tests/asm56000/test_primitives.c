/* Small host-side checks for the recovered, target-independent primitives. */
#include <stdio.h>
#include <string.h>

#include "../../src/asm56000/asm56000.h"

static int failures;

static int int_cmp(void *key, void *entry)
{
    int a;
    int b;

    a = *(int *)key;
    b = *(int *)entry;
    if (a < b)
        return -1;
    if (a > b)
        return 1;
    return 0;
}

FILE *CurSrcFp;
char *CurFileName;
void *MacroStateStack;
void *InputModeStack;
char RawLineBuf[ASM56000_INPUT_LINE_CAP];
unsigned long TabWidth = 8UL;
unsigned long LineNo;
unsigned long LineNoBase;
unsigned long OpenFileCount;
unsigned long Pass;
char NoMoreInput;
char PendingLine;
char *LabelField;
char *MnemField;
char *Op1Field;
char *Op2Field;
char *Op3Field;
char *Op4Field;

void fatal(char *msg)
{
    fprintf(stderr, "fatal: %s\n", msg);
    failures++;
}

void *find_directive(char *name, int chk_macro)
{
    (void)name;
    (void)chk_macro;
    return (void *)0;
}

void *find_mnemonic(char *name, int chk_macro)
{
    (void)name;
    (void)chk_macro;
    return (void *)0;
}

int pseudo_dispatch(char *name)
{
    (void)name;
    return 0;
}

static void check_ulong(char *name, unsigned long got, unsigned long want)
{
    if (got != want) {
        fprintf(stderr, "%s: got %08lX want %08lX\n", name, got, want);
        failures++;
    }
}

static void check_int(char *name, int got, int want)
{
    if (got != want) {
        fprintf(stderr, "%s: got %d want %d\n", name, got, want);
        failures++;
    }
}

static void check_text(char *name, char *got, char *want)
{
    if (got == (char *)0 || strcmp(got, want) != 0) {
        fprintf(stderr, "%s: got %s want %s\n", name,
                got == (char *)0 ? "(null)" : got, want);
        failures++;
    }
    xfree(got);
}

int main(void)
{
    FILE *fp;
    char *p;
    int values[4];
    int key;
    char path[32];
    char lower[16];
    char upper[16];
    char *joined;

    check_ulong("insert_bits", insert_bits(0UL, 5UL, 3, 3), 0x28UL);
    check_ulong("insert_bits preserve",
                insert_bits(0xa5a5UL, 3UL, 4, 2), 0xa5b5UL);
    check_ulong("insert_bits2",
                insert_bits2(0UL, 0x2dUL, 0x0fUL, 0, 0, 4,
                             0xf0UL, 4, 8, 4), 0x20dUL);
    check_text("insert_bits_expr",
               insert_bits_expr("$123456", "expr", 4, 2),
               "(($123456&~(~(~0<<2)<<4))|((expr&~(~0<<2))<<4))");
    check_text("insert_bits_expr zero",
               insert_bits_expr("$123456", "expr", 0, 2),
               "(($123456&(~0<<2))|(expr&~(~0<<2)))");

    values[0] = 2;
    values[1] = 7;
    values[2] = 11;
    values[3] = 19;
    key = 11;
    check_int("tab_search", *(int *)tab_search(&key, values, 4,
                                                (int)sizeof(int), int_cmp), 11);
    key = 10;
    check_int("tab_search_pos", (int)(((char *)tab_search_pos(
                   &key, values, 4, (int)sizeof(int), int_cmp) -
                   (char *)values) / (int)sizeof(int)), 2);
    strcpy(path, "C:\\tmp/thing.asm");
    check_text("base_name", str_dupcat(base_name(path), (char *)0), "thing.asm");
    check_ulong("hash_name", hash_name("ABC"), 610UL);
    strcpy(lower, "AbC");
    strcpy(upper, "aBc");
    check_text("str_lower_copy", str_dupcat(str_lower_copy(lower), (char *)0), "abc");
    check_text("str_upper_copy", str_dupcat(str_upper_copy(upper), (char *)0), "ABC");
    joined = str_dupcat("one", "-", "two", (char *)0);
    check_text("str_dupcat", joined, "one-two");

    check_int("d_code D0", d_code(2), 0);
    check_int("d_code D1", d_code(3), 1);
    check_int("rrr_code R0", rrr_code(0, 0x0e), 0);
    check_int("rrr_code R7", rrr_code(0, 0x15), 7);
    check_int("mmm_code (Rn)", mmm_code(2), 4);
    check_int("mmm_code #long", mmm_code(9), 6);
    check_int("d6_code D7", d6_code(7), 7);
    check_int("d6_code N3", d6_code(0x19), 0x1b);
    check_int("xx_code", xx_code(6), 1);
    check_int("yy_code", yy_code(7), 1);
    check_int("x_code", x_code(6), 1);

    mstate_push(1UL);
    mstate_push(9UL);
    check_ulong("mstate_pop top", mstate_pop(), 9UL);
    check_ulong("mstate_pop bottom", mstate_pop(), 1UL);
    check_ulong("mstate_pop empty", mstate_pop(), 0UL);

    p = scan_token("'quoted text' next");
    if (p == (char *)0 || strcmp(p, " next") != 0) {
        fprintf(stderr, "scan_token: unexpected result\n");
        failures++;
    }

    fp = tmpfile();
    if (fp == (FILE *)0) {
        fprintf(stderr, "tmpfile failed\n");
        return 1;
    }
    fputs("one\ttwo\\\nthree\n", fp);
    rewind(fp);
    CurSrcFp = fp;
    check_ulong("read_line continuation", read_line(), 1UL);
    if (strcmp(RawLineBuf, "one     twothree") != 0) {
        fprintf(stderr, "read_line: got <%s>\n", RawLineBuf);
        failures++;
    }
    check_ulong("read_line eof", read_line(), 0UL);
    fclose(fp);

    fp = tmpfile();
    if (fp == (FILE *)0) {
        fprintf(stderr, "tmpfile failed\n");
        return 1;
    }
    fputs("line\n", fp);
    rewind(fp);
    CurSrcFp = fp;
    NoMoreInput = 0;
    LineNo = 0UL;
    check_ulong("get_line line", get_line(), 1UL);
    check_ulong("get_line number", LineNo, 1UL);
    check_ulong("get_line eof", get_line(), 0UL);

    strcpy(RawLineBuf, "LABEL: move x0,y0 ; comment");
    check_ulong("parse_line label", parse_line(), 1UL);
    if (strcmp(LabelField, "LABEL") != 0 ||
        strcmp(MnemField, "move") != 0 ||
        strcmp(Op1Field, "x0,y0") != 0) {
        fprintf(stderr, "parse_line label fields incorrect\n");
        failures++;
    }

    strcpy(RawLineBuf, "    add x0, y0");
    check_ulong("parse_line indented", parse_line(), 1UL);
    if (strcmp(LabelField, "") != 0 ||
        strcmp(MnemField, "add") != 0 ||
        strcmp(Op1Field, "x0,") != 0 ||
        strcmp(Op2Field, "y0") != 0) {
        fprintf(stderr, "parse_line indented fields incorrect\n");
        failures++;
    }

    if (failures != 0)
        return 1;
    puts("OK asm56000 primitives");
    return 0;
}
