#ifndef EnemyManager_H
#define EnemyManager_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "Enemy.h"
#include "Player.h"

#define MAX_ENEMIES 200 // Defines the maximum amount of enemies that can be active simultaneously

typedef struct {
    Enemy enemies[MAX_ENEMIES];
    Uint32 lastSpawnTime;
    int spawnInterval;
    SDL_Texture* enemiesTextures[6];
} EnemyManager;

void EnemyManager_Init(EnemyManager* EnemyManager, int spawnInterval, SDL_Renderer* ren);
void EnemyManager_UpdateEnemies(EnemyManager* EnemyManager, SDL_Renderer* ren, Player player, float deltaTime, float radiusX, float radiusY);
void EnemyManager_RenderEnemies(EnemyManager* EnemyManager, SDL_Renderer* ren);
float EnemyManager_GetNearestEnemy(EnemyManager* EnemyManager,float *x,float*y,int x0,int y0);
void EnemyManager_Destroy(EnemyManager* enemyController);

extern EnemyManager enemyController;
#endif

