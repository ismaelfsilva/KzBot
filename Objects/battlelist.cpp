#include "../Addresses/client.h"
#include "../Addresses/battlelist.h"
#include "client.h"
#include "battlelist.h"
#include "../Util/kzhelper.h"

#include <cstdlib>

using namespace Objects;


std::map<uint32_t, Creature *> Battlelist::getCreatures(uint32_t dataPointer)
{
    std::map<uint32_t, Creature *> creatureList;

    uint32_t battleListPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Battlelist::getPointer());
    std::map<uint32_t, uint32_t> creaturesCollection = Util::KzHelper::readQtCollection(battleListPointer + Addresses::Battlelist::getCreaturesList());

    if (creaturesCollection.empty())
        return creatureList;

    for (auto creatureEntry : creaturesCollection)
    {
        Creature *c = new Creature(creatureEntry.first, Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), creatureEntry.second + Addresses::Battlelist::getCreaturePointer()));
        creatureList.insert({creatureEntry.first, c});
    }

    return creatureList;
}

std::map<uint32_t, Creature *> Battlelist::getCreaturesOnScreen(uint32_t dataPointer)
{
    std::map<uint32_t, Creature *> creatureList;

    uint32_t creatureOnScreenListClass = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Battlelist::getCreaturesOnScreenPointer());
    std::map<uint32_t, uint32_t> creaturesOnScreenIdList = Util::KzHelper::readQtCollection(creatureOnScreenListClass + Addresses::Battlelist::getCreaturesOnScreenList());

    if (creaturesOnScreenIdList.empty())
        return creatureList;

    uint32_t battleListPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Battlelist::getPointer());
    std::map<uint32_t, uint32_t> creaturesCollection = Util::KzHelper::readQtCollection(battleListPointer + Addresses::Battlelist::getCreaturesList());

    if (creaturesCollection.empty())
        return creatureList;

    for (auto creatureEntry : creaturesCollection)
    {
        if (creaturesOnScreenIdList.find(creatureEntry.first) == creaturesOnScreenIdList.end())
            continue;

        Creature *c = new Creature(creatureEntry.first, Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), creatureEntry.second + Addresses::Battlelist::getCreaturePointer()));

        creatureList.insert({creatureEntry.first, c});
    }

    return creatureList;
}

uint32_t Battlelist::getCreatureCount(uint32_t dataPointer)
{
    uint32_t battleListPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Battlelist::getPointer());
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), battleListPointer + Addresses::Battlelist::getCreaturesCount());
}

uint32_t Battlelist::getTargetId(uint32_t dataPointer)
{
    uint32_t battleListPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Battlelist::getPointer());
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), battleListPointer + Addresses::Battlelist::getRedSquare());
}

uint32_t Battlelist::getFollowId(uint32_t dataPointer)
{
    uint32_t battleListPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Battlelist::getPointer());
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), battleListPointer + Addresses::Battlelist::getGreenSquare());
}

uint32_t Battlelist::getHoverId(uint32_t dataPointer)
{
    uint32_t battleListPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Battlelist::getPointer());
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), battleListPointer + Addresses::Battlelist::getWhiteSquare());
}

void Battlelist::setTargetId(uint32_t dataPointer, uint32_t id)
{
    uint32_t battleListPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Battlelist::getPointer());
    Util::KzHelper::WriteMemoryUInt32(Globals::getHandle(), battleListPointer + Addresses::Battlelist::getRedSquare(), id);
}
