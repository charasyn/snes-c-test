    ; Very basic NMI handler, used only to maintain a counter.
    ; charasyn 2026
    ;
    ; This is free and unencumbered software released into the public domain.
    ;
    ; Anyone is free to copy, modify, publish, use, compile, sell, or
    ; distribute this software, either in source code form or as a compiled
    ; binary, for any purpose, commercial or non-commercial, and by any
    ; means.
    ;
    ; In jurisdictions that recognize copyright laws, the author or authors
    ; of this software dedicate any and all copyright interest in the
    ; software to the public domain. We make this dedication for the benefit
    ; of the public at large and to the detriment of our heirs and
    ; successors. We intend this dedication to be an overt act of
    ; relinquishment in perpetuity of all present and future rights to this
    ; software under copyright law.
    ;
    ; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    ; EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    ; MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    ; IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
    ; OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
    ; ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    ; OTHER DEALINGS IN THE SOFTWARE.
    ;
    ; For more information, please refer to <https://unlicense.org>

    .section "_bss.near.asm_main"
    .global _Global_FrameCounter
_Global_FrameCounter:
    ; Allocate two bytes, but only the low byte will be used
    .blk 2

    .section "_text.near.asm_main"
    .global ___irq_vblank

___irq_vblank:                 ; 120 cycles (15 slow CPU clocks) to increment a byte
    sep #$20                   ; 22 cyc
    inc _Global_FrameCounter   ; 46 cyc
    rti                        ; 52 cyc
