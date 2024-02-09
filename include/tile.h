#include "common.h"

typedef struct
{
    Texture2D texture;
    Rectangle src;
} Tile;

Tile NewTile();
void DrawTile(Tile tile, int x, int y);
void DrawTilemap(int tilemap[][25], Tile tiles[], int rows, int cols);

void HighlightTile(int tile_x, int tile_y);
void DebugHighlightNeighbouringTiles(Vector2 *ref, int tilemap[19][25]);