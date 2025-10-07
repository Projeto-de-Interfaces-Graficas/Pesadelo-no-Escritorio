#include "EnemyManager.h"
#include <stdlib.h>
#include <stdio.h>

/* Creates and initializes the variables of the EnemyManager object */
void EnemyManager_Init(EnemyManager* EnemyManager, int spawnInterval) {
    EnemyManager->lastSpawnTime = SDL_GetTicks();
    EnemyManager->spawnInterval = spawnInterval;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        EnemyManager->enemies[i].active = 0;
    }
}

/* Control enemies updating */
void EnemyManager_UpdateEnemies(EnemyManager* EnemyManager, SDL_Renderer* ren) {
    Uint32 currentTime = SDL_GetTicks();

    // Spawns an enemy if enough time has passed since the last enemy was spawned
    if (currentTime - EnemyManager->lastSpawnTime >= EnemyManager->spawnInterval) {
        EnemyManager->lastSpawnTime = currentTime;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (!EnemyManager->enemies[i].active) {
                int x = rand() % 600;
                int y = rand() % 400;
                Enemy_CreateEnemy(&EnemyManager->enemies[i], 0, x, y, ren);
                break;
            }
        }
    }

    // Updates the active enemies behavior
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (EnemyManager->enemies[i].active) {
            Enemy_UpdateEnemy(&EnemyManager->enemies[i]);
        }
    }
}

/* Control enemies rendering */
void EnemyManager_RenderEnemies(EnemyManager* EnemyManager, SDL_Renderer* ren) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (EnemyManager->enemies[i].active) {
            Enemy_RenderEnemy(ren, &EnemyManager->enemies[i]);
        }
    }
}

void EnemyManager_DestroyEnemies(EnemyManager* EnemyManager) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (EnemyManager->enemies[i].active) {
            Enemy_DestroyEnemy(&EnemyManager->enemies[i]);
        }
    }
}