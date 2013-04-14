#include "Engine.h"

int main( int argc, char *argv[] )
{
    srand( time( NULL ) );

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
        exit( 1 );
    if( TTF_Init( ) < 0 )
        exit( 2 );
    atexit( SDL_Quit );

    Engine engine;
    engine.start();

    return 0;
}
