.org 0x023A7080+0x30F70+0x24
.area 0xB0

FaceTagHook:
	push r5
	ldr r0,[r13, StackThing+4]
	ldr r1,=face_str
	bl TagCheck
	cmp r0,#0
	popeq r5
	beq TagCodeError
	mov r0,#13
	bl OverlayIsLoaded
	cmp r0,#1
	ldreq r5,=ScriptPortraitPointer
	beq change_face
	mov r0,#14
	bl OverlayIsLoaded
	ldr r5,=dungeon_portrait_ptr
	ldr r5,[r5]
	cmp r0,#0
	cmpne r5,#0
	beq ret
change_face:
	ldr r0,[r13, StackThing+8]
 	bl GetTagParameter
	mov r1,r0
	mov r0,r5
	bl SetPortraitExpressionID
	add r0,=portrait_dbox_id
	ldrb r0,[r0]
	mov r1,r5
	bl ShowPortrait
ret:
	pop r5
	b AfterTagIsFound

DBoxHook:
	ldrsb r0,[r5,#0x0] ; Original instruction
	add r1,=portrait_dbox_id
	strb r0,[r1]
	bx r14

DungeonHook:
	mov r4,r2 ; Original instruction
	ldr r2,=dungeon_portrait_ptr
	str r6,[r2]
	bx r14

.pool
	dungeon_portrait_ptr:
		.word 0x0
	portrait_dbox_id:
		.byte 0x0
	face_str:
		.asciiz "FACE"
.endarea