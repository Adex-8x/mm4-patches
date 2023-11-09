; ------------------------------------------------------------------------------
; Play All Box
; No params
; ------------------------------------------------------------------------------

.relativeinclude on
.nds
.arm

.definelabel MaxSize, 0x810

; Uncomment/comment the following labels depending on your version.

; For US
.include "lib/stdlib_us.asm"
.definelabel ProcStartAddress, 0x022E7248
.definelabel ProcJumpAddress, 0x022E7AC0
.definelabel AssemblyPointer, 0x20B0A48

; For EU
;.include "lib/stdlib_eu.asm"
;.definelabel ProcStartAddress, 0x022E7B88
;.definelabel ProcJumpAddress, 0x022E8400
;.definelabel WriteSave, 0x020492A0


; File creation
.create "./code_out.bin", 0x022E7248 ; For EU: 0x022E7B88
	.org ProcStartAddress
	.area MaxSize

		push r9
		mov r1, #0
		ldr r0,=AssemblyPointer
		ldr r0, [r0]
		sub r0, r0, #0x700
		sub r0, r0, #0x4c
		str r1, [r0]
		mov r0, #0
		mov r1, #0x33
		bl #0x204b4ec
		mov r9,r0 ; $REQUEST_CLEAR COUNT marks which scene we're on...
		mov r0,#0
		mov r1,#0x14
		bl #0x204b4ec ; $SCENARIO_BALANCE_DEBUG marks which branch we're on...
		; Some scenes rely on the top portion of the screen...!
		ldr r12,=DBOX_FORMAT
		cmp r0,#2
		bne fetch_string
		cmp r9,#2
		cmpne r9,#8
		cmpne r9,#9
		moveq r1,#20
		streqb r1,[r12,#+0x5]
		; Text String nonsense
fetch_string:
		ldr r3,=#8126 ; Start of scene text strings...
		mov r1,#0xA
		mla r3,r0,r1,r3
		sub r9,r9,#1 ; Off by one...
		add r3, r3, r9
		mov r1, #0
		mov r2, #0
		mov r0,r12
		bl #0x202fe2c
		mov r3, r0
		mov r2, #0
		mov r1, #0xc
		mov r0, #0
		bl #0x204b988
		mov r3, #1
		mov r2, #1
		mov r1, #0xc
		mov r0, #0
		bl #0x204b988
		pop r9
		b ProcJumpAddress
DBOX_FORMAT:
	; Function to update stuff
	.byte 0x10 ;0x88
	.byte 0xFF ;0xF4
	.byte 0x02
	.byte 0x02
	.byte 0x1 ; X offset
	.byte 0x1 ; Y offset
	.byte 0x1E ; Width
	.byte 0x2 ; Height
	.byte 0x0 ; Screen
	.byte 0xFC ; Frame Type (0xFA for blank)
	.fill 0x6, 0x0
		.pool
	.endarea
.close
