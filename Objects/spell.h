#ifndef SPELL_H
#define SPELL_H

#include "../Util/Enums.h"
#include "qxmlstream.h"

class Spell
{
public:
    Spell(QXmlStreamReader &reader);

    int id = 0;
    CooldownGroup group;
    std::string name;
    std::string words;
    int itemId = 0;
    int level = 0;
    int magicLevel = 0;
    int mana = 0;
    int range = 0;
    int area = 0;
    int duration = 0;
    bool allowFarUse = 0;
    bool requiresTarget = 0;
    bool requiresRealTarget = 0;
    bool requiresPlayerNameParam = 0;
    bool selfTarget = 0;
    std::unordered_map<Vocation, bool> vocations;
};

#endif // SPELL_H
