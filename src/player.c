#include "common.h"
#include "player.h"
#include "tile.h"
#include "raymath.h"

Player NewPlayer(Vector2 pos, const char *texture_file_name)
{
    Player player = {0};
    player.pos = pos;
    player.is_on_ground = false;
    player.texture = LoadTexture(texture_file_name);
    player.rec = (Rectangle){player.pos.x, player.pos.y, player.texture.width, player.texture.height};
    return player;
}

void CollidePlayerWithTile(Player *player, Rectangle tile_rec)
{
    if (CheckCollisionRecs(player->rec, tile_rec))
    { // Collision with tile detected, stop vertical movement
        if (player->vel.y > 0 && player->pos.y + player->rec.height - player->vel.y <= tile_rec.y)
        {
            // Player is falling and collides with the top of the platform
            player->pos.y = tile_rec.y - player->rec.height;
            player->vel.y = 0;
            player->is_on_ground = true;
        }
        else if (player->vel.y < 0 && player->pos.y - player->vel.y >= tile_rec.y + tile_rec.height)
        {
            // Player is jumping and collides with the bottom of the platform
            player->pos.y = tile_rec.y + tile_rec.height;
            player->vel.y = 0;
        }
        else if (player->vel.x > 0 && player->pos.x + player->rec.width - player->vel.x <= tile_rec.x)
        {
            // Player is moving right and collides with the left side of the platform
            player->pos.x = tile_rec.x - player->rec.width;
        }
        else if (player->vel.x < 0 && player->pos.x - player->vel.x >= tile_rec.x + tile_rec.width)
        {
            // Player is moving left and collides with the right side of the platform
            player->pos.x = tile_rec.x + tile_rec.width;
        }
    }
}
void UpdatePlayer(Player *player, float deltaTime, int tilemap[][25], int rows, int cols, bool godmode)
{
    // Horizontal movement
    bool right_key = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
    bool left_key = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
    int player_x_direction = (right_key - left_key);
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

        if (!player->is_on_ground)
            player->vel.y += GRAVITY * deltaTime;

        for (int y = 0; y < rows; y++)
        {
            for (int x = 0; x < cols; x++)
            {
                if (tilemap[y][x] != 0) // Check for non-empty tiles
                    CollidePlayerWithTile(player, (Rectangle){x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE});
            }
        }
    }

    // update player position
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    // update the player collider rectangle
    player->rec.x = player->pos.x;
    player->rec.y = player->pos.y;
}
void DrawPlayer(Player *player)
{
    DrawTextureV(player->texture, player->pos, WHITE);
}
void DrawPlayerCoords(Player *player)
{
    DrawText(TextFormat("%.0f %.0f", player->pos.x, player->pos.y), 20, 20, 20, WHITE);
}