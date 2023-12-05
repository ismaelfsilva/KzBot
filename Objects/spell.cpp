#include "spell.h"
#include <iostream>

Spell::Spell(QXmlStreamReader &reader)
{
    QXmlStreamAttributes XmlAttributes = reader.attributes();

    this->name = XmlAttributes.value("name").toString().toStdString();
    this->id = XmlAttributes.value("spellid").toInt();

    std::string groupName = XmlAttributes.value("group").toString().toStdString();
    if (groupName == "attack")
        this->group = CooldownGroup::Attack;
    else if (groupName == "healing")
        this->group = CooldownGroup::Heal;
    else if (groupName == "support")
        this->group = CooldownGroup::Support;
    else if (groupName == "item")
        this->group = CooldownGroup::Item;
    else if (groupName == "food")
        this->group = CooldownGroup::Food;
    else if (groupName == "equip")
        this->group = CooldownGroup::Equip;


    if (!XmlAttributes.value("words").isNull())
        this->words = XmlAttributes.value("words").toString().toStdString();
    else if (!XmlAttributes.value("id").isNull())
        this->itemId = XmlAttributes.value("id").toInt();

    this->level = XmlAttributes.value("level").toInt();
    this->magicLevel = XmlAttributes.value("magiclevel").toInt();
    this->mana = XmlAttributes.value("mana").toInt();
    this->range = XmlAttributes.value("range").toInt();
    this->area = XmlAttributes.value("area").toInt();
    this->duration = XmlAttributes.value("duration").toInt();
    this->allowFarUse = !XmlAttributes.value("allowfaruse").isNull() && XmlAttributes.value("allowfaruse").toInt() == 1;
    this->requiresTarget = !XmlAttributes.value("needtarget").isNull(); //|| !XmlAttributes.value("casterTargetOrDirection").isNull();
    this->requiresRealTarget = !XmlAttributes.value("casterTargetOrDirection").isNull();
    this->requiresPlayerNameParam = !XmlAttributes.value("playernameparam").isNull();
    this->selfTarget = (!XmlAttributes.value("selftarget").isNull() && XmlAttributes.value("selftarget").toInt() == 1) || (!XmlAttributes.value("casterTargetOrDirection").isNull() && this->area > 0);

    reader.readNextStartElement();
    bool hasVocationsSet = false;

    while (!reader.name().compare("vocation"))
    {
        hasVocationsSet = true;
        QXmlStreamAttributes vocationAttributes = reader.attributes();
        std::string vocationName = vocationAttributes.value("name").toString().toStdString();

        if (vocationName == "Elite Knight")
            this->vocations[Vocation::Knight] = true;
        else if (vocationName == "Royal Paladin")
            this->vocations[Vocation::Paladin] = true;
        else if (vocationName == "Elder Druid")
            this->vocations[Vocation::Druid] = true;
        else if (vocationName == "Master Sorcerer")
            this->vocations[Vocation::Sorcerer] = true;

        reader.readNextStartElement();
    }
    if (!hasVocationsSet)
    {
        this->vocations[Vocation::Knight] = true;
        this->vocations[Vocation::Paladin] = true;
        this->vocations[Vocation::Druid] = true;
        this->vocations[Vocation::Sorcerer] = true;
    }

}
