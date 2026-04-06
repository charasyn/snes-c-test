/*
ROM to test PPU/CPU cycle alignment effects on writes to the TM register

Copyright (c) 2026 charasyn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "snes_regs_xc.h"

#include "assets/sprites.h"

#include "platform.h"
#include "game.h"

#define rgb15(r, g, b) ((b&0x1f) << 10 | (g&0x1f) << 5 | (r&0x1f))

#define NUM_ELEMS(x) (sizeof(x)/sizeof(x[0]))

static const int bgdropcolour = rgb15(28,28,28);
static const int fgcolour[4] = {
    rgb15(31,31,31),
    rgb15(31,0,0),
    rgb15(0,31,0),
    rgb15(0,0,31),
};

void writeColour(int offset, uint16_t c) {
    REG_CGADD = offset;
    REG_CGDATA = (c>>0);
    REG_CGDATA = (c>>8);
}

extern void asm_main(void);

void resetPpu(void) {
    REG_OBSEL = 0;
    REG_OAMADD = 0;
    REG_BGMODE = 0;
    REG_MOSAIC = 0;
    REG_BG1SC = 0;
    REG_BG2SC = 0;
    REG_BG3SC = 0;
    REG_BG4SC = 0;
    REG_BG12NBA = 0;
    REG_BG34NBA = 0;
    REG_BG1HOFS = 0;
    REG_BG1HOFS = 0;
    REG_BG1VOFS = 0;
    REG_BG1VOFS = 0;
    REG_BG2HOFS = 0;
    REG_BG2VOFS = 0;
    REG_BG3HOFS = 0;
    REG_BG3VOFS = 0;
    REG_BG4HOFS = 0;
    REG_BG4VOFS = 0;
    REG_VMAIN = 0x80;
    REG_M7SEL = 0;
    REG_M7A = 0;
    REG_M7A = 0;
    REG_M7B = 0;
    REG_M7C = 0;
    REG_M7D = 0;
    REG_M7X = 0;
    REG_M7X = 0;
    REG_M7Y = 0;
    REG_M7Y = 0;
    for (int i = 0; i < 256; i += 1) {
        writeColour(i, 0);
    }
    REG_W12SEL = 0;
    REG_W34SEL = 0;
    REG_WOBJSEL = 0;
    REG_WH0 = 1;
    REG_WH1 = 0;
    REG_WH2 = 1;
    REG_WH3 = 0;
    REG_WBGLOG = 0;
    REG_WOBJLOG = 0;
    REG_TM = 0;
    REG_TS = 0;
    REG_TMW = 0;
    REG_TSW = 0;
    REG_CGWSEL = 0;
    REG_CGADSUB = 0;
    REG_COLDATA = 0xE0;
    REG_SETINI = 0;
    // reset OPHCT/OPVCT latch
    (void)(REG_STAT78);
}

int main(void) {
    REG_INIDISP = 0x8F;
    REG_NMITIMEN = 1;
    resetPpu();

    // Upload all-zeros tilemap
    REG_VMAIN = 0x80; // increment after writing high byte
    REG_VMADD = 0x2000;
    for (int i = 0; i < (32*32); i += 1) {
        REG_VMDATA = 0;
    }

    // Upload tile which is all colour 1
    REG_VMAIN = 0x80; // increment after writing high byte
    REG_VMADD = 0;
    for (int i = 0; i < 8; i += 1) {
        REG_VMDATA = 0x00FF;
    }

    // Upload sprite character data
    REG_VMAIN = 0x80; // increment after writing high byte
    REG_VMADD = 0x4000;
    for (unsigned i = 0; i < NUM_ELEMS(sprites_tiles); i += 1) {
        REG_VMDATA = sprites_tiles[i];
    }

    // Configure colours in CGRAM
    writeColour(0, bgdropcolour);
    for (unsigned i = 0; i < NUM_ELEMS(sprites_palette); i += 1) {
        writeColour(128+i, sprites_palette[i]);
    }

    // Configure BGs - we only use BG1 but we configure all the same
    REG_BG1SC = 8 << 2; 
    REG_BG2SC = 8 << 2;
    REG_BG3SC = 8 << 2;
    REG_BG4SC = 8 << 2;
    REG_BG12NBA = 0;
    REG_BG34NBA = 0;

    // Configure sprites
    // OAM1 addr: $4000
    // OAM2 addr: $5000
    // Sizes: 8x8, 16x16
    REG_OBSEL = 0x02;

    REG_TM = 0x10;

    Platform_init();

    // Wait for VBlank to enable screen
    while(!(REG_RDNMI & 0x80)){}
    REG_INIDISP = 0x0F;

    while(1){
        Game_main(4, 10);
    }
}
