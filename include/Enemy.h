#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

/* Constants */
#define MAX_ENEMIES 50 // Max amount of enemies that can be active simultaneously

/* Types of enemies */
typedef enum EnemyType {
    PENCIL,
    TELEPHONE,
    PRINTER,
    ADHESIVE_TAPE,
    STAPLER,
    PAPER_SHREDDER
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

extern Enemy enemiesActive[MAX_ENEMIES]; // Stores all spawned enemies

/* Enemy creation */
void Enemy_SpawnEnemy(Enemy* enemy, int enemyType, int enemyPositionX, int enemyPositionY, SDL_Texture* image);

/* Enemy informations update */
void Enemy_UpdateEnemy(Enemy* enemy);

/* Enemy render */
void Enemy_DrawEnemy(SDL_Renderer* renderer, Enemy* enemy);

/* Enemy destruction */
void Enemy_DestroyEnemy();

/* Active enemies counter */
int Enemy_CountActiveEnemies();

#endif