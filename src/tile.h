#pragma once
#include "raylib.h"

typedef enum
{
    TILE_EMPTY = -1,
    TILE_GRASS = 0,
    TILE_GROUND = 1
} TileType;

void DrawTilemap(int *tilemap, Vector2 mapsize, Texture2D atlas);

void GetTilesAround(int tiles_around[9][2], Vector2 pos);

void HighlightTile(int tile_x, int tile_y);
void DebugHighlightNeighbouringTiles(Vector2 pos, int *tilemap, Vector2 mapsize);

Vector2 GetTilemapDimensions(const char *filename);
void ImportTilemap(const char *filename, int *tilemap, Vector2 mapsize);
