#include "player.h"
#include "common.h"
#include "tile.h"
#include <raylib.h>

Player NewPlayer(Vector2 pos, const char *texture_file_name)
{
    Player player = {0};
    player.pos = pos;
    player.is_on_ground = false;
    player.texture = LoadTexture(texture_file_name);
    player.rec = (Rectangle){player.pos.x, player.pos.y, player.texture.width, player.texture.height};
    return player;
}

void SetPlayerRecPosToPlayerPos(Player *player)
{
    player->rec.x = player->pos.x;
    player->rec.y = player->pos.y;
}

void CollidePlayerWithTileRecX(Player *player, Rectangle tile_rec)
{
    if (CheckCollisionRecs(player->rec, tile_rec))
    {
        if (player->vel.x > 0) // moving right and collides with left side of tile
            player->pos.x = tile_rec.x - player->rec.width;

        else if (player->vel.x < 0) // moving left and collides with right side of tile
            player->pos.x = tile_rec.x + tile_rec.width;

        player->vel.x = 0;
        SetPlayerRecPosToPlayerPos(player);
    }
}

void CollidePlayerWithTileRecY(Player *player, Rectangle tile_rec)
{
    if (CheckCollisionRecs(player->rec, tile_rec))
    {
        if (player->vel.y > 0) // player is falling and collides with top of tile
        {
            player->pos.y = tile_rec.y - player->rec.height;
            player->is_on_ground = true;
        }
        else if (player->vel.y < 0) // player is jumping and collides with the bottom of tile
            player->pos.y = tile_rec.y + tile_rec.height;

        player->vel.y = 0;
        SetPlayerRecPosToPlayerPos(player);
    }
}

void CollidePlayerWithTilemapX(Player *player, int *tilemap)
{
    int tiles_around[9][2];
    GetTilesAround(tiles_around, player->pos);

    for (int i = 0; i < 9; i++)
    {
        int x = tiles_around[i][0];
        int y = tiles_around[i][1];

        // get the rectangle for the tile
        Rectangle tile_rect = (Rectangle){
            x * TILE_SIZE,
            y * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE,
        };
        if (tilemap[y * MAP_WIDTH + x] != TILE_EMPTY)
            CollidePlayerWithTileRecX(player, tile_rect);
    }
}

void CollidePlayerWithTilemapY(Player *player, int *tilemap)
{
    int tiles_around[9][2];
    GetTilesAround(tiles_around, player->pos);

    for (int i = 0; i < 9; i++)
    {
        int x = tiles_around[i][0];
        int y = tiles_around[i][1];

        // get the rectangle for the tile
        Rectangle tile_rect = (Rectangle){
            x * TILE_SIZE,
            y * TILE_SIZE,
            TILE_SIZE,
            TILE_SIZE,
        };
        if (tilemap[y * MAP_WIDTH + x] != TILE_EMPTY)
            CollidePlayerWithTileRecY(player, tile_rect);
    }
}

void UpdatePlayer(Player *player, float deltaTime, int *tilemap, bool godmode)
{
    // HACK: teleport back to center of screen
    if (IsKeyPressed(KEY_ZERO))
    {
        player->pos.x = WIN_WIDTH/2 - player->rec.width/2;
        player->pos.y = WIN_HEIGHT/2 - player->rec.height/2;
    }

    bool right_key = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
    bool left_key = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
    bool space_key = IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);

    // Horizontal movement
    int player_x_direction = (right_key - left_key);
    player->vel.x = PLAYER_H_SPD * player_x_direction * deltaTime;

    if (godmode)
    {
        int player_y_direction = ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) - (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)));
        player->vel.y = PLAYER_H_SPD * player_y_direction * deltaTime;

        // update player position
        player->pos.x += player->vel.x;
        player->pos.y += player->vel.y;
    }
    else
    {
        // Jumping on jump key
        if (space_key && player->is_on_ground)
        {
            player->vel.y = -PLAYER_JUMP;
            player->is_on_ground = false;
        }
        // Gravity
        if (!player->is_on_ground)
            player->vel.y += GRAVITY * deltaTime;

        // Reset ground flag before checking collisions
        player->is_on_ground = false;

        // Horizontal movement and Collison detection
        player->pos.x += player->vel.x;
        player->rec.x = player->pos.x;
        CollidePlayerWithTilemapX(player, tilemap);

        // Vertical movement and Collision detection
        player->pos.y += player->vel.y;
        player->rec.y = player->pos.y;
        CollidePlayerWithTilemapY(player, tilemap);
    }
}
void DrawPlayer(Player *player)
{
    DrawTextureV(player->texture, player->pos, WHITE);
}
void DrawPlayerCoords(Player *player)
{
    DrawText(TextFormat("%.0f %.0f", player->pos.x, player->pos.y), 20, 20, 20, WHITE);
}
