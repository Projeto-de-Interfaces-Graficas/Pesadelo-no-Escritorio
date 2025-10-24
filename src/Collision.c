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