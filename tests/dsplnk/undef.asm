; undef: references to symbols that nobody defines
        section undef
        xref    nosuch,nosuch2,ufunc
        org     p:
        jsr     nosuch
        move    #nosuch2+1,r0
        jmp     ufunc
        org     x:
        dc      nosuch*3
        endsec
        end
