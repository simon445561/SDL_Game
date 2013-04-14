#ifndef _NAME_H
#define _NAME_H

#include "Includes.h"

class Name
{
    public:
    Name ( );
    ~Name( );

    std::string handleInput ( SDL_Surface*&, SDL_Surface*& );

    private:
    int         startTick;
    std::string str;
    TTF_Font    *font;
    SDL_Surface *text[2];
    SDL_Rect    rect [2];
    SDL_Color   color;
    SDL_Event   currentEvent;

};

#endif // _NAME_H
