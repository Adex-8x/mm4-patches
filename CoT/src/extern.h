#pragma once

#include <pmdsky.h>
#include <cot.h>

// 0 = Down; proceed counter-clockwise...
static const int OFFSETS_XY[8][2] = { {0x0, 0x200}, {0x200, 0x200}, {0x200, 0x0}, {0x200, 0xFFFFFE00}, {0x0, 0xFFFFFE00}, {0xFFFFFE00, 0xFFFFFE00}, {0xFFFFFE00, 0x0}, {0xFFFFFE00, 0x200} };

extern bool ShouldDisplayUi;
extern uint8_t layout_idx;
extern struct spawned_monster_data shadow_spawn_data;
extern bool has_used_move[4];

int CleanScriptParam(int dungeon_id);
void FadeInOutAll(int fade_type, int time, bool screen);
void DisplayMessage3(undefined4* param1, struct portrait_box* portrait, const char* message, bool flag);
void ResetTextColorPalette();
void se_Play(int se_id, int volume, int idk);
void MoveEntityGraphically(struct entity* entity, int offset_x, int offset_y);
void SetEntityAnimation(struct entity* entity, int anim_id, int direction);
void CopyStuffFromSomewhereToSomewhereElse(int member_idx, short species, uint8_t origin_id, undefined4 unk);
void SomethingIDK0(struct ground_monster* member, uint8_t level, undefined4 unk);
void SomethingIDK1(struct ground_monster* member);
void RemoveActiveMembersFromAllTeams();
void InitDungeonPortrait(struct portrait_box*, int species_id, int face_id);
void SetGameMode(uint8_t game_mode);
void SetSpecialEpisodeType(uint8_t spep_type);
void SomePortraitFunction(struct portrait_box*, int unk);
void PlayEffectAnimationEntitySimple(struct entity* entity, int effect_id);
void ShakeScreen(int intensity);
void ToggleAnimLoop(struct entity* user, struct entity* target, bool no_loop);
void FreezeAnim(struct entity* entity);
void UnfreezeAnim(struct entity* entity);
void GenerateRandomPositions(struct position* pos);
void TryActivateWaryFighter(struct entity* entity, int direction, int unk, int text_string_id);
void PlayColorChangeAnimation(struct entity* entity);
void StopMusic();
void ChangeDungeonColors(struct rgba* colors, int duration);
void SetColorField(undefined field, int value);
int SetMoveNbStrikes(struct move* move);
void SetEntityDirection(struct entity* entity, int direction);

struct button_struct {
  int16_t bitfield;
  int16_t unk;
};

// Layouts for portraits
enum portrait_layout_types {
    FACE_POS_STANDARD = 0,
    FACE_POS_ABSCOORD = 1,
    FACE_POS_ABSCOORDFACEL = 2,
    FACE_POS_ABSCOORDFACER = 3,
    FACE_POS_BOTTOM_C_FACER = 4,
    FACE_POS_BOTTOM_L_FACEINW = 5,
    FACE_POS_BOTTOM_R_FACEINW = 6,
    FACE_POS_BOTTOM_L_CENTER = 7,
    FACE_POS_BOTTOM_R_CENTER = 8,
    FACE_POS_BOTTOM_C_FACEL = 9,
    FACE_POS_BOTTOM_L_FACEOUTW = 10,
    FACE_POS_BOTTOM_R_FACEOUTW = 11,
    FACE_POS_BOTTOM_LC_FACEOUTW = 12,
    FACE_POS_BOTTOM_RC_FACEOUTW = 13,
    FACE_POS_TOP_C_FACER = 14,
    FACE_POS_TOP_L_FACEINW = 15,
    FACE_POS_TOP_R_FACEINW = 16,
    FACE_POS_TOP_L_CENTER = 17,
    FACE_POS_TOP_R_CENTER = 18,
    FACE_POS_TOP_C_FACEL = 19,
    FACE_POS_TOP_L_FACEOUTW = 20,
    FACE_POS_TOP_RC_FACER = 21,
    FACE_POS_TOP_LC_FACEOUTW = 22,
    FACE_POS_TOP_RC_FACEOUTW = 23,
};

#define FADE_IN 1
#define FADE_OUT 2
#define WHITE_IN 4
#define WHITE_OUT 5
#define FLASH_WAIT_TIME 0xA000
#define BWAIX_ID 1232
#define MARCUS_ID 358
#define DUCKY_ID 298
#define SHADOW_ID 1276

static void __attribute__((naked)) ChangeMonsterSprite(struct entity* entity, int species_id)
{
    asm("stmdb  sp!,{r4,r5,r6,r14}");
    asm("mov r5,r0");
    asm("mov r4,r1");
    asm("ldr r6,[r5,#0xB4]");
    asm("mov r1,#1");
    // asm("mov r0,r4");
    // asm("bl LoadMonsterSprite");
    asm("mov r0,r4");
    asm("bl DungeonGetSpriteIndex");
    asm("strh r0,[r5,#0xA8]");
    asm("strh r4,[r6,#0x4]");
    asm("mov r0,r5");
    asm("bl UnkSpriteFunc1");
    asm("mov r0,r5");
    asm("bl GetSleepAnimationId");
    asm("mov r1,r0");
    asm("mov r0,r5");
    asm("bl UnkSpriteFunc2");
    asm("ldmia  sp!,{r4,r5,r6,r15}");
}

static void SetTextboxAttribute(uint8_t x_start, uint8_t y_start, uint8_t x_width, uint8_t y_width, bool top_screen, uint8_t border_type)
{
    SaveScriptVariableValue(NULL, VAR_VERSION, 11621);
    SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB1, 0, x_start);
    SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB1, 1, y_start);
    SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB2, 0, x_width);
    SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB2, 1, y_width);
    SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB3, 0, top_screen);
    SaveScriptVariableValueAtIndex(NULL, VAR_SCENARIO_SUB3, 1, border_type);
}

static void ResetTextboxAttribute()
{
    SaveScriptVariableValue(NULL, VAR_VERSION, 1);
}

static void PlaySoundEffect(int se_id)
{
    se_Play(se_id, 0x100, 0x1F);
}

static void WaitFrames(int n) {
  for (int i = 0; i < n; i++) {
    AdvanceFrame(0);
  }
}

static int GetMainPhase()
{
  return LoadScriptVariableValue(NULL, VAR_DUNGEON_EVENT_LOCAL);
}

static void NextMainPhase()
{
  SaveScriptVariableValue(NULL, VAR_DUNGEON_EVENT_LOCAL, GetMainPhase() + 1);
  SaveScriptVariableValue(NULL, VAR_EVENT_LOCAL, 0);
}

static int GetSubPhase()
{
  return LoadScriptVariableValue(NULL, VAR_EVENT_LOCAL);
}

static void NextSubPhase()
{
  SaveScriptVariableValue(NULL, VAR_EVENT_LOCAL, GetSubPhase() + 1);
}

static void ConstantDamage(struct entity* user, struct entity* target, struct move* move, int damage)
{
  struct damage_data damage_out;
  int move_type = GetMoveType(move);
  int move_category = GetMoveCategory(move->id.val);
  union damage_source source = GetDamageSourceWrapper(move, NULL);
  struct monster* target_mon = target->info;
  int old_hp = target_mon->hp;
  CalcDamageFixedWrapper(user, target, damage, false, &damage_out, move_type, move_category, source, 0, 1, 0);
  if(target_mon->id.val == MARCUS_ID && target_mon->max_hp_stat == 999 && GetMainPhase() < 3 && damage != 333)
    target_mon->hp = old_hp;
}

static void Talk(int species_id, int portrait_emotion, uint8_t portrait_layout_idx, char* dialogue, bool auto_close_flag)
{
  struct portrait_box portrait_box;
  layout_idx = portrait_layout_idx;
  InitDungeonPortrait(&portrait_box, species_id, portrait_emotion);
  DisplayMessage3(NULL, &portrait_box, dialogue, auto_close_flag);
}

static void Turn2Direction(struct entity* entity, int speed, bool clockwise, int start_direction, int end_direction)
{
  int current_direction = start_direction;
  int iteration = 1;
  int frame_count = speed << 1;
  if(clockwise)
    iteration = -1;
  while(current_direction != end_direction)
  {
    current_direction = (current_direction + iteration) & 7;
    SetEntityDirection(entity, current_direction);
    WaitFrames(frame_count);
  }
}

static void JumpAngry(struct entity* entity)
{
  struct monster* monster = entity->info;
  SetEntityAnimation(entity, 0, monster->action.direction.val);
  FreezeAnim(entity);
  for(int j = 0; j < 2; j++)
  {
    for(int i = 0; i < 6; i++)
    {
      entity->elevation += 0x160;
      if(i & 1)
        AdvanceFrame(0);
    }
    AdvanceFrame(0);
    for(int i = 0; i < 6; i++)
    {
      entity->elevation -= 0x160;
      if(i & 1)
        AdvanceFrame(0);
    }
  }
  UnfreezeAnim(entity);
  SetEntityAnimation(entity, 7, monster->action.direction.val);
}

static void HeadShake(struct entity* entity)
{
  struct monster* monster = entity->info;
  int current_direction = monster->action.direction.val;
  current_direction = (current_direction - 1) & 7;
  SetEntityAnimation(entity, 7, current_direction);
  WaitFrames(4);
  current_direction = (current_direction + 2) & 7;
  SetEntityAnimation(entity, 7, current_direction);
  WaitFrames(4);
  current_direction = (current_direction - 2) & 7;
  SetEntityAnimation(entity, 7, current_direction);
  WaitFrames(4);
  current_direction = (current_direction + 1) & 7;
  SetEntityAnimation(entity, 7, current_direction);
  WaitFrames(6);
}

static int FindMoveIndex(struct monster* monster, int move_id)
{
  for(int i = 0; i < 4; i++)
  {
    struct move* move = &monster->moves[i];
    if(move->f_exists && move->id.val == move_id)
    {
      move->pp = 255;
      return i;
    }
  }
  CardPullOut();
  return -1;
}

static bool CanActivateWaryFighter(struct entity* entity, int direction)
{
  // This sucks, only really usable in the context of this fight only, but who caaaaaaares
  int new_pos_x = entity->pos.x + DIRECTIONS_XY[direction][0];
  int new_pos_y = entity->pos.y + DIRECTIONS_XY[direction][1];
  struct tile* tile = GetTileSafe(new_pos_x, new_pos_y);
  return !(tile->f_impassable_wall || tile->monster); /* !(CannotStandOnTile(entity, tile)); */ // Why doesn't this work?
}

static void DodgeWarp(struct entity* target)
{
  SubstitutePlaceholderStringTags(0, target, 0);
  LogMessageByIdWithPopupCheckUser(target, 301);
  TryWarp(target, target, WARP_RANDOM, NULL);
}