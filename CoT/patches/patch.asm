.nds
.include "symbols.asm"

.open "arm9.bin", arm9_start
    .org GetColorCodePaletteOffset
    .area 0x4
        b CustomGetColorCodePaletteOffset
    .endarea
.close

.open "overlay11.bin", overlay11_start
    .org ReloadPaletteCallOv11
    .area 0x4
        bl OverrideReloadPalette
    .endarea

    .org CleanEnterDungeonParam1
    .area 0x4
        bl DungeonMagicNumberCheck
    .endarea
.close

.open "overlay29.bin", overlay29_start
    .org RunDungeon
    .area 0xC
        push r3-r11,r14 // Reverting the RunDungeon intentional crash!
        sub r13,r13,#0xD0
        mov r10,r0
    .endarea

    .org DisplayUiCallsite1
    .area 0x4
        nop
    .endarea

    .org DisplayUiCallsite2
    .area 0x4
        bl CustomDisplayUi
    .endarea

    .org StartDungeonFadeIn
    .area 0x2C
        bl CustomIntro
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
    .endarea

    .org SomePortraitCall
    .area 0x4
        bl CustomInitPortraitBox
    .endarea

    .org RunMonsterAiCallsite1
    .area 0x4
        bl CustomRunMonsterAi
    .endarea

    .org RunMonsterAiCallsite2
    .area 0x4
        bl CustomRunMonsterAi
    .endarea

    .org RunMonsterAiCallsite3
    .area 0x4
        bl CustomRunMonsterAi
    .endarea

    .org RunMonsterAiCallsite4
    .area 0x4
        bl CustomRunMonsterAi
    .endarea

    .org RunMonsterAiCallsite5
    .area 0x4
        bl CustomRunMonsterAi
    .endarea

    .org DecrementWindCounterCallsite
    .area 0x4
        bl NextTurn
    .endarea

    .org AreTileJumpsAllowed
    .area 0x8
        mov r0,#1
        bx r14
    .endarea

    .org MoveHitCheck
    .area 0xC
        push r14
        bl CustomMoveHitCheck
        pop r15
    .endarea

    .org HurlDamageCallsite1
    .area 0x4
        nop
    .endarea

    .org HurlDamageCallsite2
    .area 0x4
        nop
    .endarea

    .org UpdateMovePp
    .area 0x4
        bx r14
    .endarea

    .org PlayMoveAnimationCallsite1
    .area 0x4
        bl CustomPlayMoveAnimation
    .endarea

    .org PlayMoveAnimationCallsite2
    .area 0x4
        bl CustomPlayMoveAnimation
    .endarea

    .org ApplyDamageBeforeFaintCheck
    .area 0x40
        mov r0,r7
        mov r1,r4
        ldr r2,[r6,#0x0]
        bl CustomFaintCheck
        str r0,[r6,#0x0]
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
        nop
    .endarea

    .org SetMoveNbStrikesCallsite
    .area 0x4
        bl CustomSetMoveNbStrikes
    .endarea

    .org RunLeaderTurnCallsite
    .area 0x4
        bl CustomRunLeaderTurn
    .endarea

    .org EndSleepClassStatusCallsite1
    .area 0x4
        bl CustomEndSleepClassStatus
    .endarea

    .org EndSleepClassStatusCallsite2
    .area 0x4
        bl CustomEndSleepClassStatus
    .endarea

    .org EndSleepClassStatusCallsite3
    .area 0x4
        bl CustomEndSleepClassStatus
    .endarea

    .org EndSleepClassStatusCallsite4
    .area 0x4
        bl CustomEndSleepClassStatus
    .endarea

    .org EndSleepClassStatusCallsite5
    .area 0x4
        bl CustomEndSleepClassStatus
    .endarea

    .org FadeToBlackCallsite1
    .area 0x4
        bl CustomFadeToBlack
    .endarea

    .org FadeToBlackCallsite2
    .area 0x4
        bl CustomFadeToBlack
    .endarea

.close


.open "overlay31.bin", overlay31_start
    .org DungeonMenuYWidth
    .area 0x1
        .byte 0x7
    .endarea
.close
