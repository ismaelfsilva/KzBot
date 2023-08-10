#ifndef ACTIONSETTINGS_H
#define ACTIONSETTINGS_H

#include <string>



class actionSettings
{
public:
    actionSettings();

    void setActionBarId(int actionBarId) { actionBar = actionBarId; };
    void setActionBarButtonId(int buttonId) { actionButton = buttonId; };
    void setUseObjectId(int objectId) { useObject = objectId; };
    void setChatText(std::string text) { chatText = text; };
    void setUseType(std::string type) { useType = type; };

    void setHotkeyChatOn(uint32_t key) { hotkeyChatOn = key; };
    void setHotkeyChatOff(uint32_t key) { hotkeyChatOff = key; };
    uint32_t getHotkeyChatOn() const { return hotkeyChatOn; }
    uint32_t getHotkeyChatOff() const { return hotkeyChatOff; }

    void setHotkeyChatOnExtended(bool extended) { hotkeyChatOnExtended = extended; };
    void setHotkeyChatOffExtended(bool extended) { hotkeyChatOffExtended = extended; };
    bool getHotkeyChatOnExtended() const { return hotkeyChatOnExtended; }
    bool getHotkeyChatOffExtended() const { return hotkeyChatOffExtended; }

    int getActionBarId() const { return actionBar; }
    int getActionBarButtonId() const { return actionButton; }
    int getUseObjectId() const { return useObject; }
    std::string getChatText() const { return chatText; }
    std::string getUseType() const { return useType; }

    void updateHotkey();

private:
    int actionBar;
    int actionButton;

    uint32_t hotkeyChatOn = 0;
    bool hotkeyChatOnExtended = false;

    uint32_t hotkeyChatOff = 0;
    bool hotkeyChatOffExtended = false;

    int useObject;
    std::string useType;
    std::string chatText;
};

#endif // ACTIONSETTINGS_H
