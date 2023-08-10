
#include "actionrule.h"
#include "globals.h"
#include <iostream>
#include <string>

ActionRule::ActionRule()
{

}

bool ActionRule::Deserialize(QXmlStreamReader &reader)
{
    isDefaultValue = false;


    enabled = false;
    minHp = 0;
    maxHp = 100;
    minMagicShield = 0;
    maxMagicShield = 100;
    minMp = 0;
    maxMp = 100;
    minCreatureHp = 0;
    maxCreatureHp = 100;

    creatureCount = 1;
    turn = false;

    itemId = 0;
    spell = nullptr;

    if (!reader.attributes().value("id").isNull())
    {
        int _itemId = reader.attributes().value("id").toInt();
        Spell* _spell = Globals::getSpell(_itemId);
        if (_spell == nullptr)
            itemId = _itemId;
        else
            spell = _spell;
    }
    else if (!reader.attributes().value("spell").isNull())
        spell = Globals::getSpell(reader.attributes().value("spell").toInt());


    if (!reader.attributes().value("minHp").isNull())
        minHp = reader.attributes().value("minHp").toInt();
    if (!reader.attributes().value("maxHp").isNull())
        maxHp = reader.attributes().value("maxHp").toInt();

    if (!reader.attributes().value("minMp").isNull())
        minMp = reader.attributes().value("minMp").toInt();
    if (!reader.attributes().value("maxMp").isNull())
        maxMp = reader.attributes().value("maxMp").toInt();

    if (!reader.attributes().value("minMagicShield").isNull())
        minMagicShield = reader.attributes().value("minMagicShield").toInt();
    if (!reader.attributes().value("maxMagicShield").isNull())
        maxMagicShield = reader.attributes().value("maxMagicShield").toInt();

    if (!reader.attributes().value("minCreatureHp").isNull())
        minCreatureHp = reader.attributes().value("minCreatureHp").toInt();
    if (!reader.attributes().value("maxCreatureHp").isNull())
        maxCreatureHp = reader.attributes().value("maxCreatureHp").toInt();

    if (!reader.attributes().value("creatureCount").isNull())
        creatureCount = reader.attributes().value("creatureCount").toInt();

    if (!reader.attributes().value("turn").isNull())
        turn = reader.attributes().value("turn").toInt();

    if (!reader.attributes().value("enabled").isNull())
        enabled = reader.attributes().value("enabled").toInt();

    return true;
}

bool ActionRule::Serialize(QXmlStreamWriter &writer)
{
    writer.writeStartElement("Action");

    writer.writeAttribute("name", name);

    if (spell != nullptr && spell->itemId > 0)
        writer.writeAttribute("id", QString::number(spell->itemId));
    else if (spell != nullptr && spell->id > 0)
        writer.writeAttribute("spell", QString::number(spell->id));
    else if (itemId > 0)
        writer.writeAttribute("id", QString::number(itemId));

    if (minHp != 0)
        writer.writeAttribute("minHp", QString::number(minHp));
    if (maxHp != 100)
        writer.writeAttribute("maxHp", QString::number(maxHp));
    if (minMp != 0)
        writer.writeAttribute("minMp", QString::number(minMp));
    if (maxMp != 100)
        writer.writeAttribute("maxMp", QString::number(maxMp));
    if (minMagicShield != 0)
        writer.writeAttribute("minMagicShield", QString::number(minMagicShield));
    if (maxMagicShield != 100)
        writer.writeAttribute("maxMagicShield", QString::number(maxMagicShield));
    if (minCreatureHp != 0)
        writer.writeAttribute("minCreatureHp", QString::number(minCreatureHp));
    if (maxCreatureHp != 100)
        writer.writeAttribute("maxCreatureHp", QString::number(maxCreatureHp));
    if (creatureCount != 1)
        writer.writeAttribute("creatureCount", QString::number(creatureCount));
    if (turn != false)
        writer.writeAttribute("turn", QString::number(turn));

    writer.writeAttribute("enabled", QString::number(enabled));
    writer.writeEndElement();

    return true;
}

