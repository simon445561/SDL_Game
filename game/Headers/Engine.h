#ifndef _ENGINE_H
#define _ENGINE_H

#include "Includes.h"
#include "Square.h"
#include "Player.h"
#include "Splash.H"
#include "Menu.h"
#include "Name.h"
#include "Death.h"
#include "HighScore.h"

class Engine
{
public:
    Engine    ( );
    ~Engine   ( );
    void start( );

private:
    bool isExiting    ( );
    void EngineLoop   ( );
    void showSplash   ( );
    void Starting     ( );
    void showMenu     ( );
    void Game         ( );
    void Restart      ( );
    void showHighScore( );
    void enterName    ( );
    void showDeath    ( );
    void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
    int  Loaded;
    int  startTick;
    int  maxTime;
    int  numBonus;
    int  numBadBonus;
    int  prevBadBonus;
    int  prevbonus;

    enum   EngineState{ initializing, showingSplash, showingMenu, enteringName,
           playing, exiting, showingDeath, restart, starting, showingHighscore };
    static EngineState engineState;

    Square      square[4][6];
    Player      player;
    Menu        menu;
    Name        name;
    Death       death;
    Score       score;
    Splash      splash;
    SDL_Rect    Clip[3];
    TTF_Font    *font;
    SDL_Color   textColor[2];

    std::string scoreString[2];
    std::stringstream   str;

    SDL_Surface *objectTexture;
    SDL_Surface *textSurface[2];
    SDL_Surface *text;
    SDL_Surface *screen;
    SDL_Surface *bonus;
    SDL_Surface *playerTexture;
    SDL_Surface *background;
    SDL_Surface *endtexture;
    SDL_Surface *load_image( std::string filename );

};


#endif // _EGINE_H
