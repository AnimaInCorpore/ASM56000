; abs: assembled in absolute mode (-a); not valid linker input
        org     p:$100
astart  nop
        jmp     astart
        end     astart
