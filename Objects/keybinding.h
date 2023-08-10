#ifndef KEYBINDING_OBJ_H
#define KEYBINDING_OBJ_H


#include <cstdint>
#include <Qt>
#include <string>
#include "../Util/Enums.h"

namespace Objects
{
class KeyBinding
{
public:
    KeyBinding(uint32_t id, uint32_t address);
    uint32_t getAddress();

    std::string getName();
    uint32_t getKey(bool& extended);
    Qt::KeyboardModifier getModifier();
    bool& isExtended() { return m_isExtended; };

    std::string getText();
    void setText(std::string text);
    int getId();
    void setId(int itemId);
    ItemUseType getUseType();
    void setUseType(ItemUseType useType);
    bool getSendAutomatically();
    void setSendAutomatically(bool automatically);
private:
    uint32_t m_id;
    uint32_t m_address;
    bool m_isExtended = false;
};
}

#endif // KEYBINDING_OBJ_H
