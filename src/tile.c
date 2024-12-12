#include "tile.h"
#include "common.h"
#include "game.h"
#include "raylib.h"
#include "sprite.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int GetTileDamage(TileType tile) {
    switch (tile) {
    case TILE_SPIKE:
        return 10;
    default:
        return 0;
    }
}

void DrawTilemap(int *tilemap) {
    // tilemap
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SpriteID sprite_id = SPRITE_NONE;
            switch (tilemap[y * MAP_WIDTH + x]) {
            case TILE_EMPTY: // air
            {
                sprite_id = SPRITE_NONE;
                break;
            }
            case TILE_GRASS: {
                sprite_id = SPRITE_TILE_GRASS;
                break;
            }
            case TILE_GROUND: {
                sprite_id = SPRITE_TILE_GROUND;
                break;
            }
            case TILE_SPIKE: {
                sprite_id = SPRITE_TILE_SPIKE;
                break;
            }
            default:
                break;
            }
            if (sprite_id != SPRITE_NONE)
                DrawStaticSprite(sprite_id, game.atlas,
                           (Vector2){.x = x * TILE_SIZE, y * TILE_SIZE}, false);
        }
    }
}

void GetTilesAround(int tiles_around[9][2], Vector2 pos) {
    int tile_pos_y = (pos.y / TILE_SIZE) + 0.5f;
    int tile_pos_x = (pos.x / TILE_SIZE) + 0.5f;

    for (int i = -1, k = 0; i <= 1; i++) {
        for (int j = -1; j <= 1; j++, k++) {
            int check_tile_x = tile_pos_x + i;
            int check_tile_y = tile_pos_y + j;

            tiles_around[k][0] = check_tile_x;
            tiles_around[k][1] = check_tile_y;
        }
    }
}

void DebugHighlighTile(int tile_x, int tile_y) {
    DrawRectangleLines(tile_x * TILE_SIZE, tile_y * TILE_SIZE, TILE_SIZE,
                       TILE_SIZE, RED);
}

void DebugHighlightNeighbouringTiles(Vector2 pos, int *tilemap) {
    int tiles_around[9][2];
    GetTilesAround(tiles_around, pos);

    for (int i = 0; i < 9; i++) {
        int x = tiles_around[i][0];
        int y = tiles_around[i][1];
        if (tilemap[y * MAP_WIDTH + x] != TILE_EMPTY)
            DebugHighlighTile(x, y);
    }
}

// TODO: check for tilemap max rows and columns in the loops
void ImportTilemap(const char *filename, int *tilemap) {
    char buffer[1024];
    char *token;

    FILE *file = fopen(filename, "r");
    if (file == NULL)
        printf("Map file could not be opened");

    // read file content line by line
    int y = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        // replace the trailing newline character with 0 (aka remove it)
        // buffer[strcspn(buffer, "\n")] = 0;
        token = strtok(buffer, ",");

        int x = 0;
        while (token != NULL) {

            // set the tilemap cell accordingly
            tilemap[y * MAP_WIDTH + x] = atoi(token);
            token = strtok(NULL, ",");
            x++;
        }
        y++;
    }

    // close the file after use
    fclose(file);
}
