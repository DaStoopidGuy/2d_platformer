#pragma once
#include "raylib.h"

typedef enum
{
    TILE_EMPTY = -1,
    TILE_GRASS = 0,
    TILE_GROUND = 1,
    TILE_SPIKE = 2,
} TileType;

int GetTileDamage(TileType tile);

void DrawTilemap(int *tilemap);

void GetTilesAround(int tiles_around[9][2], Vector2 pos);

void HighlightTile(int tile_x, int tile_y);
void DebugHighlightNeighbouringTiles(Vector2 pos, int *tilemap);

void ImportTilemap(const char *filename, int *tilemap);
