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
    int x, y; // Position
    int w, h; // Dimensions (size)
    int hp, dmg, def, spd; // Life, damage, defense and speed status
    SDL_Texture* sprite; // Current sprite
    int active; // State (dead or alive)
} Enemy;

/* Enemy creation */
void Enemy_CreateEnemy(Enemy* enemy, EnemyType type, int enemyPositionX, int enemyPositionY, SDL_Renderer* ren);

/* Enemy informations update */
void Enemy_UpdateEnemy(Enemy* enemy);

/* Enemy render */
void Enemy_RenderEnemy(SDL_Renderer* ren, Enemy* enemy);

/* Enemy destruction */
void Enemy_DestroyEnemy(Enemy* enemy);

#endif