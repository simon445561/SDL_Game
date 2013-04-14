#include "Menu.h"

Menu::Menu( )
{
    for( int i=0; i<3; i++ )
    {
        textRect[i].x = 1024/2-90;
        textRect[i].y = ((786/2)-75) + (60 *i);
    }

    x = 0;
    y = 0;

    textColor[0].r = 0;
    textColor[0].g = 255;
    textColor[0].b = 0;

    textColor[1].r = 0;
    textColor[1].g = 255;
    textColor[1].b = 255;

    item[0] = "Start";
    item[1] = "High Score";
    item[2] = "Exit";

    font = TTF_OpenFont( "main/defused.ttf", 40 );

    textSurface[0] = TTF_RenderText_Solid( font, item[0].c_str(), textColor[0] );
    textSurface[1] = TTF_RenderText_Solid( font, item[1].c_str(), textColor[0] );
    textSurface[2] = TTF_RenderText_Solid( font, item[2].c_str(), textColor[0] );
}

Menu::~Menu( )
{
    for( int i=0; i<3; i++ )
    {
        SDL_FreeSurface( textSurface[i] );
    }
}

int Menu::Draw( SDL_Surface*& screen )
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
                    for( int i=0; i<3; i++ )
                    {
                        if( ( x >= textRect[i].x ) && ( x <= textRect[i].x + textRect[i].w )
                        &&  ( y >= textRect[i].y ) && ( y <= textRect[i].y + textRect[i].h ) )
                        {
                            SDL_FreeSurface( textSurface[i] );
                            textSurface[i] = TTF_RenderText_Solid( font, item[i].c_str(), textColor[1] );
                        }
                        else
                        {
                            SDL_FreeSurface( textSurface[i] );
                            textSurface[i] = TTF_RenderText_Solid( font, item[i].c_str(), textColor[0] );
                        }
                    }
                break;
                case SDL_MOUSEBUTTONDOWN:
                    for( int i=0; i<3; i++ )
                    {
                        if( ( x >= textRect[i].x ) && ( x <= textRect[i].x + textRect[i].w )
                        &&  ( y >= textRect[i].y ) && ( y <= textRect[i].y + textRect[i].h ) )
                        {
                            return i;
                        }
                    }
                break;
                case SDL_QUIT:
                    return 2;
            }
        }
        for( int i=0; i<3; i++ )
        {
            SDL_BlitSurface( textSurface[i], NULL, screen, &textRect[i] );
        }

        SDL_Flip( screen );
        if( SDL_GetTicks( ) - startTick < 1000 / 30 )
        {
            SDL_Delay( ( 1000 / 30 ) - (SDL_GetTicks() - startTick) );
        }
    }
}
