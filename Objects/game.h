#ifndef GAME_H
#define GAME_H

#include "../Settings/globals.h"
#include "../Util/Enums.h"
#include "hotkey.h"
#include "position.h"
#include "creature.h"
#include "chatmessage.h"

using namespace Objects;

namespace Objects
{


class CachedCreature
{
public:
    CreatureType Type;
    Position Position;
    std::string Name;
    int Id = 0;
    int Health;
    int Speed = 0;
    int distToPlayer = 99;
    bool isGuildAlly;
    bool isPartyAlly;
    bool isAttackingMe;
};

class CachedHotkey
{
public:
    uint32_t key = 0;
    std::string name = "";
    bool extended = false;

    int itemId = 0;
    ItemUseType useType = (ItemUseType)0;

    std::string text = "";
};

class Game
{
public:
    static void Update();
    static int getDataPointer() { return m_dataPointer; }

    static bool isSpellOnCooldown(Spell* spell) {
        return (spell->id != 0 && (m_cooldownGroups[(int)spell->group] > 0 || m_cooldownSpells[spell->id] > m_gameTime));
    };

    static uint64_t getSpellLastCooldownEnd(Spell* spell) {
        if (spell->id == 0)
            return 0;

        return m_cooldownSpells[spell->id];
    };

    static void setSpellLastCooldownEnd(Spell* spell, uint32_t value) {
        if (spell->id == 0)
            return;

        m_cooldownSpells[spell->id] = value;
    };
    static bool isGroupOnCooldown(CooldownGroup group) { return m_cooldownGroups[(int)group] > 0; };

    static int getPlayersAround() { return m_playersAround; };
    static bool canUseHealItem() { return m_canUseHealItem; };
    static bool canCast(DelayType delayType) { return m_castDelays[delayType] < m_gameTime; };
    static bool increaseDelay(DelayType delayType) {
        if (delayType == DelayType::None)
            return false;
        return m_castDelays[delayType] = m_gameTime + Globals::getScriptConfig()->TypeDelay[delayType];
    };

    static uint32_t getTargetId() { return m_targetId; };
    static void setLastTargetId(uint32_t id) { m_lastTargetId = id; };
    static uint32_t getLastTargetId() { return m_lastTargetId; };
    static bool isLastTargetOnScreen() { return m_lastTargetOnScreen; };
    static bool isLastTargetRunning() { return m_lastTargetIsRunning; };

    static void setHotkeys(std::vector<CachedHotkey> hotkeys) { m_hotkeys = hotkeys; };
    static CachedHotkey getHotkey(std::string text);
    static CachedHotkey getHotkey(int itemId, ItemUseType itemUseType);
    static CachedHotkey getHotkey(int itemId);

    static uint64_t getGameTime() { return m_gameTime; };
    static CachedCreature getFriendToHeal() { return m_friendToHeal; };
    static CachedCreature getPartyKnight() { return m_partyKnight; };
    static CachedCreature getClosestCreature() { return m_closestCreature; };
    static CachedCreature getTargetedCreature() { return m_targetedCreature; };
    static std::map<std::pair<int, int>, std::vector<CachedCreature>> getCreatureMap() { return m_creatureMap; };
    static std::vector<CachedCreature> getCreaturesOnScreen() { return m_creaturesOnScreen; };

    static inline int getCreaturesKnightAreaSmall() { return m_creaturesKnightAreaSmall; }
    static inline int getCreaturesKnightAreaDefault() { return m_creaturesKnightAreaDefault; }
    static inline int getCreaturesKnightAreaUltimate() { return m_creaturesKnightAreaUltimate; }
    static inline int getCreaturesPlayerAreaSmall() { return m_creaturesPlayerAreaSmall; }
    static inline int getCreaturesPlayerAreaDefault() { return m_creaturesPlayerAreaDefault; }
    static inline int getCreaturesPlayerAreaUltimate() { return m_creaturesPlayerAreaUltimate; }

    static inline int getCreaturesAroundCount() { return m_creaturesAround; }

    static inline Position getPlayerPosition() { return m_playerPosition; }
    static inline Vocation getPlayerVocation() { return m_playerVocation; }
    static inline int getPlayerSpeed() { return m_playerSpeed; }
    static inline Direction getPlayerDirection() { return m_playerDirection; }

    static int getPlayerHp() { return m_playerHp; }
    static int getPlayerHpMax() { return m_playerHpMax; }
    static int getPlayerHpPercent() { return m_playerHpPercent; }

    static int getPlayerMp() { return m_playerMp; }
    static int getPlayerMpMax() { return m_playerMpMax; }
    static int getPlayerMpPercent() { return m_playerMpPercent; }

    static int getPlayerManaShield() { return m_playerManaShield; }
    static int getPlayerManaShieldMax() { return m_playerManaShieldMax; }
    static int getPlayerManaShieldPercent() { return m_playerManaShieldPercent; }

    static int getPlayerLevel() { return m_playerLevel; }

    static int getAmuletId() { return m_amuletId; };
    static int getRingId() { return m_ringId; };


    // Chat Data
    static std::vector<std::pair<std::string, std::string>> getNewChatMessages() { return m_newChatMessages; };

private:
    static uint32_t m_dataPointer;

    static Creature* m_playerCreature;
    static Position m_playerPosition;
    static Direction m_playerDirection;
    static Vocation m_playerVocation;
    static int m_playerSpeed;

    // Health
    static int m_playerHp;
    static int m_playerHpMax;
    static int m_playerHpPercent;

    // Mana
    static int m_playerMp;
    static int m_playerMpMax;
    static int m_playerMpPercent;

    // Mana Shield
    static int m_playerManaShield;
    static int m_playerManaShieldMax;
    static int m_playerManaShieldPercent;

    static int m_playerLevel;

    static uint32_t m_targetId;
    static uint32_t m_lastTargetId;

    static uint64_t m_gameTime;
    static int m_gamePing;

    static std::unordered_map<uint32_t, uint64_t> m_cooldownGroups;
    static std::unordered_map<uint32_t, uint64_t> m_cooldownSpells;

    static std::map<std::pair<int, int>, std::vector<CachedCreature>> m_creatureMap;
    static std::map<Vocation, std::vector<CachedCreature>> m_alliesOnScreen;
    static std::map<Vocation, std::vector<CachedCreature>> m_partyMembersOnScreen;
    static std::map<Vocation, std::vector<CachedCreature>> m_guildMemebersOnScreen;
    static std::map<Vocation, std::vector<CachedCreature>> m_enemiesOnScreen;
    static std::vector<CachedCreature> m_creaturesOnScreen;
    static CachedCreature m_friendToHeal;
    static CachedCreature m_partyKnight;
    static CachedCreature m_closestCreature;
    static CachedCreature m_targetedCreature;

    static bool m_lastTargetOnScreen;
    static bool m_lastTargetIsRunning;
    static bool m_hasTarget;
    static int m_comboCount;
    static int m_alliesAround;
    static int m_enemiesAround;
    static int m_playersAround;
    static int m_creaturesAround;

    static int m_creaturesKnightAreaSmall;
    static int m_creaturesKnightAreaDefault;
    static int m_creaturesKnightAreaUltimate;
    static int m_creaturesPlayerAreaSmall;
    static int m_creaturesPlayerAreaDefault;
    static int m_creaturesPlayerAreaUltimate;

    static bool m_canUseHealItem;
    static std::unordered_map<DelayType, uint64_t> m_castDelays;

    static std::vector<CachedHotkey> m_hotkeys;

    // Chat Area
    static uint32_t m_lastSeenChatMessage;
    static std::vector<std::pair<std::string, std::string>> m_newChatMessages;

    // Inventory Area
    static uint32_t m_amuletId;
    static uint32_t m_ringId;
};
};
#endif // GAME_H
