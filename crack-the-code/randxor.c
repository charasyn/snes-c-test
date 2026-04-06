#include "randxor.h"
#include <stdint.h>

uint16_t Random_Current;

void Random_init(uint16_t seed) {
    if (seed == 0) {
        seed = 0xFFFF;
    }
}
uint16_t Random_step(void) {
    Random_Current ^= Random_Current << 7;
    Random_Current ^= Random_Current >> 9;
    Random_Current ^= Random_Current << 8;
    return Random_Current;
}
