#include "AUX_WaitEventTimeoutCount.h"
#include "Weapons.h"
#include <SDL2/SDL.h>
#include <stdio.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* ms, EnemyManager* enemyController) {

    // Captura o erro de ponteiro nulo
    if (ms == NULL) {
        printf("Erro! Não foi passado nenhum tempo!");
        return -1;
    }
    
    // Marca o tempo de início de espera pelo evento
    Uint32 inicio = SDL_GetTicks();

    // Chama o WaitEventTimeout() original
    int resultado = SDL_WaitEventTimeout(evt, *ms);
    
    // Marca o tempo de fim da captura do evento
    Uint32 fim = SDL_GetTicks();

    // Marca o tempo total de execução da função
    Uint32 tempo_execucao = fim - inicio;

    if (tempo_execucao >= *ms) {
        *ms = 0;
    }
    else {
        *ms -= tempo_execucao;
    }

    ATT_Duration_Weapon(tempo_execucao, enemyController);

    return resultado;
}
