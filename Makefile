ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME with path to its folder and restart application. (you can do it on windows with <setx PVSNESLIB_HOME "/c/snesdev">)")
endif

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules
 
.PHONY: bitmaps all
 
#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := Snesfest


export MAPCONV_4BPP := @python map_converter.py --verbose Textures/4BPP_Set.png
export PALCONV := @python palette_converter.py --verbose
export TILECONV_4BPP := @python tileset_converter.py --verbose 4


all: validate convert_palette converte_tilesets convert_maps $(ROMNAME).sfc preview

clean: cleanBuildRes cleanRom cleanTex

#---------------------------------------------------------------------------------

cleanTex:
	@echo clean graphics data
	@find . -type f -regex '\(.*\.pic\|.*\.map\|.*\.clm\)' -delete

validate:
	@mkdir -p output

converte_tilesets: tileset_bg tileset_obj
	

tileset_obj:
	$(TILECONV_4BPP) Textures/CharacterSet.png output/tiles_obj.bin 

tileset_bg:
	$(TILECONV_4BPP) Textures/4BPP_Set.png output/tiles_bg.bin

convert_palette:
	@echo converting palette
	$(PALCONV) Textures/palette.hex Textures/palette.bin

convert_maps: map_bg1 map_bg2

map_bg1: 
	$(MAPCONV_4BPP) Textures/BG1.png Textures/BG1.bin

map_bg2: 
	$(MAPCONV_4BPP) Textures/BG2.png Textures/BG2.bin


preview: 
	@higan $(ROMNAME).sfc &