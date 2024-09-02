#include "input.h"
#include <raylib.h>

/*typedef struct {*/
/*    bool toggle_debug;*/
/*    bool game_exit_to_menu;*/
/*    bool toggle_godmode;*/
/*    bool player_up;*/
/*    bool player_down;*/
/*    bool player_right;*/
/*    bool player_left;*/
/*    bool player_jump;*/
/*    bool player_teleport_back;*/
/*} Inputs;*/
Inputs inputs;

void GetInputs() {
    inputs.toggle_debug = IsKeyPressed(KEY_BACKSLASH);
    inputs.game_exit_to_menu = IsKeyPressed(KEY_ESCAPE);
    inputs.toggle_godmode = IsKeyPressed(KEY_G);
    inputs.player_up = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
    inputs.player_down = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_D);
    inputs.player_right = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
    inputs.player_left = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
    inputs.player_jump =
        IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
    inputs.player_teleport_back = IsKeyPressed(KEY_ZERO);
}

