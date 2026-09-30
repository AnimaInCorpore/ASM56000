#!/bin/sh
# Regenerate the DSPLNK test inputs with the fixed-time original tools.
# usage: sh mkinputs.sh   (from anywhere; writes into this directory)
cd "$(dirname "$0")"
BIN=../../re/bin_ft
ASM="$BIN/ASM56000.EXE -q"
LIB="$BIN/DSPLIB.EXE -q"
LNK="$BIN/DSPLNK.EXE -q"
set -e

# relocatable objects
for m in main util start data vec vec2 dup dupg undef case1 case2 big range \
         lib1 lib2 lib2b lib3 uselib ovb; do
    $ASM -b$m.cln $m.asm >/dev/null
done
# with source line debug information
$ASM -g -bdbg.cln dbg.asm >/dev/null
# absolute object: no relocation information
$ASM -a -babs.cld abs.asm >/dev/null

# libraries
rm -f mylib.clb duplib.clb
$LIB -c mylib.clb lib1.cln lib2.cln lib3.cln >/dev/null
$LIB -c duplib.clb lib2.cln lib2b.cln >/dev/null

# incremental link output used as linker input
$LNK -i -binc.cln main.cln util.cln >/dev/null || true

# mem*.mem / membad*.mem are hand-written DSPLNK memory control files
# (-r); they are plain text, not assembler output, so nothing to
# regenerate here. Their syntax (MEMORY/RESERVE/SECTION/SYMBOL/MAP/
# REGION.../ENDR/INCLUDE, $-hex addresses, ';' comments) was confirmed
# against re/bin_ft/DSPLNK.EXE -r by hand; see cases.txt for how they
# are exercised.
