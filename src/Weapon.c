#include <Weapons.h>
#include <math.h>

#define seconds 100

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
	case 0:
		new_weapon.cooldown = 10;
		new_weapon.damage = 3;
		new_weapon.duration = 2;
		new_weapon.range = 50;
		new_weapon.recharging_time = 0;
		new_weapon.tipo = ARMA_CHICOTE;
		new_weapon.active = 0;
		break;
	case 1:
		new_weapon.active = 0;
		new_weapon.cooldown = 2;
		new_weapon.damage = 1;
		new_weapon.range= 100;
		new_weapon.recharging_time = 0;
		new_weapon.duration = 0;
		new_weapon.tipo = ARMA_PROJETIL;
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
		selecionadas[0].box.x = x;
		selecionadas[0].box.y = y;
		selecionadas[0].box.w = 50;
		selecionadas[0].box.h = 50;
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
		novo_projetil.speed = 25;
		int x1,y1;
		x1 = 100;
		y1 = 100;
		x = x1-x;
		y= y1-y;
		int dis = sqrt(x*x+y*y);
		novo_projetil.dir_x = x1/dis;
		novo_projetil.dir_y = y1/dis;
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
	for (int i = 0; i < Max_Weapons; i++)
	{
		if (selecionadas[i].active)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
			SDL_RenderFillRect(renderer, &selecionadas[i].box);
		}
	}
	for(int i=0;i<Max_projectiles;i++){
		if (list_projects[i].active)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
			SDL_RenderFillRect(renderer, &list_projects[i].box);
			list_projects[i].box.x += 1;
			list_projects[i].box.y += list_projects[i].dir_y * list_projects[i].speed;
		}
	}
}

void ATT_Duration_Weapon(Uint32 tempo_execucao)
{
	for(int i=0;i<Max_projectiles;i++){
		if (list_projects[i].active)
		{
			list_projects[i].is_on_screen += tempo_execucao;
			printf("list_projects[i].is_on_screen = %d, list_projects[i].Weapon->duration = %d\n",list_projects[i].is_on_screen,list_projects[i].Weapon->duration);
			if (list_projects[i].is_on_screen >= list_projects[i].Weapon->duration)
			{
				printf("Inativo\n");
				list_projects[i].active = 0;
			}
		}
	}
	for (int i = 0; i < Max_Weapons; i++)
	{
		if (selecionadas[i].active)
		{
			selecionadas[i].is_on_screen += tempo_execucao;
			if (selecionadas[i].is_on_screen >= selecionadas[i].duration)
			{
				selecionadas[i].active = 0;
			}
		}
		else
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
