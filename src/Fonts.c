#include "Fonts.h"

FontCache fonts;

void Fonts_Init(const char* fontPath) {
    for (int i = 8; i < 65; i++) {
        fonts.sizes[i] = TTF_OpenFont(fontPath, i);
    }
}

void Fonts_Destroy() {
    for (int i = 8; i < 65; i++) {
        TTF_CloseFont(fonts.sizes[i]);
    }
}

TTF_Font* Fonts_FitTextInRect(const char* text, int maxW, int maxH, int maxFontSize) {
    int w, h;
    if (maxFontSize >= 64) {
        maxFontSize = 64;
    }

    for (int size = maxFontSize; size >= 8; size--) {
        TTF_Font* font = fonts.sizes[size];
        SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, text, (SDL_Color){255, 255, 255, 255}, maxW); 
        w = surface->w;
        h = surface->h;
        SDL_FreeSurface(surface);
        if (w <= maxW && h <= maxH) {
            return font;
        }
    }

    return fonts.sizes[8];
}