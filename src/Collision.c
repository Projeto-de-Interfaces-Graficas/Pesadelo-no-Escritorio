#include "Collision.h"

void Collision_PlayerAndEnemy(Player* player, EnemyManager* enemyController, int* keepRunning) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemyController->enemies[i].active) {
			int hasCollided = Collision_RectAndRect(&enemyController->enemies[i].box, &player->box);
			if (hasCollided) {
				Uint32 currentTime = SDL_GetTicks();
				if (currentTime - player->last_damage_time >= player->invencibility_time) {
					Take_damage(enemyController->enemies[i].dmg);
					player->last_damage_time = currentTime;
					printf("Tomou dano!\nVida atual: %d\n", player->player_hp); 
				}
                if (player->player_hp <= 0) {
                    *keepRunning = 0;
                    printf("VOCÊ MORREU!!!\n");
                    break;
		        }
			}
		}
	}
}

void Collision_EnemyAndEnemy(EnemyManager* enemyController) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy* e1 = &enemyController->enemies[i];
        if (e1->active) {
            for (int j = i + 1; j < MAX_ENEMIES; j++) {
                Enemy* e2 = &enemyController->enemies[j];
                if (e2->active) {
                    int hasCollided = Collision_RectAndRect(&e1->box, &e2->box);
                    if (hasCollided) {
                        // Calcula a sobreposição horizontal e vertical entre os retângulos
                        float overlapX = 0, overlapY = 0;
                        float e1_direito = e1->posX + e1->box.w;
                        float e2_direito = e2->posX + e2->box.w;
                        float e1_baixo = e1->posY + e1->box.h;
                        float e2_baixo = e2->posY + e2->box.h;

                        if (e1->posX < e2->posX) {
                            overlapX = e1_direito - e2->posX;
                        } else {
                            overlapX = e2_direito - e1->posX;
                        }

                        if (e1->posY < e2->posY) {
                            overlapY = e1_baixo - e2->posY;
                        } else {
                            overlapY = e2_baixo - e1->posY;
                        }

                        // Afasta os dois inimigos ao mesmo tempo, dependendo de qual está na direita/esquerda ou cima/baixo
                        if (overlapX < overlapY) {
                            if (e1->posX < e2->posX) {
                                e1->posX -= (overlapX / 2);
                                e2->posX += (overlapX / 2);
                            } else {
                                e1->posX += (overlapX / 2);
                                e2->posX -= (overlapX / 2);
                            }
                        } else {
                            if (e1->posY < e2->posY) {
                                e1->posY -= (overlapY / 2);
                                e2->posY += (overlapY / 2);
                            } else {
                                e1->posY += (overlapY / 2);
                                e2->posY -= (overlapY / 2);
                            }
                        }

                    }
                }
            }
        }
    }
}

int Collision_RectAndRect(SDL_Rect* r1, SDL_Rect* r2) {

    // Define os lados dos retângulos
    int direito_r1, direito_r2, esquerdo_r1, esquerdo_r2, cima_r1, cima_r2, baixo_r1, baixo_r2;

    // Calcula os lados do retângulo 1
    direito_r1 = r1->x + r1->w;
    esquerdo_r1 = r1->x;
    cima_r1 = r1->y;
    baixo_r1 = r1->y + r1->h;

    // Calcula os lados do retângulo 2
    direito_r2 = r2->x + r2->w;
    esquerdo_r2 = r2->x;
    cima_r2 = r2->y;
    baixo_r2 = r2->y + r2->h;

    // Se não houver colisão, retorna 0
    return !(baixo_r1 < cima_r2 || cima_r1 > baixo_r2 || direito_r1 < esquerdo_r2 || esquerdo_r1 > direito_r2);
}