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
  float damage;
  float defence;
  float movement_speed;
  float xp;
  float xp_for_level_up;
  float posX, posY;
  float luck;
  Uint32 last_damage_time;
  Uint32 invencibility_time;
  SDL_Rect box;
  int dir;
}Player;

extern Player player;

void Create_player(int i);
void Take_damage(int damage);
void Get_exp(float xp);
void Levelup();
void Render_player(SDL_Renderer *renderer);

#endif
