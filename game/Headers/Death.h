#ifndef _DEATH_H
#define _DEATH_H

#include "Includes.h"

class Death
{
public:
    Death ( );
    ~Death( );
    int Draw( SDL_Surface*& screen, SDL_Surface*& );

private:
    int         x;
    int         y;
    int         startTick;
    std::string item  [3];
    SDL_Surface *text [3];
    TTF_Font    *font;
    SDL_Rect    rect  [3];
    SDL_Color   color [2];
    SDL_Event   currentEvent;
};

#endif
