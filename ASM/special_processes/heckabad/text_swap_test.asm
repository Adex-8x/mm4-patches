; ------------------------------------------------------------------------------
; The EoP Team
; ASM made for Explorers Of Pain that swaps the text in a dbox. Beware when
; using this process. We know it works, but we don't know if it works
; because of extreme jank or what.
; Based on the template provided by https://github.com/SkyTemple
; ------------------------------------------------------------------------------


.relativeinclude on
.nds
.arm


.definelabel MaxSize, 0x810

; Uncomment the correct version

; For US
.include "lib/stdlib_us.asm"
.definelabel ProcStartAddress, 0x022E7248
.definelabel ProcJumpAddress, 0x022E7AC0

; File creation
.create "./code_out.bin", 0x022E7248
	.org ProcStartAddress
	.area MaxSize ; Define the size of the area
		; Usable Variables: 
		; r7 = D Box ID
		; r6 = Text String To Use
		; Returns: 
		; r0 = User Defined Value
		; Registers r4 to r11 and r13 must remain unchanged after the execution of that code
		
		mov r0,r7
        ldr r1,=#0x404
        mov r2,r6
        mov r3,#0
        bl  0x202F1B4
		
		; Always branch at the end
		b ProcJumpAddress
		.pool
	.endarea
.close