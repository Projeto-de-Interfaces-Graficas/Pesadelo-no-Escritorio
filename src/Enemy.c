#include "Enemy.h"

void Enemy_CreateEnemy(Enemy* enemy, EnemyType type, int enemyPositionX, int enemyPositionY, SDL_Renderer* ren) {
    enemy->x = enemyPositionX;
    enemy->y = enemyPositionY;
    enemy->active = 1;
    enemy->type = type;
    switch (type) {
        case ENEMY_LAPIS:
            enemy->hp = 20; enemy->dmg = 5; enemy->def = 20; enemy->spd = 2;
            enemy->w = 16; enemy->h = 16;
            enemy->sprite = IMG_LoadTexture(ren, "assets/images/teste.png");
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
    enemy->x += directionX * enemy->spd;
    enemy->y += directionY * enemy->spd;
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