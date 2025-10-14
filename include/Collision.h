#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>
#include <stdio.h>

// Função que detecta colisões entre dois retângulos
int Collision_RectAndRect(SDL_Rect* r1, SDL_Rect* r2);

#endif