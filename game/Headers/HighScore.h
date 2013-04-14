#ifndef _HIGHSCORE_H
#define _HIGHSCORE_H

#include "Includes.h"

class Score
{
public:
    Score ( );
    ~Score( );

    void Write ( int Score, std::string Name );
    void Read  ( );
    int  Output( SDL_Surface*&, SDL_Surface*& );

    struct HighScore
    {
        std::string name;
        int score;
    };
    struct myclass
    {
        bool operator( ) ( HighScore const& i,HighScore const& j ) { return ( i.score > j.score );}
    } Sort;

private:
    int         x;
    int         y;
    int         startTick;

    std::vector<HighScore> vScore;
    HighScore              tmp;

    std::ofstream filein;
    std::ifstream fileout;
    std::string   item        [13];
    std::stringstream  neki;

    SDL_Surface *textSurface  [13];
    TTF_Font    *font;
    SDL_Event   currentEvent;
    SDL_Rect    textRect      [13];
    SDL_Color   textColor     [2];

};

#endif
