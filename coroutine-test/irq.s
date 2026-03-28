    .include "snesregs.s"
    .section "_text.near"
    .global ___irq_ext
    .global ___irq_vblank
    .global _SetupEndOfFrameIrqHandler
    .global _DisableIrqHandler
    ; .extern _REGMIRROR_INIDISP
    .extern _REGMIRROR_TMTS
    .extern _REGMIRROR_HDMAEN
    .extern _CGRAM_MIRROR
    .extern _OAM_MIRROR
    .extern _oamMirrorLocked
    .extern _curIrqHandler
    .extern _waitingForFramePresent
    .extern _nmiCount
___irq_ext:
    ; prologue
    rep #$30
    .a16
    .x16
    pha
    phx
    phy
    jmp (_curIrqHandler)

_irq_epilogue:
    rep #$30
    ply
    plx
    pla
    rti

_DisableIrqHandler:
    sep #$10
    .a16
    .x8
    ldy #$81
    sty NMITIMEN
    rep #$30
    lda #<IRQHANDLER_Error
    sta _curIrqHandler
    rtl

IRQHANDLER_Error:
    sep #$20
    rep #$10
    .a8
    .x16
    stz NMITIMEN
    ldx #$dead
    ldy #$0002
    jmp IRQHANDLER_Error

  .macro IRQ_SETUP,Handler,Hpos,Vpos
    sep #$10
    .a16
    .x8
    ; disable IRQ generation
    ldy #$81
    sty NMITIMEN
    ; set handler code address
    lda #<\Handler
    sta _curIrqHandler
    ; set handler trigger point
    lda #\Hpos
    sta HTIME
    lda #\Vpos
    sta VTIME
    ; clear IRQ latch
    ldy TIMEUP
    ; re-enable IRQ generation
    ldy #$b1
    sty NMITIMEN
    rep #$30
    rtl
  .endm

_SetupEndOfFrameIrqHandler:
    IRQ_SETUP IRQHANDLER_EndOfFrame, 205, 220

IRQHANDLER_EndOfFrame:
    ; actual interrupt handling logic
    ; disable rendering (the IRQ will be timed so that this happens precisely)
    sep #$10
    .a16
    .x8
    ; set up IRQ to go off as a "overrun" timer
    lda #270
    sta HTIME
    lda #261
    sta VTIME
    ldy #$b1
    sty NMITIMEN
    ; acknowledge IRQ
    ldy TIMEUP
    ; enable reading PPU position
    ldy #$80
    sty WRIO
    ; disable hdma
    stz HDMAEN

    ; vram DMA - todo
    rep #$20
    .a16
    lda #39
.loop1:
    ldy #33
.loop2:
    dey
    bne .loop2
    nop
    nop
    nop
    nop
    nop
    nop
    dec
    bne .loop1
    lda #30
.loop3:
    dec
    bne .loop3
    sep #$20
    .a8

    ; enable hdma
    lda _REGMIRROR_HDMAEN
    sta HDMAEN
    rep #$20
    .a16
    ; set up OAM DMA
    stz OAMADDR
    lda #$00|((OAMDATA&$FF)<<8)
    sta DMAP0
    lda #<_OAM_MIRROR
    sta A1T0
    ldy #^_OAM_MIRROR
    sty A1B0
    lda #544
    sta DAS0
    ; mark OAM as locked to avoid having game logic write to it
    lda #1
    sta _oamMirrorLocked
    stz _waitingForFramePresent
    
    sep #$20
    .a8
    ; ensure PPU Y position is between 220 and the max value (hasn't wrapped to zero)
    ; this ensures HDMA will be initialized correctly (on scanline 0)
    lda STAT78 ; reset "which byte" flipflop
    lda SLHV ; latch current beam location
    ldy OPVCT ; get scanline #
    lda OPVCT
    and #$01
    xba
    tya
    rep #$20
    .a16
    ldy TIMEUP
    bmi .die_dma_overrun
    ; If we are on scanline 261, the overhead of installing the handler,
    ; exiting the interrupt, and re-entering will take too long. Just go
    ; directly to the OAM DMA code.
    cmp #261
    bcs IRQHANDLER_OamDma
    ; install another IRQ handler for later on, to execute the OAM DMA
    rep #$30
    jsl _SetupOamDmaIrqHandler
    jmp _irq_epilogue

.die_dma_overrun:
    sep #$20
    rep #$10
    .a8
    .x16
    stz NMITIMEN
    ldx #$dead
    ldy #$0001
    jmp .die_dma_overrun

_SetupOamDmaIrqHandler:
    IRQ_SETUP IRQHANDLER_OamDma, 160, 261

IRQHANDLER_OamDma:
    sep #$10
    .a16
    .x8
    ; set up precise timing for starting DMA
    lda #2
    sta HTIME
    lda #0
    sta VTIME
    ; acknowledge IRQ
    ldy TIMEUP
    ; once IRQ fires, trigger DMA - this needs to be precisely timed to avoid
    ; finishing at the same time as HDMA starts
    ldy #$01
    wai
    sty MDMAEN
    ; clear IRQ latch
    ldy TIMEUP

    ; ; disable any layers from displaying by writing TM/TS
    ; stz TM
    ; ; wait for the right moment to disable force-blank
    ; lda #276
    ; sta HTIME
    ; lda #4
    ; sta VTIME
    ; ldy _REGMIRROR_INIDISP
    ; wai
    ; ; work around INIDISP early read glitch by ensuring the last data bus
    ; ; value is $0F (no force-blank, no brightness)
    ; ; (the last instruction byte read will be the last value on the bus)
    ; sty INIDISP|$0F0000
    ; ; clear IRQ latch
    ; ldy TIMEUP
    ; ; wait for the right moment to re-enable display
    ; lda #276
    ; sta HTIME
    ; lda #6
    ; sta VTIME
    ; lda _REGMIRROR_TMTS
    ; wai
    ; sta TM
    ; ; clear IRQ latch
    ; ldy TIMEUP

    ; set up IRQ to go off for "next NMI"
    rep #$30
    jsl _DisableIrqHandler

    stz _oamMirrorLocked

    jmp _irq_epilogue

___irq_vblank:
    rep #$20
    inc _nmiCount
    rti

    .section "_text.huge"
    .global _inidispHdmaTable
    .extern _inidispForScreenOff
    .extern _inidispForScreenPreOn
    .extern _inidispForScreenOn
_inidispHdmaTable:
    .db 3
    .dw _inidispForScreenOff
    .db 1
    .dw _inidispForScreenPreOn
    .db 123
    .dw _inidispForScreenOn
    .db (220-123-4)
    .dw _inidispForScreenOn
    .db 1
    .dw _inidispForScreenOff
    .db 0
