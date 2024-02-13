#include "common.h"

typedef struct
{
    Texture2D texture;
    Rectangle src;
} Tile;

enum
{
    TILE_EMPTY = -1
};

Tile NewTile();
void DrawTile(Tile tile, int x, int y);
void DrawTilemap(int tilemap[][MAP_WIDTH], Tile tiles[]);

void GetTilesAround(Vector2 *tiles_around, Vector2 pos);

void HighlightTile(int tile_x, int tile_y);
void DebugHighlightNeighbouringTiles(Vector2 pos, int tilemap[][MAP_WIDTH]);

void ImportTilemap(const char *filename, int tilemap[][MAP_WIDTH]);