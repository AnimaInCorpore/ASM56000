; big: absolute values that are too large for short address/immediate forms
        section big
        xdef    bigval,iobad,uzero,neg,hugev
bigval  equ     $1234
iobad   equ     $0040
uzero   equ     0
neg     equ     -5
hugev   equ     $7fffff
        endsec
        end
