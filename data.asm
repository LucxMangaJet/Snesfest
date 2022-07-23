.include "hdr.asm"

.section ".rodata1" superfree

d_pal:              .incbin "Textures/palette.bin"
d_pal_end:

d_obj_tiles:        .incbin "Textures/CharacterSet.bin"
d_obj_tiles_end:

d_bg_tiles:         .incbin "Textures/BackgroundSet4BPP.bin"
d_bg_tiles_end;

d_map_bg1:          .incbin "Maps/map1.bin"
d_map_bg1_end:

.ends