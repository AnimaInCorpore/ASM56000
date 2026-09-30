; conditional-assembly / structured-control errors (11 distinct messages)
        org     p:$0
        else
        endif
        .if     a <zz> b
        nop
        .endi
        .for    r0 = #0 downup #10
        nop
        .endf
        .for    r0 #0 to #10
        nop
        .endf
        if      1
        nop
        .if     <eq>
        nop
        .endi
        .while  <cs>
        nop
        .until  <cs>
        .for    r0 = #0 to
        nop
        .endf
