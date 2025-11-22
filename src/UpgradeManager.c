#include "UpgradeManager.h"
#include "Player.h"
#include "Weapons.h"

void UpgradeManager_Init(UpgradeManager* upController, SDL_Renderer* ren) {
    upController->upgradeTitleFont = TTF_OpenFont("assets/fonts/VT323/VT323-Regular.ttf", 50);
    upController->upgradeDescriptionFont = TTF_OpenFont("assets/fonts/VT323/VT323-Regular.ttf", 30);
    upController->upgradeCount = 10;
    upController->upgradeCardTexture = IMG_LoadTexture(ren, "assets/images/menus/upgrade-option.png");
    upController->allUpgrades[0] = (Upgrade) {
        .id = 0,
        .name = "Dano +1",
        .description = "Aumenta em 5 o dano causado pelo jogador",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/dmg.png"),
    };
    
    upController->allUpgrades[1] = (Upgrade) {
        .id = 1,
        .name = "Velocidade +1",
        .description = "Aumenta a velocidade de movimento do jogador em 10%",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/spd.png"),
    };

    upController->allUpgrades[2] = (Upgrade) {
        .id = 2,
        .name = "Vida +1",
        .description = "Aumenta a vida máxima do jogador em 20",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
    };
    upController->allUpgrades[3] = (Upgrade) {
        .id = 3,
        .name = "Mochila",
        .description = "Uma mochila que pode ser usada para ser defender contra inimigos em sua frente",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
    };
    upController->allUpgrades[4] = (Upgrade) {
        .id = 4,
        .name = "Mochila - cooldown",
        .description = "Diminui o tempo para poder atacar em 0.1 segundos",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
    };
    upController->allUpgrades[5] = (Upgrade) {
        .id = 5,
        .name = "Mochila + Dano",
        .description = "Aumenta o poder de ataque em 5 dano",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
    };
    upController->allUpgrades[6] = (Upgrade) {
        .id = 6,
        .name = "Mochila + alcance",
        .description = "Aumento o alcence que a mochila acerta inimigos em 5",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
    };
    upController->allUpgrades[7] = (Upgrade) {
        .id = 7,
        .name = "Projetil",
        .description = "Aremessa projetis em direção nos inimigos",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
    };
    upController->allUpgrades[8] = (Upgrade) {
        .id = 8,
        .name = "Projetil - cooldown",
        .description = "Diminui o tempo para poder atacar em 0.1 segundos",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
    };
    upController->allUpgrades[9] = (Upgrade) {
        .id = 9,
        .name = "Projetil + Dano",
        .description = "Aumento o dano que causa em 1",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
    };
    upController->allUpgrades[10] = (Upgrade) {
        .id = 10,
        .name = "Projetil + quantidades",
        .description = "Aumenta a qauntidade de Projeteis",
        .icon = IMG_LoadTexture(ren, "assets/images/upgrades/hp.png"),
    };
}

void UpgradeManager_Destroy(UpgradeManager* upController) {
    for (int i = 0; i < upController->upgradeCount; i++) {
        if (upController->allUpgrades[i].icon) {
            SDL_DestroyTexture(upController->allUpgrades[i].icon);
        }
    }
    TTF_CloseFont(upController->upgradeTitleFont);
    TTF_CloseFont(upController->upgradeDescriptionFont);
}

void UpgradeManager_SelectUpgrades(UpgradeManager* upController) {
    for (int i = 0; i < 3; i++) {
       upController->selectedUpgrades[i] = &upController->allUpgrades[rand() % upController->upgradeCount];
    }
}

void UpgradeManager_Apply(Upgrade* upgrade) {
    switch (upgrade->id) {
        case 0: player.damage += 5; break; 
        case 1: player.movement_speed *= 1.10f; break;
        case 2: player.player_hp += 20; break;
        case 3: Select_Weapon(ARMA_CHICOTE);break;
        case 4: Upgrade_Weapon(&selecionadas[Get_Weapon_index(ARMA_CHICOTE)],1);break;
        case 5: Upgrade_Weapon(&selecionadas[Get_Weapon_index(ARMA_CHICOTE)],2);break;
        case 6: Upgrade_Weapon(&selecionadas[Get_Weapon_index(ARMA_CHICOTE)],4);break;
        case 7: Select_Weapon(ARMA_PROJETIL);break;
        case 8: Upgrade_Weapon(&selecionadas[Get_Weapon_index(ARMA_PROJETIL)],1);break;
        case 9: Upgrade_Weapon(&selecionadas[Get_Weapon_index(ARMA_PROJETIL)],2);break;
        case 10: Upgrade_Weapon(&selecionadas[Get_Weapon_index(ARMA_PROJETIL)],5);break;
    }
    printf("o upgrade foi %d\n",upgrade->id);
}

void UpgradeManager_RenderUpgradeCard(SDL_Renderer* ren, UpgradeManager* upController, Upgrade* upgrade, int x, int y) {

    // Renderização do card/frame onde o upgrade é exibido
    SDL_Rect upgradeCardBox = {x, y, 240, 340};
    SDL_RenderCopy(ren, upController->upgradeCardTexture, NULL, &upgradeCardBox);

    // Renderização do ícone do upgrade
    SDL_Rect upgradeIconBox = {x + 61, y + 43, 120, 60};
    SDL_RenderCopy(ren, upgrade->icon, NULL, &upgradeIconBox);

    // Renderização dos textos do upgrade
}
