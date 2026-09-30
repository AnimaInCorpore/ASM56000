; page layout directives: PAGE, TITLE, STITLE, LSTCOL, TABS, LIST/NOLIST, PRCTL
        page    100,30,2,3,4
        title   'Listing layout test'
        stitle  'first subtitle'
        prctl   $1b,'E'
        org     p:$0
lab1    move    #1,x0           ; a comment
        mac     x0,y0,a x:(r0)+,x0      y:(r4)+,y0      ; parallel
        nop
	nop	; tab separated fields
        page
        stitle  'second subtitle after an explicit page eject'
        lstcol  12,6,20,15,15
averylonglabelname move  #$123456,x1  ; long label
        mac     x0,y0,a x:(r0)+,x0      y:(r4)+,y0      ; parallel
        lstcol
        tabs    4
	move	#2,x0	; tabs expanded with a tab stop of 4
        tabs    8
        nolist
        nop                     ; not listed
        nop
        list
        nop                     ; listed again
        dup     20
        nop
        endm
        page    132,0
        stitle  'page length zero: no page breaks'
        dup     20
        nop
        endm
        page    80,20
        title   'new title'
        dup     30
        nop                     ; comment that runs past the page width to show how the listing folds long lines
        endm
        end
