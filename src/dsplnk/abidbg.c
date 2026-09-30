/*
 * DSPLNK linker (CLAS56 v6.3, DSP Linker 6.3.7), abidbg.c
 * Debug print helpers of the ABI subsystem (0x4335b0-0x433620); the
 * original never calls them.
 */
#include "elfout.h"

void dbg_print_str(char *msg, char *val)
{
    printf("Msg: %s, Val: %s \n", msg, val);
}

void dbg_print_long(char *msg, long val)
{
    printf("Msg: %s, Val: %ld \n", msg, val);
}

void dbg_print_ulong(char *msg, unsigned long val)
{
    printf("Msg: %s, Unsigned long Val: %lu \n", msg, val);
}
