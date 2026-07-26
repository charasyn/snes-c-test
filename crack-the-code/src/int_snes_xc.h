/*
MIT License

Copyright (c) 2021 Phillip

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

#ifndef __INT_SNES_XC_H
#define __INT_SNES_XC_H

#ifdef __TCC816__
// For TCC816, use stdint.h which it has
#include <stdint.h>
#else
// For other compilers, use inttypes.h
#include <inttypes.h>
#endif

typedef volatile int8_t *volatile vs8;
typedef volatile int16_t *volatile vs16;
typedef volatile int32_t *volatile vs32;
typedef volatile uint8_t *volatile vu8;
typedef volatile uint16_t *volatile vu16;
typedef volatile uint32_t *volatile vu32;

#endif // __INT_SNES_XC_H
