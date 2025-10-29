#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef enum EnemyType {
    ENEMY_LAPIS,
    ENEMY_TELEFONE,
    ENEMY_IMPRESSORA,
    ENEMY_FITA_ADESIVA,
    ENEMY_GRAMPEADOR,
    ENEMY_FRAGMENTADORA
} EnemyType;

typedef struct Enemy {
    EnemyType type; 
    SDL_Rect box; 
    float posX, posY; 
    int hp, dmg, def; 
    float spd; 
    SDL_Texture* sprite; 
    int active; 
} Enemy;

void Enemy_CreateEnemy(Enemy* enemy, EnemyType type, float enemyPositionX, float enemyPositionY, SDL_Renderer* ren);
void Enemy_UpdateEnemy(Enemy* enemy, float directionX, float directionY, float deltaTime);
void Enemy_RenderEnemy(SDL_Renderer* ren, Enemy* enemy);
void Enemy_DestroyEnemy(Enemy* enemy);

#endif