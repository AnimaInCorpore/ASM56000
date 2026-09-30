; symbols defined on the command line with -d <symbol> <string>
        opt     cex
        org     x:$0
        dc      FOO,BAR
        dc      FOO*2
        org     p:$0
        move    #FOO,x0
        end
