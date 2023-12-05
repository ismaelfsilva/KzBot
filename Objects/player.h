
#ifndef PLAYER_OBJ_H
#define PLAYER_OBJ_H


#include "creature.h"
#include <cstdint>





namespace Objects
{

class Player
{
public:
    Player(uint32_t addr) { m_address = addr; };

    int getHealth();
    int getHealthMax();
    int getHealthPercent();

    int getMana();
    int getManaMax();
    int getManaPercent();

    int getUtamo();
    int getUtamoMax();
    int getUtamoPercent();

    int getLevel();
    int getFoodTime();
    std::vector<Icons> getConditions();
private:
    uint32_t m_address;
};

}

#endif // PLAYER_OBJ_H
