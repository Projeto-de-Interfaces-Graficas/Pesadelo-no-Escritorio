#include "Experience.h"

void Experience_CreateXp(ExperiencePoint* xp, ExperienceType type) {
    xp->type = type;
    switch(type) {
        case XP_SMALL:
            xp->amount = 25;
        case XP_MEDIUM:
            xp->amount = 50;
        case XP_LARGE:
            xp->amount = 75;
    }
}