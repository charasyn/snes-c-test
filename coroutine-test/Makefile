TARGET := output.sfc
OBJECTS := test.o irq.o

include ../include.mk

### Dependencies
test.o: test.c int_snes_xc.h snes_regs_xc.h hdma_data.inc
irq.o: irq.s snesregs.s
