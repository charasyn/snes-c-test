/*
Simple HDMA test program

Copyright (c) 2025 charasyn

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

#include <stdbool.h>
#include "snes_regs_xc.h"

#define rgb15(r, g, b) ((b&0x1f) << 10 | (g&0x1f) << 5 | (r&0x1f))


static const int bgdropcolour = rgb15(16,16,31);


#define hdma_entry(duration, value) duration, (value) & 0xff, ((value) >> 8) & 0xff,
static const uint8_t bgHdmaColourTable[] = {

#include "hdma_data.inc"

0
};
#undef hdma_entry

#define hdma_entry(duration, value) duration, 0, 0,
static const uint8_t bgHdmaAddrTable[] = {

#include "hdma_data.inc"

0
};
#undef hdma_entry

uint16_t inidispForScreenOff = 0x8080;
uint16_t inidispForScreenPreOn = 0x0000;
uint16_t inidispForScreenOn = 0x0F0F;

extern uint8_t inidispHdmaTable[];

// uint8_t REGMIRROR_INIDISP = 0;
uint8_t REGMIRROR_HDMAEN = 0;
uint16_t REGMIRROR_TMTS = 0;

uint8_t OAM_MIRROR[544];
volatile uint16_t oamMirrorLocked = 0;
volatile uint16_t waitingForFramePresent = 0;
volatile uint16_t nmiCount = 0;

void EnableInterrupts() {
    __asm("  cli");
}
extern void DisableIrqHandler(void);
extern void SetupEndOfFrameIrqHandler(void);

uint16_t curIrqHandler;

#define BANK(x) ((uint8_t)((long)(x)<<16))

void PresentFrame(void) {
    while(oamMirrorLocked) {}
    waitingForFramePresent = 1;
    SetupEndOfFrameIrqHandler();
    while(waitingForFramePresent){}
}
inline void SwapU16(uint16_t * a, uint16_t * b) {
    uint16_t tmp = *a;
    *a = *b;
    *b = tmp;
}
// void QuickSort(uint16_t * data, uint16_t count) {
//     if (count == 1) return;
//     if (count == 2) {
//         if (data[0] > data[1]) {
//             SwapU16(&data[0], &data[1]);
//         }
//         return;
//     }
//     uint16_t lcount = 0, rcount = count - 2;
//     uint16_t partitionVal = data[count / 2];
//     data[count / 2] = data[count - 1];
//     while(lcount < rcount) {
//         while(lcount < rcount && data[lcount] < partitionVal) {
//             lcount += 1;
//         }
//         if (lcount >= rcount) break;
//         while(rcount > lcount && data[rcount] >= partitionVal) {
//             rcount -= 1;
//         }
//         if (lcount >= rcount) break;
//         SwapU16(&data[lcount], &data[rcount]);
//         lcount += 1;
//     }
//     data[count - 1] = 
// }
void InsertionSort(uint16_t * data, uint16_t count) {
    uint16_t numSorted = 1;
    uint16_t lastMax = data[0];
    uint16_t lastRead;
    while (numSorted < count) {
        lastRead = data[numSorted];
        if (lastMax <= lastRead) {
            numSorted += 1;
            lastMax = lastRead;
            continue;
        }
        // lastRead is less than lastMax
        // Find where in the sorted values to insert it
        uint16_t i = numSorted-1;
        uint16_t toInsert = lastRead;
        data[numSorted] = lastMax;
        while (i != 0) {
            lastRead = data[i-1];
            if (lastRead <= toInsert) {
                // Found the spot
                break;
            }
            data[i] = lastRead;
            i -= 1;
        }
        data[i] = toInsert;
        numSorted += 1;
    }
    return;
}
bool MeanMedianMode(uint16_t const * data, uint16_t count, uint16_t * output) {
    uint16_t tmp[16];
    if (count > 16) return false;
    for (int i = 0; i < count; i += 1) {
        tmp[i] = data[i];
    }
    InsertionSort(tmp, count);
    return false;
}

void ResetPpu(void) {
    REG_INIDISP = 0x8F;
    REG_OBSEL = 0;
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
    REG_BG2HOFS = 0;
    REG_BG2VOFS = 0;
    REG_BG2VOFS = 0;
    REG_BG3HOFS = 0;
    REG_BG3HOFS = 0;
    REG_BG3VOFS = 0;
    REG_BG3VOFS = 0;
    REG_BG4HOFS = 0;
    REG_BG4HOFS = 0;
    REG_BG4VOFS = 0;
    REG_BG4VOFS = 0;
    REG_VMAIN = 0;
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
    REG_WH0 = 0;
    REG_WH1 = 0;
    REG_WH2 = 0;
    REG_WH3 = 0;
    REG_WBGLOG = 0;
    REG_WOBJLOG = 0;
    REG_TM = 0;
    REG_TS = 0;
    REG_TMW = 0;
    REG_TSW = 0;
    REG_CGWSEL = 0x30;
    REG_CGADSUB = 0;
    // Set colour to black
    REG_COLDATA = 0xe0;
    REG_SETINI = 0;
    // TODO: clear OAM
    // TODO: clear CGRAM
    // TODO: clear VRAM
}

int main(void) {
    ResetPpu();
    REG_DMAP1 = 0x41;
    REG_BBAD1 = 0xFF;
    REG_A1T1 = (int)inidispHdmaTable;
    REG_A1B1 = BANK(inidispHdmaTable);
    REG_DASB1 = BANK(inidispForScreenOff);
    REG_CGADD = 0;
    REG_CGDATA = bgHdmaColourTable[1];
    REG_CGDATA = bgHdmaColourTable[2];
    REG_DMAP6 = 0x02;
    REG_BBAD6 = 0x21;
    REG_A1T6 = (int)bgHdmaAddrTable;
    REG_A1B6 = ((long)bgHdmaAddrTable)>>16;
    REG_DMAP7 = 0x02;
    REG_BBAD7 = 0x22;
    REG_A1T7 = (int)bgHdmaColourTable;
    REG_A1B7 = ((long)bgHdmaColourTable)>>16;
    REGMIRROR_HDMAEN = 0b11000010;
    DisableIrqHandler();
    EnableInterrupts();
    while(1){
        (void)(u8_reg(0x1));
        PresentFrame();
    }
}
