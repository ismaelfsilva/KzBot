#include "versions.h"
#include "../player.h"
#include "../cooldown.h"
#include "../inventory.h"
#include "../inventoryitem.h"
#include "../creature.h"
#include "../client.h"
#include "../battlelist.h"
#include "../hotkey.h"
#include "../chat.h"
#include "../chatmessage.h"
#include "../../Settings/globals.h"
#include "../../Util/kzhelper.h"

std::string Addresses::Versions::getVersion(HANDLE& handle, uint32_t baseAddress)
{
    std::vector<uint32_t> clientDataPointers = {
        0x10B69EC, // 13.10.12892
        0x117CC5C, // 13.20.13623; 13.20.13560
        0x11A79B4, // 13.20.13709
        0x11D714C, // 13.21.13743
        0x11D8188, // 13.21.13775
        0x011D817C, // 13.21.13810; 13.21.13839
        0x11D516C, // 13.21.14172
        0x11E5424, // 13.22.14282; 13.22.14242
        0x123C0A4, // 13.30.14423; 13.30.14428; 13.30.14434
    };

    for (uint32_t clientDataPointer : clientDataPointers)
    {
        try
        {
            auto dataCollection = Util::KzHelper::readQtCollection(handle, clientDataPointer + baseAddress);
            for (auto data : dataCollection)
            {
                std::string dataName = Util::KzHelper::ReadMemoryStringUnicode(handle, data.first + 0x10);
                std::string dataValue = Util::KzHelper::ReadMemoryStringUnicode(handle, Util::KzHelper::ReadMemoryUInt32(handle, data.second + 0x14) + 0x10);

                if (dataName == "Version")
                    return dataValue;
            }
        }
        catch (...)
        {

        }
    }

    return "Not Supported";
}

bool Addresses::Versions::isSupportedVersion(std::string versionString)
{
    if (versionString == "13.10.12892") // Pandora
        return true;
    else if (versionString == "13.20.13560") // Hellgate
        return true;
    else if (versionString == "13.20.13673") // Hellgate
        return true;
    else if (versionString == "13.20.13623") // Hades
        return true;
    else if (versionString == "13.20.13709") // Arcana
        return true;
    else if (versionString == "13.21.13743")
        return true;
    else if (versionString == "13.21.13775")
        return true;
    else if (versionString == "13.21.13810") // Fortera
        return true;
    else if (versionString == "13.21.13839")
        return true;
    else if (versionString == "13.21.14172") //
        return true;
    else if (versionString == "13.22.14282") //
        return true;
    else if (versionString == "13.22.14242") //
        return true;
    else if (versionString == "13.22.14366") // Ferumbrinha
        return true;
    else if (versionString == "13.30.14423") //
        return true;
    else if (versionString == "13.30.14428") // Rubini
        return true;
    else if (versionString == "13.30.14434") // Ferumbrinha
        return true;
}

void Addresses::Versions::setVersion(std::string versionString)
{
    //if (versionString == "13.05.12827") // Furia
    //    Addresses::Versions::setV130512827(Globals::getBaseAddress());
    if (versionString == "13.10.12892") // Pandora
        Addresses::Versions::setV131012892(Globals::getBaseAddress());
    else if (versionString == "13.20.13560") // Hellgate
        Addresses::Versions::setV132013560(Globals::getBaseAddress());
    else if (versionString == "13.20.13673") // Hellgate
        Addresses::Versions::setV132013560(Globals::getBaseAddress());
    else if (versionString == "13.20.13623") // Hades
        Addresses::Versions::setV132013623(Globals::getBaseAddress());
    else if (versionString == "13.20.13709") // Arcana
        Addresses::Versions::setV132013709(Globals::getBaseAddress());
    else if (versionString == "13.21.13743")
        Addresses::Versions::setV132113743(Globals::getBaseAddress());
    else if (versionString == "13.21.13775")
        Addresses::Versions::setV132113775(Globals::getBaseAddress());
    else if (versionString == "13.21.13810") // Fortera
        Addresses::Versions::setV132113810(Globals::getBaseAddress());
    else if (versionString == "13.21.13839")
        Addresses::Versions::setV132113839(Globals::getBaseAddress());
    else if (versionString == "13.21.14172") // Rubini
        Addresses::Versions::setV132114172(Globals::getBaseAddress());
    else if (versionString == "13.22.14282") //
        Addresses::Versions::setV132114172(Globals::getBaseAddress());
    else if (versionString == "13.22.14242") //
        Addresses::Versions::setV132214282(Globals::getBaseAddress());
    else if (versionString == "13.22.14366") // Rubini
        Addresses::Versions::setV132214366(Globals::getBaseAddress());
    else if (versionString == "13.30.14423") //
        Addresses::Versions::setV133014423(Globals::getBaseAddress());
    else if (versionString == "13.30.14428") // Rubini
        Addresses::Versions::setV133014423(Globals::getBaseAddress());
    else if (versionString == "13.30.14434") // Ferumbrinha
        Addresses::Versions::setV133014423(Globals::getBaseAddress());
}

void Addresses::Versions::setV130512827(uint32_t baseAddress) // 13.05.12827
{
    Addresses::Client::setBaseAddress(baseAddress);
    Addresses::Client::setLoggedIn(0x103CE58 + baseAddress);
    Addresses::Client::setDataPointer(Addresses::Client::getLoggedIn() + 0x1C);

    Addresses::Client::setClientFocus({0x107A370 + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setInventoryPointer(0x107A2D0 + baseAddress); // OFF 3E

    Addresses::Versions::setOffsetsA();
}

void Addresses::Versions::setV131012892(uint32_t baseAddress) // 13.10.12892
{
    Addresses::Client::setBaseAddress(baseAddress);
    Addresses::Client::setLoggedIn(0x10B69F0 + baseAddress);
    Addresses::Client::setDataPointer(Addresses::Client::getLoggedIn() + 0x1C);

    Addresses::Client::setClientFocus({0x010F4E3C + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setInventoryPointer(0x010F4D58 + baseAddress);

    Addresses::Versions::setOffsetsC();
}

void Addresses::Versions::setV132013623(uint32_t baseAddress) // 13.20.13623
{
    Addresses::Client::setBaseAddress(baseAddress);
    Addresses::Client::setLoggedIn(0x117CC60 + baseAddress);
    Addresses::Client::setDataPointer(Addresses::Client::getLoggedIn() + 0x1C);

    Addresses::Client::setClientFocus({0x11BA7A0 + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setInventoryPointer(Addresses::Client::getClientFocus()[0] - 0xCC);

    Addresses::Versions::setOffsetsA();
}

void Addresses::Versions::setV132013560(uint32_t baseAddress) // 13.20.13560
{
    Addresses::Client::setBaseAddress(baseAddress);
    Addresses::Client::setLoggedIn(0x117CC60 + baseAddress);
    Addresses::Client::setDataPointer(Addresses::Client::getLoggedIn() + 0x1C);

    Addresses::Client::setClientFocus({0x11BA7C0 + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setInventoryPointer(Addresses::Client::getClientFocus()[0] - 0xCC);

    Addresses::Versions::setOffsetsA();
}

void Addresses::Versions::setV132013709(uint32_t baseAddress) // 13.20.13709
{
    Addresses::Client::setBaseAddress(baseAddress);
    Addresses::Client::setLoggedIn(0x11A79B8 + baseAddress);
    Addresses::Client::setDataPointer(Addresses::Client::getLoggedIn() + 0x1C);

    Addresses::Client::setClientFocus({0x11E5B40 + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setInventoryPointer(Addresses::Client::getClientFocus()[0] - 0xCC);

    Addresses::Versions::setOffsetsA();
}
void Addresses::Versions::setV132113743(uint32_t baseAddress) // 13.21.13743
{
    Addresses::Client::setBaseAddress(baseAddress);
    Addresses::Client::setLoggedIn(0x11D7150 + baseAddress);
    Addresses::Client::setDataPointer(Addresses::Client::getLoggedIn() + 0x1C);

    Addresses::Client::setClientFocus({0x12157EC + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setInventoryPointer(Addresses::Client::getClientFocus()[0] - 0xCC);

    Addresses::Versions::setOffsetsA();
}
void Addresses::Versions::setV132113775(uint32_t baseAddress) // 13.21.13775
{
    Addresses::Client::setBaseAddress(baseAddress);
    Addresses::Client::setLoggedIn(0x11D8188 + baseAddress);
    Addresses::Client::setDataPointer(Addresses::Client::getLoggedIn() + 0x1C);

    Addresses::Client::setClientFocus({0x1216818 + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setInventoryPointer(Addresses::Client::getClientFocus()[0] - 0xCC);

    Addresses::Versions::setOffsetsA();
}
void Addresses::Versions::setV132113810(uint32_t baseAddress) // 13.21.13810
{
    Addresses::Client::setBaseAddress(baseAddress);
    Addresses::Client::setLoggedIn(0x11D8180 + baseAddress);
    Addresses::Client::setDataPointer(Addresses::Client::getLoggedIn() + 0x1C);

    Addresses::Client::setClientFocus({0x12168C0 + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setInventoryPointer(0x012167C4 + baseAddress); // +0x4 = DESLOGADO 3F; LOGADO +

    Addresses::Versions::setOffsetsA();
}

void Addresses::Versions::setV132113839(uint32_t baseAddress) // 13.21.13839
{
    Addresses::Client::setBaseAddress(baseAddress);
    Addresses::Client::setLoggedIn(0x11D8180 + baseAddress);
    Addresses::Client::setDataPointer(Addresses::Client::getLoggedIn() + 0x1C);

    Addresses::Client::setClientFocus({0x12168F0 + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setInventoryPointer(0x012167F4 + baseAddress); // +0x4 = DESLOGADO 3F; LOGADO +

    Addresses::Versions::setOffsetsA();
}

void Addresses::Versions::setV132114172(uint32_t baseAddress) // 13.21.14172
{
    Addresses::Client::setBaseAddress(baseAddress);
    Addresses::Client::setLoggedIn(0x11D5170 + baseAddress);
    Addresses::Client::setDataPointer(Addresses::Client::getLoggedIn() + 0x1C);

    Addresses::Client::setClientFocus({0x1213790 + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setInventoryPointer(0x1213694 + baseAddress); // +0x4 = DESLOGADO 3F; LOGADO +

    Addresses::Versions::setOffsetsA();
}

void Addresses::Versions::setV132214282(uint32_t baseAddress) // 13.22.14282
{
    Addresses::Client::setBaseAddress(baseAddress);
    Addresses::Client::setLoggedIn(0x11E5428 + baseAddress);
    Addresses::Client::setDataPointer(Addresses::Client::getLoggedIn() + 0x1C);

    Addresses::Client::setClientFocus({0x1225084 + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setInventoryPointer(0x1224F84 + baseAddress); // +0x4 = DESLOGADO 3F; LOGADO +

    Addresses::Versions::setOffsetsA();
}

void Addresses::Versions::setV132214366(uint32_t baseAddress) // 13.22.14366
{
    Addresses::Client::setBaseAddress(baseAddress);
    Addresses::Client::setLoggedIn(0x11E5428 + baseAddress);
    Addresses::Client::setDataPointer(Addresses::Client::getLoggedIn() + 0x1C);

    Addresses::Client::setClientFocus({0x1225044 + baseAddress, 0x10, 0x20, 0x8});
    Addresses::Client::setInventoryPointer(0x1224F44 + baseAddress); // +0x4 = DESLOGADO 3F; LOGADO +

    Addresses::Versions::setOffsetsA();
}

void Addresses::Versions::setV133014423(uint32_t baseAddress) // 13.30.14423
{
    Addresses::Client::setBaseAddress(baseAddress);
    Addresses::Client::setLoggedIn(0x123C0A8 + baseAddress);
    Addresses::Client::setDataPointer(Addresses::Client::getLoggedIn() + 0x1C);

    Addresses::Client::setClientFocus({0x127C16C + baseAddress, 0x10, 0x20, 0x8});

    Addresses::Versions::setOffsetsA();
}

void Addresses::Versions::setOffsetsA() // Player Creature 0x27C
{
    Addresses::Client::setPlayerPointer(0x68);
    Addresses::Client::setPlayerCreaturePointer(0x27C);
    Addresses::Client::setPing({0x498, 0x10});


    Addresses::Client::setCooldownsPointer(0x70);
    Addresses::Client::setCooldownsGroupCollection(0x18);
    Addresses::Client::setCooldownsSpellsCollection(0x10);
    Addresses::Client::setCooldownsSpellsCount(0x14);
    //0x3C = Passive Count
    //0x38 = Passive Collection
    //Ids: 1 = Gift;
    // CDS EM CONTAGEM REGRESSIVA NESSA LISTA

    Addresses::Client::setGotoData(0x4D8);
    Addresses::Client::setGotoIsWalking(0xA8);
    Addresses::Client::setGotoX(0xB8);
    Addresses::Client::setGotoY(0xBC);
    Addresses::Client::setGotoZ(0xC0);

    Addresses::Client::setKeyBindingCollection({0x88, 0x40});
    Addresses::Client::setCurrentHotkeyPresetName({0x3C, 0xF0});
    Addresses::Client::setHotkeyPresetCollection({0x38, 0xEC});
    Addresses::Client::setHotkeyCollectionName(0x10);
    Addresses::Client::setHotkeyActionBarCollection(0x20);
    Addresses::Client::setHotkeyCollection(0x10);

    Addresses::Client::setInventoryPathToItem({0x4, 0x8, 0x4C, 0x8});
    Addresses::Client::setInventoryItemSlot(0x10);
    Addresses::Client::setInventoryItemIsEquipped(0x18);
    Addresses::Client::setInventoryItemId(0x58);
    Addresses::Client::setInventoryItemCount(0x68);

    // Inventory
    Addresses::Inventory::setPointer(0x174);
    Addresses::Inventory::setInventoryContainerPointer(0xC);
    Addresses::Inventory::setInventoryContainerItemList(0x8);
    Addresses::Inventory::setContainersPointer(0x10);

    Addresses::InventoryItem::setItemSlot(0x10);
    Addresses::InventoryItem::setItemDataPointer(0x14);
    Addresses::InventoryItem::setItemDataId(0x8);

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
    Addresses::Battlelist::setCreaturesCount(0xC);
    Addresses::Battlelist::setCreaturePointer(0x14);
    Addresses::Battlelist::setRedSquare(0x1C);
    Addresses::Battlelist::setGreenSquare(0x18);
    Addresses::Battlelist::setWhiteSquare(0x14);

    Addresses::Battlelist::setCreaturesOnScreenPointer(0x41C);
    Addresses::Battlelist::setCreaturesOnScreenList(0x30);

    Addresses::Creature::setId(0x10);
    Addresses::Creature::setName(0x18);
    Addresses::Creature::setX(0x24);
    Addresses::Creature::setY(0x28);
    Addresses::Creature::setZ(0x2C);
    Addresses::Creature::setType(0x30);
    Addresses::Creature::setGuild(0x38);
    Addresses::Creature::setParty(0x39);
    Addresses::Creature::setOutOfPz(0x3C);
    Addresses::Creature::setHpPc(0x84);
    Addresses::Creature::setVocation(0x60);
    Addresses::Creature::setIsNear(0xC8);
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
    Addresses::Player::setFoodTime(0x78);
    Addresses::Player::setStatusListStart(0x84);
    Addresses::Player::setStatusListEnd(0x88);

    Addresses::Cooldown::setId(0x10);
    Addresses::Cooldown::setEndTimeStamp(0x18);
}


void Addresses::Versions::setOffsetsB() // Player Creature 0x270
{
    Addresses::Client::setPlayerPointer(0x6C); //
    Addresses::Client::setPlayerCreaturePointer(0x270); //
    Addresses::Client::setPing({0x47C, 0x10}); //


    Addresses::Client::setCooldownsPointer(0x74);
    Addresses::Client::setCooldownsGroupCollection(0x10);
    Addresses::Client::setCooldownsSpellsCollection(0x8);
    Addresses::Client::setCooldownsSpellsCount(0xC);

    Addresses::Cooldown::setId(0x10);
    Addresses::Cooldown::setEndTimeStamp(0x18);

    Addresses::Client::setGotoData(0x4BC);
    Addresses::Client::setGotoIsWalking(0xA8);
    Addresses::Client::setGotoX(0xB8);
    Addresses::Client::setGotoY(0xBC);
    Addresses::Client::setGotoZ(0xC0);

    // ATT ATÉ AQUI

    Addresses::Client::setKeyBindingCollection({0x88, 0x40});

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

    Addresses::Battlelist::setPointer(0x140);
    Addresses::Battlelist::setCreaturesList(0x8);
    Addresses::Battlelist::setCreaturesCount(0xC);
    Addresses::Battlelist::setCreaturePointer(0x14);
    Addresses::Battlelist::setRedSquare(0x1C);
    Addresses::Battlelist::setGreenSquare(0x18);
    Addresses::Battlelist::setWhiteSquare(0x14);

    Addresses::Battlelist::setCreaturesOnScreenPointer(0x400);
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
    Addresses::Creature::setOutOfPz(0x3C);
    Addresses::Creature::setVocation(0x60);
    Addresses::Creature::setIsNear(0xC8);
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
}



void Addresses::Versions::setOffsetsC() // Player Creature 0x290
{
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

    Addresses::Client::setPing({0x4BC, 0x10}); //

    // Inventory
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
    Addresses::Creature::setOutOfPz(0x3C);
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
    Addresses::Player::setFoodTime(0x78);
    Addresses::Player::setStatusListStart(0x84);
    Addresses::Player::setStatusListEnd(0x88);

    Addresses::Cooldown::setId(0x10);
    Addresses::Cooldown::setEndTimeStamp(0x18);
}
