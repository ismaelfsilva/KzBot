#include "client.h"

using namespace Addresses;

uint32_t Client::m_baseAddress;
uint32_t Client::m_dataPointer;

uint32_t Client::m_cooldownsPointer;
uint32_t Client::m_playerPointer;
uint32_t Client::m_playerCreaturePointer;

uint32_t Client::m_cooldownsSpellsCollection;
uint32_t Client::m_cooldownsSpellsCount;
uint32_t Client::m_cooldownsGroupCollection;

std::vector<uint32_t> Client::m_uiCurrentText;
std::vector<uint32_t> Client::m_uiChatStatus;

std::vector<uint32_t> Client::m_clientFocus;


std::vector<uint32_t> Client::m_ping;

// Inventory
uint32_t Client::m_inventoryPointer;
std::vector<uint32_t> Client::m_inventoryPathToItem;
uint32_t Client::m_inventoryItemSlot;
uint32_t Client::m_inventoryItemIsEquipped;
uint32_t Client::m_inventoryItemId;
uint32_t Client::m_inventoryItemCount;

//Goto
uint32_t Client::m_gotoData;
uint32_t Client::m_gotoIsWalking;
uint32_t Client::m_gotoX;
uint32_t Client::m_gotoY;
uint32_t Client::m_gotoZ;

// Hotkeys
std::vector<uint32_t> Client::m_hotkeyKeyBindingCollection;
std::vector<uint32_t> Client::m_currentHotkeyPresetName;
std::vector<uint32_t> Client::m_hotkeyPresetCollection;
uint32_t Client::m_hotkeyCollectionName;
uint32_t Client::m_hotkeyCollection;
uint32_t Client::m_hotkeyActionBarCollection;
