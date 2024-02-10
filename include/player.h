#pragma once

typedef struct
{
    Vector2 pos;
    Vector2 vel;
    bool is_on_ground;
    Texture2D texture;
    Rectangle rec;
} Player;

Player NewPlayer(Vector2 pos, const char *texture_file_name);
void UpdatePlayer(Player *player, float deltaTime, int tilemap[][25], int rows, int cols, bool godmode);
void DrawPlayer(Player *player);
void DrawPlayerCoords(Player *player);