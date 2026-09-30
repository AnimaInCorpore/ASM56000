; general program used with many listing/reporting option combinations
; (see cases.txt: -o s,cre,mu,md,mex,cex,cl,u,loc,nocm,fc,rc,...)
        define  DEFSYM '$1234'
        define  PI_ '3.14159'
MAXC    equ     10
mask    equ     $00ff00
fl      equ     0.75
xdata   equ     $10
count   set     5
count   set     count+1
; a macro that is defined but the definition may be suppressed (nomd)
fill    macro   n,v
        ; comment inside the macro body
        dup     n
        dc      v               ; data word
        endm
        endm
        org     p:$100
begin   move    #DEFSYM,x0      ; operand with define symbol
        move    #mask,x1
        do      #MAXC,_end
        mac     x0,y0,a x:(r0)+,x0      y:(r4)+,y0      ; parallel moves
_end
        jmp     _loop
_loop   nop
next    nop                     ; plain label ends the local label scope
_loop   jmp     _loop
        if      count>5
        nop                     ; assembled conditional part
        else
        rts                     ; skipped conditional part
        endif
        move    #fl,y1
        move    x:xdata,a
        section sec1
        global  subr
        org     p:
subr    move    #>@cvi(PI_*100),x0
_l      rts
        org     x:
sdat    dc      1,2,3,DEFSYM
        endsec
        org     p:
        jsr     subr
        org     x:$20
tab     fill    3,$aa
        dc      'a string that is longer than one word',0
        dc      'abcdefgh'
        ds      4
        org     y:$0
ytab    dc      -1,-0.5,0.5
        bsc     5,$5
        org     l:$20
ltab    dc      $1,-1
        end     begin
