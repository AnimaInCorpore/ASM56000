/* Initial pseudo-op semantics: symbol, section, visibility, and OPT state. */
#include <ctype.h>
#include <string.h>

#include "asm56000.h"

#define PSEUDO_SET 0x10UL
#define PSEUDO_EQU 0x400UL

static int text_equal(char *a, char *b)
{
    return strcmp(str_lower_copy(a), b) == 0;
}

static int define_value(unsigned long flags)
{
    void *value;
    unsigned long *words;

    if (LabelField == (char *)0 || *LabelField == '\0' ||
        Op1Field == (char *)0 || *Op1Field == '\0')
        return 0;
    value = eval_expr_text(Op1Field);
    if (value == (void *)0)
        return 0;
    words = (unsigned long *)value;
    words[ASM56000_EXPR_W6 / 4] |= flags;
    if (Pass == 0UL)
        Pass = 1UL;
    flags = (unsigned long)sym_define(LabelField, value);
    if (Pass == 1UL && (flags != 0UL || PSEUDO_EQU != 0UL))
        ++AsmEquCount;
    free_expr(value);
    return flags != 0UL;
}

static int apply_opt(char *name)
{
    void *entry;
    unsigned long id;
    char copy[256];
    char *part;

    if (name == (char *)0 || *name == '\0')
        return 0;
    if (strchr(name, ',') != (char *)0) {
        if (strlen(name) >= sizeof(copy))
            return 0;
        strcpy(copy, name);
        part = strtok(copy, ",");
        while (part != (char *)0) {
            if (!apply_opt(part))
                return 0;
            part = strtok((char *)0, ",");
        }
        return 1;
    }

    entry = find_option(name);
    if (entry == (void *)0)
        return 0;
    id = table_entry_id(entry);
    if (id == 0x28UL)
        OptIC = 1;
    else if (id == 0x20UL)
        OptXR = 1;
    else if (id == 0x41UL)
        OptUR = 1;
    else if (id == 0x4dUL) {
        OptWarn = 1;
        SectionGlobalCounters = 1;
    }
    else if (id == 0x12UL)
        OptWarn = 0;
    else if (id == 0x4bUL)
        OptIC = 0;
    else if (id == 0x42UL)
        OptUR = 0;
    else if (id == 0x3bUL)
        OptSi = 1;
    else if (id == 0x3cUL)
        OptSi = 0;
    else if (id == 6UL) {
        OptCm = 1;
        SourceCexDirective = 1;
        SourceOptCex = 1;
    }
    else if (id == 0xdUL)
        OptCm = 0;
    else if (id == 5UL)
        ListingReportCrossRef = 1;
    else if (id == 0x19UL)
        ListingReportMemory = 1;
    else if (id == 0x1aUL)
        ListingReportLocals = 1;
    else if (id == 0x2fUL)
        SectionGlobalCounters = 1;
    else if (id == 0x13UL)
        ListingReportSymbols = 1;
    else if (id == 0x16UL)
        ListingSeparateComments = 1;
    else if (id == 8UL)
        OptMd = 1;
    else if (id == 0xfUL)
        OptMd = 0;
    else if (id == 9UL)
        OptMex = 1;
    else if (id == 0x10UL)
        OptMex = 0;
    else if (id == 0x39UL)
        set_opt_rp(1);
    else if (id == 0x3aUL)
        set_opt_rp(0);
    return 1;
}

int pseudo_dispatch(char *name)
{
    if (name == (char *)0)
        return 0;
    if (text_equal(name, "set") || text_equal(name, "="))
        return define_value(PSEUDO_SET);
    if (text_equal(name, "equ"))
        return define_value(PSEUDO_EQU);
    if (text_equal(name, "define")) {
        void *value;

        if (Op1Field == (char *)0 || *Op1Field == '\0' ||
            Op2Field == (char *)0 || *Op2Field == '\0')
            return 0;
        value = eval_expr_text(Op2Field);
        if (value == (void *)0)
            return 0;
        sym_define(Op1Field, value);
        free_expr(value);
        return 1;
    }
    if (text_equal(name, "undef")) {
        if (Op1Field == (char *)0 || *Op1Field == '\0')
            return 0;
        return sym_undef(Op1Field);
    }
    if (text_equal(name, "section")) {
        char *mods[2];
        int i;

        if (Op1Field == (char *)0 || *Op1Field == '\0') {
            CurInstrFieldMsg = (char *)0;
            err("Missing section name");
            return 0;
        }
        if (!isalpha((unsigned char)Op1Field[0])) {
            CurInstrFieldMsg = Op1Field;
            err("Symbols must start with alphabetic character");
            return 0;
        }
        mods[0] = Op2Field;
        mods[1] = Op3Field;
        for (i = 0; i < 2; ++i)
            if (mods[i] != (char *)0 && *mods[i] != '\0' &&
                strcmp(str_lower_copy(mods[i]), "global") != 0 &&
                strcmp(str_lower_copy(mods[i]), "static") != 0 &&
                strcmp(str_lower_copy(mods[i]), "local") != 0 &&
                strcmp(str_lower_copy(mods[i]), "debug") != 0) {
                CurInstrFieldMsg = Op1Field;
                err_s("Invalid section directive modifier", mods[i]);
                return 0;
            }
        return asm_section_enter(Op1Field, Op2Field, Op3Field);
    }
    if (text_equal(name, "endsec")) {
        if (!asm_section_leave()) {
            CurInstrFieldMsg = (char *)0;
            err("ENDSEC without associated SECTION directive");
            return 0;
        }
        return 1;
    }
    if (text_equal(name, "local"))
        return sec_local();
    if (text_equal(name, "global"))
        return sec_global();
    if (text_equal(name, "xref"))
        return sec_xref();
    if (text_equal(name, "xdef"))
        return sec_xdef();
    if (text_equal(name, "opt")) {
        if (Op1Field == (char *)0)
            return 0;
        return apply_opt(Op1Field);
    }
    if (text_equal(name, "radix"))
        return 1;
    if (text_equal(name, "list") || text_equal(name, "nolist"))
        return 1;
    return 0;
}
