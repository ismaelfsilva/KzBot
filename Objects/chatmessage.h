#ifndef CHATMESSAGE_OBJ_H
#define CHATMESSAGE_OBJ_H


#include <cstdint>
#include <string>

class ChatMessage
{
public:
    ChatMessage(uint32_t addr);

    uint32_t getAddress();
    uint32_t getId();
    std::string getContent();
    std::string getSender();

private:
    uint32_t m_address;
};

#endif // CHATMESSAGE_H
