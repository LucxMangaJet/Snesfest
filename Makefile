ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME with path to its folder and restart application. (you can do it on windows with <setx PVSNESLIB_HOME "/c/snesdev">)")
endif

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules
 
.PHONY: bitmaps all
 
#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := Snesfest

all: bitmaps $(ROMNAME).sfc preview

clean: cleanBuildRes cleanRom cleanGfx

#---------------------------------------------------------------------------------

preview: 
	@higan $(ROMNAME).sfc &

bitmaps : tex_char tex_pvsneslibfont tex_bg0

tex_char: Textures/mario_sprite.bmp
	@echo convert char sprites...
	$(GFXCONV) -gs16 -pc16 -po16 -n $<

tex_pvsneslibfont: pvsneslibfont.bmp
	@echo convert font with no tile reduction ... $(notdir $@)
	$(GFXCONV) -n -gs8 -po2 -pc4 -pe1 -mR! -m! -p! $<

tex_bg0: Textures/bg0.bmp
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -pc4 -n -gs8 -pe0 -po4 -fbmp -m $<