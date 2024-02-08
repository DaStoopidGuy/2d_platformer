#include "common.h"
#include "player.h"

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
    DrawTextureV(player->texture, player->pos, WHITE);
}
void DrawPlayerCoords(Player *player)
{
    DrawText(TextFormat("%.0f %.0f", player->pos.x, player->pos.y), 20, 20, 20, WHITE);
}