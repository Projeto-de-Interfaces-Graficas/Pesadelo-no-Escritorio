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
        .title = "Passe da Academia",
        .description = "Aumenta o dano causado pelos ataques do funcionário em 5",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/passe-academia.png"),
    };

    upController->allUpgrades[1] = (Upgrade){
        .id = 1,
        .title = "Cafezinho",
        .description = "Aumenta a velocidade de movimento do funcionário em 10%",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/cafezinho.png"),
    };

    upController->allUpgrades[2] = (Upgrade){
        .id = 2,
        .title = "Terno Corporativo",
        .description = "Aumenta a vida máxima do funcionário em 20",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/terno.png"),
    };

    upController->allUpgrades[3] = (Upgrade){
        .id = 3,
        .title = "Mochila",
        .description = "Uma mochila que pode ser usada para se defender dos inimigos à sua frente",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/mochila.png"),
    };

    upController->allUpgrades[4] = (Upgrade){
        .id = 4,
        .title = "Elástico",
        .description = "Aremessa elásticos na direção do inimigo mais próximo",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/elastico.png"),
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
                printf("Previni que dois upgrades iguais fossem escolhidos!\n");
            }
        } else {
            upController->selectedUpgrades[addedUpgrades] = up;
            addedUpgrades++;
        }
    }
}

void UpgradeManager_Apply(SDL_Renderer *ren, UpgradeManager* upController, Upgrade *upgrade)
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
        Select_Weapon(Mochila, ren);
        UpgradeManager_RemoveSelectWeapon(upController, 3);
        upController->allUpgrades[upController->upgradeCount] = (Upgrade){
            .id = 5,
            .title = "Manejo Ágil",
            .description = "Diminui o tempo de espera entre os ataques da mochila em 0.1 segundos",
            .icon = IMG_LoadTexture(ren, "assets/images/upgrades/mochila.png"),
        };

        upController->allUpgrades[upController->upgradeCount+1] = (Upgrade){
            .id = 6,
            .title = "Costura Reforçada",
            .description = "Aumenta o dano dos ataques da mochila em 5",
            .icon = IMG_LoadTexture(ren, "assets/images/upgrades/mochila.png"),
        };
        upController->allUpgrades[upController->upgradeCount+2] = (Upgrade){
            .id = 7,
            .title = "Alças Esticáveis",
            .description = "Aumenta o alcance dos ataques da mochila",
            .icon = IMG_LoadTexture(ren, "assets/images/upgrades/mochila.png"),
        };
        upController->upgradeCount += 3;
        break;
    case 4:
        Select_Weapon(Elastico, ren);
        UpgradeManager_RemoveSelectWeapon(upController, 4);
        upController->allUpgrades[upController->upgradeCount] = (Upgrade){
            .id = 8,
            .title = "Agrupamento de Documentos",
            .description = "Diminui o tempo de espera entre os disparos dos elásticos em 0.1 segundos",
            .icon = IMG_LoadTexture(ren, "assets/images/upgrades/elastico.png"),
        };

        upController->allUpgrades[upController->upgradeCount+1] = (Upgrade){
            .id = 9,
            .title = "Borracha de Qualidade",
            .description = "Aumenta o dano causado pelos elásticos em 5",
            .icon = IMG_LoadTexture(ren, "assets/images/upgrades/elastico.png"),
        };
        upController->allUpgrades[upController->upgradeCount+2] = (Upgrade){
            .id = 10,
            .title = "Nova Remessa",
            .description = "Aumenta a quantidade de elásticos disparados em 1",
            .icon = IMG_LoadTexture(ren, "assets/images/upgrades/elastico.png"),
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
    int iconBox_w = 64, iconBox_h = 64;
    int iconBox_x = ((cardBox.w / 2) - (iconBox_w / 2)) + cardBox.x;
    int iconBox_y = cardBox.y + 50;
    SDL_Rect iconBox = {iconBox_x, iconBox_y, iconBox_w, iconBox_h};
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
