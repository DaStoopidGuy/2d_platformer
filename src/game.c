#include <math.h>
#include <stdlib.h>
#include "game.h"
#include "common.h"
#include "input.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include "tile.h"

Game game;

// returns a boolean telling to exit the game or not
bool GameLoop() {
    //TODO: remove Adele - Skyfall as the bgm when shipping the game
    Music bgm = LoadMusicStream(ASSETS_PATH "bgm.mp3");
    PlayMusicStream(bgm);


    bool showDebug = false;
    bool shouldQuit = false;
    while (true) {
        GetInputs();

        if (game.god_mode)
            UpdateMusicStream(bgm);

        // TODO: draw to a small render target first then scale it up to window
        // size
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

        // toggle god mode on G
        if (inputs.toggle_godmode)
            game.god_mode = !game.god_mode;

        if (inputs.toggle_debug)
            showDebug = !showDebug;

        // UPDATE STUFF
        UpdatePlayer(&game.player, deltaTime, game.tilemap, game.god_mode);
        UpdatePlayerCamera(&game.player);

        // RENDER STUFF
        BeginTextureMode(game.target);
            ClearBackground((Color){48, 122, 169}); // clear the screen
            DrawTilemap(game.tilemap);
            DrawPlayer(&game.player);

            if (showDebug)
                DebugHighlightNeighbouringTiles(game.player.pos, game.tilemap);
        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLUE);
            BeginMode2D(game.player.camera);
            DrawTexturePro(game.target.texture,
                           (Rectangle){0, 0, game.target.texture.width,
                                       -game.target.texture.height},
                           (Rectangle){0, 0, win_width, win_height},
                           (Vector2){0, 0}, 0.0f, WHITE);
            EndMode2D();

            if (game.god_mode)
                DrawText("GODMODE", 73*SCALE, 1, 30, RED);

            // debug
            if (showDebug) {
                DrawFPS(win_width - 100, 30);
                DrawPlayerCoords(&game.player);
                DrawText("Congrats! You suck!", 190, 200, 20, WHITE);
            }

        EndDrawing();
    }
    StopMusicStream(bgm);
    return shouldQuit;
}

void InitGameData(Game *g) {
    g->target = LoadRenderTexture(200, 152);
    g->atlas = LoadTexture(ASSETS_PATH "atlas.png");
    g->god_mode = false;
    g->player = NewPlayer((Vector2){0, 0});
    g->tilemap = malloc(sizeof(int) * MAP_WIDTH * MAP_HEIGHT);
    ImportTilemap(ASSETS_PATH "map.csv", g->tilemap);
}

void FreeGameData(Game *g) {
    UnloadRenderTexture(g->target);
    UnloadTexture(g->atlas);
    DestroyPlayer(&g->player);
    free(g->tilemap);
}
