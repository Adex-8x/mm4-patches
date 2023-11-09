; ------------------------------------------------------------------------------
; HeckaBad
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
.definelabel DEFAULT_DBOX_LOCATION_AND_SIZE, 0x051C1102
.definelabel DEFAULT_DBOX_SETTINGS, 0x0000FD00

; File creation
.create "./code_out.bin", 0x022E7248
	.org ProcStartAddress
	.area MaxSize ; Define the size of the area
		; Usable Variables: 
		; r7 = New Default DBOX Location (0 to reset to normal)
		; r6 = New Default DBOX Size (0 to reset to normal)
		; Returns: 
		; r0 = User Defined Value
		; Registers r4 to r11 and r13 must remain unchanged after the execution of that code
        
        ; Change location/size.
        ldr   r2,=#0x0209AF30
        cmp   r7,#0
        cmpne r6,#0
        ldreq r1,=DEFAULT_DBOX_LOCATION_AND_SIZE
        streq r1,[r2,#0x0]
        strneh r7,[r2,#0x0]
        strneh r6,[r2,#0x2]
		
		; Always branch at the end
		b ProcJumpAddress
		.pool
	.endarea
.close