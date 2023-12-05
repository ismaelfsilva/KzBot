#ifndef ENUMS_H
#define ENUMS_H

enum class DelayType
{
    None = 0,
    EquipAmulet,
    EquipRing,
    DefaultAmulet,
    DefaultRing,
    Heal,
    Item,
    Food,
    NpcFood,
    CupcakeHp,
    CupcakeMp,
    Utamo
};

enum class ActionType
{
    None,
    Spell,
    Rune,
    Item,
    Equip,
};

enum class ItemUseType
{
    Use,
    UseOnYourself,
    UseOnTarget,
    UseWithCrosshair,
    Equip
};


enum class CooldownGroup
{
    Item = 0,
    Attack = 1,
    Heal = 2,
    Support = 3,
    Equip = 4,
    Food = 4,
};

enum class AmuletType
{
    Unknown = -1,
    None = 82,
    StoneSkin = 184,
};

enum class RingType
{
    Unknown = -1,
    None = 94,
    Might = 155,
    Energy = 65,
};

enum class ChatStatus
{
    Off = 0,
    On = 1,
    SemiOn = 2
};

//{0xC4, 0x8, ch_id (0x14 Default; 0x1C Server Log), 0x18, msg_id, (0x8 Content; 0x10 Sender; ), 0x10} Default Msgs
//{0xC4, 0x8, ch_id (0x14 Default; 0x1C Server Log), 0x24} - Msg Qty DEFAULT
enum class ChatChannel
{
    Default = 0x14,
    Server = 0x1C,
};

enum class ChatMessageData
{
    Content = 0x8,
    Sender = 0x10,
};


enum class Vocation
{
    None = 0,
    Knight,
    Paladin,
    Sorcerer,
    Druid
};

enum class Direction
{
    None = -1,
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3,
    NORTH_EAST = 4,
    SOUTH_EAST = 5,
    SOUTH_WEST = 6,
    NORTH_WEST = 7
};

enum class PartyShield
{
    None = 0,
    WHITEYELLOW = 1,
    WHITEBLUE = 2,
    BLUE = 3,
    YELLOW = 4,
    BLUE_SHAREDEXP = 5,
    YELLOW_SHAREDEXP = 6,
    BLUE_NOSHAREDEXP_BLINK = 7,
    YELLOW_NOSHAREDEXP_BLINK = 8,
    BLUE_NOSHAREDEXP = 9,
    YELLOW_NOSHAREDEXP = 10,
    GRAY = 11,
};

enum class CreatureType
{
    Player = 0,
    Monster,
    Npc,
    SummonOwn,
    SummonOther,
    Unknown = 0xFF
};

enum class SkullType
{
    None = 0,
    Yellow,
    Green,
    White,
    Red,
    Black,
    Orange
};

enum class GuildEmblem
{
    None = 0,
    Green,
    Red,
    Blue,
    Member,
    Other
};

enum class InventorySlot
{
    InventorySlotHead = 1,
    InventorySlotNecklace,
    InventorySlotBackpack,
    InventorySlotArmor,
    InventorySlotRight,
    InventorySlotLeft,
    InventorySlotLegs,
    InventorySlotFeet,
    InventorySlotRing,
    InventorySlotAmmo,
    InventorySlotPurse,
    InventorySlotExt1,
    InventorySlotExt2,
    InventorySlotExt3,
    InventorySlotExt4,
    LastInventorySlot
};

enum class Icons
{
    ICON_POISON = 0,
    ICON_BURN = 1,
    ICON_ENERGY = 2,
    ICON_DRUNK = 3,
    ICON_MANASHIELD = 4,
    ICON_PARALYZE = 5,
    ICON_HASTE = 6,
    ICON_SWORDS = 7,
    ICON_DROWNING = 8,
    ICON_FREEZING = 9,
    ICON_DAZZLED = 10,
    ICON_CURSED = 11,
    ICON_PARTY_BUFF = 12,
    ICON_REDSWORDS = 13,
    ICON_PIGEON = 14,
    ICON_BLEEDING = 15,
    ICON_LESSERHEX = 16,
    ICON_INTENSEHEX = 17,
    ICON_GREATERHEX = 18,
    ICON_ROOT = 19,
    ICON_FEAR = 20,
    ICON_GOSHNAR1 = 21,
    ICON_GOSHNAR2 = 22,
    ICON_GOSHNAR3 = 23,
    ICON_GOSHNAR4 = 24,
    ICON_GOSHNAR5 = 25,
    ICON_MANASHIELD_BREAKABLE = 26,
};

#endif // ENUMS_H
