
#ifndef CREATURE_ADR_H
#define CREATURE_ADR_H


#include <cstdint>

namespace Addresses {

class Creature
{
public:
    static uint32_t getId() { return m_id; };
    static uint32_t getName() { return m_name; };
    static uint32_t getX() { return m_x; };
    static uint32_t getY() { return m_y; };
    static uint32_t getZ() { return m_z; };
    static uint32_t getDirection() { return m_direction; };
    static uint32_t getLastX() { return m_lastX; };
    static uint32_t getLastY() { return m_lastY; };
    static uint32_t getLastZ() { return m_lastZ; };
    static uint32_t getTimers() { return m_timers; };
    static uint32_t getLastWalkTime() { return m_lastWalkTime; };
    static uint32_t getGameTime() { return m_gameTime; };
    static uint32_t getHpPc() { return m_hpPc; };
    static uint32_t getOutfit() { return m_outfit; };
    static uint32_t getSpeed() { return m_speed; };
    static uint32_t getType() { return m_type; };
    static uint32_t getGuild() { return m_guild; };
    static uint32_t getParty() { return m_party; };
    static uint32_t getSkull() { return m_skull; };
    static uint32_t getIsNear() { return m_isNear; };
    static uint32_t getVocation() { return m_vocation; };
    static uint32_t getMouseHovered() { return m_mouseHovered; };
    static uint32_t getHasBlackSquare() { return m_hasBlackSquare; };
    static uint32_t getLastBlackSquareTick() { return m_lastBlackSquareTick; };

    static void setId(uint32_t id) { m_id = id; };
    static void setName(uint32_t name) { m_name = name; };
    static void setX(uint32_t x) { m_x = x; };
    static void setY(uint32_t y) { m_y = y; };
    static void setZ(uint32_t z) { m_z = z; };
    static void setDirection(uint32_t direction) { m_direction = direction; };
    static void setLastX(uint32_t lastX) { m_lastX = lastX; };
    static void setLastY(uint32_t lastY) { m_lastY = lastY; };
    static void setLastZ(uint32_t lastZ) { m_lastZ = lastZ; };
    static void setTimers(uint32_t value) { m_timers = value; };
    static void setLastWalkTime(uint32_t value) { m_lastWalkTime = value; };
    static void setGameTime(uint32_t value) { m_gameTime = value; };
    static void setHpPc(uint32_t hpPc) { m_hpPc = hpPc; };
    static void setOutfit(uint32_t outfit) { m_outfit = outfit; };
    static void setSpeed(uint32_t speed) { m_speed = speed; };
    static void setType(uint32_t type) { m_type = type; };
    static void setGuild(uint32_t guild) { m_guild = guild; };
    static void setParty(uint32_t party) { m_party = party; };
    static void setSkull(uint32_t skull) { m_skull = skull; };
    static void setIsNear(uint32_t isNear) { m_isNear = isNear; };
    static void setVocation(uint32_t vocation) { m_vocation = vocation; };
    static void setMouseHovered(uint32_t mouseHovered) { m_mouseHovered = mouseHovered; };
    static void setHasBlackSquare(uint32_t hasBlackSquare) { m_hasBlackSquare = hasBlackSquare; };
    static void setLastBlackSquareTick(uint32_t lastBlackSquareTick) { m_lastBlackSquareTick = lastBlackSquareTick; };

private:
    static uint32_t m_id;
    static uint32_t m_name;

    static uint32_t m_x;
    static uint32_t m_y;
    static uint32_t m_z;
    static uint32_t m_direction;

    static uint32_t m_lastX;
    static uint32_t m_lastY;
    static uint32_t m_lastZ;

    static uint32_t m_timers;
    static uint32_t m_lastWalkTime;
    static uint32_t m_gameTime;

    static uint32_t m_hpPc;
    static uint32_t m_outfit;
    static uint32_t m_speed;
    static uint32_t m_type;
    static uint32_t m_guild;
    static uint32_t m_skull;
    static uint32_t m_party;
    static uint32_t m_isNear;
    static uint32_t m_vocation;
    static uint32_t m_mouseHovered;
    static uint32_t m_hasBlackSquare;
    static uint32_t m_lastBlackSquareTick;
};

}
#endif // CREATURE_ADR_H
