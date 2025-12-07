#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>



typedef enum{
  Comum,
  Estagiario,
  Faxineira,
  Vice_chefe,
  RH,
  Segurança,
} PlayerTipo;

typedef struct 
{
  int player_hp;
  int player_Maxhp;
  float damage;
  float movement_speed;
  float xp;
  float xp_for_level_up;
  int level;
  int has_leveled_up;
  float posX, posY;
  float luck;
  Uint32 last_damage_time;
  Uint32 invencibility_time;
  SDL_Texture* sprite;
  int current_frame;
  float animation_time;
  SDL_Rect box;
  int dir;
  int is_moving;
  int alive;
  SDL_Rect bar_hp;
  SDL_Rect bar_HPoutline;
  SDL_Rect bar_XP;
  SDL_Rect bar_XPoutline;
}Player;

extern Player player;

void Create_player(int i, SDL_Renderer* renderer);
void Take_damage(int damage);
void Get_exp(float xp);
void Levelup();
void Render_player(SDL_Renderer *renderer);
void Render_HPbar(SDL_Renderer* ren);
void Render_XPbar(SDL_Renderer* ren);
#endif
