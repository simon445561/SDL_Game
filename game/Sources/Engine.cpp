#include "Engine.h"

Engine::Engine( )
{
    SDL_WM_SetCaption( "Engine!", NULL );

    for( int i=0; i<3; i++ )
    {
        Clip[i].x = 0;
        Clip[i].y = i*100;
        Clip[i].w = 100;
        Clip[i].h = 100;
    }

    screen = SDL_SetVideoMode( 1024, 768, 32, SDL_SWSURFACE );

    background    = load_image  ( "main/bg.bmp" );
    objectTexture = load_image  ( "main/kvadratki.bmp" );
    playerTexture = load_image  ( "main/player.bmp" );
    endtexture    = load_image  ( "main/konc2.bmp" );
    bonus         = load_image  ( "main/bonus.bmp" );

    font = TTF_OpenFont( "main/defused.ttf", 40 );

    SDL_SetColorKey( objectTexture, SDL_SRCCOLORKEY, SDL_MapRGB( screen->format, 0x00, 0xFF, 0xFF ) );
    SDL_SetColorKey( playerTexture, SDL_SRCCOLORKEY, SDL_MapRGB( screen->format, 0x00, 0xFF, 0xFF ) );
    SDL_SetColorKey( endtexture,    SDL_SRCCOLORKEY, SDL_MapRGB( screen->format, 0x00, 0xFF, 0xFF ) );
    SDL_SetColorKey( bonus,         SDL_SRCCOLORKEY, SDL_MapRGB( screen->format, 0x00, 0xFF, 0xFF ) );

    Loaded       = 0;
    numBonus     = 0;
    numBadBonus  = 0;
    maxTime      = 300;
    prevbonus    = 5000;
    prevBadBonus = 3000;

    textColor[0].r = 0;
    textColor[0].g = 255;
    textColor[0].b = 255;

    textColor[1].r = 255;
    textColor[1].g = 0;
    textColor[1].b = 0;

    scoreString[0] = "Score: ";

    scoreString[1] = "CONFUSED!";

    font = TTF_OpenFont( "main/defused.ttf", 40 );

    textSurface[0] = TTF_RenderText_Solid( font, scoreString[0].c_str(), textColor[0] );
    textSurface[1] = TTF_RenderText_Solid( font, scoreString[1].c_str(), textColor[1] );
}

Engine::~Engine( )
{
    SDL_FreeSurface( objectTexture );
    SDL_FreeSurface( playerTexture );
    SDL_FreeSurface( background );
    TTF_Quit( );
    SDL_Quit( );
}

void Engine::start( )
{
    if( engineState != initializing )
        return;

    apply_surface( 0, 0, background, screen );

    for( int i=0; i<4; i++ )
    {
        for( int j=0; j<6; j++ )
        {
            square[i][j].SetPosition( ( j*170 ) +28, ( i*170 )+150 );
        }
    }

    square[3][0].Undead = true;
    square[0][5].Undead = true;
    square[3][0].Load( true );
    square[0][5].Load( true );
    square[3][0].setClip( 0 );
    square[0][5].setClip( 0 );

    engineState = Engine::showingSplash;

    while( !isExiting( ) )
    {
        EngineLoop();
    }

    SDL_Quit();
}

bool Engine::isExiting( )
{
    if( engineState == Engine::exiting )
        return true;
    else
        return false;
}

void Engine::EngineLoop( )
{
    SDL_Event currentEvent;
    startTick = SDL_GetTicks( );
    while( SDL_PollEvent( &currentEvent ) )
    {
        switch( currentEvent.type )
        {
            case SDL_QUIT:
                engineState = Engine::exiting;
            break;
            case SDLK_ESCAPE:
                engineState = Engine::showingMenu;
            break;
        }
        if( currentEvent.type == SDL_KEYDOWN && engineState == Engine::playing )
        {
            switch( currentEvent.key.keysym.sym )
            {
                case SDLK_KP1: if( player.getBonus() ) player.setDirection( 5 ); else player.setDirection( 6 ); player.Move( ); break;
                case SDLK_KP2: if( player.getBonus() ) player.setDirection( 4 ); else player.setDirection( 3 ); player.Move( ); break;
                case SDLK_KP3: if( player.getBonus() ) player.setDirection( 6 ); else player.setDirection( 5 ); player.Move( ); break;
                case SDLK_KP4: if( player.getBonus() ) player.setDirection( 1 ); else player.setDirection( 2 ); player.Move( ); break;
                case SDLK_KP6: if( player.getBonus() ) player.setDirection( 2 ); else player.setDirection( 1 ); player.Move( ); break;
                case SDLK_KP7: if( player.getBonus() ) player.setDirection( 7 ); else player.setDirection( 8 ); player.Move( ); break;
                case SDLK_KP8: if( player.getBonus() ) player.setDirection( 3 ); else player.setDirection( 4 ); player.Move( ); break;
                case SDLK_KP9: if( player.getBonus() ) player.setDirection( 8 ); else player.setDirection( 7 ); player.Move( ); break;
            }
        }
    }
    switch( engineState )
    {
        case Engine::playing:
            Game( );
        break;

        case Engine::showingDeath:
            showDeath( );
        break;

        case Engine::showingSplash:
            showSplash( );
        break;

        case Engine::showingMenu:
            showMenu( );
        break;

        case Engine::restart:
            Restart( );
        break;

        case Engine::starting:
            Starting( );
        break;

        case Engine::showingHighscore:
            showHighScore( );
        break;

        case Engine::enteringName:
            enterName( );
        break;
    }
    SDL_Flip( screen );

    if( SDL_GetTicks( ) - startTick < 1000 / 30 )
    {
        SDL_Delay( ( 1000 / 30 ) - (SDL_GetTicks() - startTick) );
    }
}

void Engine::Game( )
{
    apply_surface( 0, 0, background, screen );
    for( int i=0; i<4; i++ )
    {
        for( int j=0; j<6; j++ )
        {
            if( Loaded < 15 )
            {
                if( !square[i][j].Loaded( ) )
                {
                    if( ( rand( ) %500 ) %100 == 0 )
                    {
                        square[i][j].Load( true );
                        Loaded++;
                        square[i][j].setTime( maxTime );
                        square[i][j].setBonus( false );
                    }
                }
            }
            if( square[i][j].Loaded( ) )
            {
                if( i == 0 && j == 5 )
                    apply_surface( (5*170)+28, 150, endtexture, screen );
                else
                    square[i][j].Draw( screen, objectTexture, Clip );
            }
            else
            {
                if( player.Collision( player.getPositionX( ), player.getPositionY( ), square[i][j].getPositionX( ), square[i][j].getPositionY( ) ) )
                {
                    player.setBonus( false );
                    engineState = Engine::showingDeath;
                    for( int i=0; i<4; i++ )
                    {
                        for( int j=0; j<6; j++ )
                        {
                            if( !square[i][j].Undead && square[i][j].Loaded( ) )
                            {
                                square[i][j].Load( false );
                                Loaded--;
                                square[i][j].setTime( -1 );
                            }
                            if( square[i][j].getBonus( ) )
                            {
                                square[i][j].setBonus( false );
                                numBonus--;
                            }
                            if( square[i][j].getBonus2( ) )
                            {
                                square[i][j].setBonus2( false );
                                numBadBonus--;
                            }
                        }
                    }
                }
            }

            if( numBonus < 2 && !square[i][j].Undead && square[i][j].Loaded() && !square[i][j].getBonus() && prevbonus == 0 && !square[i][j].getBonus2() )
            {
                square[i][j].setBonus( true );
                numBonus++;
                prevbonus = 4000;
            }

            if( numBadBonus < 2 && !square[i][j].Undead && square[i][j].Loaded() && !square[i][j].getBonus() && prevBadBonus == 0 && !square[i][j].getBonus2() )
            {
                square[i][j].setBonus2( true );
                numBadBonus++;
                prevBadBonus = 3000;
            }

            if( square[i][j].getBonus( ) )
            {
                apply_surface( square[i][j].getPositionX(), square[i][j].getPositionY(), bonus, screen );
            }

            if( square[i][j].getBonus( ) )
            {
                if(  player.Collision( player.getPositionX( ), player.getPositionY( ), square[i][j].getPositionX( ), square[i][j].getPositionY( ) ) )
                {
                    player.setLevel( player.getLevel()+1 );
                    square[i][j].setBonus( false );
                    numBonus--;
                }
            }

            if( square[i][j].getBonus2( ) )
            {
                if(  player.Collision( player.getPositionX( ), player.getPositionY( ), square[i][j].getPositionX( ), square[i][j].getPositionY( ) ) )
                {
                    player.setBonus( true );
                    square[i][j].setBonus2( false );
                    numBadBonus--;
                }
            }

            if( player.Collision( player.getPositionX( ), player.getPositionY( ), square[0][5].getPositionX( ), square[0][5].getPositionY( ) ) )
            {
                player.setBonus( false );
                player.setLevel( player.getLevel( )+1 );
                player.SetPosition( 28, (3*170) + 150 );
                if( maxTime > 100 )
                    maxTime--;
                for( int i=0; i<4; i++ )
                {
                    for( int j=0; j<6; j++ )
                    {
                        if( !square[i][j].Undead && square[i][j].Loaded( ) )
                        {
                            square[i][j].Load( false );
                            Loaded--;
                            square[i][j].setTime( -1 );
                        }
                        if( square[i][j].getBonus( ) )
                        {
                            square[i][j].setBonus( false );
                            numBonus--;
                        }
                        if( square[i][j].getBonus2( ) )
                        {
                            square[i][j].setBonus2( false );
                            numBadBonus--;
                        }
                    }
                }
            }
            if( square[i][j].Loaded() && !square[i][j].Undead )
            {
                if( square[i][j].getTime( ) == (maxTime / 1) )
                    square[i][j].setClip( 0 );
                if( square[i][j].getTime( ) == (maxTime / 2) )
                    square[i][j].setClip( 1 );
                if( square[i][j].getTime( ) == (maxTime / 3) )
                    square[i][j].setClip( 2 );
                if( square[i][j].getTime( ) == 0 )
                {
                    square[i][j].setClip( 0 );
                    square[i][j].Load( false );
                    Loaded--;
                    if( square[i][j].getBonus() )
                    {
                        square[i][j].setBonus( false );
                        numBonus--;
                    }
                    if( square[i][j].getBonus2() )
                    {
                        square[i][j].setBonus2( false );
                        numBadBonus--;
                    }
                }
                square[i][j].setTime( (square[i][j].getTime())-1 );
                if( prevbonus > 0 )
                    prevbonus--;
                if( prevBadBonus > 0 )
                    prevBadBonus--;
            }
        }
    }

    if( player.getBonus( ) )
    {
        apply_surface( 480, 50, textSurface[1], screen );
    }

    str << player.getLevel( );
    scoreString[0].resize(7);
    scoreString[0] += str.str();

    str.clear( );
    str.str(std::string( ));

    textSurface[0] = TTF_RenderText_Solid( font, scoreString[0].c_str(), textColor[0] );
    apply_surface( 100, 50, textSurface[0], screen );

    SDL_FreeSurface( textSurface[0] );
    player.Draw( screen, playerTexture, NULL );
}

void Engine::Starting( )
{
    maxTime = 300;
    prevbonus    = 5000;
    prevBadBonus = 3000;

    player.SetPosition( 28, (3*170) + 150 );
    player.setLevel( 1 );

    engineState = Engine::enteringName;
}

void Engine::Restart( )
{
    maxTime = 300;
    prevbonus    = 5000;
    prevBadBonus = 3000;

    player.SetPosition( 28, (3*170) + 150 );
    player.setLevel( 1 );

    engineState = Engine::playing;
}

void Engine::enterName( )
{
    apply_surface( 0, 0, background, screen );
    player.setName( name.handleInput( screen, background ) );
    engineState = Engine::playing;
}

void Engine::showHighScore( )
{
    switch( score.Output( screen, background ) )
    {
        case 0:
            engineState = Engine::showingMenu;
        break;
        case 1:
            engineState = Engine::exiting;
        break;
    }
}

void Engine::showDeath( )
{
    score.Write( player.getLevel( ), player.getName( ) );

    switch( death.Draw( screen, background ) )
    {
        case 1:
            engineState = Engine::showingMenu;
        break;
        case 2:
            engineState = Engine::restart;
        break;
        case 3:
            engineState = Engine::exiting;
        break;
    }
}

void Engine::showSplash( )
{
    if( splash.Show( screen ) )
        engineState = Engine::showingMenu;
}

void Engine::showMenu( )
{
    apply_surface( 0, 0, background, screen );

    switch( menu.Draw( screen ) )
    {
        case 0:
            engineState = Engine::starting;
        break;
        case 1:
            engineState = Engine::showingHighscore;
        break;
        case 2:
            engineState = Engine::exiting;
        break;
    }
}

SDL_Surface* Engine::load_image( std::string filename )
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL )
    {
        optimizedImage = SDL_DisplayFormat( loadedImage );
        SDL_FreeSurface( loadedImage );
    }

    return optimizedImage;
}

void Engine::apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, NULL, destination, &offset );
}

Engine::EngineState Engine::engineState = initializing;
