#include "Death.h"

Death::Death( )
{
    font = TTF_OpenFont( "main/defused.ttf", 40 );

    x = 0;
    y = 0;

    color[0].r = 255;
    color[0].g = 0;
    color[0].b = 0;

    color[1].r = 0;
    color[1].g = 255;
    color[1].b = 0;

    color[2].r = 0;
    color[2].g = 255;
    color[2].b = 255;

    rect[0].x = 1024/2 -140;
    rect[0].y = 768/2 -70;

    rect[1].x = 120;
    rect[1].y = 700;

    rect[2].x = 648;
    rect[2].y = 700;

    item[0] = "You Died!";
    item[1] = "Menu";
    item[2] = "Restart";

    text[0] = TTF_RenderText_Solid( font, item[0].c_str( ), color[0] );
    text[1] = TTF_RenderText_Solid( font, item[1].c_str( ), color[1] );
    text[2] = TTF_RenderText_Solid( font, item[2].c_str( ), color[1] );
}

Death::~Death( )
{
    for( int i=0; i<3; i++ )
    {
        SDL_FreeSurface( text[i] );
    }
}

int Death::Draw( SDL_Surface*& screen, SDL_Surface*& background )
{
    while( 1 )
    {
        startTick = SDL_GetTicks( );

        while( SDL_PollEvent( &currentEvent ) )
        {
            switch( currentEvent.type )
            {
                case SDL_MOUSEMOTION:
                    x = currentEvent.motion.x;
                    y = currentEvent.motion.y;
                    for( int i=1; i<3; i++ )
                    {
                        if( ( x >= rect[i].x ) && ( x <= rect[i].x + rect[i].w )
                        &&  ( y >= rect[i].y ) && ( y <= rect[i].y + rect[i].h ) )
                        {
                            SDL_FreeSurface( text[i] );
                            text[i] = TTF_RenderText_Solid( font, item[i].c_str(), color[2] );
                        }
                        else
                        {
                            SDL_FreeSurface( text[i] );
                            text[i] = TTF_RenderText_Solid( font, item[i].c_str(), color[1] );
                        }
                    }
                break;
                case SDL_MOUSEBUTTONDOWN:
                    for( int i=1; i<3; i++ )
                    {
                        if( ( x >= rect[i].x ) && ( x <= rect[i].x + rect[i].w )
                        &&  ( y >= rect[i].y ) && ( y <= rect[i].y + rect[i].h ) )
                        {
                            return i;
                        }
                    }
                break;
                case SDL_QUIT:
                    return 3;
            }
        }
        SDL_BlitSurface( background, NULL, screen, NULL );

        for( int i=0; i<3; i++ )
        {
            SDL_BlitSurface( text[i], NULL, screen, &rect[i] );
        }

        SDL_Flip( screen );
        if( SDL_GetTicks( ) - startTick < 1000 / 30 )
        {
            SDL_Delay( ( 1000 / 30 ) - (SDL_GetTicks() - startTick) );
        }
    }
}
