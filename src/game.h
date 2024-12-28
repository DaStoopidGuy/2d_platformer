#pragma once

#include "player.h"
#include "raylib.h"

typedef struct {
    bool paused;
    Player player;
    bool god_mode;
    Texture2D atlas;
    Vector2 mapsize;
    int *tilemap;
    Music bgm;
} Game;

extern Game game;

void InitGameData(Game *g);
void FreeGameData(Game *g);

bool GameLoop();
