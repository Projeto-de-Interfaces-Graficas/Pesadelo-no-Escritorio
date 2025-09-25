#include <stdio.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "AUX_WaitEventTimeoutCount.h"
#include "Enemy.h"

#define LARGURA 800
#define ALTURA 800

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { 
        printf("Erro ao inicializar biblioteca!");
        exit(-1); 
    }
    
    IMG_Init(0);

    SDL_Window* window = SDL_CreateWindow("Teste - Inimigos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGURA, ALTURA, 0); 
    assert(window != NULL);
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); 
    assert(renderer != NULL);

    SDL_Texture* image = IMG_LoadTexture(renderer, "assets/images/teste.png");
    assert(image != NULL);

    for (int i = 0; i < 10; i++) {
        Enemy_UpdateEnemy(&enemiesActive[i]);
        Enemy_SpawnEnemy(&enemiesActive[i], 0, i * 50, i * 50, image);
        printf("Spawnei %d inimigo(s)\n", i+1);
    }

    int continuarTeste = 1;
    SDL_Event evt;
    Uint32 tempo = 16;
    while (continuarTeste) {

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00); 
        SDL_RenderClear(renderer); 

        // Draw enemies
        int enemiesSpawned = Enemy_CountActiveEnemies();
        for (int j = 0; j < enemiesSpawned; j++) {
            Enemy_DrawEnemy(renderer, &enemiesActive[j]);
        }

        SDL_RenderPresent(renderer); 

        int isevt = AUX_WaitEventTimeoutCount(&evt, &tempo);
        if (isevt) {
            if (evt.type == SDL_QUIT) {
                continuarTeste = 0;
            }
        } else {
            continue;
        }
    }

    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window); 
    SDL_Quit();
    return 0; 
}