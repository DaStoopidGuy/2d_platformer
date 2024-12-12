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

extern bool gameEnd;
extern bool gamePaused;

void InitGameData(Game *g);
void FreeGameData(Game *g);
void ResetGame(Game *g);

bool GameLoop();
