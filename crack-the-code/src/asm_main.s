    ; ROM to test PPU/CPU cycle alignment effects on writes to the TM register
    ; 
    ; Copyright (c) 2026 charasyn
    ; 
    ; Permission is hereby granted, free of charge, to any person obtaining a copy
    ; of this software and associated documentation files (the "Software"), to deal
    ; in the Software without restriction, including without limitation the rights
    ; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    ; copies of the Software, and to permit persons to whom the Software is
    ; furnished to do so, subject to the following conditions:
    ; 
    ; The above copyright notice and this permission notice shall be included in all
    ; copies or substantial portions of the Software.
    ; 
    ; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    ; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    ; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    ; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    ; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    ; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    ; SOFTWARE.

    .include "snesregs.s"

    .section "_bss.near.asm_main"
GlobalLineCounter:
    .blk 1

    .section "_text.near.asm_main"
    .global _asm_main

  .macro IRQ_HV_SETUP,Hpos,Vpos
    sep #$10
    .a16
    .x8
    ; disable IRQ generation
    ldy #$01
    sty NMITIMEN
    ; set handler trigger point
    lda #\Hpos
    sta HTIME
    lda #\Vpos
    sta VTIME
    ; clear IRQ latch
    ldy TIMEUP
    ; re-enable IRQ generation
    ldy #$31
    sty NMITIMEN
    rep #$30
  .endm

  .macro IRQ_H_SETUP,Hpos
    sep #$10
    .a16
    .x8
    ; disable IRQ generation
    ldy #$01
    sty NMITIMEN
    ; set handler trigger point
    lda #\Hpos
    sta HTIME
    ; clear IRQ latch
    ldy TIMEUP
    ; re-enable IRQ generation
    ldy #$11
    sty NMITIMEN
    rep #$30
  .endm

_asm_main:
    rep #$31
    sei
    .a16
    .x16

    ; wait for H=0, V=250
    IRQ_HV_SETUP 0, 250
    wai
    sep #$20
    .a8
    lda #$01
    sta TM
    rep #$20
    .a16

    ; wait for H=274, V=32
    IRQ_HV_SETUP 274, 32
    wai
    sep #$20
    .a8
    lda #$00
    sta TM
    rep #$20
    .a16

    ; wait for H=150, V=64
    IRQ_HV_SETUP 150, 64
    wai

    ; on every future scanline, wait for H=150
    IRQ_H_SETUP 150
    sep #$30
    .a8
    .x8
    lda #((160-64)/2)
    sta GlobalLineCounter
    lda #$00
.lineloop1:
    wai
    ; do several stores in a row
    ; should assemble to 8D 2C 21
    ; this means the data bus will be $21 when the write cycle begins,
    ; which should result in TM being loaded with $01 long enough to have
    ; an effect on the screen!
    ; should take 4x8 21mhz clocks per instruction -> 8 dots
    sta TM
    sta TM
    sta TM
    sta TM
    sta TM
    sta TM
    sta TM
    sta TM

    ; acknowledge IRQ
    ldy TIMEUP

    ; loop
    dec GlobalLineCounter
    bne .lineloop1

    ; now do the same thing but with the alignment shifted slightly by one nop
    lda #((160-64)/2)
    sta GlobalLineCounter
    lda #$00
.lineloop2:
    wai
    nop
    sta TM
    sta TM
    sta TM
    sta TM
    sta TM
    sta TM
    sta TM
    sta TM

    nop
    nop

    ; acknowledge IRQ
    ldy TIMEUP

    ; loop
    dec GlobalLineCounter
    bne .lineloop2

    ; infinite loop
    jmp _asm_main
