#define NOMINMAX
#include "game.h"
#include "client.h"
#include "battlelist.h"
#include "chat.h"
#include <iostream>

using namespace Objects;


uint32_t Game::m_dataPointer;

uint64_t Game::m_gameTime;
int Game::m_gamePing;

Creature* Game::m_playerCreature;
Position Game::m_playerPosition;
Direction Game::m_playerDirection;
Vocation Game::m_playerVocation;
uint32_t Game::m_targetId;
uint32_t Game::m_lastTargetId;
int Game::m_playerSpeed;

int Game::m_playerHp;
int Game::m_playerHpMax;
int Game::m_playerHpPercent;

// Mana
int Game::m_playerMp;
int Game::m_playerMpMax;
int Game::m_playerMpPercent;

// Mana Shield
int Game::m_playerManaShield;
int Game::m_playerManaShieldMax;
int Game::m_playerManaShieldPercent;

int Game::m_playerLevel;

std::unordered_map<uint32_t, uint64_t> Game::m_cooldownGroups;
std::unordered_map<uint32_t, uint64_t> Game::m_cooldownSpells;

std::map<std::pair<int, int>, std::vector<CachedCreature>> Game::m_creatureMap;
std::map<Vocation, std::vector<CachedCreature>> Game::m_alliesOnScreen;
std::map<Vocation, std::vector<CachedCreature>> Game::m_partyMembersOnScreen;
std::map<Vocation, std::vector<CachedCreature>> Game::m_guildMemebersOnScreen;
std::map<Vocation, std::vector<CachedCreature>> Game::m_enemiesOnScreen;
std::vector<CachedCreature> Game::m_creaturesOnScreen;
CachedCreature Game::m_friendToHeal;
CachedCreature Game::m_partyKnight;
CachedCreature Game::m_closestCreature;
CachedCreature Game::m_targetedCreature;


int Game::m_creaturesKnightAreaSmall;
int Game::m_creaturesKnightAreaDefault;
int Game::m_creaturesKnightAreaUltimate;
int Game::m_creaturesPlayerAreaSmall;
int Game::m_creaturesPlayerAreaDefault;
int Game::m_creaturesPlayerAreaUltimate;

bool Game::m_lastTargetOnScreen;
bool Game::m_lastTargetIsRunning;

bool Game::m_hasTarget;
int Game::m_comboCount;
int Game::m_alliesAround;
int Game::m_enemiesAround;
int Game::m_playersAround;
int Game::m_creaturesAround;

bool Game::m_canUseHealItem;
std::unordered_map<DelayType, uint64_t> Game::m_castDelays;

std::vector<CachedHotkey> Game::m_hotkeys;

uint32_t Game::m_lastSeenChatMessage = 0;
std::vector<std::pair<std::string, std::string>> Game::m_newChatMessages;

// Inventory
uint32_t Game::m_amuletId = 0;
uint32_t Game::m_ringId = 0;

void Game::Update()
{
    //std::chrono::time_point<std::chrono::system_clock> dateTimeStart = std::chrono::system_clock::now();
    m_dataPointer = Client::getDataPointer();

    // Player Data;
    Player* playerData = Client::getPlayer(m_dataPointer);
    m_playerHp = playerData->getHealth();
    m_playerHpMax = playerData->getHealthMax();
    m_playerHpPercent = std::ceil((double)((double)m_playerHp / (double)m_playerHpMax) * 100.0);

    // Mana
    m_playerMp = playerData->getMana();
    m_playerMpMax = playerData->getManaMax();
    m_playerMpPercent = std::ceil((double)((double)m_playerMp / (double)m_playerMpMax) * 100.0);

    // Mana Shield
    m_playerManaShield = playerData->getUtamo();
    m_playerManaShieldMax = playerData->getUtamoMax();
    m_playerManaShieldPercent = std::max(0.0, (double)((double)m_playerManaShield / (double)m_playerManaShieldMax) * 100.0);

    m_playerLevel = playerData->getLevel();

    m_playerCreature = Client::getPlayerCreature(m_dataPointer);

    m_playerPosition = m_playerCreature->getPosition();
    m_playerDirection = m_playerCreature->getDirection();
    m_playerVocation = m_playerCreature->getVocation();
    m_playerSpeed = m_playerCreature->getSpeed();

    // Game Data
    m_gamePing = Client::getPing(m_dataPointer);
    m_gameTime = m_playerCreature->getGameTime() + m_gamePing;

    delete m_playerCreature;

    // Update Groups Cooldown
    for (Cooldown* cd : Client::getCooldownGroups(m_dataPointer))
    {
        m_cooldownGroups[cd->id()] = cd->endTime();
        delete cd;
    }

    // Update Spells Cooldown
    for (Cooldown* cd : Client::getCooldowns(m_dataPointer))
    {
        m_cooldownSpells[cd->id()] = cd->endTime();
        delete cd;
    }

    // Update Chat Messages

    // Update Battlelist Data
    m_targetId = Battlelist::getTargetId(m_dataPointer);
    m_hasTarget = m_targetId != 0;
    std::map<std::pair<int, int>, std::vector<CachedCreature>> _creatureMap;
    std::map<Vocation, std::vector<CachedCreature>> _alliesOnScreen;
    std::map<Vocation, std::vector<CachedCreature>> _enemiesOnScreen;
    std::vector<CachedCreature> _creaturesOnScreen;

    bool _lastTargetOnScreen = false;
    bool _lastTargetIsRunning = false;

    int _comboCount = 0;
    int _alliesAround = 0;
    int _enemiesAround = 0;
    int _playersAround = 0;
    int _creaturesAround = 0;

    int _creaturesKnightAreaSmall = 0;
    int _creaturesKnightAreaDefault = 0;
    int _creaturesKnightAreaUltimate = 0;
    int _creaturesPlayerAreaSmall = 0;
    int _creaturesPlayerAreaDefault = 0;
    int _creaturesPlayerAreaUltimate = 0;

    CachedCreature _friendToHeal;
    _friendToHeal.Health = 101;

    CachedCreature _closestCreature;
    CachedCreature _targetedCreature;

    for (auto creatureEntry : Battlelist::getCreaturesOnScreen(m_dataPointer))
    {
        Creature* c = creatureEntry.second;
        CreatureType type = c->getType();
        if ((int)type > 1)
        {
            delete c;
            continue;
        }

        CachedCreature _c;
        _c.Position = c->getPosition();
        _c.Type = type;
        _c.Id = c->getId();

        if (type == CreatureType::Player)
        {
            if (_c.Position.Z() != m_playerPosition.Z() || !c->isNear())
                continue;

            GuildEmblem guildEmblem = c->getGuild();
            PartyShield partyShield = c->getPartyShield();
            Vocation vocation = c->getVocation();

            _playersAround++;
            bool isGuildAlly = guildEmblem == GuildEmblem::Green || guildEmblem == GuildEmblem::Member;
            bool isPartyAlly = (int)partyShield >= 3 && (int)partyShield <= 10;

            _c.isGuildAlly = isGuildAlly;
            _c.isPartyAlly = isPartyAlly;

            // SÓ FAZER ISSO SE SIO=ON, HEALER=ON E TIVER CD DE HEAL
            if (Globals::getScriptConfig()->getHealerStatus() && !isGroupOnCooldown(CooldownGroup::Heal) && Globals::getScriptConfig()->getHealFriendGeneralStatus())
            {
                if ((isGuildAlly && Globals::getScriptConfig()->getHealFriendGuild()) ||
                    (isPartyAlly && Globals::getScriptConfig()->getHealFriendParty()))
                {
                    if (Globals::getScriptConfig()->getHealFriendStatus(vocation))
                    {
                        _c.Health = c->getHpPc();
                        if (_c.Health < _friendToHeal.Health && _c.Health <= Globals::getScriptConfig()->getHealFriendHealth(vocation))
                        {
                            if (m_playerVocation == Vocation::Druid)
                                _c.Name = c->getName();

                            _friendToHeal = _c;
                        }
                    }
                }
            }

            if (Globals::getScriptConfig()->getPartyHuntStatus() && isPartyAlly && vocation == Vocation::Knight)
            {
                m_partyKnight = _c;
            }
            if (Globals::getScriptConfig()->getPvPToolslsStatus() && (!isGuildAlly && !isPartyAlly) && c->lastBlackSquareTick() - m_gameTime < 10000)
            {
                _c.isAttackingMe = true;
                _comboCount++;
            }


            // Get if Last Targeted Player is On Screen
            if (_c.Id == m_targetId)
            {
                _targetedCreature = _c;
                m_lastTargetId = _c.Id;
                _targetedCreature.Speed = c->getSpeed();
            }

            if (_c.Id == m_lastTargetId)
            {
                if (m_gameTime - c->getLastWalkTime() < 2000)
                    _lastTargetIsRunning = true;

                _lastTargetOnScreen = true;
            }


        }
        else if (type == CreatureType::Monster && Globals::getScriptConfig()->getPartyHuntStatus())
        {
            int distToPlayer = -1;

            if (Globals::getScriptConfig()->getPartyHuntAutoTargetStatus())
            {
                distToPlayer = _c.Position.getDistance(m_playerPosition);

                _c.distToPlayer = distToPlayer;
                if (distToPlayer < _closestCreature.distToPlayer)
                    _closestCreature = _c;

                if (_c.Id == m_targetId)
                    _targetedCreature = _c;
            }

            // SÓ SE SINGLE TARGET ESTIVER ATIVO
            _c.Health = c->getHpPc();
            if (!_creaturesOnScreen.empty() && _c.Health < _creaturesOnScreen.front().Health)
                _creaturesOnScreen.insert(_creaturesOnScreen.begin(), _c);
            else
                _creaturesOnScreen.push_back(_c);

            // SÓ É ÚTIL PRA CALCULAR ÁREA DE MAGIA
            if (!isGroupOnCooldown(CooldownGroup::Attack))
            {

                // SÓ SE TIVER USANDO WAVE / EXORI MOE
                if (m_partyKnight.Id != 0)
                {
                    int distToKnight = _c.Position.getDistance(m_partyKnight.Position);
                    if (distToKnight <= 1)
                    {
                        _creaturesKnightAreaSmall++;
                        _creaturesKnightAreaDefault++;
                        if (_c.Health <= Globals::getScriptConfig()->getPartyHuntUltimateHealth())
                            _creaturesKnightAreaUltimate++;
                    }
                    else if (distToKnight <= 2)
                    {
                        _creaturesKnightAreaDefault++;
                        if (_c.Health <= Globals::getScriptConfig()->getPartyHuntUltimateHealth())
                            _creaturesKnightAreaUltimate++;
                    }
                    else if (distToKnight <= 4)
                    {
                        if (_c.Health <= Globals::getScriptConfig()->getPartyHuntUltimateHealth())
                            _creaturesKnightAreaUltimate++;
                    }
                }

                // SÓ SE TIVER USANDO UE/AREA SPELL
                if (distToPlayer == -1)
                    distToPlayer = _c.Position.getDistance(m_playerPosition);

                if (distToPlayer <= 1)
                {
                    _creaturesPlayerAreaSmall++;
                    _creaturesPlayerAreaDefault++;
                    if (_c.Health <= Globals::getScriptConfig()->getPartyHuntUltimateHealth())
                        _creaturesPlayerAreaUltimate++;
                }
                else if (distToPlayer <= 2)
                {
                    _creaturesPlayerAreaDefault++;
                    if (_c.Health <= Globals::getScriptConfig()->getPartyHuntUltimateHealth())
                        _creaturesPlayerAreaUltimate++;
                }
                else if (distToPlayer <= 4)
                {
                    if (_c.Health <= Globals::getScriptConfig()->getPartyHuntUltimateHealth())
                        _creaturesPlayerAreaUltimate++;
                }
            }



            _creatureMap[std::make_pair(_c.Position.X() - m_playerPosition.X(), _c.Position.Y() - m_playerPosition.Y())].push_back(_c);
            _creaturesAround++;
        }

        delete c;
    }

    m_friendToHeal = _friendToHeal;
    m_closestCreature = _closestCreature;

    m_lastTargetOnScreen = _lastTargetOnScreen;
    m_lastTargetIsRunning = _lastTargetIsRunning;

    m_creaturesKnightAreaSmall = _creaturesKnightAreaSmall;
    m_creaturesKnightAreaDefault = _creaturesKnightAreaDefault;
    m_creaturesKnightAreaUltimate= _creaturesKnightAreaUltimate;
    m_creaturesPlayerAreaSmall=_creaturesPlayerAreaSmall;
    m_creaturesPlayerAreaDefault=_creaturesPlayerAreaDefault;
    m_creaturesPlayerAreaUltimate=_creaturesPlayerAreaUltimate;

    m_comboCount = _comboCount;
    m_alliesAround = _alliesAround;
    m_enemiesAround = _enemiesAround;
    m_playersAround = _playersAround;
    m_creaturesAround = _creaturesAround;

    m_creaturesOnScreen = _creaturesOnScreen;
    m_targetedCreature = _targetedCreature;
    m_creatureMap = _creatureMap;
    m_enemiesOnScreen = _enemiesOnScreen;
    m_alliesOnScreen = _alliesOnScreen;

    m_canUseHealItem = (!Globals::getScriptConfig()->getRespectAttackTurns() || m_cooldownGroups[(int)CooldownGroup::Attack] > 0 || (Globals::getScriptConfig()->getPartyHuntStatus() && m_creaturesAround < 1));

    // Chat Data
    if (Globals::getScriptConfig()->getPvPToolslsStatus() && Globals::getScriptConfig()->getPvPChatNaviStatus())
    {
        std::map<uint32_t, ChatMessage*> defaultChannelMessages = Objects::Chat::getDefaultChannel(m_dataPointer);
        uint32_t newLastSeenMessage = m_lastSeenChatMessage;
        m_newChatMessages.clear();
        bool firstUpdate = m_lastSeenChatMessage == 0;

        for (auto msg : defaultChannelMessages)
        {
            if (msg.first > m_lastSeenChatMessage)
            {
                newLastSeenMessage = msg.first;
                if (!firstUpdate)
                    m_newChatMessages.push_back({msg.second->getSender(), msg.second->getContent()});
            }
            delete msg.second;
        }
        m_lastSeenChatMessage = newLastSeenMessage;
    }

    // Equipment Data
    if (Globals::getScriptConfig()->getToolsStatus() && Globals::getScriptConfig()->getToolsReadInventory())
    {
        std::map<InventorySlot, InventoryItem*> inventoryItems = Client::getInventoryItems();

        for (std::pair<InventorySlot, InventoryItem*> item : inventoryItems)
        {
            if (item.first == InventorySlot::InventorySlotNecklace)
                m_amuletId = item.second->getId();
            if (item.first == InventorySlot::InventorySlotRing)
                m_ringId = item.second->getId();

            delete item.second;
        }
    }


    // Pathfinding Data

    /* End
     *
    std::chrono::time_point<std::chrono::system_clock> dateTimeEnd = std::chrono::system_clock::now();
    std::chrono::milliseconds elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(dateTimeEnd - dateTimeStart);
    std::cout << "[" << m_gameTime << "]" << " Update End. Time elapsed: " << elapsedMs.count() << "ms. Ping: " << m_gamePing << std::endl;
*/
}

CachedHotkey Game::getHotkey(std::string text)
{
    for (CachedHotkey h : m_hotkeys)
    {
        if (h.text == text)
            return h;
    }

    return CachedHotkey();
}

CachedHotkey Game::getHotkey(int itemId, ItemUseType itemUseType)
{
    for (CachedHotkey h : m_hotkeys)
    {
        if (h.itemId == itemId && h.useType == itemUseType)
            return h;
    }

    return CachedHotkey();
}

CachedHotkey Game::getHotkey(int itemId)
{
    for (CachedHotkey h : m_hotkeys)
    {
        if (h.itemId == itemId)
            return h;
    }

    return CachedHotkey();
}
