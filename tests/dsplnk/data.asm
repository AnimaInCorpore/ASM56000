; data module: block data, buffers, overlays, counters and mappings
        section data
        xdef    dtab,dbuf,drev,dovl,dovlend
        org     x:
dtab    dc      'ABC',"de",1.0/4,-0.5
        bsc     5,$aaaaaa
        dsm     8
dbuf    ds      2
        buffer  m,16
bm1     dc      1,2,3
        endbuf
        buffer  r,8
drev    dc      4
        endbuf
        dsr     4
        org     y:
        bsc     3
        dcb     1,2,3
        org     p:
        nop
; overlay: runs at p: but is loaded into x memory
        org     p:,x:
dovl    move    #dtab,r0
        jmp     dovl
dovlend
        org     p:
        rts
; location counters and memory mappings
        org     ph:
hi1     nop
        org     pl:
lo1     jmp     hi1
        org     p(1):
c1      jmp     c1
        org     x(2):
        dc      c1,lo1
        org     pi:
int1    nop
        org     pe:
ext1    jmp     int1
        org     ye:
        dc      ext1
        endsec
        end
