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

int main(void) {
    REG_INIDISP = 0x8F;
    REG_NMITIMEN = 1;
    REG_TM = 0;
    REG_TS = 0;
    REG_BGMODE = 0;
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
    while(!(REG_RDNMI & 0x80)){}
    REG_HDMAEN = 0b11000000;
    REG_INIDISP = 0x0F;
    while(1){
        (void)(u8_reg(0x1));
    }
}
