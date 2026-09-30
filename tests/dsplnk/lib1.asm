; lib1: library module needing lib2
        section lib1
        xdef    lfunc1
        xref    lfunc2
        org     p:
lfunc1  jsr     lfunc2
        rts
        org     x:
l1dat   dc      1
        endsec
        end
