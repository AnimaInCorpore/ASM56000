; symbol definition / section-symbol errors (9 distinct messages)
        org     p:$0
lab1    nop
lab1    nop
counter set     1
counter equ     2
val1    equ     1
val1    set     2
        section s1
        local   lab1
        local   999bad
        global  lab1
        xref    lab1
        xdef    lab1
        org     p:
        nop
        endsec
        section
        global  gg2
        end
