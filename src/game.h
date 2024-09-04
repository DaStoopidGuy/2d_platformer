#pragma once

#include "player.h"

typedef struct {
    RenderTexture2D target;
    Player player;
    bool god_mode;
    Texture2D atlas;
    int *tilemap;
} Game;

extern Game game;

void InitGameData(Game *g);
void FreeGameData(Game *g);

bool GameLoop();
