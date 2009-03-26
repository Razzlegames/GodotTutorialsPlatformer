GFX_CONV = gfx2gba
#GFX_ARGS = "-t8 -M -fsrc -o gfx -pmaster.pal "

#all:$(patsubst %.bmp,%.map.c,$(wildcard *bmp))
BMP_FILES = $(wildcard *bmp)

.PHONY : graphics

#  Change all bmp graphics files to name.map.c, the output of gfx2gba
BMP_CFILES = $(BMP_FILES:.bmp=.map.c)

#  Run the Makefile recursively for each graphics source file name.map.c
all:
	@for i in $(BMP_CFILES); do\
	    $(MAKE) $$i; done

# Recompile the graphics file for each bmp file that is 
#    newer that it's map.c file
%.map.c: %.bmp
	@echo "remaking $*"
	@echo ""
	@echo "-------------------------------------------------------------"
	@echo "   Converting your GFX to source.."
	@echo "-------------------------------------------------------------"
	$(GFX_CONV) -t8 -M -fsrc -pmaster.pal  $(BMP_FILES)

#../$(TARGET) : $(BMP_FILES)
#	@echo ""
#	@echo ""
#	@echo "-------------------------------------------------------------"
#	@echo "   Converting your GFX to source.."
#	@echo "-------------------------------------------------------------"
#	$(GFX_CONV) -t8 -M -fsrc -pmaster.pal  $(BMP_FILES)



# Convert Charset WITHOUT map optimation!
#	gfx2gba -t8 -D -M -fsrc -ogfx -pCharset.pal gfx/Charset.bmp
#	echo "gfx2gba -t8 -M -fsrc -pgfx/crazy_hero.pal gfx/crazy_hero.bmp"
#	gfx2gba -t8 -M -fsrc -pgfx/crazy_hero.pal gfx/crazy_hero.bmp
#	echo "gfx2gba -t8 -M -fsrc -pgfx/gummy.pal gfx/gummy.bmp"
#	gfx2gba -t8 -M -fsrc -pgfx/gummy.pal gfx/gummy.bmp
#gfx: Makefile gfx/gummy.bmp gfx/crazy_hero.bmp gfx/ball_blue.bmp gfx/ball_green.bmp gfx/ball_red.bmp gfx/ball_yellow.bmp gfx/casper.pcx\
#		gfx/casper2.pcx
