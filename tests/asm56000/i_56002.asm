; instructions that exist only on later family members (56002/56004/56007)
        org     p:$200
        dec     a
        dec     b
        inc     a
        inc     b
        debug
        debugcc
        debugcs
        debugec
        debugeq
        debuges
        debugge
        debuggt
        debughs
        debuglc
        debugle
        debuglo
        debugls
        debuglt
        debugmi
        debugne
        debugnn
        debugnr
        debugpl
        debuga
        debugal
        debugneq
        jneq    *
        jsneq   *
        tneq    x0,a
        lea     (r0)+n0,r1
        addl    b,a
        end
