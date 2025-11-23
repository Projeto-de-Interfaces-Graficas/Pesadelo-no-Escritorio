#ifndef UPGRADEMANAGER_H
#define UPGRADEMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Upgrade.h"

#define MAX_UPGRADES 60

typedef struct {
    Upgrade allUpgrades[MAX_UPGRADES];
    Upgrade* selectedUpgrades[3];
    int upgradeCount;
    SDL_Texture* upgradeCardTexture;
    TTF_Font* upgradeTitleFont;
    TTF_Font* upgradeDescriptionFont;
} UpgradeManager;

void UpgradeManager_Init(UpgradeManager* upController, SDL_Renderer* ren);
void UpgradeManager_Destroy(UpgradeManager* upController);
void UpgradeManager_SelectUpgrades(UpgradeManager* upController);
void UpgradeManager_Apply(Upgrade* up);
void UpgradeManager_RenderUpgradeCard(SDL_Renderer* ren, UpgradeManager* upController, Upgrade* up, int x, int y);
TTF_Font* FitTextInRect(const char* fontPath, const char* text, int maxW, int maxH, int initialSize);

#endif