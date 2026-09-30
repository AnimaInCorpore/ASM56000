/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), abistub.c
 * Port only: stand-ins for the ABI expression parser (abiparse.c,
 * abilex.c, the InfArray modules; 00433d00-0043a40d) and the COFF to ELF
 * debug file converter (cof2elf.c, 004326d0-004332ae), which are not
 * reconstructed.  They print nothing and fail safely:
 *  - abi_expr_eval/abi_expr_eval_impl return NULL = "not an ABI expression",
 *    so the callers fall back to the normal expression evaluator;
 *  - abimparr_create returns NULL and abi_mp_symtbl_dispatch ignores a NULL
 *    array (as the original does);
 *  - coff_to_elf returns 1 (failure: main warns and continues).
 */
#include "dsplnk.h"

int coff_to_elf(char *coff_path, char *elf_path)
{
    (void)coff_path;
    (void)elf_path;
    return 1;
}

EXPR *abi_expr_eval(MODULE *mod, long flag, char *text)
{
    return abi_expr_eval_impl(mod, flag, text);
}

EXPR *abi_expr_eval_impl(MODULE *mod, long flag, char *text)
{
    (void)mod;
    (void)flag;
    (void)text;
    return NULL;
}

void abi_free_all(void)
{
    abi_modules = NULL;
}

void *abimparr_create(long init, long blk, void (*freefn)(void *))
{
    (void)init;
    (void)blk;
    (void)freefn;
    return NULL;
}

void abi_mp_sym_free_with_arr(void *elem)
{
    (void)elem;
}

void abi_mp_symtbl_dispatch(void *arr, MODULE *mod)
{
    (void)arr;
    (void)mod;
}
