#include "common.h"
#include "player.h"
#include "structs.h"
#include "tile.h"
#include <raylib.h>
#include <stdlib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

void InitGameData(Game *gd);
void FreeGameData(Game *gd);
bool GameLoop();

Game game;

float win_width = WIN_WIDTH;
float win_height = WIN_HEIGHT;

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(win_width, win_height, "2d Platformer");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    InitGameData(&game);

    // "main menu" label
    const char *label_text = "Main Menu";
    const int label_font_size = 50;

    Rectangle label_rec;
    label_rec.height = label_font_size;
    label_rec.width = MeasureText(label_text, label_font_size);
    label_rec.x = (float)win_width / 2 - label_rec.width / 2;
    label_rec.y = (float)win_height / 15;

    const float BTN_W = 150;
    const float BTN_H = 60;
    Rectangle play_button_rec =
        (Rectangle){win_width / 2. - BTN_W / 2, win_height / 2., BTN_W, BTN_H};
    Rectangle quit_button_rec = (Rectangle){
        win_width / 2. - BTN_W / 2, win_height / 2. + BTN_H + 10, BTN_W, BTN_H};
    const int button_text_size = 30;

    GuiLoadStyle("resources/style_dark.rgs");

    bool shouldQuit = false;
    while (!WindowShouldClose() && !shouldQuit) {
        // handle window resize
        if (IsWindowResized()) {
            win_width = GetScreenWidth();
            win_height = GetScreenHeight();
            label_rec.x = win_width / 2 - label_rec.width / 2;
            label_rec.y = win_height / 15;
            play_button_rec = (Rectangle){win_width / 2 - BTN_W / 2,
                                          win_height / 2, BTN_W, BTN_H};
            quit_button_rec =
                (Rectangle){win_width / 2 - BTN_W / 2,
                            win_height / 2 + BTN_H + 10, BTN_W, BTN_H};
        }
        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        DrawText(label_text, label_rec.x, label_rec.y, label_font_size, LIME);

        GuiSetStyle(DEFAULT, TEXT_SIZE, button_text_size);
        if (GuiButton(play_button_rec, "Play"))
            shouldQuit = GameLoop();

        if (GuiButton(quit_button_rec, "Quit"))
            shouldQuit = true;

        EndDrawing();
    }
    // Cleanup
    FreeGameData(&game);
    CloseWindow();

    return 0;
}

bool GameLoop() {
    bool showDebug = false;
    bool shouldQuit = false;
    while (true) {
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
        if (IsKeyPressed(KEY_ESCAPE))
            break;

        // toggle god mode on G
        if (IsKeyPressed(KEY_G))
            game.god_mode = !game.god_mode;

        if (IsKeyPressed(KEY_BACKSLASH))
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
    return shouldQuit;
}

void InitGameData(Game *g) {
    g->target = LoadRenderTexture(200, 152);
    g->god_mode = false;
    g->player = NewPlayer((Vector2){0, 0}, "resources/player.png");
    g->tiles = malloc(sizeof(Tile) * 2);
    g->tiles[0] = NewTile("resources/grass-tile.png");
    g->tiles[1] = NewTile("resources/ground-tile.png");
    g->tilemap = malloc(sizeof(int) * MAP_WIDTH * MAP_HEIGHT);
    ImportTilemap("resources/map.csv", g->tilemap);
}

void FreeGameData(Game *g) {
    UnloadRenderTexture(g->target);
    DestroyPlayer(&g->player);
    free(g->tiles);
    free(g->tilemap);
}
