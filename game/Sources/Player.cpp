#include "Player.h"

Player::Player( )
{
    SetPosition( 28, (3*170) + 150 );
    Load( true );
    Direction = 0;
    Bonus = false;
    Level = 1;
}

Player::~Player( )
{

}

bool Player::Collision( int x, int y, int xSquare, int ySquare )
{
    if( x >= xSquare && x+100 <= xSquare+100
    &&  y >= ySquare && y+100 <= ySquare+100 )
        return true;
    return false;
}

bool Player::Collision( int x, int y )
{
    if( x > 27 && x < 879
    &&  y > 149 && y < 661 )
        return true;
    return false;
}

void Player::Move( )
{
    switch ( Direction )
    {
        case 1:
        if( Collision( getPositionX( )+170, getPositionY( ) ) )
        SetPosition( getPositionX( )+170, getPositionY( ) );
        Direction = 0;
        break;
        case 2:
        if( Collision( getPositionX( )-170, getPositionY( ) ) )
        SetPosition( getPositionX( )-170, getPositionY( ) );
        Direction = 0;
        break;
        case 3:
        if( Collision( getPositionX( ), getPositionY( )+170 ) )
        SetPosition( getPositionX( ), getPositionY( )+170 );
        Direction = 0;
        break;
        case 4:
        if( Collision( getPositionX( ), getPositionY( )-170 ) )
        SetPosition( getPositionX( ), getPositionY( )-170 );
        Direction = 0;
        break;
        case 5:
        if( Collision( getPositionX( )+170, getPositionY( )+170 ) )
        SetPosition( getPositionX( )+170, getPositionY( )+170 );
        Direction = 0;
        break;
        case 6:
        if( Collision( getPositionX( )-170, getPositionY( )+170 ) )
        SetPosition( getPositionX( )-170, getPositionY( )+170 );
        Direction = 0;
        break;
        case 7:
        if( Collision( getPositionX( )+170, getPositionY( )-170 ) )
        SetPosition( getPositionX( )+170, getPositionY( )-170 );
        Direction = 0;
        break;
        case 8:
        if( Collision( getPositionX( )-170, getPositionY( )-170 ) )
        SetPosition( getPositionX( )-170, getPositionY( )-170 );
        Direction = 0;
        break;
    }
}

int Player::getDirection( )
{
    return Direction;
}

void Player::setDirection( short currentDirection )
{
    Direction = currentDirection;
}

int Player::getLevel( )
{
    return Level;
}

void Player::setLevel( int currentLevel )
{
    Level = currentLevel;
}

bool Player::getBonus( )
{
    return Bonus;
}

void Player::setBonus( bool currentBonus )
{
    Bonus = currentBonus;
}

std::string Player::getName( )
{
    return name;
}

void Player::setName( std::string currentName )
{
    name = currentName;
}

