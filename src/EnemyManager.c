#include "EnemyManager.h"

void EnemyManager_StartEnemies(EnemyManager* EnemyManager, int spawnInterval) {
    EnemyManager->lastSpawnTime = SDL_GetTicks();
    EnemyManager->spawnInterval = spawnInterval;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        EnemyManager->enemies[i].active = 0;
    }
    EnemyManager->enemiesActive = 0;
    srand(time(NULL));
}

void EnemyManager_UpdateEnemies(EnemyManager* EnemyManager, SDL_Renderer* ren, Player player, float deltaTime, float radiusX, float radiusY) {
    /* Spawna um inimigo em uma posição aleatória fora da visão do jogador, se tempo suficiente passou desde que o último inimigo foi spawnado */
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - EnemyManager->lastSpawnTime >= EnemyManager->spawnInterval) {
        EnemyManager->lastSpawnTime = currentTime;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (!EnemyManager->enemies[i].active) {
                int n = rand();
                double nd = (double)n / RAND_MAX;
                double angle = nd * 2 * M_PI;
                float x = (player.box.x + 16) + radiusX * cos(angle);
                float y = (player.box.y + 16) + radiusY * sin(angle);
                Enemy_CreateEnemy(&EnemyManager->enemies[i], 0, x, y, ren);
                EnemyManager->enemiesActive += 1;
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
        if (EnemyManager->enemies[i].active) {
            enemyX = (float) EnemyManager->enemies[i].box.x;
            enemyY = (float) EnemyManager->enemies[i].box.y;
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

            Enemy_UpdateEnemy(&EnemyManager->enemies[i], normalizedDirectionX, normalizedDirectionY, deltaTime);
        }
    }
}

/* Controla a renderização dos inimigos na tela */
void EnemyManager_RenderEnemies(EnemyManager* EnemyManager, SDL_Renderer* ren) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (EnemyManager->enemies[i].active) {
            Enemy_RenderEnemy(ren, &EnemyManager->enemies[i]);
        }
    }
}

/* int Get_Near_Enemy(EnemyManager* EnemyManager,int *x,int*y,int x0,int y0){
    int best_dis = 9999999;
    int dis = 9999999;
    for(int i=0;i<MAX_ENEMIES;i++){
        int x1= EnemyManager->enemies[i].box.x-x0;
		int y1= EnemyManager->enemies[i].box.y-y0;
		int dis = sqrt(x1*x1+y1*y1);
        if(dis<best_dis){
            best_dis = dis;
            y = EnemyManager->enemies[i].box.y;
            x = EnemyManager->enemies[i].box.x;
        }
    }
    return dis;
} */ 
