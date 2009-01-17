AS := arm-eabi-as
MODULES := absnuts_changed.s3m living.s3m

ASFLAGS := -mthumb-interwork

PROJECT := modules.o

RM := rm -f

CONVERT := $(LIBKRAWALL)/bin/converter

all : $(PROJECT)

$(PROJECT) : Makefile $(MODULES) $(CONVERT)
	$(CONVERT) $(MODULES)
	$(AS) $(ASFLAGS) *.s -o $@

.PHONY : clean

clean :
	-$(RM) *.s *.h $(PROJECT)

