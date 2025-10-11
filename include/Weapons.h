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

typedef struct{
	Uint32 is_on_screen;
	Arma *Weapon;
	SDL_Rect box;
	float dir_x;
	float dir_y;
	float speed;
	int pierce;
	int active;
}Projectiles;

void Select_Weapon(int type);

void Active_Weapon(int x , int y,Arma arma);

void DrawWeapons(SDL_Renderer *renderer);

void ATT_Duration_Weapon(Uint32 tempo_execucao);

void Get_Near_Enemy();

#endif
