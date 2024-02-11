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
                DrawTile(tiles[1], x * TILE_SIZE, y * TILE_SIZE);
                break;
            }
            case 2:
            {
                DrawTile(tiles[0], x * TILE_SIZE, y * TILE_SIZE);
                break;
            }

            default:
                break;
            }
        }
    }
}

const int NEIGHBOUR_OFFSETS[][2] = {
    {0, 0},
    {-1, 0},
    {0, -1},
    {-1, -1},
    {1, 0},
    {0, 1},
    {1, 1},
    {-1, 1},
    {1, -1},

};
const int NEIGHBOUR_OFFSETS_LEN = sizeof(NEIGHBOUR_OFFSETS) / sizeof(NEIGHBOUR_OFFSETS[0]);

void DebugHighlighTile(int tile_x, int tile_y)
{

    DrawRectangleLines(
        tile_x * TILE_SIZE,
        tile_y * TILE_SIZE,
        TILE_SIZE,
        TILE_SIZE,
        RED);
}

void DebugHighlightNeighbouringTiles(Vector2 *ref, int tilemap[19][25])
{
    // get player tile coords
    int tile_coord_y = (int)((ref->y / TILE_SIZE) + 0.5f);
    int tile_coord_x = (int)((ref->x / TILE_SIZE) + 0.5f);
    // printf("%d, %d\n", tile_coord_x, tile_coord_y);
    for (int i = 0; i < NEIGHBOUR_OFFSETS_LEN; i++)
    {
        int check_tile_x = tile_coord_x + NEIGHBOUR_OFFSETS[i][0];
        int check_tile_y = tile_coord_y + NEIGHBOUR_OFFSETS[i][1];

        // check tilemap if tile is solid
        if (tilemap[check_tile_y][check_tile_x] != 0)
        {
            // printf("Solid block: %d %d\n", check_tile_x, check_tile_y);
            DebugHighlighTile(check_tile_x, check_tile_y);
        }
    }
}