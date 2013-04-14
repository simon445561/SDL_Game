#include "HighScore.h"

Score::Score( )
{
    for( int i=0; i<10; i++ )
    {
        textRect[i].x = 200;
        textRect[i].y = (60 *i)+100;
    }

    textRect[10].x = 1024/2 -120;
    textRect[10].y = 50;
    textRect[11].x = 1024/2 -100;
    textRect[11].y = 700;

    x = 0;
    y = 0;

    textColor[0].r = 0;
    textColor[0].g = 255;
    textColor[0].b = 0;

    textColor[1].r = 0;
    textColor[1].g = 255;
    textColor[1].b = 255;


    item[10] = "High Score:";
    item[11] = "Menu";

    font = TTF_OpenFont( "main/defused.ttf", 40 );

    textSurface[10] = TTF_RenderText_Solid( font, item[10].c_str( ), textColor[0] );
    textSurface[11] = TTF_RenderText_Solid( font, item[11].c_str( ), textColor[0] );

    for( int i=0; i<10; i++ )
    {
        textSurface[i] = TTF_RenderText_Solid( font, item[i].c_str( ), textColor[0] );
    }
}

Score::~Score( )
{

}

void Score::Write( int Score, std::string Name )
{
    if( vScore.empty( ) )
        Read( );

    tmp.name  = Name;
    tmp.score = Score;

    vScore.push_back( tmp );

    std::sort( vScore.begin( ), vScore.end( ), Sort );

    if( vScore.size( ) > 10 )
        vScore.resize( 10 );

    remove( "score.txt" );

    filein.open( "score.txt" );

    if (filein.is_open())
    {
        for( int i=0; i<vScore.size( ); i++ )
        {
            filein << vScore.at( i ).name;
            filein << ',';
            filein << vScore.at( i ).score;
            filein << '\n';
        }
    }
    filein.close( );
}

void Score::Read( )
{
    std::string line, test;
    fileout.open( "score.txt" );

    if( fileout.is_open( ) )
    {
        while( getline( fileout, line ) )
        {
            std::istringstream iss( line );
            std::getline( iss, tmp.name, ',' );
            iss >> tmp.score;
            vScore.push_back( tmp );
        }
        std::sort( vScore.begin( ), vScore.end( ), Sort );
    }
    fileout.close( );
}

int Score::Output( SDL_Surface*& screen, SDL_Surface*& background )
{
    if( vScore.empty( ) )
        Read( );

    for( int i=0; i<10; i++ )
    {
        item[i] = "";
    }

    for( int i=0; i<10; i++ )
    {
        neki << i+1;
        item[i] = neki.str( );
        neki.clear();
        neki.str(std::string());
    }

    for( int i=0; i<10; i++ )
    {
        if( vScore.size() > i )
        {
            neki.clear();
            neki.str(std::string());
            neki << vScore.at(i).score;
            for( int lenght=0; lenght<( 8 - ((i+1)/10) ); lenght++ )
                item[i] += " ";
            item[i] += vScore.at(i).name;
            for( int lenght=0; lenght<( 16 - vScore.at(i).name.size( ) ); lenght++ )
                item[i] += " ";
            item[i] += neki.str();
        }
    }

    for( int i=0; i<10; i++ )
    {
        textSurface[i] = TTF_RenderText_Solid( font, item[i].c_str( ), textColor[0] );
    }

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

                    if( ( x >= textRect[11].x ) && ( x <= textRect[11].x + textRect[11].w )
                    &&  ( y >= textRect[11].y ) && ( y <= textRect[11].y + textRect[11].h ) )
                    {
                        SDL_FreeSurface( textSurface[11] );
                        textSurface[11] = TTF_RenderText_Solid( font, item[11].c_str( ), textColor[1] );
                    }
                    else
                    {
                        SDL_FreeSurface( textSurface[11] );
                        textSurface[11] = TTF_RenderText_Solid( font, item[11].c_str( ), textColor[0] );
                    }

                break;
                case SDL_MOUSEBUTTONDOWN:
                    if( ( x >= textRect[11].x ) && ( x <= textRect[11].x + textRect[11].w )
                    &&  ( y >= textRect[11].y ) && ( y <= textRect[11].y + textRect[11].h ) )
                    {
                        return 0;
                    }
                break;
                case SDL_QUIT:
                    return 1;
            }
        }

        SDL_BlitSurface( background, NULL, screen, NULL );

        for( int i=0; i<12; i++ )
        {
            SDL_BlitSurface( textSurface[i], NULL, screen, &textRect[i] );
        }

        SDL_Flip( screen );
        if( SDL_GetTicks( ) - startTick < 1000 / 30 )
        {
            SDL_Delay( ( 1000 / 30 ) - (SDL_GetTicks( ) - startTick) );
        }
    }
}
