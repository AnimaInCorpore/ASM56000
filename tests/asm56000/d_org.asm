; ORG: runtime/load spaces, location counters, memory mapping
        org     p:$100
        opt     cex
start   nop
        org     x:$10
xv      dc      1
        org     y:$20
yv      dc      2
        org     l:$30
lv      dc      $123456654321
        org     p:
        nop
        org     x:
xv2     dc      3
        org     pl:$400
low1    nop
        org     ph:$800
high1   nop
        org     pl:
low2    nop
        org     ph:
high2   nop
        org     p(1):$500
c1      nop
        org     p(2):$600
c2      nop
        org     p(1):
c1b     nop
        org     x(7):$40
xc7     dc      7
        org     pi:$10
int1    nop
        org     pe:$1000
ext1    nop
        org     xi:$50
        dc      $50
        org     ye:$2000
        dc      $2000
        org     pr:$e00
rom1    nop
; runtime counter differs from load counter
        org     p:$40,p:$1040
ovl     nop
        jmp     ovl
ovend
        org     p:$60,x:$300
        nop
        move    #ovl,r0
        org     x:$70,y:$80
        dc      1,2,3
        org     l:$90,l:$190
        dc      5
        org     p:,p:
        nop
        org     pl:$700,ph:$900
        nop
        org     p(3):$a00,pe:$b00
        nop
; @LCV/@LCV and the * location counter symbol
        org     p:$c00
here    dc      *,@lcv(r),@lcv(l),@lcv(r,l),@lcv(l,l),@lcv(r,h)
        org     p:$d00,p:$e00
        dc      *,@lcv(r),@lcv(l)
        org     p:$50
        end     start
