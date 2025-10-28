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

void Damage_Controler();

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
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(0);
	*win = SDL_CreateWindow("Pesadelo no Escritório", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGURA, ALTURA, 0);
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
	/* Select_Weapon(ARMA_PROJETIL); */

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
		Damage_Controler(&enemyController);
		
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

		/* COLLISION CHECKING */
		Collision_PlayerAndEnemy(&player, &enemyController, &keepRunning); // Collision between the player and the enemies
		
	}
}

/* GAME FINALIZATION */
void FinishGame(SDL_Window **win, SDL_Renderer **ren) {
	SDL_DestroyRenderer(*ren);
	SDL_DestroyWindow(*win);
	IMG_Quit();
	SDL_Quit();
}

void Damage_Controler(EnemyManager* enemyController){
	for(int i =0;i<n_weapons_choices;i++){
		for(int j =0;j<MAX_ENEMIES;j++){
			if(enemyController->enemies[j].active != 1 || selecionadas[i].active != 1) continue;
			if(Collision_RectAndRect(&enemyController->enemies[j].box,&selecionadas[i].box)){
				enemyController->enemies[j].hp -= selecionadas[i].damage;
			}
		}
	}
	for(int i =0;i<Max_projectiles;i++){
		if(list_projects[i].active != 1) continue;
		for(int j =0;j<MAX_ENEMIES;j++){
			if(enemyController->enemies[j].active != 1 || list_projects[i].active != 1 ) continue;
			if(Collision_RectAndRect(&enemyController->enemies[j].box,&list_projects[i].box)){
				enemyController->enemies[j].hp -= list_projects[i].Weapon->damage;
			}
		}
	}
}
