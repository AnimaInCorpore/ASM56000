#include <stdio.h>
#include <string.h>

#include "../../src/asm56000/asm56000.h"

static int failures;

int which_field(char *msg)
{
    (void)msg;
    return 0;
}

void wrap_message(int indent, char *msg)
{
    (void)indent;
    (void)msg;
}

void lst_putstr(char *msg)
{
    (void)msg;
}

void lst_newline(void)
{
}

static void expect_word(char *name, char *mnemonic, char *operands,
                        unsigned long expected, int count)
{
    int got_count;

    MnemField = mnemonic;
    Op1Field = operands;
    Op2Field = (char *)"";
    got_count = proc_instr_name(mnemonic) ? asm56000_last_count() : -1;
    if (got_count != count || asm56000_last_word(0) != expected) {
        fprintf(stderr, "%s: got %d/%06lX want %d/%06lX\n", name,
                got_count, asm56000_last_word(0), count, expected);
        ++failures;
    }
}

int main(void)
{
    symtab_init();
    sec_init();
    Pass = 2UL;
    expect_word("nop", "nop", "", 0x000000UL, 1);
    expect_word("andi", "and", "#$fe,mr", 0x00feb8UL, 1);
    expect_word("rep", "rep", "#$123", 0x0623a1UL, 1);
    expect_word("short jump", "jmp", "$200", 0x0c0200UL, 1);
    expect_word("ea jump", "jmp", "(r1)", 0x0ae180UL, 1);
    expect_word("bit absolute", "bset", "#5,y:$10", 0x0a1065UL, 1);
    if (failures != 0)
        return 1;
    puts("OK asm56000 instruction encoding");
    return 0;
}
