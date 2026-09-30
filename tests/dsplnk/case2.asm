; case2: references differ only in case from case1.asm
        section cases2
        xref    MIXEDCASE,LowerCase
        org     p:
        jsr     MIXEDCASE
        jsr     LowerCase
        endsec
        end
