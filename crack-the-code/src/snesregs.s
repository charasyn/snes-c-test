; taken from https://github.com/PeterLemon/SNES/blob/master/LIB/SNES.INC
; thanks, krom / PeterLemon

; PPU Picture Processing Unit Ports (Write-Only)
INIDISP .equ $2100  ; Display Control 1                                     1B/W
OBSEL .equ $2101    ; Object Size & Object Base                             1B/W
OAMADDR .equ $2102  ; OAM Address                                           2B/W
OAMADDL .equ $2102  ; OAM Address (Lower 8-Bit)                             2B/W
OAMADDH .equ $2103  ; OAM Address (Upper 1-Bit) & Priority Rotation         1B/W
OAMDATA .equ $2104  ; OAM Data Write                                        1B/W D
BGMODE .equ $2105   ; BG Mode & BG Character Size                           1B/W
MOSAIC .equ $2106   ; Mosaic Size & Mosaic Enable                           1B/W
BG1SC .equ $2107    ; BG1 Screen Base & Screen Size                         1B/W
BG2SC .equ $2108    ; BG2 Screen Base & Screen Size                         1B/W
BG3SC .equ $2109    ; BG3 Screen Base & Screen Size                         1B/W
BG4SC .equ $210A    ; BG4 Screen Base & Screen Size                         1B/W
BG12NBA .equ $210B  ; BG1/BG2 Character Data Area Designation               1B/W
BG34NBA .equ $210C  ; BG3/BG4 Character Data Area Designation               1B/W
BG1HOFS .equ $210D  ; BG1 Horizontal Scroll (X) / M7HOFS                    1B/W D
BG1VOFS .equ $210E  ; BG1 Vertical   Scroll (Y) / M7VOFS                    1B/W D
BG2HOFS .equ $210F  ; BG2 Horizontal Scroll (X)                             1B/W D
BG2VOFS .equ $2110  ; BG2 Vertical   Scroll (Y)                             1B/W D
BG3HOFS .equ $2111  ; BG3 Horizontal Scroll (X)                             1B/W D
BG3VOFS .equ $2112  ; BG3 Vertical   Scroll (Y)                             1B/W D
BG4HOFS .equ $2113  ; BG4 Horizontal Scroll (X)                             1B/W D
BG4VOFS .equ $2114  ; BG4 Vertical   Scroll (Y)                             1B/W D
VMAIN .equ $2115    ; VRAM Address Increment Mode                           1B/W
VMADDR .equ $2116   ; VRAM Address                                          2B/W
VMADDL .equ $2116   ; VRAM Address    (Lower 8-Bit)                         2B/W
VMADDH .equ $2117   ; VRAM Address    (Upper 8-Bit)                         1B/W
VMDATA .equ $2118   ; VRAM Data Write                                       2B/W
VMDATAL .equ $2118  ; VRAM Data Write (Lower 8-Bit)                         2B/W
VMDATAH .equ $2119  ; VRAM Data Write (Upper 8-Bit)                         1B/W
M7SEL .equ $211A    ; Mode7 Rot/Scale Mode Settings                         1B/W
M7A .equ $211B      ; Mode7 Rot/Scale A (COSINE A) & Maths 16-Bit Operand   1B/W D
M7B .equ $211C      ; Mode7 Rot/Scale B (SINE A)   & Maths  8-bit Operand   1B/W D
M7C .equ $211D      ; Mode7 Rot/Scale C (SINE B)                            1B/W D
M7D .equ $211E      ; Mode7 Rot/Scale D (COSINE B)                          1B/W D
M7X .equ $211F      ; Mode7 Rot/Scale Center Coordinate X                   1B/W D
M7Y .equ $2120      ; Mode7 Rot/Scale Center Coordinate Y                   1B/W D
CGADDR .equ $2121   ; Palette CGRAM Address                                 1B/W
CGADD .equ $2121    ; Palette CGRAM Address                                 1B/W
CGDATA .equ $2122   ; Palette CGRAM Data Write                              1B/W D
W12SEL .equ $2123   ; Window BG1/BG2  Mask Settings                         1B/W
W34SEL .equ $2124   ; Window BG3/BG4  Mask Settings                         1B/W
WOBJSEL .equ $2125  ; Window OBJ/MATH Mask Settings                         1B/W
WH0 .equ $2126      ; Window 1 Left  Position (X1)                          1B/W
WH1 .equ $2127      ; Window 1 Right Position (X2)                          1B/W
WH2 .equ $2128      ; Window 2 Left  Position (X1)                          1B/W
WH3 .equ $2129      ; Window 2 Right Position (X2)                          1B/W
WBGLOG .equ $212A   ; Window 1/2 Mask Logic (BG1..BG4)                      1B/W
WOBJLOG .equ $212B  ; Window 1/2 Mask Logic (OBJ/MATH)                      1B/W
TM .equ $212C       ; Main Screen Designation                               1B/W
TS .equ $212D       ; Sub  Screen Designation                               1B/W
TMW .equ $212E      ; Window Area Main Screen Disable                       1B/W
TSW .equ $212F      ; Window Area Sub  Screen Disable                       1B/W
CGWSEL .equ $2130   ; Color Math Control Register A                         1B/W
CGADSUB .equ $2131  ; Color Math Control Register B                         1B/W
COLDATA .equ $2132  ; Color Math Sub Screen Backdrop Color                  1B/W
SETINI .equ $2133   ; Display Control 2                                     1B/W

; PPU Picture Processing Unit Ports (Read-Only)
MPYL .equ $2134     ; PPU1 Signed Multiply Result (Lower  8-Bit)            1B/R
MPYM .equ $2135     ; PPU1 Signed Multiply Result (Middle 8-Bit)            1B/R
MPYH .equ $2136     ; PPU1 Signed Multiply Result (Upper  8-Bit)            1B/R
SLHV .equ $2137     ; PPU1 Latch H/V-Counter By Software (Read=Strobe)      1B/R
RDOAM .equ $2138    ; PPU1 OAM  Data Read                                   1B/R D
RDVRAML .equ $2139  ; PPU1 VRAM  Data Read (Lower 8-Bit)                    1B/R
RDVRAMH .equ $213A  ; PPU1 VRAM  Data Read (Upper 8-Bit)                    1B/R
RDCGRAM .equ $213B  ; PPU2 CGRAM Data Read (Palette)                        1B/R D
OPHCT .equ $213C    ; PPU2 Horizontal Counter Latch (Scanline X)            1B/R D
OPVCT .equ $213D    ; PPU2 Vertical   Counter Latch (Scanline Y)            1B/R D
STAT77 .equ $213E   ; PPU1 Status & PPU1 Version Number                     1B/R
STAT78 .equ $213F   ; PPU2 Status & PPU2 Version Number (Bit 7=0)           1B/R

; APU Audio Processing Unit Ports (Read/Write)
APUIO0 .equ $2140   ; Main CPU To Sound CPU Communication Port 0            1B/RW
APUIO1 .equ $2141   ; Main CPU To Sound CPU Communication Port 1            1B/RW
APUIO2 .equ $2142   ; Main CPU To Sound CPU Communication Port 2            1B/RW
APUIO3 .equ $2143   ; Main CPU To Sound CPU Communication Port 3            1B/RW
; $2140..$2143 - APU Ports Mirrored To $2144..$217F

; WRAM Access Ports
WMDATA .equ $2180   ; WRAM Data Read/Write                                  1B/RW
WMADDL .equ $2181   ; WRAM Address (Lower  8-Bit)                           1B/W
WMADDM .equ $2182   ; WRAM Address (Middle 8-Bit)                           1B/W
WMADDH .equ $2183   ; WRAM Address (Upper  1-Bit)                           1B/W
; $2184..$21FF - Unused Region (Open Bus)/Expansion (B-Bus)
; $2200..$3FFF - Unused Region (A-Bus)

; CPU On-Chip I/O Ports (These Have Long Waitstates: 1.78MHz Cycles Instead Of 3.5MHz)
; ($4000..$4015 - Unused Region (Open Bus)
JOYWR .equ $4016    ; Joypad Output                                         1B/W
JOYA .equ $4016     ; Joypad Input Register A (Joypad Auto Polling)         1B/R
JOYB .equ $4017     ; Joypad Input Register B (Joypad Auto Polling)         1B/R
; $4018..$41FF - Unused Region (Open Bus)

; CPU On-Chip I/O Ports (Write-only, Read=Open Bus)
NMITIMEN .equ $4200 ; Interrupt Enable & Joypad Request                     1B/W
WRIO .equ $4201     ; Programmable I/O Port (Open-Collector Output)         1B/W
WRMPYA .equ $4202   ; Set Unsigned  8-Bit Multiplicand                      1B/W
WRMPYB .equ $4203   ; Set Unsigned  8-Bit Multiplier & Start Multiplication 1B/W
WRDIVL .equ $4204   ; Set Unsigned 16-Bit Dividend (Lower 8-Bit)            2B/W
WRDIVH .equ $4205   ; Set Unsigned 16-Bit Dividend (Upper 8-Bit)            1B/W
WRDIVB .equ $4206   ; Set Unsigned  8-Bit Divisor & Start Division          1B/W
HTIME .equ $4207    ; H-Count Timer Setting                                 2B/W
HTIMEL .equ $4207   ; H-Count Timer Setting (Lower 8-Bit)                   2B/W
HTIMEH .equ $4208   ; H-Count Timer Setting (Upper 1bit)                    1B/W
VTIME .equ $4209    ; V-Count Timer Setting                                 2B/W
VTIMEL .equ $4209   ; V-Count Timer Setting (Lower 8-Bit)                   2B/W
VTIMEH .equ $420A   ; V-Count Timer Setting (Upper 1-Bit)                   1B/W
MDMAEN .equ $420B   ; Select General Purpose DMA Channels & Start Transfer  1B/W
HDMAEN .equ $420C   ; Select H-Blank DMA (H-DMA) Channels                   1B/W
MEMSEL .equ $420D   ; Memory-2 Waitstate Control                            1B/W
; $420E..$420F - Unused Region (Open Bus)

; CPU On-Chip I/O Ports (Read-only)
RDNMI .equ $4210    ; V-Blank NMI Flag and CPU Version Number (Read/Ack)    1B/R
TIMEUP .equ $4211   ; H/V-Timer IRQ Flag (Read/Ack)                         1B/R
HVBJOY .equ $4212   ; H/V-Blank Flag & Joypad Busy Flag                     1B/R
RDIO .equ $4213     ; Joypad Programmable I/O Port (Input)                  1B/R
RDDIVL .equ $4214   ; Unsigned Div Result (Quotient) (Lower 8-Bit)          2B/R
RDDIVH .equ $4215   ; Unsigned Div Result (Quotient) (Upper 8-Bit)          1B/R
RDMPYL .equ $4216   ; Unsigned Div Remainder / Mul Product (Lower 8-Bit)    2B/R
RDMPYH .equ $4217   ; Unsigned Div Remainder / Mul Product (Upper 8-Bit)    1B/R
JOY1L .equ $4218    ; Joypad 1 (Gameport 1, Pin 4) (Lower 8-Bit)            2B/R
JOY1H .equ $4219    ; Joypad 1 (Gameport 1, Pin 4) (Upper 8-Bit)            1B/R
JOY2L .equ $421A    ; Joypad 2 (Gameport 2, Pin 4) (Lower 8-Bit)            2B/R
JOY2H .equ $421B    ; Joypad 2 (Gameport 2, Pin 4) (Upper 8-Bit)            1B/R
JOY3L .equ $421C    ; Joypad 3 (Gameport 1, Pin 5) (Lower 8-Bit)            2B/R
JOY3H .equ $421D    ; Joypad 3 (Gameport 1, Pin 5) (Upper 8-Bit)            1B/R
JOY4L .equ $421E    ; Joypad 4 (Gameport 2, Pin 5) (Lower 8-Bit)            2B/R
JOY4H .equ $421F    ; Joypad 4 (Gameport 2, Pin 5) (Upper 8-Bit)            1B/R
; $4220..$42FF - Unused Region (Open Bus)

; CPU DMA Ports (Read/Write) ($43XP X = Channel Number 0..7, P = Port)
DMAP0 .equ $4300    ; DMA0 DMA/HDMA Parameters                              1B/RW
BBAD0 .equ $4301    ; DMA0 DMA/HDMA I/O-Bus Address (PPU-Bus AKA B-Bus)     1B/RW
A1T0 .equ $4302     ; DMA0 DMA/HDMA Table Start Address                     2B/RW
A1T0L .equ $4302    ; DMA0 DMA/HDMA Table Start Address (Lower 8-Bit)       2B/RW
A1T0H .equ $4303    ; DMA0 DMA/HDMA Table Start Address (Upper 8-Bit)       1B/RW
A1B0 .equ $4304     ; DMA0 DMA/HDMA Table Start Address (Bank)              1B/RW
DAS0 .equ $4305     ; DMA0 DMA Count / Indirect HDMA Address                2B/RW
DAS0L .equ $4305    ; DMA0 DMA Count / Indirect HDMA Address (Lower 8-Bit)  2B/RW
DAS0H .equ $4306    ; DMA0 DMA Count / Indirect HDMA Address (Upper 8-Bit)  1B/RW
DASB0 .equ $4307    ; DMA0 Indirect HDMA Address (Bank)                     1B/RW
A2A0L .equ $4308    ; DMA0 HDMA Table Current Address (Lower 8-Bit)         2B/RW
A2A0H .equ $4309    ; DMA0 HDMA Table Current Address (Upper 8-Bit)         1B/RW
NTRL0 .equ $430A    ; DMA0 HDMA Line-Counter (From Current Table entry)     1B/RW
UNUSED0 .equ $430B  ; DMA0 Unused Byte                                      1B/RW
; $430C..$430E - Unused Region (Open Bus)
MIRR0 .equ $430F    ; DMA0 Mirror Of $430B                                  1B/RW

DMAP1 .equ $4310    ; DMA1 DMA/HDMA Parameters                              1B/RW
BBAD1 .equ $4311    ; DMA1 DMA/HDMA I/O-Bus Address (PPU-Bus AKA B-Bus)     1B/RW
A1T1 .equ $4312     ; DMA1 DMA/HDMA Table Start Address (Lower 8-Bit)       2B/RW
A1T1L .equ $4312    ; DMA1 DMA/HDMA Table Start Address (Lower 8-Bit)       2B/RW
A1T1H .equ $4313    ; DMA1 DMA/HDMA Table Start Address (Upper 8-Bit)       1B/RW
A1B1 .equ $4314     ; DMA1 DMA/HDMA Table Start Address (Bank)              1B/RW
DAS1  .equ $4315    ; DMA1 DMA Count / Indirect HDMA Address (Lower 8-Bit)  2B/RW
DAS1L .equ $4315    ; DMA1 DMA Count / Indirect HDMA Address (Lower 8-Bit)  2B/RW
DAS1H .equ $4316    ; DMA1 DMA Count / Indirect HDMA Address (Upper 8-Bit)  1B/RW
DASB1 .equ $4317    ; DMA1 Indirect HDMA Address (Bank)                     1B/RW
A2A1L .equ $4318    ; DMA1 HDMA Table Current Address (Lower 8-Bit)         2B/RW
A2A1H .equ $4319    ; DMA1 HDMA Table Current Address (Upper 8-Bit)         1B/RW
NTRL1 .equ $431A    ; DMA1 HDMA Line-Counter (From Current Table entry)     1B/RW
UNUSED1 .equ $431B  ; DMA1 Unused Byte                                      1B/RW
; $431C..$431E - Unused Region (Open Bus)
MIRR1 .equ $431F    ; DMA1 Mirror Of $431B                                  1B/RW

DMAP2 .equ $4320    ; DMA2 DMA/HDMA Parameters                              1B/RW
BBAD2 .equ $4321    ; DMA2 DMA/HDMA I/O-Bus Address (PPU-Bus AKA B-Bus)     1B/RW
A1T2L .equ $4322    ; DMA2 DMA/HDMA Table Start Address (Lower 8-Bit)       2B/RW
A1T2H .equ $4323    ; DMA2 DMA/HDMA Table Start Address (Upper 8-Bit)       1B/RW
A1B2 .equ $4324     ; DMA2 DMA/HDMA Table Start Address (Bank)              1B/RW
DAS2L .equ $4325    ; DMA2 DMA Count / Indirect HDMA Address (Lower 8-Bit)  2B/RW
DAS2H .equ $4326    ; DMA2 DMA Count / Indirect HDMA Address (Upper 8-Bit)  1B/RW
DASB2 .equ $4327    ; DMA2 Indirect HDMA Address (Bank)                     1B/RW
A2A2L .equ $4328    ; DMA2 HDMA Table Current Address (Lower 8-Bit)         2B/RW
A2A2H .equ $4329    ; DMA2 HDMA Table Current Address (Upper 8-Bit)         1B/RW
NTRL2 .equ $432A    ; DMA2 HDMA Line-Counter (From Current Table entry)     1B/RW
UNUSED2 .equ $432B  ; DMA2 Unused Byte                                      1B/RW
; $432C..$432E - Unused Region (Open Bus)
MIRR2 .equ $432F    ; DMA2 Mirror Of $432B                                  1B/RW

DMAP3 .equ $4330    ; DMA3 DMA/HDMA Parameters                              1B/RW
BBAD3 .equ $4331    ; DMA3 DMA/HDMA I/O-Bus Address (PPU-Bus AKA B-Bus)     1B/RW
A1T3L .equ $4332    ; DMA3 DMA/HDMA Table Start Address (Lower 8-Bit)       2B/RW
A1T3H .equ $4333    ; DMA3 DMA/HDMA Table Start Address (Upper 8-Bit)       1B/RW
A1B3 .equ $4334     ; DMA3 DMA/HDMA Table Start Address (Bank)              1B/RW
DAS3L .equ $4335    ; DMA3 DMA Count / Indirect HDMA Address (Lower 8-Bit)  2B/RW
DAS3H .equ $4336    ; DMA3 DMA Count / Indirect HDMA Address (Upper 8-Bit)  1B/RW
DASB3 .equ $4337    ; DMA3 Indirect HDMA Address (Bank)                     1B/RW
A2A3L .equ $4338    ; DMA3 HDMA Table Current Address (Lower 8-Bit)         2B/RW
A2A3H .equ $4339    ; DMA3 HDMA Table Current Address (Upper 8-Bit)         1B/RW
NTRL3 .equ $433A    ; DMA3 HDMA Line-Counter (From Current Table entry)     1B/RW
UNUSED3 .equ $433B  ; DMA3 Unused Byte                                      1B/RW
; $433C..$433E - Unused Region (Open Bus)
MIRR3 .equ $433F    ; DMA3 Mirror Of $433B                                  1B/RW

DMAP4 .equ $4340    ; DMA4 DMA/HDMA Parameters                              1B/RW
BBAD4 .equ $4341    ; DMA4 DMA/HDMA I/O-Bus Address (PPU-Bus AKA B-Bus)     1B/RW
A1T4L .equ $4342    ; DMA4 DMA/HDMA Table Start Address (Lower 8-Bit)       2B/RW
A1T4H .equ $4343    ; DMA4 DMA/HDMA Table Start Address (Upper 8-Bit)       1B/RW
A1B4 .equ $4344     ; DMA4 DMA/HDMA Table Start Address (Bank)              1B/RW
DAS4L .equ $4345    ; DMA4 DMA Count / Indirect HDMA Address (Lower 8-Bit)  2B/RW
DAS4H .equ $4346    ; DMA4 DMA Count / Indirect HDMA Address (Upper 8-Bit)  1B/RW
DASB4 .equ $4347    ; DMA4 Indirect HDMA Address (Bank)                     1B/RW
A2A4L .equ $4348    ; DMA4 HDMA Table Current Address (Lower 8-Bit)         2B/RW
A2A4H .equ $4349    ; DMA4 HDMA Table Current Address (Upper 8-Bit)         1B/RW
NTRL4 .equ $434A    ; DMA4 HDMA Line-Counter (From Current Table entry)     1B/RW
UNUSED4 .equ $434B  ; DMA4 Unused Byte                                      1B/RW
; $434C..$434E - Unused Region (Open Bus)
MIRR4 .equ $434F    ; DMA4 Mirror Of $434B                                  1B/RW

DMAP5 .equ $4350    ; DMA5 DMA/HDMA Parameters                              1B/RW
BBAD5 .equ $4351    ; DMA5 DMA/HDMA I/O-Bus Address (PPU-Bus AKA B-Bus)     1B/RW
A1T5L .equ $4352    ; DMA5 DMA/HDMA Table Start Address (Lower 8-Bit)       2B/RW
A1T5H .equ $4353    ; DMA5 DMA/HDMA Table Start Address (Upper 8-Bit)       1B/RW
A1B5 .equ $4354     ; DMA5 DMA/HDMA Table Start Address (Bank)              1B/RW
DAS5L .equ $4355    ; DMA5 DMA Count / Indirect HDMA Address (Lower 8-Bit)  2B/RW
DAS5H .equ $4356    ; DMA5 DMA Count / Indirect HDMA Address (Upper 8-Bit)  1B/RW
DASB5 .equ $4357    ; DMA5 Indirect HDMA Address (Bank)                     1B/RW
A2A5L .equ $4358    ; DMA5 HDMA Table Current Address (Lower 8-Bit)         2B/RW
A2A5H .equ $4359    ; DMA5 HDMA Table Current Address (Upper 8-Bit)         1B/RW
NTRL5 .equ $435A    ; DMA5 HDMA Line-Counter (From Current Table entry)     1B/RW
UNUSED5 .equ $435B  ; DMA5 Unused Byte                                      1B/RW
; $435C..$435E - Unused Region (Open Bus)
MIRR5 .equ $435F    ; DMA5 Mirror Of $435B                                  1B/RW

DMAP6 .equ $4360    ; DMA6 DMA/HDMA Parameters                              1B/RW
BBAD6 .equ $4361    ; DMA6 DMA/HDMA I/O-Bus Address (PPU-Bus AKA B-Bus)     1B/RW
A1T6L .equ $4362    ; DMA6 DMA/HDMA Table Start Address (Lower 8-Bit)       2B/RW
A1T6H .equ $4363    ; DMA6 DMA/HDMA Table Start Address (Upper 8-Bit)       1B/RW
A1B6 .equ $4364     ; DMA6 DMA/HDMA Table Start Address (Bank)              1B/RW
DAS6L .equ $4365    ; DMA6 DMA Count / Indirect HDMA Address (Lower 8-Bit)  2B/RW
DAS6H .equ $4366    ; DMA6 DMA Count / Indirect HDMA Address (Upper 8-Bit)  1B/RW
DASB6 .equ $4367    ; DMA6 Indirect HDMA Address (Bank)                     1B/RW
A2A6L .equ $4368    ; DMA6 HDMA Table Current Address (Lower 8-Bit)         2B/RW
A2A6H .equ $4369    ; DMA6 HDMA Table Current Address (Upper 8-Bit)         1B/RW
NTRL6 .equ $436A    ; DMA6 HDMA Line-Counter (From Current Table entry)     1B/RW
UNUSED6 .equ $436B  ; DMA6 Unused Byte                                      1B/RW
; $436C..$436E - Unused Region (Open Bus)
MIRR6 .equ $436F    ; DMA6 Mirror Of $436B                                  1B/RW

DMAP7 .equ $4370    ; DMA7 DMA/HDMA Parameters                              1B/RW
BBAD7 .equ $4371    ; DMA7 DMA/HDMA I/O-Bus Address (PPU-Bus AKA B-Bus)     1B/RW
A1T7L .equ $4372    ; DMA7 DMA/HDMA Table Start Address (Lower 8-Bit)       2B/RW
A1T7H .equ $4373    ; DMA7 DMA/HDMA Table Start Address (Upper 8-Bit)       1B/RW
A1B7 .equ $4374     ; DMA7 DMA/HDMA Table Start Address (Bank)              1B/RW
DAS7L .equ $4375    ; DMA7 DMA Count / Indirect HDMA Address (Lower 8-Bit)  2B/RW
DAS7H .equ $4376    ; DMA7 DMA Count / Indirect HDMA Address (Upper 8-Bit)  1B/RW
DASB7 .equ $4377    ; DMA7 Indirect HDMA Address (Bank)                     1B/RW
A2A7L .equ $4378    ; DMA7 HDMA Table Current Address (Lower 8-Bit)         2B/RW
A2A7H .equ $4379    ; DMA7 HDMA Table Current Address (Upper 8-Bit)         1B/RW
NTRL7 .equ $437A    ; DMA7 HDMA Line-Counter (From Current Table entry)     1B/RW
UNUSED7 .equ $437B  ; DMA7 Unused Byte                                      1B/RW
; $437C..$437E - Unused Region (Open Bus)
MIRR7 .equ $437F    ; DMA7 Mirror Of $437B                                  1B/RW

