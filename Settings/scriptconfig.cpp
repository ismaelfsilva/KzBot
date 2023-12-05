
#include "actionsettings.h"
#include "globals.h"
#include "scriptconfig.h"
#include "../Util/kzhelper.h"
#include <iostream>
#include "../Objects/client.h"
#include "../Settings/globals.h"

ScriptConfig::ScriptConfig()
{
    m_generalStatus = false;

    m_healerStatus = false;
    m_respectAttackTurns = false;

    m_healerDelay = 100;
    m_healerWait = 100;

    m_healFriendLockKeyboard = false;
    m_healFriendParty = false;
    m_healFriendGuild = false;
    m_healFriendList = false;

    m_healFriendGranSioStatus = false;
    m_healFriendGranSioHp = 0;

    m_healFriendHealth = {
                          {Vocation::Knight, 0},
                          {Vocation::Paladin, 0},
                          {Vocation::Druid, 0},
                          {Vocation::Sorcerer, 0},
                          };

    m_healFriendStatus = {
                          {Vocation::Knight, false},
                          {Vocation::Paladin, false},
                          {Vocation::Druid, false},
                          {Vocation::Sorcerer, false},
                          };

    m_healFriendGeneralStatus = false;


    m_pvpToolsStatus = false;
    m_pvpHoldTarget = false;
    m_pvpParalyzeTarget = false;
    m_pvpDashTarget = false;
    m_pvpChatNaviStatus = true;
    m_UEsToConsiderCombo = 3;
    m_AvatarCountToConsiderCombo = 3;

    m_partyHuntStatus = false;

    m_partyHuntUseTargetNext = false;
    m_partyHuntTargetNextKey = 0x0;
    m_partyHuntTargetNextKeyExtended = false;

    m_partyHuntUseFakeTarget = true;
    m_partyHuntAreaRune = true;
    m_partyHuntAutoTargetStatus = false;
    m_partyHuntUltimateHealth = 100;

    m_partyHuntUseEKCombo = false;


    m_toolsStatus = false;
    m_toolsReadInventory = false;


}



void ScriptConfig::addHealRule(ActionRule* healRule) { HealRules.push_back(healRule); };

ActionRule* ScriptConfig::addHealRule(std::string name, ActionType type, std::string spellId) {
    Spell* spell = Globals::getSpell(spellId);
    return addHealRule(name, type, spell);
}

ActionRule* ScriptConfig::addHealRule(std::string name, ActionType type, Spell* spell) {
    ActionRule* rule = new ActionRule();

    rule->name = name;
    rule->type = type;
    rule->spell = spell;

    addHealRule(rule);
    return rule;
}
ActionRule* ScriptConfig::getHealRule(std::string name) {
    for (ActionRule *rule : HealRules)
        if (rule->name == name)
            return rule;

    return nullptr;
}








void ScriptConfig::addToolsRule(ActionRule* toolsRule) { ToolsRules.push_back(toolsRule); };

ActionRule* ScriptConfig::addToolsRule(std::string name, ActionType type, std::string spellId) {
    Spell* spell = Globals::getSpell(spellId);
    return addToolsRule(name, type, spell);
}

ActionRule* ScriptConfig::addToolsRule(std::string name, ActionType type, Spell* spell) {
    ActionRule* rule = new ActionRule();

    rule->name = name;
    rule->type = type;
    rule->spell = spell;

    addToolsRule(rule);
    return rule;
}

ActionRule* ScriptConfig::getToolsRule(std::string name) {
    for (ActionRule *rule : ToolsRules)
        if (rule->name == name)
            return rule;

    return nullptr;
}









void ScriptConfig::addKnightTargetRule(ActionRule* targetRule) { KnightTargetRules.push_back(targetRule); };

ActionRule* ScriptConfig::addKnightTargetRule(std::string name, ActionType type, std::string spellId) {
    Spell* spell = Globals::getSpell(spellId);
    return addKnightTargetRule(name, type, spell);
}

ActionRule* ScriptConfig::addKnightTargetRule(std::string name, ActionType type, Spell* spell) {
    ActionRule* rule = new ActionRule();

    rule->name = name;
    rule->type = type;
    rule->spell = spell;

    addKnightTargetRule(rule);
    return rule;
}
ActionRule* ScriptConfig::getKnightTargetRule(std::string name) {
    for (ActionRule *rule : KnightTargetRules)
        if (rule->name == name)
            return rule;

    return nullptr;
}





void ScriptConfig::addTargetRule(ActionRule* targetRule) { TargetRules.push_back(targetRule); };

ActionRule* ScriptConfig::addTargetRule(std::string name, ActionType type, std::string spellId) {
    Spell* spell = Globals::getSpell(spellId);
    return addTargetRule(name, type, spell);
}

ActionRule* ScriptConfig::addTargetRule(std::string name, ActionType type, Spell* spell) {
    ActionRule* rule = new ActionRule();

    rule->name = name;
    rule->type = type;
    rule->spell = spell;

    addTargetRule(rule);
    return rule;
}
ActionRule* ScriptConfig::getTargetRule(std::string name) {
    for (ActionRule *rule : TargetRules)
        if (rule->name == name)
            return rule;

    return nullptr;
}














void ScriptConfig::Serialize(QXmlStreamWriter &writer)
{
    writer.writeStartElement("KzBot");

    // Healer
    writer.writeStartElement("Healer");
    bool wroteHealRulesStart = false;
    for (ActionRule* rule: HealRules)
    {
        if (!wroteHealRulesStart)
        {
            writer.writeStartElement("Rules");
            wroteHealRulesStart = true;
        }

        rule->Serialize(writer);
    }
    if (wroteHealRulesStart)
        writer.writeEndElement();

    writer.writeStartElement("HealFriend");
    writer.writeAttribute("Knight", std::to_string(getHealFriendHealth(Vocation::Knight)));
    writer.writeAttribute("Paladin", std::to_string(getHealFriendHealth(Vocation::Paladin)));
    writer.writeAttribute("Druid", std::to_string(getHealFriendHealth(Vocation::Druid)));
    writer.writeAttribute("Sorcerer", std::to_string(getHealFriendHealth(Vocation::Sorcerer)));

    writer.writeAttribute("KnightStatus", std::to_string(getHealFriendStatus(Vocation::Knight)));
    writer.writeAttribute("PaladinStatus", std::to_string(getHealFriendStatus(Vocation::Paladin)));
    writer.writeAttribute("DruidStatus", std::to_string(getHealFriendStatus(Vocation::Druid)));
    writer.writeAttribute("SorcererStatus", std::to_string(getHealFriendStatus(Vocation::Sorcerer)));

    writer.writeAttribute("Party", std::to_string(m_healFriendParty));
    writer.writeAttribute("Guild", std::to_string(m_healFriendGuild));
    writer.writeAttribute("List", std::to_string(m_healFriendList));
    writer.writeEndElement();

    writer.writeEndElement();

    // Tools
    writer.writeStartElement("Tools");

    writer.writeTextElement("AntiIdle", std::to_string(m_toolsAntiIdle));
    writer.writeTextElement("HoldPosition", std::to_string(m_toolsHoldPosition));
    writer.writeTextElement("EatFood", std::to_string(m_toolsEatFood));
    writer.writeTextElement("EatFoodId", std::to_string(m_toolsEatFoodId));
    writer.writeTextElement("AutoBuff", std::to_string(m_toolsAutoBuff));
    writer.writeTextElement("AutoBuffId", std::to_string(m_toolsBuffItemId));

    bool wroteToolsRulesStart = false;
    for (ActionRule* rule: ToolsRules)
    {
        if (!wroteToolsRulesStart)
        {
            writer.writeStartElement("Rules");
            wroteToolsRulesStart = true;
        }

        rule->Serialize(writer);
    }
    if (wroteToolsRulesStart)
        writer.writeEndElement();

    writer.writeEndElement();

    // Pvp Tools
    writer.writeStartElement("PvP");

    writer.writeTextElement("HoldTarget", std::to_string(m_pvpHoldTarget));
    writer.writeTextElement("ParalyzeTarget", std::to_string(m_pvpParalyzeTarget));
    writer.writeTextElement("DashTarget", std::to_string(m_pvpDashTarget));

    writer.writeTextElement("OnComboUE", std::to_string(m_pvpOnComboUE));
    m_pvpOnComboUEActionA->Serialize(writer);
    m_pvpOnComboUEActionB->Serialize(writer);

    writer.writeTextElement("OnComboAvatar", std::to_string(m_pvpOnComboAvatar));
    m_pvpOnComboAvatarActionA->Serialize(writer);
    m_pvpOnComboAvatarActionB->Serialize(writer);

    bool wroteComboRulesStart = false;
    for (ComboRule* rule: ComboRules)
    {
        if (!wroteComboRulesStart)
        {
            writer.writeStartElement("Rules");
            wroteComboRulesStart = true;
        }

        rule->Serialize(writer);
    }
    if (wroteComboRulesStart)
        writer.writeEndElement();

    writer.writeEndElement();

    // Party Hunt
    writer.writeStartElement("PartyHunt");
    writer.writeTextElement("AutoTarget", std::to_string(m_partyHuntAutoTargetStatus));
    writer.writeTextElement("UseTargetNext", std::to_string(m_partyHuntUseTargetNext));

    bool wroteTargetingRulesStart = false;
    for (ActionRule* rule: TargetRules)
    {
        if (!wroteTargetingRulesStart)
        {
            writer.writeStartElement("Caster");
            wroteTargetingRulesStart = true;
        }

        rule->Serialize(writer);
    }
    if (wroteTargetingRulesStart)
        writer.writeEndElement();

    writer.writeTextElement("UseEKCombo", std::to_string(m_partyHuntUseEKCombo));

    bool wroteEKTargetingRulesStart = false;
    for (ActionRule* rule: KnightTargetRules)
    {
        if (!wroteEKTargetingRulesStart)
        {
            writer.writeStartElement("EKRules");
            wroteEKTargetingRulesStart = true;
        }

        rule->Serialize(writer);
    }
    if (wroteEKTargetingRulesStart)
        writer.writeEndElement();

    writer.writeEndElement();

    writer.writeStartElement("Config");
    writer.writeTextElement("RespectAttackTurns", std::to_string(m_respectAttackTurns));
    writer.writeEndElement();


    writer.writeStartElement("Status");
    writer.writeTextElement("Healer", std::to_string(m_healerStatus));
    writer.writeTextElement("Tools", std::to_string(m_toolsStatus));
    writer.writeTextElement("PvP", std::to_string(m_pvpToolsStatus));
    writer.writeTextElement("PartyHunt", std::to_string(m_partyHuntStatus));
    writer.writeEndElement();

    writer.writeEndElement();
}

void ScriptConfig::Deserialize(QXmlStreamReader &reader)
{
    while (!reader.atEnd() && !reader.hasError())
    {
        reader.readNext();

        if (reader.isStartElement())
        {
            if (reader.name().compare("Healer") == 0)
            {
                // Desserialização das configurações do Healer
                while (!(reader.isEndElement() && reader.name().compare("Healer") == 0))
                {
                    reader.readNext();

                    if (reader.isStartElement())
                    {
                        if (reader.name().compare("Rules") == 0)
                        {
                            while (!(reader.isEndElement() && reader.name().compare("Rules") == 0))
                            {
                                reader.readNext();

                                if (reader.isStartElement() && reader.name().compare("Action") == 0)
                                {
                                    QString name = reader.attributes().value("name").toString();

                                    auto ruleIt = std::find_if(HealRules.begin(), HealRules.end(), [&name](ActionRule* rule) {
                                        return rule->name == name.toStdString();
                                    });

                                    if (ruleIt != HealRules.end())
                                    {
                                        ActionRule* rule = *ruleIt;
                                        rule->Deserialize(reader);
                                    }
                                }
                            }
                        }
                        else if (reader.name().compare("HealFriend") == 0)
                        {
                            setHealFriendHealth(Vocation::Knight, reader.attributes().value("Knight").toInt());
                            setHealFriendHealth(Vocation::Paladin, reader.attributes().value("Paladin").toInt());
                            setHealFriendHealth(Vocation::Druid, reader.attributes().value("Druid").toInt());
                            setHealFriendHealth(Vocation::Sorcerer, reader.attributes().value("Sorcerer").toInt());

                            setHealFriendStatus(Vocation::Knight, reader.attributes().value("KnightStatus").toInt());
                            setHealFriendStatus(Vocation::Paladin, reader.attributes().value("PaladinStatus").toInt());
                            setHealFriendStatus(Vocation::Druid, reader.attributes().value("DruidStatus").toInt());
                            setHealFriendStatus(Vocation::Sorcerer, reader.attributes().value("SorcererStatus").toInt());

                            m_healFriendGuild = reader.attributes().value("Guild").toInt();
                            m_healFriendParty = reader.attributes().value("Party").toInt();
                            m_healFriendList = reader.attributes().value("List").toInt();

                            reader.readNext();
                        }
                    }
                }
            }
            else if (reader.name().compare("Tools") == 0)
            {
                while (!(reader.isEndElement() && reader.name().compare("Tools") == 0))
                {
                    reader.readNext();

                    if (reader.isStartElement() && reader.name().compare("AntiIdle") == 0)
                    {
                        reader.readNext();
                        m_toolsAntiIdle = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("HoldPosition") == 0)
                    {
                        reader.readNext();
                        m_toolsHoldPosition = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("EatFood") == 0)
                    {
                        reader.readNext();
                        m_toolsEatFood = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("EatFoodId") == 0)
                    {
                        reader.readNext();
                        m_toolsEatFoodId = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("AutoBuff") == 0)
                    {
                        reader.readNext();
                        m_toolsAutoBuff = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("AutoBuffId") == 0)
                    {
                        reader.readNext();
                        m_toolsBuffItemId = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("Rules") == 0)
                    {
                        while (!(reader.isEndElement() && reader.name().compare("Rules") == 0))
                        {
                            reader.readNext();

                            if (reader.isStartElement() && reader.name().compare("Action") == 0)
                            {
                                QString name = reader.attributes().value("name").toString();

                                auto ruleIt = std::find_if(ToolsRules.begin(), ToolsRules.end(), [&name](ActionRule* rule) {
                                    return rule->name == name.toStdString();
                                });

                                if (ruleIt != ToolsRules.end())
                                {
                                    ActionRule* rule = *ruleIt;
                                    rule->Deserialize(reader);
                                }
                            }
                        }
                    }
                    else if (reader.isStartElement() && reader.name().compare("Rules") == 0)
                    {

                    }
                }
            }
            else if (reader.name().compare("PvP") == 0)
            {
                int comboId = 0;
                while (!(reader.isEndElement() && reader.name().compare("PvP") == 0))
                {
                    reader.readNext();


                    if (reader.isStartElement() && reader.name().compare("HoldTarget") == 0)
                    {
                        reader.readNext();
                        m_pvpHoldTarget = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("ParalyzeTarget") == 0)
                    {
                        reader.readNext();
                        m_pvpParalyzeTarget = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("DashTarget") == 0)
                    {
                        reader.readNext();
                        m_pvpDashTarget = reader.text().toString().toInt();
                    }


                    else if (reader.isStartElement() && reader.name().compare("OnComboUE") == 0)
                    {
                        reader.readNext();
                        m_pvpOnComboUE = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("OnComboAvatar") == 0)
                    {
                        reader.readNext();
                        m_pvpOnComboAvatar = reader.text().toString().toInt();
                    }

                    else if (reader.isStartElement() && reader.name().compare("Combo") == 0)
                    {
                        switch (comboId)
                        {
                        case 0:
                            m_pvpOnComboUEActionA->Deserialize(reader);
                            break;
                        case 1:
                            m_pvpOnComboUEActionB->Deserialize(reader);
                            break;
                        case 2:
                            m_pvpOnComboAvatarActionA->Deserialize(reader);
                            break;
                        case 3:
                            m_pvpOnComboAvatarActionB->Deserialize(reader);
                            break;
                        }

                        comboId++;
                        reader.readNext();
                    }



                    else if (reader.isStartElement() && reader.name().compare("Rules") == 0)
                    {
                        int i = 0;
                        while (!(reader.isEndElement() && reader.name().compare("Rules") == 0))
                        {
                            reader.readNext();
                            if (reader.isStartElement() && reader.name().compare("Combo") == 0)
                            {
                                ComboRule* rule = ComboRules[i++];
                                rule->Deserialize(reader);
                            }
                        }
                    }
                }
            }
            else if (reader.name().compare("PartyHunt") == 0)
            {
                while (!(reader.isEndElement() && reader.name().compare("PartyHunt") == 0))
                {
                    reader.readNext();

                    if (reader.isStartElement() && reader.name().compare("AutoTarget") == 0)
                    {
                        reader.readNext();
                        m_partyHuntAutoTargetStatus = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("UseTargetNext") == 0)
                    {
                        reader.readNext();
                        m_partyHuntUseTargetNext = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("Caster") == 0)
                    {
                        while (!(reader.isEndElement() && reader.name().compare("Caster") == 0))
                        {
                            reader.readNext();

                            if (reader.isStartElement() && reader.name().compare("Action") == 0)
                            {
                                QString name = reader.attributes().value("name").toString();

                                auto ruleIt = std::find_if(TargetRules.begin(), TargetRules.end(), [&name](ActionRule* rule) {
                                    return rule->name == name.toStdString();
                                });

                                if (ruleIt != TargetRules.end())
                                {
                                    ActionRule* rule = *ruleIt;
                                    rule->Deserialize(reader);
                                }
                            }
                        }
                    }
                    else if (reader.isStartElement() && reader.name().compare("UseEKCombo") == 0)
                    {
                        reader.readNext();
                        m_partyHuntUseEKCombo = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("EKRules") == 0)
                    {
                        while (!(reader.isEndElement() && reader.name().compare("EKRules") == 0))
                        {
                            reader.readNext();

                            if (reader.isStartElement() && reader.name().compare("Action") == 0)
                            {
                                QString name = reader.attributes().value("name").toString();

                                auto ruleIt = std::find_if(KnightTargetRules.begin(), KnightTargetRules.end(), [&name](ActionRule* rule) {
                                    return rule->name == name.toStdString();
                                });

                                if (ruleIt != KnightTargetRules.end())
                                {
                                    ActionRule* rule = *ruleIt;
                                    rule->Deserialize(reader);
                                }
                            }
                        }
                    }
                }
            }
            else if (reader.name().compare("Config") == 0)
            {
                // Desserialização das configurações gerais
                while (!(reader.isEndElement() && reader.name().compare("Config") == 0))
                {
                    reader.readNext();

                    if (reader.isStartElement() && reader.name().compare("RespectAttackTurns") == 0)
                    {
                        reader.readNext();
                        m_respectAttackTurns = reader.text().toString().toInt();
                    }
                }
            }
            else if (reader.name().compare("Status") == 0)
            {
                // Desserialização das configurações de status do Healer
                while (!(reader.isEndElement() && reader.name().compare("Status") == 0))
                {
                    reader.readNext();

                    if (reader.isStartElement() && reader.name().compare("Healer") == 0)
                    {
                        reader.readNext();
                        m_healerStatus = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("Tools") == 0)
                    {
                        reader.readNext();
                        m_toolsStatus = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("PvP") == 0)
                    {
                        reader.readNext();
                        m_pvpToolsStatus = reader.text().toString().toInt();
                    }
                    else if (reader.isStartElement() && reader.name().compare("PartyHunt") == 0)
                    {
                        reader.readNext();
                        m_partyHuntStatus = reader.text().toString().toInt();
                    }
                }
            }
        }
    }
}

void ScriptConfig::UpdateHotkeys(std::string& errorString)
{
    //Vocation playerVoc = Objects::Client::getPlayerCreature()->getVocation();
    for (auto rule : Globals::getScriptConfig()->HealRules)
    {
        // Reset

        /*
        actionSettings* setting = NULL;
        std::string name = rule->spell->name;
        std::string input = rawInput;
        std::string itemUseType = rule->getItemUseType();

        QString inputQString = QString::fromStdString(input).toLower();

        if (input.empty())
            continue;
        else if (!Objects::Client::items[inputQString.toStdString()].empty())
            input = Objects::Client::items[inputQString.toStdString()];

        if (std::all_of(input.begin(), input.end(), ::isdigit))
            setting = Objects::Client::getHotkeyByItemId(std::stoi(input), itemUseType);
        else
            setting = Objects::Client::getHotkeyByText(input);

        if (setting == NULL)
        {
            if (rule->getStatus() && (rule->getHealth() != 0 || rule->getMana() != 0) && errorString.find(rawInput) == std::string::npos)
                errorString += "Nao foi possivel achar uma hotkey para " + rawInput + ".\n";
        }
        else
        {
            rule->setHotkeyChatOff(setting->getHotkeyChatOff());
            rule->setHotkeyChatOffExtended(setting->getHotkeyChatOffExtended());
            rule->setHotkeyChatOn(setting->getHotkeyChatOn());
            rule->setHotkeyChatOnExtended(setting->getHotkeyChatOnExtended());
        }
*/
    }
/*
    for (auto rule : Globals::getScriptConfig()->getTargetRules())
    {
        // Reset
        rule->setHotkeyChatOn(0);
        rule->setHotkeyChatOnExtended(false);
        rule->setHotkeyChatOff(0);
        rule->setHotkeyChatOffExtended(false);

        actionSettings* setting = NULL;
        std::string rawInput = rule->getInput();
        std::string input = rawInput;
        QString inputQString = QString::fromStdString(input).toLower();
        std::string itemUseType = rule->getItemUseType();

        if (input.empty())
            continue;
        //else if (rule->)
        //    input = Objects::Client::items[inputQString.toStdString()];


        if (std::all_of(input.begin(), input.end(), ::isdigit))
            setting = Objects::Client::getHotkeyByItemId(std::stoi(input), itemUseType);
        else
            setting = Objects::Client::getHotkeyByText(input);

        if (setting == NULL)
        {
            if (rule->getStatus() && (rule->getStatus()) && errorString.find(rawInput) == std::string::npos)
                errorString += "Nao foi possivel achar uma hotkey para " + rawInput + ".\n";
        }
        else
        {
            rule->setHotkeyChatOff(setting->getHotkeyChatOff());
            rule->setHotkeyChatOffExtended(setting->getHotkeyChatOffExtended());
            rule->setHotkeyChatOn(setting->getHotkeyChatOn());
            rule->setHotkeyChatOnExtended(setting->getHotkeyChatOnExtended());
        }
    }
*/
}
