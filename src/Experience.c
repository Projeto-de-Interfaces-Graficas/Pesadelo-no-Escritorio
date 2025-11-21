#include "Experience.h"

void Experience_CreateXp(ExperiencePoint* xp, ExperienceType type, int x, int y, int size, SDL_Texture* sprite) {
    xp->type = type;
    xp->sprite = sprite;
    switch(type) {
        case XP_SMALL:
            xp->amount = 5;
            break;
        case XP_MEDIUM:
            xp->amount = 5;
            break;
        case XP_LARGE:
            xp->amount = 15;
            break;
    }
    xp->renderBox.x = x - size / 2;
    xp->renderBox.y = y - size / 2;
    xp->renderBox.w = size;
    xp->renderBox.h = size;

    xp->hitBox.w = size * 0.75;
    xp->hitBox.h = size * 0.75;
    xp->hitBox.x = xp->renderBox.x + (size - xp->hitBox.w) / 2;
    xp->hitBox.y = xp->renderBox.y + (size - xp->hitBox.h) / 2;

    xp->active = 1;
}