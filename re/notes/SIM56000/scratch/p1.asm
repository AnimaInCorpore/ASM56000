        org     p:$40
start   move    #5,r0
        move    #$123456,a
        move    #3,x0
        do      #4,loop
        add     x0,a
        inc     b
loop    nop
        move    a,x:(r0)+
        jmp     *
