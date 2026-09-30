#!/bin/sh
# Build the test inputs with the original assembler and linker, then the
# hand-made files.  Run from tests/cofdmp.
R=../../re/bin
$R/ASM56000.EXE -q -b -lr1.lst r1.asm
$R/ASM56000.EXE -q -b -g -lr2.lst r2.asm
$R/ASM56000.EXE -q -b -g -lr3.lst r3.asm
$R/ASM56000.EXE -q -a -bt1.cld -lt1.lst t1.asm
$R/ASM56000.EXE -q -a -g -bt2g.cld -lt2g.lst t2.asm
$R/ASM56000.EXE -q -bt2.cln -lt2.lst t2.asm
$R/ASM56000.EXE -q -g -bt2g.cln -lt2gr.lst t2.asm
$R/ASM56000.EXE -q -a -g -bovl.cld -lovl.lst ovl.asm
$R/ASM56000.EXE -q -g -b -lovlr.lst ovlr.asm
$R/ASM56000.EXE -q -a -z -bstrip.cld -lstrip.lst t1.asm
$R/DSPLNK.EXE -q -blnk.cld r1.cln r2.cln
$R/DSPLNK.EXE -q -g -blnkg.cld r1.cln r2.cln
$R/DSPLNK.EXE -q -i -blnki.cln r1.cln r2.cln
$R/DSPLNK.EXE -q -g -blnk3.cld r3.cln r1.cln r2.cln
$R/DSPLNK.EXE -q -g -i -blnk3i.cln r3.cln r1.cln
$R/DSPLNK.EXE -q -g -bovll.cld ovlr.cln r1.cln r2.cln
python mkcoff.py
