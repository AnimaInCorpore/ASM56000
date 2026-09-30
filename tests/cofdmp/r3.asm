; buffers, macros, local labels, block data, overlays of memory spaces
        section bufsec
        xdef    cbuf,rbuf,mac1
        org     x:
        buffer  m,16
cbuf
        dc      1,2,3
        endbuf
        buffer  r,8
rbuf
        endbuf
        org     y:
ydata   dc      $aaaaaa
        dsm     32
yblk    bsc     10,$55
        org     p:
mymac   macro   arg
        move    #arg,a
        endm
mac1    mymac   5
_loc    nop
        mymac   7
        jmp     _loc
        endsec
        section big_section_name_here
        org     l:
lbig    dc      0.5,-0.25
        org     p:
        dc      "text string"
        endsec
