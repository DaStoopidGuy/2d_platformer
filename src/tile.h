#include "common.h"

enum
{
    TILE_EMPTY = -1,
    TILE_GRASS = 0,
    TILE_GROUND = 1
};

Tile NewTile(const char *filename);
void DrawTile(Tile tile, int x, int y);
void DrawTilemap(int *tilemap, Tile *tiles);

void GetTilesAround(int tiles_around[9][2], Vector2 pos);

void HighlightTile(int tile_x, int tile_y);
void DebugHighlightNeighbouringTiles(Vector2 pos, int *tilemap);

void ImportTilemap(const char *filename, int *tilemap);
