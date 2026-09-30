/*
 * symarr.c - DSPLNK.EXE (CLAS56 v6.3, DSP Linker 6.3.7), module symtableInfArray.c
 * (code at 0x433d00..4342a0): the InfArray container instantiation used for
 * this table; the body is shared, see infarr.inc.
 */
#include "abi.h"

#define IA_PFX symtblarr_
#define IA_NAME SymArr
#define IA_ELEM struct abisym *
#define IA_FILE "symtableInfArray.c"
#define IA_CREATE_RET SymArr *
#include "infarr.inc"
