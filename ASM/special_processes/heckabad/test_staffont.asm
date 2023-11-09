; ------------------------------------------------------------------------------
; Let's try to display the staffont!
; ------------------------------------------------------------------------------

.relativeinclude on
.nds
.arm

.definelabel MaxSize, 0x810

.include "lib/stdlib_us.asm"
.definelabel ProcStartAddress, 0x022E7248
.definelabel ProcJumpAddress, 0x022E7AC0

; File creation
.create "./code_out.bin", 0x022E7248
	.org ProcStartAddress
	.area MaxSize

		mov r0,r7
		cmp r0,#0
		beq markfont
		bl 0x02025B90 ; staffont
		b ProcJumpAddress
markfont:
		bl 0x02025AD8 ; font
		bl 0x02025C14 ; pal
		b ProcJumpAddress
		.pool
	.endarea
.close