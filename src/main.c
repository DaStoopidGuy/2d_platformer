#include "common.h"
#include "player.h"
#include "structs.h"
#include "tile.h"
#include <raylib.h>
#include <stdlib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void InitGameData(GameData *gd);
void FreeGameData(GameData *gd);
bool GameLoop();

GameData game;

int main(void)
{
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "2d Platformer");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    InitGameData(&game);
    
    // "main menu" label
    const char * label_text = "Main Menu";
    const int label_font_size = 50;

    Rectangle label_rec;
    label_rec.height = label_font_size;
    label_rec.width  = MeasureText(label_text, label_font_size);
    label_rec.x = WIN_WIDTH/2 - label_rec.width/2;
    label_rec.y = WIN_HEIGHT/15;


    #define BTN_W 150
    #define BTN_H 60
    Rectangle play_button_rec = (Rectangle){WIN_WIDTH/2 - BTN_W/2, WIN_HEIGHT/2, BTN_W, BTN_H};
    Rectangle quit_button_rec = (Rectangle){WIN_WIDTH/2 - BTN_W/2, WIN_HEIGHT/2 + BTN_H + 10, BTN_W, BTN_H};
    const int button_text_size = 30;

    GuiLoadStyle("src/style_dark.rgs");

    bool shouldQuit = false;
    while (!WindowShouldClose() && !shouldQuit)
    {
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
    CloseWindow();
    FreeGameData(&game);

    return 0;
}

bool GameLoop()
{
    bool shouldQuit = false;
    while (true)
    {
        BeginDrawing();
        float deltaTime = GetFrameTime();

        // handle window exit
        if (WindowShouldClose())
        {
            shouldQuit = true;
            break;
        }

        // go back to main menu on pressing esc
        if (IsKeyPressed(KEY_ESCAPE))
            break;

        // toggle god mode on G
        if (IsKeyPressed(KEY_G))
            game.god_mode = !game.god_mode;

        // UPDATE STUFF
        UpdatePlayer(&game.player, deltaTime, game.tilemap, game.god_mode);

        // RENDER STUFF
        ClearBackground((Color){48,122,169}); // clear the screen
        // ClearBackground(DARKGRAY);

        DrawTilemap(game.tilemap, game.tiles);
        DebugHighlightNeighbouringTiles(game.player.pos, game.tilemap);

        DrawText("Congrats! You suck!", 190, 200, 20, WHITE);

        // debug
        DrawFPS(WIN_WIDTH - 100, 30);
        DrawPlayerCoords(&game.player);
        if (game.god_mode)
            DrawText("GODMODE", WIN_WIDTH / 2, 10, 15, RED);

        // player
        DrawPlayer(&game.player);

        EndDrawing();
    }
    return shouldQuit;
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
    free(gd->tiles);
    free(gd->tilemap);
}
