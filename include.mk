export VBCC := ../vbcc65816/vbcc65816_win/vbcc
export PATH := $(VBCC)/bin:$(PATH)
export VBCC_PATH := $(VBCC_PATH)

CC := vc
AS := vasm6502_oldstyle
LD := vc

# Flags are taken from Phillip May's snes-homebrew repo, which can be found here:
# https://github.com/Phillip-May/snes-homebrew/blob/master/SimpleCDemos/shared/build/shared-config.mk

# Can't use -O4 as it fails to find `main` when linking...
LDFLAGS := +snes-hi -lm -maxoptpasses=300 -O3 -inline-depth=1000 -unroll-all
LDFLAGS += -fp-associative -force-statics -range-opt -D__VBCC__=1
LDFLAGS += -D__VBCC65816__=1

ASFLAGS := -816 -vobj3 -nowarn=62 -opt-branch -Fvobj -dotdir

CCFLAGS := $(LDFLAGS) -c

### Targets

all: $(TARGET)

clean:
	rm *.o *.sfc 2>/dev/null || true

.PHONY: all clean

%.sfc: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

%.asm: %.c
	$(CC) $(LDFLAGS) -o $@ -S $<
