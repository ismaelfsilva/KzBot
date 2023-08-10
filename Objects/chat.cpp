#include "chat.h"
#include "../Addresses/chat.h"
#include "../Util/kzhelper.h"
#include "../Settings/globals.h"

using namespace Objects;

std::unordered_map<uint32_t, bool> Chat::m_processedMessages;

uint32_t Chat::getPointer(uint32_t dataPointer)
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Chat::getChatDataPointer());
}

uint32_t Chat::getTabsPointer(uint32_t dataPointer)
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), getPointer(dataPointer) + Addresses::Chat::getChatTabsPointer());
}

std::map<uint32_t, ChatMessage*> Chat::getDefaultChannel(uint32_t dataPointer)
{
    std::map<uint32_t, ChatMessage*> messageList;

    uint32_t defaultChannelPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), getTabsPointer(dataPointer) + Addresses::Chat::getDefaultChatPointer());

    int messageCount = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), defaultChannelPointer + Addresses::Chat::getChatMessagesCount());
    uint32_t messageListStart = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), defaultChannelPointer + Addresses::Chat::getChatMessagesList());
    uint32_t messageListSize = messageCount * 0x4;

    char qtCollectionData[0x1000];
    if (!Util::KzHelper::ReadMemory(Globals::getHandle(), messageListStart, qtCollectionData, sizeof(qtCollectionData)))
        return messageList;

    for (int i = 0; i < messageListSize; i += 0x4)
    {
        uint32_t messageAddress = *reinterpret_cast<uint32_t*>(qtCollectionData + i);

        ChatMessage* chatMessage = new ChatMessage(messageAddress);
        messageList[chatMessage->getId()] = chatMessage;
    }
    return messageList;
}
