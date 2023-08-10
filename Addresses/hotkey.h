#ifndef HOTKEY_ADDR_H
#define HOTKEY_ADDR_H

#include <cstdint>
namespace Addresses
{

class Hotkey
{
public:
    static void setId(uint32_t value) { m_id = value; };
    static void setText(uint32_t value) { m_text = value; };
    static void setTextSendAutomatically(uint32_t value) { m_textSendAutomatically = value; };
    static void setItemId(uint32_t value) { m_itemId = value; };
    static void setItemUseType(uint32_t value) { m_itemUseType = value; };

    static uint32_t getId() { return m_id; };
    static uint32_t getText() { return m_text; };
    static uint32_t getTextSendAutomatically() { return m_textSendAutomatically; };
    static uint32_t getItemId() { return m_itemId; };
    static uint32_t getItemUseType() { return m_itemUseType; };
private:
    static uint32_t m_id;
    static uint32_t m_text;
    static uint32_t m_textSendAutomatically;
    static uint32_t m_itemId;
    static uint32_t m_itemUseType;
};

};
#endif // HOTKEY_ADDR_H
