#include "Enemy.h"

void Enemy_CreateEnemy(Enemy* enemy, EnemyType type, float enemyPositionX, float enemyPositionY, SDL_Texture* sprite) {
    // Initializes enemy logical position (float) and render position (int)
    enemy->posX = enemyPositionX;
    enemy->posY = enemyPositionY;
    enemy->box.x = (int) enemyPositionX;
    enemy->box.y = (int) enemyPositionY;

    enemy->sprite = sprite;
    enemy->type = type;

    switch (type) {
        case ENEMY_LAPIS:
            enemy->hp = 5; 
            enemy->dmg = 5; 
            enemy->def = 5; 
            enemy->spd = 100;
            enemy->xpBaseDropChance = 50;
            enemy->box.w = 32; 
            enemy->box.h = 32;
            break;
        case ENEMY_TELEFONE: 
        case ENEMY_IMPRESSORA: 
        case ENEMY_FITA_ADESIVA: 
        case ENEMY_GRAMPEADOR: 
        case ENEMY_FRAGMENTADORA: 
    }
    enemy->active = 1;
}

void Enemy_UpdateEnemy(Enemy* enemy, float directionX, float directionY, float deltaTime) {
    if(enemy->hp <= 0){
        enemy->active = 0;
    }
    // Only updates if the enemy is active
    if (enemy->active == 0) {
        return;
    }

    // Updates real enemy position
    enemy->posX += directionX * enemy->spd * deltaTime;
    enemy->posY += directionY * enemy->spd * deltaTime;

    // Updates enemy position for renderization
    enemy->box.x = (int) enemy->posX;
    enemy->box.y = (int) enemy->posY;
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
    }
}
