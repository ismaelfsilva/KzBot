#include "chatmessage.h"
#include "../Util/kzhelper.h"
#include "../Settings/globals.h"
#include "../Addresses/chatmessage.h"

ChatMessage::ChatMessage(uint32_t addr)
{
    m_address = addr;
}

uint32_t ChatMessage::getAddress()
{
    return m_address;
}

uint32_t ChatMessage::getId()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::ChatMessage::getId());
}

std::string ChatMessage::getContent()
{
    uint32_t contentPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::ChatMessage::getContent());
    return Util::KzHelper::ReadMemoryStringUnicode(Globals::getHandle(), contentPointer + 0x10);
}

std::string ChatMessage::getSender()
{
    uint32_t senderPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), m_address + Addresses::ChatMessage::getSender());
    return Util::KzHelper::ReadMemoryStringUnicode(Globals::getHandle(), senderPointer + 0x10);
}
