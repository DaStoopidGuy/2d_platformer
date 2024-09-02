#pragma once
#include "raylib.h"

typedef struct {
    Texture2D texture;
    int fps; // Number of spritesheet frames shown per second

    Rectangle *rects;
    int rects_length;
} SpriteAnimation;

void DrawSpriteAnimation(SpriteAnimation *animation, Vector2 position,
                         bool flip, Color tint);

void DrawSpriteAnimationPro(SpriteAnimation *animation, Rectangle dest,
                            Vector2 origin, float rotation, bool flip,
                            Color tint);

SpriteAnimation CreateSpriteAnimation(Texture2D texture, int fps,
                                      Rectangle rects[], int rects_length);

void DestructionSpriteAnimation(SpriteAnimation *animation);

void GetRectsArrayFromSpritesheet(Rectangle *rects, Texture2D texture,
                                  int frames);
