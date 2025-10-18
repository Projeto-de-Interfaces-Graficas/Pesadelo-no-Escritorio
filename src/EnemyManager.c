#include "EnemyManager.h"

/* CREATE AND INITIALIZE AN ENEMY MANAGER */
void EnemyManager_StartEnemies(EnemyManager* EnemyManager, int spawnInterval) {
    EnemyManager->lastSpawnTime = SDL_GetTicks();
    EnemyManager->spawnInterval = spawnInterval;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        EnemyManager->enemies[i].active = 0;
    }
    EnemyManager->enemiesActive = 0;
    srand(time(NULL));
}

/* CONTROLS ENEMIES SPAWN AND MOVEMENT */
void EnemyManager_UpdateEnemies(EnemyManager* EnemyManager, SDL_Renderer* ren, Player player, float deltaTime) {

    /* Spawns an enemy in a circular area around the player if enough time has passed since the last enemy was spawned */
    Uint32 currentTime = SDL_GetTicks();

    if (currentTime - EnemyManager->lastSpawnTime >= EnemyManager->spawnInterval) {
        EnemyManager->lastSpawnTime = currentTime;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (!EnemyManager->enemies[i].active) {
                int n = rand();
                double nd = (double)n / RAND_MAX;
                double angle = nd * 2 * M_PI;
                float x = (player.box.x + 16) + 100 * cos(angle);
                float y = (player.box.y + 16) + 100 * sin(angle);
                Enemy_CreateEnemy(&EnemyManager->enemies[i], 0, x, y, ren);
                EnemyManager->enemiesActive += 1;
                break;
            }
        }       
    }

    /* Moves all the active enemies in a straight line to the player position */
    float enemyX, enemyY; // Enemy current position 
    float playerX, playerY; // Player current position
    float directionX, directionY; // Direction that the enemy will move
    float normalizedDirectionX, normalizedDirectionY, magnitude; // Normalized movement direction

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (EnemyManager->enemies[i].active) {

            // Converts entities positions to float
            enemyX = (float) EnemyManager->enemies[i].box.x;
            enemyY = (float) EnemyManager->enemies[i].box.y;
            playerX = (float) player.box.x;
            playerY = (float) player.box.y;

            // Calculate the direction that the enemy will move
            directionX = playerX - enemyX;
            directionY = playerY - enemyY;

            // Normalization of the direction vector
            magnitude = sqrtf(directionX * directionX + directionY * directionY);
            if (magnitude != 0) {
                normalizedDirectionX = directionX / magnitude;
                normalizedDirectionY = directionY / magnitude;
            } else {
                normalizedDirectionX = 0;
                normalizedDirectionY = 0;
            }

            Enemy_UpdateEnemy(&EnemyManager->enemies[i], normalizedDirectionX, normalizedDirectionY, deltaTime);
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
