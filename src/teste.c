#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "AUX_WaitEventTimeoutCount.h"
#include "Enemy.h"
#include "Weapons.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Collision.h"
#include "Experience.h"
#include "ExperienceManager.h"

#define LARGURA 800
#define ALTURA 600

void InitializeGame(SDL_Window **win, SDL_Renderer **ren);
void ExecuteGame(SDL_Window *win, SDL_Renderer *ren);
void FinishGame(SDL_Window **win, SDL_Renderer **ren);

typedef enum {
	GAMESTATE_MENUPRINCIPAL,
	GAMESTATE_JOGO,
	GAMESTATE_PAUSE,
	GAMESTATE_LEVELUP
} GameState;

int main(int argc, char *argv[]) {
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	InitializeGame(&window, &renderer);
	ExecuteGame(window, renderer);
	FinishGame(&window, &renderer);
	return 0;
}

/* GAME INICIALIZATION */
void InitializeGame(SDL_Window **win, SDL_Renderer **ren) {
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(0);
	*win = SDL_CreateWindow("Pesadelo no Escritório", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGURA, ALTURA, 0);
	*ren = SDL_CreateRenderer(*win, -1, 0);
}

/* GAME EXECUTION */
void ExecuteGame(SDL_Window *win, SDL_Renderer *ren) {

	/* EXECUTION VARIABLES */
	GameState currentGameState = GAMESTATE_MENUPRINCIPAL;
	int mainMenuOptionSelected = 0;
	int pauseMenuOptionSelected = 0;
	int levelUpMenuOptionSelected = 0;
	SDL_Event event;
	int keepRunning = 1;
	Uint32 delay = 16;
	int isEvent;
	Uint32 previousTime = SDL_GetTicks();
	Uint32 currentTime;
	float deltaTime;
	int movingUp = 0, movingDown = 0, movingLeft = 0, movingRight = 0;
	ExperienceManager xpController;
	EnemyManager enemyController;

	/* ENTITIES INITIALIZATION */
	Create_player(Comum);
	EnemyManager_Init(&enemyController, 2000, ren);
	ExperienceManager_Init(&xpController, ren, 16);
	Select_Weapon(ARMA_PROJETIL);

	/* GAME LOOP */
	while (keepRunning) {

		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - previousTime) / 1000.0f; 
		previousTime = currentTime;

		/* CAPTURA DE EVENTOS */
		isEvent = AUX_WaitEventTimeoutCount(&event, &delay, &enemyController);
		if (isEvent) {
			if (event.type == SDL_QUIT) {
				keepRunning = 0;
				EnemyManager_Destroy(&enemyController);
				ExperienceManager_Destroy(&xpController);
				break;
			}
			switch (currentGameState) {
				// Eventos relacionados ao menu principal do jogo
				case GAMESTATE_MENUPRINCIPAL:
					if (event.type == SDL_KEYDOWN) {
						switch (event.key.keysym.sym) {
							case SDLK_UP:
								mainMenuOptionSelected = (mainMenuOptionSelected + 1) % 2;
								break;
							case SDLK_DOWN:
								mainMenuOptionSelected = (mainMenuOptionSelected + 1) % 2;
								break;
							case SDLK_RETURN:
								if (mainMenuOptionSelected == 1) {
									currentGameState = GAMESTATE_JOGO;
								} else {
									keepRunning = 0;
								}
								break;
							default:
								break;
						}
					}
					break;
				// Eventos relacionados ao jogo em si
				case GAMESTATE_JOGO:
					if (event.type == SDL_KEYDOWN) {
						switch (event.key.keysym.sym) {
							case SDLK_w: 
								movingUp = 1; 
								break;
							case SDLK_s: 
								movingDown = 1; 
								break;
							case SDLK_a: 
								movingLeft = 1; 
								player.dir = -1; 
								break;
							case SDLK_d: 
								movingRight = 1; 
								player.dir = 1; 
								break;
							case SDLK_ESCAPE: 
								currentGameState = GAMESTATE_PAUSE; 
								break;
							default: 
								break;
						}
					}
					if (event.type == SDL_KEYUP) {
						switch (event.key.keysym.sym) {
							case SDLK_w: 
								movingUp = 0; 
								break;
							case SDLK_s: 
								movingDown = 0; 
								break;
							case SDLK_a: 
								movingLeft = 0; 
								break;
							case SDLK_d: 
								movingRight = 0; 
								break;
							default: 
								break;
						}
					}
					break;
				// Eventos relacionados ao menu de pausa do jogo
				case GAMESTATE_PAUSE:
					movingUp = 0;
					movingDown = 0;
					movingRight = 0;
					movingLeft = 0;
					if (event.type == SDL_KEYDOWN) {
						switch (event.key.keysym.sym) {
							case SDLK_UP:
								pauseMenuOptionSelected = (pauseMenuOptionSelected + 1) % 3;
								break;
							case SDLK_DOWN:
								pauseMenuOptionSelected = (pauseMenuOptionSelected + 1) % 3;
								break;
							case SDLK_RETURN:
								if (pauseMenuOptionSelected == 0) {
									currentGameState = GAMESTATE_JOGO;
								} else if (pauseMenuOptionSelected == 1) {
									currentGameState = GAMESTATE_MENUPRINCIPAL;
								} else {
									keepRunning = 0;
								}
								break;
							case SDLK_ESCAPE:
								currentGameState = GAMESTATE_JOGO;
								break;
							default:
								break;
						}
					}
					break;
				// Eventos relacionados ao menu de escolha de aprimoramentos ao subir de nível
				case GAMESTATE_LEVELUP:
					movingUp = 0;
					movingDown = 0;
					movingRight = 0;
					movingLeft = 0;
					if (event.type == SDL_KEYDOWN) {
						switch (event.key.keysym.sym) {
							case SDLK_LEFT:
								levelUpMenuOptionSelected = (levelUpMenuOptionSelected + 1) % 3;
								break;
							case SDLK_RIGHT:
								levelUpMenuOptionSelected = (levelUpMenuOptionSelected + 1) % 3;
								break;
							case SDLK_RETURN:
								printf("Você escolheu o upgrade %d\n", levelUpMenuOptionSelected + 1);
								currentGameState = GAMESTATE_JOGO;
								break;
							default:
								break;
						}
					}
				default:
					break;
			}			
		} else {
			delay = 16;
		}

		/* RENDERIZAÇÃO */
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
		SDL_RenderClear(ren);

		if (currentGameState == GAMESTATE_MENUPRINCIPAL) {
			SDL_Rect backgroundImageBox = {0, 0, 800, 600};
			SDL_Texture* backgroundImage = IMG_LoadTexture(ren, "assets/images/tela-inicial-placeholder.png");
			SDL_RenderCopy(ren, backgroundImage, NULL, &backgroundImageBox);
		}

		if (currentGameState == GAMESTATE_JOGO) {
			// Renderização dos objetos do jogo
			Render_player(ren);
			EnemyManager_RenderEnemies(&enemyController, ren);
			ExperienceManager_RenderXp(&xpController, ren);
			DrawWeapons(ren);

			// Atualização dos objetos do jogo
			EnemyManager_UpdateEnemies(&enemyController, ren, player, deltaTime, LARGURA, ALTURA);
			Collision_EnemyAndEnemy(&enemyController);
			Collision_EnemyAndWeapon(&enemyController, &xpController);

			float movX = movingRight - movingLeft;
			float movY = movingDown - movingUp;
			float len = sqrtf(movX * movX + movY * movY);
			if (len > 0) {
				movX /= len;
				movY /= len;
			}
			player.posX += movX * player.movement_speed * deltaTime;
			player.posY += movY * player.movement_speed * deltaTime;
			player.box.x = (int) player.posX;
			player.box.y = (int) player.posY;
			Collision_PlayerAndEnemy(&player, &enemyController, &keepRunning);
			Collision_PlayerAndXp(&xpController);
			if (player.has_leveled_up) {
				player.has_leveled_up = 0;
				currentGameState = GAMESTATE_LEVELUP;
			}
		}

		SDL_RenderPresent(ren);
	}
}

/* GAME FINALIZATION */
void FinishGame(SDL_Window **win, SDL_Renderer **ren) {
	SDL_DestroyRenderer(*ren);
	SDL_DestroyWindow(*win);
	IMG_Quit();
	SDL_Quit();
}

