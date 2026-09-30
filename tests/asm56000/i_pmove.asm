; parallel data moves: every move class and effective address mode
xs      equ     $12
xl      equ     $1234
ys      equ     $3f
yl      equ     $ffc0
        org     p:$100
; immediate short (I)
        add     x0,a    #$12,x0
        add     x0,a    #$ff,x1
        sub     y0,b    #$7f,y0
        add     x0,a    #$55,y1
        tfr     x0,b    #$80,a
        tst     a       #1,b
        clr     a       #$1f,r0
        clr     b       #$20,n3
        move    #$0a,m7
        move    #$12,a0
        move    #$12,b1
        move    #$12,a2
; register to register (R)
        add     x0,a    x1,b
        add     y0,a    a,x0
        add     x1,b    b,y1
        clr     a       r0,r1
        clr     b       n7,r0
        tfr     a,b     a1,x0
        move    x0,y0
        move    a,b
        move    b0,r3
        move    m1,n2
        move    a2,x1
        move    r4,a
; address register update (U)
        add     x0,a    (r0)+n0
        add     x0,a    (r1)-n1
        add     x0,a    (r2)+
        add     x0,a    (r3)-
        move    (r4)+n4
        move    (r7)-
; X memory moves, every ea
        move    x:(r0)-n0,x0
        move    x:(r1)+n1,x1
        move    x:(r2)-,y0
        move    x:(r3)+,y1
        move    x:(r4),a
        move    x:(r5+n5),b
        move    x:-(r6),a0
        move    x:xs,a1
        move    x:xl,b1
        move    x:<xs,a2
        move    x:>xs,b2
        move    x:$ffc5,b0
        move    x:<<$ffe0,r0
        move    #$123456,x0
        move    #>$12,x1
        move    #<$12,x1
        move    #>xl,r7
        move    x0,x:(r0)-n0
        move    a,x:(r1)+n1
        move    b0,x:(r2)-
        move    r3,x:(r3)+
        move    n4,x:(r4)
        move    m5,x:(r5+n5)
        move    y1,x:-(r6)
        move    a2,x:xs
        move    a1,x:xl
        add     x0,a    x:(r0)+,x1
        add     x0,a    a,x:(r7)+n7
        mac     x0,y0,b x:(r2)+,y1
; Y memory moves
        move    y:(r0)-n0,x0
        move    y:(r1)+n1,x1
        move    y:(r2)-,y0
        move    y:(r3)+,y1
        move    y:(r4),a
        move    y:(r5+n5),b
        move    y:-(r6),a0
        move    y:ys,a1
        move    y:yl,b1
        move    y:<ys,a2
        move    y:>ys,b2
        move    y:<<$ffc0,r1
        move    x0,y:(r0)-n0
        move    a,y:(r1)+n1
        move    b,y:$3f
        move    n0,y:$1234
        sub     x1,b    y:(r7)-n7,a
        mpy     x0,x1,a b,y:(r4)+
; long memory moves
        move    l:(r0)+,a10
        move    l:(r1)-,b10
        move    l:(r2)+n2,x
        move    l:(r3)-n3,y
        move    l:(r4),a
        move    l:(r5+n5),b
        move    l:-(r6),ab
        move    l:$10,ba
        move    l:$1234,a
        move    l:<$10,b
        move    l:>$10,x
        move    a10,l:(r0)+
        move    b10,l:(r1)+n1
        move    x,l:$20
        move    y,l:$4321
        move    ab,l:(r7)
        move    ba,l:-(r2)
        add     x,a     l:(r0)+,y
        sub     y,b     a,l:(r4)-n4
; X:R class I and II
        add     x0,a    x:(r0)+,x0      a,y0
        add     x0,a    x:(r1)-,x1      b,y1
        sub     y0,b    x:$12,a         a,y0
        add     y0,a    x:$1234,b       a,y1
        add     x0,a    a,x:(r2)+n2     a,y0
        mac     x0,y0,b x0,x:(r3)       b,y1
        add     x0,a    #$123456,x0     a,y0
        add     y1,b    #>$10,x1        b,y1
        add     y0,b    a,x:(r4)+       x0,a
        add     y1,a    b,x:(r5)-       x0,b
; R:Y class I and II
        add     x0,a    a,x0            y:(r4)+,y0
        add     x0,a    b,x1            y:(r5)-,y1
        sub     x1,b    a,x0            y:$12,a
        sub     x1,a    b,x1            y:$1234,b
        sub     x1,b    a,x0            b,y:(r6)+n6
        add     x0,a    b,x1            #$123456,y0
        add     x0,b    y0,a            a,y:(r0)+
        add     x1,a    y0,b            b,y:(r1)-n1
; XY double moves, every allowed ea combination
        mac     x0,y0,a x:(r0)+,x0      y:(r4)+,y0
        mac     x0,y0,a x:(r1)-,x1      y:(r5)-,y1
        mac     x0,y0,a x:(r2)+n2,b     y:(r6)+n6,y0
        move    x:(r2)+n2,a     y:(r6)+n6,b
        move    x:(r3),b        y:(r7),a
        move    x:(r4)+,x0      y:(r0)+,y0
        move    x:(r5)+n5,x1    y:(r1)-,y1
        move    x0,x:(r0)+      y0,y:(r4)+
        move    a,x:(r1)+n1     b,y:(r5)+n5
        move    b,x:(r2)        a,y:(r6)
        move    x:(r3)+,a       y1,y:(r7)-
        move    x1,x:(r0)+n0    y:(r4)-,b
        end
