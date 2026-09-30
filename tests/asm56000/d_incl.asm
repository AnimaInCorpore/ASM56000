; INCLUDE and MACLIB, with -i and -m search paths (see cases.txt)
        opt     cex,mex
        org     x:$0
        include 'incloc.asm'
        include "incdefs.asm"
        include <incnest.asm>
        dc      incval,nestval
        org     p:$0
        mlmac1  5
        org     x:$20
        mlmac2  1,2
        end
