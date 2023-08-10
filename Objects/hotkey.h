#ifndef HOTKEY_OBJ_H
#define HOTKEY_OBJ_H


#include "keybinding.h"
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <Qt>
#include "../Util/Enums.h"

namespace Objects
{

class Hotkey
{
public:
    Hotkey(uint32_t address, int actionBarId);

    std::string getText();
    std::string getName() { return m_name; };
    int getId();
    bool getTextSendAutomatically();
    int getItemId();
    ItemUseType getUseType();
    bool isItem();
    KeyBinding* getKeyBinding(std::unordered_map<std::string, KeyBinding*>& keyBindingMap);

    void setText(std::string text);
    void setItem(int itemId, int useType);
private:
    uint32_t m_address;
    std::string m_name;
    uint32_t m_actionBarId;
    Qt::Key m_key;
};

}
#endif // HOTKEY_OBJ_H
