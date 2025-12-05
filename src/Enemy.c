#include "Enemy.h"

void Enemy_CreateEnemy(Enemy* enemy, EnemyType type, float enemyPositionX, float enemyPositionY, SDL_Texture* sprite) {
    // Initializes enemy logical position (float) and render position (int)
    enemy->posX = enemyPositionX;
    enemy->posY = enemyPositionY;
    enemy->box.x = (int) enemyPositionX;
    enemy->box.y = (int) enemyPositionY;

    enemy->sprite = sprite;
    enemy->currentSprite = 0;
    if (enemyPositionX > 0) {
        enemy->direction = 1;
    } else {
        enemy->direction = -1;
    }
    enemy->type = type;
    enemy->animationTime = 0;

    switch (type) {
        case ENEMY_LAPIS:
            enemy->hp = 5; 
            enemy->dmg = 5; 
            enemy->def = 5; 
            enemy->spd = 100;
            enemy->xpBaseDropChance = 50;
            enemy->box.w = 32; 
            enemy->box.h = 32;
            enemy->maxAnimationTime = 0.15;
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
    if (enemy->active == 0) {
        return;
    }

    enemy->posX += directionX * enemy->spd * deltaTime;
    enemy->posY += directionY * enemy->spd * deltaTime;

    enemy->box.x = (int) enemy->posX;
    enemy->box.y = (int) enemy->posY;
}

void Enemy_RenderEnemy(SDL_Renderer* ren, Enemy* enemy) {
    if (enemy->active == 0) {
        return;
    }

    SDL_Rect renderBox;
    switch (enemy->currentSprite) {
        case 0: renderBox = (SDL_Rect) {0, 0, 32, 32}; break;
        case 1: renderBox = (SDL_Rect) {32, 0, 32, 32}; break;
        case 2: renderBox = (SDL_Rect) {64, 0, 32, 32}; break;
        default: break;
    }

    if (enemy->direction == -1) {
        SDL_RenderCopyEx(ren, enemy->sprite, &renderBox, &enemy->box, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopy(ren, enemy->sprite, &renderBox, &enemy->box);
    }
    
}

void Enemy_DestroyEnemy(Enemy* enemy) {
    if (enemy->active) {
        SDL_DestroyTexture(enemy->sprite);
        enemy->active = 0;
    }
}
