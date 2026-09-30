; minimal valid source, used for command-line option coverage in cases.txt
FOO     equ     1
        org     p:$0
        nop
        move    #FOO,x0
        end
