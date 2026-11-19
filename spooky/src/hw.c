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

#define HW_DEFINE_VARS 1
#include "hw.h"

#include "font.h"

const uint8_t zeros32[32] = {
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0
};

uint16_t textLayerTilemap[0x400];

static inline void triggerDma(uint8_t channels) {
    REG_MDMAEN = channels;
    __asm("    nop");
}

static inline void waitForInterrupt(void) {
    __asm("    wai");
}

void writeColour(int offset, uint16_t c) {
    REG_CGADD = offset;
    REG_CGDATA = (c>>0);
    REG_CGDATA = (c>>8);
}

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

    REG_CGADD = 0;
    REG_DMAP0 = 0x0A;
    REG_BBAD0 = (uint8_t)(&REG_CGDATA);
    REG_A1T0 = (uint16_t)zeros32;
    REG_A1B0 = ((uint32_t)zeros32)>>16;
    REG_DAS0 = 0x200;
    triggerDma(1);

    REG_VMAIN = 0x80; // increment after writing high byte
    REG_VMADD = 0;
    REG_DMAP0 = 0x09;
    REG_BBAD0 = (uint8_t)(&REG_VMDATA);
    REG_A1T0 = (uint16_t)zeros32;
    REG_A1B0 = ((uint32_t)zeros32)>>16;
    REG_DAS0 = 0x0000; // value of 0 gives 64k
    triggerDma(1);
}

void uploadFont(void) {
    REG_VMAIN = 0x80; // increment after writing high byte
    REG_VMADD = 0x5800;
    REG_DMAP0 = 0x01;
    REG_BBAD0 = (uint8_t)(&REG_VMDATA);
    REG_A1T0 = (uint16_t)font_tiles;
    REG_A1B0 = ((uint32_t)font_tiles)>>16;
    REG_DAS0 = 0x1000;
    triggerDma(1);
    writeColour(0, font_palette[0]);
    writeColour(1, font_palette[1]);
    writeColour(2, font_palette[2]);
    writeColour(3, font_palette[3]);
}

void Hw_configureGraphicsMode(gfxmode_t gfxMode) {
    // VRAM layout:
    // $0000-3FFF: 4BPP FG/BG graphics
    // $0000-1FFF: 2BPP FG graphics
    // $2000-3FFF: 2BPP BG graphics
    // $4000-5FFF: Text layer graphics + all tilemaps
    // $4000-47FF: Dynamic!
    // $4800-4FFF: FG tilemap
    // $5000-53FF: Dynamic, usually BG tilemap
    // $5400-57FF: Text tilemap
    // $5800-5FFF: Font graphics
    // $6000-7FFF: Sprite graphics
    Hw_curGfxMode = gfxMode;
    switch(gfxMode) {
    case MODE0:
        REG_BGMODE = 0;
        // Configure BGs:
        //     Layer 1: text
        //     Layer 2: FG
        //     Layer 3: BG
        //     Layer 4: BG
        REG_BG1SC = 0x54;
        REG_BG2SC = 0x48 | 1;
        REG_BG3SC = 0x50;
        REG_BG4SC = 0x44;
        REG_BG12NBA = 0x04;
        REG_BG34NBA = 0x22;
        // Configure sprites
        // OAM1 addr: $6000
        // OAM2 addr: $7000
        // Sizes: 8x8, 32x32
        REG_OBSEL = 0x23;
        break;
    case MODE1:
        REG_BGMODE = 9;
        // Configure BGs:
        //     Layer 1: FG
        //     Layer 2: BG
        //     Layer 3: text
        REG_BG1SC = 0x48 | 1;
        REG_BG2SC = 0x50;
        REG_BG3SC = 0x54;
        REG_BG12NBA = 0x00;
        REG_BG34NBA = 0x04;
        // Configure sprites
        // OAM1 addr: $6000
        // OAM2 addr: $7000
        // Sizes: 8x8, 32x32
        REG_OBSEL = 0x23;
        break;
    default:
        assert(false);
    }
}

void completeFrame(void) {
    REG_VMAIN = 0x80; // increment after writing high byte
    REG_VMADD = 0x5400;
    REG_DMAP0 = 0x01;
    REG_BBAD0 = (uint8_t)(&REG_VMDATA);
    REG_A1T0 = (uint16_t)textLayerTilemap;
    REG_A1B0 = ((uint32_t)textLayerTilemap)>>16;
    REG_DAS0 = sizeof(textLayerTilemap);
    waitForInterrupt();
    triggerDma(1);
}

void renderTextbox(int x, int y, int w, int h) {
    uint16_t *tilemapLoc = textLayerTilemap + x + y * 32;
    int stride = 32 - w - 2;
    // Top row
    *tilemapLoc++ = 0x2302;
    for (int i = w; i != 0; i--) {
        *tilemapLoc++ = 0x2303;
    }
    *tilemapLoc++ = 0x2302 | 0x4000;
    // Middle rows
    for (int j = h; j != 0; j--) {
        tilemapLoc += stride;
        *tilemapLoc++ = 0x2304;
        for (int i = w; i != 0; i--) {
            *tilemapLoc++ = 0x2340;
        }
        *tilemapLoc++ = 0x2304 | 0x4000;
        tilemapLoc += stride;
        *tilemapLoc++ = 0x2304;
        for (int i = w; i != 0; i--) {
            *tilemapLoc++ = 0x2350;
        }
        *tilemapLoc++ = 0x2304 | 0x4000;
    }
    tilemapLoc += stride;
    // Bottom row
    *tilemapLoc++ = 0x2302 | 0x8000;
    for (int i = w; i != 0; i--) {
        *tilemapLoc++ = 0x2303 | 0x8000;
    }
    *tilemapLoc++ = 0x2302 | 0x4000 | 0x8000;
}

void plotCharacter(int x, int y, char letter) {
    uint16_t *tilemapLoc = textLayerTilemap + x + y * 32;
    uint16_t tmapVal = 0x2300 | (letter & 0x0f) | ((letter & 0x70) << 1);
    tilemapLoc[0] = tmapVal;
    tilemapLoc[32] = tmapVal | 0x0010;
}

void drawString(int x, int y, char const * str) {
    for(; *str; x++, str++) {
        plotCharacter(x, y, *str);
    }
}

int main(void) {
    REG_INIDISP = 0x8F;
    REG_NMITIMEN = 0x81;
    resetPpu();

    uploadFont();
    Hw_configureGraphicsMode(MODE1);

    // Tilemap test
    renderTextbox(1, 1, 1, 1);
    plotCharacter(2, 2, '@');

    renderTextbox(11, 1, 19, 3);
    drawString(12, 2, "@What a horrible   ");
    drawString(12, 4, " night to have a   ");
    drawString(12, 6, " curse.            ");


    renderTextbox(5, 13, 19, 3);
    drawString(6, 14, "@damn dude that    ");
    drawString(6, 16, " sucks lol. chat,  ");
    drawString(6, 18, " can we get a <f>  ");

    REG_TM = 0x04;

    // Wait for VBlank to enable screen
    completeFrame();
    REG_BG3VOFS = 0xFF;
    REG_BG3VOFS = 0xFF;
    REG_INIDISP = 0x0F;

    while(1){
        // todo
    }
}
