; sections, XDEF/XREF/GLOBAL/LOCAL, nested sections (relocatable mode)
        opt     cex
gconst  equ     $42
        section main
        xdef    mentry
        xref    helper,extfun,extdat
        global  mglob
        org     p:
mentry  jsr     helper
        jsr     extfun
        move    x:extdat,a
        move    #mdat,r0
        move    #gconst,x0
mglob   nop
        org     x:
mdat    dc      1,2,3
        section inner
        local   ival
        xdef    iexp
        org     p:
iexp    move    #ival,r1
        rts
        org     y:
ival    dc      $55
        endsec
        org     p:
        jmp     iexp
        endsec
        section helpers global
        xdef    helper
        org     p:
helper  move    x:hdat,b
        rts
        org     x:
hdat    ds      4
        endsec
        section stat static
        org     p:
sfun    rts
        endsec
        section main
        org     p:
        nop
        endsec
        org     p:
gstart  jmp     mentry
        org     x:
glx     dc      gstart,mentry
        end     gstart
