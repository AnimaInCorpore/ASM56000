; data definition and storage allocation directives
        opt     cex
        org     x:$0
w1      dc      1,-1,$7fffff,$800000,$ffffff
w2      dc      0.5,-0.5,0.25,-1.0,0.999999,0.0
w3      dc      'ABC','abcd','x',''
w4      dc      "AB","ABCDEF",'it''s'
w5      dc      ('A'+1),('AB'<<8),@cvi(0.5*256),-'a',$41+'a'
w6      dc      w1+2,*,*-w1,(3+4)*5
w7      dc      'ABC'++'DEF'
w8      dc      1,,2
w9      dc      1.5e-3,-2.5E-2,.125,1e-7
        org     y:$0
        ds      3
yds     ds      $10
        dsm     8
ydsm    dsm     16
ydsr    dsr     16
        dsr     8
        ds      1
        org     p:$100
        bsc     4,$123456
pbsc    bsc     3
        bsm     8,$aaaaaa
pbsm    bsm     4
        bsr     8,7
pbsr    bsr     16,$1
        org     x:$200
buf1    buffer  m,16
        dc      1,2,3
        ds      2
        endbuf
        buffer  r,8
        dc      9,8
        endbuf
        baddr   m,32
        dc      1
        baddr   r,4
        org     l:$300
ldat    dc      $1122334455,-1,0.5,1.0e-2
        dc      'ABCDEF'
        ds      2
        bsc     2,$aabbccddeeff
        dup     2
        dc      *
        endm
        align   4
        org     p:$400
        dc      $123,'P'
        end
