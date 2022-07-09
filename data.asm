.include "hdr.asm"

.section ".rodata1" superfree

snesfont: .incbin "pvsneslibfont.pic"
snesfont_end:

m0: .incbin "Textures/bg0.map"
m0_end:

p0: .incbin "Textures/bg0.pal"
p0_end:

t0: .incbin "Textures/bg0.pic"
t0_end:

.ends