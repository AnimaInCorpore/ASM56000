; main module: references to external code/data with every address form
        section main
        xdef    mstart,mdata,mtab
        xref    ufunc,ufunc2,uxdat,uydat,uiop,ucnt,ushort,uldat
        global  mglob
        org     p:
mstart  jsr     ufunc           ; long absolute address (extension word)
        jmp     <ufunc2         ; short 12-bit jump address
        jsr     <ufunc2
        jcc     ufunc
        jscs    <ufunc
        move    x:uxdat,a       ; long absolute X address
        move    y:uydat,b
        move    x:<ushort,x0    ; short 6-bit absolute address
        move    y:<ushort,y0
        move    #uxdat,r0       ; long immediate
        move    #<ushort,r1     ; short 8-bit immediate
        move    #>ucnt,x1       ; forced long immediate
        movep   x:<<uiop,a      ; I/O short address
        movep   #$12,x:<<uiop
        bset    #3,x:<<uiop
        jclr    #1,x:<<uiop,ufunc
        jset    #2,x:<ushort,ufunc2
        do      #ucnt,mloop     ; immediate count, loop address
        nop
mloop
        rep     #ucnt
        nop
        move    l:uldat,a
        move    l:<ushort,b
        move    #ufunc+2,r2     ; expression, deferred
        move    #ufunc2-ufunc,r3 ; difference of two externals
        move    x:uxdat+1,y0
mglob   rts
        org     x:
mdata   dc      uxdat,uxdat+5,uydat-1
        dc      ucnt*2,ucnt/2,ucnt<<3,ucnt>>1,-ucnt,~ucnt
        dc      ucnt&$f0,ucnt|1,ucnt^$ff,ucnt%7
        dc      ufunc2-ufunc,mstart,mloop
mtab    ds      3
        org     y:
        dc      mdata,mtab+1,ufunc
        org     l:
        dc      mstart
        endsec
        end     mstart
