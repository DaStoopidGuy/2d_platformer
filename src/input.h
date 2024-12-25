#pragma once

#include <stdbool.h>

typedef struct {
    bool toggle_debug;
    bool game_exit_to_menu;
    bool game_pause;
    bool toggle_godmode;
    bool player_up;
    bool player_down;
    bool player_right;
    bool player_left;
    bool player_jump;
    bool player_teleport_back;
} Inputs;

extern Inputs inputs;

void GetInputs();
