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
	SDL_Event event;
	int keepRunning = 1;
	Uint32 delay = 16;
	int isEvent;
	Uint32 previousTime = SDL_GetTicks();
	Uint32 currentTime;
	float deltaTime;
	ExperienceManager xpController;

	/* ENTITIES INITIALIZATION */
	Create_player(Comum);
	EnemyManager_StartEnemies(&enemyController, 2000);
	ExperienceManager_Init(&xpController, ren, 8);
	Select_Weapon(ARMA_PROJETIL);

	/* GAME LOOP */
	while (keepRunning) {

		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - previousTime) / 1000.0f; 
		previousTime = currentTime;

		/* FRAME BUILDING */
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
		SDL_RenderClear(ren);

		Render_player(ren);
		EnemyManager_RenderEnemies(&enemyController, ren);
		ExperienceManager_RenderXp(&xpController, ren);
		DrawWeapons(ren);

		SDL_RenderPresent(ren);

		/* CAPTURA DE EVENTOS */
		isEvent = AUX_WaitEventTimeoutCount(&event, &delay);
		if (isEvent) {
			if (event.type == SDL_QUIT) {
				keepRunning = 0;
			}
		}

		delay = 16;
		EnemyManager_UpdateEnemies(&enemyController, ren, player, deltaTime, LARGURA, ALTURA);
		Collision_EnemyAndEnemy(&enemyController);
		Collision_EnemyAndWeapon(&enemyController, &xpController);
		
		/* MOVIMENTAÇÃO DO JOGADOR */
		float movX = 0, movY = 0;
		const Uint8* teclado = SDL_GetKeyboardState(NULL);
		if (teclado[SDL_SCANCODE_W]) {
			movY -= 1;
		}
		if (teclado[SDL_SCANCODE_A]) {
			movX -= 1;
			player.dir = -1;
		}
		if (teclado[SDL_SCANCODE_S]) {
			movY += 1;
		}
		if (teclado[SDL_SCANCODE_D]) {
			movX += 1;
			player.dir = 1;
		}
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
	}
}

/* GAME FINALIZATION */
void FinishGame(SDL_Window **win, SDL_Renderer **ren) {
	SDL_DestroyRenderer(*ren);
	SDL_DestroyWindow(*win);
	IMG_Quit();
	SDL_Quit();
}

