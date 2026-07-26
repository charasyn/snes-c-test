MAKEFLAGS += --always-make

TARGET := output.sfc
OBJECTS := main.o misc.o game.o gameio.o platform.o randxor.o sprites.o

SRC := ../src
ASSETS := ../assets
TOOLS := ../../tools

all: $(TARGET)

### Dependencies
main.o: $(SRC)/main.c $(SRC)/int_snes_xc.h $(SRC)/snes_regs_xc.h sprites.h $(SRC)/game.h

### Asset rules
sprites.s sprites.h: $(ASSETS)/sprites.png $(ASSETS)/sprites.pal.png
	$(TOOLS)/tileimg_to_bin.py --bpp=4 $(ASSETS)/sprites.png $(ASSETS)/sprites.pal.png sprites.s

### Boilerplate
# Assume if user has not set VBCC path, we are on my Windows machine...
ifeq ($(VBCC),)
   export VBCC := ../../vbcc65816/vbcc65816_win/vbcc
   export PATH := $(VBCC)/bin:$(PATH)
endif


CC := vc
AS := vasm6502_oldstyle
LD := vc

# Flags are taken from Phillip May's snes-homebrew repo, which can be found here:
# https://github.com/Phillip-May/snes-homebrew/blob/master/SimpleCDemos/shared/build/shared-config.mk

# Can't use -O4 as it fails to find `main` when linking...
LDFLAGS := +snes-hi -lm -maxoptpasses=300 -Os -inline-depth=1000
LDFLAGS += -fp-associative -force-statics -range-opt -D__VBCC__=1
LDFLAGS += -D__VBCC65816__=1

ASFLAGS := -816 -vobj3 -nowarn=62 -opt-branch -Fvobj -dotdir

CCFLAGS := $(LDFLAGS) -I. -c

### Targets

clean:
	rm *.o *.sfc 2>/dev/null || true
	rm $(ASSETS)/*.o $(ASSETS)/*.s $(ASSETS)/*.h $(ASSETS)/*.bin 2>/dev/null || true

.PHONY: all clean

%.sfc: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: $(SRC)/%.c
	$(CC) $(CCFLAGS) -o $@ $<

%.o: $(SRC)/%.s
	$(AS) $(ASFLAGS) -o $@ $<

%.asm: $(SRC)/%.c
	$(CC) $(LDFLAGS) -o $@ -S $<
