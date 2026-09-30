/*
 * longarr.c - DSPLNK.EXE (CLAS56 v6.3, DSP Linker 6.3.7), module LONGInfArray.c
 * (code at 0x433620..433bc0): the InfArray container instantiation used for
 * this table; the body is shared, see infarr.inc.
 */
#include "abi.h"

#define IA_PFX longarr_
#define IA_NAME LONGArr
#define IA_ELEM long
#define IA_FILE "LONGInfArray.c"
#define IA_CREATE_RET LONGArr *
#include "infarr.inc"
