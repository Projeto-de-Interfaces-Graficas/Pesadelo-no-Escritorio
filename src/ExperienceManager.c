#include "ExperienceManager.h"
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>

void ExperienceManager_Init(ExperienceManager* xpController, SDL_Renderer* ren, int size) {
    xpController->xpTextures[XP_SMALL] = IMG_LoadTexture(ren, "assets/images/xp-small.png");
    xpController->xpTextures[XP_MEDIUM] = IMG_LoadTexture(ren, "assets/images/xp-medium.png");
    xpController->xpTextures[XP_LARGE] = IMG_LoadTexture(ren, "assets/images/xp-large.png");
    xpController->xpSpriteSize = size;
    for (int i = 0; i < MAX_XP_POINTS; i++) {
        xpController->xpPoints[i].active = 0;
    }
}

int ExperienceManager_DropXp(int baseDropChance, float luckMultiplier) {
    float minimunRollToDrop = baseDropChance * luckMultiplier;
    int roll = rand() % 100;
    return roll > minimunRollToDrop;
    
}

void ExperienceManager_CreateXp(ExperienceManager* xpController, ExperienceType type, int x, int y) {
    for (int i = 0; i < MAX_XP_POINTS; i++) {
        if (!xpController->xpPoints[i].active) {
            Experience_CreateXp(&xpController->xpPoints[i], type, x, y, xpController->xpSpriteSize, xpController->xpTextures[type]);
            break;
        }
    }
}

void ExperienceManager_RenderXp(ExperienceManager* xpController, SDL_Renderer* ren) {
    for (int i = 0; i < MAX_XP_POINTS; i++) {
        if (xpController->xpPoints[i].active) {
            SDL_RenderCopy(ren, xpController->xpPoints[i].sprite, NULL, &xpController->xpPoints[i].renderBox);
        }
    }
}

void ExperienceManager_Destroy(ExperienceManager* xpController) {
    for (int i = 0; i < 3; i++) {
        SDL_DestroyTexture(xpController->xpTextures[i]);
    }
}