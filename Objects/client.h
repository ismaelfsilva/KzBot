
#ifndef CLIENT_H
#define CLIENT_H


#include "cooldown.h"
#include "hotkey.h"
#include "inventoryitem.h"
#include "keybinding.h"
#include "player.h"
#include "creature.h"
#include "../Settings/actionsettings.h"




namespace Objects
{


class Client
{
public:
    static uint32_t getDataPointer();
    static Player *getPlayer(uint32_t dataPointer);
    static Creature *getPlayerCreature(uint32_t dataPointer);
    static uint64_t getGameTime(uint32_t dataPointer);
    static int getPing(uint32_t dataPointer);

    static std::vector<Cooldown*> getCooldownGroups(uint32_t dataPointer);
    static Cooldown *getCooldownGroup(uint32_t dataPointer, int cId);
    static Cooldown *getCooldownGroup(uint32_t dataPointer, CooldownGroup group);

    static Point *getEquipmentPoint() { return m_equipmentPoint; };
    static void setEquipmentPoint(Point *point) { m_equipmentPoint = point; };
    static void updateEquipmentPoint();

    static RECT *getGameScreenRect() { return m_gameScreenRect; };
    static void setGameScreenRect(RECT *rect) { m_gameScreenRect = rect; };
    static void updateGameScreenRect();

    static void setGameScreenTileSize(int size) { m_gameScreenTileSize = size; };
    static void setGameScreenHalfTileSize(int size) { m_gameScreenHalfTileSize = size; };
    static void setGameScreenPlayerPoint(Point* point) { m_gameScreenPlayerPoint = point; };
    static Point* getGameScreenPlayerPoint() { return m_gameScreenPlayerPoint; };
    static int getGameScreenTileSize() { return m_gameScreenTileSize; };
    static int getGameScreenHalfTileSize() { return m_gameScreenHalfTileSize; };


    static std::pair<AmuletType, RingType> getEquipmentInfo();
    static bool getEquipmentInfo(std::pair<AmuletType, RingType>& output);

    static std::string getCurrentHotkeySetNameFromFile();
    static void updateHotkeysFromFile();
    static void parseHotkey(QJsonValue& jsonValue, int chatStatus = -1);
    static actionSettings* getHotkeyByText(std::string words);
    static actionSettings* getHotkeyByItemId(int itemId);
    static actionSettings *getHotkeyByItemId(int itemId, std::string useType);
    static std::vector<Cooldown *> getCooldowns(uint32_t dataPointer);
    static Cooldown *getCooldown(uint32_t dataPointer, int cId);
    static void setClientFocus(bool focus);
    static bool getClientFocus();

    static std::map<InventorySlot, InventoryItem*> getInventoryItems();

    static void Target(uint32_t dataPointer, Position p);
    static void Target(uint32_t dataPointer, uint32_t cId);
    static void Target(uint32_t dataPointer, Creature* c);
    static Point* getSqmPoint(uint32_t dataPointer, Position pos);
    static Point* getSqmPoint(uint32_t dataPointer, int x, int y);

    static std::string getCurrentHotkeyName(uint32_t dataPointer);
    static std::vector<Hotkey*> getHotkeys();
    static std::vector<KeyBinding*> getKeyBindings();
    static KeyBinding *getKeyBindingByKey(uint32_t key);
    static void updateHotkeys();


    static void Say(std::string text);
    static void Use(int itemId);
    static void Equip(int itemId);
    static void UseWithCrosshair(int itemId);
    static void UseOnYourself(int itemId);
    static void UseOnTarget(int itemId);

    static void Turn(Direction dir);
    static void Goto(Position p);
private:
    static RECT *m_gameScreenRect;
    static int m_gameScreenTileSize;
    static int m_gameScreenHalfTileSize;
    static Point *m_gameScreenPlayerPoint;
    static Point *m_equipmentPoint;
    static std::vector<actionSettings*> m_hotkeys;

};

}

#endif // CLIENT_H
