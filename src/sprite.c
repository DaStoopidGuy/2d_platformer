#include "sprite.h"
#include "raylib.h"
#include <assert.h>

Sprite GetSprite(SpriteID sprite_id) {
    Sprite sprite = {0};
    sprite.frame_count = 1;
    sprite.fps = 1;
    sprite.size = (Vector2){8, 8};

    switch (sprite_id) {
        case SPRITE_NONE:
            break;

        case SPRITE_TILE_GRASS:
        {
            sprite.atlas_offset = (Vector2){0, 0};
            break;
        }
        case SPRITE_TILE_GROUND:
        {
            sprite.atlas_offset = (Vector2){8, 0};
            break;
        }
        case SPRITE_GHOST_STATIC: {
            sprite.atlas_offset = (Vector2){16, 0};
            break;
        }
        case SPRITE_GHOST_RUN:
        {
            sprite.atlas_offset = (Vector2){0, 8};
            sprite.frame_count = 6;
            sprite.fps = 11;
            break;
        }
        case SPRITE_GHOST_JUMP:
        {
            sprite.atlas_offset = (Vector2){0, 16};
            sprite.frame_count = 3;
            sprite.fps = 8;
            break;
        }
        case SPRITE_COUNT:
        {
            break;
        }
    }
    return sprite;
}

void DrawSprite(SpriteID sprite_id, Texture2D atlas, Vector2 pos, bool flip) {
    if (sprite_id == SPRITE_NONE)
        return;

    Sprite sprite = GetSprite(sprite_id);
    Rectangle source = {.x = sprite.atlas_offset.x,
                        .y = sprite.atlas_offset.y,
                        .width = sprite.size.x,
                        .height = sprite.size.y};
    if (flip)
        source.width = -source.width;
    DrawTextureRec(atlas, source, pos, WHITE);
}

void DrawAnimatedSprite(SpriteID sprite_id, Texture2D atlas, Vector2 pos,
                        bool flip) {
    if (sprite_id == SPRITE_NONE)
        return;

    Sprite sprite = GetSprite(sprite_id);

    // NOTE: if i ever need animations to start at the first index, i can make a
    // new function which returns an index
    int idx = (int)(GetTime() * sprite.fps) % sprite.frame_count;

    assert(idx < sprite.frame_count);

    Rectangle source = {.x = sprite.atlas_offset.x + idx * sprite.size.x,
                        .y = sprite.atlas_offset.y,
                        .width = sprite.size.x,
                        .height = sprite.size.y};

    if (flip) source.width = -source.width;

    DrawTextureRec(atlas, source, pos, WHITE);
}
