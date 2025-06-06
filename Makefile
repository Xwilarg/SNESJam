ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME by following this guide: https://github.com/alekmaul/pvsneslib/wiki/Installation")
endif

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules

.PHONY: bitmaps all

#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := snesjam

all: bitmaps $(ROMNAME).sfc

clean: cleanBuildRes cleanRom cleanGfx
	
#---------------------------------------------------------------------------------
pvsneslibfont.pic: pvsneslibfont.png
	$(GFXCONV) -s 8 -o 16 -u 16 -p -e 0 -i $<

map_512_512.pic: map_512_512.bmp
	$(GFXCONV) -s 8 -o 16 -u 16 -e 2 -p -m -t bmp -i $<

ball.pic: ball.bmp
	$(GFXCONV) -s 16 -o 16 -u 16 -p -t bmp -i $<

bitmaps : pvsneslibfont.pic map_512_512.pic ball.pic
