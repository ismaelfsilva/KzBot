
#ifndef HEALRULE_H
#define HEALRULE_H

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include "../Objects/spell.h"

class ActionRule
{
public:
    ActionRule();

    // BASIC CONFIG

    std::string name;
    bool alwaysUse = false;
    DelayType delayType1 = DelayType::None;
    DelayType delayType2 = DelayType::None;
    bool hasteSpell = false;
    bool onParalyzeSpell = false;
    bool centerKnight = false;

    // USER INPUT

    bool enabled = false;
    int minHp = 0;
    int maxHp = 100;
    int minMagicShield = 0;
    int maxMagicShield = 100;
    int minMp = 0;
    int maxMp = 100;
    int minCreatureHp = 0;
    int maxCreatureHp = 100;

    int creatureCount = 1;
    bool turn = false;

    int itemId = 0;

    // INTERNAL

    Spell* spell = nullptr;
    ActionType type;
    ItemUseType itemUseType;

    std::chrono::time_point<std::chrono::system_clock> lastUse = std::chrono::system_clock::now();

    bool isDefaultValue = true;
    bool Serialize(QXmlStreamWriter &writer);
    bool Deserialize(QXmlStreamReader &writer);
};

#endif // HEALRULE_H
