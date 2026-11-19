#include <stdint.h>

extern uint16_t Random_Current;

void Random_init(uint16_t seed);
uint16_t Random_step(void);
