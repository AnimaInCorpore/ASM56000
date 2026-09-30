; srec test: several sections per space, long data, L data and blocks
        org     p:$0
        jmp     main
        org     p:$40
main    move    #$abcdef,x0
        move    x0,x:$10
        dc      $010203,$040506,$070809,$0a0b0c,$0d0e0f,$101112,$131415
        dc      $161718,$191a1b,$1c1d1e,$1f2021,$222324,$252627,$28292a
        nop
        org     x:$100
xt      dc      $111111,$222222,$333333,$444444,$555555,$666666,$777777
        dc      $888888,$999999,$aaaaaa,$bbbbbb,$cccccc,$dddddd,$eeeeee
        bsc     17,$123456
        org     y:$fff0
yt      dc      1,2,3,4,5,6,7,8,9,10,11,12
        org     l:$200
lt      dc      $0102030405060708090a0b0c0d0e0f101112131415161718
        dc      $a1a2a3a4a5a6,$b1b2b3b4b5b6,$c1c2c3c4c5c6,$d1d2d3d4d5d6
        bsc     9,$fedcba987654
        org     y:$20
        bsc     40,$0f0f0f
        end     main
