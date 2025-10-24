#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include "Player.h"
#include "EnemyManager.h"

// Função que detecta colisões entre dois retângulos
int Collision_RectAndRect(SDL_Rect* r1, SDL_Rect* r2);

// Função que detecta colisões entre o jogador e os inimigos
void Collision_PlayerAndEnemy(Player* player, EnemyManager* enemyController, int* keepRunning);

// Função que detecta colisões entre os inimigos
int Collision_EnemyAndEnemy(EnemyManager* enemyController);

#endif