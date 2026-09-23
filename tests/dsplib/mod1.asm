        SECTION alpha
        XDEF    start,count
        ORG     P:
start   move    #count,r0
        nop
        rts
        ORG     X:
count   DC      1,2,3
        ENDSEC
        END
