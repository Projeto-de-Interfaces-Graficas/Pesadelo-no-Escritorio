#include <stdio.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "AUX_WaitEventTimeoutCount.h"
#include "Enemy.h"
#include "Weapons.h"

#define LARGURA 1280
#define ALTURA 720

int Initializer(SDL_Window** win, SDL_Renderer** ren);
void Execution();
int Finisher(SDL_Window** win, SDL_Renderer** ren);

int main(int argc, char* argv[]) {

    // SDL subsystems and components inicialization
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int sucess;
    sucess = Initializer(&window, &renderer);
    switch (sucess) {
        case 1:
            printf("The program was initalized correctely!\n");
            break;
        case -1:
            printf("Error at SDL library initialization!\n");
            return sucess;
        case -2:
            printf("Error at window creation!\n");
            return sucess;
        case -3:
            printf("Error at renderer creation!\n");
            return sucess;
    }

    // Program execution
    Execution();

    // SDL subsystems and components finalization
    sucess = 0;
    sucess = Finisher(&window, &renderer);
    switch (sucess) {
        case 1:
            printf("Libraries successfully closed!\n");
            break;
        case -1:
            printf("Invalid window!\n");
            return sucess;
        case -2:
            printf("Invalid renderer!\n");
            return sucess;
    }
    return 0;

}

int Initializer(SDL_Window** win, SDL_Renderer** ren) {

    int start;

    // SDL library initialization
    start = SDL_Init(SDL_INIT_EVERYTHING);
    if (start < 0) {
        return -1;
    }

    // SDL_image library initialization
    IMG_Init(0);

    // Window creation
    *win = SDL_CreateWindow("Pesadelo no Escritório", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGURA, ALTURA, 0);
    if (*win == NULL) {
        return -2;
    }

    // Renderer creation
    *ren = SDL_CreateRenderer(*win, -1, 0);
    if (*ren == NULL) {
        return -3;
    }

    // Return '1' if there aren't errors detected
    return 1;
}

void Execution() {
    printf("COLOCA COISA AQUI\n");
}

int Finisher(SDL_Window** win, SDL_Renderer** ren) {

    // Check if the components were correctely passed
    if (*win == NULL) {
        return -1;
    }
    if(*ren == NULL) {
        return -2;
    }

    // Finish SDL and external libraries subsystems and desalocate the created components
    SDL_DestroyRenderer(*ren);
    SDL_DestroyWindow(*win);
    IMG_Quit();
    SDL_Quit();
    return 1; 
}
