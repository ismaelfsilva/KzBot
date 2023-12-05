#include "pvptools.h"

#include <iostream>
#include <thread>
#include <chrono>

#include "../Settings/globals.h"
#include "../Objects/game.h"
#include "../Objects/client.h"
#include "../Objects/battlelist.h"

using namespace Objects;

Threads::PvPTools::PvPTools()
{    
    scriptConfig = Globals::getScriptConfig();
}

Threads::PvPTools::~PvPTools()
{
    Stop();
}

void Threads::PvPTools::Start()
{
    m_pvpToolsThread = std::thread(&Threads::PvPTools::m_threadFunc, this);
}

void Threads::PvPTools::m_threadFunc()
{
    //try
    {
        if (!Globals::isSet) // Client not set
            return;

        if (scriptConfig->getPvPOnComboUE())
        {
            // Combo UE
            static uint64_t lastComboUE = 0;
            if (Game::getGameTime() - lastComboUE > 10000)
            {
                uint32_t UECount = 0;
                for (auto UE : Game::getUltimateExplosions())
                {
                    if (Game::getGameTime() - UE.second < 5000 && (lastComboUE == 0 || UE.second - lastComboUE > 10000))
                        UECount++;
                }
                if (UECount >= scriptConfig->getUECountToConsiderCombo())
                {
                    std::cout << "combo ue" << std::endl;
                    lastComboUE = Game::getGameTime();

                    // Do Rules
                    std::vector<ComboRule*> ueComboRules = {scriptConfig->m_pvpOnComboUEActionA, scriptConfig->m_pvpOnComboUEActionB};
                    for (ComboRule* c : ueComboRules)
                    {
                        Input* input = new Input();

                        if (c->spell != nullptr && ((Game::isSpellOnCooldown(c->spell) && c->itemId != 35563) && c->spell->vocations[Game::getPlayerVocation()]))
                        {
                            delete input;
                            continue;
                        }

                        input->gameTime = Game::getGameTime();
                        input->canRepeat = true;

                        if (c->itemId > 0)
                        {
                            input->itemId = c->itemId;
                            input->itemUseType = ItemUseType::UseOnTarget;

                            if (c->spell != nullptr && c->spell->selfTarget)
                                input->itemUseType = ItemUseType::Use;
                        }
                        else if (!c->spellInput.empty())
                        {
                            input->text = c->spellInput;
                        }

                        Globals::addInput(input);
                    }
                }
            }
        }

        if (scriptConfig->getPvPOnComboAvatar())
        {
            static uint64_t lastAvatarCombo = 0;
            if (Game::getGameTime() - lastAvatarCombo > 10000)
            {
                uint32_t avatarCount = 0;
                for (auto avatar : Game::getAvatarTransformations())
                {
                    if (Game::getGameTime() - avatar.second < 5000 && (lastAvatarCombo == 0 || avatar.second - lastAvatarCombo > 10000))
                        avatarCount++;
                }
                if (avatarCount >= scriptConfig->getAvatarCountToConsiderCombo())
                {
                    std::cout << "avatar" << std::endl;
                    lastAvatarCombo = Game::getGameTime();

                    // Do Rules
                    std::vector<ComboRule*> avatarComboRules = {scriptConfig->m_pvpOnComboAvatarActionA, scriptConfig->m_pvpOnComboAvatarActionB};
                    for (ComboRule* c : avatarComboRules)
                    {
                        Input* input = new Input();

                        if (c->spell != nullptr && ((Game::isSpellOnCooldown(c->spell) && c->itemId != 35563) && c->spell->vocations[Game::getPlayerVocation()]))
                        {
                            delete input;
                            continue;
                        }

                        input->gameTime = Game::getGameTime();
                        input->canRepeat = true;

                        if (c->itemId > 0)
                        {
                            input->itemId = c->itemId;
                            input->itemUseType = ItemUseType::UseOnTarget;

                            if (c->spell != nullptr && c->spell->selfTarget)
                                input->itemUseType = ItemUseType::Use;
                        }
                        else if (!c->spellInput.empty())
                        {
                            input->text = c->spellInput;
                        }

                        Globals::addInput(input);
                    }
                }
            }
        }

        if (scriptConfig->getPvPHoldTarget() && Game::isLastTargetOnScreen() && Game::getTargetId() != Game::getLastTargetId())
            Objects::Battlelist::setTargetId(Game::getDataPointer(), Game::getLastTargetId());

        if (scriptConfig->getPvPParalyzeTarget() && Game::getTargetId() == Game::getLastTargetId() && Game::isLastTargetRunning())
        {
            Spell* paralyzeRune = Globals::getSpell(54);

            if (Game::getTargetedCreature().Speed > 200 && Game::getPlayerVocation() == Vocation::Druid && Game::getPlayerMp() > 1400 && !Game::isSpellOnCooldown(paralyzeRune))
            {
                Input* itemInput = new Input();
                itemInput->gameTime = Game::getGameTime();
                itemInput->itemId = paralyzeRune->itemId;
                itemInput->itemUseType = ItemUseType::UseOnTarget;

                Globals::addInput(itemInput);
            }
        }

        if (scriptConfig->getPvPDashTarget() && Game::getTargetedCreature().Id == Game::getLastTargetId())
        {
            Objects::Client::Goto(Game::getTargetedCreature().Position);
        }

        if (scriptConfig->getPvPChatNaviStatus())
        {
            for (std::pair<std::string, std::string> chatMessage : Game::getNewChatMessages())
            {
                for (ComboRule* c : scriptConfig->ComboRules)
                {
                    if (chatMessage.first == c->leader && chatMessage.second == c->content)
                    {
                        Input* input = new Input();

                        if (c->spell != nullptr && ((Game::isSpellOnCooldown(c->spell) && c->itemId != 35563) && c->spell->vocations[Game::getPlayerVocation()]))
                        {
                            delete input;
                            continue;
                        }

                        input->gameTime = Game::getGameTime();
                        input->canRepeat = true;

                        if (c->itemId > 0)
                        {
                            input->itemId = c->itemId;
                            input->itemUseType = ItemUseType::UseOnTarget;

                            if (c->spell != nullptr && c->spell->selfTarget)
                                input->itemUseType = ItemUseType::Use;
                        }
                        else if (!c->spellInput.empty())
                        {
                            input->text = c->spellInput;
                        }

                        Globals::addInput(input);
                    }
                }
            }
        }
    }
    /*
    catch (...)
    {    }
    */
}

void Threads::PvPTools::Stop()
{
    m_pvpToolsThread.join();
    m_pvpToolsThread.detach();
}
