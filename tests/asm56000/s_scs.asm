; structured control statements (.IF/.WHILE/.REPEAT/.FOR/.LOOP ...)
        opt     mex,cex
        org     p:$100
start
        .if     <cs>
        nop
        .endi
        .if     <eq> then
        clr     a
        .else
        clr     b
        .endi
        .if     x0 <gt> a then
        inc     a
        .endi
        .if     a <le> b and <cc>
        nop
        .endi
        .if     b <ne> y1 or a <lt> x1
        nop
        .else
        rts
        .endi
        .if     <ge>
        .if     <mi>
        nop
        .endi
        .endi
        .while  a <gt> b do
        sub     x0,a
        .endw
        .while  <nr>
        nop
        .endw
        .repeat
        dec     b
        .until  <eq>
        .repeat
        add     x1,a
        .until  a <ge> y0 and <pl>
        .for    r0 = #0 to #10
        nop
        .endf
        .for    x0 = #1 to #20 by #2 do
        add     x0,a
        .endf
        .for    n1 = y0 downto #0 by #1
        nop
        .endf
        .for    x:$10 = #5 to x1
        nop
        .endf
        .loop   #5
        nop
        .endl
        .loop   x0
        nop
        .break
        nop
        .continue
        nop
        .endl
        .while  <cs>
        .if     <eq>
        .break
        .endi
        .if     <ne>
        .continue
        .endi
        nop
        .endw
        scsjmp  short
        .if     <eq>
        nop
        .endi
        scsjmp  long
        .if     <eq>
        nop
        .endi
        scsreg  y1,b
        .for    r2 = #1 to #3
        nop
        .endf
        end
