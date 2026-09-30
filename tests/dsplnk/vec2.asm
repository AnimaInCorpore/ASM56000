; vec2: absolute section overlapping vec.asm
        section vect2
        org     p:$1
        nop
        nop
        org     x:$100
        dc      $55
        endsec
        end
