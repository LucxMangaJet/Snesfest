.include "hdr.asm"

.section ".rodata0" superfree

d_pal:              .incbin "output/palette.bin"
d_pal_end:

d_obj_tiles:        .incbin "output/tiles_obj.bin"
d_obj_tiles_end:

d_bg_tiles:         .incbin "output/tiles_bg.bin"
d_bg_tiles_end;

d_map_bg1:          .incbin "output/BG1.bin"
d_map_bg1_end:

.ends