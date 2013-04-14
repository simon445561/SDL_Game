#include "Square.h"

Square::Square()
{
    Undead = false;
    Bonus  = false;
    Bonus2 = false;
    time = 0;
}

Square::~Square()
{

}

bool Square::getBonus( )
{
    return Bonus;
}

void Square::setBonus( bool currentBonus )
{
    Bonus = currentBonus;
}

bool Square::getBonus2( )
{
    return Bonus2;
}

void Square::setBonus2( bool currentBonus )
{
    Bonus2 = currentBonus;
}

int Square::getTime( )
{
    return time;
}

void Square::setTime( int a )
{
    time = a;
}
