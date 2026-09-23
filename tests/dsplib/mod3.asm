        SECTION gamma
        XDEF    tab
        ORG     Y:
tab     DC      $123456,$654321,$ABCDEF,0,0,0,0,0
        ENDSEC
        SECTION delta
        XDEF    fn
        ORG     P:
fn      move    y:tab,a
        rts
        ENDSEC
        END
