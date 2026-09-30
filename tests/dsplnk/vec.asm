; vec: absolute sections inside a relocatable module
        section vectors
        xref    mglob
        xdef    reset
        org     p:$0
reset   jmp     mglob
        org     p:$20
        jsr     mglob
        endsec
        section vdata
        xref    reset
        org     x:$100
vtab    dc      reset,mglob
        endsec
        end
