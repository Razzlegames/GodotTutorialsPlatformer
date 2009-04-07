##########################################################################################
# DevkitARM Makefile
#
#
##########################################################################################
#
# Here are the gfx2gba options, since they're very often needed and they're just
# too much to keep all in mind ...
#
# Get the latest gfx2gba version at: http://www.ohnehirn.de/tools/
# Normally the recent version is "gfx2gba.exe" instead of zip file!
#
##########################################################################################
# =======================
# gfx2gba Converter v0.14
# -----------------------
# (C) 2oo1-2oo2 [TRiNiTY]
# =======================
#
# Usage: gfx2gba [options] bmp/pcx/tga/tim/spr files ...
#
# Options are:
#
#  -pPalettename                  -m generate map (optimized)
#  -oOutputdir                    -M generate map (not optimized)
#  -fOutput format                -mm generate metatiled map (optimized)
#  -sSection                      -MM generate metatiled map (not optimized)
#  -SpSuffix for palette          -bBank for map
#  -SmSuffix for map              -mc save map in column order
#  -StSuffix for tiledata         -F turn off check for flipped tiles
#  -TMetatilesize                 -rs output a rotate/scale BG screen map
#  -tTilesize                     -P don't save palette data
#  -tc save tiles as columns      -G don't save tile/image data
#  -cColordepth                   -D don't save map data
#  -CColor-Offset                 -X don't save anything
#  -A force color offset add      -Z compress everything
#  -aTransparent color            -zt compress tile/bitmap data
#  -vVRAM-Offset                  -zp compress palette data
#  -x don't merge palettes        -zm compress map data
#  -q quiet mode                  -ap use aPLib as compressor
#  -B only optimize blank tiles   -aps use aPLib (safe) as compressor
#  -extern add extern to arrays   -align add alignment info for GCC
#
##########################################################################################


#
# Set a list of files you want to compile
#
#OFILES += main.o CrazyHero.o Gummy.o gfx/gummy.raw.o gfx/crazy_hero.raw.o world1_physics.o Sprites.o sine_cos_table.o interrupts.o

##########################################################################################
# Standard Makefile targets start here
##########################################################################################
#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
#DEVKITARM   =	/home/kyle2/Development/Games/Gameboy/devkitARM/devkitARM
#DEVKITPRO   =	/home/kyle2/Development/Games/Multi_System_Compilers/DevikitPro

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/gba_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output, if this ends with _mb a multiboot image is generated
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing data files
# INCLUDES is a list of directories containing header files
#---------------------------------------------------------------------------------

export TARGET		:=	$(shell basename $(CURDIR))
BUILD		:=	build
SOURCES		:=	gfx source "Maps/test/"
DATA		:=
INCLUDES	:=	"include" 

INCLUDES	+=	build
INCLUDES	+=	sound
INCLUDES	+=	Maps/test/
KRAWALLDATA	:=	sound
export BMP_GRAPHICS	:=	gfx/gummy.bmp gfx/crazy_hero.bmp \
			gfx/ball_blue.bmp gfx/ball_green.bmp \
			gfx/ball_red.bmp gfx/ball_yellow.bmp \
			gfx/heart_16x16.bmp 

# Compile using Krawall software (set to yes or no) ?
# Also specify if Krawall is registered (yes or no)
#
#USE_KRAWALL=yes
#KRAWALL_IS_REGISTERED=no
KRAWALL_FILES	:= 	sound/absnuts_changed.s3m 

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

ARCH	:=	-mthumb -mthumb-interwork

CFLAGS	:=	-g -Wall -O3\
		-mcpu=arm7tdmi -mtune=arm7tdmi\
 		-fomit-frame-pointer\
		-ffast-math \
		$(ARCH)

CFLAGS	+=	$(INCLUDE)

CXXFLAGS	:=	$(CFLAGS) -fno-rtti -fno-exceptions -fno-rtti
#-fnoexceptions

ASFLAGS	:=	$(ARCH)
LDFLAGS	=	-g $(ARCH) -Wl,-Map,$(notdir $@).map

#export LIBKRAWALL	:=	$(DEVKITPRO)/Krawall
#export LIBGBA		:=	$(DEVKITPRO)/libgba

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:=	-lgba -lkrawall

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=	$(LIBGBA) $(LIBKRAWALL)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# Automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))
PCXFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.pcx)))

KRAWALLOBJ	:=	$(CURDIR)/$(KRAWALLDATA)/modules.o


#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
#$
export OFILES	:=	$(KRAWALLOBJ) \
			$(PCXFILES:.pcx=.o)\
			$(addsuffix .o,$(BINFILES)) \
			$(CPPFILES:.cpp=.o) \
			$(CFILES:.c=.o) \
			$(SFILES:.s=.o)\


#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD)

#export INCLUDE += -I$(DEVKITARM)/include/c++/4.1.1 

export HFILES	:= 	$(foreach dir,$(INCLUDE),$(notdir $(wildcard $(dir)/*.h)))

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

export PATH	:=	$(PATH):$(DEVKITARM)/bin:$(LIBKRAWALL)/bin

.PHONY: $(BUILD) $(KRAWALLOBJ) clean doc music


#---------------------------------------------------------------------------------
$(BUILD): Makefile graphics $(KRAWALLOBJ) backgrounds
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

$(KRAWALLOBJ):
	$(MAKE) -C $(KRAWALLDATA)

all	: Makefile $(BUILD) $(KRAWALLOBJ) 

ctags:
	ctags -R ./ $(DEVKITARM)/include $(LIBDIRS)


#---------------------------------------------------------------------------------
clean: ctags 
	@echo clean ...
	$(MAKE) -C $(KRAWALLDATA) clean
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).gba
#---------------------------------------------------------------------------------
else


#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).gba	:	$(OUTPUT).elf 

$(OUTPUT).elf	:	$(OFILES) $(LIBGBA)/lib/libgba.a

%.o	:	%.pcx
	@echo $(notdir $<)
	@$(bin2o)

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------


##########################################################################################
# Custom  Makefile targets start here
##########################################################################################

# Convert Charset WITHOUT map optimation!
#	gfx2gba -t8 -D -M -fsrc -ogfx -pCharset.pal gfx/Charset.bmp
#	echo "gfx2gba -t8 -M -fsrc -pgfx/crazy_hero.pal gfx/crazy_hero.bmp"
#	gfx2gba -t8 -M -fsrc -pgfx/crazy_hero.pal gfx/crazy_hero.bmp
#	echo "gfx2gba -t8 -M -fsrc -pgfx/gummy.pal gfx/gummy.bmp"
#	gfx2gba -t8 -M -fsrc -pgfx/gummy.pal gfx/gummy.bmp
#gfx: Makefile gfx/gummy.bmp gfx/crazy_hero.bmp gfx/ball_blue.bmp gfx/ball_green.bmp gfx/ball_red.bmp gfx/ball_yellow.bmp gfx/casper.pcx\
#		gfx/casper2.pcx

graphics:
	$(MAKE) -C gfx/
#graphics: Makefile $(BMP_GRAPHICS)
#	@echo ""
#	@echo ""
#	@echo "-------------------------------------------------------------"
#	@echo "   Converting your GFX to source.."
#	@echo "-------------------------------------------------------------"
#	gfx2gba -t8 -M -fsrc -o gfx -pmaster.pal $(BMP_GRAPHICS)

backgrounds: 
	$(MAKE) -C Maps/test/

#gfx2gba -fsrc -c16 -t4 -m Maps/test/gimp_grid.bmp -o gfx

#music: jungle_noises.wav
#	wav2gba jungle_noises.wav jungle_noises.raw

# Interrupts related (if doing my own ISRs)
#interrupt_files: Makefile interrupts/interrupts.c interrupts.h
#	@echo "-------------------------------------------------------------"
#	@echo "    Compiling CUSTOM interrupts ISRs"
#	@echo "-------------------------------------------------------------"
#	@echo "$(CC) $(CFLAGS) -S -marm interrupts/interrupts.c"
#	$(CC) $(CFLAGS) -S -marm interrupts/interrupts.c

music: Makefile $(KRAWALL_FILES)
	@echo ""
	@echo "-------------------------------------------------------------"
	@echo "   Hooking up the Music and sound gangster"
	@echo "-------------------------------------------------------------"
	krawall_converter -d $(KRAWALL_FILES)

#depend: 
#	makedepend ./*{cpp,c} ./include/*h

run: all
	konsole -e VisualBoyAdvance -3 *.gba &

doc: $(HFILES) $(CFILES) $(CPPFILES) $(SFILES) Makefile
#doc: all
	doxygen


diff:
	svn diff --diff-cmd=diffwrap


