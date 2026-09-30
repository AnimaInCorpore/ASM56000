/*
 * elfout.h - private declarations of the COFF to ELF converter
 * (DSPLNK.EXE, CLAS56 v6.3, modules elfout.c / cof2elf.c / abidbg.c).
 * dsplnk.h holds ELFBUF/ELFSEC and the entry points used by the linker.
 */
#ifndef ELFOUT_H
#define ELFOUT_H

#include "dsplnk.h"

/* elfout.c (0x431630-0x4326d0, 0x43271d) */
void elf_write_data2(void *buf, unsigned long size, unsigned long n, FILE *fp);
long strtab_append(ELFBUF *tab, char *name);
void elf_build_header(void);
unsigned long elf_write_maybe_swapped(void *buf, unsigned long size,
                                      unsigned long n, FILE *fp);

/* cof2elf.c (0x432799-0x43329e) */
int read_coff_headers(void);
int read_coff_strtab(long off, long count);
int read_coff_sections(long off, long count);
int test_bit1(unsigned long flags);

/* abidbg.c (0x4335b0-0x433620) */
void dbg_print_str(char *msg, char *val);
void dbg_print_long(char *msg, long val);
void dbg_print_ulong(char *msg, unsigned long val);

#endif
