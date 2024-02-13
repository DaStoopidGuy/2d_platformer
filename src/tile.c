#include "tile.h"
#include <string.h>
#include "raymath.h"

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

void DrawTilemap(int tilemap[][MAP_WIDTH], Tile tiles[])
{
    // tilemap
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            switch (tilemap[y][x])
            {
            case -1: // air
                break;

            case 0:
            {
                DrawTile(tiles[0], x * TILE_SIZE, y * TILE_SIZE);
                break;
            }
            case 1:
            {
                DrawTile(tiles[1], x * TILE_SIZE, y * TILE_SIZE);
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

void GetTilesAround(Vector2 *tiles_around, Vector2 pos)
{
    // get player tile position
    int tile_pos_y = (pos.y / TILE_SIZE) + 0.5f;
    int tile_pos_x = (pos.x / TILE_SIZE) + 0.5f;

    for (int i = 0; i < NEIGHBOUR_OFFSETS_LEN; i++)
    {
        int check_tile_x = tile_pos_x + NEIGHBOUR_OFFSETS[i][0];
        int check_tile_y = tile_pos_y + NEIGHBOUR_OFFSETS[i][1];

        tiles_around[i] = (Vector2){check_tile_x, check_tile_y};
    }
}

void DebugHighlighTile(int tile_x, int tile_y)
{

    DrawRectangleLines(
        tile_x * TILE_SIZE,
        tile_y * TILE_SIZE,
        TILE_SIZE,
        TILE_SIZE,
        RED);
}

void DebugHighlightNeighbouringTiles(Vector2 pos, int tilemap[][MAP_WIDTH])
{
    // get player tile coords
    int tile_pos_y = (int)((pos.y / TILE_SIZE) + 0.5f);
    int tile_pos_x = (int)((pos.x / TILE_SIZE) + 0.5f);

    for (int i = 0; i < NEIGHBOUR_OFFSETS_LEN; i++)
    {
        int check_tile_x = tile_pos_x + NEIGHBOUR_OFFSETS[i][0];
        int check_tile_y = tile_pos_y + NEIGHBOUR_OFFSETS[i][1];

        // check tilemap if tile is solid
        if (tilemap[check_tile_y][check_tile_x] != TILE_EMPTY)
        {
            DebugHighlighTile(check_tile_x, check_tile_y);
        }
    }
}

// TODO: check for tilemap max rows and columns in the loops
void ImportTilemap(const char *filename, int tilemap[][MAP_WIDTH])
{
    char buffer[1024];
    char *token;

    FILE *file = fopen(filename, "r");
    if (file == NULL)
        printf("Map file could not be opened");

    // read file content line by line
    int y = 0;
    while (fgets(buffer, sizeof(buffer), file))
    {
        // replace the trailing newline character with 0 (aka remove it)
        // buffer[strcspn(buffer, "\n")] = 0;
        token = strtok(buffer, ",");

        int x = 0;
        while (token != NULL)
        {

            // set the tilemap cell accordingly
            tilemap[y][x] = atoi(token);
            token = strtok(NULL, ",");
            x++;
        }
        y++;
    }

    // close the file after use
    fclose(file);
}