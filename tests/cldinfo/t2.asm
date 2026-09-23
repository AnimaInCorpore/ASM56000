        ident   2,7     ; module ident comment
        comment 'section comment text'
        page    132,66
flt     equ     1.25
negflt  equ     -3.0e-10
abcdefgh equ    $107
averylongsymbolname equ $123
        org     p:$107
entry8  nop
        rep     #5
        nop
        move    #flt,x0
        bsc     20,$A5A5A5
        dc      1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19
        org     x:$40
xdata   bsc     4,$555555
        org     y:$80
ydat8ch dc      $111111,$222222
        org     l:$100
ldata   dc      $00000100000200000300
        bsc     3,$123456789abc
        end     entry8
