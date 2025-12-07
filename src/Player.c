#include<Player.h>
#include <SDL2/SDL_image.h>
#include "Weapons.h"
#include "UpgradeManager.h"

Player player;

void Create_player(int i, SDL_Renderer* renderer){
  player.dir = 1;
  switch (i)
  {
  case 0:
    player.player_hp = 100;
    player.player_Maxhp = 100;
    player.damage = 1;
    player.movement_speed = 200;
    player.xp = 0;
    player.xp_for_level_up = 5;
    player.level = 1;
    player.has_leveled_up = 0;
    player.sprite = IMG_LoadTexture(renderer, "assets/images/characters/comum.png");
    player.box.x = 384;
    player.box.y = 284;
    player.box.w = 48;
    player.box.h = 48;
    player.last_damage_time = 0;
    player.invencibility_time = 500;
    player.posX = 384;
    player.posY = 284;
    player.luck = 1;
    player.alive = 1;
    player.is_moving = 0;
    player.current_frame = 0;
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
  if (player.level <= 20) {
    player.xp_for_level_up += 10;
  } else if (player.level <= 40) {
    player.xp_for_level_up += 13;
  } else {
    player.xp_for_level_up += 16;
  }
  player.level += 1;
  player.xp = 0;
  player.has_leveled_up = 1;
}

void Render_player(SDL_Renderer *renderer){
  SDL_Rect renderBox;
  switch (player.current_frame) {
    case 0: renderBox = (SDL_Rect) {0, 0, 32, 32}; break;
    case 1: renderBox = (SDL_Rect) {32, 0, 32, 32}; break;
    case 2: renderBox = (SDL_Rect) {64, 0, 32, 32}; break;
    default: break;
  }

  if (player.dir == -1) {
    SDL_RenderCopyEx(renderer, player.sprite, &renderBox, &player.box, 0, NULL, SDL_FLIP_HORIZONTAL);
  } else {
    SDL_RenderCopy(renderer, player.sprite, &renderBox, &player.box);
  } 
}

void Render_HPbar(SDL_Renderer* ren){
  player.bar_HPoutline.w  = 50;
  player.bar_HPoutline.h  = 15;
  player.bar_HPoutline.x  = (player.box.x + (player.box.w) / 2) - player.bar_HPoutline.w/2;
  player.bar_HPoutline.y  = player.box.y-30;
  player.bar_hp.w = ((float)player.player_hp/player.player_Maxhp*player.bar_HPoutline.w);
  player.bar_hp.h = player.bar_HPoutline.h-6;
  player.bar_hp.x = player.bar_HPoutline.x;
  player.bar_hp.y = (player.bar_HPoutline.y + (float)player.bar_HPoutline.h/2) - player.bar_hp.h/2;
  SDL_SetRenderDrawColor(ren, 0, 0, 0, 200);
	SDL_RenderFillRect(ren, &player.bar_HPoutline);
  SDL_SetRenderDrawColor(ren, 255, 0, 0, 200);
	SDL_RenderFillRect(ren, &player.bar_hp);
}

void Render_XPbar(SDL_Renderer* ren){
  player.bar_XPoutline.w  = 800;
  player.bar_XPoutline.h  = 50;
  player.bar_XPoutline.x  = 0;
  player.bar_XPoutline.y  = 550;
  player.bar_XP.w = ((float)player.xp/player.xp_for_level_up*player.bar_XPoutline.w);
  player.bar_XP.h = player.bar_XPoutline.h-10;
  player.bar_XP.x = player.bar_XPoutline.x;
  player.bar_XP.y = (player.bar_XPoutline.y + (float)player.bar_XPoutline.h/2) - player.bar_XP.h/2;
  SDL_SetRenderDrawColor(ren, 100, 100, 100, 200);
	SDL_RenderFillRect(ren, &player.bar_XPoutline);
  SDL_SetRenderDrawColor(ren, 0, 0, 255, 200);
	SDL_RenderFillRect(ren, &player.bar_XP);
}
