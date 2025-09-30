#ifndef WEAPONS_H
#define WEAPONS_H

#include <SDL2/SDL.h>

typedef enum{
  ARMA_CHICOTE,
  ARMA_PROJETIL,
  ARMA_AREA,
} ArmaTipo;

typedef struct 
{
  ArmaTipo tipo;
  float cooldown;
  float recharging_time;
  int damage;
  int range;
  Uint32 duration;
  Uint32 is_on_screen;
  int active;
  SDL_Rect box;
}Arma;

void Select_Weapon(int type);

void Active_Weapon(int x , int y,int arma);

void DrawWeapons(SDL_Renderer *renderer);

void ATT_Duration_Weapon(Uint32 tempo_execucao);

#endif
