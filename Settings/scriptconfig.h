
#ifndef SCRIPTCONFIG_H
#define SCRIPTCONFIG_H

#include "actionrule.h"
#include "comborule.h"
#include <QXmlStreamWriter>
#include <string>
#include <vector>
#include "../Objects/position.h"
#include <windows.h>

class ScriptConfig
{
public:
    ScriptConfig();

    void setGeneralStatus(bool value) { m_generalStatus = value; };
    bool getGeneralStatus() { return m_generalStatus; };

    void setHealerStatus(bool value) { m_healerStatus = value; };
    bool getHealerStatus() { return m_healerStatus; };
    void setRespectAttackTurns(bool value) { m_respectAttackTurns = value; };
    bool getRespectAttackTurns() { return m_respectAttackTurns; };
    void setHealerDelay(int value) { m_healerDelay = value; };
    void setHealerWait(int value) { m_healerWait = value; };
    int getHealerDelay() { return m_healerDelay; };
    int getHealerWait() { return m_healerWait; };

    void setHealFriendLockKeyboard(bool value) { m_healFriendLockKeyboard = value; };
    bool getHealFriendLockKeyboard() { return m_healFriendLockKeyboard; };
    void setHealFriendParty(bool value) { m_healFriendParty = value; };
    bool getHealFriendParty() { return m_healFriendParty; };
    void setHealFriendGuild(bool value) { m_healFriendGuild = value; };
    bool getHealFriendGuild() { return m_healFriendGuild; };
    void setHealFriendList(bool value) { m_healFriendList = value; };
    bool getHealFriendList() { return m_healFriendList; };
    void setHealFriendGranSioStatus(bool value) { m_healFriendGranSioStatus = value; };
    bool getHealFriendGranSioStatus() { return m_healFriendGranSioStatus; };
    void setHealFriendGranSioHp(int value) { m_healFriendGranSioHp = value; };
    int getHealFriendGranSioHp() { return m_healFriendGranSioHp; };

    uint32_t minAntiSpamDelay = 100;
    std::map<DelayType, uint64_t> TypeDelay = {
        {DelayType::EquipAmulet, 500},
        {DelayType::EquipRing, 500},
        {DelayType::DefaultAmulet, 500},
        {DelayType::DefaultRing, 500},
        {DelayType::Heal, 0},
        {DelayType::Item, 500},
        {DelayType::Food, 500},
        {DelayType::NpcFood, 600000},
        {DelayType::CupcakeHp, 600000},
        {DelayType::CupcakeMp, 600000},
        {DelayType::Utamo, 500},
        {DelayType::AttackSpell, 500},
    };


    void setPvPToolsStatus(bool value) { m_pvpToolsStatus = value; };
    bool getPvPToolslsStatus() { return m_pvpToolsStatus; };

    void setPvPHoldTarget(bool value) { m_pvpHoldTarget = value; };
    bool getPvPHoldTarget() { return m_pvpHoldTarget; };

    void setPvPParalyzeTarget(bool value) { m_pvpParalyzeTarget = value; };
    bool getPvPParalyzeTarget() { return m_pvpParalyzeTarget; };

    void setPvPDashTarget(bool value) { m_pvpDashTarget = value; };
    bool getPvPDashTarget() { return m_pvpDashTarget; };

    void setPvPChatNaviStatus(bool value) { m_pvpChatNaviStatus = value; };
    bool getPvPChatNaviStatus() { return m_pvpChatNaviStatus; };

    bool m_pvpSingleTargetComboStatus;
    std::vector<ComboRule*> m_pvpSingleTargetComboRules;


    std::vector<ComboRule*> ComboRules;

    uint32_t getUECountToConsiderCombo() { return m_UEsToConsiderCombo; };
    void setPvPOnComboUE(bool value) { m_pvpOnComboUE = value; };
    bool getPvPOnComboUE() { return m_pvpOnComboUE; };
    ComboRule* m_pvpOnComboUEActionA = nullptr;
    ComboRule* m_pvpOnComboUEActionB = nullptr;

    uint32_t getAvatarCountToConsiderCombo() { return m_AvatarCountToConsiderCombo; };
    void setPvPOnComboAvatar(bool value) { m_pvpOnComboAvatar = value; };
    bool getPvPOnComboAvatar() { return m_pvpOnComboAvatar; };
    ComboRule* m_pvpOnComboAvatarActionA = nullptr;
    ComboRule* m_pvpOnComboAvatarActionB = nullptr;



    void setPartyHuntStatus(bool value) { m_partyHuntStatus = value; };
    bool getPartyHuntStatus() { return m_partyHuntStatus; };

    void setPartyHuntUseTargetNext(bool value) { m_partyHuntUseTargetNext = value; };
    bool getPartyHuntUseTargetNext() { return m_partyHuntUseTargetNext; };
    void setPartyHuntTargetNextKey(uint32_t value) { m_partyHuntTargetNextKey = value; };
    uint32_t getPartyHuntTargetNextKey() { return m_partyHuntTargetNextKey; };
    void setPartyHuntTargetNextKeyExtended(bool value) { m_partyHuntTargetNextKeyExtended = value; };
    bool getPartyHuntTargetNextKeyExtended() { return m_partyHuntTargetNextKeyExtended; };


    void setPartyHuntAreaRune(bool value) { m_partyHuntAreaRune = value; };
    bool getPartyHuntAreaRune() { return m_partyHuntAreaRune; };
    void setPartyHuntUseFakeTarget(bool value) { m_partyHuntUseFakeTarget = value; };
    bool getPartyHuntUseFakeTarget() { return m_partyHuntUseFakeTarget; };
    void setPartyHuntAutoTargetStatus(bool value) { m_partyHuntAutoTargetStatus = value; };
    bool getPartyHuntAutoTargetStatus() { return m_partyHuntAutoTargetStatus; };

    void setPartyHuntUseEKCombo(bool value) { m_partyHuntUseEKCombo = value; };
    bool getPartyHuntUseEKCombo() { return m_partyHuntUseEKCombo; };

    int getPartyHuntUltimateHealth() { return m_partyHuntUltimateHealth; };
    void setPartyHuntUltimateHealth(int value) { m_partyHuntUltimateHealth = value; };

    void Serialize(QXmlStreamWriter& writer);
    void Deserialize(QXmlStreamReader& reader);
    void UpdateHotkeys(std::string& errorString);

    int getHealFriendHealth(Vocation voc) { return m_healFriendHealth[voc]; };
    void setHealFriendHealth(Vocation voc, int health) { m_healFriendHealth[voc] = health; };
    int getHealFriendStatus(Vocation voc) { return m_healFriendStatus[voc]; };
    void setHealFriendStatus(Vocation voc, bool value) { m_healFriendStatus[voc] = value; };

    bool getHealFriendGeneralStatus() { return m_healFriendGeneralStatus; };
    void setHealFriendGeneralStatus(bool value) { m_healFriendGeneralStatus = value; };

    std::vector<ActionRule*> HealRules;
    void addHealRule(ActionRule *healRule);
    ActionRule *addHealRule(std::string name, ActionType type, Spell* spell = nullptr);
    ActionRule *addHealRule(std::string name, ActionType type, std::string spellId);
    ActionRule *getHealRule(std::string name);




    void setToolsStatus(bool value) { m_toolsStatus = value; };
    bool getToolsStatus() { return m_toolsStatus; };

    void setToolsReadInventory(bool value) { m_toolsReadInventory = value; };
    bool getToolsReadInventory() { return m_toolsReadInventory; };

    bool getToolsAntiIdle() const { return m_toolsAntiIdle; }
    bool getToolsEatFood() const { return m_toolsEatFood; }
    int getToolsEatFoodId() const { return m_toolsEatFoodId; }
    bool getToolsHoldPosition() const { return m_toolsHoldPosition; }
    Position getToolsHoldPositionPos() { return m_toolsHoldPositionPos; }
    bool getToolsChangeGold() const { return m_toolsChangeGold; }
    bool getToolsAutoBuff() const { return m_toolsAutoBuff; }
    int getToolsAutoBuffItemId() const { return m_toolsBuffItemId; }

    void setToolsAntiIdle(bool value) { m_toolsAntiIdle = value; }
    void setToolsEatFood(bool value) { m_toolsEatFood = value; }
    void setToolsEatFoodId(int value) { m_toolsEatFoodId = value; }
    void setToolsHoldPosition(bool value) { m_toolsHoldPosition = value; }
    void setToolsHoldPositionPos(Position value) { m_toolsHoldPositionPos = value; }
    void setToolsChangeGold(bool value) { m_toolsChangeGold = value; }
    void setToolsAutoBuff(bool value) { m_toolsAutoBuff = value; }
    void setToolsAutoBuffItemId(int value) { m_toolsBuffItemId = value; }



    std::vector<ActionRule*> ToolsRules;
    void addToolsRule(ActionRule *toolRule);
    ActionRule *addToolsRule(std::string name, ActionType type, Spell* spell = nullptr);
    ActionRule *addToolsRule(std::string name, ActionType type, std::string spellId);
    ActionRule *getToolsRule(std::string name);


    std::vector<ActionRule*> KnightTargetRules;
    void addKnightTargetRule(ActionRule *targetRule);
    ActionRule *addKnightTargetRule(std::string name, ActionType type, Spell* spell = nullptr);
    ActionRule *addKnightTargetRule(std::string name, ActionType type, std::string spellId);
    ActionRule *getKnightTargetRule(std::string name);


    std::vector<ActionRule*> TargetRules;
    void addTargetRule(ActionRule *targetRule);
    ActionRule *addTargetRule(std::string name, ActionType type, Spell* spell = nullptr);
    ActionRule *addTargetRule(std::string name, ActionType type, std::string spellId);
    ActionRule *getTargetRule(std::string name);


    POINT clearTileDestPoint;
    POINT flowerSourcePoint;
private:
    bool m_generalStatus = false;

    bool m_healerStatus = false;
    bool m_respectAttackTurns = true;
    int m_healerDelay = 100;
    int m_healerWait = 100;

    bool m_healFriendLockKeyboard = true;
    bool m_healFriendParty = false;
    bool m_healFriendGuild = false;
    bool m_healFriendList = false;


    bool m_healFriendGranSioStatus = false;
    int m_healFriendGranSioHp = false;


    std::map<Vocation, int> m_healFriendHealth;
    std::map<Vocation, int> m_healFriendStatus;
    bool m_healFriendGeneralStatus;


    bool m_toolsStatus = false;
    bool m_toolsReadInventory = false;
    bool m_toolsReadItems = false;

    bool m_toolsAntiIdle = false;
    bool m_toolsEatFood = false;
    int m_toolsEatFoodId = 0;
    bool m_toolsHoldPosition = false;
    Position m_toolsHoldPositionPos = Position(0, 0, 0);
    bool m_toolsChangeGold = false;
    bool m_toolsAutoBuff = false;
    int m_toolsBuffItemId = 0;




    int m_UEsToConsiderCombo = 3;
    int m_AvatarCountToConsiderCombo = 3;

    bool m_pvpToolsStatus = false;
    bool m_pvpHoldTarget = false;
    bool m_pvpParalyzeTarget = false;
    bool m_pvpDashTarget = false;

    bool m_pvpOnComboUE = false;
    bool m_pvpOnComboAvatar = false;

    bool m_pvpChatNaviStatus = true;

    bool m_partyHuntStatus = false;
    bool m_partyHuntUseTargetNext = false;
    uint32_t m_partyHuntTargetNextKey = 0x0;
    bool m_partyHuntTargetNextKeyExtended = false;
    bool m_partyHuntUseFakeTarget = true;
    bool m_partyHuntAreaRune = false;
    bool m_partyHuntAutoTargetStatus = false;
    int m_partyHuntUltimateHealth = 30;

    bool m_partyHuntUseEKCombo = false;
};

#endif // SCRIPTCONFIG_H
