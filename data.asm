.include "hdr.asm"

.section ".rodata1" superfree

d_pal:              .incbin "Textures/pallette.pal"
d_pal_end:

d_obj_tiles:        .incbin "Textures/CharacterSet.bin"
d_obj_tiles_end:

d_bg_tiles:         .incbin "Textures/BackgroundSet.bin"
d_bg_tiles_end;

d_map_bg1:          .incbin "Textures/BG1.map"
d_map_bg1_end:

.ends