
#ifndef COOLDOWN_H
#define COOLDOWN_H



#include "../Settings/globals.h"
#include <cstdint>
namespace Objects
{
class Cooldown
{
public:
    Cooldown(uint32_t id, uint32_t addr);
    uint8_t id();
    CooldownGroup group();
    uint64_t endTime();
    bool isUp();

private:
    uint8_t m_id;
    uint32_t m_address;
};
}

#endif // COOLDOWN_H
