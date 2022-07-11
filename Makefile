ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME with path to its folder and restart application. (you can do it on windows with <setx PVSNESLIB_HOME "/c/snesdev">)")
endif

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules
 
.PHONY: bitmaps all
 
#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := Snesfest

all: bitmaps $(ROMNAME).sfc preview

clean: cleanBuildRes cleanRom cleanTex

cleanTex:
	@echo clean graphics data
	@find . -type f -regex '\(.*\.pic\|.*\.map\|.*\.clm\)' -delete

#---------------------------------------------------------------------------------

preview: 
	@higan $(ROMNAME).sfc &

#--- Graphics options
#-gb               add blank tile management (for multiple bgs)");
#-gp               Output in packed pixel format");
#-glz              Output in lzss compressed pixel format");
#-gs(8|16|32|64)   Size of image blocks in pixels [8]");

#--- Map options
#-m!               Exclude map from output");
#-m                Convert the whole picture");
#-mp               Convert the whole picture with high priority");
#-m7               Convert the whole picture for mode 7 format");
#-m5               Convert the whole picture for mode 5 & 6 512 width hires");
#-mc               Generate collision map only");
#-ms#              Generate collision map only with sprites table");
#                   where # is the 1st tile corresponding to a sprite (0 to 255)");
#-mn#              Generate the whole picture with an offset for tile number");
#                   where # is the offset in decimal (0 to 2047)");
#-mR!              No tile reduction (not advised)");
#-m32p             Generate tile map organized in pages of 32x32 (good for scrolling)");
#-me               Convert the map for PVSneslib map engine");
#-mt(filename)     Tileset picture filename (PNG,BMP,PCX) for PVSneslib map engine matching");

#--- Palette options ---
#-p!               Exclude palette from output.");
#-pc(4|16|128|256) The number of colors to use [256]");
#-po#              The number of colors to output (0 to 256) to the filename.pal");
#-pe#              The palette entry to add to map tiles (0 to 16)");
#-pt#              The palette entry to add to tileset (0 to 16) for PVSneslib map engine");
#-pr               Rearrange palette, and preserve palette numbers in the tilemap");
#-pR               Palette rounding");
#-- File options
#-f[bmp|pcx|tga|png]   convert a bmp or pcx or tga or png file [bmp]");

#--- Misc options ---
#-n                no border");
#-q                quiet mode");

bitmaps: tex_pvsneslibfont tex_bg1

tex_bg1:
	$(GFXCONV) -n -m -gs8 -p! -pc16 -fpng -mtTextures/BackgroundSet.bin Textures/BG1.png

tex_pvsneslibfont: pvsneslibfont.bmp
	@echo convert font with no tile reduction ... $(notdir $@)
	$(GFXCONV) -n -gs8 -po2 -pc4 -pe1 -mR! -m! -p! $<
