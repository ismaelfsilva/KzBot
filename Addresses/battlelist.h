
#ifndef BATTLELIST_H
#define BATTLELIST_H


#include <cstdint>

namespace Addresses {


class Battlelist
{
public:

    static uint32_t getPointer() { return m_pointer; }
    static void setPointer(uint32_t value) { m_pointer = value; }

    static uint32_t getCreaturesList() { return m_creaturesList; }
    static void setCreaturesList(uint32_t value) { m_creaturesList = value; }

    static uint32_t getCreaturesCount() { return m_creaturesCount; }
    static void setCreaturesCount(uint32_t value) { m_creaturesCount = value; }

    static uint32_t getCreaturePointer() { return m_creaturePointer; }
    static void setCreaturePointer(uint32_t value) { m_creaturePointer = value; }

    static uint32_t getRedSquare() { return m_redsquare; }
    static void setRedSquare(uint32_t value) { m_redsquare = value; }

    static uint32_t getGreenSquare() { return m_greensquare; }
    static void setGreenSquare(uint32_t value) { m_greensquare = value; }

    static uint32_t getWhiteSquare() { return m_whitesquare; }
    static void setWhiteSquare(uint32_t value) { m_whitesquare = value; }





    static uint32_t getCreaturesOnScreenPointer() { return m_creaturesOnScreenPointer; }
    static void setCreaturesOnScreenPointer(uint32_t value) { m_creaturesOnScreenPointer = value; }

    static uint32_t getCreaturesOnScreenList() { return m_creaturesOnScreenList; }
    static void setCreaturesOnScreenList(uint32_t value) { m_creaturesOnScreenList = value; }


private:
    static uint32_t m_pointer;

    static uint32_t m_creaturesList;
    static uint32_t m_creaturesCount;
    static uint32_t m_creaturePointer;

    static uint32_t m_redsquare;
    static uint32_t m_greensquare;
    static uint32_t m_whitesquare;

    static uint32_t m_creaturesOnScreenPointer;
    static uint32_t m_creaturesOnScreenList;
};

}
#endif // BATTLELIST_H
