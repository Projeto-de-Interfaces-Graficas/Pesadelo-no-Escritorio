#include <Weapons.h>
#include <math.h>
#include <Player.h>

#define seconds 1000

#define Max_projectiles  50
#define Max_Weapons  3

int n_weapons_choices =0;

Arma selecionadas[Max_Weapons];

Projectiles list_projects[Max_projectiles];

void Select_Weapon(int tipo)
{
	Arma new_weapon;
	switch (tipo)
	{
	case ARMA_CHICOTE:
		new_weapon.cooldown = 2 * seconds;
		new_weapon.damage = 3;
		new_weapon.duration = 1 * seconds;
		new_weapon.range = 50;
		new_weapon.recharging_time = 0;
		new_weapon.tipo = ARMA_CHICOTE;
		new_weapon.active = 0;
		break;
	case ARMA_PROJETIL:
		new_weapon.active = 0;
		new_weapon.cooldown = 2 * seconds;
		new_weapon.damage = 1;
		new_weapon.range= 100;
		new_weapon.recharging_time = 0;
		new_weapon.duration = 1 * seconds;
		new_weapon.tipo = ARMA_PROJETIL;
		new_weapon.box.x =0;
		new_weapon.box.y =0;
		new_weapon.box.w =0;
		new_weapon.box.h =0;
		break;
	default:
		break;
	}
	if(n_weapons_choices <Max_Weapons){
		selecionadas[n_weapons_choices] = new_weapon;
		n_weapons_choices++;
	}
}

void Active_Weapon(int x, int y, Arma arma)
{
	switch (arma.tipo)
	{
	case ARMA_CHICOTE:
		x = (player.box.x + (player.box.w)/2) - selecionadas[0].box.w;
		y = (player.box.y + (player.box.h)/2) - selecionadas[0].box.h;
		selecionadas[0].box.x = x;
		selecionadas[0].box.y = y;
		selecionadas[0].box.w = 100;
		selecionadas[0].box.h = 15;
		selecionadas[0].active = 1;
		selecionadas[0].is_on_screen = 0;
		break;
	case ARMA_PROJETIL:
		Projectiles novo_projetil;
		novo_projetil.is_on_screen = 0;
		novo_projetil.box.x = x;
		novo_projetil.box.y = y;
		novo_projetil.box.w = 10;
		novo_projetil.box.h = 10;
		novo_projetil.active = 1;
		novo_projetil.pierce = 1;
		novo_projetil.Weapon = &arma;
		novo_projetil.speed = 5;
		int x1,y1;
		x1 = 100;
		y1 = 100;
		x = x1-x;
		y= y1-y;
		int dis = sqrt(x*x+y*y);
		novo_projetil.dir_x = (float)x1/(float)dis;
		novo_projetil.dir_y = (float)y1/(float)dis;
		for(int i =0;i<Max_projectiles;i++){
			if(list_projects[i].active != 1){
				list_projects[i] = novo_projetil;
				break;
			}
		}
		break;
	default:
		break;
	}
}

void DrawWeapons(SDL_Renderer *renderer)
{
	for (int i = 0; i < n_weapons_choices; i++)
	{
		if (selecionadas[i].active == 1)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
			SDL_RenderFillRect(renderer, &selecionadas[i].box);
			if(selecionadas[i].tipo == ARMA_CHICOTE){
				selecionadas[0].box.x = (player.box.x + (player.box.w)/2);
				selecionadas[0].box.y = (player.box.y + (player.box.h)/2) - selecionadas[0].box.h/2;
			}
		}
	}
	for(int i=0;i<Max_projectiles;i++){
		if (list_projects[i].active == 1)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
			SDL_RenderFillRect(renderer, &list_projects[i].box);
			if(list_projects[i].is_on_screen-list_projects[i].is_on_screen_last >= 50){
				list_projects[i].box.x -= list_projects[i].dir_y * list_projects[i].speed;
				list_projects[i].box.y -= list_projects[i].dir_y * list_projects[i].speed;
				list_projects[i].is_on_screen_last = list_projects[i].is_on_screen;
			}
		}
	}
}

void ATT_Duration_Weapon(Uint32 tempo_execucao)
{
	for(int i=0;i<Max_projectiles;i++){
		if (list_projects[i].active == 1)
		{	
			list_projects[i].is_on_screen += tempo_execucao;
			if (list_projects[i].is_on_screen >= list_projects[i].Weapon->duration)
			{
				list_projects[i].active = 0;
			}
		}
	}
	for (int i = 0; i < n_weapons_choices; i++)
	{
		if (selecionadas[i].active == 1)
		{
			selecionadas[i].is_on_screen += tempo_execucao;
			if (selecionadas[i].is_on_screen >= selecionadas[i].duration)
			{
				selecionadas[i].active = 0;
			}
		}
		else if(selecionadas[i].active == 0)
		{
			selecionadas[i].recharging_time += tempo_execucao;
			if (selecionadas[i].recharging_time >= selecionadas[i].cooldown)
			{
				Active_Weapon(400, 400, selecionadas[i]);
				selecionadas[i].recharging_time = 0;
			}
		}
	}
}
