#include "Name.h"

Name::Name( )
{
    str = "";

    text[0] = NULL;
    text[1] = NULL;

    rect[0].x = 1024/2 - 120;
    rect[0].y = 768/2;
    rect[1].x = 1024/2 - 120;
    rect[1].y = 768/2-80;

    color.r = 0;
    color.g = 255;
    color.b = 0;

    font = TTF_OpenFont( "main/defused.ttf", 40 );

    text[1] = TTF_RenderText_Solid( font, "Enter Name:", color );

    SDL_EnableUNICODE( SDL_ENABLE );
}

Name::~Name( )
{
    SDL_FreeSurface( text[0] );
    SDL_FreeSurface( text[1] );

    SDL_EnableUNICODE( SDL_DISABLE );
}

std::string Name::handleInput( SDL_Surface*& screen, SDL_Surface*& background )
{
    str = "";
    SDL_FreeSurface( text[0] );
    text[0] = TTF_RenderText_Solid( font, str.c_str( ), color );

    while( 1 )
    {
        startTick = SDL_GetTicks( );
        while( SDL_PollEvent( &currentEvent ) )
        {
            if( currentEvent.type == SDL_KEYDOWN )
            {
                std::string temp = str;

                if( str.length( ) <= 16 )
                {
                    if( currentEvent.key.keysym.unicode == ( Uint16 )' ' )
                    {
                        str += (char)currentEvent.key.keysym.unicode;
                    }
                    else if( ( currentEvent.key.keysym.unicode >= ( Uint16 )'0' ) && ( currentEvent.key.keysym.unicode <= (Uint16)'9' ) )
                    {
                        str += (char)currentEvent.key.keysym.unicode;
                    }
                    else if( ( currentEvent.key.keysym.unicode >= ( Uint16 )'A' ) && ( currentEvent.key.keysym.unicode <= (Uint16)'Z' ) )
                    {
                        str += (char)currentEvent.key.keysym.unicode;
                    }
                    else if( ( currentEvent.key.keysym.unicode >= ( Uint16 )'a' ) && ( currentEvent.key.keysym.unicode <= (Uint16)'z' ) )
                    {
                        str += (char)currentEvent.key.keysym.unicode;
                    }
                }

                if( ( currentEvent.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length( ) != 0 ) )
                {
                    str.erase( str.length( ) - 1 );
                }

                if( str != temp )
                {
                    SDL_FreeSurface( text[0] );
                    text[0] = TTF_RenderText_Solid( font, str.c_str( ), color );
                }

                if( ( currentEvent.key.keysym.sym == SDLK_RETURN ) || ( currentEvent.key.keysym.sym == SDLK_KP_ENTER ) )
                {
                    return str;
                }
            }
        }

        SDL_BlitSurface( background, NULL, screen, NULL );

        if( text[0] != NULL )
            SDL_BlitSurface( text[0], NULL, screen, &rect[0] );
        if( text[1] != NULL )
            SDL_BlitSurface( text[1], NULL, screen, &rect[1] );

        SDL_Flip( screen );
        if( SDL_GetTicks( ) - startTick < 1000 / 30 )
        {
            SDL_Delay( ( 1000 / 30 ) - ( SDL_GetTicks() - startTick ) );
        }
    }
}
