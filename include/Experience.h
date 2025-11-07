#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include <SDL2/SDL.h>

typedef enum {
    XP_SMALL,
    XP_MEDIUM,
    XP_LARGE
} ExperienceType;

typedef struct {
    int amount;
    int active;
    SDL_Texture* sprite;
    SDL_Rect renderBox;
    SDL_Rect hitBox;
    ExperienceType type;
} ExperiencePoint;

void Experience_CreateXp(ExperiencePoint* xp, ExperienceType type, int x, int y, int size, SDL_Texture* sprite);

#endif