.org 0x023A7080+0x30F70
.area 0x20
CheckTalkFlag:
	mov r0,#0
	mov r1,#18
	mov r2,#1
	bl GetGameVarIndexed
	cmp r0,#0
	beq VanillaBehavior
	b BeforeSetGroundDeletion+28
.endarea
