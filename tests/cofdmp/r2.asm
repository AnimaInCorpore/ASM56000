        section modtwo
        xdef    extfn
        xref    buf1
        org     p:
extfn   move    x:buf1,a
        rep     #3
        nop
        rts
        endsec
