#ifndef UPGRADE_H
#define UPGRADE_H

#include <SDL2/SDL.h>

typedef struct {
    int id;
    const char* title;
    const char* description;
    SDL_Texture* icon;
} Upgrade;

#endif