#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "AUX_WaitEventTimeoutCount.h"
#include "Enemy.h"
#include "Weapons.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Collision.h"

#define LARGURA 800
#define ALTURA 600

void InitializeGame(SDL_Window **win, SDL_Renderer **ren);
void ExecuteGame(SDL_Window *win, SDL_Renderer *ren);
void FinishGame(SDL_Window **win, SDL_Renderer **ren);

int main(int argc, char *argv[]) {

	/* GAME INITIALIZATION */
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	InitializeGame(&window, &renderer);

	/* GAME EXECUTION */
	ExecuteGame(window, renderer);

	/* GAME FINALIZATION */
	FinishGame(&window, &renderer);
	return 0;
}

/* GAME INICIALIZATION */
void InitializeGame(SDL_Window **win, SDL_Renderer **ren) {

	// SDL library initialization
	SDL_Init(SDL_INIT_EVERYTHING);

	// SDL_image library initialization
	IMG_Init(0);

	// Window creation
	*win = SDL_CreateWindow("Pesadelo no Escritório", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGURA, ALTURA, 0);

	// Renderer creation
	*ren = SDL_CreateRenderer(*win, -1, 0);
}

/* GAME EXECUTION */
void ExecuteGame(SDL_Window *win, SDL_Renderer *ren) {

	/* EXECUTION VARIABLES */
	EnemyManager enemyController = {0};
	SDL_Event event;
	int keepRunning = 1;
	Uint32 delay = 16;
	int isEvent;
	Uint32 previousTime = SDL_GetTicks();
	Uint32 currentTime;
	float deltaTime;

	/* ENTITIES INITIALIZATION */
	Create_player(Comum);
	EnemyManager_StartEnemies(&enemyController, 2000);
	Select_Weapon(ARMA_PROJETIL);

	/* GAME LOOP */
	while (keepRunning) {

		/* FRAME BUILDING */
		// Initial clearing of render
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
		SDL_RenderClear(ren);

		// Entities rendering
		Render_player(ren);
		EnemyManager_RenderEnemies(&enemyController, ren);
		DrawWeapons(ren);

		// Frame exibition
		SDL_RenderPresent(ren);

		/* EVENTS CAPTURE*/
		isEvent = AUX_WaitEventTimeoutCount(&event, &delay);
		if (isEvent) {

			// Ends game loop execution
			if (event.type == SDL_QUIT) {
				keepRunning = 0;
			}

			// Moves player
			if (event.type == SDL_KEYDOWN) {
				switch(event.key.keysym.sym) {
				case 'w':
					player.box.y -= player.movement_speed;
					break;
				case 'a':
					player.box.x -= player.movement_speed;
					break;
				case 's':
					player.box.y += player.movement_speed;
					break;
				case 'd':
					player.box.x += player.movement_speed;
					break;
				default:
					break;
				}
			}
		} else {

			// Resets delay
			delay = 16;

			// Time calculation for enemies movement
			currentTime = SDL_GetTicks();
			deltaTime = (currentTime - previousTime) / 1000.0f; 
			previousTime = currentTime;

			// Update entities non-related to events
			EnemyManager_UpdateEnemies(&enemyController, ren, player, deltaTime, LARGURA, ALTURA);
		}

		/* COLLISION CHECKING */
		// Check collision between all active enemies and the player
		for (int i = 0; i < MAX_ENEMIES; i++) {
			if (enemyController.enemies[i].active) {
				int hasCollided = Collision_RectAndRect(&enemyController.enemies[i].box, &player.box);
				if (hasCollided) {
					currentTime = SDL_GetTicks();
					if (currentTime - player.last_damage_time >= player.invencibility_time) {
						Take_damage(enemyController.enemies[i].dmg);
						player.last_damage_time = currentTime;
						printf("Tomou dano!\nVida atual: %d\n", player.player_hp); 
					}
					if (player.player_hp <= 0) {
						keepRunning = 0;
						printf("VOCÊ MORREU!!!!\n");
						break; 
					}
				}
			}
		}		
	}
}

/* GAME FINALIZATION */
void FinishGame(SDL_Window **win, SDL_Renderer **ren) {

	// Finish SDL and external libraries subsystems and desalocate the created components
	SDL_DestroyRenderer(*ren);
	SDL_DestroyWindow(*win);
	IMG_Quit();
	SDL_Quit();
}
