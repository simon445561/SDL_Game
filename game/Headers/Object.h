#ifndef _KVADRATKI_H
#define _KVADRATKI_H

#include "Includes.h"

class GameObject
{
public:
    GameObject         ( );
    virtual ~GameObject( );

    virtual int  getClip( );
    virtual void setClip( int );
    virtual bool Loaded ( );
    virtual void Load   ( bool );
    virtual void Draw   ( SDL_Surface*& screen, SDL_Surface*& texture, SDL_Rect Clip[] );
    virtual void SetPosition ( int x, int y );
    virtual int  getPositionX( );
    virtual int  getPositionY( );

private:
    SDL_Rect Object;
    bool     isLoaded;
    int      clip;

};

#endif // _KVADRATKI_H
