#include <pmdsky.h>
#include <cot.h>
#include "extern.h"

static void KillShadow(struct entity* target)
{
  union damage_source sauce = {0x257};
  struct tile* tile = GetTileAtEntity(target);
  target->transparent = true;
  LogMessageWithPopupCheckUser(target, "The shadow vanished...");
  PlayEffectAnimationEntitySimple(target, 520);
  HandleFaint(target, sauce, target);
}

static bool MoveEarthPower(struct entity *user, struct entity *target, struct move *move)
{
  struct monster* user_mon = user->info;
  struct monster* target_mon = target->info;
  switch(GetMainPhase())
  {
    case 0:
      ConstantDamage(user, target, move, ((target_mon->hp) >> 1) - 5);
      TryBlowAway(user, target, (target_mon->action.direction.val + 4) & 7);
      ShouldDisplayUi = false;
      Talk(BWAIX_ID, PORTRAIT_PAIN, FACE_POS_STANDARD, "[TS:0](Agh...[K]that move is so broken...)[C](Maybe I can dodge it, right as he uses it...[K]\nby choosing a direction with [M:B8]...)[TR]", true);
      PlaySoundEffect(5143);
      FadeInOutAll(WHITE_OUT, FLASH_WAIT_TIME, 0);
      WaitFrames(5);
      FadeInOutAll(WHITE_IN, FLASH_WAIT_TIME, 0);
      WaitFrames(10);
      PlaySoundEffect(5143);
      FadeInOutAll(WHITE_OUT, FLASH_WAIT_TIME, 0);
      WaitFrames(5);
      TryPointCameraToMonster(user, 0x0, 0x1);
      FadeInOutAll(WHITE_IN, FLASH_WAIT_TIME, 0);
      WaitFrames(10);
      Talk(MARCUS_ID, PORTRAIT_ANGRY, FACE_POS_BOTTOM_R_FACEINW, "Think outside the box,[W:10] Mozilla Firefox![K]\nDo you seriously think that you could\never even keep up with me?[C]I'll always be four parallel universes ahead!", true);
      TryPointCameraToMonster(target, 0x0, 0x1);
      Talk(BWAIX_ID, PORTRAIT_PAIN, FACE_POS_STANDARD, "[TS:0][VS:1:3](Tch...[VS:1:2][K]he's right...)[C](Gotta...[K][VS:2:3]go...[VR][K][FACE:9]FAST...!)[TR]", true);
      BoostSpeed(user, target, 2, 0x7F, false);
      Talk(BWAIX_ID, PORTRAIT_DETERMINED, FACE_POS_STANDARD, "[TS:0](My only moves are close-ranged...[K]\nI think [CS:M]Hypnosis[CR] might slow him down, but...[K]\nMy best shot is sneaking up right behind him!)[TR]", true);
      NextMainPhase();
      ShouldDisplayUi = true;
      break;
    default:
      ConstantDamage(user, target, move, 4);
  }
  has_used_move[FindMoveIndex(user_mon, move->id.val)] = true;
  return true;
}

static bool MoveBugBuzz(struct entity *user, struct entity *target, struct move *move)
{
  struct monster* user_mon = user->info;
  struct monster* target_mon = target->info;
  ConstantDamage(user, target, move, 4);
  if(!(has_used_move[FindMoveIndex(user_mon, move->id.val)]))
  {
    ShouldDisplayUi = false;
    Talk(BWAIX_ID, PORTRAIT_PAIN, FACE_POS_STANDARD, "[TS:0](And as for THAT[W:10] move...[K]\nJust rolling outta the way won't work...)[C](But if I hold [M:B3], I should be able\nto warp out quickly...!)[TR]", true);
    ShouldDisplayUi = true;
  }
  has_used_move[FindMoveIndex(user_mon, move->id.val)] = true;
  return true;
}

static bool MoveEmber(struct entity *user, struct entity *target, struct move *move)
{
  struct monster* user_mon = user->info;
  struct monster* target_mon = target->info;
  switch(GetMainPhase())
  {
    case 1:
        ConstantDamage(user, target, move, 1);
        NextSubPhase();
        if(GetSubPhase() > 6)
        {
          ShouldDisplayUi = false;
          EndNegativeStatusCondition(target, target, false, false, true);
          Turn2Direction(target, 3, false, target_mon->action.direction.val, ((target_mon->action.direction.val + 4) & 7));
          Talk(MARCUS_ID, PORTRAIT_ANGRY, FACE_POS_BOTTOM_R_FACEINW, "[VS:3]Can you just[W:10][VS:1:2] STAND STILL?![VR]", true);
          PlaySoundEffect(8971);
          JumpAngry(user);
          Talk(BWAIX_ID, PORTRAIT_ANGRY, FACE_POS_STANDARD, "You're one to talk![C]You're...[K][FACE:2]huff...[K][FACE:3][VS:2:3]s-[W:5]so annoying...![VR]", true);
          Talk(MARCUS_ID, PORTRAIT_SPECIAL0, FACE_POS_BOTTOM_R_FACEINW, "Oh, already tiring out?[K][VS:1:2] Pathetic.", true);
          PlaySoundEffect(6925);
          FadeInOutAll(FADE_OUT, 0x1000, 0);
          WaitFrames(30);
          ChangeMonsterSprite(target, SHADOW_ID);
          FadeInOutAll(FADE_IN, 0x500, 0);
          WaitFrames(60);
          DisplayMessage3(NULL, NULL, "Just try and catch me NOW![VR]", true);
          TryWarp(user, target, WARP_RANDOM, NULL);
          NextMainPhase();
          ShouldDisplayUi = true;
        }
      break;
    case 2:
      ConstantDamage(user, target, move, 1);
      NextSubPhase();
      break;
    case 3:
      ConstantDamage(user, target, move, 333);
      if(GetMainPhase() == 3)
        NextSubPhase();
      break;
    case 4:
      if(GetSubPhase() > 0)
        DUNGEON_PTR->end_floor_flag = 1;
      break;
    default:
      DisplayMessage3(NULL, NULL, "[CN]TODO EMBER", true);
  }
  return true;
}

static bool MoveHypnosis(struct entity *user, struct entity *target, struct move *move)
{
  struct monster* user_mon = user->info;
  struct monster* target_mon = target->info;
  if(target_mon->id.val == SHADOW_ID)
  {
    target_mon->is_ally = true;
    LogMessageWithPopupCheckUserTarget(user, target, "[string:0] took control of the shadow!");
    int index = FindMoveIndex(target_mon, MOVE_STRENGTH);
    target_mon->moves[index].f_enabled_for_ai = false;
    target_mon->moves[index].f_sealed = true;
    target_mon->moves[index].f_disabled = true;
    index = FindMoveIndex(target_mon, MOVE_DARK_VOID);
    target_mon->moves[index].f_enabled_for_ai = true;
    target_mon->moves[index].f_sealed = false;
    target_mon->moves[index].f_disabled = false;
  }
  else
  {
    switch(GetMainPhase())
    {
      case 1:
      case 2:
        LowerSpeed(user, target, 4, true);
        break;
      case 3:
        DoMoveSleep(user, target, move, NULL);
        target_mon->statuses.sleep_turns = 1;
        break;
      case 4:
        DoMoveSleep(user, target, move, NULL);
        target_mon->statuses.sleep_turns = 0x7F;
        if(GetSubPhase() == 0)
        {
          struct rgba color_map[256];
          StopMusic();
          PlaySoundEffect(10764);
          FadeInOutAll(FADE_OUT, 0xA00, 0);
          WaitFrames(25);
          for(int i = 0; i < 256; i++)
          {
            color_map[i].r = 0xFF;
            color_map[i].g = 0x0;
            color_map[i].b = 0x0;
            color_map[i].a = 0x0;
          }
          SetColorField(user->field_0xaa, 1);
          SetColorField(target->field_0xaa, 1);
          ChangeDungeonColors(color_map, 2);
          FadeInOutAll(FADE_IN, 0xA00, 0);
          WaitFrames(30);
          NextSubPhase();
        }
        user_mon->statuses.freeze = 2;
        user_mon->statuses.freeze_turns = 0x7F;
        user_mon->statuses.freeze_damage_countdown = 0x0;
        target_mon->statuses.freeze = 2;
        target_mon->statuses.freeze_turns = 0x7F;
        target_mon->statuses.freeze_damage_countdown = 0x0;
        break;
      default:
        DisplayMessage3(NULL, NULL, "[CN]TODO HYPNOSIS", true);
    }
  }
  return true;
}

// Called when using moves. Should return true if a custom effect was applied.
// This function is only called if the move doesn't fail due to a missing target
bool CustomApplyMoveEffect(
    move_effect_input *data, struct entity *user, struct entity *target, struct move *move)
{
  struct monster* target_mon = target->info;
  struct monster* user_mon = user->info;
  if(target_mon->id.val == SHADOW_ID && ((user_mon->id.val == BWAIX_ID) || (user_mon->id.val == MARCUS_ID)) && move->id.val != MOVE_HYPNOSIS)
  {
    data->out_dealt_damage = true;
    KillShadow(target);
    return true;
  }
  switch(data->move_id)
  {
    case MOVE_EARTH_POWER:
      data->out_dealt_damage = MoveEarthPower(user, target, move);
      return true;
    case MOVE_BUG_BUZZ:
      data->out_dealt_damage = MoveBugBuzz(user, target, move);
      return true;
    case MOVE_EMBER:
      data->out_dealt_damage = MoveEmber(user, target, move);
      return true;
    case MOVE_HYPNOSIS:
      data->out_dealt_damage = MoveHypnosis(user, target, move);
      return true;
    case MOVE_DARK_VOID:
      data->out_dealt_damage = DoMoveSleep(user, target, move, NULL);
      if(user_mon->id.val == SHADOW_ID)
        KillShadow(user);
      return true;
    case MOVE_REGULAR_ATTACK:
      if(CanActivateWaryFighter(target, user_mon->action.direction.val))
        TryActivateWaryFighter(target, user_mon->action.direction.val, 1, 301);
      else if(GetMainPhase() < 4)
        DodgeWarp(target);
      else
        LogMessageWithPopupCheckUser(user, "That won't help here.");
      data->out_dealt_damage = false;
      return true;
    default:
      return false;
  }
}
