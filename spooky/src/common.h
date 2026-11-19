#ifndef __COMMON_H
#define __COMMON_H

#include <assert.h>
#include <stdbool.h>

#include "int_snes_xc.h"

#define NUM_ELEMS(x) (sizeof(x)/sizeof(x[0]))
extern const uint8_t zeros32[32];
extern uint16_t textLayerTilemap[0x400];

#endif // __COMMON_H
