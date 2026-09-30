; dbg: assembled with -g for source line debug information
        section debug
        xdef    dfunc
        xref    ufunc
        org     p:
dfunc   move    #1,x0
        jsr     ufunc
        do      #4,dend
        nop
dend    rts
        org     x:
dvar    dc      1,2
        org     y:
dyv     ds      2
        endsec
        end
