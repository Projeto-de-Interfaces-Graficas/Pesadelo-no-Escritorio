#include "EnemyManager.h"
#include "Experience.h"

void EnemyManager_Init(EnemyManager* EnemyManager, int spawnInterval, SDL_Renderer* ren) {
    EnemyManager->lastSpawnTime = SDL_GetTicks();
    EnemyManager->spawnInterval = spawnInterval;
    EnemyManager->enemiesTextures[ENEMY_LAPIS] = IMG_LoadTexture(ren, "assets/images/lapis.png");
    for (int i = 0; i < MAX_ENEMIES; i++) {
        EnemyManager->enemies[i].active = 0;
    }
    srand(time(NULL));
}

void EnemyManager_UpdateEnemies(EnemyManager* enemyController, SDL_Renderer* ren, Player player, float deltaTime, float radiusX, float radiusY) {
    /* Spawna um inimigo em uma posição aleatória fora da visão do jogador, se tempo suficiente passou desde que o último inimigo foi spawnado */
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - enemyController->lastSpawnTime >= enemyController->spawnInterval) {
        enemyController->lastSpawnTime = currentTime;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (!enemyController->enemies[i].active) {
                int n = rand();
                double nd = (double)n / RAND_MAX;
                double angle = nd * 2 * M_PI;
                float x = (player.box.x + 16) + radiusX * cos(angle);
                float y = (player.box.y + 16) + radiusY * sin(angle);
                Enemy_CreateEnemy(&enemyController->enemies[i], 0, x, y, enemyController->enemiesTextures[ENEMY_LAPIS]);
                break;
            }
        }       
    }

    /* Move todos os inimigos ativos na direção do jogador */
    float enemyX, enemyY; // Posição atual do inimigo
    float playerX, playerY; // Posição atual do jogador
    float directionX, directionY; // Direção que o inimigo vai se mover
    float normalizedDirectionX, normalizedDirectionY, magnitude; // Vetor direção normalizado

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemyController->enemies[i].active) {
            enemyX = (float) enemyController->enemies[i].box.x;
            enemyY = (float) enemyController->enemies[i].box.y;
            playerX = (float) player.box.x;
            playerY = (float) player.box.y;

            directionX = playerX - enemyX;
            directionY = playerY - enemyY;

            magnitude = sqrtf(directionX * directionX + directionY * directionY);
            if (magnitude != 0) {
                normalizedDirectionX = directionX / magnitude;
                normalizedDirectionY = directionY / magnitude;
            } else {
                normalizedDirectionX = 0;
                normalizedDirectionY = 0;
            }

            Enemy_UpdateEnemy(&enemyController->enemies[i], normalizedDirectionX, normalizedDirectionY, deltaTime);
        }
    }
}

void EnemyManager_RenderEnemies(EnemyManager* EnemyManager, SDL_Renderer* ren) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (EnemyManager->enemies[i].active) {
            Enemy_RenderEnemy(ren, &EnemyManager->enemies[i]);
        }
    }
}

float EnemyManager_GetNearestEnemy(EnemyManager* EnemyManager,float *x,float*y,int x0,int y0){
    float best_dis = 9999999;
    for(int i=0;i<MAX_ENEMIES;i++){
        if(EnemyManager->enemies[i].active != 1) continue;
        int x1= (EnemyManager->enemies[i].box.x + EnemyManager->enemies[i].box.w/2)-x0;
		int y1= (EnemyManager->enemies[i].box.y+EnemyManager->enemies[i].box.h/2)-y0;
		int dis = sqrt(x1*x1+y1*y1);
        if(dis<best_dis){
            best_dis = dis;
            *y = y1;
            *x = x1;
        }
    }
    return best_dis;
}  

void EnemyManager_Destroy(EnemyManager* enemyController) {
    for (int i = 0; i < 6; i++) {
        SDL_DestroyTexture(enemyController->enemiesTextures[i]);
    }
}