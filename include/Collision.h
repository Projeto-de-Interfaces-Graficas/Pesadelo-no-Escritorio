#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include "Player.h"
#include "EnemyManager.h"

int Collision_RectAndRect(SDL_Rect* r1, SDL_Rect* r2); // Detecta colisão entre dois retângulos quaisquer
void Collision_PlayerAndEnemy(Player* player, EnemyManager* enemyController, int* keepRunning); // Detecta colisão entre o jogador e os inimigos
void Collision_EnemyAndEnemy(EnemyManager* enemyController); // Detecta colisão entre os inimigos

#endif