#include "player.h"
#include "../Util/kzhelper.h"
#include "../Settings/globals.h"
#include "../Addresses/player.h"
#include "../Objects/client.h"
#include "creature.h"
#include <iostream>

using namespace Objects;

int Player::getHealth()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Player::getHealth());
}

int Player::getHealthMax()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Player::getHealthMax());
}

int Player::getHealthPercent()
{
    return  std::ceil((double)((double)getHealth() / (double)getHealthMax()) * 100.0);
}

int Player::getMana()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Player::getMana());
}
int Player::getManaMax()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Player::getManaMax());
}
int Player::getManaPercent()
{
    return std::ceil((double)((double)getMana() / (double)getManaMax()) * 100.0);
}



int Player::getUtamo()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Player::getUtamo());
}
int Player::getUtamoMax()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Player::getUtamoMax());
}
int Player::getUtamoPercent()
{
    return std::max(0.0, (double)((double)getUtamo() / (double)getUtamoMax()) * 100.0);
}

int Player::getLevel()
{
    return Util::KzHelper::ReadMemoryUInt16(Globals::getHandle(), m_address + Addresses::Player::getLevel());
}
