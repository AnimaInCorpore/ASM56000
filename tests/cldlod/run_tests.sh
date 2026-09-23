#!/bin/sh
# cldlod regression tests (inputs made with re/bin_ft/ASM56000.EXE)
C="python ../compare.py"
$C cldlod t1.cld
$C cldlod t2.cld
$C cldlod t2rel.cln
$C cldlod t1.asm
$C cldlod
$C cldlod nofile
