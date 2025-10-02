#include <stdio.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "AUX_WaitEventTimeoutCount.h"
#include "Enemy.h"
#include "Weapons.h"

int Initializer(SDL_Window** win, SDL_Renderer** ren);
void Execution(SDL_Window* win, SDL_Renderer* ren);
int Finisher(SDL_Window** win, SDL_Renderer** ren);

int main(int argc, char* argv[]) {

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int successInit;
    successInit = Initializer(&window, &renderer);
    switch (successInit) {
        case 1:
            printf("The program was initalized correctely!\n");
            break;
        case -1:
            printf("Error at SDL library initialization!\n");
            return successInit;
        case -2:
            printf("Error at getting display mode!\n");
            return successInit;
        case -3:
            printf("Error at window creation!\n");
            return successInit;
        case -4:
            printf("Error at renderer creation!\n");
            return successInit;
            
    }

    Execution(window, renderer);

    int successFinish;
    successFinish = Finisher(&window, &renderer);
    switch (successFinish) {
        case 1:
            printf("Libraries successfully closed!\n");
            break;
        case -1:
            printf("Invalid window!\n");
            return successFinish;
        case -2:
            printf("Invalid renderer!\n");
            return successFinish;
    }
    return 0;

}

/* GAME INICIALIZATION */
int Initializer(SDL_Window** win, SDL_Renderer** ren) {

    int start;

    // SDL library initialization
    start = SDL_Init(SDL_INIT_EVERYTHING);
    if (start < 0) {
        return -1;
    }

    // SDL_image library initialization
    IMG_Init(0);

    // Setting monitor size
    SDL_DisplayMode currentDisplayMode;
    int monitorWidth;
    int monitorHeight;
    if (SDL_GetCurrentDisplayMode(0, &currentDisplayMode) != 0) {
        return -2;
    } else {
        monitorWidth = currentDisplayMode.w;
        monitorHeight = currentDisplayMode.h;
    }

    // Window creation
    *win = SDL_CreateWindow("Pesadelo no Escritório", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, monitorWidth, monitorHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (*win == NULL) {
        return -3;
    }

    // Renderer creation
    *ren = SDL_CreateRenderer(*win, -1, 0);
    if (*ren == NULL) {
        return -4;
    }

    // Setting rendering size based on monitor size
    int logicalWidth = 1980;
    int logicalHeight = 1080;
    SDL_RenderSetLogicalSize(*ren, logicalWidth, logicalHeight);

    // Return '1' if there aren't errors detected
    return 1;
}

/* GAME EXECUTION */
void Execution(SDL_Window* win, SDL_Renderer* ren) {

    /* EXECUTION VARIABLES */
    SDL_Event event;
    int keepRunning = 1;
    Uint32 delay = 16;
    int isEvent;

    /* GAME LOOP */
    while (keepRunning) {

        /* FRAME BUILDING */
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
        SDL_RenderClear(ren);
        SDL_RenderPresent(ren);

        /* EVENTS CAPTURE*/
        isEvent = AUX_WaitEventTimeoutCount(&event, &delay);
        if (isEvent) {
            // Quiting event
            if (event.type == SDL_QUIT) {
                keepRunning = 0;
            }
        } else {
            // Timeout
            delay = 16;
        }
    }
}

/* GAME FINALIZATION */
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
