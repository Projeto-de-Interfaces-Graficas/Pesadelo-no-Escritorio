#include <Weapons.h>
#include <math.h>
#include <Player.h>
#include <EnemyManager.h>

int n_weapons_choices = 0;

Arma selecionadas[Max_Weapons];

Projectiles list_projects[Max_projectiles];

void Select_Weapon(int tipo)
{
	Arma new_weapon;
	switch (tipo)
	{
	case Mochila:
		new_weapon.cooldown = 2 * seconds;
		new_weapon.damage = 10;
		new_weapon.duration = 0.25 * seconds;
		new_weapon.range = 50;
		new_weapon.recharging_time = 0;
		new_weapon.tipo = Mochila;
		new_weapon.active = 0;
		new_weapon.active_max = 1;
		break;
	case Elastico:
		new_weapon.active = 0;
		new_weapon.active_max = 1;
		new_weapon.cooldown = 4 * seconds;
		new_weapon.damage = 5;
		new_weapon.range = 100;
		new_weapon.recharging_time = 0;
		new_weapon.duration = 1 * seconds;
		new_weapon.tipo = Elastico;
		new_weapon.box.x = 0;
		new_weapon.box.y = 0;
		new_weapon.box.w = 0;
		new_weapon.box.h = 0;
		break;
	case Cracha:
		new_weapon.active = 0;
		new_weapon.active_max = 1;
		new_weapon.cooldown = 3 * seconds;
		new_weapon.damage = 10;
		new_weapon.range = 25;
		new_weapon.recharging_time = 0;
		new_weapon.duration = 2 * seconds;
		new_weapon.tipo = Cracha;
		break;
	default:
		break;
	}
	if (n_weapons_choices < Max_Weapons)
	{
		selecionadas[n_weapons_choices] = new_weapon;
		n_weapons_choices++;
	}
}

void Active_Weapon(Arma *arma, int i, EnemyManager *enemyController)
{
	int x;
	int y;
	switch (arma->tipo)
	{
	case Mochila:
		selecionadas[i].box.w = 100;
		selecionadas[i].box.h = 15;
		if (player.dir == -1)
		{
			x = (player.box.x + (player.box.w) / 2) - selecionadas[0].box.w;
		}
		else
		{
			x = (player.box.x + (player.box.w) / 2);
		}
		selecionadas[i].box.x = x;
		y = (player.box.y + (player.box.h) / 2) - selecionadas[0].box.h / 2;
		selecionadas[i].box.y = y;
		selecionadas[i].active = selecionadas[i].active_max;
		selecionadas[i].is_on_screen = 0;
		break;
	case Elastico:
		for (int i = 0; i < arma->active_max; i++)
		{
			Projectiles novo_projetil;
			novo_projetil.is_on_screen = 0;
			novo_projetil.box.x = (player.box.x + (player.box.w) / 2) + i * 10;
			novo_projetil.box.y = (player.box.y + (player.box.h) / 2) + i * 10;
			novo_projetil.box.w = 10;
			novo_projetil.box.h = 10;
			novo_projetil.active = 1;
			novo_projetil.pierce = 1;
			novo_projetil.Weapon = arma;
			novo_projetil.speed = 10;
			x = novo_projetil.box.x;
			y = novo_projetil.box.y;
			float x1, y1;
			float dis = EnemyManager_GetNearestEnemy(enemyController, &x1, &y1, x, y);
			novo_projetil.dir_x = x1 / dis;
			novo_projetil.dir_y = y1 / dis;
			for (int j = 0; j < Max_projectiles; j++)
			{
				if (list_projects[j].active != 1)
				{
					list_projects[j] = novo_projetil;
					break;
				}
			}
		}
		break;
	case Cracha:
		for (int i = 0; i < arma->active_max; i++)
		{
			Projectiles novo_projetil;
			novo_projetil.dir_x = 45;
			novo_projetil.is_on_screen = 0;
			novo_projetil.box.x =  player.box.x + 100 * cos(novo_projetil.dir_x *  i * M_PI / 180) - selecionadas[i].range / 2;
			novo_projetil.box.y =  player.box.y + 100 * sin(novo_projetil.dir_x  * i * M_PI / 180) - selecionadas[i].range / 2;
			novo_projetil.box.w = 10;
			novo_projetil.box.h = 10;
			novo_projetil.active = 1;
			novo_projetil.pierce = 1;
			novo_projetil.Weapon = arma;
			novo_projetil.speed = 5;
			for (int j = 0; j < Max_projectiles; j++)
			{
				if (list_projects[j].active != 1)
				{
					list_projects[j] = novo_projetil;
					break;
				}
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
		}
	}
	for (int i = 0; i < Max_projectiles; i++)
	{
		if (list_projects[i].active == 1)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
			SDL_RenderFillRect(renderer, &list_projects[i].box);
		}
	}
}

void Update_Weapon(Uint32 tempo_execucao, EnemyManager *enemyController)
{
	for (int i = 0; i < Max_projectiles; i++)
	{
		if (list_projects[i].active == 1)
		{
			list_projects[i].is_on_screen += tempo_execucao;
			if (list_projects[i].is_on_screen >= list_projects[i].Weapon->duration)
			{
				list_projects[i].active -= 1;
			}
			if (list_projects[i].is_on_screen - list_projects[i].is_on_screen_last >= 20)
			{
				if(list_projects[i].Weapon->tipo == Elastico){
					list_projects[i].box.x += list_projects[i].dir_x * list_projects[i].speed;
					list_projects[i].box.y += list_projects[i].dir_y * list_projects[i].speed;
				}
				else if(list_projects[i].Weapon->tipo == Cracha){
					list_projects[i].dir_x += list_projects[i].speed;
					list_projects[i].box.y =  player.box.y + 100 * sin(list_projects[i].dir_x * M_PI / 180) - list_projects[i].Weapon->range / 2;
					list_projects[i].box.x =  player.box.x + 100 * cos(list_projects[i].dir_x * M_PI / 180) - list_projects[i].Weapon->range / 2;
				}
				list_projects[i].is_on_screen_last = list_projects[i].is_on_screen;
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
				selecionadas[i].active -= 1;
			}
			if (selecionadas[i].tipo == Mochila)
			{
				if (player.dir == -1)
				{
					selecionadas[0].box.x = (player.box.x + (player.box.w) / 2) - selecionadas[0].box.w;
				}
				else
				{
					selecionadas[0].box.x = (player.box.x + (player.box.w) / 2);
				}
				selecionadas[0].box.y = (player.box.y + (player.box.h) / 2) - selecionadas[0].box.h / 2;
			}
		}
		else if (selecionadas[i].active == 0)
		{
			selecionadas[i].recharging_time += tempo_execucao;
			if (selecionadas[i].recharging_time >= selecionadas[i].cooldown)
			{
				Active_Weapon(&selecionadas[i], i, enemyController);
				selecionadas[i].recharging_time = 0;
			}
		}
	}
}

void Upgrade_Weapon(Arma *arma, int upgrade_type)
{
	ArmaTipo armatype = arma->tipo;
	switch (upgrade_type)
	{
	case 1: // Cooldown
		switch (armatype)
		{
		case Mochila:
			arma->cooldown -= 0.05 * seconds;
			break;
		case Elastico:
			arma->cooldown -= 0.1 * seconds;
			break;
		default:
			break;
		}
		break;
	case 2: // Damage
		switch (armatype)
		{
		case Mochila:
			arma->damage += 5;
			break;
		case Elastico:
			arma->damage += 1;
			break;
		default:
			break;
		}
		break;
	case 3: // Duration
		break;
	case 4: // Range
		switch (armatype)
		{
		case Mochila:
			arma->range += 5;
			break;
		default:
			break;
		}
		break;
	case 5: // Active
		switch (armatype)
		{
		case Elastico:
			arma->active_max += 1;
			break;

		default:
			break;
		}
		break;
	default:
		break;
	}
}

int Get_Weapon_index(ArmaTipo tipo)
{
	for (int i = 0; i < Max_Weapons; i++)
	{
		if (selecionadas[i].tipo == tipo)
			return i;
	}
	return -1;
}
