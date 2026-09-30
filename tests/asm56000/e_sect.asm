; SECTION/ENDSEC directive errors (5 distinct messages)
        org     p:$0
        section main
        org     p:
        nop
        section main
        org     p:
        nop
        section 9bad
        endsec
        endsec
        endsec
        org     p:$0
        section abc def
        section open1
