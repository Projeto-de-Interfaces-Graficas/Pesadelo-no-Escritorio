#include "Enemy.h"

void Enemy_CreateEnemy(Enemy* enemy, int enemyType, int enemyPositionX, int enemyPositionY, SDL_Renderer* ren) {
    enemy->x = enemyPositionX;
    enemy->y = enemyPositionY;
    enemy->active = 1;
    enemy->type = enemyType;
    switch (enemyType) {
        case 0: // Pencil
            enemy->hp = 20; enemy->dmg = 5; enemy->def = 20; enemy->spd = 2;
            enemy->w = 16; enemy->h = 16;
            enemy->sprite = IMG_LoadTexture(ren, "assets/images/teste.png");
            break;
        case 1: // Telephone
        case 2: // Printer
        case 3: // Adhesive Tape
        case 4: // Stapler
        case 5: // Paper Shredder
    }
}

void Enemy_UpdateEnemy(Enemy* enemy) {
    if (enemy->active == 0) {
        return;
    }
    enemy->x += enemy->spd;
    enemy->y += enemy->spd;
}

void Enemy_RenderEnemy(SDL_Renderer* ren, Enemy* enemy) {
    if (enemy->active == 0) {
        return;
    }
    SDL_Rect enemyBox = {enemy->x, enemy->y, enemy->w, enemy->h};
    SDL_RenderCopy(ren, enemy->sprite, NULL, &enemyBox);
}

void Enemy_DestroyEnemy(Enemy* enemy) {
    if (enemy->sprite) {
        SDL_DestroyTexture(enemy->sprite);
        enemy->active = 0;
    }
}