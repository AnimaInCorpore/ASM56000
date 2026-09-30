; dup: redefines symbols already exported by util.asm and main.asm
        section dup
        xdef    ufunc,ucnt
        global  mglob
ucnt    equ     13
        org     p:
ufunc   nop
mglob   rts
        endsec
        end
