#include <pmdsky.h>
#include <cot.h>
#include "extern.h"

bool ShouldDisplayUi = false;
uint8_t layout_idx = FACE_POS_STANDARD;
struct spawned_monster_data SHADOW_SPAWN_DATA = { SHADOW_ID, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0 };
bool has_used_move[4] = {false, false, false, false};
struct position earth_power_missed_coords = { 0, 0 };
bool earth_power_missed = false;
struct rgba current_color_map[256];

void PutRecruitable(int member_idx, short species, uint8_t level, uint8_t origin_id)
{
  CopyStuffFromSomewhereToSomewhereElse(member_idx, species, origin_id, 0);
  struct ground_monster* member = GetTeamMember(member_idx);
  SomethingIDK0(member, level, 0);
  SomethingIDK1(member);
}

void SetMentryName(int member_idx, char* name)
{
  struct ground_monster* member = GetTeamMember(member_idx);
  StrncpySimple(member->name, name, 10);
}

int DungeonMagicNumberCheck(short dungeon_id)
{
    if(dungeon_id > 403)
    {
        // ChangeOptions();
        RemoveAllItemsStartingAt(0);
        RemoveActiveMembersFromAllTeams();
        PutRecruitable(0, BWAIX_ID, 24, 216);
        SetMentryName(0, "Bwaix");
        struct ground_monster* member = GetTeamMember(0);
        member->max_hp = 128;
        member->atk = 42;
        member->sp_atk = 255;
        member->def = 42;
        member->sp_def = 128;
        PutRecruitable(1, DUCKY_ID, 1, 0);
        SetMentryName(1, "ducky");
        PutRecruitable(2, MARCUS_ID, 100, 0);
        SetMentryName(2, "Marcus");
        member = GetTeamMember(2);
        member->max_hp = 999;
        member->atk = 255;
        member->sp_atk = 255;
        member->def = 255;
        member->sp_def = 255;
        SetTeamSetupHeroAndPartnerOnly();
        MemcpySimple(&(TEAM_MEMBER_TABLE_PTR->explorer_maze_monsters[0]), member, sizeof(struct ground_monster));
        return CleanScriptParam(dungeon_id);
    }
    else if(dungeon_id != 403)
      CardPullOut();
    return CleanScriptParam(DUNGEON_LITTLE_PLAINS);
}

void CustomInitPortraitBox(struct portrait_box* portrait, int unk)
{
  SetPortraitLayout(portrait, layout_idx);
  SomePortraitFunction(portrait, unk);
}

void CustomDisplayUi()
{
  if(ShouldDisplayUi)
    DisplayUi();
}

struct entity* FindMarcus()
{
  for(int i = 0; i < 0x14; i++)
  {
    struct entity* target = &(DUNGEON_PTR->entity_table.entities[i]);
    if(EntityIsValid(target))
    {
      struct monster* target_monster = target->info;
      if(target_monster->id.val == MARCUS_ID && target_monster->max_hp_stat == 999)
        return target;
    }
  }
  CardPullOut();
  return NULL;
}

bool ShadowExists()
{
  for(int i = 0; i < 0x14; i++)
  {
    struct entity* target = &(DUNGEON_PTR->entity_table.entities[i]);
    if(EntityIsValid(target))
    {
      struct monster* target_monster = target->info;
      if(target_monster->id.val == SHADOW_ID)
        return true;
    }
  }
  return false;
}

void JumpHappy(struct entity* entity)
{
  struct monster* monster = entity->info;
  SetEntityAnimation(entity, 0, monster->action.direction.val);
  FreezeAnim(entity);
  for(int i = 0; i < 10; i++)
  {
    entity->elevation += 0x160;
    if(i & 1)
      AdvanceFrame(0);
  }
  AdvanceFrame(0);
  for(int i = 0; i < 10; i++)
  {
    entity->elevation -= 0x160;
    if(i & 1)
      AdvanceFrame(0);
  }
  UnfreezeAnim(entity);
  SetEntityAnimation(entity, 7, monster->action.direction.val);
}

void MoveTileOffset(struct entity* entity, int offset_tile_count, bool should_animate, bool slow)
{
  if(!(EntityIsValid(entity)))
    return;
  struct monster* monster = entity->info;
  int dir = monster->action.direction.val;
  if(offset_tile_count < 0)
  {
    offset_tile_count *= -1;
    dir = (dir + 4) & 7;
  }
  int offset_tile_x = OFFSETS_XY[dir][0];
  int offset_tile_y = OFFSETS_XY[dir][1];
  if(slow)
  {
    offset_tile_x = offset_tile_x >> 1;
    offset_tile_y = offset_tile_y >> 1;
    offset_tile_count = offset_tile_count << 1;
  }
  SetEntityAnimation(entity, 0, dir);
  for(int i = 0; i < offset_tile_count*12; i++)
  {
    MoveEntityGraphically(entity, offset_tile_x, offset_tile_y);
    if(should_animate)
      AdvanceFrame(0);
  }
  SetEntityAnimation(entity, 7, dir);
}

void CustomIntro()
{
    ChangeDungeonMusic(189);
    SetGameMode(3);
    SetSpecialEpisodeType(2);
    SetBothScreensWindowsColor(2);
    SaveScriptVariableValue(NULL, VAR_DUNGEON_EVENT_LOCAL, 0);
    LoadMonsterSprite(SHADOW_ID, 0);
    struct entity* marcus = FindMarcus();
    struct monster* marcus_mon = marcus->info;
    struct entity* bwaix = GetLeader();
    struct monster* bwaix_mon = bwaix->info;
    struct entity* ducky = NULL;
    MemcpySimple(current_color_map, GetWeatherColorTable(GetApparentWeather(bwaix)), sizeof(current_color_map));
    for(int i = 0; i < 0x14; i++)
    {
      struct entity* target = &(DUNGEON_PTR->entity_table.entities[i]);
      if(EntityIsValid(target))
      {
        struct monster* target_monster = target->info;
        if(target_monster->id.val == DUCKY_ID)
          ducky = target;
      }
    }
    if(!(ducky))
      CardPullOut();
    struct monster* ducky_mon = ducky->info;
    bwaix_mon->display_shadow = false; // A bit of a hacky/simple way to hide the fact that we're in dungeon mode, since the floor is the same color as an enemy's shadow
    ducky_mon->display_shadow = false;
    TryPointCameraToMonster(marcus, 0x0, 0x1);
    SetTextboxAttribute(0x2, 0x2, 0x1C, 0x14, 0x0, 0xFA); 
    DisplayMessage3(NULL, NULL, "[TS:0][TR]", false); // Stops the upper portion of the Touch Screen from being buggy
    ResetTextboxAttribute();
    ToggleAnimLoop(bwaix, ducky, true);
    FadeInOutAll(WHITE_IN, 0x300, 0);
    WaitFrames(180);
    ResetTextColorPalette();
    Talk(MARCUS_ID, PORTRAIT_SPECIAL0, FACE_POS_BOTTOM_R_FACEINW, "[VS:1:2]Well,[W:20] you two really HAVE[W:10] forced my hand.[VR][K][VS:2:3]\nEqually commendable and annoying.[VR][C][FACE:4]Since it will end up killing some time,[W:20]\nand by extension,[W:20] all of us...[K]\n[VS:2:5]I'll fight.[VR][C]As you may be able to tell,[W:20] however...[K]\nThis will be under [FACE:9]MY[W:10] rules.[K] No one else's.", true);
    MoveTileOffset(marcus, 4, true, false);
    Talk(MARCUS_ID, PORTRAIT_SPECIAL0, FACE_POS_BOTTOM_R_FACEINW, "[VS:1:3]Do I make myself clear?[VR]", true);
    Talk(DUCKY_ID, PORTRAIT_PAIN, FACE_POS_STANDARD, "[VS:1:10]...[VS:1:5][K][CS:Y]B[CR]-[W:10][CS:Y]Bwaix[CR]...[C][VS:1:5]Forgive me...[K][VS:1:2]I could have never prepared\nus for something like this...[VR]", true);
    PlaySoundEffect(5143);
    FadeInOutAll(WHITE_OUT, FLASH_WAIT_TIME-0x2000, 0);
    WaitFrames(5);
    TryPointCameraToMonster(bwaix, 0x0, 0x1);
    ToggleAnimLoop(bwaix, ducky, true);
    FadeInOutAll(WHITE_IN, FLASH_WAIT_TIME-0x2000, 0);
    WaitFrames(4);
    Talk(BWAIX_ID, PORTRAIT_SURPRISED, FACE_POS_STANDARD, "W-[W:5]what do you mean?[K] What's going on?[C][FACE:5]Why does everything feel so...[K][FACE:2][VS:1:2]different...?[VR]", true);
    ToggleAnimLoop(bwaix, ducky, true);
    TryPointCameraToMonster(marcus, 0x0, 0x1);
    WaitFrames(10);
    HeadShake(marcus);
    Talk(MARCUS_ID, PORTRAIT_SIGH, FACE_POS_BOTTOM_R_FACEINW, "[VS:1:4]Feh...[VR][K][FACE:4] Allow me to educate you.[K]\nBy making the first move.", true);
    LogMessageWithPopupCheckUser(marcus, "?! ...What did [CS:N]Marcus[CR] do?!");
    SetEntityAnimation(marcus, 11, marcus_mon->action.direction.val);
    PlayEffectAnimationEntitySimple(marcus, 22);
    PlayEffectAnimationEntitySimple(marcus, 543);
    FadeInOutAll(WHITE_OUT, 0x1000, 0);
    WaitFrames(42);
    UnfreezeAnim(ducky);
    SetEntityAnimation(ducky, 6, ducky_mon->action.direction.val);
    PlaySoundEffect(11274);
    FadeInOutAll(WHITE_IN, 0x800, 0);
    ShakeScreen(2);
    ConstantDamage(marcus, ducky, &(marcus_mon->moves[0]), 9999);
    WaitFrames(30);
    if(EntityIsValid(ducky))
      CardPullOut();
    TryPointCameraToMonster(bwaix, 0x0, 0x1);
    PlayEffectAnimationEntitySimple(bwaix, 62);
    Talk(BWAIX_ID, PORTRAIT_SURPRISED, FACE_POS_STANDARD, "[CS:C]d[CR]-[CS:C]ducky[CR]...?![K] No![W:15][FACE:8][VS:1:2] NO...![VR][C][VS:2:5]How...[K]how could you...?[VR]", true);
    TryPointCameraToMonster(marcus, 0x0, 0x1);
    MoveTileOffset(marcus, 2, true, false);
    JumpHappy(marcus);
    Talk(MARCUS_ID, PORTRAIT_WORRIED, FACE_POS_BOTTOM_R_FACEINW, "Physically,[W:10] or emotionally?[K]\nIf it's the latter,[W:20] I really don't\nwant to repeat my entire monologue...", true);
    PlaySoundEffect(8971);
    JumpAngry(bwaix);
    FreezeAnim(bwaix);
    Talk(BWAIX_ID, PORTRAIT_ANGRY, FACE_POS_STANDARD, "[VS:2:1]Don't get smart with me![VR][K] And I already heard\nevery little thing that came out of your mouth!", true);
    WaitFrames(60);
    MoveTileOffset(marcus, 1, true, true);
    WaitFrames(60);
    Talk(MARCUS_ID, PORTRAIT_WORRIED, FACE_POS_BOTTOM_R_FACEINW, "Is that so...?[K] My,[W:10] you're much more\nresistant than I had anticipated...[C]Why,[W:20] then,[W:10] do you wish for this world\nto thrive?[K] You--[W:5]compared to most others--[W:5]\nshould also recognize your role in everything.[C][FACE:5]We both of the same brain cell.[K][VS:1:2] Protagonists.[VR][K]\nVehicles rather than agents of chaos.", true);
    HeadShake(bwaix);
    Talk(BWAIX_ID, PORTRAIT_ANGRY, FACE_POS_STANDARD, "So what?![K] That doesn't mean we can't live\nour lives the way we want to!", true);
    WaitFrames(60);
    HeadShake(marcus);
    Talk(MARCUS_ID, PORTRAIT_WORRIED, FACE_POS_BOTTOM_R_FACEINW, "This is a fundamental misunderstanding.[K]\nWe've never had a choice.[K][FACE:9] It's arguably\na better fate for us to be forgotten.", true);
    Talk(BWAIX_ID, PORTRAIT_SAD, FACE_POS_STANDARD, "[VS:1:3]We...[K]w-[W:5][FACE:2]we...![VR]", true);
    ChangeDungeonMusic(0);
    WaitFrames(90);
    PlaySoundEffect(8975);
    JumpAngry(bwaix);
    FreezeAnim(bwaix);
    Talk(BWAIX_ID, PORTRAIT_DETERMINED, FACE_POS_STANDARD, "We're all going to be forgotten someday.[K]\nYou [FACE:3]CAN'T[W:10] just take away the chance for\nall of us to make the best use of our time...!", true);
    WaitFrames(60);
    HeadShake(marcus);
    WaitFrames(90);
    Turn2Direction(marcus, 10, true, DIR_LEFT, DIR_RIGHT);
    WaitFrames(60);
    Talk(MARCUS_ID, PORTRAIT_DETERMINED, FACE_POS_BOTTOM_R_FACEOUTW, "[VS:2:3]I didn't take anyone's chances away.[VR][K]\nThe otherworldy players did this.[C][FACE:5]So don't assume I feel no fear in my actions.[K]\nBut this is the sole decision I've held in two\nyears that wasn't thrust into my lap.", true);
    MoveTileOffset(marcus, 7, true, true);
    WaitFrames(60);
    Talk(MARCUS_ID, PORTRAIT_WORRIED, FACE_POS_BOTTOM_R_FACEOUTW, "[VS:2:3]With what little time you have left,[W:20][VS:1:2] you're\ngoing to die fighting for the status quo?[VR]", true);
    Turn2Direction(marcus, 4, false, DIR_RIGHT, DIR_LEFT);
    WaitFrames(90);
    PlaySoundEffect(8971);
    JumpAngry(marcus);
    Talk(MARCUS_ID, PORTRAIT_DETERMINED, FACE_POS_BOTTOM_R_FACEINW, "If nothing else,[W:20] I respect this as your choice.[K]\nIsn't freedom wonderful?[C][FACE:3]You now have the right to be wrong!", true);
    PlaySoundEffect(5140);
    FadeInOutAll(WHITE_OUT, FLASH_WAIT_TIME, 0);
    WaitFrames(5);
    FadeInOutAll(WHITE_IN, FLASH_WAIT_TIME, 0);
    WaitFrames(10);
    FadeInOutAll(WHITE_OUT, FLASH_WAIT_TIME, 0);
    WaitFrames(5);
    TryPointCameraToMonster(bwaix, 0x0, 0x1);
    bwaix_mon->display_shadow = true;
    ShouldDisplayUi = true;
    UnfreezeAnim(bwaix);
    ChangeDungeonMusic(16);
    FadeInOutAll(FADE_IN, FLASH_WAIT_TIME, 1);
    FadeInOutAll(WHITE_IN, FLASH_WAIT_TIME, 0);
    WaitFrames(10);
}

void FaceEachOther(struct entity* entity1, struct entity* entity2)
{
  SetEntityDirection(entity1, GetDirectionTowardsPosition(&entity1->pos, &entity2->pos));
  SetEntityDirection(entity2, GetDirectionTowardsPosition(&entity2->pos, &entity1->pos));
}

void SpawnShadows(int amount)
{
  ShouldDisplayUi = false;
  WaitFrames(4);
  struct entity* entity = FindMarcus();
  struct monster* monster = entity->info;
  TryPointCameraToMonster(entity, 0x0, 0x1);
  SetEntityAnimation(entity, 11, monster->action.direction.val);
  LogMessageWithPopupCheckUser(entity, "?! ...What did [CS:N]Marcus[CR] do?!");
  WaitFrames(10);
  PlayEffectAnimationEntitySimple(entity, 22);
  PlaySoundEffect(9477);
  FadeInOutAll(FADE_OUT, 0x1000, 0);
  WaitFrames(60);
  for(int i = 0; i < amount; i++)
  {
    GenerateRandomPositions(&(SHADOW_SPAWN_DATA.pos));
    entity = SpawnMonster(&SHADOW_SPAWN_DATA, true);
    monster = entity->info;
    InitMove(&(monster->moves[0]), MOVE_STRENGTH);
    InitMove(&(monster->moves[1]), MOVE_DARK_VOID);
    monster->moves[1].f_enabled_for_ai = false;
    monster->moves[1].f_sealed = true;
    monster->moves[1].f_disabled = true;
  }
  TryPointCameraToMonster(GetLeader(), 0x0, 0x1);
  FadeInOutAll(FADE_IN, 0x2000, 0);
  ShouldDisplayUi = true;
  LogMessageQuiet(GetLeader(), "Could they somehow be controlled...?");
  WaitFrames(60);
}

bool CustomMoveHitCheck(struct entity* attacker, struct entity* defender, struct move* move, bool use_second_accuracy, bool never_miss_self)
{
  struct entity* marcus = FindMarcus();
  struct entity* bwaix = GetLeader();
  struct monster* bwaix_mon = bwaix->info;
  struct monster* marcus_mon = marcus->info;
  int move_id = move->id.val;
  earth_power_missed = false;
  if(marcus == attacker && bwaix == defender && move_id != MOVE_REGULAR_ATTACK && (has_used_move[FindMoveIndex(marcus_mon, move->id.val)]))
  {
    struct button_struct held_buttons;
    // struct button_struct pressed_buttons;
    // GetPressedButtons(0, &pressed_buttons);
    switch(move->id.val)
    {
      case MOVE_EARTH_POWER:
        for(int i = 0; i < 30; i++)
        {
          GetHeldButtons(0, &held_buttons);
          held_buttons.bitfield &= 0b11110000;
          if(held_buttons.bitfield != 0)
            break;
          AdvanceFrame(0);
        }
        if(held_buttons.bitfield != 0)
        {
          // Check the tile based on inputs, and if we can jump to it, then dodge the attack!
          uint8_t direction;
          switch(held_buttons.bitfield) // This is stupid and an array would probably be better, but whatever
          {
            case 0x80:
              direction = 0; // Down
              break;
            case 0x90:
              direction = 1; // Down Left
              break;
            case 0x10:
              direction = 2; // Left
              break;
            case 0x50:
              direction = 3; // Up Left
              break;
            case 0x40:
              direction = 4; // Up
              break;
            case 0x60:
              direction = 5; // Up Right
              break;
            case 0x20:
              direction = 6; // Right
              break;
            case 0xA0:
            default:
              direction = 7; // Down Right
          }
          if(CanActivateWaryFighter(bwaix, direction))
          {
            earth_power_missed_coords.x = bwaix->pos.x;
            earth_power_missed_coords.y = bwaix->pos.y;
            earth_power_missed = true;
            TryActivateWaryFighter(bwaix, direction, 1, 301);
            return false;
          }
        }
        break;
      case MOVE_BUG_BUZZ:
        for(int i = 0; i < 30; i++)
        {
          GetHeldButtons(0, &held_buttons);
          if(held_buttons.bitfield & 0x2)
            break;
          AdvanceFrame(0);
        }
        if(held_buttons.bitfield & 0x2) // B
        {
          DodgeWarp(bwaix);
          return false;
        }
        break;
      case MOVE_DRAGON_PULSE:
        break;
      default:
        CardPullOut();
    }
  }
  else if(bwaix == attacker && marcus == defender)
  {
    if(GetMainPhase() < 4)
    {
      if(move->id.val == MOVE_EMBER)
      {
        if(bwaix_mon->action.direction.val == marcus_mon->action.direction.val)
          return true;
        else
        {
          DodgeWarp(marcus);
          return false;
        }
      }
    }
    else
    {
      if(GetSubPhase() >= 1)
      {
        return true;
      }
      else if(move->id.val == MOVE_EMBER)
      {
        Turn2Direction(marcus, 4, true, marcus_mon->action.direction.val, GetDirectionTowardsPosition(&marcus->pos, &bwaix->pos));
        Talk(MARCUS_ID, PORTRAIT_PAIN, FACE_POS_BOTTOM_R_FACEINW, "[VS:1:4]No,[W:10] n-[W:5]no...[K]I'm not done...[C]So long as my eyes are open...[K]\nSo long as I draw breath...[K]I'm NOT done...[VR]", true);
        DodgeWarp(marcus);
        return false;
      }
    }
  }
  return true;
}

void CustomPlayMoveAnimation(struct entity* user, struct entity* target, struct move* move, struct position* position)
{
  struct entity* bwaix = GetLeader();
  if(target == bwaix && earth_power_missed)
    PlayEffectAnimationPos(&earth_power_missed_coords, 528, true);
  else
    PlayMoveAnimation(user, target, move, position);
}

void CustomEndSleepClassStatus(struct entity* user, struct entity* target)
{
  if(!(GetMainPhase() >= 4 && GetSubPhase() >= 1))
    EndSleepClassStatus(user, target);
}

void CustomFadeToBlack()
{
  if(GetMainPhase() >= 4 && GetSubPhase() >= 1)
  {
    FadeInOutAll(FADE_OUT, FLASH_WAIT_TIME, 1);
    FadeInOutAll(FADE_OUT, FLASH_WAIT_TIME, 0);
    WaitFrames(120);
  }
  else
    FadeToBlack();
}

void CustomRunLeaderTurn(undefined param_1)
{
  struct entity* bwaix = GetLeader();
  struct entity* marcus = FindMarcus();
  struct monster* bwaix_mon = bwaix->info;
  struct monster* marcus_mon = marcus->info;
  if(GetMainPhase() == 2 && GetSubPhase() > 4)
  {
    if(MonsterHasNegativeStatus(bwaix, false))
      EndNegativeStatusCondition(bwaix, bwaix, false, false, true);
    ShouldDisplayUi = false;
    FaceEachOther(bwaix, marcus);
    HeadShake(bwaix);
    FreezeAnim(bwaix);
    ChangeDungeonMusic(0);
    WaitFrames(60);
    JumpHappy(bwaix);
    FreezeAnim(bwaix);
    Talk(BWAIX_ID, PORTRAIT_SAD, FACE_POS_STANDARD, "[VS:1:2]Heh...[K][FACE:2]hehe...[K][FACE:1][VS:1:3]hahahahaha...[VR]", true);
    TryPointCameraToMonster(marcus, 0x0, 0x1);
    ChangeMonsterSprite(marcus, MARCUS_ID);
    if(MonsterHasNegativeStatus(marcus, false))
      EndNegativeStatusCondition(marcus, marcus, false, false, true);
    PlayColorChangeAnimation(marcus);
    Talk(MARCUS_ID, PORTRAIT_STUNNED, FACE_POS_BOTTOM_R_FACEINW, "Hm,[W:10] HMM?[K] Something you wanna share?", true);
    TryPointCameraToMonster(bwaix, 0x0, 0x1);
    FreezeAnim(bwaix);
    Talk(BWAIX_ID, PORTRAIT_HAPPY, FACE_POS_STANDARD, "[VS:1:2]It's so funny...[VR][K]all that bravado you had...[K]\nHow threatened I felt just standing near you...", true);
    PlaySoundEffect(5143);
    FadeInOutAll(WHITE_OUT, FLASH_WAIT_TIME, 0);
    WaitFrames(5);
    FadeInOutAll(WHITE_IN, FLASH_WAIT_TIME, 0);
    WaitFrames(25);
    PlaySoundEffect(8971);
    JumpAngry(bwaix);
    FreezeAnim(bwaix);
    Talk(BWAIX_ID, PORTRAIT_ANGRY, FACE_POS_STANDARD, "I was so [VS:1:3]STUPID![VR][K] Thinking I had any reason\nto be scared of YOU![C]All you've done this entire time is hide\nbehind your own shadows--[W:10]LITERALLY![K]\nCould you GET any more cowardly?!", true);
    HeadShake(bwaix);
    FreezeAnim(bwaix);
    Talk(BWAIX_ID, PORTRAIT_DETERMINED, FACE_POS_STANDARD, "I KNOW[W:10] you have the power worth fearing.[K]\nIt's the reason I'm standing here.[C]So [FACE:3]WHAT[W:10][VS:1:2] are you afraid of?![VR]", true);
    WaitFrames(60);
    union damage_source sauce = {0x257};
    for(int i = 0; i < 0x14; i++)
    {
      struct entity* target = &(DUNGEON_PTR->entity_table.entities[i]);
      if(EntityIsValid(target))
      {
        struct monster* target_monster = target->info;
        if(target_monster->id.val == SHADOW_ID)
        {
          TryPointCameraToMonster(target, 0x0, 0x1);
          struct tile* tile = GetTileAtEntity(target);
          target->transparent = true;
          PlayEffectAnimationEntitySimple(target, 520);
          HandleFaint(target, sauce, target);
        }
      }
    }
    PlaySoundEffect(5140);
    FadeInOutAll(WHITE_OUT, FLASH_WAIT_TIME, 0);
    WaitFrames(5);
    FadeInOutAll(WHITE_IN, FLASH_WAIT_TIME, 0);
    WaitFrames(10);
    FadeInOutAll(WHITE_OUT, FLASH_WAIT_TIME, 0);
    WaitFrames(5);
    int direction = bwaix_mon->action.direction.val;
    if(!(AreEntitiesAdjacent(bwaix, marcus)))
    {
      if(CanActivateWaryFighter(bwaix, direction))
        MoveMonsterToPos(marcus, bwaix->pos.x + DIRECTIONS_XY[direction][0], bwaix->pos.y + DIRECTIONS_XY[direction][1], 1);
      else
      {
        for(int i = 0; i < 8; i++)
        {
          if(CanActivateWaryFighter(bwaix, i))
          {
            MoveMonsterToPos(marcus, bwaix->pos.x + DIRECTIONS_XY[i][0], bwaix->pos.y + DIRECTIONS_XY[i][1], 1);
            break;
          }
        }
      }
      UpdateEntityPixelPos(marcus, 0);
    }
    FaceEachOther(bwaix, marcus);
    for(int i = 0; i < 256; i++)
    {
      current_color_map[i].r = 0xFF - current_color_map[i].r;
      current_color_map[i].g = 0xFF - current_color_map[i].g;
      current_color_map[i].b = 0xFF - current_color_map[i].b;
    }
    TryPointCameraToMonster(marcus, 0x0, 0x1);
    ChangeDungeonColors(current_color_map, 2);
    PlaySoundEffect(9992);
    FadeInOutAll(WHITE_IN, 0x300, 0);
    ShakeScreen(3);
    WaitFrames(60);
    HeadShake(marcus);
    Talk(MARCUS_ID, PORTRAIT_SPECIAL0, FACE_POS_BOTTOM_R_FACEINW, "[VS:1:3]Nothing,[W:20] save for two eyes boring into my soul.[VR]", true);
    SubstitutePlaceholderStringTags(0, bwaix, 0);
    SubstitutePlaceholderStringTags(1, marcus, 0);
    SetEntityAnimation(marcus, 9, marcus_mon->action.direction.val);
    LogMessageWithPopupCheckUser(marcus, "[string:1] has the power of [CS:H]Anime[CR] on his side!");
    PlayEffectAnimationEntitySimple(marcus, 80);
    BoostSpeed(bwaix, marcus, 4, 0x7F, true);
    LowerSpeed(marcus, bwaix, 0x7F, true);
    for(int i = 0; i < 5; i++)
      bwaix_mon->statuses.speed_down_counters[i] = 0x7F;
    marcus_mon->moves[FindMoveIndex(marcus_mon, MOVE_EARTH_POWER)].f_subsequent_in_link_chain = true;
    LogMessageWithPopupCheckUser(marcus, "[string:1] linked his moves!");
    PlayEffectAnimationEntitySimple(marcus, 360);
    WaitFrames(80);
    TryPointCameraToMonster(bwaix, 0x0, 0x1);
    JumpHappy(bwaix);
    FreezeAnim(bwaix);
    Talk(BWAIX_ID, PORTRAIT_SPECIAL1, FACE_POS_STANDARD, "[VS:1:4]That makes two of us.[VR]", true);
    SetEntityAnimation(bwaix, 11, bwaix_mon->action.direction.val);
    LogMessageWithPopupCheckUser(bwaix, "[string:0] has the power of [CS:N]God[CR] on her side!");
    PlayEffectAnimationEntitySimple(bwaix, 6);
    bwaix_mon->moves[FindMoveIndex(bwaix_mon, MOVE_EMBER)].ginseng = 255;
    LogMessageWithPopupCheckUser(bwaix, "[string:0]'s [CS:M]Ember[CR] grew stronger!");
    PlayEffectAnimationEntitySimple(bwaix, 0x1A9);
    bwaix_mon->moves[FindMoveIndex(bwaix_mon, MOVE_HYPNOSIS)].ginseng = 255;
    LogMessageWithPopupCheckUser(bwaix, "[string:0]'s [CS:M]Hypnosis[CR] grew stronger!");
    PlayEffectAnimationEntitySimple(bwaix, 0x192);
    UnfreezeAnim(bwaix);
    WaitFrames(30);
    HeadShake(marcus);
    WaitFrames(15);
    UpdateEntityPixelPos(marcus, 0);
    Talk(MARCUS_ID, PORTRAIT_WORRIED, FACE_POS_BOTTOM_R_FACEINW, "[VS:1:2]Invoking the power of [CS:N]God[CR]...?[VR][K]\nAh,[W:10] yes,[W:10] you are acquainted...[K]they DID give\nyou the [CS:K]Glaceon[CR] that ended up killing everyone.[C]But are we not beyond gods,[W:20] at this point?[K]\nAnd what has [CS:N]God[CR] done that [CS:H]Anime[CR] hasn't?", true);
    Talk(BWAIX_ID, PORTRAIT_SPECIAL2, FACE_POS_STANDARD, "[VS:1:2]Let's find out,[W:20] shall we?[VR]", true);
    ChangeDungeonMusic(189);
    ShouldDisplayUi = true;
    NextMainPhase();
  }
  RunLeaderTurn(param_1);
}

int CustomFaintCheck(struct entity* entity, struct monster* monster, int damage)
{
  struct rgba color_map[256];
  if(monster->hp-damage > 0)
    return damage;
  if(monster->is_team_leader)
  {
    // Game Over
    for(int i = 0; i < 256; i++)
    {
      if(i & 1)
        color_map[i].r = 0x0;
      else
        color_map[i].r = 0xFF;
      color_map[i].g = 0x0;
      color_map[i].b = 0x0;
      color_map[i].a = 0x0;
    }
    ShouldDisplayUi = false;
    FreezeAnim(entity);
    ChangeDungeonMusic(189);
    WaitFrames(20);
    SetColorField(entity->field_0xaa, 1); 
    ChangeDungeonMusic(0);
    ChangeDungeonColors(color_map, 6);
    layout_idx = FACE_POS_STANDARD;
    struct portrait_box portrait_box;
    InitDungeonPortrait(&portrait_box, BWAIX_ID, PORTRAIT_PAIN);
    if(YesNoMenu(&portrait_box, 302, 0, NULL) != 1)
    {
      StopMusic();
      MemZero(color_map, sizeof(color_map));
      ChangeDungeonColors(color_map, 2);
      SetTextboxAttribute(0x2, 0x4, 0x1C, 0x5, 0x0, 0xFA);
      DisplayMessage3(NULL, NULL, "[TS:0][FT:1][CN][VS:1:10]AND SO CHAOS CLAIMED\n[CN]ITS FINAL VICTIM", true);
      FadeInOutAll(FADE_OUT, 0x400, 1);
      FadeInOutAll(FADE_OUT, 0x400, 0);
      WaitFrames(120);
      CardPullOut();
    }
    ChangeDungeonMusic(0);
    monster->hp = 32;
    entity->transparent = false;
    JumpAngry(entity);
    ChangeDungeonColors(current_color_map, 4); // Restores the screen's colors
    if(GetMainPhase() < 3)
      ChangeDungeonMusic(16);
    else
      ChangeDungeonMusic(189);
    SetColorField(entity->field_0xaa, 0);
    UnfreezeAnim(entity);
    ShouldDisplayUi = true;
    int sub_phase = GetSubPhase() - 1;
    if(sub_phase < 0)
      sub_phase = 0;
    SaveScriptVariableValue(NULL, VAR_EVENT_LOCAL, sub_phase); // Restart from previous Sub Phase
  }
  else if(monster->id.val == MARCUS_ID && monster->max_hp_stat == 999)
  {
    switch(GetMainPhase())
    {
      case 3:
        ShouldDisplayUi = false;
        SetEntityAnimation(entity, 6, monster->action.direction.val);
        FreezeAnim(entity);
        monster->hp = 1;
        PlaySoundEffect(10764);
        FadeInOutAll(FADE_OUT, 0xB00, 0);
        WaitFrames(25);
        TryPointCameraToMonster(entity, 0x0, 0x1);
        SetEntityAnimation(entity, 6, monster->action.direction.val);
        FreezeAnim(entity);
        FadeInOutAll(FADE_IN, 0xB00, 0);
        WaitFrames(60);
        Talk(MARCUS_ID, PORTRAIT_PAIN, FACE_POS_BOTTOM_R_FACEINW, "[VS:1:2]It's...[K]not enough...[VS:1:3][K]YOU'RE[W:15] n-[W:5]not enough...![C][VS:1:2]You're not enough...[VS:2:3][K]NEVER[W:10] enough...![VR]", true);
        TryInflictTerrifiedStatus(entity, entity);
        monster->statuses.terrified_turns = 0x7F;
        FadeInOutAll(FADE_OUT, 0xB00, 0);
        WaitFrames(25);
        UnfreezeAnim(entity);
        TryPointCameraToMonster(GetLeader(), 0x0, 0x1);
        FadeInOutAll(FADE_IN, 0xB00, 0);
        WaitFrames(25);
        NextMainPhase();
        break;
      case 4:
        break;
      default:
        StopMusic();
        PlaySoundEffect(5140);
        FadeInOutAll(WHITE_OUT, FLASH_WAIT_TIME, 0);
        WaitFrames(5);
        FadeInOutAll(WHITE_IN, FLASH_WAIT_TIME, 0);
        WaitFrames(10);
        FadeInOutAll(WHITE_OUT, FLASH_WAIT_TIME, 0);
        WaitFrames(5);
        TryPointCameraToMonster(entity, 0x0, 0x1);
        entity->transparent = false;
        ShouldDisplayUi = false;
        MemZero(color_map, sizeof(color_map));
        SetColorField(entity->field_0xaa, 0);
        FadeInOutAll(WHITE_IN, FLASH_WAIT_TIME, 0);
        SetEntityAnimation(entity, 7, monster->action.direction.val);
        SetEntityDirection(entity, DIR_DOWN);
        WaitFrames(20);
        HeadShake(entity);
        ChangeDungeonColors(color_map, 8);
        WaitFrames(30);
        SetTextboxAttribute(0x2, 0x4, 0x1C, 0x5, 0x0, 0xFA);
        DisplayMessage3(NULL, NULL, "[CN][VS:1:8]You think you are above MY[W:20] rules?", true);
        SetEntityAnimation(entity, 11, monster->action.direction.val);
        LogMessageWithPopupCheckUser(entity, "?! ...What did [CS:N]Marcus[CR] do?!");
        PlayEffectAnimationEntitySimple(entity, 22);
        CardPullOut();
    }
  }
  else
    return damage;
  return 0;
}

int CustomSetMoveNbStrikes(struct move* move)
{
  if(move->id.val == MOVE_EARTH_POWER && GetMainPhase() == 3)
    return (GetSubPhase()+1) << 1;
  else
    return SetMoveNbStrikes(move);
}

void SetMonsterUseMove(struct entity* entity, struct monster* monster, int move_id, int direction)
{
  if(monster->statuses.burn == 4 || monster->statuses.sleep != 0)
    SetMonsterActionFields(&(monster->action), 0x1);
  else
  {
    SetActionUseMoveAi(&monster->action, FindMoveIndex(monster, move_id), direction);
    SetEntityDirection(entity, direction);
  }
}

void CustomRunMonsterAi(struct entity* entity, undefined param_2)
{
  if(!IsMonster(entity))
    return RunMonsterAi(entity, param_2);
  struct entity* bwaix = GetLeader();
  struct monster* bwaix_mon = bwaix->info;
  struct monster* monster = entity->info;
  if(!(monster->id.val == MARCUS_ID && monster->max_hp_stat == 999) || GetMainPhase() >= 4)
    return RunMonsterAi(entity, param_2);
  ClearMonsterActionFields(&monster->action);
  if(HasStatusThatPreventsActing(entity))
    return;
  int marcus_direction = GetDirectionTowardsPosition(&entity->pos, &bwaix->pos);
  int bwaix_direction = GetDirectionTowardsPosition(&bwaix->pos, &entity->pos);
  int sub_phase;
  switch(GetMainPhase())
  {
    case 0: // Intro
      SetMonsterActionFields(&(monster->action), 0x1);
      if(GetChebyshevDistance(&(bwaix->pos), &(entity->pos)) <= 2)
      {
        ShouldDisplayUi = false;
        TryPointCameraToMonster(entity, 0x0, 0x1);
        FaceEachOther(bwaix, entity);
        FreezeAnim(bwaix);
        Talk(MARCUS_ID, PORTRAIT_SPECIAL0, FACE_POS_BOTTOM_R_FACEINW, "Oh?[W:20] You're approaching me?[C]Instead of running away,[W:20]\nyou're coming right toward me?", true);
        TryPointCameraToMonster(bwaix, 0x0, 0x1);
        FaceEachOther(bwaix, entity);
        Talk(BWAIX_ID, PORTRAIT_ANGRY, FACE_POS_STANDARD, "I can't beat the shit out of you\nwithout getting closer.", true);
        UnfreezeAnim(bwaix);
        SetActionUseMoveAi(&monster->action, FindMoveIndex(monster, MOVE_EARTH_POWER), marcus_direction);
        ShouldDisplayUi = true;
      }
      else
        SetMonsterActionFields(&(monster->action), 0x1);
      break;
    case 1: // Must attack Marcus from behind
      if(AreEntitiesAdjacent(bwaix, entity))
        SetMonsterUseMove(entity, monster, MOVE_BUG_BUZZ, marcus_direction);
      else
      {
        sub_phase = GetSubPhase();
        if(sub_phase >= 4)
        {
          if(!(ShadowExists()))
            SpawnShadows(2);
          if(sub_phase >= 6)
            SetMonsterUseMove(entity, monster, MOVE_EARTH_POWER, marcus_direction);
          else
            SetMonsterActionFields(&(monster->action), 0x1);
        }
        else
        {
          SetActionPassTurnOrWalk(&monster->action, MARCUS_ID);
          monster->target_pos.x = bwaix->pos.x;
          monster->target_pos.y = bwaix->pos.y;
        }
      }
      break;
    case 2: // Marcus camoflauged as a shadow--still attack from behind
      if(AreEntitiesAdjacent(bwaix, entity))
      {
        SetEntityAnimation(entity, 11, monster->action.direction.val);
        LogMessageWithPopupCheckUser(entity, "?! ...What did [CS:N]Marcus[CR] do?!");
        PlayEffectAnimationEntitySimple(entity, 22);
        PlayEffectAnimationEntitySimple(bwaix, 520);
        TryInflictBlinkerStatus(entity, bwaix, false, true);
        bwaix_mon->statuses.blinded_turns = 1;
        SetMonsterUseMove(entity, monster, MOVE_EARTH_POWER, marcus_direction);
      }
      else
      {
        sub_phase = GetSubPhase();
        if(!(ShadowExists()))
        {
          if(sub_phase > 3)
            SpawnShadows(3);
          else
            SpawnShadows(2);
        }
        if(sub_phase > 3)
        {
          SetActionPassTurnOrWalk(&monster->action, MARCUS_ID);
          monster->target_pos.x = bwaix->pos.x;
          monster->target_pos.y = bwaix->pos.y;
        }
        else
          SetMonsterUseMove(entity, monster, MOVE_EARTH_POWER, marcus_direction);
      }
      break;
    case 3: // Marcus speedster
      if(AreEntitiesAdjacent(bwaix, entity))
      {
        SetActionUseMoveAi(&monster->action, FindMoveIndex(monster, MOVE_BUG_BUZZ), marcus_direction);
      }
      else
      {
        SetActionPassTurnOrWalk(&monster->action, MARCUS_ID);
        monster->target_pos.x = bwaix->pos.x;
        monster->target_pos.y = bwaix->pos.y;
      }
      break;
    default:
      DisplayMessage3(NULL, NULL, "[CN]TODO MARCUS AI", true);
  }
}

void NextTurn()
{
  FindMarcus();
}


// Same as the original function
static int GetColorCodePaletteOffsetOriginal(int index) 
{
  switch(index) {
    case 'A':
      return 0x26;
    case 'B':
      return 0x23;
    case 'C':
      return 0x19;
    case 'E':
      return 0x18;
    case 'F':
      return 0x1d;
    case 'G':
      return 0x29;
    case 'H':
      return 0x2c;
    case 'I':
      return 0x26;
    case 'J':
      return 0x2d;
    case 'K':
      return 0x1f;
    case 'L':
      return 0x2b;
    case 'M':
      return 0x20;
    case 'N':
      return 0x1e;
    case 'O':
      return 0x2e;
    case 'P':
      return 0x21;
    case 'Q':
      return 0x25;
    case 'R':
      return 0x2a;
    case 'S':
      return 0x24;
    case 'T':
      return 0;
    case 'U':
      return 0x27;
    case 'V':
      return 0x22;
    case 'W':
      return 0x1a;
    case 'X':
      return 0x1b;
    case 'Y':
      return 0x1c;
    case 'Z':
      return 0x28;
    case 0x6a:
      return 0x21;
    case 0x72:
      return 0x15;
  }
  return 0x17;
}

// Shoutout to Techticks and Irdkwia for this cursed knowledge
static int GetColorCodePaletteOffsetGrayscale(uint8_t index)
{

  #define DARK_GRAY 0x83
  #define GRAY 0x84
  #define LIGHT_GRAY 0x85

  switch (index) {
    case 'A':
    case 'C':
    case 'F':
    case 'K':
    case 'L':
    case 'M':
    case 'J':
    case 'R':
    case 'X':
      return LIGHT_GRAY;
    case 'B':
    case 'P':
    case 'Q':
    case 'S':
      return DARK_GRAY;
    case 'E':
    case 'G':
    case 'H':
    case 'I':
    case 'N':
    case 'O':
    case 'Y':
    case 'Z':
      return GRAY;
    case 'T':
      return 0;
  }
  return 0x17; // White
}

int CustomGetColorCodePaletteOffset(int index) 
{
  if(LoadScriptVariableValueAtIndex(NULL, VAR_PERFORMANCE_PROGRESS_LIST, 62))
    return GetColorCodePaletteOffsetGrayscale(index);
  return GetColorCodePaletteOffsetOriginal(index);
}
