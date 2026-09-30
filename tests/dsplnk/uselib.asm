; uselib: references library routines
        section uselib
        xref    lfunc1,lval
        org     p:
        jsr     lfunc1
        move    #lval,r0
        endsec
        end
