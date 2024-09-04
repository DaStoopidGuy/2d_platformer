#pragma once
#include "raylib.h"
#include "sprite.h"

typedef enum {
    PLAYER_ANIM_IDLE,
    PLAYER_ANIM_RUN,
    PLAYER_ANIM_JUMP,
    PLAYER_ANIM_FALL,

    PLAYER_ANIM_COUNT
} PlayerAnimState;

typedef struct {
    Vector2 pos;
    Vector2 vel;
    int facing;
    bool is_on_ground;
    Rectangle rec;
    PlayerAnimState animation_state;
    SpriteID animation_sprites[PLAYER_ANIM_COUNT];
} Player;

Player NewPlayer(Vector2 pos);
void DestroyPlayer(Player *player);
void UpdatePlayer(Player *player, float deltaTime, int *tilemap, bool godmode);
void DrawPlayer(Player *player);
void DrawPlayerCoords(Player *player);
