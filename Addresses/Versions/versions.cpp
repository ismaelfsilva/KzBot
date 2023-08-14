#include "versions.h"
#include "../player.h"
#include "../cooldown.h"
#include "../creature.h"
#include "../client.h"
#include "../battlelist.h"
#include "../hotkey.h"
#include "../chat.h"
#include "../chatmessage.h"
#include "../../Settings/globals.h"

bool Addresses::Versions::isSupportedVersion(std::string versionString)
{
    if (versionString == "13.10.12892")
        return true;
    else if (versionString == "13.12.13018")
        return true;
    else if (versionString == "13.17.13405")
        return true;
    else if (versionString == "13.20.13560") // Rubini
        return true;
    else if (versionString == "13.20.13623") // Hades
        return true;
    else if (versionString == "13.20.13709") // Arcana
        return true;

    return false;
}

void Addresses::Versions::setVersion(std::string versionString)
{
    if (versionString == "13.10.12892")
        Addresses::Versions::setV131012892(Globals::getBaseAddress());
    else if (versionString == "13.12.13018")
        Addresses::Versions::setV131213018(Globals::getBaseAddress());
    else if (versionString == "13.17.13405")
        Addresses::Versions::setV131713405(Globals::getBaseAddress());
    else if (versionString == "13.20.13560") // Rubini
        Addresses::Versions::setV132013560(Globals::getBaseAddress());
    else if (versionString == "13.20.13623")
        Addresses::Versions::setV132013623(Globals::getBaseAddress());
    else if (versionString == "13.20.13709")
        Addresses::Versions::setV132013709(Globals::getBaseAddress());
}

void Addresses::Versions::setV131012892(uint32_t baseAddress) // 13.10.12892
{
    Addresses::Client::setBaseAddress(baseAddress);

    Addresses::Client::setDataPointer(0x10B6A0C + baseAddress);
    Addresses::Client::setClientFocus({0x010F4E3C + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setPlayerPointer(0x6C);
    Addresses::Client::setPlayerCreaturePointer(0x290);


    Addresses::Client::setGotoData(0x4FC);
    Addresses::Client::setGotoIsWalking(0xA8);
    Addresses::Client::setGotoX(0xB8);
    Addresses::Client::setGotoY(0xBC);
    Addresses::Client::setGotoZ(0xC0);

    Addresses::Client::setCooldownsPointer(0x74);
    Addresses::Client::setCooldownsSpellsCollection(0x10); // SPELLS/RUNES COOLDOWNS
    Addresses::Client::setCooldownsSpellsCount(0x14); // SPELLS/RUNES COOLDOWNS QTY
    Addresses::Client::setCooldownsGroupCollection(0x18);

    Addresses::Client::setUiCurrentText({0x10F4E3C + baseAddress, 0xC, 0x4, 0x7C, 0x28, 0x4, 0x8, 0x4, 0x80, 0xC0});
    Addresses::Client::setUiChatStatus({0x8C, 0x24, 0x8});
    Addresses::Client::setPing({0x4BC, 0x10}); //



    // Inventory
    Addresses::Client::setInventoryPointer(0x10F4D58 + baseAddress);
    Addresses::Client::setInventoryPathToItem({0x4, 0x8, 0x4C, 0x8});
    Addresses::Client::setInventoryItemSlot(0x10);
    Addresses::Client::setInventoryItemIsEquipped(0x18);
    Addresses::Client::setInventoryItemId(0x58);
    Addresses::Client::setInventoryItemCount(0x68);



    Addresses::Client::setKeyBindingCollection({0x8C, 0x40});
    Addresses::Client::setCurrentHotkeyPresetName({0x40, 0xF0}); //
    Addresses::Client::setHotkeyPresetCollection({0x3C, 0xEC}); // testar
    Addresses::Client::setHotkeyCollectionName(0x10); //
    Addresses::Client::setHotkeyActionBarCollection(0x20);
    Addresses::Client::setHotkeyCollection(0x10);


    Addresses::Chat::setChatDataPointer(0xC8);
    Addresses::Chat::setChatTabsPointer(0x8);
    Addresses::Chat::setDefaultChatPointer(0x14);

    Addresses::Chat::setChatMessagesList(0x18);
    Addresses::Chat::setChatMessagesCount(0x24);

    Addresses::ChatMessage::setContent(0x8);
    Addresses::ChatMessage::setSender(0x10);
    Addresses::ChatMessage::setId(0xC);


    Addresses::Hotkey::setId(0x8);
    Addresses::Hotkey::setText(0xC);
    Addresses::Hotkey::setTextSendAutomatically(0x10);
    Addresses::Hotkey::setItemId(0x1C);
    Addresses::Hotkey::setItemUseType(0x18);

    Addresses::Battlelist::setPointer(0x158);
    Addresses::Battlelist::setCreaturesList(0x8);
    Addresses::Battlelist::setCreaturesCount(0xC); // CREATURE COUNT
    Addresses::Battlelist::setCreaturePointer(0x14);
    Addresses::Battlelist::setRedSquare(0x1C);
    Addresses::Battlelist::setGreenSquare(0x18); // FOLLOW CREATURE
    Addresses::Battlelist::setWhiteSquare(0x14); // HOVERED CREATURE
    Addresses::Battlelist::setCreaturesOnScreenPointer(0x440);
    Addresses::Battlelist::setCreaturesOnScreenList(0x30);

    Addresses::Creature::setId(0x10);
    Addresses::Creature::setName(0x18);
    Addresses::Creature::setX(0x24);
    Addresses::Creature::setY(0x28);
    Addresses::Creature::setZ(0x2C);
    Addresses::Creature::setType(0x30);
    Addresses::Creature::setGuild(0x38);
    Addresses::Creature::setParty(0x39);
    Addresses::Creature::setHpPc(0x84);
    Addresses::Creature::setVocation(0x60); //
    Addresses::Creature::setIsNear(0xC8); //
    Addresses::Creature::setDirection(0x54);
    Addresses::Creature::setSpeed(0x58);
    Addresses::Creature::setMouseHovered(0x8C); // BYTE MOUSE HOVER
    Addresses::Creature::setHasBlackSquare(0xC0); // BYTE BLACKSQUARE
    Addresses::Creature::setLastBlackSquareTick(0xB8); // 4 BYTE ALGUMA QUANTIDADE DE TEMPO / ÚLTIMA VEZ NA TELA ou ÚLTIMO ATAQUE

    Addresses::Creature::setTimers(0x64);
    Addresses::Creature::setGameTime(0x50);
    Addresses::Creature::setLastWalkTime(0x58);

    Addresses::Player::setHealth(0xC);
    Addresses::Player::setHealthMax(0x10);
    Addresses::Player::setMana(0x58);
    Addresses::Player::setManaMax(0x5C);
    Addresses::Player::setUtamo(0xF4);
    Addresses::Player::setUtamoMax(0xF8);
    Addresses::Player::setLevel(0x28);

    Addresses::Cooldown::setId(0x10);
    Addresses::Cooldown::setEndTimeStamp(0x18);
}

void Addresses::Versions::setV131213018(uint32_t baseAddress) // 13.12.13018
{
    Addresses::Client::setBaseAddress(baseAddress);

    Addresses::Client::setDataPointer(0x10BAD54 + baseAddress);
    Addresses::Client::setPlayerPointer(0x6C);
    Addresses::Client::setPlayerCreaturePointer(0x290);
    Addresses::Client::setCooldownsPointer(0x74);
    Addresses::Client::setCooldownsGroupCollection(0x18);

    Addresses::Battlelist::setPointer(0x158);
    Addresses::Battlelist::setCreaturesList(0x8);
    Addresses::Battlelist::setCreaturePointer(0x14);
    Addresses::Battlelist::setRedSquare(0x1C);

    Addresses::Creature::setId(0x10);
    Addresses::Creature::setName(0x18);
    Addresses::Creature::setGuild(0x38);
    Addresses::Creature::setParty(0x39);
    Addresses::Creature::setHpPc(0x84);
    Addresses::Creature::setVocation(0x60);
    Addresses::Creature::setIsNear(0xC8);
    Addresses::Creature::setSpeed(0x58);

    Addresses::Player::setHealth(0xC);
    Addresses::Player::setHealthMax(0x10);
    Addresses::Player::setMana(0x58);
    Addresses::Player::setManaMax(0x5C);
    Addresses::Player::setUtamo(0xF4);
    Addresses::Player::setUtamoMax(0xF8);
    Addresses::Player::setLevel(0x28);

    Addresses::Cooldown::setId(0x10);
    Addresses::Cooldown::setEndTimeStamp(0x18);
}

void Addresses::Versions::setV131713405(uint32_t baseAddress) // 13.17.13405
{
    Addresses::Client::setBaseAddress(baseAddress);

    Addresses::Client::setDataPointer(0x1171F84 + baseAddress);
    Addresses::Client::setPlayerPointer(0x68);
    Addresses::Client::setPlayerCreaturePointer(0x27C);

    Addresses::Client::setCooldownsPointer(0x70);
    Addresses::Client::setCooldownsGroupCollection(0x18); // GROUP COOLDOWNS
    Addresses::Client::setCooldownsSpellsCollection(0x10); // SPELLS/RUNES COOLDOWNS
    Addresses::Client::setCooldownsSpellsCount(0x14); // SPELLS/RUNES COOLDOWNS QTY

    Addresses::Client::setClientFocus({0x11AF46C + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setUiChatStatus({0x88, 0x24, 0x8});
    Addresses::Client::setPing({0x4A0, 0x10});

    Addresses::Client::setKeyBindingCollection({0x88, 0x40});
    Addresses::Client::setCurrentHotkeyPresetName({0x3C, 0xF0});
    Addresses::Client::setHotkeyPresetCollection({0x38, 0xEC});
    Addresses::Client::setHotkeyCollectionName(0x10);
    Addresses::Client::setHotkeyActionBarCollection(0x20);
    Addresses::Client::setHotkeyCollection(0x10);

    Addresses::Hotkey::setId(0x8);
    Addresses::Hotkey::setText(0xC);
    Addresses::Hotkey::setTextSendAutomatically(0x10);
    Addresses::Hotkey::setItemId(0x1C);
    Addresses::Hotkey::setItemUseType(0x18);

    Addresses::Battlelist::setPointer(0x154);
    Addresses::Battlelist::setCreaturesList(0x8);
    Addresses::Battlelist::setCreaturesCount(0xC); // CREATURE COUNT
    Addresses::Battlelist::setCreaturePointer(0x14);
    Addresses::Battlelist::setRedSquare(0x1C);
    Addresses::Battlelist::setGreenSquare(0x18); // FOLLOW CREATURE
    Addresses::Battlelist::setWhiteSquare(0x14); // HOVERED CREATURE
    Addresses::Battlelist::setCreaturesOnScreenPointer(0x424);
    Addresses::Battlelist::setCreaturesOnScreenList(0x30);
    // 0x424, 0x34 -> QUANTIDADE DE MONSTROS NA TELA

    Addresses::Creature::setId(0x10); //
    Addresses::Creature::setName(0x18);
    Addresses::Creature::setX(0x24);
    Addresses::Creature::setY(0x28);
    Addresses::Creature::setZ(0x2C);
    Addresses::Creature::setType(0x30);
    Addresses::Creature::setGuild(0x38);
    Addresses::Creature::setParty(0x39);
    Addresses::Creature::setHpPc(0x84);
    Addresses::Creature::setVocation(0x60); //
    Addresses::Creature::setIsNear(0xC8); //
    Addresses::Creature::setDirection(0x54);
    Addresses::Creature::setSpeed(0x58);
    Addresses::Creature::setMouseHovered(0x8C); // BYTE MOUSE HOVER
    Addresses::Creature::setHasBlackSquare(0xC0); // BYTE BLACKSQUARE
    Addresses::Creature::setLastBlackSquareTick(0xB8); // 4 BYTE ALGUMA QUANTIDADE DE TEMPO / ÚLTIMA VEZ NA TELA ou ÚLTIMO ATAQUE

    Addresses::Creature::setTimers(0x64);
    Addresses::Creature::setGameTime(0x50);
    Addresses::Creature::setLastWalkTime(0x58);


    Addresses::Player::setHealth(0xC);
    Addresses::Player::setHealthMax(0x10);
    Addresses::Player::setMana(0x50);
    Addresses::Player::setManaMax(0x54);
    Addresses::Player::setUtamo(0xDC);
    Addresses::Player::setUtamoMax(0xE0);
    Addresses::Player::setLevel(0x28);

    Addresses::Cooldown::setId(0x10);
    Addresses::Cooldown::setEndTimeStamp(0x18);
}


void Addresses::Versions::setV132013560(uint32_t baseAddress) // 13.20.13623
{
    Addresses::Client::setBaseAddress(baseAddress);

    Addresses::Client::setDataPointer(0x117CC7C + baseAddress);//
    Addresses::Client::setPlayerPointer(0x68); //
    Addresses::Client::setPlayerCreaturePointer(0x27C);//
    Addresses::Client::setPing({0x498, 0x10});//

    Addresses::Client::setGotoData(0x4D8);//
    Addresses::Client::setGotoIsWalking(0xA8);//
    Addresses::Client::setGotoX(0xB8);//
    Addresses::Client::setGotoY(0xBC);//
    Addresses::Client::setGotoZ(0xC0);//

    Addresses::Client::setCooldownsPointer(0x70);//
    Addresses::Client::setCooldownsGroupCollection(0x18);//
    Addresses::Client::setCooldownsSpellsCollection(0x10);//
    Addresses::Client::setCooldownsSpellsCount(0x14);//

    Addresses::Client::setClientFocus({0x11BA7C0 + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setUiChatStatus({0x88, 0x24, 0x8});

    Addresses::Client::setKeyBindingCollection({0x88, 0x40});
    Addresses::Client::setCurrentHotkeyPresetName({0x3C, 0xF0});
    Addresses::Client::setHotkeyPresetCollection({0x38, 0xEC});
    Addresses::Client::setHotkeyCollectionName(0x10);
    Addresses::Client::setHotkeyActionBarCollection(0x20);
    Addresses::Client::setHotkeyCollection(0x10);

    // Inventory
    Addresses::Client::setInventoryPointer(0x11BA6F4 + baseAddress);
    Addresses::Client::setInventoryPathToItem({0x4, 0x8, 0x4C, 0x8});
    Addresses::Client::setInventoryItemSlot(0x10);
    Addresses::Client::setInventoryItemIsEquipped(0x18);
    Addresses::Client::setInventoryItemId(0x58);
    Addresses::Client::setInventoryItemCount(0x68);

    // Chat

    Addresses::Chat::setChatDataPointer(0xC4);//
    Addresses::Chat::setChatTabsPointer(0x8);//
    Addresses::Chat::setDefaultChatPointer(0x14);//

    Addresses::Chat::setChatMessagesList(0x18);//
    Addresses::Chat::setChatMessagesCount(0x24);//

    Addresses::ChatMessage::setContent(0x8);//
    Addresses::ChatMessage::setSender(0x10);//
    Addresses::ChatMessage::setId(0xC);//

    Addresses::Hotkey::setId(0x8);//
    Addresses::Hotkey::setText(0xC);//
    Addresses::Hotkey::setTextSendAutomatically(0x10);//
    Addresses::Hotkey::setItemId(0x1C);//
    Addresses::Hotkey::setItemUseType(0x18);//

    Addresses::Battlelist::setPointer(0x154);//
    Addresses::Battlelist::setCreaturesList(0x8);//
    Addresses::Battlelist::setCreaturesCount(0xC); //
    Addresses::Battlelist::setCreaturePointer(0x14);//
    Addresses::Battlelist::setRedSquare(0x1C);//
    Addresses::Battlelist::setGreenSquare(0x18); //
    Addresses::Battlelist::setWhiteSquare(0x14); //

    Addresses::Battlelist::setCreaturesOnScreenPointer(0x41C);//
    Addresses::Battlelist::setCreaturesOnScreenList(0x30);//

    Addresses::Creature::setId(0x10);//
    Addresses::Creature::setName(0x18);//
    Addresses::Creature::setX(0x24);//
    Addresses::Creature::setY(0x28);//
    Addresses::Creature::setZ(0x2C);//
    Addresses::Creature::setType(0x30);//
    Addresses::Creature::setGuild(0x38);//
    Addresses::Creature::setParty(0x39);//
    Addresses::Creature::setHpPc(0x84);//
    Addresses::Creature::setVocation(0x60);//
    Addresses::Creature::setIsNear(0xC8);//
    Addresses::Creature::setDirection(0x54);//
    Addresses::Creature::setSpeed(0x58);//
    Addresses::Creature::setMouseHovered(0x8C);  //BYTE MOUSE HOVER
    Addresses::Creature::setHasBlackSquare(0xC0); // BYTE BLACKSQUARE
    Addresses::Creature::setLastBlackSquareTick(0xB8); // 4 BYTE ALGUMA QUANTIDADE DE TEMPO / ÚLTIMA VEZ NA TELA ou ÚLTIMO ATAQUE

    Addresses::Creature::setTimers(0x64);//
    Addresses::Creature::setGameTime(0x50);//
    Addresses::Creature::setLastWalkTime(0x58);//


    Addresses::Player::setHealth(0xC);//
    Addresses::Player::setHealthMax(0x10);//
    Addresses::Player::setMana(0x50);//
    Addresses::Player::setManaMax(0x54);//
    Addresses::Player::setUtamo(0xDC);//
    Addresses::Player::setUtamoMax(0xE0);//
    Addresses::Player::setLevel(0x28);//

    Addresses::Cooldown::setId(0x10);
    Addresses::Cooldown::setEndTimeStamp(0x18);
}


void Addresses::Versions::setV132013623(uint32_t baseAddress) // 13.20.13623
{
    Addresses::Client::setBaseAddress(baseAddress);

    Addresses::Client::setDataPointer(0x117CC7C + baseAddress); //
    Addresses::Client::setPlayerPointer(0x68); //
    Addresses::Client::setPlayerCreaturePointer(0x27C); //
    Addresses::Client::setPing({0x498, 0x10}); //

    Addresses::Client::setGotoData(0x4D8);
    Addresses::Client::setGotoIsWalking(0xA8);
    Addresses::Client::setGotoX(0xB8);
    Addresses::Client::setGotoY(0xBC);
    Addresses::Client::setGotoZ(0xC0);

    Addresses::Client::setCooldownsPointer(0x70); //
    Addresses::Client::setCooldownsGroupCollection(0x18); //
    Addresses::Client::setCooldownsSpellsCollection(0x10); //
    Addresses::Client::setCooldownsSpellsCount(0x14); //

    Addresses::Client::setClientFocus({0x11BA7A0 + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setUiChatStatus({0x88, 0x24, 0x8});

    Addresses::Client::setKeyBindingCollection({0x88, 0x40});
    Addresses::Client::setCurrentHotkeyPresetName({0x3C, 0xF0}); //
    Addresses::Client::setHotkeyPresetCollection({0x38, 0xEC});
    Addresses::Client::setHotkeyCollectionName(0x10);
    Addresses::Client::setHotkeyActionBarCollection(0x20);
    Addresses::Client::setHotkeyCollection(0x10);

    // Inventory
    Addresses::Client::setInventoryPointer(0x11BA6D4 + baseAddress);
    Addresses::Client::setInventoryPathToItem({0x4, 0x8, 0x4C, 0x8});
    Addresses::Client::setInventoryItemSlot(0x10);
    Addresses::Client::setInventoryItemIsEquipped(0x18);
    Addresses::Client::setInventoryItemId(0x58);
    Addresses::Client::setInventoryItemCount(0x68);

    // Chat

    Addresses::Chat::setChatDataPointer(0xC4);
    Addresses::Chat::setChatTabsPointer(0x8);
    Addresses::Chat::setDefaultChatPointer(0x14);

    Addresses::Chat::setChatMessagesList(0x18);
    Addresses::Chat::setChatMessagesCount(0x24);

    Addresses::ChatMessage::setContent(0x8);
    Addresses::ChatMessage::setSender(0x10);
    Addresses::ChatMessage::setId(0xC);

    Addresses::Hotkey::setId(0x8);
    Addresses::Hotkey::setText(0xC);
    Addresses::Hotkey::setTextSendAutomatically(0x10);
    Addresses::Hotkey::setItemId(0x1C);
    Addresses::Hotkey::setItemUseType(0x18);

    Addresses::Battlelist::setPointer(0x154);
    Addresses::Battlelist::setCreaturesList(0x8);
    Addresses::Battlelist::setCreaturesCount(0xC); // CREATURE COUNT
    Addresses::Battlelist::setCreaturePointer(0x14);
    Addresses::Battlelist::setRedSquare(0x1C);
    Addresses::Battlelist::setGreenSquare(0x18); // FOLLOW CREATURE
    Addresses::Battlelist::setWhiteSquare(0x14); // HOVERED CREATURE

    Addresses::Battlelist::setCreaturesOnScreenPointer(0x41C);
    Addresses::Battlelist::setCreaturesOnScreenList(0x30);
    // 0x424, 0x34 -> QUANTIDADE DE MONSTROS NA TELA

    Addresses::Creature::setId(0x10); //
    Addresses::Creature::setName(0x18);
    Addresses::Creature::setX(0x24);
    Addresses::Creature::setY(0x28);
    Addresses::Creature::setZ(0x2C);
    Addresses::Creature::setType(0x30);
    Addresses::Creature::setGuild(0x38);
    Addresses::Creature::setParty(0x39);
    Addresses::Creature::setHpPc(0x84);
    Addresses::Creature::setVocation(0x60); //
    Addresses::Creature::setIsNear(0xC8); //
    Addresses::Creature::setDirection(0x54);
    Addresses::Creature::setSpeed(0x58);
    Addresses::Creature::setMouseHovered(0x8C); // BYTE MOUSE HOVER
    Addresses::Creature::setHasBlackSquare(0xC0); // BYTE BLACKSQUARE
    Addresses::Creature::setLastBlackSquareTick(0xB8); // 4 BYTE ALGUMA QUANTIDADE DE TEMPO / ÚLTIMA VEZ NA TELA ou ÚLTIMO ATAQUE

    Addresses::Creature::setTimers(0x64);
    Addresses::Creature::setGameTime(0x50);
    Addresses::Creature::setLastWalkTime(0x58);


    Addresses::Player::setHealth(0xC); //
    Addresses::Player::setHealthMax(0x10); //
    Addresses::Player::setMana(0x50); //
    Addresses::Player::setManaMax(0x54); //
    Addresses::Player::setUtamo(0xDC); //
    Addresses::Player::setUtamoMax(0xE0); //
    Addresses::Player::setLevel(0x28); //

    Addresses::Cooldown::setId(0x10);
    Addresses::Cooldown::setEndTimeStamp(0x18);
}



void Addresses::Versions::setV132013709(uint32_t baseAddress) // 13.20.13709
{
    Addresses::Client::setBaseAddress(baseAddress);

    Addresses::Client::setDataPointer(0x11A79D4 + baseAddress); //
    Addresses::Client::setPlayerPointer(0x68); //
    Addresses::Client::setPlayerCreaturePointer(0x27C); //
    Addresses::Client::setPing({0x498, 0x10}); //

    Addresses::Client::setGotoData(0x4D8);
    Addresses::Client::setGotoIsWalking(0xA8);
    Addresses::Client::setGotoX(0xB8);
    Addresses::Client::setGotoY(0xBC);
    Addresses::Client::setGotoZ(0xC0);

    Addresses::Client::setCooldownsPointer(0x70); //
    Addresses::Client::setCooldownsGroupCollection(0x18); //
    Addresses::Client::setCooldownsSpellsCollection(0x10); //
    Addresses::Client::setCooldownsSpellsCount(0x14); //

    Addresses::Client::setClientFocus({0x11E5B40 + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setUiChatStatus({0x88, 0x24, 0x8});

    Addresses::Client::setKeyBindingCollection({0x88, 0x40});
    Addresses::Client::setCurrentHotkeyPresetName({0x3C, 0xF0}); //
    Addresses::Client::setHotkeyPresetCollection({0x38, 0xEC});
    Addresses::Client::setHotkeyCollectionName(0x10);
    Addresses::Client::setHotkeyActionBarCollection(0x20);
    Addresses::Client::setHotkeyCollection(0x10);

    // Inventory
    Addresses::Client::setInventoryPointer(0x11E5B40 - 0xCC + baseAddress);
    Addresses::Client::setInventoryPathToItem({0x4, 0x8, 0x4C, 0x8});
    Addresses::Client::setInventoryItemSlot(0x10);
    Addresses::Client::setInventoryItemIsEquipped(0x18);
    Addresses::Client::setInventoryItemId(0x58);
    Addresses::Client::setInventoryItemCount(0x68);

    // Chat

    Addresses::Chat::setChatDataPointer(0xC4);
    Addresses::Chat::setChatTabsPointer(0x8);
    Addresses::Chat::setDefaultChatPointer(0x14);

    Addresses::Chat::setChatMessagesList(0x18);
    Addresses::Chat::setChatMessagesCount(0x24);

    Addresses::ChatMessage::setContent(0x8);
    Addresses::ChatMessage::setSender(0x10);
    Addresses::ChatMessage::setId(0xC);

    Addresses::Hotkey::setId(0x8);
    Addresses::Hotkey::setText(0xC);
    Addresses::Hotkey::setTextSendAutomatically(0x10);
    Addresses::Hotkey::setItemId(0x1C);
    Addresses::Hotkey::setItemUseType(0x18);

    Addresses::Battlelist::setPointer(0x154);
    Addresses::Battlelist::setCreaturesList(0x8);
    Addresses::Battlelist::setCreaturesCount(0xC); // CREATURE COUNT
    Addresses::Battlelist::setCreaturePointer(0x14);
    Addresses::Battlelist::setRedSquare(0x1C);
    Addresses::Battlelist::setGreenSquare(0x18); // FOLLOW CREATURE
    Addresses::Battlelist::setWhiteSquare(0x14); // HOVERED CREATURE

    Addresses::Battlelist::setCreaturesOnScreenPointer(0x41C);
    Addresses::Battlelist::setCreaturesOnScreenList(0x30);
    // 0x424, 0x34 -> QUANTIDADE DE MONSTROS NA TELA

    Addresses::Creature::setId(0x10); //
    Addresses::Creature::setName(0x18);
    Addresses::Creature::setX(0x24);
    Addresses::Creature::setY(0x28);
    Addresses::Creature::setZ(0x2C);
    Addresses::Creature::setType(0x30);
    Addresses::Creature::setGuild(0x38);
    Addresses::Creature::setParty(0x39);
    Addresses::Creature::setHpPc(0x84);
    Addresses::Creature::setVocation(0x60); //
    Addresses::Creature::setIsNear(0xC8); //
    Addresses::Creature::setDirection(0x54);
    Addresses::Creature::setSpeed(0x58);
    Addresses::Creature::setMouseHovered(0x8C); // BYTE MOUSE HOVER
    Addresses::Creature::setHasBlackSquare(0xC0); // BYTE BLACKSQUARE
    Addresses::Creature::setLastBlackSquareTick(0xB8); // 4 BYTE ALGUMA QUANTIDADE DE TEMPO / ÚLTIMA VEZ NA TELA ou ÚLTIMO ATAQUE

    Addresses::Creature::setTimers(0x64);
    Addresses::Creature::setGameTime(0x50);
    Addresses::Creature::setLastWalkTime(0x58);


    Addresses::Player::setHealth(0xC); //
    Addresses::Player::setHealthMax(0x10); //
    Addresses::Player::setMana(0x50); //
    Addresses::Player::setManaMax(0x54); //
    Addresses::Player::setUtamo(0xDC); //
    Addresses::Player::setUtamoMax(0xE0); //
    Addresses::Player::setLevel(0x28); //

    Addresses::Cooldown::setId(0x10);
    Addresses::Cooldown::setEndTimeStamp(0x18);
}

