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

        // Anti Idle
        static uint64_t lastActionTime = Game::getPlayerLastWalk();
        if (scriptConfig->getToolsAntiIdle())
        {
            if (Game::getPlayerLastWalk() > lastActionTime)
                lastActionTime = Game::getPlayerLastWalk();

            if (Game::getGameTime() - lastActionTime >= 9 * 60 * 1000)
            {
                Client::Turn(Direction::NORTH);
                Client::Turn(Direction::SOUTH);

                lastActionTime = Game::getGameTime();
            }
        }

        // Auto Eat Food
        static uint64_t lastEatFoodTime = 0;
        if (scriptConfig->getToolsEatFood())
        {
            if (Game::getPlayerIsHungry() && Game::getGameTime() - lastEatFoodTime > 2000)
            {
                for (int i = 0; i < 3; i++)
                {
                    Input* itemInput = new Input();
                    itemInput->gameTime = Game::getGameTime();
                    itemInput->itemId = scriptConfig->getToolsEatFoodId();
                    itemInput->itemUseType = ItemUseType::Use;

                    Globals::addInput(itemInput);
                }

                lastEatFoodTime = Game::getGameTime();
            }
        }

        // Auto Buff
        static uint64_t lastBuffTime = 0;
        if (scriptConfig->getToolsAutoBuff())
        {
            if (!Game::getPlayerHasStatus(Icons::ICON_PARTY_BUFF) && Game::getGameTime() - lastBuffTime > 2000)
            {
                Input* itemInput = new Input();
                itemInput->gameTime = Game::getGameTime();
                itemInput->itemId = scriptConfig->getToolsAutoBuffItemId();
                itemInput->itemUseType = ItemUseType::Use;

                Globals::addInput(itemInput);

                lastBuffTime = Game::getGameTime();
            }
        }

        // Auto Hold Position
        if (scriptConfig->getToolsHoldPosition() &&  Game::getPlayerPosition() != scriptConfig->getToolsHoldPositionPos())
        {
            Client::Goto(scriptConfig->getToolsHoldPositionPos());
        }

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
                if (rule->name == "stoneSkinAmuletEquip" && (rule->spell == nullptr || (Game::getAmuletId() == rule->spell->itemId) == ((rule->maxHp != 0 && playerHp <= rule->maxHp) || (rule->maxMp != 0 && playerMp <= rule->maxMp))))
                    continue;
                else if (rule->name == "defaultAmuletEquip" && Game::getAmuletId() != 0)
                    continue;


                // Rings
                else if (rule->name == "energyRingEquip" && (Game::getRingId() == 3088) && (playerHp <= rule->maxHp && playerMp >= rule->minMp))
                    continue;
                else if (rule->name == "energyRingEquip" && (Game::getRingId() != 3088) && (playerHp > rule->maxHp || playerMp < rule->minMp))
                    continue;
                else if (rule->name == "mightRingEquip" && (rule->spell == nullptr || (Game::getRingId() == 3088 || (Game::getRingId() == rule->spell->itemId) == ((rule->maxHp != 0 && playerHp <= rule->maxHp) || (rule->maxMp != 0 && playerMp <= rule->maxMp)))))
                    continue;
                else if (rule->name == "defaultRingEquip" && Game::getRingId() != 0)
                    continue;
            }
            else if (playerHp < rule->minHp || playerHp > rule->maxHp || playerMp < rule->minMp || playerMp > rule->maxMp || playerMagicShield < rule->minMagicShield || playerMagicShield > rule->maxMagicShield )
                continue;

            if (rule->hasteSpell && Game::getPlayerHasStatus(Icons::ICON_HASTE))
                continue;

            if (rule->onParalyzeSpell && !Game::getPlayerHasStatus(Icons::ICON_PARALYZE))
                continue;

            if (Game::getGameTime() - rule->lastUse < scriptConfig->minAntiSpamDelay)
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

                // CHECK IF HAS DURATION, THEN SET SPELL COOLDOWN TO DURATION
                cooldownGroupUsed[ruleSpell->group] = true;

                Game::increaseDelay(rule->delayType1);
                Game::increaseDelay(rule->delayType2);
            }

            rule->lastUse = Game::getGameTime();
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


