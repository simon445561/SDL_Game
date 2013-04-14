#include "Includes.h"
#include "Object.h"

class Player : public GameObject
{
public:
    Player ( );
    ~Player( );
    int  getDirection( );
    int  getLevel    ( );
    bool getBonus    ( );
    void setBonus    ( bool );
    void setName     ( std::string );
    void setLevel    ( int );
    void setDirection( short );
    void Move        ( );
    bool Collision   ( int, int );
    bool Collision   ( int, int, int, int );
    std::string getName( );

private:
    short Direction;
    bool  Bonus;
    int   Level;
    std::string name;

};
