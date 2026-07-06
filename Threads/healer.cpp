
#include "healer.h"
#include "../Settings/globals.h"
#include "../Objects/client.h"
#include "../Objects/battlelist.h"
#include "../Objects/creature.h"
#include "../Objects/player.h"
#include "../Objects/game.h"
#include "../Util/kzhelper.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace Objects;

Threads::Healer::Healer()
{
    scriptConfig = Globals::getScriptConfig();
}

Threads::Healer::~Healer()
{
    Stop();
}

void Threads::Healer::Start()
{
        m_healerThread = std::thread(&Threads::Healer::m_threadFunc, this);
}

    // 266 AVATAR MS

void Threads::Healer::m_threadFunc()
{
        //try
        {
            if (!Globals::isSet) // Client not set
                return;

            int playerHp = Game::getPlayerHpPercent();
            int playerMp = Game::getPlayerMpPercent();
            int playerMana = Game::getPlayerMp();
            int playerMagicShield = Game::getPlayerManaShieldPercent();
            int playerLevel = Game::getPlayerLevel();
            Vocation playerVoc = Game::getPlayerVocation();
            uint64_t gameTime = Objects::Game::getGameTime();

            bool usedItem = false;
            bool usedUtamo = false;
            std::unordered_map<CooldownGroup, bool> cooldownGroupUsed = {
                {CooldownGroup::Heal, Game::isGroupOnCooldown(CooldownGroup::Heal)},
                {CooldownGroup::Attack, Game::isGroupOnCooldown(CooldownGroup::Attack)},
                {CooldownGroup::Support, Game::isGroupOnCooldown(CooldownGroup::Support)}
            };

            CachedCreature friendToHeal = Objects::Game::getFriendToHeal();

            for (ActionRule *rule : scriptConfig->HealRules)
            {
                Spell* ruleSpell = rule->spell;

                if (!rule->enabled || ruleSpell == nullptr)
                    continue;

                if (ruleSpell != nullptr && (cooldownGroupUsed[ruleSpell->group] || Game::isSpellOnCooldown(ruleSpell) || (ruleSpell->duration > 0 && Game::getGameTime() < Game::getSpellLastCooldownEnd(ruleSpell) + ruleSpell->duration) || ruleSpell->mana > playerMana || ruleSpell->level > playerLevel || !ruleSpell->vocations[playerVoc]))
                    continue;

                bool isItem = ruleSpell->itemId > 0;
                if (isItem && !rule->alwaysUse && (usedItem || !Game::canUseHealItem()))
                    continue;

                if (isItem && ruleSpell->itemId == 35563 && usedUtamo)
                    continue;

                if (ruleSpell->id == 245 && (usedUtamo || playerMagicShield < rule->minMagicShield || ((rule->minHp == 0 || playerHp < rule->minHp) && (rule->maxMp == 0 || playerMp > rule->maxMp))))
                    continue;
                else if (ruleSpell->id != 245 && (playerHp < rule->minHp || playerHp > rule->maxHp || playerMp < rule->minMp || playerMp > rule->maxMp || playerMagicShield < rule->minMagicShield || playerMagicShield > rule->maxMagicShield ))
                    continue;

                // Sio ter prioridade do que cura se tiver de utamo
                //if ((Globals::getScriptConfig()->getHealFriendGeneralStatus() && !(ruleSpell->requiresPlayerNameParam && ruleSpell->requiresTarget) && friendToHeal.Id > 0 && !isItem) && playerMagicShield > 50 && playerHp > 60)
                //    continue;


                if ((ruleSpell->requiresPlayerNameParam || ruleSpell->requiresTarget) && (friendToHeal.Id == 0 || friendToHeal.Health < rule->minCreatureHp || friendToHeal.Health > rule->maxCreatureHp))
                    continue;

                if (!Game::canCast(rule->delayType1) || !Game::canCast(rule->delayType2))
                    continue;


                if (Game::getGameTime() - rule->lastUse < scriptConfig->minAntiSpamDelay)
                    continue;

                if (isItem)
                {
                    Input* itemInput = new Input();
                    itemInput->gameTime = Game::getGameTime();
                    itemInput->itemId = ruleSpell->itemId;

                    if (ruleSpell->requiresTarget)
                    {
                        itemInput->targetId = friendToHeal.Id;
                        itemInput->itemUseType = ItemUseType::UseOnTarget;
                        itemInput->requiresRealTarget = ruleSpell->requiresRealTarget;
                    }
                    else if (ruleSpell->selfTarget)
                        itemInput->itemUseType = ItemUseType::Use;
                    else
                        itemInput->itemUseType = ItemUseType::UseOnYourself;

                    Globals::addInput(itemInput);
                }
                else
                {
                    Input* textInput = new Input();
                    textInput->gameTime = Game::getGameTime();
                    if (ruleSpell->requiresPlayerNameParam)
                        textInput->text = ruleSpell->words + " \"" + friendToHeal.Name;
                    else
                        textInput->text = ruleSpell->words;
                    Globals::addInput(textInput);

                    if (ruleSpell->id == 44)
                        usedUtamo = true;
                }

                cooldownGroupUsed[ruleSpell->group] = true;
                Game::increaseDelay(rule->delayType1);
                Game::increaseDelay(rule->delayType2);

                rule->lastUse = Game::getGameTime();
            }
        }
        /*
        catch (...)
        {
        }
*/
}

void Threads::Healer::Stop()
{
    m_healerThread.join();
    m_healerThread.detach();
}

