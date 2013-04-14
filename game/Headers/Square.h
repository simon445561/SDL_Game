#include "Includes.h"
#include "Object.h"

class Square : public GameObject
{
public:
    Square ( );
    ~Square( );
    void setTime  ( int );
    int  getTime  ( );
    bool getBonus ( );
    void setBonus ( bool );
    bool getBonus2 ( );
    void setBonus2 ( bool );
    bool Undead;

private:
    int  time;
    bool Bonus;
    bool Bonus2;

};
