ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME with path to its folder and restart application. (you can do it on windows with <setx PVSNESLIB_HOME "/c/snesdev">)")
endif

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules
 
.PHONY: bitmaps all
 
#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := Snesfest

export MAPCONV_BG_4BPP := @python3 map_converter.py --verbose Textures/4BPP_Set.png
export PALCONV := @python3 palette_converter.py --verbose


all: bitmaps convert_palette convert_maps $(ROMNAME).sfc preview

clean: cleanBuildRes cleanRom cleanTex

#---------------------------------------------------------------------------------

cleanTex:
	@echo clean graphics data
	@find . -type f -regex '\(.*\.pic\|.*\.map\|.*\.clm\)' -delete


convert_palette:
	@echo converting palette
	$(PALCONV) Textures/palette.hex Textures/palette.bin

convert_maps: map_bg1

map_bg1: 
	$(MAPCONV_BG_4BPP) Textures/BG1.png Textures/BG1.bin


preview: 
	@higan $(ROMNAME).sfc &