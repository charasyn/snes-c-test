#ifndef __HW_H
#define __HW_H
#include "common.h"

typedef enum {
    MODE0 = 0,
    MODE1 = 1,
} gfxmode_t;

#ifdef HW_DEFINE_VARS
#define HWVAR
#else
#define HWVAR extern
#endif

HWVAR int Hw_curGfxMode;
HWVAR uint16_t Hw_textLayerVramAddr;

void Hw_configureGraphicsMode(gfxmode_t gfxMode);

#endif // __HW_H
