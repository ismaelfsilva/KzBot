
#include "creature.h"
#include "../Util/kzhelper.h"
#include "../Settings/globals.h"
#include "../Addresses/creature.h"
#include "position.h"
#include <iostream>

using namespace Objects;


uint32_t Objects::Creature::getId()
{
    return m_id;
}

std::string Creature::getName()
{
    uint32_t qstringPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Creature::getName());
    return Util::KzHelper::ReadMemoryStringUnicode(Globals::getHandle(), qstringPointer + 0x10);
}

uint32_t Creature::getX()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Creature::getX());
}

uint32_t Creature::getY()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Creature::getY());
}

uint32_t Creature::getZ()
{
    return Util::KzHelper::ReadMemoryByte(Globals::getHandle(), m_address + Addresses::Creature::getZ());
}

Position Creature::getPosition()
{
    char positionData[0xC];
    Util::KzHelper::ReadMemory(Globals::getHandle(), m_address + Addresses::Creature::getX(), positionData, sizeof(positionData));

    return Position(*reinterpret_cast<uint32_t*>(positionData + 0x0),
                    *reinterpret_cast<uint32_t*>(positionData + 0x4),
                    *reinterpret_cast<uint32_t*>(positionData + 0x8));
}

uint32_t Creature::getDistance(Creature* c)
{
    int distX = (getX()) - (c->getX());
    int distY = (getY()) - (c->getY());

    double result = sqrt(pow(distX, 2) + pow(distY, 2));
    return (int)result;
}

uint32_t Creature::getDistance(Position p)
{
    int distX = (getX()) - (p.X());
    int distY = (getY()) - (p.Y());

    double result = sqrt(pow(distX, 2) + pow(distY, 2));
    return (int)result;
}

Direction Creature::getDirection()
{
    return (Direction)Util::KzHelper::ReadMemoryByte(Globals::getHandle(), m_address + Addresses::Creature::getDirection());
}

uint32_t Creature::getLastX()
{
    return 0;
}

uint32_t Creature::getLastY()
{
    return 0;
}

uint32_t Creature::getLastZ()
{
    return 0;
}

uint64_t Creature::getLastWalkTime()
{
    uint32_t creatureTimers = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Creature::getTimers());
    return Util::KzHelper::ReadMemoryUInt64(Globals::getHandle(), creatureTimers + Addresses::Creature::getLastWalkTime());
}

uint64_t Creature::getGameTime()
{
    uint32_t creatureTimers = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Creature::getTimers());
    return Util::KzHelper::ReadMemoryUInt64(Globals::getHandle(), creatureTimers + Addresses::Creature::getGameTime());
}

uint32_t Creature::getHpPc()
{
    return Util::KzHelper::ReadMemoryByte(Globals::getHandle(), m_address + Addresses::Creature::getHpPc());
}

uint32_t Creature::getOutfit()
{
    return 0;
}

uint32_t Creature::getSpeed()
{
    return Util::KzHelper::ReadMemoryUInt16(Globals::getHandle(), m_address + Addresses::Creature::getSpeed());
}

CreatureType Creature::getType()
{
    return (CreatureType)Util::KzHelper::ReadMemoryByte(Globals::getHandle(), m_address + Addresses::Creature::getType());
}

GuildEmblem Creature::getGuild()
{
    return (GuildEmblem)Util::KzHelper::ReadMemoryByte(Globals::getHandle(), m_address + Addresses::Creature::getGuild());
}

PartyShield Creature::getPartyShield()
{
    return (PartyShield)Util::KzHelper::ReadMemoryByte(Globals::getHandle(), m_address + Addresses::Creature::getParty());
}

SkullType Creature::getSkull()
{
    return (SkullType)Util::KzHelper::ReadMemoryByte(Globals::getHandle(), m_address + Addresses::Creature::getSkull());
}

bool Creature::isOutOfPz()
{
    return Util::KzHelper::ReadMemoryByte(Globals::getHandle(), m_address + Addresses::Creature::getOutOfPz()) == 1;
}

bool Creature::isNear()
{
    return Util::KzHelper::ReadMemoryByte(Globals::getHandle(), m_address + Addresses::Creature::getIsNear()) == 1;
}

bool Creature::hasWhiteSquare()
{
    return Util::KzHelper::ReadMemoryByte(Globals::getHandle(), m_address + Addresses::Creature::getMouseHovered()) == 1;
}

bool Creature::hasBlackSquare()
{
    return Util::KzHelper::ReadMemoryByte(Globals::getHandle(), m_address + Addresses::Creature::getHasBlackSquare()) == 1;
}

uint64_t Creature::lastBlackSquareTick()
{
    return Util::KzHelper::ReadMemoryUInt64(Globals::getHandle(), m_address + Addresses::Creature::getLastBlackSquareTick());
}

Vocation Creature::getVocation()
{
    return (Vocation)Util::KzHelper::ReadMemoryByte(Globals::getHandle(), m_address + Addresses::Creature::getVocation());
}

void Creature::Debug()
{
    std::cout << "Address: " << getAddress() << " | Name: " << getName() << " | Type: " << (int)getType() << " | Id: " << getId() << " | Vocation: " << (int)getVocation() << " | HP%: " << getHpPc() << " | Guild: " << (int)getGuild()
              << " | On Screen: " << isNear()
              << " | X: " << getX() << " | Y: " << getY() << " | Z: " << getZ() << " | Dir: " << (int)getDirection()
              << std::endl;
}

