#include<Weapons.h>

#define seconds 100

Arma selecionadas[3];

void Selct_Weapon(int tipo){
  switch (tipo)
  {
  case 0:
    Arma chicote;
    chicote.cooldown = 10;
    chicote.damage =3;
    chicote.duration = 2;
    chicote.range = 50;
    chicote.recharging_time = 0;
    chicote.tipo = ARMA_CHICOTE;
    chicote.active = 0;
    selecionadas[0] = chicote;
    break;
  default:
    break;
  }
}

void Active_Weapon(int x , int y,int arma){
  switch (arma)
  {
  case ARMA_CHICOTE:
    selecionadas[0].box.x = x;
    selecionadas[0].box.y = y;
    selecionadas[0].box.w = 50;
    selecionadas[0].box.h = 50;
    selecionadas[0].active = 1;
    selecionadas[0].is_on_screen = 0;
    break;
  
  default:
    break;
  }
}

void DrawWeapons(SDL_Renderer *renderer){
  for(int i=0;i<1;i++){
    if(selecionadas[i].active){
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
      SDL_RenderFillRect(renderer, &selecionadas[i].box);
    }
  }
}

void ATT_Duration_Weapon(Uint32 tempo_execucao){
  for(int i=0;i<1;i++){
    if(selecionadas[i].active){
      selecionadas[i].is_on_screen += tempo_execucao;
      if( selecionadas[i].is_on_screen>= selecionadas[i].duration){
        selecionadas[i].active = 0;
      }
    }
    else{
      selecionadas[i].recharging_time += tempo_execucao;
      if(selecionadas[i].recharging_time >= selecionadas[i].cooldown){
        Active_Weapon(400,400,0);
        selecionadas[i].recharging_time = 0;
      }
    }
  }
}
