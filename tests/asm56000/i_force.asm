; forced addressing: < short, > long, << I/O short, forward references
bk      equ     $20
io      equ     $ffe2
        org     p:$300
        move    #$12,x0
        move    #<$12,x0
        move    #>$12,x0
        move    #fwdimm,x0
        move    #<fwdimm,x1
        move    #>fwdimm,y0
        move    x:bk,a
        move    x:<bk,a
        move    x:>bk,a
        move    x:fwdabs,a
        move    x:<fwdabs,a
        move    x:>fwdabs,a
        move    y:io,b
        move    y:<<io,b
        move    y:>io,b
        movep   x:io,a
        movep   x:<<io,a
        movep   x:fwdio,a
        movep   x:<<fwdio,a
        bset    #1,x:io
        bset    #1,x:<<io
        bset    #1,x:>io
        bset    #1,x:fwdio
        bset    #1,x:<fwdabs
        bset    #1,x:<<fwdio
        jclr    #0,x:<<fwdio,*
        jclr    #0,x:<fwdabs,*
        jmp     fwdlab
        jmp     <fwdlab
        jmp     >fwdlab
        jsr     <fwdlab
        jeq     <fwdlab
        jmp     bk
        jmp     >bk
        do      #fwdimm,fwdlab
        rep     #fwdimm
        nop
        move    #<-1,x0
        move    #>-1,x0
        move    #-1,x0
        move    #0.5,x0
        move    #<0.5,x0
        move    #-0.5,a
        movec   #fwdimm,m0
        movec   #<fwdimm,m0
        movec   x:bk,m1
        movec   x:>bk,m1
        movem   p:<bk,x0
        movem   p:>bk,x0
        andi    #<$12,mr
        andi    #fwdimm,ccr
        force   short
        move    x:fwdabs2,a
        jmp     fwdlab2
        force   long
        move    x:bk,a
        jmp     bk
        force   none
        move    x:bk,a
fwdlab  nop
fwdlab2 nop
fwdimm  equ     $10
fwdabs  equ     $30
fwdabs2 equ     $31
fwdio   equ     $ffe9
        end
