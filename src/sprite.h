#pragma once

#include "raylib.h"

//
//  Structs
//

typedef enum SpriteID {
    SPRITE_TILE_GRASS,
    SPRITE_TILE_GROUND,
    SPRITE_GHOST_STATIC,
    SPRITE_GHOST_RUN,
    SPRITE_GHOST_JUMP,

    SPRITE_NONE, //TODO: should i move it under count? as this enum signifies nothing
    SPRITE_COUNT
} SpriteID;

typedef struct Sprite {
    Vector2 atlas_offset;
    Vector2 size;
    int frame_count;
    int fps;
} Sprite;

//
// Function Declarations
//

Sprite GetSprite(SpriteID sprite_id);
void DrawSprite(SpriteID sprite_id, Texture2D atlas, Vector2 pos, bool flip);
void DrawAnimatedSprite(SpriteID sprite_id, Texture2D atlas, Vector2 pos, bool flip);
