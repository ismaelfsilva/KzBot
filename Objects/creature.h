
#ifndef CREATURE_OBJ_H
#define CREATURE_OBJ_H




#include <cstdint>
#include <string>
#include "position.h"
#include "../Util/Enums.h"



namespace Objects
{
class Creature
{
public:
    Creature(uint32_t id, uint32_t addr) {
        m_id = id;
        m_address = addr;
    };

    uint32_t getAddress() { return m_address; };
    uint32_t getId();

    std::string getName();

    uint32_t getX();
    uint32_t getY();
    uint32_t getZ();
    Position getPosition();
    uint32_t getDistance(Creature* c);
    uint32_t getDistance(Position p);
    Direction getDirection();

    uint32_t getLastX();
    uint32_t getLastY();
    uint32_t getLastZ();

    uint64_t getLastWalkTime();
    uint64_t getGameTime();


    uint32_t getHpPc();
    uint32_t getOutfit();
    uint32_t getSpeed();
    CreatureType getType();
    GuildEmblem getGuild();
    PartyShield getPartyShield();
    SkullType getSkull();
    bool isOutOfPz();
    bool isNear();
    Vocation getVocation();

    void Debug();
    bool hasWhiteSquare();
    bool hasBlackSquare();
    uint64_t lastBlackSquareTick();
private:
    uint32_t m_id;
    uint32_t m_address;
};
}
#endif // CREATURE_OBJ_H
