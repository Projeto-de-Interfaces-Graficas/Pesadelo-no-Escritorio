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
    player.movement_speed = 200;
    player.xp = 0;
    player.xp_for_level_up = 5;
    player.level = 1;
    player.box.x = 384;
    player.box.y = 284;
    player.box.w = 32;
    player.box.h = 32;
    player.last_damage_time = 0;
    player.invencibility_time = 500;
    player.posX = 384;
    player.posY = 284;
    player.luck = 1;
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
  printf("Nível atual do jogador: %d\n", player.level);
  printf("Qtd. atual de xp necessária para subir de nível: %.0f\n", player.xp_for_level_up);
  if (player.level <= 20) {
    player.xp_for_level_up += 10;
  } else if (player.level <= 40) {
    player.xp_for_level_up += 13;
  } else {
    player.xp_for_level_up += 16;
  }
  player.level += 1;
  player.xp = 0;
  printf("Nível do jogador após o level up: %d\n", player.level);
  printf("Qtd. de xp necessária para subir de nível após o level up: %.0f\n", player.xp_for_level_up);
}

void Render_player(SDL_Renderer *renderer){
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 200);
  SDL_RenderFillRect(renderer, &player.box);
}
