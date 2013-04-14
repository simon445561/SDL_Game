#include "Splash.h"

bool Splash::Show( SDL_Surface*& screen )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( "main/brain-blog-pic.jpg" );

    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
    }

    SDL_BlitSurface( optimizedImage, NULL, screen, NULL );
    SDL_Flip( screen );

    SDL_Event currentEvent;

    while( 1 )
    {
        while( SDL_PollEvent( &currentEvent ) )
        {
            if( currentEvent.type == SDL_KEYDOWN || currentEvent.type == SDL_MOUSEBUTTONDOWN )
            {
                return true;
            }
        }
        SDL_Delay( 500 );
    }
}
