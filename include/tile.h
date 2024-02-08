#include "common.h"

typedef struct
{
    Texture2D texture;
    Rectangle src;
} Tile;

Tile NewTile();
void DrawTile(Tile tile, int x, int y);
void DrawTilemap(int tilemap[][25], Tile tiles[], int rows, int cols);