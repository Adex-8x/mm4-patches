
typedef struct astruct_53 astruct_53, *Pastruct_53;

typedef struct AnotherRenderAllocStuff AnotherRenderAllocStuff, *PAnotherRenderAllocStuff;

typedef struct astruct_36 astruct_36, *Pastruct_36;

typedef struct ImportantPaletteRelatedStruct ImportantPaletteRelatedStruct, *PImportantPaletteRelatedStruct;

typedef struct astruct_messedup astruct_messedup, *Pastruct_messedup;

typedef struct astruct_35 astruct_35, *Pastruct_35;

typedef struct ImportantPaletteRelatedSubStruct ImportantPaletteRelatedSubStruct, *PImportantPaletteRelatedSubStruct;

typedef struct PaletteData PaletteData, *PPaletteData;

struct RGBA8 {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

struct PaletteData {
    struct ImportantPaletteRelatedSubStruct * unk_pal_related_maybe_owner;
    int nb_color;
    bool need_update;
    undefined field3_0x9;
    uint16_t fade_opposite;
    struct RGBA8 flush_colors;
    undefined4 unk;
    void (* refresh_command)(struct PaletteData *);
    struct RGBA8 * rgba_palette; /* seemingly allocated */
    uint16_t * raw_palette;
    struct PaletteData * previous_palette;
    struct PaletteData * next_palette;
};

struct ImportantPaletteRelatedSubStruct {
    uint32_t skip_certain_color_for_effect; /* skip certain color when applying effects when value is 2 (are they the portrait and text box color?) */
    int count; /* number of element in the alloc at offset 0x10 of this struct */
    undefined field2_0x8;
    undefined field3_0x9;
    undefined field4_0xa;
    undefined field5_0xb;
    undefined4 field6_0xc;
    undefined2 * palettes; /* 2-byte (BGR5?) colors */
};

struct ImportantPaletteRelatedStruct {
    struct ImportantPaletteRelatedSubStruct sub_1;
    struct PaletteData pal_1;
    struct ImportantPaletteRelatedSubStruct sub_2;
    struct PaletteData pal_2;
    undefined field4_0x78;
    undefined field5_0x79;
    undefined field6_0x7a;
    undefined field7_0x7b;
    undefined field8_0x7c;
    undefined field9_0x7d;
    undefined field10_0x7e;
    undefined field11_0x7f;
    undefined field12_0x80;
    undefined field13_0x81;
    undefined field14_0x82;
    undefined field15_0x83;
    undefined field16_0x84;
    undefined field17_0x85;
    undefined field18_0x86;
    undefined field19_0x87;
    undefined field20_0x88;
    undefined field21_0x89;
    undefined field22_0x8a;
    undefined field23_0x8b;
    undefined field24_0x8c;
    undefined field25_0x8d;
    undefined field26_0x8e;
    undefined field27_0x8f;
    undefined field28_0x90;
    undefined field29_0x91;
    undefined field30_0x92;
    undefined field31_0x93;
    undefined field32_0x94;
    undefined field33_0x95;
    undefined field34_0x96;
    undefined field35_0x97;
    undefined field36_0x98;
    undefined field37_0x99;
    undefined field38_0x9a;
    undefined field39_0x9b;
};

struct astruct_35 {
    int field0_0x0;
    int something_important_for_rendering;
    int field2_0x8;
    undefined2 field3_0xc;
    char field4_0xe;
    undefined field5_0xf;
};

struct astruct_36 {
    struct astruct_35 field0_0x0[223];
    undefined field1_0xdf0;
    undefined field2_0xdf1;
    undefined field3_0xdf2;
    undefined field4_0xdf3;
    undefined field5_0xdf4;
    undefined field6_0xdf5;
    undefined field7_0xdf6;
    undefined field8_0xdf7;
    undefined field9_0xdf8;
    undefined field10_0xdf9;
    undefined field11_0xdfa;
    undefined field12_0xdfb;
    undefined field13_0xdfc;
    undefined field14_0xdfd;
    undefined field15_0xdfe;
    undefined field16_0xdff;
    short field17_0xe00;
    undefined field18_0xe02;
    undefined field19_0xe03;
};

struct astruct_messedup {
    int field0_0x0;
    int field1_0x4;
    int field2_0x8;
    undefined2 * field3_0xc;
    void * field4_0x10;
    undefined field5_0x14;
    undefined field6_0x15;
    undefined field7_0x16;
    undefined field8_0x17;
    undefined4 * field9_0x18;
    void * field10_0x1c;
};

struct AnotherRenderAllocStuff { /* 112 bytes memzeroed on init */
    char field0_0x0;
    undefined field1_0x1;
    undefined field2_0x2;
    undefined field3_0x3;
    struct astruct_36 * pnt_at_byte_4;
    struct ImportantPaletteRelatedStruct * pnt_at_byte_8;
    uint16_t field6_0xc;
    char field7_0xe;
    undefined field8_0xf;
    undefined field9_0x10;
    undefined field10_0x11;
    undefined field11_0x12;
    undefined field12_0x13;
    undefined field13_0x14;
    undefined field14_0x15;
    undefined field15_0x16;
    undefined field16_0x17;
    undefined field17_0x18;
    undefined field18_0x19;
    undefined field19_0x1a;
    undefined field20_0x1b;
    char field21_0x1c;
    undefined field22_0x1d;
    undefined field23_0x1e;
    undefined field24_0x1f;
    struct astruct_messedup field25_0x20;
    undefined4 field26_0x40;
    undefined field27_0x44;
    undefined field28_0x45;
    undefined field29_0x46;
    undefined field30_0x47;
    undefined field31_0x48;
    undefined field32_0x49;
    undefined field33_0x4a;
    undefined field34_0x4b;
    undefined field35_0x4c;
    undefined field36_0x4d;
    undefined field37_0x4e;
    undefined field38_0x4f;
    undefined field39_0x50;
    undefined field40_0x51;
    undefined field41_0x52;
    undefined field42_0x53;
    undefined field43_0x54;
    undefined field44_0x55;
    undefined field45_0x56;
    undefined field46_0x57;
    undefined field47_0x58;
    undefined field48_0x59;
    undefined field49_0x5a;
    undefined field50_0x5b;
    undefined field51_0x5c;
    undefined field52_0x5d;
    undefined field53_0x5e;
    undefined field54_0x5f;
    undefined field55_0x60;
    undefined field56_0x61;
    undefined field57_0x62;
    undefined field58_0x63;
    int field59_0x64;
    undefined field60_0x68;
    undefined field61_0x69;
    undefined field62_0x6a;
    undefined field63_0x6b;
    undefined field64_0x6c;
    undefined field65_0x6d;
    undefined field66_0x6e;
    undefined field67_0x6f;
};

struct astruct_53 {
    struct AnotherRenderAllocStuff something_rndr[4];
    struct astruct_36 field1_0x1c0[2];
    struct ImportantPaletteRelatedStruct palette_related[2];
};

extern astruct_53* ANOTHER_SPRITE_RENDER_THING;