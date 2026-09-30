; conditional assembly, DEFINE/UNDEF, symbols from the -d command line option
        opt     cex
        org     x:$0
defd    equ     1
        if      @def(defd)
        dc      defd
        else
        dc      $999
        endif
        define  TWO '2'
        define  STR "'hello'"
        dc      TWO,TWO*TWO
        if      TWO==2
        dc      $22
        if      TWO>1
        dc      $33
        if      TWO<1
        dc      $bad
        else
        dc      $44
        endif
        else
        dc      $bad
        endif
        endif
        undef   TWO
        if      @def(TWO)||@def(undefd)
        dc      $bad
        endif
        if      0
        this is not assembled at all
        if      1
        neither is this
        endif
        else
        dc      $55
        endif
        if      @scp(STR,'hello')
        dc      $66
        endif
        if      !@scp('abc','abd')
        dc      $77
        endif
        if      1&&0||1
        dc      $88
        endif
        if      @len('abcd')!=4
        dc      $bad
        else
        dc      @len('abcd')
        endif
cnt     set     0
        if      cnt
        dc      $bad
        endif
cnt     set     cnt+1
        if      cnt
        dc      cnt
        endif
        end
