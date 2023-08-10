
#ifndef BATTLELIST_OBJ_H
#define BATTLELIST_OBJ_H


#include "creature.h"
#include <vector>
namespace Objects
{



class Battlelist
{
public:
    static uint32_t getPointer(uint32_t dataPointer);
    static std::map<uint32_t, Creature *> getCreatures(uint32_t dataPointer);
    static std::map<uint32_t, Creature *> getCreaturesOnScreen(uint32_t dataPointer);

    static uint32_t getTargetId(uint32_t dataPointer);
    static void setTargetId(uint32_t dataPointer, uint32_t id);
    static uint32_t getFollowId(uint32_t dataPointer);
    static uint32_t getHoverId(uint32_t dataPointer);
    static uint32_t getCreatureCount(uint32_t dataPointer);
};

}

#endif // BATTLELIST_OBJ_H
