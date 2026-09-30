/*
 * mparr.c - DSPLNK.EXE (CLAS56 v6.3, DSP Linker 6.3.7), module ABI_mp_symtblInfArray.c
 * (code at 0x434550..434b00): the InfArray container instantiation used for
 * this table; the body is shared, see infarr.inc.
 */
#include "abi.h"

#define IA_PFX abimparr_
#define IA_NAME MpArr
#define IA_ELEM void *
#define IA_FILE "ABI_mp_symtblInfArray.c"
#define IA_CREATE_RET void *
#include "infarr.inc"
