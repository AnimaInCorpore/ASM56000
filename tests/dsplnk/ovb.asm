; ovb: buffers inside overlays (runtime counter differs from load counter)
        section ovb
        org     x:,y:
        dc      1
        buffer  m,8
ob1     dc      1,2
        endbuf
        buffer  r,4
ob2     dc      3
        endbuf
        endsec
        end
