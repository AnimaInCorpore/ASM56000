/*
 * formarr.c - DSPLNK.EXE (CLAS56 v6.3, DSP Linker 6.3.7), module formtableInfArray.c
 * (code at 0x434e80..435400): the InfArray container instantiation used for
 * this table; the body is shared, see infarr.inc.
 */
#include "abi.h"

#define IA_PFX formarr_
#define IA_NAME FormArr
#define IA_ELEM struct abiform *
#define IA_FILE "formtableInfArray.c"
#define IA_CREATE_RET FormArr *
#include "infarr.inc"
