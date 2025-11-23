#ifndef FONTS_H
#define FONTS_H

#include <SDL2/SDL_ttf.h>

typedef struct {
    TTF_Font* sizes[65];
} FontCache;

void Fonts_Init();
void Fonts_Destroy();
TTF_Font* Fonts_FitTextInRect(const char* text, int maxW, int maxH, int maxFontSize);

extern FontCache fonts;

#endif