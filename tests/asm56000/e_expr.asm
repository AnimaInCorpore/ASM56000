; expression evaluation errors (13 distinct messages)
        org     x:$0
        dc      1+
        dc      1 2
        dc      (1+2
        dc      #1
        dc      @sqrt(2)
        dc      1.5&2
xsym    equ     x:$5
ysym    equ     y:$5
        dc      xsym+ysym
        org     p:$0
        move    #$1234567,x0
        move    #1.5,a
        move    #$1000000,x0
        do      #-1,dlp
        nop
dlp
        move    x:$10,a         y:$20,b
        dc      3
        jmp     *-fwd2
        dc
        bsc     0,1
        org     p:$100
fwd2
        end
