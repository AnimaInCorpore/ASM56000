; DO/REP loop-nesting and loop-count errors (6 distinct messages)
        org     p:$0
        do      ssh,lp1
        nop
lp1
        do      #3,lp2
lp2     do      #4,lp2
        nop
        do      #3,outer
        do      #4,inner
outer
        nop
inner
        rep     #3
        do      #2,rlp
        nop
rlp
        end
