#include "player.h"
#include "animation.h"
#include "common.h"
#include "input.h"
#include "tile.h"
#include <raylib.h>

Player NewPlayer(Vector2 pos, const char *texture_file_name) {
    Player player = {0};
    player.pos = pos;
    player.is_on_ground = false;
    // HACK: sprite animation mess
    Texture2D spritesheet = LoadTexture(ASSETS_PATH "player-sheet.png");
    int frames = 5;

    player.animation = CreateSpriteAnimationFromSpritesheet(spritesheet, frames, 8);
    player.rec = player.animation.rects[0];
    player.facing = 1;
    return player;
}

void DestroyPlayer(Player *player) {
    DestructionSpriteAnimation(&player->animation);
}

void SetPlayerRecPosToPlayerPos(Player *player) {
    player->rec.x = player->pos.x;
    player->rec.y = player->pos.y;
}

void CollidePlayerWithTileRecX(Player *player, Rectangle tile_rec) {
    if (CheckCollisionRecs(player->rec, tile_rec)) {
        if (player->vel.x >
            0) // moving right and collides with left side of tile
            player->pos.x = tile_rec.x - player->rec.width;

        else if (player->vel.x <
                 0) // moving left and collides with right side of tile
            player->pos.x = tile_rec.x + tile_rec.width;

        player->vel.x = 0;
        SetPlayerRecPosToPlayerPos(player);
    }
}

void CollidePlayerWithTileRecY(Player *player, Rectangle tile_rec) {
    if (CheckCollisionRecs(player->rec, tile_rec)) {
        if (player->vel.y >
            0) // player is falling and collides with top of tile
        {
            player->pos.y = tile_rec.y - player->rec.height;
            player->is_on_ground = true;
        } else if (player->vel.y <
                   0) // player is jumping and collides with the bottom of tile
            player->pos.y = tile_rec.y + tile_rec.height;

        player->vel.y = 0;
        SetPlayerRecPosToPlayerPos(player);
    }
}

void CollidePlayerWithTilemapX(Player *player, int *tilemap) {
    int tiles_around[9][2];
    GetTilesAround(tiles_around, player->pos);

    for (int i = 0; i < 9; i++) {
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

void CollidePlayerWithTilemapY(Player *player, int *tilemap) {
    int tiles_around[9][2];
    GetTilesAround(tiles_around, player->pos);

    for (int i = 0; i < 9; i++) {
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

void UpdatePlayer(Player *player, float deltaTime, int *tilemap, bool godmode) {

    // HACK: teleport back to center of screen
    if (inputs.player_teleport_back) {
        player->pos.x = (TILE_SIZE * MAP_WIDTH) / 2.0 - player->rec.width / 2.0;
        player->pos.y =
            (TILE_SIZE * MAP_HEIGHT) / 2.0 - player->rec.height / 2.0;
    }

    // Horizontal movement
    int player_x_direction = (inputs.player_right - inputs.player_left);
    player->vel.x = PLAYER_H_SPD * player_x_direction * deltaTime;

    // update player facing
    if (player_x_direction != 0)
        player->facing = player_x_direction;

    if (godmode) {
        int player_y_direction = inputs.player_down - inputs.player_up;

        player->vel.y = PLAYER_H_SPD * player_y_direction * deltaTime;

        // update player position
        player->pos.x += player->vel.x;
        player->pos.y += player->vel.y;
    } else {
        // Jumping on jump key
        if (inputs.player_jump && player->is_on_ground) {
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
void DrawPlayer(Player *player) {
    Vector2 position = player->pos;
    // NOTE: casting to int is to solve the animation rendering glitch
    position.x = (int)position.x;
    position.y = (int)position.y;
    DrawSpriteAnimation(&player->animation, position, player->facing < 0,
                        WHITE);

    // TODO: this code below seems to mess with Godmode! and it doesn't work lol
    // but rendering animations is fine

    /*Rectangle dest = player->rec;*/
    /*dest.x = (int) dest.x;*/
    /*dest.y = (int) dest.y;*/
    /*DrawSpriteAnimationPro(&player->animation, dest, Vector2Zero(), 0.0f,
     * player->facing < 0, WHITE);*/
}
void DrawPlayerCoords(Player *player) {
    DrawText(TextFormat("%.0f %.0f", player->pos.x, player->pos.y), 20, 20, 20,
             WHITE);
}
