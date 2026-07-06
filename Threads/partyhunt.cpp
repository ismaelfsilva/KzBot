
#include "partyhunt.h"
#include "../Settings/globals.h"
#include "../Objects/client.h"
#include "../Objects/game.h"
#include "../Objects/battlelist.h"
#include "../Objects/creature.h"
#include "../Objects/player.h"
#include <iostream>
#include <thread>
#include <chrono>

Threads::PartyHunt::PartyHunt()
{
    scriptConfig = Globals::getScriptConfig();
}

Threads::PartyHunt::~PartyHunt()
{
    Stop();
}

void Threads::PartyHunt::Start()
{
        m_partyHuntThread = std::thread(&Threads::PartyHunt::m_threadFunc, this);
}

bool getBestPosition(Position& bestAreaRunePos, int& bestAreaRuneQty, CachedCreature& creatureToTarget)
{
    Position playerPosition = Objects::Game::getPlayerPosition();
    std::map<std::pair<int, int>, std::vector<CachedCreature>> creatureMap = Game::getCreatureMap();

    int bestAreaRuneDist = 99;

    int bestAreaTargetQty = 0;
    int bestAreaTargetDist = 99;

    for (int x = -7; x <= 7; x++)
    {
        for (int y = -5; y <= 5; y++)
        {
            int posAroundQty = 0;
            Position pos = Position(playerPosition.X() + x, playerPosition.Y() + y, playerPosition.Z());

            for (int aroundX = -2; aroundX <= 2; aroundX++)
            {
                for (int aroundY = -2; aroundY <= 2; aroundY++)
                {
                    posAroundQty += creatureMap[{x + aroundX, y + aroundY}].size();
                }
            }

            if (posAroundQty >= bestAreaTargetQty && !creatureMap[{x, y}].empty())
            {
                int posDistToPlayer = playerPosition.getDistance(pos);
                if (posDistToPlayer <= 5 && (posAroundQty > bestAreaTargetQty || posDistToPlayer < bestAreaTargetDist))
                {
                    creatureToTarget = creatureMap[{x, y}].front();
                    bestAreaTargetQty = posAroundQty;
                    bestAreaTargetDist = posDistToPlayer;
                }
            }
            if (posAroundQty >= bestAreaRuneQty)
            {
                int posDistToPlayer = playerPosition.getDistance(pos);
                if (posAroundQty > bestAreaRuneQty || posDistToPlayer < bestAreaRuneDist)
                {
                    bestAreaRunePos = pos;
                    bestAreaRuneQty = posAroundQty;
                    bestAreaRuneDist = posDistToPlayer;
                }

            }
        }
    }

    return true;
}

void Threads::PartyHunt::m_threadFunc()
{
    //while (scriptConfig->getGeneralStatus() && scriptConfig->getPartyHuntStatus())
    //{
    //try
    {
        if (!Globals::isSet) // Client not set
            return;

        if (Game::getCreaturesAroundCount() <= 0) // No Creatures Around
            return;

        if (Game::getPlayerHasStatus(Icons::ICON_PIGEON))
            return;

        bool usedItem = false;
        std::unordered_map<CooldownGroup, bool> cooldownGroupUsed = {
            {CooldownGroup::Heal, Game::isGroupOnCooldown(CooldownGroup::Heal)},
            {CooldownGroup::Attack, Game::isGroupOnCooldown(CooldownGroup::Attack)},
            {CooldownGroup::Support, Game::isGroupOnCooldown(CooldownGroup::Support)}
        };

        bool findBestAreaRunePos = scriptConfig->getPartyHuntAreaRune() && !cooldownGroupUsed[CooldownGroup::Attack];
        Position bestAreaRunePos;
        int bestAreaRuneQty = 0;

        bool findBestAreaTarget = Objects::Game::getPlayerVocation() == Vocation::Paladin && scriptConfig->getPartyHuntAutoTargetStatus();
        CachedCreature targetedCreature = Game::getTargetedCreature();
        CachedCreature creatureToTarget;

        bool foundBestSpots = false;
        std::chrono::time_point<std::chrono::system_clock> timeNow = std::chrono::system_clock::now();
        static std::chrono::time_point<std::chrono::system_clock> timeToTargetAgain;
        static std::chrono::time_point<std::chrono::system_clock> minDelayBetweenTargets;

        if (scriptConfig->getPartyHuntAutoTargetStatus() && timeNow > minDelayBetweenTargets && (targetedCreature.Id == 0 || timeNow > timeToTargetAgain))
        {
            if (findBestAreaTarget)
                foundBestSpots = getBestPosition(bestAreaRunePos, bestAreaRuneQty, creatureToTarget);
            else
            {
                creatureToTarget = Game::getClosestCreature();
                if (creatureToTarget.distToPlayer >= targetedCreature.distToPlayer)
                    creatureToTarget = targetedCreature;
            }

            if (creatureToTarget.Id != 0 && targetedCreature.Id != creatureToTarget.Id)
            {
                if (targetedCreature.Id == 0)
                    timeToTargetAgain = timeNow + std::chrono::milliseconds(1900);
                else
                    timeToTargetAgain = timeNow + std::chrono::milliseconds(2000);

                Input* targetInput = new Input();
                targetInput->requiresRealTarget = true;
                targetInput->targetId = creatureToTarget.Id;
                targetInput->canRepeat = true;
                targetInput->gameTime = Game::getGameTime();
                targetInput->position = creatureToTarget.Position;

                minDelayBetweenTargets = timeNow + std::chrono::milliseconds(200);
                Globals::addInput(targetInput);
            }
        }

        // DEBUFF MS - ADICIONAR CHECK SE TEM CD E SE TA ATIVO
        if (cooldownGroupUsed[CooldownGroup::Attack])
            return;

        int playerHp = Game::getPlayerHpPercent();
        int playerMp = Game::getPlayerMpPercent();
        int playerMana = Game::getPlayerMp();
        int playerMagicShield = Game::getPlayerManaShieldPercent();
        int playerLevel = Game::getPlayerLevel();
        Direction playerDir = Game::getPlayerDirection();
        Vocation playerVoc = Game::getPlayerVocation();
        Position playerPosition = Objects::Game::getPlayerPosition();

        // Find Party's Knight // Default Value = Player Creature;
        CachedCreature partyKnight = Game::getPartyKnight();
        CachedCreature lowestCreature = Game::getCreaturesOnScreen().front();
        int distPlayerToKnight = 99;
        if (partyKnight.Id != 0)
            distPlayerToKnight = partyKnight.Position.getDistance(playerPosition);

        int creaturesAroundKnightSmallArea = Game::getCreaturesKnightAreaSmall(); // Creatures 1 SQM Away from EK;
        int creaturesAroundKnightDefaultArea = Game::getCreaturesKnightAreaDefault(); // Creatures 2 SQM Away from EK;
        int creaturesAroundKnightUltimateArea = Game::getCreaturesKnightAreaUltimate(); // Creatures 2 SQM Away from EK;

        int creaturesAroundPlayerSmallArea = Game::getCreaturesPlayerAreaSmall(); // Creatures 1 SQM Away from Player;
        int creaturesAroundPlayerDefaultArea = Game::getCreaturesPlayerAreaDefault(); // Creatures 2 SQM Away from Player;
        int creaturesAroundPlayerUltimateArea = Game::getCreaturesPlayerAreaUltimate(); // Creatures 4 SQM Away from Player;

        std::vector<ActionRule*>* targetingRules = &scriptConfig->TargetRules;
        if (scriptConfig->getPartyHuntUseEKCombo())
            targetingRules = &scriptConfig->KnightTargetRules;


        for (ActionRule* rule : *targetingRules)
        {
            Spell* ruleSpell = rule->spell;
            Direction dirToTurn = Direction::None;

            if (!rule->enabled || ruleSpell == nullptr)
                continue;

            if (ruleSpell != nullptr && (cooldownGroupUsed[ruleSpell->group] || Game::isSpellOnCooldown(ruleSpell) || (ruleSpell->duration > 0 && Game::getGameTime() < Game::getSpellLastCooldownEnd(ruleSpell) + ruleSpell->duration) || ruleSpell->mana > playerMana || ruleSpell->level > playerLevel || !ruleSpell->vocations[playerVoc]))
                continue;

            bool isItem = ruleSpell->itemId > 0;
            if (isItem && !rule->alwaysUse && usedItem)
                continue;

            if (playerHp < rule->minHp || playerHp > rule->maxHp || playerMp < rule->minMp || playerMp > rule->maxMp || playerMagicShield < rule->minMagicShield || playerMagicShield > rule->maxMagicShield )
                continue;

            if (rule->centerKnight && partyKnight.Id > 0)
            {
                if (ruleSpell->area == 1 && creaturesAroundKnightSmallArea < rule->creatureCount)
                    continue;
                else if (ruleSpell->area == 2 && creaturesAroundKnightDefaultArea < rule->creatureCount)
                    continue;
                else if (ruleSpell->area == 4 && creaturesAroundKnightUltimateArea < rule->creatureCount)
                    continue;

                int ekX = partyKnight.Position.X();
                int ekY = partyKnight.Position.Y();
                int pX = playerPosition.X();
                int pY = playerPosition.Y();

                if (pX == ekX && pY - ekY == ruleSpell->range)
                    dirToTurn = Direction::NORTH;
                else if (pX == ekX && ekY - pY == ruleSpell->range)
                    dirToTurn = Direction::SOUTH;
                else if (pY == ekY && pX - ekX  == ruleSpell->range)
                    dirToTurn = Direction::WEST;
                else if (pY == ekY && ekX - pX == ruleSpell->range)
                    dirToTurn = Direction::EAST;
                else if (ruleSpell->range > 0)
                    continue;

                // CHECK WAVE HERE
            }
            else if (ruleSpell->requiresTarget)
            {
                if ((lowestCreature.Id <= 0 || lowestCreature.Health > rule->maxCreatureHp || lowestCreature.Health <= 0))
                    continue;
                else if (ruleSpell->range > 0 && lowestCreature.distToPlayer > ruleSpell->range)
                {
                    for (CachedCreature creature : Game::getCreaturesOnScreen())
                    {
                        if (creature.distToPlayer <= ruleSpell->range && creature.Health <= rule->maxCreatureHp && creature.Health > 0)
                        {
                            lowestCreature = creature;
                            break;
                        }
                    }

                    if (ruleSpell->range > 0 && lowestCreature.distToPlayer > ruleSpell->range)
                        continue;
                }
            }
            else if (ruleSpell->selfTarget)
            {
                if (ruleSpell->area == 1 && creaturesAroundPlayerSmallArea < rule->creatureCount)
                    continue;
                else if (ruleSpell->area == 2 && creaturesAroundPlayerDefaultArea < rule->creatureCount)
                    continue;
                else if (ruleSpell->area == 4 && creaturesAroundPlayerUltimateArea < rule->creatureCount)
                    continue;
            }
            else if (findBestAreaRunePos && ruleSpell->allowFarUse)
            {
                if (!foundBestSpots)
                    foundBestSpots = getBestPosition(bestAreaRunePos, bestAreaRuneQty, creatureToTarget);

                if (bestAreaRuneQty < rule->creatureCount)
                    continue;
            }
            else
                continue;

            if (!Game::canCast(rule->delayType1) || !Game::canCast(rule->delayType2))
                continue;

            if (isItem)
            {
                Input* itemInput = new Input();
                itemInput->gameTime = Game::getGameTime();
                itemInput->itemId = ruleSpell->itemId;
                itemInput->canRepeat = true;

                if (ruleSpell->requiresTarget)
                {
                    itemInput->targetId = lowestCreature.Id;
                    itemInput->itemUseType = ItemUseType::UseOnTarget;
                }
                else
                {
                    if (rule->centerKnight && partyKnight.Id > 0)
                        itemInput->position = partyKnight.Position;
                    else if (findBestAreaRunePos && bestAreaRuneQty >= rule->creatureCount)
                        itemInput->position = bestAreaRunePos;
                    else
                    {
                        delete itemInput;
                        continue;
                    }

                    itemInput->itemUseType = ItemUseType::UseWithCrosshair;
                    itemInput->usesCrosshair = true;
                }
                Globals::addInput(itemInput);
            }
            else
            {
                if (dirToTurn != Direction::None && dirToTurn != playerDir)
                {
                    if (rule->turn)
                        Objects::Client::Turn(dirToTurn);
                    else
                        continue;
                }


                Input* textInput = new Input();
                textInput->canRepeat = true;

                if (ruleSpell->requiresRealTarget)
                {
                    textInput->requiresRealTarget = true;

                    if (rule->centerKnight && partyKnight.Id > 0)
                        textInput->position = partyKnight.Position;
                    else if (!rule->centerKnight && lowestCreature.Id > 0)
                        textInput->position = lowestCreature.Position;
                    else if (rule->centerKnight && ruleSpell->area > 0)
                    {}
                    else
                    {
                        delete textInput;
                        continue;
                    }
                }
                textInput->gameTime = Game::getGameTime();
                textInput->text = ruleSpell->words;
                Globals::addInput(textInput);

                // Reset Utito/Utamo CD
                if (ruleSpell->id == 132)
                    Game::setSpellLastCooldownEnd(Globals::getSpell(133), 0);
                else if (ruleSpell->id == 133)
                    Game::setSpellLastCooldownEnd(Globals::getSpell(132), 0);
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

void Threads::PartyHunt::Stop()
{
    m_partyHuntThread.join();
    m_partyHuntThread.detach();
}

