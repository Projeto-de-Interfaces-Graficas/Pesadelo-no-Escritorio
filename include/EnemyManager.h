#ifndef EnemyManager_H
#define EnemyManager_H

#include <SDL2/SDL.h>
#include "Enemy.h"

#define MAX_ENEMIES 100 // Defines the maximum amount of enemies that can be active simultaneously

typedef struct {
    Enemy enemies[MAX_ENEMIES];
    Uint32 lastSpawnTime;
    int spawnInterval;
} EnemyManager;

void EnemyManager_Init(EnemyManager* EnemyManager, int spawnInterval);
void EnemyManager_UpdateEnemies(EnemyManager* EnemyManager, SDL_Renderer* ren);
void EnemyManager_RenderEnemies(EnemyManager* EnemyManager, SDL_Renderer* ren);
void EnemyManager_DestroyEnemies(EnemyManager* EnemyManager);

#endif

