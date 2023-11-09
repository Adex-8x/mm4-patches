; ------------------------------------------------------------------------------
; Check Many Team Names
; Checks if a team name is equal to some predefined names!
; Returns: 0 for no match, 1 for Name 1, 2 for Name 2, etc.
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

		push r10
		sub r13,r13,#0x20
		ldr r0,=0x020B0A48
		ldr r0,[r0]
		sub r0,r0,#0x400
		sub r0,r0,#0xc8
		mov r1,r13
		bl AllLowercase
		mov r10,#0
@@name_loop:
		mov r0,r13
		ldr r1,=NAMES
		ldr r1,[r1,r10,lsl #+0x2]
		cmp r1,#0
		moveq r0,#0
		beq @@ret
		mov r2,#10
		bl #0x02089940
		add r10,r10,#1
		cmp r0,#0
		moveq r0,r10
		bne @@name_loop
@@ret:
		add r13,r13,#0x20
		pop r10
		b ProcJumpAddress
		.pool

AllLowercase:
		push r4-r6,r14
		mov r6,r0
		mov r5,r1
		mov r4,#0
		b lowercase_loop_next_iter
lowercase_loop:
		ldrsb r0,[r6],#+0x1
		cmp r0,#0
		beq lowercase_ret
		bl 0x0200238C
		strb r0,[r5],#0x1
		add r4,r4,#0x1
lowercase_loop_next_iter:
		cmp r4,#0xA
		blt lowercase_loop
lowercase_ret:
		mov r0,#0
		strb r0,[r5,#+0x0]
		pop r4-r6,r15

	NAMES:
		.word name_1
		.word name_2
		.word name_3
		.word name_4
		.word name_5
		.word name_6
		.word name_7
		.word name_8
		.word name_9
		.word name_10
		.word name_11
		.word name_12
		.word name_13
		.word name_14
		.word name_15
		.word name_16
		.word name_17
		.word name_18
		.word name_19
		.word name_20
		.word name_21
		.word name_22
		.word name_23
		.word name_24
		.word name_25
		.word name_26
		.word name_27
		.word name_28
		.word name_29
		.word name_30
		.word name_31
		.word name_32
		.word name_33
		.word name_34
		.word name_35
		.word name_36
		.word name_37
		.word name_38
		.word name_39
		.word name_40
		.word name_41
		.word name_42
		.word name_43
		.word name_44
		.word name_45
		.word name_46
		.word name_47
		.word name_48
		.word name_49
		.word name_50
		.word name_51
		.word name_52
		.word name_53
		.word name_54
		.word name_55
		.word name_56
		.word name_57
		.word name_58
		.word name_59
		.word name_60
		.word name_61
		.word name_62
		.word name_63
		.word name_64
		.word 0x0
	; Branch B
	name_1: 
		.asciiz "murpi"
	name_2:
		.asciiz "gelius"
	name_3:
		.asciiz "cucumber"
	name_4:
		.asciiz "minarchu"
	name_5: 
		.asciiz "big"
	name_6:
		.asciiz "birdobssess"
	name_7:
		.asciiz "auraxalaiv"
	name_8:
		.asciiz "axcel"
	name_9: 
		.asciiz "minemaker"
	name_10:
		.asciiz "shimx"
	name_11:
		.asciiz "3p1c"
	name_12:
		.asciiz "haifan"
	name_13:
		.asciiz "ecla"
	; Branch G
	name_14: 
		.asciiz "cait sith"
	name_15:
		.asciiz "cait"
	name_16:
		.asciiz "sergey"
	name_17:
		.asciiz "pixel"
	name_18: 
		.asciiz "nolasmor"
	name_19:
		.asciiz "bwappi"
	name_20:
		.asciiz "shyrain"
	name_21:
		.asciiz "maruvert"
	name_22: 
		.asciiz "memersimon"
	name_23:
		.asciiz "simon"
	name_24:
		.asciiz "heckabad"
	name_25:
		.asciiz "1235nut"
	name_26:
		.asciiz "solargress"
	name_27: 
		.asciiz "chesyon"
	; Branch Y
	name_28:
		.asciiz "espik"
	name_29:
		.asciiz "sudzoof"
	name_30:
		.asciiz "dutch"
	name_31: 
		.asciiz "ambush"
	name_32:
		.asciiz "pazkallan"
	name_33:
		.asciiz "paz"
	name_34:
		.asciiz "irdkwia"
	name_35: 
		.asciiz "boredcrow"
	name_36:
		.asciiz "guy"
	name_37:
		.asciiz "dovey"
	name_38:
		.asciiz "polybo"
	name_39:
		.asciiz "parker"
	; Branch K
	name_40: 
		.asciiz "mew"
	name_41:
		.asciiz "25pi25"
	name_42:
		.asciiz "sec"
	name_43:
		.asciiz "j.p."
	name_44: 
		.asciiz "lurantis"
	name_45:
		.asciiz "shiny"
	name_46:
		.asciiz "okami"
	name_47:
		.asciiz "argonien"
	name_48: 
		.asciiz "adakite"
	name_49:
		.asciiz "marius"
	name_50:
		.asciiz "zorquil"
	name_51:
		.asciiz "noivern"
	name_52:
		.asciiz "juanmasg"
	; Organizers
	name_53:
		.asciiz "burrito"
	name_54:
		.asciiz "groovy"
	name_55:
		.asciiz "kecleon"
	name_56:
		.asciiz "kec"
	name_57:
		.asciiz "adex"
	; I forgor
	name_58:
		.asciiz "starborb"
	name_59:
		.asciiz "borb"
	name_60:
		.asciiz "glec"
	name_61:
		.asciiz "keckleon"
	name_62:
		.asciiz "mitchell"
	name_63:
		.asciiz "yakko"
	name_64:
		.asciiz "yakkomon"
	.endarea
.close
