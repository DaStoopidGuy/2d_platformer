#pragma once
#include "common.h"

Player NewPlayer(Vector2 pos, const char *texture_file_name);
void UpdatePlayer(Player *player, float deltaTime, int *tilemap, bool godmode);
void DrawPlayer(Player *player);
void DrawPlayerCoords(Player *player);
