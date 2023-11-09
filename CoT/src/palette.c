/// Contain code on how to change the palette of a Pokémon (or potentially other actors (untested)) in real-time.

#include <pmdsky.h>
#include <cot.h>

#include "more_palette.h"
#include "actor.h"
#include "palette.h"

//convert RGBA to hmm... ABGR when viewed as is, but maybe it’s depicted as GRAB due to endianess. I don’t know, I don’t care, it work.
//actually seems to be RGBA. How? Whatever.
unsigned int color_to_packed(const unsigned char base [3]) {
    unsigned char r = base[0];
    unsigned char g = base[1];
    unsigned char b = base[2];
    unsigned int result = (0x80 << 0x18) + (b << 0x10) + (g << 0x8) + r;
    return result;
}

int THING_1_ENTITY_ID = 432;
int THING_2_ENTITY_ID = 433;

uint32_t TEST_COUNTER = 0;

uint8_t somethingColor(uint8_t input) {
    if (input < 128) {
        return input*2;
    } else if (input == 128) {
        return 255;
    } else {
        return 255-(input-128)*2;
    }
}

void TestMessUpWithPalette(int entity_id) {
    struct live_actor_list_custom* live_actor_list_tmp = (struct live_actor_list_custom *) (GROUND_STATE_PTRS.actors);
    int actor_id = LookupActorLiveIdForGroundActorId((enum script_entity_id) entity_id);
    if (actor_id != -1) {
        struct AnimationSub* animation_sub = &live_actor_list_tmp->actors[actor_id].animation.sub_content;

        int render_bank_id_unlooked = animation_sub->field56_0x7a;
        int render_bank_id = SPRITE_BANK_ID_SOMETHING_IDK[render_bank_id_unlooked];
        
        struct AnotherRenderAllocStuff* another_sprite_alloc_stuff = &ANOTHER_SPRITE_RENDER_THING->something_rndr[render_bank_id];
        
        ImportantPaletteRelatedStruct* imp_pal_rel_struct = another_sprite_alloc_stuff->pnt_at_byte_8;
        uint32_t* vanilla_palette_ptr = (uint32_t*) imp_pal_rel_struct->pal_1.rgba_palette; //why always pal1 and never pal2?
        
        int palette_start_count = (animation_sub->field29_0x41 & 0xf) << 4;

        for (int i = 0; i < 16; i++) {
            unsigned char result[3];
            int imul = (i*4)/9+1;
            result[0] = somethingColor((imul*TEST_COUNTER/3) % 256) / 4;
            result[1] = somethingColor(imul*((TEST_COUNTER*5)/13) % 256) / 4;
            result[2] = somethingColor(imul*((TEST_COUNTER*13)/30) % 256) / 4;
            vanilla_palette_ptr[palette_start_count + i] = color_to_packed(result);
        }

        imp_pal_rel_struct->pal_1.need_update = true;
    }
}

extern void ReloadPaletteFun();

void OverrideReloadPalette() {
    if (TEST_COUNTER > (2 << 21)) {
        TEST_COUNTER = 0;
    } else {
        TEST_COUNTER += 1;
    }
    for (int i = 0; i < 5; i++) {
        int actor_id = ACTORS_WITH_BLOB_EFFECT[i];
        if (actor_id != 0) {
            TestMessUpWithPalette(actor_id);
        }
    }
    ReloadPaletteFun();
}

int ACTORS_WITH_BLOB_EFFECT[5];