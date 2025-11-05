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
    int enemiesActive;
} EnemyManager;

void EnemyManager_StartEnemies(EnemyManager* EnemyManager, int spawnInterval);
void EnemyManager_UpdateEnemies(EnemyManager* EnemyManager, SDL_Renderer* ren, Player player, float deltaTime, float radiusX, float radiusY);
void EnemyManager_RenderEnemies(EnemyManager* EnemyManager, SDL_Renderer* ren);
void EnemyManager_EnemiesDrops(Enemy* enemy);
float Get_Near_Enemy(EnemyManager* EnemyManager,float *x,float*y,int x0,int y0);

extern EnemyManager enemyController;
#endif

