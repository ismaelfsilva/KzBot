
#ifndef PLAYER_ADR_H
#define PLAYER_ADR_H

#include <cstdint>
namespace Addresses {


class Player
{
public:
    static void setHealth(uint32_t value) { m_hp = value; }
    static void setHealthMax(uint32_t value) { m_hpMax = value; }
    static void setMana(uint32_t value) { m_mana = value; }
    static void setManaMax(uint32_t value) { m_manaMax = value; }
    static void setUtamo(uint32_t value) { m_utamo = value; }
    static void setUtamoMax(uint32_t value) { m_utamoMax = value; }
    static void setLevel(uint32_t value) { m_level = value; }

    static uint32_t getHealth() { return m_hp; }
    static uint32_t getHealthMax() { return m_hpMax; }
    static uint32_t getMana() { return m_mana; }
    static uint32_t getManaMax() { return m_manaMax; }
    static uint32_t getUtamo() { return m_utamo; }
    static uint32_t getUtamoMax() { return m_utamoMax; }
    static uint32_t getLevel() { return m_level; }


private:
    static uint32_t m_hp;
    static uint32_t m_hpMax;
    static uint32_t m_mana;
    static uint32_t m_manaMax;
    static uint32_t m_utamo;
    static uint32_t m_utamoMax;
    static uint32_t m_level;
};

}
#endif // PLAYER_ADR_H
