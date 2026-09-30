/* Expression parser checks for the recovered evaluator/symbol ABI. */
#include <stdio.h>
#include <string.h>

#include "../../src/asm56000/asm56000.h"

static int failures;

void fatal(char *msg)
{
    fprintf(stderr, "fatal: %s\n", msg);
    ++failures;
}

static void check_value(char *name, char *text, unsigned long expected)
{
    void *value;
    unsigned long got;

    value = eval_expr_text(text);
    if (value == (void *)0) {
        fprintf(stderr, "%s: parse failed\n", name);
        ++failures;
        return;
    }
    got = expr_as_int32(value);
    if (got != expected) {
        fprintf(stderr, "%s: got %08lX want %08lX\n",
                name, got, expected);
        ++failures;
    }
    free_expr(value);
}

int main(void)
{
    unsigned long value[23];
    unsigned long operand[12];
    char regtext[8];
    char *regptr;

    symtab_init();
    sec_init();
    if (!sec_section("code", "global", (char *)0) ||
        sec_endsec() == 0) {
        fprintf(stderr, "section state failed\n");
        ++failures;
    }
    memset(operand, 0, sizeof(operand));
    if (!asm56000_parse_operand_text("#$ff", 0UL, operand, 0, 0, 0, 6) ||
        operand[0] != 11UL || operand[4] != 0xffUL) {
        fprintf(stderr, "immediate addressing parse failed\n");
        ++failures;
    }
    memset(operand, 0, sizeof(operand));
    if (!asm56000_parse_operand_text("(r3)+n3", 0UL, operand,
                                     0, 1, 0, 0) ||
        operand[0] != 5UL || operand[5] != 17UL) {
        fprintf(stderr, "indirect addressing parse failed\n");
        ++failures;
    }
    strcpy(regtext, "A10,");
    regptr = regtext;
    if (match_register_name(&regptr) != 0x28 || *regptr != ',') {
        fprintf(stderr, "register lexer failed\n");
        ++failures;
    }
    if (find_mnemonic("MOVE", 0) == (void *)0 ||
        find_option("nomsw") == (void *)0 ||
        find_processor("56002") == (void *)0 ||
        find_condition("eq") == (void *)0 ||
        find_directive("rev", 0) != (void *)0) {
        fprintf(stderr, "static table lookup failed\n");
        ++failures;
    }
    OptT = 1;
    if (find_directive("rev", 0) == (void *)0) {
        fprintf(stderr, "hidden REV lookup failed\n");
        ++failures;
    }
    check_value("precedence", "1+2*3", 7UL);
    check_value("parentheses", "(1+2)<<2", 12UL);
    check_value("bitwise", "$ff&$0f", 15UL);
    check_value("binary", "%10101", 21UL);
    check_value("comparison", "4>=4", 1UL);
    check_value("unary", "~-1", 0UL);
    check_value("function abs", "@ABS(-4)", 4UL);
    check_value("function pow", "@POW(2,3)", 8UL);
    check_value("function field", "@FLD(0,-1,8)", 0xffUL);
    check_value("function long", "@LNG(1,2)", 0x01000002UL);

    Pass = 1UL;
    LabelField = (char *)"bar";
    Op1Field = (char *)"41";
    if (!pseudo_dispatch("set")) {
        fprintf(stderr, "SET pseudo-op failed\n");
        ++failures;
    }
    check_value("set symbol", "bar+1", 42UL);

    value[0] = 0UL;
    value[1] = 0UL;
    value[2] = 40UL;
    value[3] = 0UL;
    value[4] = 0x100UL;
    value[5] = 3UL;
    value[6] = 0UL;
    value[7] = 4UL;
    value[8] = 4UL;
    value[9] = 0UL;
    value[10] = 0UL;
    value[11] = 0UL;
    value[12] = 0UL;
    value[13] = 0UL;
    value[14] = 0UL;
    value[15] = 0xffffffffUL;
    value[16] = 0UL;
    value[17] = 0UL;
    value[18] = 0UL;
    value[19] = 0UL;
    value[20] = 0UL;
    value[21] = 0xffffffffUL;
    value[22] = 0UL;
    if (!sym_define("foo", value)) {
        fprintf(stderr, "sym_define failed\n");
        ++failures;
    }
    check_value("symbol", "foo+2", 42UL);
    if (failures != 0)
        return 1;
    puts("OK asm56000 expression");
    return 0;
}
