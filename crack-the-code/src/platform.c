#include "snes_regs_xc.h"

#define PLATFORM_DEFINE_VARIABLES 1
#include "platform.h"


static uint8_t oamBuffer[544];
static uint16_t oamOffset;
static uint8_t oamHiByteTemp;
static uint8_t oamHiByteCount;
static uint8_t oamHiByteOffset;

void OamMan_reset(void) {
    oamOffset = 0;
    oamHiByteTemp = 0;
    oamHiByteCount = 0;
    oamHiByteOffset = 0;
    for (int i = 0; i < 512; i += 4) {
        oamBuffer[i+1] = 224;
    }
}

void OamMan_addSprite(void) {
    if (OamMan_SpriteX <= -64 || OamMan_SpriteX >= 256){
        return;
    }
    if (OamMan_SpriteY <= -64 || OamMan_SpriteY >= 224) {
        return;
    }
    uint8_t hibyte = (OamMan_Flags & 1) << 1 | (OamMan_SpriteX & 0x100) >> 8;
    switch (oamHiByteCount & 3) {
        case 0:
            oamHiByteTemp |= hibyte;
            oamHiByteCount++;
            break;
        case 1:
            oamHiByteTemp |= hibyte << 2;
            oamHiByteCount++;
            break;
        case 2:
            oamHiByteTemp |= hibyte << 4;
            oamHiByteCount++;
            break;
        case 3:
            oamHiByteTemp |= hibyte << 6;
            oamHiByteCount = 0;
            oamBuffer[512+oamHiByteOffset] = oamHiByteTemp;
            oamHiByteOffset += 1;
            oamHiByteTemp = 0;
            break;
    }
    uint8_t flags;
    flags = (OamMan_Flags & 0xfe) | ((OamMan_TileId & 0x0100) >> 8);
    oamBuffer[oamOffset] = OamMan_SpriteX;
    oamBuffer[oamOffset+1] = OamMan_SpriteY;
    oamBuffer[oamOffset+2] = OamMan_TileId;
    oamBuffer[oamOffset+3] = flags;
    oamOffset += 4;
}

void OamMan_completeFrame(void) {
    oamBuffer[512+oamHiByteOffset] = oamHiByteTemp;
    REG_OAMADD = 0;
    REG_A1T0 = (uint16_t)oamBuffer;
    REG_A1B0 = ((uint32_t)oamBuffer)>>16;
    REG_DAS0 = sizeof(oamBuffer);
    REG_DMAP0 = 0;
    REG_BBAD0 = (uint8_t)(&REG_OAMDATA);
    REG_MDMAEN = 0x01;
    OamMan_reset();
}

void Platform_init(void) {
    Platform_FrameCounter = 0;
    Keys_Held = 0;
    Keys_Pressed = 0;
    REG_NMITIMEN = 1;
    OamMan_reset();
    Platform_completeFrame();
}
void Platform_completeFrame(void) {
    // If we are currently in VBlank, wait for it to end
    // (we missed a frame window)
    while((REG_HVBJOY & 0x80)){}
    // Wait for start of VBlank
    while(!(REG_HVBJOY & 0x80)){}
    // Do VBlank processing
    OamMan_completeFrame();
    // Wait for end of joypad auto-read
    while((REG_HVBJOY & 0x01)){}
    Keys_process();
    // Wait for end of VBlank
    while((REG_HVBJOY & 0x80)){}
    Platform_FrameCounter += 1;
}

void Keys_process(void) {
    uint16_t newHeld = REG_JOY1;
    Keys_Pressed = newHeld & (~Keys_Held);
    Keys_Held = newHeld;
}
