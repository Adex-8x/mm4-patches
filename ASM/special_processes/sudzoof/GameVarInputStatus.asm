; 
; ------------------------------------------------------------------------------
; Checks if an input is in status held/pressed and put it into $SCENARIO_TALK_BIT_FLAG
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
.definelabel SetGameVarIndexed, 0x0204B988
.definelabel SetGameVar, 0x0204B820

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
		
		sub r13,r13,#4
		
		; Code here
		mov r0,#0
		mov r1,r13
		cmp r6,#0
		bne check_held
		bl 0x0200625C
		b end_check
	check_held:
		bl 0x020061EC
	end_check:
		
		mov r1, #18
		mov r2, #0
	begin_loop:
		cmp r2, #14
		bge end

		ldrh r3, [r13]

		mov r0, #1
		lsl r0, r0, r2

		tst r3, r0
		movne r3, #1
		moveq r3, #0

		mov r0, #0
		push{r0-r3}
		bl SetGameVarIndexed
		pop{r0-r3}
		add r2, r2, #1
		b begin_loop

end:

		add r13,r13,#4
		; Always branch at the end
		b ProcJumpAddress
		.pool
	.endarea
.close
