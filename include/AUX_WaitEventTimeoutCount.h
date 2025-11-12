#ifndef AUX_WAITEVENTTIMEOUTCOUNT_H
#define AUX_WAITEVENTTIMEOUTCOUNT_H

#include <SDL2/SDL.h>
#include "EnemyManager.h"

// Função que espera por um evento e atualiza o ms com o tempo de delay restante
int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms, EnemyManager* enemyController);

#endif