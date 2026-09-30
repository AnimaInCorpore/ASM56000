; lib3: library module nobody references (pulled in with -u)
        section lib3
        xdef    lfunc3
        org     p:
lfunc3  nop
        nop
        rts
        org     y:
l3dat   dc      3,3,3
        endsec
        end
