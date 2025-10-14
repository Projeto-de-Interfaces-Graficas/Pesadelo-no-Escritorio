#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <SDL2/SDL.h>
#include <stdio.h>

// Function that controls collision detection
void CollisionManager_DetectCollisions(EnemyManager* enemyController, Player* player);

// Função que detecta colisões entre dois retângulos
int Collision_RectAndRect(SDL_Rect* r1, SDL_Rect* r2);

#endif