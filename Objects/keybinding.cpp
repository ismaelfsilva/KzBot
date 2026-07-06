#include "keybinding.h"
#include <cstdint>
#include "../Util/kzhelper.h"
#include "../Settings/globals.h"

using namespace Objects;

KeyBinding::KeyBinding(uint32_t id, uint32_t address)
{
    m_id = id;
    m_address = address;
}

uint32_t KeyBinding::getAddress()
{
    return m_address;
}

std::string KeyBinding::getName()
{
    uint32_t keyNamePointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + 0x1C);
    std::string keyName = Util::KzHelper::ReadMemoryStringUnicode(Globals::getHandle(), keyNamePointer + 0x10);

    return keyName;
}

uint32_t KeyBinding::getKey(bool& extended)
{
    uint32_t key = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_id + 0x4);

    return Util::KzHelper::qtKeyToVK(key, extended);
}

void KeyBinding::setKey(uint32_t key)
{
    Util::KzHelper::WriteMemoryUInt32(Globals::getHandle(), m_id + 0x4, key);
}

Qt::KeyboardModifier KeyBinding::getModifier()
{
    uint32_t keyData = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + 0x10);
    uint32_t key = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), keyData + 0x4);

    if (key < Qt::NoModifier)
        return Qt::NoModifier;
    else if (key & Qt::ShiftModifier)
        return Qt::ShiftModifier;
    else if (key & Qt::ControlModifier)
        return Qt::ControlModifier;
    else if (key & Qt::AltModifier)
        return Qt::AltModifier;
    else if (key & Qt::MetaModifier)
        return Qt::MetaModifier;
    else if (key & Qt::KeypadModifier)
        return Qt::KeypadModifier;

    return Qt::NoModifier;
}

int KeyBinding::getId()
{
    uint32_t itemId = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + 0x24);
    return itemId;
}

void KeyBinding::setId(int itemId)
{
    Util::KzHelper::WriteMemoryUInt32(Globals::getHandle(), m_address + 0x24, itemId);
}

ItemUseType KeyBinding::getUseType()
{
    uint32_t useType = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + 0x20);
    return (ItemUseType)useType;
}

void KeyBinding::setUseType(ItemUseType useType)
{
    Util::KzHelper::WriteMemoryUInt32(Globals::getHandle(), m_address + 0x20, (int)useType);
}

std::string KeyBinding::getText()
{
    uint32_t keyTextPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + 0x14);
    std::string keyText = Util::KzHelper::ReadMemoryStringUnicode(Globals::getHandle(), keyTextPointer + 0x10);

    return keyText;
}

void KeyBinding::setText(std::string text)
{
    uint32_t keyTextPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + 0x14);
    Util::KzHelper::WriteMemoryUInt32(Globals::getHandle(), keyTextPointer + 0x4, text.length());
    Util::KzHelper::WriteMemoryStringUnicode(Globals::getHandle(), keyTextPointer + 0x10, text);
}

bool KeyBinding::getSendAutomatically()
{
    uint32_t itemId = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + 0x18);
    return itemId;
}

void KeyBinding::setSendAutomatically(bool automatically)
{
    Util::KzHelper::WriteMemoryUInt32(Globals::getHandle(), m_address + 0x18, automatically);
}
