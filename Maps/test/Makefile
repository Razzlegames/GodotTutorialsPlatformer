.PHONY: all clean

MAP_BMP = ./gimp_grid.bmp \
	  puzzle_bezel.bmp \
	  puzzle_background_swirl.bmp

MAP_BMP_CFILES= $(MAP_BMP:.bmp=.c)
MAP_BMP_HFILES= $(MAP_BMP:.bmp=.h)

#  Run the Makefile recursively for each map bmp 
#       file in the list above
all: Makefile
	@for i in $(MAP_BMP_CFILES); do\
	    $(MAKE) $$i; done
	@for i in $(MAP_BMP_HFILES); do\
	    $(MAKE) $$i; done

%.h %.c: %.bmp
	@echo ""
	@echo ""
	@echo "----------------------------------------------------------"
	@echo "  Converting background:$*"
	@echo "----------------------------------------------------------"
	grit $*.bmp -gB4 -mRtpf -mLs -o $*.c
	cp  -fv $*.{c,h} ../../source/



clean:
	@echo "----------------------------------------------------------"
	@echo "  Cleaning map files: "
	@echo "----------------------------------------------------------"
	@echo rm -fv $(MAP_BMP_CFILES)
	rm -fv $(MAP_BMP_CFILES)
	@echo rm -fv $(MAP_BMP_HFILES)
	rm -fv $(MAP_BMP_HFILES)

# MAP_NAME = test_map2
#$(MAP_NAME).h $(MAP_NAME).c: $(MAP_BMP)
#	@echo ""
#	@echo ""
#	@echo "----------------------------------------------------------"
#	@echo "  Converting backgrounds"
#	@echo "----------------------------------------------------------"
#	grit $(MAP_BMP) -gB4 -mRtpf -mLs -o $(MAP_NAME).c
#	cp  -fv $(MAP_NAME).{c,h} ../../source/


#---grit v0.8.1 ---
#GRIT: GBA Raster Image Transmogrifier. (grit v0.8.1, 20080512)
#	  Converts bitmap files into something the GBA can use.
#usage: grit srcfile(s) [args]
#
#
#--- Graphics options (base: "-g") ---
#	-g | -g!       Include  or exclude gfx data [inc]
#-gu(8|16|32)   Gfx data type: u8, u16, u32 [u32]
#	-gz[!lhr0]     Gfx compression: off, lz77, huff, RLE, off+header [off]
#	-ga{n}         Gfx pixel offset (non-zero pixels) [0]
#	-gb | -gt      Gfx format, bitmap or tile [tile]
#	-gB{n}         Gfx bit depth (1, 2, 4, 8, 16) [img bpp]
#-gS            NEW: Shared graphics
#	-gT{n}         Transparent color; rrggbb hex or 16bit BGR hex [FF00FF]
#	-al{n}         Area left [0]
#	-ar{n}         Area right (exclusive) [img width]
#	-aw{n}         Area width [img width]. Overrides -ar
#	-at{n}         Area top [0]
#	-ab{n}         Area bottom (exclusive) [img height]
#	-ah{n}         Area height [img height]. Overrides -ab
#
#--- Map options (base: "-m") ---
#	-m | -m!       Include or exclude map data [exc]
#-mu(8|16|32)   Map data type: u8, u16, u32 [u16]
#	-mz[!lhr0]     Map compression: off, lz77, huff, RLE, off+header [off]
#	-ma{n}         Map-entry offset n (non-zero entries) [0]
#-mR{t,p,f}     Tile reduction: (t)iles, (p)al, (f)lipped
#	                 options can be combined [-mRtpf]
#-mR[48a]       Common tile reduction combos: reg 4bpp (-mRtpf),
#	                 reg 8bpp (-mRtf), affine (-mRt), respectively
#			 -mR!           No tile reduction (not advised)
#-mL[fsa]       Map layout: reg flat, reg sbb, affine [reg flat]
#
#--- Palette options (base: "-p") ---
#	-p | -p!       Include or exclude pal data [inc]
#-pu(8|16|32)   Pal data-type: u8, u16 , u32 [u16]
#	-pz[!lhr0]     Pal compression: off, lz77, huff, RLE, off+header [off]
#	-ps{n}         Pal range start [0]
#	-pe{n}         Pal range end (exclusive) [pal size]
#	-pn{n}         Pal count [pal size]. Overrides -pe
#-pS            NEW: shared palette
#	-pT{n}         Transparent palette index; swaps with index 0 [0]
#--- Meta/Obj options (base: "-M") ---
#	-Mh{n}         Metatile height (in tiles!) [1]
#	-Mw{n}         Metatile width (in tiles!) [1]
#	-MRp           Metatile reduction (pal only) [none]
#
#--- File / var options ---
#-ft[!csbgr]    File type (no output, C, GNU asm, bin, gbfs, grf) [.s]
#-fr            NEW: Enable GRF-format for .c or .s
#	-fa            File append
#	-fh | -fh!     Create header or not [create header]
#	-ff{name}      Additional options read from flag file [dst-name.grit]
#	-fx{name}      External tileset file
#	-o{name}       Destination filename [based on source]
#	-s{name}       Symbol base name [based from dst]
#-O{name}       NEW: Destination file for shared data
#	-S{name}       NEW: Symbol base name for shared data
#
#--- Misc ---
#-tc            NEW: Tiling in column-major order.
#	-q             Quiet mode; no report at the end
#-U(8|16|32)    All data type: u8, u16, u32
#	-W{n}          Warning/log level 1, 2 or 3 [1]
#-Z[!lhr0]      All compression: off, lz77, huff, RLE, off+header [off]
#
#New options: -fr, -ftr, -gS, -O, -pS, -S, -Z0 (et al)
#
