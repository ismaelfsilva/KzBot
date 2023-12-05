
#ifndef CLIENT_ADDR_H
#define CLIENT_ADDR_H



#include <cstdint>
#include <vector>
namespace Addresses {

class Client
{
public:
    static void setBaseAddress(uint32_t value) { m_baseAddress = value; }
    static void setDataPointer(uint32_t value) { m_dataPointer = value; }
    static void setLoggedIn(uint32_t value) { m_loggedIn = value; }
    static void setCooldownsPointer(uint32_t value) { m_cooldownsPointer = value; }
    static void setCooldownsGroupCollection(uint32_t value) { m_cooldownsGroupCollection = value; }
    static void setCooldownsSpellsCollection(uint32_t value) { m_cooldownsSpellsCollection = value; }
    static void setCooldownsSpellsCount(uint32_t value) { m_cooldownsSpellsCount = value; }
    static void setPlayerPointer(uint32_t value) { m_playerPointer = value; }
    static void setPlayerCreaturePointer(uint32_t value) { m_playerCreaturePointer = value; }

    static uint32_t getBaseAddress() { return m_baseAddress; }
    static uint32_t getDataPointer() { return m_dataPointer; }
    static uint32_t getLoggedIn() { return m_loggedIn; }

    static uint32_t getCooldownsPointer() { return m_cooldownsPointer; }
    static uint32_t getCooldownsGroupCollection() { return m_cooldownsGroupCollection; }
    static uint32_t getCooldownsSpellsCollection() { return m_cooldownsSpellsCollection; }
    static uint32_t getCooldownsSpellsCount() { return m_cooldownsSpellsCount; }
    static uint32_t getPlayerPointer() { return m_playerPointer; }
    static uint32_t getPlayerCreaturePointer() { return m_playerCreaturePointer; }

    static void setClientFocus(std::vector<uint32_t> value) { m_clientFocus = value; }
    static std::vector<uint32_t> getClientFocus() { return m_clientFocus; }

    //Inventory
    static inline uint32_t getInventoryPointer() { return m_inventoryPointer; }
    static inline void setInventoryPointer(uint32_t value) { m_inventoryPointer = value; }

    static inline std::vector<uint32_t> getInventoryPathToItem() { return m_inventoryPathToItem; }
    static inline void setInventoryPathToItem(std::vector<uint32_t> value) { m_inventoryPathToItem = value; }
    // Getter and Setter for m_inventoryItemSlot
    static inline uint32_t getInventoryItemSlot() { return m_inventoryItemSlot; }
    static inline void setInventoryItemSlot(uint32_t value) { m_inventoryItemSlot = value; }

    static inline uint32_t getInventoryItemIsEquipped() { return m_inventoryItemIsEquipped; }
    static inline void setInventoryItemIsEquipped(uint32_t value) { m_inventoryItemIsEquipped = value; }
    static inline uint32_t getInventoryItemId() { return m_inventoryItemId; }
    static inline void setInventoryItemId(uint32_t value) { m_inventoryItemId = value; }
    static inline uint32_t getInventoryItemCount() { return m_inventoryItemCount; }
    static inline void setInventoryItemCount(uint32_t value) { m_inventoryItemCount = value; }




    //Goto
    static void setGotoData(uint32_t value) { m_gotoData = value; }
    static uint32_t getGotoData() { return m_gotoData; }
    static void setGotoX(uint32_t value) { m_gotoX = value; }
    static uint32_t getGotoX() { return m_gotoX; }
    static void setGotoY(uint32_t value) { m_gotoY = value; }
    static uint32_t getGotoY() { return m_gotoY; }
    static void setGotoZ(uint32_t value) { m_gotoZ = value; }
    static uint32_t getGotoZ() { return m_gotoZ; }
    static void setGotoIsWalking(uint32_t value) { m_gotoIsWalking = value; }
    static uint32_t getGotoIsWalking() { return m_gotoIsWalking; }


    static void setPing(std::vector<uint32_t> value) { m_ping = value; }
    static std::vector<uint32_t> getPing() { return m_ping; }

    // Hotkeys
    static void setKeyBindingCollection(std::vector<uint32_t> value) { m_hotkeyKeyBindingCollection= value;};
    static void setCurrentHotkeyPresetName(std::vector<uint32_t> value) { m_currentHotkeyPresetName= value;};
    static void setHotkeyPresetCollection(std::vector<uint32_t> value) {m_hotkeyPresetCollection = value;};
    static void setHotkeyCollectionName(uint32_t value) {m_hotkeyCollectionName = value;};
    static void setHotkeyActionBarCollection(uint32_t value) {m_hotkeyActionBarCollection = value;};
    static void setHotkeyCollection(uint32_t value) {m_hotkeyCollection = value;};

    static std::vector<uint32_t> getKeyBindingCollection() { return m_hotkeyKeyBindingCollection; };
    static std::vector<uint32_t> getCurrentHotkeyName() { return m_currentHotkeyPresetName; };
    static std::vector<uint32_t> getHotkeyPresetCollection() { return m_hotkeyPresetCollection; };
    static uint32_t getHotkeyCollectionName() { return m_hotkeyCollectionName; };
    static uint32_t getHotkeyActionBarCollection() { return m_hotkeyActionBarCollection; };
    static uint32_t getHotkeyCollection() { return m_hotkeyCollection; };
private:
    static uint32_t m_baseAddress;
    static uint32_t m_loggedIn;
    static uint32_t m_dataPointer;

    static uint32_t m_cooldownsPointer;
    static uint32_t m_playerPointer;
    static uint32_t m_playerCreaturePointer;

    static uint32_t m_cooldownsSpellsCollection;
    static uint32_t m_cooldownsSpellsCount;
    static uint32_t m_cooldownsGroupCollection;

    static std::vector<uint32_t> m_currentHotkeyName;
    static std::vector<uint32_t> m_hotkeyData;

    static std::vector<uint32_t> m_ping;

    // Inventory
    static uint32_t m_inventoryPointer;
    static std::vector<uint32_t> m_inventoryPathToItem;
    static uint32_t m_inventoryItemSlot;
    static uint32_t m_inventoryItemIsEquipped;
    static uint32_t m_inventoryItemId;
    static uint32_t m_inventoryItemCount;

    // Goto
    static uint32_t m_gotoData;
    static uint32_t m_gotoIsWalking;
    static uint32_t m_gotoX;
    static uint32_t m_gotoY;
    static uint32_t m_gotoZ;

    static std::vector<uint32_t> m_uiCurrentText;
    static std::vector<uint32_t> m_uiChatStatus;

    static std::vector<uint32_t> m_clientFocus;

    // Hotkeys
    static std::vector<uint32_t> m_hotkeyKeyBindingCollection;
    static std::vector<uint32_t> m_currentHotkeyPresetName;
    static std::vector<uint32_t> m_hotkeyPresetCollection;
    static uint32_t m_hotkeyCollectionName;
    static uint32_t m_hotkeyCollection;
    static uint32_t m_hotkeyActionBarCollection;
};

}
#endif // CLIENT_ADDR_H
