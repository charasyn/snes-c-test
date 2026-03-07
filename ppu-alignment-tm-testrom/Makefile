TARGET := output.sfc
OBJECTS := test.o asm_main.o

include ../include.mk

### Dependencies
test.o: test.c int_snes_xc.h snes_regs_xc.h

asm_main.o: asm_main.s snesregs.s
