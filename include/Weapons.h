#ifndef WEAPONS_H
#define WEAPONS_H

#include <SDL2/SDL.h>

#define seconds 1000

#define Max_projectiles  50
#define Max_Weapons  3

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
	Uint32 is_on_screen_last;
	Arma *Weapon;
	SDL_Rect box;
	float dir_x;
	float dir_y;
	float speed;
	int pierce;
	int active;
}Projectiles;

extern int n_weapons_choices;

extern Arma selecionadas[Max_Weapons];

extern Projectiles list_projects[Max_projectiles];

void Select_Weapon(int type);

void Active_Weapon(Arma arma);

void DrawWeapons(SDL_Renderer *renderer);

void ATT_Duration_Weapon(Uint32 tempo_execucao);

#endif
