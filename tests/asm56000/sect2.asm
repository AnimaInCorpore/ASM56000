; second module assembled together with sect1.asm
        section lib
        xdef    extfun,extdat
        org     p:
extfun  move    x:extdat,a
        rts
        org     x:
extdat  dc      $123456
        endsec
        end
