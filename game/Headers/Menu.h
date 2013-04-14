#ifndef _MENU_H
#define _MENU_H

#include "Includes.h"

class Menu
{
public:
    Menu ( );
    ~Menu( );
    int Draw   ( SDL_Surface*& );

private:
    int x;
    int y;
    int         startTick;
    std::string item        [3];
    TTF_Font    *font;
    SDL_Surface *textSurface[3];
    SDL_Event   currentEvent;
    SDL_Rect    textRect    [3];
    SDL_Color   textColor   [2];

};

#endif // _MENU_H
