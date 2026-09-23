; simple smoke test for the CLAS56 toolchain
        page    132,66
        org     p:$100
start   move    #$123456,x0
        move    #>tab,r0
        do      #10,loop
        mac     x0,y0,a   x:(r0)+,x0  y:(r4)+,y0
loop
        jmp     start
        org     x:$0
tab     dc      1,2,3,4,5
        org     y:$10
ytab    ds      8
        org     l:$20
ltab    dc      $123456789abc
        end     start
