; macros: arguments, concatenation, value substitution, local labels,
; nested definitions and calls, EXITM, @ARG/@CNT/@MAC/@MXP, DUP family
        opt     mex,cex
        org     p:$100
ldimm   macro   reg,val
        move    #val,reg
        endm
addto   macro   src,dst
        add     src,dst
        endm
clr2    macro
        clr     a
        clr     b
        endm
concat  macro   n
        move    r\n,x:save\n
        endm
valsub  macro   sym
        dc      ?sym,%sym
        endm
loclab  macro
_lab    nop
        jmp     _lab
        endm
quote   macro   str
        dc      "str"
        dc      '\str'
        endm
cnt     macro   p1,p2,p3
        if      @arg(3)
        dc      3,@cnt()
        else
        if      @arg(2)
        dc      2,@cnt()
        else
        dc      1,@cnt()
        endif
        endif
        endm
early   macro   v
        dc      v
        exitm
        dc      v+1
        endm
outer   macro   name,v
name    macro
        dc      v
        endm
        endm
recur   macro   depth
        dc      depth
        if      depth>0
        recur   depth-1
        endif
        endm
isdef   macro   mname
        dc      @mac(mname),@mxp()
        endm
save0   equ     $10
save5   equ     $15
        ldimm   x0,$123456
        ldimm   y1,1
        addto   x0,a
        clr2
        concat  0
        concat  5
        loclab
        loclab
        org     x:$0
        valsub  save5
        valsub  save0
        quote   hello
        cnt     1
        cnt     1,2
        cnt     1,2,3
        early   5
        outer   inmac,$77
        inmac
        recur   3
        isdef   ldimm
        isdef   nothere
        pmacro  clr2,ldimm
        dc      @mac(clr2)
; DUP family
        dup     3
        dc      *
        endm
        dupa    val,1,2,$10
        dc      val
        endm
        dupa    reg,x0,x1
        endm
        dupc    ch,'AB9'
        dc      "ch"
        endm
        dupc    d,'123'
        dc      d*2
        endm
        dupf    i,1,4
        dc      i
        endm
        dupf    j,10,0,-5
        dc      j
        endm
        end
