#ifndef CHAT_OBJ_H
#define CHAT_OBJ_H


#include "chatmessage.h"
#include <cstdint>
#include <map>
#include <unordered_map>
#include <vector>

namespace Objects
{
class Chat
{
public:
    static uint32_t getPointer(uint32_t dataPointer);
    static uint32_t getTabsPointer(uint32_t dataPointer);

    static std::map<uint32_t, ChatMessage*> getDefaultChannel(uint32_t dataPointer);
private:
    static std::unordered_map<uint32_t, bool> m_processedMessages;
};
}
#endif // CHAT_H
