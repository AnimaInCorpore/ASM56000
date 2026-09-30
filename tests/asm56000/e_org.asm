; malformed ORG / EQU / SET / DS operands
        org     p:$100
        org     q:$0
        org
        org     $10
        org     xy:$0
        org     p:$0,
        org     x:$0,q:$0
        equ     5
        set     5
lab1    equ
lab2    set
lab3    =
        ds
        dsm
        end
