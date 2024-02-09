#pragma once

typedef struct
{
    Vector2 pos;
    Vector2 vel;
    bool can_jump;
    Texture2D texture;
} Player;

void UpdatePlayer(Player *player, float deltaTime, int tilemap[][25], int rows, int cols);
void DrawPlayer(Player *player);
void DrawPlayerCoords(Player *player);