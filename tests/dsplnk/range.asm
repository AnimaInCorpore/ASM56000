; range: short forms whose external values do not fit
        section range
        xref    bigval,iobad,uzero,neg,hugev,ufunc,uxdat
        org     p:
rstart  jmp     <bigval
        move    x:<bigval,a
        move    #<bigval,r0
        movep   x:<<iobad,a
        bset    #3,x:<<iobad
        jclr    #1,x:<bigval,rstart
        do      #bigval,rend
        rep     #bigval
        move    l:<bigval,a
        move    #>hugev*4,x0
rend    nop
        org     x:
        dc      100/uzero,100%uzero
        dc      hugev*$100
        dc      ufunc-uxdat
        dc      ufunc+ufunc
        dc      ufunc*2
        dc      1<<neg
        endsec
        end
