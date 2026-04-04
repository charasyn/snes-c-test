TARGET := output.sfc
OBJECTS := main.o asm_main.o assets/sprites.o

all: $(TARGET)

### Dependencies
main.o: main.c int_snes_xc.h snes_regs_xc.h assets/sprites.h
asm_main.o: asm_main.s snesregs.s

### Asset rules
assets/sprites.s assets/sprites.h: assets/sprites.png assets/sprites.pal.png
	$(TOOLS)/tileimg_to_bin.py --bpp=4 assets/sprites.png assets/sprites.pal.png assets/sprites.s

### Boilerplate
# Assume if user has not set VBCC path, we are on my Windows machine...
ifeq ($(VBCC),)
   export VBCC := ../vbcc65816/vbcc65816_win/vbcc
   export PATH := $(VBCC)/bin:$(PATH)
endif

TOOLS := ../tools

CC := vc
AS := vasm6502_oldstyle
LD := vc

# Flags are taken from Phillip May's snes-homebrew repo, which can be found here:
# https://github.com/Phillip-May/snes-homebrew/blob/master/SimpleCDemos/shared/build/shared-config.mk

# Can't use -O4 as it fails to find `main` when linking...
LDFLAGS := +snes-hi -lm -maxoptpasses=300 -O3 -inline-depth=1000
LDFLAGS += -fp-associative -force-statics -range-opt -D__VBCC__=1
LDFLAGS += -D__VBCC65816__=1

ASFLAGS := -816 -vobj3 -nowarn=62 -opt-branch -Fvobj -dotdir

CCFLAGS := $(LDFLAGS) -c

### Targets

clean:
	rm *.o *.sfc 2>/dev/null || true
	rm assets/*.o assets/*.s assets/*.h assets/*.bin 2>/dev/null || true

.PHONY: all clean

%.sfc: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

%.asm: %.c
	$(CC) $(LDFLAGS) -o $@ -S $<
