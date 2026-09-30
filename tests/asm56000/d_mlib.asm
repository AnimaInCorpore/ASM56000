; MACLIB directive: current directory, and an explicit library directory
; (MACLIB requires a quoted pathname; a DEFINE/-d symbol used bare there is
; textually substituted unquoted and fails "expected quote" - see d_mlibd.asm)
        opt     cex,mex
        maclib  '.'
        maclib  'mlib'
        org     x:$0
        mlcwd
        mlmac2  4,5
        mlmac3
        org     p:$0
        mlmac1  7
        end
