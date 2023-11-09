
; Menu
.org 0x0238a510
.area 0x4
	b 0x0238a858 ; welcome to duskull bank
.endarea

.org 0x0238a624
.area 0xC
Exit:
	mov r1,#0x6
	str r1,[r3,#0x8]
	nop
.endarea

.org 0x0238a814
.area 0x4
	;bl 0x202F148
	b 0x0238a624
.endarea

.org 0x0238a514
.area 0x4
	b 0x0238a56c ; oops, don't change
.endarea

.org 0x0238a524 ; press B during deposit
.area 0x4
	b 0x0238aa08 ; 0x0238a56c
.endarea

.org 0x0238a780 ; text string 0x379 display
.area 0x4
	b Exit
.endarea



; don't show dbox on confirmation
.org 0x0238aa0c
.area 0x4
	nop ; bl 0x0202f488; 0x202F148 ; nop
.endarea

.org 0x0238aa80
.area 0x4
	nop
.endarea




; please fix the bug
;.org 0x0238a524
;.area 0x4
;	b 0x0238a7ac
;.endarea





; Portrait stuff
.org 0x0238a19c
.area 0x4
	mvn r1,#0
.endarea


.org 0x0238a1d8
.area 0x4
	b 0x0238a218
.endarea


; Text Flag Stuff
.org 0x0238a900
.area 0x4
	mov r1,r12 ; add r1,r12,#0x3000
.endarea

.org 0x0238a908
.area 0x4
	mov r3,#0
.endarea

.org 0x0238ad60
.area 0x4
	.word 0x1015
.endarea

; 895 = forever, if you wish

; 0238a790 is the final message being printed
; 0238a584 is before jump back to main menu