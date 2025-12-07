#ifndef WEAPONS_H
#define WEAPONS_H

#include <SDL2/SDL.h>
#include "EnemyManager.h"

#define seconds 1000

#define Max_projectiles  50
#define Max_Weapons  3

typedef enum{
	Mochila,
	Elastico,
	Cracha,
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
	int active_max;
	SDL_Texture* sprite;
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
	SDL_Texture* sprite;
}Projectiles;

extern int n_weapons_choices;

extern Arma selecionadas[Max_Weapons];

extern Projectiles list_projects[Max_projectiles];

void Select_Weapon(int type, SDL_Renderer* ren);

void Active_Weapon(Arma *arma, int i, EnemyManager* enemyController);

void DrawWeapons(SDL_Renderer *renderer);

void Update_Weapon(Uint32 tempo_execucao, EnemyManager* enemyController);

void Upgrade_Weapon(Arma* arma, int upgrade_type);

int Get_Weapon_index(ArmaTipo tipo);

#endif
