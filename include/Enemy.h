#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* Types of enemies */
typedef enum EnemyType {
    ENEMY_LAPIS,
    ENEMY_TELEFONE,
    ENEMY_IMPRESSORA,
    ENEMY_FITA_ADESIVA,
    ENEMY_GRAMPEADOR,
    ENEMY_FRAGMENTADORA
} EnemyType;

/* Enemy representation */
typedef struct Enemy {
    int type; // Type of enemy
    SDL_Rect box; // Enemy area in-game
    float posX, posY; // Position X and Y of the enemy 
    int hp, dmg, def; // Life, damage and defense status
    float spd; // Movement speed status
    SDL_Texture* sprite; // Current sprite
    int active; // State (dead or alive)
} Enemy;

/* Enemy creation */
void Enemy_CreateEnemy(Enemy* enemy, EnemyType type, float enemyPositionX, float enemyPositionY, SDL_Renderer* ren);

/* Enemy informations update */
void Enemy_UpdateEnemy(Enemy* enemy, float directionX, float directionY, float deltaTime);

/* Enemy render */
void Enemy_RenderEnemy(SDL_Renderer* ren, Enemy* enemy);

/* Enemy destruction */
void Enemy_DestroyEnemy(Enemy* enemy);

#endif