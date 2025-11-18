#include"Menus.h"

void RenderStartMenu(SDL_Renderer *ren,int state){
    TTF_Font *fnt = TTF_OpenFont("assets/fonts/VT323/VT323-Regular.ttf",100);
    SDL_Color notselect = {0XFF,0XFF,0XFF,0XFF};
    SDL_Color select = {0X00,0X00,0XFF,0XFF};
    SDL_Surface *start;
    SDL_Surface *quit;
    if(state == 1){
        start = TTF_RenderText_Blended(fnt,"Iniciar",select); 
        quit = TTF_RenderText_Blended(fnt,"Sair",notselect);
    }
    else{
        start = TTF_RenderText_Blended(fnt,"Iniciar",notselect); 
        quit = TTF_RenderText_Blended(fnt,"Sair",select);
    }

    SDL_Texture *starttxt = SDL_CreateTextureFromSurface(ren,start); 
    SDL_Texture *quittxt = SDL_CreateTextureFromSurface(ren,quit);
    SDL_Rect r1={340,200,120,100}; 
    SDL_Rect r2={350,300,100,100};

    SDL_RenderCopy(ren,starttxt,NULL,&r1);
    SDL_RenderCopy(ren,quittxt,NULL,&r2);
}