; start: GLOBAL-section startup code with an END start address
        org     p:
entry   jsr     mglob
        jmp     entry
gdat    equ     *
        org     x:
gtab    dc      entry,gdat,mglob+1
        end     entry
