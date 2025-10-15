#include "Enemy.h"

void Enemy_CreateEnemy(Enemy* enemy, EnemyType type, int enemyPositionX, int enemyPositionY, SDL_Renderer* ren) {
    enemy->box.x = enemyPositionX;
    enemy->box.y = enemyPositionY;
    enemy->active = 1;
    enemy->type = type;
    switch (type) {
        case ENEMY_LAPIS:
            enemy->hp = 5; enemy->dmg = 5; enemy->def = 5; enemy->spd = 1.5;
            enemy->box.w = 32; enemy->box.h = 32;
            enemy->sprite = IMG_LoadTexture(ren, "assets/images/lapis.png");
            break;
        case ENEMY_TELEFONE: 
        case ENEMY_IMPRESSORA: 
        case ENEMY_FITA_ADESIVA: 
        case ENEMY_GRAMPEADOR: 
        case ENEMY_FRAGMENTADORA: 
    }
}

void Enemy_UpdateEnemy(Enemy* enemy, float directionX, float directionY) {
    if (enemy->active == 0) {
        return;
    }
    enemy->box.x += directionX * enemy->spd;
    enemy->box.y += directionY * enemy->spd;
}

void Enemy_RenderEnemy(SDL_Renderer* ren, Enemy* enemy) {
    if (enemy->active == 0) {
        return;
    }
    SDL_RenderCopy(ren, enemy->sprite, NULL, &enemy->box);
}

void Enemy_DestroyEnemy(Enemy* enemy) {
    if (enemy->active) {
        SDL_DestroyTexture(enemy->sprite);
        enemy->active = 0;
        printf("Inimigo destruído\n");
    }
}