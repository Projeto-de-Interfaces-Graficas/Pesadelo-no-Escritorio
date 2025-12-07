#include "UpgradeManager.h"
#include "Player.h"
#include "Weapons.h"
#include "Fonts.h"

void UpgradeManager_Init(UpgradeManager *upController, SDL_Renderer *ren)
{
    upController->upgradeCount = 5;
    upController->upgradeCardTexture = IMG_LoadTexture(ren, "assets/images/menus/upgrade-option.png");
    upController->allUpgrades[0] = (Upgrade){
        .id = 0,
        .title = "Dano +1",
        .description = "Aumenta em 5 o dano causado pelo jogador",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/dmg.png"),
    };

    upController->allUpgrades[1] = (Upgrade){
        .id = 1,
        .title = "Velocidade +1",
        .description = "Aumenta a velocidade de movimento do jogador em 10%",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/spd.png"),
    };

    upController->allUpgrades[2] = (Upgrade){
        .id = 2,
        .title = "Vida +1",
        .description = "Aumenta a vida máxima do jogador em 20",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
    };

    upController->allUpgrades[3] = (Upgrade){
        .id = 3,
        .title = "Mochila",
        .description = "Uma mochila que pode ser usada para ser defender contra inimigos em sua frente",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
    };

    upController->allUpgrades[4] = (Upgrade){
        .id = 4,
        .title = "Projetil",
        .description = "Aremessa projetis em direção nos inimigos",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
    };
}

void UpgradeManager_Destroy(UpgradeManager *upController)
{
    for (int i = 0; i < upController->upgradeCount; i++)
    {
        if (upController->allUpgrades[i].icon)
        {
            SDL_DestroyTexture(upController->allUpgrades[i].icon);
        }
    }
}

void UpgradeManager_SelectUpgrades(UpgradeManager *upController)
{
    int addedUpgrades = 0;
    while (addedUpgrades < 3) {
        int repeatedUpgrade = 0;
        Upgrade* up = &upController->allUpgrades[rand() % upController->upgradeCount];
        if (addedUpgrades > 0) {
            for (int i = 0; i < addedUpgrades; i++) {
                if (upController->selectedUpgrades[i]->id == up->id) {
                    repeatedUpgrade = 1;
                    break;
                }
            }
            if (!repeatedUpgrade) {
                upController->selectedUpgrades[addedUpgrades] = up;
                addedUpgrades++;
            } else {
                printf("Preveni que dois upgrades iguais fossem escolhidos!\n");
            }
        } else {
            upController->selectedUpgrades[addedUpgrades] = up;
            addedUpgrades++;
        }
    }
}

void UpgradeManager_Apply(SDL_Renderer *ren,UpgradeManager* upController,Upgrade *upgrade)
{
    switch (upgrade->id)
    {
    case 0:
        player.damage += 5;
        break;
    case 1:
        player.movement_speed *= 1.10f;
        break;
    case 2:
        player.player_hp += 20;
        break;
    case 3:
        Select_Weapon(Mochila);
        UpgradeManager_RemoveSelectWeapon(upController, 3);
        upController->allUpgrades[upController->upgradeCount] = (Upgrade){
            .id = 5,
            .title = "Mochila - cooldown",
            .description = "Diminui o tempo para poder atacar em 0.1 segundos",
            .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
        };

        upController->allUpgrades[upController->upgradeCount+1] = (Upgrade){
            .id = 6,
            .title = "Mochila + Dano",
            .description = "Aumenta o poder de ataque em 5 dano",
            .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
        };
        upController->allUpgrades[upController->upgradeCount+2] = (Upgrade){
            .id = 7,
            .title = "Mochila + alcance",
            .description = "Aumento o alcence que a mochila acerta inimigos em 5",
            .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
        };
        upController->upgradeCount += 3;
        break;
    case 4:
        Select_Weapon(Elastico);
        UpgradeManager_RemoveSelectWeapon(upController, 4);
        upController->allUpgrades[upController->upgradeCount] = (Upgrade){
            .id = 8,
            .title = "Projetil - cooldown",
            .description = "Diminui o tempo para poder atacar em 0.1 segundos",
            .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
        };

        upController->allUpgrades[upController->upgradeCount+1] = (Upgrade){
            .id = 9,
            .title = "Projetil + Dano",
            .description = "Aumento o dano que causa em 1",
            .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
        };
        upController->allUpgrades[upController->upgradeCount+2] = (Upgrade){
            .id = 10,
            .title = "Projetil + quantidades",
            .description = "Aumenta a qauntidade de Projeteis",
            .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
        };
        upController->upgradeCount += 3;
        break;
    case 5:
        Upgrade_Weapon(&selecionadas[Get_Weapon_index(Mochila)], 1);
        break;
    case 6:
        Upgrade_Weapon(&selecionadas[Get_Weapon_index(Mochila)], 2);
        break;
    case 7:
        Upgrade_Weapon(&selecionadas[Get_Weapon_index(Mochila)], 4);
        break;
    case 8:
        Upgrade_Weapon(&selecionadas[Get_Weapon_index(Elastico)], 1);
        break;
    case 9:
        Upgrade_Weapon(&selecionadas[Get_Weapon_index(Elastico)], 2);
        break;
    case 10:
        Upgrade_Weapon(&selecionadas[Get_Weapon_index(Elastico)], 5);
        break;
    }
    printf("o upgrade foi %d\n", upgrade->id);
}

void UpgradeManager_RenderUpgradeCard(SDL_Renderer *ren, UpgradeManager *upController, Upgrade *upgrade, int x, int y, int selectedUpgrade)
{

    SDL_Color textColor = {0x00, 0x00, 0x00, 0xFF};

    // Card base
    SDL_Rect cardBox;
    if (upgrade->id == upController->selectedUpgrades[selectedUpgrade]->id) {
        cardBox.x = x - 10;
        cardBox.y = y - 10;
        cardBox.w = 260;
        cardBox.h = 360;
    } else {
        cardBox.x = x;
        cardBox.y = y;
        cardBox.w = 240;
        cardBox.h = 340;
    }
    SDL_RenderCopy(ren, upController->upgradeCardTexture, NULL, &cardBox);

    // Ícone
    SDL_Rect iconBox = {x + 60, y + 42, 120, 60};
    SDL_RenderCopy(ren, upgrade->icon, NULL, &iconBox);

    // Título
    int titleMaxW = 160, titleMaxH = 40;
    TTF_Font *titleFont = Fonts_FitTextInRect(upgrade->title, titleMaxW, titleMaxH, 50);
    SDL_Surface *titleSurface = TTF_RenderUTF8_Blended_Wrapped(titleFont, upgrade->title, textColor, titleMaxW);
    SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(ren, titleSurface);
    int titleBoxX = (x + 40) + (titleMaxW - titleSurface->w) / 2;
    int titleBoxY = (y + 112) + (titleMaxH - titleSurface->h) / 2;
    SDL_Rect titleBox = {titleBoxX, titleBoxY, titleSurface->w, titleSurface->h};
    SDL_RenderCopy(ren, titleTexture, NULL, &titleBox);
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);

    // Descrição
    int descriptionMaxW = 160, descriptionMaxH = 130;
    TTF_Font *descriptionFont = Fonts_FitTextInRect(upgrade->description, descriptionMaxW, descriptionMaxH, 50);
    SDL_Surface *descriptionSurface = TTF_RenderUTF8_Blended_Wrapped(descriptionFont, upgrade->description, textColor, descriptionMaxW);
    SDL_Texture *descriptionTexture = SDL_CreateTextureFromSurface(ren, descriptionSurface);
    int descriptionBoxX = (x + 40) + (descriptionMaxW - descriptionSurface->w) / 2;
    int descriptionBoxY = (y + 161) + (descriptionMaxH - descriptionSurface->h) / 2;
    SDL_Rect descriptionBox = {descriptionBoxX, descriptionBoxY, descriptionSurface->w, descriptionSurface->h};
    SDL_RenderCopy(ren, descriptionTexture, NULL, &descriptionBox);
    SDL_FreeSurface(descriptionSurface);
    SDL_DestroyTexture(descriptionTexture);
}

void UpgradeManager_RemoveSelectWeapon(UpgradeManager *upController, int id)
{
    for (int i = 0; i < upController->upgradeCount; i++)
    {
        if (upController->allUpgrades[i].id == id)
        {
            upController->allUpgrades[i] = upController->allUpgrades[upController->upgradeCount - 1];
            upController->upgradeCount -= 1;
        }
    }
}
