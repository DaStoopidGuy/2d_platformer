#include "common.h"
#include "player.h"
#include "tile.h"
#include "raymath.h"

Player NewPlayer(Vector2 pos, const char *texture_file_name)
{
    Player player = {0};
    player.pos = pos;
    player.is_on_ground = true;
    player.texture = LoadTexture(texture_file_name);
    return player;
}

void UpdatePlayer(Player *player, float deltaTime, int tilemap[][25], int rows, int cols, bool godmode)
{
    // Horizontal movement
    int player_x_direction = ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) - (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)));
    player->vel.x = PLAYER_H_SPD * player_x_direction * deltaTime;

    if (godmode)
    {
        int player_y_direction = ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) - (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)));
        player->vel.y = PLAYER_H_SPD * player_y_direction * deltaTime;
    }
    else
    {
        // Vertical movement
        if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && player->is_on_ground)
        {
            player->vel.y = -PLAYER_JUMP;
            player->is_on_ground = false;
        }

        // remove later
        if (player->pos.y > 400)
        {
            player->vel.y = 0;
            player->pos.y = 400;
            player->is_on_ground = true;
        }
        else if (player->pos.y < 400)
            player->vel.y += GRAVITY * deltaTime;
    }

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
}
void DrawPlayer(Player *player)
{
    DrawTextureV(player->texture, player->pos, WHITE);
}
void DrawPlayerCoords(Player *player)
{
    DrawText(TextFormat("%.0f %.0f", player->pos.x, player->pos.y), 20, 20, 20, WHITE);
}