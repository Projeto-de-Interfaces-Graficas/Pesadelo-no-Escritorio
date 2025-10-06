#include "Enemy.h"

Enemy enemies[MAX_ENEMIES];

void Enemy_CreateEnemy(Enemy* enemy, int enemyType, int enemyPositionX, int enemyPositionY, SDL_Texture* image) {
    enemy->x = enemyPositionX;
    enemy->y = enemyPositionY;
    enemy->active = 1;
    enemy->type = enemyType;
    enemy->sprite = image;
    switch (enemyType) {
        case 0: // Pencil
            enemy->hp = 20; enemy->dmg = 5; enemy->def = 20; enemy->spd = 2;
            enemy->w = 16; enemy->h = 16;
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

void Enemy_RenderEnemy(SDL_Renderer* renderer, Enemy* enemy) {
    if (enemy->active == 0) {
        return;
    }
    SDL_Rect enemyArea = {enemy->x, enemy->y, enemy->w, enemy->h};
    SDL_RenderCopy(renderer, enemy->sprite, NULL, &enemyArea);
}

int Enemy_CountActiveEnemies() {
    int qtd = 0;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemiesActive[i].active) {
            qtd++;
        }
    }
    return qtd;
}