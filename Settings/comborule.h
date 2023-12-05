#ifndef COMBORULE_H
#define COMBORULE_H

#include <string>
#include "../Objects/spell.h"



class ComboRule
{
public:
    ComboRule();
    ComboRule(std::string);

    std::string leader;
    std::string content;

    std::string spellInput;
    int itemId;

    Spell* spell;
    bool Deserialize(QXmlStreamReader &reader);
    bool Serialize(QXmlStreamWriter &writer);
};

#endif // COMBORULE_H
