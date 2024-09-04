#include "player.h"
#include "common.h"
#include "game.h"
#include "input.h"
#include "sprite.h"
#include "tile.h"
#include <raylib.h>
#include <raymath.h>

Player NewPlayer(Vector2 pos) {
    Player player = {0};
    player.pos = pos;
    player.vel = Vector2Zero();
    player.facing = 1;
    player.is_on_ground = false;
    player.rec = (Rectangle){0, 0, 8, 8};

    // TODO: set proper sprites
    player.animation_sprites[PLAYER_ANIM_IDLE] = SPRITE_GHOST_STATIC;
    player.animation_sprites[PLAYER_ANIM_RUN] = SPRITE_GHOST_RUN;
    player.animation_sprites[PLAYER_ANIM_JUMP] = SPRITE_GHOST_STATIC;
    player.animation_sprites[PLAYER_ANIM_FALL] = SPRITE_GHOST_STATIC;

    return player;
}

void DestroyPlayer(Player *player) {
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

        // TODO: uncomment it, its probably a solution to a bug
        /*if (x == 0 && y == 0)*/
        /*    continue;*/

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

        /*if (x == 0 && y == 0)*/
        /*    continue;*/

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
    player->animation_state = PLAYER_ANIM_IDLE;

    // HACK: teleport back to center of screen
    if (inputs.player_teleport_back) {
        player->pos.x = (TILE_SIZE * MAP_WIDTH) / 2.0 - player->rec.width / 2.0;
        player->pos.y =
            (TILE_SIZE * MAP_HEIGHT) / 2.0 - player->rec.height / 2.0;
    }

    // Jumping on jump key
    if (inputs.player_jump && player->is_on_ground) {
        player->vel.y = -PLAYER_JUMP;
        player->is_on_ground = false;
        player->animation_state = PLAYER_ANIM_JUMP;
    }

    if (!player->is_on_ground && player->vel.y > 0)
        player->animation_state = PLAYER_ANIM_FALL;

    // Horizontal movement
    int player_x_direction = (inputs.player_right - inputs.player_left);
    player->vel.x = PLAYER_H_SPD * player_x_direction * deltaTime;

    // update player facing
    if (player_x_direction != 0)
        player->facing = player_x_direction;

    // animation updates
    if (player_x_direction && player->is_on_ground) {
        player->animation_state = PLAYER_ANIM_RUN;
    }

    // HACK: Godmode - Debug only
    if (godmode) {
        int player_y_direction = inputs.player_down - inputs.player_up;

        player->vel.y = PLAYER_H_SPD * player_y_direction * deltaTime;

        // update player position
        player->pos.x += player->vel.x;
        player->pos.y += player->vel.y;

        // also set the rect xy coords
        player->rec.x = player->pos.x;
        player->rec.y = player->pos.y;
        return;
    }

    // Gravity
    if (!player->is_on_ground) {
        player->vel.y += GRAVITY * deltaTime;
    }

    // Collision (also sets is_on_ground flag)
    {
        // Reset ground flag before checking collisions
        {
            // convert player position to tilemap coordinates
            int player_tile_y = (player->pos.y / TILE_SIZE) + 0.5f;
            int player_tile_x = (player->pos.x / TILE_SIZE) + 0.5f;
            // check the tile under player and see if it is empty
            player_tile_y += 1;
            TileType tile = tilemap[player_tile_y * MAP_WIDTH + player_tile_x];
            if (tile == TILE_EMPTY)
                player->is_on_ground = false;
        }

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
    // NOTE: casting to int to solve the animation rendering glitch
    position.x = (int)position.x;
    position.y = (int)position.y;

    DrawAnimatedSprite(player->animation_sprites[player->animation_state],
                       game.atlas, position, player->facing < 0);
}
void DrawPlayerCoords(Player *player) {
    DrawText(TextFormat("%.0f %.0f", player->pos.x, player->pos.y), 20, 20, 20,
             WHITE);
}
