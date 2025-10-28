#include<Player.h>
#include "Weapons.h"

Player player;

void Create_player(int i){
  player.dir = 1;
  switch (i)
  {
  case 0:
    player.player_hp = 100;
    player.damage = 1;
    player.defence = 1;
    player.movement_speed = 5;
    player.xp = 0;
    player.xp_for_level_up = 100;
    player.box.x = 384;
    player.box.y = 284;
    player.box.w = 32;
    player.box.h = 32;
    player.last_damage_time = 0;
    player.invencibility_time = 500;

    Select_Weapon(0);
    break;
    default:
      break;
  }
}

void Take_damage(int damage){
  player.player_hp -= damage;
}



void Get_xp(float xp){
  player.xp += xp;
  if(player.xp >= player.xp_for_level_up){
    player.xp = player.xp - player.xp_for_level_up;
    Levelup();
  }
}

void Levelup(){
  return ;
}

void Render_player(SDL_Renderer *renderer){
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 200);
  SDL_RenderFillRect(renderer, &player.box);
}
