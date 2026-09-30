/*
 * symtbl.c - DSPLNK.EXE (CLAS56 v6.3, DSP Linker 6.3.7), ABI expression
 * subsystem: symbol table of the ABI scratch variables (0x4343e0-0x4344ff).
 * Elements live in a symtableInfArray (g_symtblarr); they are created by
 * abi_assign_op.
 */
#include "abi.h"

/* 4343e0: the freefn of the symbol table */
void abi_mp_sym_free_elem(ABISYM *elem)
{
    if (elem != NULL) {
        if (elem->name != NULL)
            free(elem->name);
        /* the original also frees a pointer kept in +8 when the type tag
           (+0x10) is 4; abi_assign_op only creates type 3, so no element
           ever owns a pointer and the port drops that branch */
        free(elem);
    }
}

/* 434435 */
ABISYM *abi_mp_sym_alloc(char *name, long v1, long v2, long v3)
{
    ABISYM *e;

    e = (ABISYM *)malloc(sizeof(ABISYM));
    e->name = abi_strdup(name);
    e->lo = (unsigned long)v1 & 0xffffffffUL;
    e->hi = (unsigned long)v2 & 0xffffffffUL;
    e->type = v3;
    e->unused = 0;
    return e;
}

/* 43447d: linear search; the first element whose name matches */
ABISYM *symtbl_find_by_name(SymArr *arr, char *name)
{
    long i;

    if (name == NULL) {
        fprintf(stderr, "Table Search Name NULL");
        return NULL;
    }
    for (i = 0; i <= arr->max_index; i++) {
        if (strcmp((*arr->get)(arr, i)->name, name) == 0)
            return (*arr->get)(arr, i);
    }
    return NULL;
}
