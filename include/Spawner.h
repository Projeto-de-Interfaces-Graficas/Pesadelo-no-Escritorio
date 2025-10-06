#ifndef SPAWNER_H
#define SPAWNER_H

#include <SDL2/SDL.h>
#include "Enemy.h"

#define MAX_ENEMIES 100 // Defines the maximum amount of enemies that can be active simultaneously

typedef struct {
    Enemy enemies[MAX_ENEMIES];
    Uint32 lastSpawnTime;
    int spawnInterval;
} Spawner;

void Spawner_Init(Spawner* spawner, int spawnInterval);
void Spawner_UpdateEnemies(Spawner* spawner, SDL_Renderer* ren);
void Spawner_RenderEnemies(Spawner* spawner, SDL_Renderer* ren);
void Spawner_DestroyEnemies(Spawner* spawner);

#endif

