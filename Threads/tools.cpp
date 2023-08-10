#include "tools.h"

#include "../Settings/globals.h"
#include "../Settings/scriptconfig.h"
#include "../Objects/client.h"
#include "../Objects/game.h"

using namespace Objects;

Threads::Tools::Tools()
{
    scriptConfig = Globals::getScriptConfig();
}

Threads::Tools::~Tools()
{
    Stop();
}

void Threads::Tools::Start()
{
    m_toolsThread = std::thread(&Threads::Tools::m_threadFunc, this);
}

void Threads::Tools::m_threadFunc()
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
        int playerSpeed = Game::getPlayerSpeed();
        Vocation playerVoc = Game::getPlayerVocation();

        bool usedItem = false;
        std::unordered_map<CooldownGroup, bool> cooldownGroupUsed = {
            {CooldownGroup::Heal, Game::isGroupOnCooldown(CooldownGroup::Heal)},
            {CooldownGroup::Attack, Game::isGroupOnCooldown(CooldownGroup::Attack)},
            {CooldownGroup::Support, Game::isGroupOnCooldown(CooldownGroup::Support)}
        };

        for (ActionRule* rule : scriptConfig->ToolsRules)
        {
            Spell* ruleSpell = rule->spell;

            if (!rule->enabled || (rule->type == ActionType::Spell && ruleSpell == nullptr))
                continue;

            if (ruleSpell != nullptr && (cooldownGroupUsed[ruleSpell->group] || Game::isSpellOnCooldown(ruleSpell) || ruleSpell->mana > playerMana || ruleSpell->level > playerLevel || !ruleSpell->vocations[playerVoc]))
                continue;

            if (!Game::canCast(rule->delayType1) || !Game::canCast(rule->delayType2))
                continue;

            if (rule->type == ActionType::Equip)
            {
                // Amulets
                if (rule->name == "stoneSkinAmuletEquip" && (Game::getAmuletId() == rule->spell->itemId) == ((rule->maxHp != 0 && playerHp <= rule->maxHp) || (rule->maxMp != 0 && playerMp <= rule->maxMp)))
                    continue;
                else if (rule->name == "defaultAmuletEquip" && Game::getAmuletId() != 0)
                    continue;

                // Rings
                else if (rule->name == "energyRingEquip" && (Game::getRingId() == 3088) && (playerHp <= rule->maxHp && playerMp >= rule->minMp))
                    continue;
                else if (rule->name == "energyRingEquip" && (Game::getRingId() != 3088) && (playerHp > rule->maxHp || playerMp < rule->minMp))
                    continue;
                else if (rule->name == "mightRingEquip" && (Game::getRingId() == 3088 || (Game::getRingId() == rule->spell->itemId) == ((rule->maxHp != 0 && playerHp <= rule->maxHp) || (rule->maxMp != 0 && playerMp <= rule->maxMp))))
                    continue;
                else if (rule->name == "defaultRingEquip" && Game::getRingId() != 0)
                    continue;
            }
            else if (playerHp < rule->minHp || playerHp > rule->maxHp || playerMp < rule->minMp || playerMp > rule->maxMp || playerMagicShield < rule->minMagicShield || playerMagicShield > rule->maxMagicShield )
                continue;

            if (rule->hasteSpell && playerSpeed >= floor((playerLevel + 100) * 1.3))
                continue;

            if (rule->onParalyzeSpell && playerSpeed >= playerLevel + 100)
                continue;


            if (rule->type == ActionType::Equip)
            {
                Input* itemInput = new Input();
                itemInput->gameTime = Game::getGameTime();
                //3088 id energy ring

                if (ruleSpell != nullptr)
                    itemInput->itemId = ruleSpell->itemId;
                else
                    itemInput->itemId = rule->itemId;

                if (rule->name == "energyRingEquip" && Game::getRingId() == 3088)
                    itemInput->itemId = 3088;

                itemInput->itemUseType = ItemUseType::Equip;

                if (Game::getAmuletId() != itemInput->itemId && Game::getRingId() != itemInput->itemId)
                    Game::increaseDelay(rule->delayType1);

                Globals::addInput(itemInput);
            }
            else if (rule->type == ActionType::Spell)
            {
                Input* textInput = new Input();
                textInput->gameTime = Game::getGameTime();
                textInput->text = ruleSpell->words;

                Globals::addInput(textInput);
                cooldownGroupUsed[ruleSpell->group] = true;
            }

        }
    }
    /*
    catch (...)
    {

    }
    */
}

void Threads::Tools::Stop()
{
    m_toolsThread.join();
    m_toolsThread.detach();
}


