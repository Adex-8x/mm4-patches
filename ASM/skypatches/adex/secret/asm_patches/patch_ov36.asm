.org 0x023A7080+0x30F70+0x24+0xB4+0xC4+0x34+0x434
.area 0x50

NewExtensionHook:
	push r0,r2,r14
	add r0,r13,#0xC
	ldr r1,=SPECIAL_STR
	bl Strcmp
	cmp r0,#0
	ldrne r1,=0x023196c4
	ldreq r1,=NEW_FORMAT
	pop r0,r2,r15
.pool
SPECIAL_STR:
	.asciiz "marcus"
	.align
NEW_FORMAT:
	.asciiz "SCRIPT/%s/%s.403"
	.align
.endarea
