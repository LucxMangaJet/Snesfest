.include "hdr.asm"

.section ".rodata1" superfree

snesfont:                .incbin "pvsneslibfont.pic"


tex_background1_map:     .incbin "Textures/conceptSNES.map"
tex_background1_map_end:

tex_background1_pal:     .incbin "Textures/conceptSNES.pal"
tex_background1_pal_end:

tex_background1_pic:     .incbin "Textures/conceptSNES.pic"
tex_background1_pic_end:



.ends