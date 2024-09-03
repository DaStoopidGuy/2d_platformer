#include "animation.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

void DrawSpriteAnimationPro(SpriteAnimation *animation, Rectangle dest,
                            Vector2 origin, float rotation, bool flip,
                            Color tint) {
    int index = (int)(GetTime() * animation->fps) % animation->rects_length;
    Rectangle source_rect = animation->rects[index];
    if (flip) {
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

SpriteAnimation CreateSpriteAnimationFromSpritesheet(Texture2D texture,
                                                     int frames, int fps) {
    SpriteAnimation animation = {
        .texture = texture,
        .fps = fps,
        .rects_length = frames,
        .rects = NULL,
    };

    animation.rects = GetRectsArrayFromSpritesheet(texture, frames);
    if (animation.rects == NULL) {
        TraceLog(LOG_FATAL, "animation.rects not allocated!");
        animation.rects_length = 0;
        return animation;
    }

    return animation;
}

void DestructionSpriteAnimation(SpriteAnimation *animation) {
    free(animation->rects);
}

Rectangle *GetRectsArrayFromSpritesheet(Texture2D texture, int frames) {
    Rectangle *rects = (Rectangle *)malloc(sizeof(Rectangle) * frames);
    if (rects == NULL) {
        TraceLog(LOG_FATAL,
                 "GetRectsArrayFromSpritesheet() memory allocation failed!");
        return rects;
    }

    for (int i = 0; i < frames; i++) {
        rects[i] = (Rectangle){.x = (float)i * texture.width / frames,
                               .y = 0,
                               .width = (float)texture.width / frames,
                               .height = texture.height};
    }
    return rects;
}
