; util module: definitions used by main.asm
        section util
        xdef    ucnt,ushort,uiop
ucnt    equ     12
ushort  equ     $21
uiop    equ     $ffe0
        xdef    ufunc,ufunc2,uxdat,uydat,uldat
        xref    mglob
        org     p:
ufunc   move    x:uxdat,a
        jsr     mglob
        rts
ufunc2  nop
        rts
        org     x:
uxdat   dc      $123456,$654321
        org     y:
uydat   dc      1,2,3,4
        org     l:
uldat   dc      $112233445566
        endsec
        end
