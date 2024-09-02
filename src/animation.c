#include "animation.h"
#include "raylib.h"
#include <stdlib.h>

void DrawSpriteAnimationPro(SpriteAnimation *animation, Rectangle dest,
                            Vector2 origin, float rotation, bool flip, Color tint) {
    int index = (int)(GetTime() * animation->fps) % animation->rects_length;
    Rectangle source_rect = animation->rects[index];
    if (flip)
    {
        source_rect.width = -source_rect.width;
    }
    DrawTexturePro(animation->texture, source_rect, dest, origin, rotation,
                   tint);
}

void DrawSpriteAnimation(SpriteAnimation *animation, Vector2 position,
                         bool flip, Color tint) {
    int index = (int)(GetTime() * animation->fps) % animation->rects_length;
    Rectangle source_rect = animation->rects[index];
    if (flip) {
        source_rect.width = -source_rect.width;
    }
    DrawTextureRec(animation->texture, source_rect, position, tint);
}

SpriteAnimation CreateSpriteAnimation(Texture2D texture, int fps,
                                      Rectangle *rects, int rects_length) {
    SpriteAnimation animation = {.texture = texture,
                                 .fps = fps,
                                 .rects = NULL,
                                 .rects_length = rects_length};

    Rectangle *mem = (Rectangle *)malloc(sizeof(Rectangle) * rects_length);
    if (mem == NULL) {
        TraceLog(LOG_FATAL,
                 "CreateSpriteAnimation() memory allocation failed!");
        animation.rects_length = 0;
        return animation;
    }

    animation.rects = mem;
    for (int i = 0; i < rects_length; i++) {
        animation.rects[i] = rects[i];
    }

    return animation;
}

void DestructionSpriteAnimation(SpriteAnimation *animation) {
    free(animation->rects);
}

void GetRectsArrayFromSpritesheet(Rectangle *rects, Texture2D texture,
                                  int frames) {
    for (int i = 0; i < frames; i++) {
        rects[i] = (Rectangle){.x = i * texture.width / frames,
                               .y = 0,
                               .width = texture.width / frames,
                               .height = texture.height};
    }
}
