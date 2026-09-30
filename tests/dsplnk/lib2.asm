; lib2: library module
        section lib2
        xdef    lfunc2,lval
lval    equ     $77
        org     p:
lfunc2  move    #lval,x0
        rts
        endsec
        end
