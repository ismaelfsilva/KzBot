#include "hotkey.h"
#include "../Util/kzhelper.h"
#include "../Settings/globals.h"
#include "../Addresses/hotkey.h"

using namespace Objects;

Hotkey::Hotkey(uint32_t address, int actionBarId)
{
    m_address = address;
    m_actionBarId = actionBarId;
    m_name = "TriggerActionButton_" + std::to_string(m_actionBarId) + "." + std::to_string(getId());
}

int Hotkey::getId()
{
    uint32_t id = Util::KzHelper::ReadMemoryByte(Globals::getHandle(), m_address + Addresses::Hotkey::getId());
    return id;
}

std::string Hotkey::getText()
{
    uint32_t qStringPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Hotkey::getText());
    return Util::KzHelper::ReadMemoryStringUnicode(Globals::getHandle(), qStringPointer + 0x10);
}

bool Hotkey::getTextSendAutomatically()
{
    uint32_t sendAutomatically = Util::KzHelper::ReadMemoryByte(Globals::getHandle(), m_address + Addresses::Hotkey::getTextSendAutomatically());
    return sendAutomatically;
}

int Hotkey::getItemId()
{
    uint32_t itemId = Util::KzHelper::ReadMemoryUInt16(Globals::getHandle(), m_address + Addresses::Hotkey::getItemId());
    return itemId;
}

ItemUseType Hotkey::getUseType()
{
    uint32_t useType = Util::KzHelper::ReadMemoryUInt16(Globals::getHandle(), m_address + Addresses::Hotkey::getItemUseType());
    return (ItemUseType)useType;
}

bool Hotkey::isItem()
{
    return getItemId() > 0;
}

KeyBinding* Hotkey::getKeyBinding(std::unordered_map<std::string, KeyBinding*>& keyBindingMap)
{
    return keyBindingMap["TriggerActionButton_" + std::to_string(m_actionBarId) + "." + std::to_string(getId())];
}

void Hotkey::setText(std::string text)
{
    uint32_t qStringPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::Hotkey::getText());
    Util::KzHelper::WriteMemoryUInt32(Globals::getHandle(), qStringPointer + 0x4, text.length());
    Util::KzHelper::WriteMemoryStringUnicode(Globals::getHandle(), qStringPointer + 0x10, text);
}

void Hotkey::setItem(int itemId, int useType)
{
    Util::KzHelper::WriteMemoryUInt32(Globals::getHandle(), m_address + Addresses::Hotkey::getItemId(), itemId);
    Util::KzHelper::WriteMemoryUInt32(Globals::getHandle(), m_address + Addresses::Hotkey::getItemUseType(), useType);
}
