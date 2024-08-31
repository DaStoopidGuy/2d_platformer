#include "game.h"
#include "menu.h"

float win_width = WIN_WIDTH;
float win_height = WIN_HEIGHT;

int main(void) {
    // Initialization
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(win_width, win_height, "2d Platformer");
    InitAudioDevice();
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    InitGameData(&game);

    // Display Main menu
    MainMenu();

    // Cleanup
    FreeGameData(&game);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
