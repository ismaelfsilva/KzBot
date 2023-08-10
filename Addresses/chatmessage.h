#ifndef CHATMESSAGE_ADDR_H
#define CHATMESSAGE_ADDR_H

#include <cstdint>
namespace Addresses
{

class ChatMessage
{
public:
    static uint32_t getId() { return m_id; }
    static void setId(uint32_t id) { m_id = id; }

    static uint32_t getContent() { return m_content; }
    static void setContent(uint32_t content) { m_content = content; }

    static uint32_t getSender() { return m_sender; }
    static void setSender(uint32_t sender) { m_sender = sender; }

private:
    static uint32_t m_id;
    static uint32_t m_content;
    static uint32_t m_sender;
};

}

#endif // CHATMESSAGE_H
