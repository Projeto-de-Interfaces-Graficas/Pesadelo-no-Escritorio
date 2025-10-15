#include "EnemyManager.h"

/* Creates and initializes the variables of the EnemyManager object */
void EnemyManager_StartEnemies(EnemyManager* EnemyManager, int spawnInterval) {
    EnemyManager->lastSpawnTime = SDL_GetTicks();
    EnemyManager->spawnInterval = spawnInterval;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        EnemyManager->enemies[i].active = 0;
    }
    EnemyManager->enemiesActive = 0;
    srand(time(NULL));
}

/* Control enemies updating */
void EnemyManager_UpdateEnemies(EnemyManager* EnemyManager, SDL_Renderer* ren, Player player) {

    // Spawns an enemy in a circular area around the player if enough time has passed since the last enemy was spawned
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - EnemyManager->lastSpawnTime >= EnemyManager->spawnInterval) {
        EnemyManager->lastSpawnTime = currentTime;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (!EnemyManager->enemies[i].active) {
                int n = rand();
                double nd = (double)n / RAND_MAX;
                double angle = nd * 2 * M_PI;
                int x = (player.box.x + 16) + 100 * cos(angle);
                int y = (player.box.y + 16) + 100 * sin(angle);
                Enemy_CreateEnemy(&EnemyManager->enemies[i], 0, x, y, ren);
                EnemyManager->enemiesActive += 1;
                break;
            }
        }
        
    }

    // Moves all the active enemies in a straight line to the player position
    float directionX, directionY;
    float normalizedDirectionX, normalizedDirectionY;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (EnemyManager->enemies[i].active) {
            directionX = player.box.x - EnemyManager->enemies[i].box.x;
            directionY = player.box.y - EnemyManager->enemies[i].box.y;
            normalizedDirectionX = directionX / sqrt(directionX * directionX + directionY * directionY);
            normalizedDirectionY = directionY / sqrt(directionX * directionX + directionY * directionY);
            Enemy_UpdateEnemy(&EnemyManager->enemies[i], normalizedDirectionX, normalizedDirectionY);
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
