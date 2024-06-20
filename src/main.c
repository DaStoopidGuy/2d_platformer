#include "common.h"
#include "player.h"
#include "structs.h"
#include "tile.h"
#include <stdlib.h>

void InitGameData(GameData *gd);
void FreeGameData(GameData *gd);

int main(void)
{
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "2d Platformer");
    SetTargetFPS(60);

    GameData game;
    InitGameData(&game);
    
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        if (IsKeyPressed(KEY_G))
            game.god_mode = !game.god_mode;

        // UPDATE STUFF
        UpdatePlayer(&game.player, deltaTime, game.tilemap, game.god_mode);

        // RENDER STUFF
        BeginDrawing();
        ClearBackground(DARKGRAY); // clear the screen

        DrawTilemap(game.tilemap, game.tiles);
        DebugHighlightNeighbouringTiles(game.player.pos, game.tilemap);

        DrawText("Congrats! You created your first game!", 190, 200, 20, WHITE);

        // debug
        DrawFPS(WIN_WIDTH - 100, 30);
        DrawPlayerCoords(&game.player);
        if (game.god_mode)
            DrawText("GODMODE", WIN_WIDTH / 2, 10, 15, RED);

        // player
        DrawPlayer(&game.player);

        EndDrawing();
    }

    CloseWindow();
    FreeGameData(&game);

    return 0;
}

void InitGameData(GameData *gd)
{
    gd->god_mode = false;
    gd->player   = NewPlayer((Vector2){400, 300}, "resources/player.png");
    gd->tiles    = malloc(sizeof(Tile)*2);
    gd->tiles[0] = NewTile("resources/grass-tile.png");
    gd->tiles[1] = NewTile("resources/ground-tile.png");
    gd->tilemap  = malloc(sizeof(int)*MAP_WIDTH*MAP_HEIGHT);
    ImportTilemap("resources/map.csv", gd->tilemap);
}

void FreeGameData(GameData *gd)
{
    printf("Destroying shit\n");
    free(gd->tiles);
    free(gd->tilemap);
}
