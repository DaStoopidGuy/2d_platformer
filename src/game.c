#include <stdlib.h>
#include "game.h"
#include "common.h"
#include "input.h"
#include "tile.h"

Game game;

bool GameLoop() {
    //TODO: remove Adele - Skyfall as the bgm when shipping the game
    Music bgm = LoadMusicStream(ASSETS_PATH "bgm.mp3");
    PlayMusicStream(bgm);

    bool showDebug = false;
    bool shouldQuit = false;
    while (true) {
        GetInputs();

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

        // RENDER STUFF
        BeginTextureMode(game.target);

        ClearBackground((Color){48, 122, 169}); // clear the screen

        if (game.god_mode)
            DrawText("GODMODE", 73, 1, 1, RED);

        DrawTilemap(game.tilemap, game.tiles);
        if (showDebug)
            DebugHighlightNeighbouringTiles(game.player.pos, game.tilemap);

        // player
        DrawPlayer(&game.player);

        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLUE);
        DrawTexturePro(game.target.texture,
                       (Rectangle){0, 0, game.target.texture.width,
                                   -game.target.texture.height},
                       (Rectangle){0, 0, win_width, win_height},
                       (Vector2){0, 0}, 0.0f, WHITE);

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
    g->god_mode = false;
    g->player = NewPlayer((Vector2){0, 0}, ASSETS_PATH "player.png");
    g->tiles = malloc(sizeof(Tile) * 2);
    g->tiles[TILE_GRASS] = NewTile(ASSETS_PATH "grass-tile.png");
    g->tiles[TILE_GROUND] = NewTile(ASSETS_PATH "ground-tile.png");
    g->tilemap = malloc(sizeof(int) * MAP_WIDTH * MAP_HEIGHT);
    ImportTilemap(ASSETS_PATH "map.csv", g->tilemap);
}

void FreeGameData(Game *g) {
    UnloadRenderTexture(g->target);
    DestroyPlayer(&g->player);
    free(g->tiles);
    free(g->tilemap);
}
