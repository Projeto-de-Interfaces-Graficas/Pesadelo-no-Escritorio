#ifndef EXPERIENCEMANAGER_H
#define EXPERIENCEMANAGER_H

#include "Experience.h"

#define MAX_XP_POINTS 1000

typedef struct {
    ExperiencePoint xpPoints[MAX_XP_POINTS]; 
    SDL_Texture* xpTextures[3]; 
    int xpSpriteSize;
} ExperienceManager;

void ExperienceManager_Init(ExperienceManager* xpController, SDL_Renderer* ren, int size);
void ExperienceManager_CreateXp(ExperienceManager* xpController, ExperienceType type, int x, int y);
void ExperienceManager_RenderXp(ExperienceManager* xpController, SDL_Renderer* ren);
void ExperienceManager_Destroy(ExperienceManager* xpController);

#endif