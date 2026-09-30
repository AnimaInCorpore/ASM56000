; macro definition / invocation errors (9 distinct messages)
        org     p:$0
        notdefinedmacro 1,2
mac1    macro   p1,p2
        dc      p1,p2
        endm
mac1    macro   p1,p2
        dc      p1
        endm
        mac1    1,2,3,4
        mac1    1
        exitm
        endm
badexitm exitm
        dupf    i,1,4,0
        dc      i
        endm
        pmacro  neverdefinedmac
        pmacro  9bad
mac2    macro   9bad,p2
        dc      p2
        endm
mac3    macro
        dc      1
