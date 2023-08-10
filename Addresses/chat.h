#ifndef CHAT_ADDR_H
#define CHAT_ADDR_H



#include <cstdint>
namespace Addresses
{
class Chat
{
public:
    static uint32_t getChatDataPointer() { return m_chatDataPointer; }
    static void setChatDataPointer(uint32_t pointer) { m_chatDataPointer = pointer; }

    static uint32_t getChatTabsPointer() { return m_chatTabsPointer; }
    static void setChatTabsPointer(uint32_t pointer) { m_chatTabsPointer = pointer; }

    static uint32_t getDefaultChatPointer() { return m_defaultChatPointer; }
    static void setDefaultChatPointer(uint32_t pointer) { m_defaultChatPointer = pointer; }

    static uint32_t getChatMessagesList() { return m_chatMessagesList; }
    static void setChatMessagesList(uint32_t pointer) { m_chatMessagesList = pointer; }

    static uint32_t getChatMessagesCount() { return m_chatMessagesCount; }
    static void setChatMessagesCount(uint32_t count) { m_chatMessagesCount = count; }


private:
    static uint32_t m_chatDataPointer;
    static uint32_t m_chatTabsPointer;

    static uint32_t m_defaultChatPointer;

    static uint32_t m_chatMessagesList;
    static uint32_t m_chatMessagesCount;
};
}
#endif // CHAT_H
