#pragma once

#include "player.h"
#include "raylib.h"

typedef struct {
    bool paused;
    RenderTexture2D target;
    Player player;
    bool god_mode;
    Texture2D atlas;
    Vector2 mapsize;
    int *tilemap;
} Game;

extern Game game;

void InitGameData(Game *g);
void FreeGameData(Game *g);

bool GameLoop();
