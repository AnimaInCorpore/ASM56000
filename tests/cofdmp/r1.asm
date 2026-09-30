; relocatable module with sections, external references and a float
        section modone
        xdef    entry1,buf1,fval
        xref    extfn
fval    equ     3.14159
        org     p:
entry1  move    #buf1,r0
        jsr     extfn
        move    #>tbl,r1
        move    x:(r0)+,a
        rts
        org     x:
buf1    ds      10
tbl     dc      1,2,3
        endsec
        section eightchr
        org     y:
yval    dc      $123456
        endsec
        section lsect
        org     l:
lval    dc      $123456789abc
        bsc     4,$111111222222
        endsec
