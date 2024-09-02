#pragma once

#include "player.h"
#include "tile.h"

typedef struct {
    RenderTexture2D target;
    Player player;
    bool god_mode;
    Tile *tiles;
    int *tilemap;
} Game;

extern Game game;

void InitGameData(Game *g);
void FreeGameData(Game *g);

bool GameLoop();
