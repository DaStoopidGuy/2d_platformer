#include "game.h"
#include "common.h"
#include "input.h"
#include "player.h"
#include "raylib.h"
#include "tile.h"
#include <stdlib.h>

Game game;

// returns a boolean telling to exit the game or not
bool GameLoop() {
    // TODO: remove Adele - Skyfall as the bgm when shipping the game
    PlayMusicStream(game.bgm);


    bool showDebug = false;
    bool shouldQuit = false;
    while (true) {
        GetInputs();

        if (game.god_mode)
            UpdateMusicStream(game.bgm);

        float deltaTime = GetFrameTime();

        // on window resize
        if (IsWindowResized()) {
            win_width = GetScreenWidth();
            win_height = GetScreenHeight();
        }

        // handle window exit
        if (WindowShouldClose()) {
            shouldQuit = true;
            break;
        }

        // go back to main menu on pressing esc
        if (inputs.game_exit_to_menu)
            break;

        if (inputs.game_pause)
            game.paused = !game.paused;

        // toggle god mode on G
        if (inputs.toggle_godmode)
            game.god_mode = !game.god_mode;

        if (inputs.toggle_debug)
            showDebug = !showDebug;

        // UPDATE STUFF
        if (!game.paused) {
            UpdatePlayer(&game.player, deltaTime, game.tilemap, game.mapsize, game.god_mode);
            UpdatePlayerCamera(&game.player);
        }

        // RENDER STUFF

        BeginDrawing();
            ClearBackground((Color){48, 122, 169}); // clear the screen
            BeginMode2D(game.player.camera);
                DrawTilemap(game.tilemap, game.mapsize, game.atlas);
                DrawPlayer(&game.player, game.atlas);

                if (showDebug)
                    DebugHighlightNeighbouringTiles(game.player.pos, game.tilemap, game.mapsize);
            EndMode2D();

            if (game.god_mode)
                DrawText("GODMODE", (win_width/2)-60, 1, 30, RED);

            // debug
            if (showDebug) {
                DrawFPS(win_width - 100, 30);
                DrawPlayerCoords(&game.player);
                DrawText("Congrats! You suck!", 190, 200, 20, WHITE);
            }

        EndDrawing();
    }
    StopMusicStream(game.bgm);
    return shouldQuit;
}

void InitGameData(Game *g) {
    g->atlas = LoadTexture(ASSETS_PATH "atlas.png");
    g->god_mode = false;
    g->player = NewPlayer((Vector2){0, 0});
    g->mapsize = GetTilemapDimensions(ASSETS_PATH "map.csv");
    g->tilemap = malloc(sizeof(int) * g->mapsize.x * g->mapsize.y);
    ImportTilemap(ASSETS_PATH "map.csv", g->tilemap, g->mapsize);
    g->bgm = LoadMusicStream(ASSETS_PATH "bgm.mp3");
}

void FreeGameData(Game *g) {
    UnloadTexture(g->atlas);
    DestroyPlayer(&g->player);
    free(g->tilemap);
    UnloadMusicStream(g->bgm);
}
