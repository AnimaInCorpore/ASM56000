#!/bin/sh
# cldinfo regression tests (inputs made with re/bin_ft/ASM56000.EXE)
C="python ../compare.py"
$C cldinfo t1.cld
$C cldinfo t2.cld
$C cldinfo t2rel.cln
$C cldinfo t1.asm
$C cldinfo
$C cldinfo nofile
