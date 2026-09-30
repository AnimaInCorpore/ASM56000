; addressing mode / register field syntax errors (15 distinct messages)
        org     p:$0
        move    x:(r0+,a
        move    x:(r0,a
        move    x:(r0+n0,a
        move    x:(r0+n0)),a
        move    x:,a
        move    x:(r9)+,a
        move    x:(r0+n9),a
        add     x0,a    x0,a1
        bset    #1,x:(r0
        jclr    #0,a,b,*
        clr     r99
        clr     x9
        move
        move    r0
        move    x0,a    x:(r0)+,a1     y:(r4)+,a
        move    l:(r0)+,x0
        move    ssh,ssh
        bset    #99,a
        end
