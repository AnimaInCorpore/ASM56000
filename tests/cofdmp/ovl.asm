; overlays: run-time and load-time counters differ
        org     p:$100,y:$200
ovlcode move    #1,a
        nop
        org     x:$10,p:$300
        dc      $123456,$654321
        org     pe:$20
extcode nop
        org     xi:$5
        dc      7
        org     p:$400
        dc      *
        end
