#include "common.h"
#include "tile.h"

Tile NewTile(const char *filename)
{
    Texture2D texture = LoadTexture(filename);
    Tile result = {
        texture,
        (Rectangle){0, 0, texture.width, texture.height},
    };
    return result;
}

void DrawTile(Tile tile, int x, int y)
{
    DrawTexture(tile.texture, x, y, WHITE);
}

void DrawTilemap(int tilemap[][25], Tile tiles[], int rows, int cols)
{
    // tilemap
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            switch (tilemap[y][x])
            {
            case 0:
                break;

            case 1:
            {
                DrawTile(tiles[1], x * tiles[0].texture.width, y * tiles[0].texture.height);
                break;
            }
            case 2:
            {
                DrawTile(tiles[0], x * tiles[0].texture.width, y * tiles[0].texture.height);
                break;
            }

            default:
                break;
            }
        }
    }
}