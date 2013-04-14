#include "Object.h"

GameObject::GameObject( )
{
    isLoaded = false;
    clip = 0;
}

GameObject::~GameObject( )
{

}

void GameObject::SetPosition( int x, int y )
{
    Object.x = x;
    Object.y = y;
}

void GameObject::Load( bool Load )
{
    isLoaded = Load;
}

bool GameObject::Loaded()
{
    return isLoaded;
}

void GameObject::Draw( SDL_Surface*& screen, SDL_Surface*& texture, SDL_Rect Clip[] )
{
    if( isLoaded )
    {
        SDL_BlitSurface( texture, &Clip[clip], screen, &Object );
    }
}

void GameObject::setClip( int a )
{
    clip = a;
}

int GameObject::getClip( )
{
    return clip;
}

int GameObject::getPositionX( )
{
    return Object.x;
}

int GameObject::getPositionY( )
{
    return Object.y;
}
