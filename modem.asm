; ------------------------------------------------------------------------
;
; Controls an NTT Data modem connected on controller port 2
;
; ------------------------------------------------------------------------

.include hdr.asm

.equ  REG_JOYA    $004016
.equ  REG_JOYB    $004017
.equ  REG_WRIO    $004201
.equ  REG_HVBJOY    $004212

.equ  REG_JOY1L   $004218
.equ  REG_JOY2L   $00421A

.SECTION ".modemIO" SUPERFREE

; Reads the data received from the modem on $4017
readModem:
    php
    sep #$20
    rep #$10
    lda REG_JOYB ;#modemInbound
    sta.w modemRead
    plp
    rtl

; Writes to the modem by probing $4016 and then writing $4201
writeModem:
    php
    sep #$20
    rep #$10
    jsr strobePort
    lda.w #modemWrite
    sta.w REG_WRIO ;modemOutbound
    jsr waitOnModem
    plp
    rtl

; Strobe controller port 1
strobePort:
    lda #1
    stz REG_JOYA
    sta.w REG_JOYA
    stz REG_JOYA
    rts

; The modem requires a period between each write
waitOnModem:
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    rts

.ENDS