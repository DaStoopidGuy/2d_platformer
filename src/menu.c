#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "common.h"
#include "menu.h"
#include "game.h"

void MainMenu() {
    // UI Elements Setup
    // "main menu" label
    const char *label_text = "Main Menu";
    const int label_font_size = 50;

    Rectangle label_rec;
    label_rec.height = label_font_size;
    label_rec.width = MeasureText(label_text, label_font_size);
    label_rec.x = win_width / 2 - label_rec.width / 2;
    label_rec.y = win_height / 15;

    const float BTN_W = 150;
    const float BTN_H = 60;
    Rectangle play_button_rec =
        (Rectangle){win_width / 2. - BTN_W / 2, win_height / 2., BTN_W, BTN_H};
    Rectangle quit_button_rec = (Rectangle){
        win_width / 2. - BTN_W / 2, win_height / 2. + BTN_H + 10, BTN_W, BTN_H};
    const int button_text_size = 30;

    GuiLoadStyle(ASSETS_PATH "style_dark.rgs");

    // Mainloop of the menu
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

        // Play game button
        GuiSetStyle(DEFAULT, TEXT_SIZE, button_text_size);
        if (GuiButton(play_button_rec, "Play")) {
            shouldQuit = GameLoop();
            if (gameEnd) {
                GameOverMenu();
                shouldQuit = false;
            }
            if (gamePaused) {
                PauseMenu();
                shouldQuit = false;
            }
        }


        if (GuiButton(quit_button_rec, "Quit"))
            shouldQuit = true;

        EndDrawing();
    }
}

void PauseMenu() {
    // UI Elements Setup
    // "main menu" label
    const char *label_text = "Paused";
    const int label_font_size = 50;

    Rectangle label_rec;
    label_rec.height = label_font_size;
    label_rec.width = MeasureText(label_text, label_font_size);
    label_rec.x = win_width / 2 - label_rec.width / 2;
    label_rec.y = win_height / 15;

    const float BTN_W = 150;
    const float BTN_H = 60;
    Rectangle resume_button_rec =
        (Rectangle){win_width / 2. - BTN_W / 2, win_height / 2., BTN_W, BTN_H};
    Rectangle quit_button_rec = (Rectangle){
        win_width / 2. - BTN_W / 2, win_height / 2. + BTN_H + 10, BTN_W, BTN_H};
    const int button_text_size = 30;

    GuiLoadStyle(ASSETS_PATH "style_dark.rgs");

    // Mainloop of the menu
    bool shouldQuit = false;
    while (!WindowShouldClose() && !shouldQuit) {
        // handle window resize
        if (IsWindowResized()) {
            win_width = GetScreenWidth();
            win_height = GetScreenHeight();
            label_rec.x = win_width / 2 - label_rec.width / 2;
            label_rec.y = win_height / 15;
            resume_button_rec = (Rectangle){win_width / 2 - BTN_W / 2,
                                            win_height / 2, BTN_W, BTN_H};
            quit_button_rec =
                (Rectangle){win_width / 2 - BTN_W / 2,
                            win_height / 2 + BTN_H + 10, BTN_W, BTN_H};
        }
        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        DrawText(label_text, label_rec.x, label_rec.y, label_font_size, LIME);

        // Play game button
        GuiSetStyle(DEFAULT, TEXT_SIZE, button_text_size);
        if (GuiButton(resume_button_rec, "Resume"))
        {
            shouldQuit = GameLoop();
            if (gameEnd) {
                GameOverMenu();
                shouldQuit = true;
            }
            if (gamePaused) {
                PauseMenu();
                shouldQuit = false;
            }
        }

        if (GuiButton(quit_button_rec, "Menu")) {
            shouldQuit = true;
            ResetGame(&game);
            gamePaused = false;
            gameEnd = false;
        }

        EndDrawing();
    }
}

void GameOverMenu() {
    // UI Elements Setup
    // "main menu" label
    const char *label_text = "Game Over";
    const int label_font_size = 50;

    Rectangle label_rec;
    label_rec.height = label_font_size;
    label_rec.width = MeasureText(label_text, label_font_size);
    label_rec.x = win_width / 2 - label_rec.width / 2;
    label_rec.y = win_height / 15;

    const float BTN_W = 150;
    const float BTN_H = 60;
    Rectangle play_button_rec =
        (Rectangle)
        {win_width / 2. - BTN_W / 2, win_height / 2., BTN_W, BTN_H};

    Rectangle menu_button_rec = 
        (Rectangle)
        {win_width / 2. - BTN_W / 2, win_height / 2. + BTN_H + 10, BTN_W, BTN_H};
    
    const int button_text_size = 30;

    GuiLoadStyle(ASSETS_PATH "style_dark.rgs");

    // Mainloop of the menu
    bool shouldQuit = false;
    while (!WindowShouldClose() && !shouldQuit) {
        // handle window resize
        if (IsWindowResized()) {
            win_width = GetScreenWidth();
            win_height = GetScreenHeight();

            label_rec.x = win_width / 2 - label_rec.width / 2;
            label_rec.y = win_height / 15;

            play_button_rec = 
                (Rectangle)
                {win_width / 2 - BTN_W / 2, win_height / 2, BTN_W, BTN_H};

            menu_button_rec = 
                (Rectangle)
                {win_width / 2 - BTN_W / 2, win_height / 2 + BTN_H + 10, BTN_W, BTN_H};
        }

        BeginDrawing();

        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

        DrawText(label_text, label_rec.x, label_rec.y, label_font_size, LIME);

        // Play game button
        GuiSetStyle(DEFAULT, TEXT_SIZE, button_text_size);
        if (GuiButton(play_button_rec, "Play")) {
            ResetGame(&game);
            shouldQuit = GameLoop();
        }

        // Menu button
        if (GuiButton(menu_button_rec, "Menu")) {
            shouldQuit = true;
            ResetGame(&game);
            gamePaused = false;
            gameEnd = false;
        }

        EndDrawing();
    }
}
