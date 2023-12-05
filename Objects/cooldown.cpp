
#include "cooldown.h"
#include <cstdint>
#include "../Util/kzhelper.h"
#include "../Settings/globals.h"
#include "../Addresses/cooldown.h"

using namespace Objects;

Cooldown::Cooldown(uint32_t id, uint32_t addr)
{
    m_id = id;
    m_address = addr;
}

uint16_t Cooldown::id()
{
    return m_id;
}

CooldownGroup Cooldown::group()
{
    return (CooldownGroup)Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Cooldown::getId());
}

uint64_t Cooldown::endTime()
{
    return Util::KzHelper::ReadMemoryUInt64(Globals::getHandle(), m_address + Addresses::Cooldown::getEndTimeStamp());
}

bool Cooldown::isUp()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Cooldown::getEndTimeStamp()) == 0;
}
