.include "hdr.asm"

.section ".rodata1" superfree

; CHAR DATA

char_pic: .incbin "Textures/ObjectLayerSheet.pic"
char_pic_end:

char_pal: .incbin "Textures/ObjectLayerSheet.pal"
char_pal_end:

; BACKGROUND DATA

snesfont: .incbin "pvsneslibfont.pic"
snesfont_end:

m0: .incbin "Textures/TestLevelBackground1.map"
m0_end:

p0: .incbin "Textures/TestLevelBackground1.pal"
p0_end:

t0: .incbin "Textures/TestLevelBackground1.pic"
t0_end:

.ends


.section ".rodata2" superfree

; COLLISION DATA

c0: .incbin "Textures/TestLevelCollisionMap.clm"
c0_end:

.ends