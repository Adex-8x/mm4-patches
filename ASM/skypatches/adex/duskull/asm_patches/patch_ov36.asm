.org 0x023A7080+0x30F70+0x24+0xB4+0xC4
.area 0x30
StupidHook:
	push r14
	bl 0x0200625C
	ldrh r0,[r1]
	ldr r12,=0b1111111111111101
	and r0,r0,r12
	strh r0,[r1]
	pop r15
.pool
.endarea