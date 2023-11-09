; 
; ------------------------------------------------------------------------------
; Checks if an input is in status held/pressed
; Param 1: Input 1 indicates a set of buttons of which one should be held/pressed
; Param 2: Input 2 0 if checking for pressed, 1 for held
; Return 1 if conditions are met, 0 otherwise
; Currently unstable: pressed should not be used since
; it is unknown when the game refreshes the input statuses
; As such some inputs can be missed in an active wait method
; ------------------------------------------------------------------------------


.relativeinclude on
.nds
.arm


.definelabel MaxSize, 0x810

; Uncomment the correct version
; TODO: US only

; For US
.include "lib/stdlib_us.asm"
.definelabel ProcStartAddress, 0x022E7248
.definelabel ProcJumpAddress, 0x022E7AC0
.definelabel GetGameVar, 0x0204B4EC
.definelabel SetGameVar, 0x0204B820

.definelabel Info, 0x023A7080+0x8B0

; For EU
;.include "lib/stdlib_eu.asm"
;.definelabel ProcStartAddress, 0x022E7B88
;.definelabel ProcJumpAddress, 0x022E8400


; File creation
.create "./code_out.bin", 0x022E7248 ; Change to the actual offset as this directive doesn't accept labels
	.org ProcStartAddress
	.area MaxSize ; Define the size of the area
		; Usable Variables: 
		; r7 = First Argument
		; r6 = Second Argument
		; Returns: 
		; r0 = User Defined Value
		; Registers r4 to r11 and r13 must remain unchanged after the execution of that code
		
		mov r0, #0
		mov r1, #21 ; CRYSTAL_COLOR1
		bl GetGameVar
		push{r0}
		mov r0, #0
		mov r1, #22
		bl GetGameVar
		mov r1, r0
		pop{r0}
		mov r3, #2
		mul r3, r7, r3
		ldr r2, =Info
		strb r0, [r2, r3]
		add r2, r2, #1
		strb r1, [r2, r3]

		; Always branch at the end
		b ProcJumpAddress
		.pool
	.endarea
.close
