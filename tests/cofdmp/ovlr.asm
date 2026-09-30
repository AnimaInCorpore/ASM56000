        section ovsec
        org     p:,y:
ovlcode move    #1,a
        nop
        org     x:,p:
        dc      $123456,$654321
        endsec
