#include <stdio.h>
#include "raylib.h"
#include "raymath.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#define GRAVITY 11

#define PLAYER_H_SPD 200
#define PLAYER_JUMP 4

typedef struct
{
    Vector2 pos;
    Vector2 vel;
    bool can_jump;
    Texture2D texture;
    Rectangle src_rect;
    Rectangle dest_rect;
} Player;

void UpdatePlayer(Player *player, float deltaTime);
void DrawPlayer(Player *player);
void DrawPlayerCoords(Player *player);

int main(void)
{
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "2d Platformer");
    SetTargetFPS(60);

    // player
    Player player = {0};
    player.pos = (Vector2){400, 300};
    player.can_jump = true;
    player.texture = LoadTexture("resources/player.png");
    player.src_rect = (Rectangle){.height = player.texture.height, .width = player.texture.width, .x = 0, .y = 0};
    player.dest_rect = (Rectangle){.height = 32, .width = 32, .x = player.pos.x, .y = player.pos.y};

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        // UPDATE STUFF
        UpdatePlayer(&player, deltaTime);

        // RENDER STUFF
        BeginDrawing();
        ClearBackground(DARKGRAY); // clear the screen

        DrawText("Congrats! You created your first game!", 190, 200, 20, WHITE);
        // debug
        DrawFPS(WIN_WIDTH - 100, 30);
        DrawPlayerCoords(&player);
        // player
        DrawPlayer(&player);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void UpdatePlayer(Player *player, float deltaTime)
{
    // Horizontal movement
    int player_x_direction = ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) - (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)));
    player->vel.x = PLAYER_H_SPD * player_x_direction * deltaTime;

    // Vertical movement
    if (IsKeyDown(KEY_SPACE) && player->can_jump)
    {
        player->vel.y = -PLAYER_JUMP;
        player->can_jump = false;
    }

    if (player->pos.y > 400)
    {
        player->vel.y = 0;
        player->pos.y = 400;
        player->can_jump = true;
    }
    else if (player->pos.y < 400)
        player->vel.y += GRAVITY * deltaTime;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
}
void DrawPlayer(Player *player)
{
    DrawTextureEx(player->texture, player->pos, 0, 4, WHITE);
}
void DrawPlayerCoords(Player *player)
{
    DrawText(TextFormat("%.0f %.0f", player->pos.x, player->pos.y), 20, 20, 20, WHITE);
}