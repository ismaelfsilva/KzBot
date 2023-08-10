
#ifndef COOLDOWN_ADDR_H
#define COOLDOWN_ADDR_H


#include <cstdint>
namespace Addresses
{


class Cooldown
{
public:
    static void setId(uint32_t value) { m_id = value; }
    static void setEndTimeStamp(uint32_t value) { m_endTimeStamp = value; }

    static uint32_t getId() { return m_id; }
    static uint32_t getEndTimeStamp() { return m_endTimeStamp; }

private:
    static uint32_t m_id;
    static uint32_t m_endTimeStamp;
};


}

#endif // COOLDOWN_ADDR_H
