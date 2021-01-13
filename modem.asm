; Hardware registers
;.equ joypadA $4016
;.equ modemInbound $4017
;.equ modemOutbound $4201

; ------------------------------------------------------------------------
;
; Controls an NTT Data modem connected on controller port 2
;
; ------------------------------------------------------------------------

.ramsection ".modemRW" bank 0 slot 1
modemRead dsb 10
modemWrite dsb 10
.ends

.SECTION ".modemIO" SUPERFREE

; Reads the data received from the modem on $4017
readModem:
    php
    sep #$20
    rep #$10
    lda.w REG_JOYB ;#modemInbound
    sta.w modemRead
    plp
    rtl

; Writes to the modem by probing $4016 and then writing $4201
writeModem:
    php
    sep #$20
    rep #$10
    stz REG_JOYA ;joypadA
    lda #1
    sta.w REG_JOYA ;joypadA
    stz joypadA
    lda.w #modemWrite
    sta.w REG_WRIO ;modemOutbound
    plp
    rtl

.ENDS