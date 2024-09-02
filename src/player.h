#pragma once
#include "raylib.h"
#include "animation.h"

typedef struct {
    Vector2 pos;
    Vector2 vel;
    int facing;
    bool is_on_ground;
    Texture2D texture;
    Rectangle rec;
    SpriteAnimation animation;
} Player;

Player NewPlayer(Vector2 pos, const char *texture_file_name);
void DestroyPlayer(Player *player);
void UpdatePlayer(Player *player, float deltaTime, int *tilemap, bool godmode);
void DrawPlayer(Player *player);
void DrawPlayerCoords(Player *player);
