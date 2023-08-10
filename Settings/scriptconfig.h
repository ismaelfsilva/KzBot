
#ifndef SCRIPTCONFIG_H
#define SCRIPTCONFIG_H

#include "actionrule.h"
#include "comborule.h"
#include <QXmlStreamWriter>
#include <string>
#include <vector>

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


    std::map<DelayType, uint64_t> TypeDelay = {
        {DelayType::EquipAmulet, 500},
        {DelayType::EquipRing, 500},
        {DelayType::DefaultAmulet, 500},
        {DelayType::DefaultRing, 500},
        {DelayType::Heal, 0},
        {DelayType::Item, 500},
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

    std::vector<ComboRule*> ComboRules;


    void setPartyHuntStatus(bool value) { m_partyHuntStatus = value; };
    bool getPartyHuntStatus() { return m_partyHuntStatus; };
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




    bool m_pvpToolsStatus = false;
    bool m_pvpHoldTarget = false;
    bool m_pvpParalyzeTarget = false;
    bool m_pvpDashTarget = false;
    bool m_pvpChatNaviStatus = true;

    bool m_partyHuntStatus = false;
    bool m_partyHuntUseFakeTarget = true;
    bool m_partyHuntAreaRune = false;
    bool m_partyHuntAutoTargetStatus = false;
    int m_partyHuntUltimateHealth = 30;

    bool m_partyHuntUseEKCombo = false;
};

#endif // SCRIPTCONFIG_H
