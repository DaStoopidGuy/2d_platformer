#pragma once
#include "raylib.h"

typedef struct
{
    Vector2 pos;
    Vector2 vel;
    int facing;
    bool is_on_ground;
    Texture2D texture;
    Rectangle rec;
} Player;

typedef struct
{
    Texture2D texture;
    Rectangle src;
} Tile;

