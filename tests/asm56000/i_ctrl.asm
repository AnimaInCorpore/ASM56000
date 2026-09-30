; program control, bit manipulation, loops, MOVEC/MOVEM/MOVEP, misc.
ioa     equ     $ffe0
iob     equ     $ffff
        org     p:$0
        jmp     start
        org     p:$40
start
; unconditional jumps and subroutine calls
        jmp     start
        jmp     <start
        jmp     >start
        jmp     $0fff
        jmp     $1000
        jmp     (r0)
        jmp     (r1)+
        jmp     (r2)-
        jmp     (r3)+n3
        jmp     (r4)-n4
        jmp     (r5+n5)
        jmp     -(r6)
        jsr     sub1
        jsr     >sub1
        jsr     (r7)
        jsr     $2000
; conditional jumps, every condition code
        jcc     start
        jcs     start
        jec     start
        jeq     start
        jes     start
        jge     start
        jgt     start
        jhs     start
        jlc     start
        jle     start
        jlo     start
        jls     start
        jlt     start
        jmi     start
        jne     start
        jnn     start
        jnr     start
        jpl     start
        jeq     (r0)+
        jne     >start
        jcc     $1234
        jscc    sub1
        jscs    sub1
        jsec    sub1
        jseq    sub1
        jses    sub1
        jsge    sub1
        jsgt    sub1
        jshs    sub1
        jslc    sub1
        jsle    sub1
        jslo    sub1
        jsls    sub1
        jslt    sub1
        jsmi    sub1
        jsne    sub1
        jsnn    sub1
        jsnr    sub1
        jspl    sub1
        jsgt    (r3+n3)
        jsle    $4000
; transfer conditionally, every condition code
        tcc     x0,a
        tcs     x1,b
        tec     y0,a
        teq     y1,b
        tes     a,b
        tge     b,a
        tgt     x0,b    r0,r1
        ths     x1,a    r2,r3
        tlc     y0,b    r4,r5
        tle     y1,a    r6,r7
        tlo     a,b     r7,r0
        tls     b,a     r1,r2
        tlt     x0,a
        tmi     x0,b
        tne     y0,a
        tnn     y1,b
        tnr     x1,a
        tpl     b,a     r3,r4
; bit manipulation, every addressing mode
        bchg    #0,x:(r0)+
        bchg    #23,y:(r1)-n1
        bchg    #5,x:$10
        bchg    #7,y:$3f
        bchg    #1,x:ioa
        bchg    #2,y:iob
        bchg    #3,x:$1234
        bchg    #4,a
        bchg    #12,r3
        bchg    #13,sr
        bclr    #0,x:(r5+n5)
        bclr    #1,y:-(r6)
        bclr    #2,x:$20
        bclr    #3,y:<$20
        bclr    #4,x:<<$fff0
        bclr    #5,y:>$ffc0
        bclr    #6,omr
        bclr    #7,b1
        bset    #8,x:(r2)
        bset    #9,y:(r3)+n3
        bset    #10,x:$00
        bset    #11,y:$ffd0
        bset    #12,x0
        bset    #13,m5
        btst    #14,x:(r4)-
        btst    #15,y:(r7)
        btst    #16,x:$3f
        btst    #17,y:$ffc0
        btst    #18,ssh
        btst    #19,la
; bit test and jump
        jclr    #0,x:(r0)+,start
        jclr    #1,y:(r1),start
        jclr    #2,x:$10,start
        jclr    #3,y:$20,start
        jclr    #4,x:$ffe5,start
        jclr    #5,y:ioa,start
        jclr    #6,a,start
        jclr    #7,sr,start
        jset    #8,x:-(r2),start
        jset    #9,y:$3f,start
        jset    #10,x:$fff0,start
        jset    #11,r4,start
        jsclr   #12,x:(r5)+n5,sub1
        jsclr   #13,y:$05,sub1
        jsclr   #14,x:$ffc1,sub1
        jsclr   #15,omr,sub1
        jsset   #16,y:(r6+n6),sub1
        jsset   #17,x:$00,sub1
        jsset   #18,y:$ffff,sub1
        jsset   #19,lc,sub1
; hardware loops
        do      #10,lp1
        nop
lp1
        do      #$fff,lp2
        nop
lp2
        do      x:(r0)+,lp3
        nop
lp3
        do      y:$10,lp4
        nop
lp4
        do      x0,lp5
        nop
lp5
        do      a,lp6
        nop
lp6
        do      r7,lp7
        nop
lp7
        do      #3,outer
        do      #4,inner
        mac     x0,y0,a x:(r0)+,x0      y:(r4)+,y0
inner
        nop
outer
        do      lc,lp8
        enddo
        nop
lp8
        rep     #12
        asl     a
        rep     #$fff
        nop
        rep     x:(r1)-
        asr     b
        rep     y:$3f
        lsl     a
        rep     n2
        nop
        rep     b
        nop
; control register moves
        movec   x:(r0)+,m0
        movec   y:(r1)-n1,m1
        movec   x:$10,sr
        movec   y:$3f,omr
        movec   x:$1234,la
        movec   #$ffff,m2
        movec   #$12,m3
        movec   #>$12,m4
        movec   x0,m5
        movec   a,lc
        movec   ssh,x0
        movec   sp,r0
        movec   m6,x:(r2)
        movec   m7,y:(r3)+n3
        movec   sr,x:$20
        movec   omr,y:$2000
        movec   la,b
        movec   ssl,y1
        movec   m0,ssh
        move    m1,x:(r4)+
        move    x:(r5),sr
; program memory moves
        movem   p:(r0)+,x0
        movem   p:(r1)-n1,a
        movem   p:$10,y1
        movem   p:$1234,r4
        movem   x1,p:(r2)
        movem   b,p:$3f
        movem   n5,p:$4000
        movem   m3,p:(r3+n3)
        movem   p:<$20,sr
        movem   p:>$20,omr
; peripheral moves
        movep   x:(r0)+,x:ioa
        movep   y:(r1)-n1,x:$ffe1
        movep   x:$1234,y:iob
        movep   y:$10,y:$ffc0
        movep   x:ioa,x:(r2)
        movep   y:iob,x:$20
        movep   x:$fff0,y:(r3)+n3
        movep   #$123456,x:ioa
        movep   #$1,y:$ffc2
        movep   x:ioa,p:(r4)
        movep   p:(r5)+,y:iob
        movep   p:$100,x:$ffe3
        movep   x:$ffe4,p:$100
        movep   x:ioa,a
        movep   y:iob,r3
        movep   b,x:$ffe8
        movep   n7,y:$ffff
        movep   sr,x:ioa
        movep   x:ioa,m0
        movep   x:<<ioa,x:$10
; immediate logic on control registers
        andi    #$fc,mr
        andi    #$fe,ccr
        andi    #$03,omr
        and     #$bf,mr
        ori     #$03,mr
        ori     #$01,ccr
        ori     #$80,omr
        or      #$04,ccr
; misc
        norm    r0,a
        norm    r7,b
        div     x0,a
        div     x1,b
        div     y0,a
        div     y1,b
        lua     (r0)+n0,r1
        lua     (r2)-n2,n3
        lua     (r4)+,r5
        lua     (r6)-,n7
        nop
        illegal
        reset
        stop
        wait
        swi
        rti
sub1    rts
        end     start
