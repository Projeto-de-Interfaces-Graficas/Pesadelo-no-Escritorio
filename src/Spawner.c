#include "Spawner.h"
#include <stdlib.h>
#include <stdio.h>

/* Creates and initializes the variables of the Spawner object */
void Spawner_Init(Spawner* spawner, int spawnInterval) {
    spawner->lastSpawnTime = SDL_GetTicks();
    spawner->spawnInterval = spawnInterval;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        spawner->enemies[i].active = 0;
    }
}

/* Control enemies updating */
void Spawner_UpdateEnemies(Spawner* spawner, SDL_Renderer* ren) {
    Uint32 currentTime = SDL_GetTicks();

    // Spawns an enemy if enough time has passed since the last enemy was spawned
    if (currentTime - spawner->lastSpawnTime >= spawner->spawnInterval) {
        spawner->lastSpawnTime = currentTime;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (!spawner->enemies[i].active) {
                int x = rand() % 600;
                int y = rand() % 400;
                Enemy_CreateEnemy(&spawner->enemies[i], 0, x, y, ren);
                break;
            }
        }
    }

    // Updates the active enemies behavior
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (spawner->enemies[i].active) {
            Enemy_UpdateEnemy(&spawner->enemies[i]);
        }
    }
}

/* Control enemies rendering */
void Spawner_RenderEnemies(Spawner* spawner, SDL_Renderer* ren) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (spawner->enemies[i].active) {
            Enemy_RenderEnemy(ren, &spawner->enemies[i]);
        }
    }
}

void Spawner_DestroyEnemies(Spawner* spawner) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (spawner->enemies[i].active) {
            Enemy_DestroyEnemy(&spawner->enemies[i]);
        }
    }
}