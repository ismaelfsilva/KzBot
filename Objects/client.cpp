#include "client.h"
#include "../Util/kzhelper.h"
#include "../Settings/globals.h"
#include "../Addresses/client.h"
#include "../Settings/actionsettings.h"
#include "game.h"
#include "hotkey.h"
#include "keybinding.h"
#include "player.h"
#include "cooldown.h"
#include "hotkey.h"
#include "qjsonobject.h"
#include "battlelist.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <iostream>
#include <vector>
#include <QKeySequence>

using namespace Objects;


Point *Client::m_equipmentPoint = NULL;
RECT *Client::m_gameScreenRect = nullptr;
int Client::m_gameScreenTileSize;
int Client::m_gameScreenHalfTileSize;
Point *Client::m_gameScreenPlayerPoint;
std::vector<actionSettings*> Client::m_hotkeys = std::vector<actionSettings*>();


uint32_t Client::getDataPointer()
{
    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), Addresses::Client::getDataPointer());
}

Player* Client::getPlayer(uint32_t dataPointer)
{
    uint32_t playerPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Client::getPlayerPointer());

    return new Player(playerPointer);
}

Creature *Client::getPlayerCreature(uint32_t dataPointer)
{
    uint32_t playerCreaturePointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Client::getPlayerCreaturePointer());

    return new Creature(0, playerCreaturePointer);
}

int Client::getPing(uint32_t dataPointer)
{
    std::vector<uint32_t> m_pingAddr = Addresses::Client::getPing();
    uint32_t addr = dataPointer;

    for (uint32_t offset : m_pingAddr)
        addr = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), addr + offset);

    return addr;
}

uint64_t Client::getGameTime(uint32_t dataPointer)
{
    Creature* playerCreature = getPlayerCreature(dataPointer);
    int gameTime = playerCreature->getGameTime();

    delete playerCreature;
    return gameTime;
}

std::vector<Cooldown*> Client::getCooldowns(uint32_t dataPointer)
{
    std::vector<Cooldown*> cooldownList;

    uint32_t cooldownsPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Client::getCooldownsPointer());
    std::map<uint32_t, uint32_t> qtCollection = Util::KzHelper::readQtCollection(cooldownsPointer + Addresses::Client::getCooldownsSpellsCollection());

    if (qtCollection.empty())
        return cooldownList;

    for (auto cdAddr : qtCollection)
    {
        Cooldown* c = new Cooldown(cdAddr.first, cdAddr.second);
        cooldownList.push_back(c);
    }

    return cooldownList;
}

Cooldown* Client::getCooldown(uint32_t dataPointer, int cId)
{
    std::vector<Cooldown*> cooldownList = getCooldowns(dataPointer);
    for (Cooldown* cd : cooldownList)
    {
        if (cd->id() == cId)
            return cd;
    }

    return nullptr;
}

std::vector<Cooldown*> Client::getCooldownGroups(uint32_t dataPointer)
{
    std::vector<Cooldown*> cooldownList;

    uint32_t cooldownsPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Client::getCooldownsPointer());
    std::map<uint32_t, uint32_t> qtCollection = Util::KzHelper::readQtCollection(cooldownsPointer + Addresses::Client::getCooldownsGroupCollection());

    if (qtCollection.empty())
        return cooldownList;

    for (auto cdAddr : qtCollection)
    {
        Cooldown* c = new Cooldown(cdAddr.first, cdAddr.second);
        cooldownList.push_back(c);
    }

    return cooldownList;
}

Cooldown* Client::getCooldownGroup(uint32_t dataPointer, int cId)
{
    std::vector<Cooldown*> cooldownList = getCooldownGroups(dataPointer);
    for (Cooldown* cd : cooldownList)
    {
        if (cd->id() == cId)
            return cd;
    }

    return nullptr;
}

Cooldown* Client::getCooldownGroup(uint32_t dataPointer, CooldownGroup group)
{
    std::vector<Cooldown*> cooldownList = getCooldownGroups(dataPointer);
    for (Cooldown* cd : cooldownList)
    {
        if (cd->group() == group)
            return cd;
    }

    return nullptr;
}

void Client::updateGameScreenRect()
{
    RECT rect;
    GetClientRect(Globals::getHWnd(), &rect);
    int nScreenWidth = rect.right - rect.left;
    int nScreenHeight = rect.bottom - rect.top;

    RGBQUAD* rgb = Util::KzHelper::getRGBQuad();

    // Find First Pixel
    int firstPixelY = 170;
    int topLeftColor = 25;
    int topLeftColorTolerance = 15;

    int bottomRightColor = 115;
    int bottomRightColorTolerance = 25;

    for (int firstPixelX = 0; firstPixelX < nScreenWidth; firstPixelX++)
    {
        int foundCorrectColorQty = 0;
        for (int leftPixelY = firstPixelY; leftPixelY < nScreenHeight; leftPixelY++)
        {
            int pos = (nScreenHeight-leftPixelY-1)*nScreenWidth+firstPixelX;

            int r = rgb[pos].rgbRed;
            int g = rgb[pos].rgbGreen;
            int b = rgb[pos].rgbBlue;

            if (abs(r - topLeftColor) < topLeftColorTolerance && abs(g - topLeftColor) < topLeftColorTolerance && abs(b - topLeftColor) < topLeftColorTolerance)
                foundCorrectColorQty++;
            else if (foundCorrectColorQty > 10)
            {
                foundCorrectColorQty = 0;
                firstPixelX++;
                leftPixelY--;
                for (int lastPixelX = firstPixelX + 200; lastPixelX < nScreenWidth; lastPixelX++)
                {
                    pos = (nScreenHeight-leftPixelY-1)*nScreenWidth+lastPixelX;

                    r = rgb[pos].rgbRed;
                    g = rgb[pos].rgbGreen;
                    b = rgb[pos].rgbBlue;

                    if (abs(r - bottomRightColor) < bottomRightColorTolerance && abs(g - bottomRightColor) < bottomRightColorTolerance && abs(b - bottomRightColor) < bottomRightColorTolerance)
                        foundCorrectColorQty++;
                    else if (foundCorrectColorQty > 10)
                    {
                        foundCorrectColorQty = 0;
                        lastPixelX--;

                        for (int rightPixelY = leftPixelY - 150; rightPixelY > 0; rightPixelY--)
                        {
                            pos = (nScreenHeight-rightPixelY-1)*nScreenWidth+lastPixelX;

                            r = rgb[pos].rgbRed;
                            g = rgb[pos].rgbGreen;
                            b = rgb[pos].rgbBlue;

                            if (abs(r - bottomRightColor) < bottomRightColorTolerance && abs(g - bottomRightColor) < bottomRightColorTolerance && abs(b - bottomRightColor) < bottomRightColorTolerance)
                                foundCorrectColorQty++;
                            else if (foundCorrectColorQty > 10)
                            {
                                rightPixelY++;

                                RECT* gameScreenRect = new RECT();
                                gameScreenRect->left = firstPixelX - 8;
                                gameScreenRect->bottom = leftPixelY - 32;
                                gameScreenRect->right = lastPixelX - 8;
                                gameScreenRect->top = rightPixelY - 32;

                                setGameScreenRect(gameScreenRect);
                                setGameScreenTileSize((gameScreenRect->right - gameScreenRect->left) / 15);
                                setGameScreenHalfTileSize(((gameScreenRect->right - gameScreenRect->left) / 15) / 2);
                                Point* playerPoint = new Point(0);
                                playerPoint->x = gameScreenRect->left + (gameScreenRect->right - gameScreenRect->left) / 2;
                                playerPoint->y = gameScreenRect->top + (gameScreenRect->bottom - gameScreenRect->top) / 2;
                                setGameScreenPlayerPoint(playerPoint);
                                break;
                            }
                            else
                                break;
                        }

                        break;
                    }
                    else
                        break;
                }
                break;
            }
            else
                break;
        }
    }

    delete [] rgb;
}

void Client::updateEquipmentPoint()
{
    RECT rect;
    GetWindowRect(Globals::getHWnd(), &rect);
    int nScreenWidth = 200;
    int nScreenHeight = rect.bottom - rect.top;

    RGBQUAD* rgb = Util::KzHelper::getRGBRightQuad();

    for (int x = 0; x < nScreenWidth; x++)
    {
        for (int y = 0; y < nScreenHeight; y++)
        {
            int p1 = (nScreenHeight-y-1)*nScreenWidth+x;

            int r1 = rgb[p1].rgbRed;
            int g1 = rgb[p1].rgbGreen;
            int b1 = rgb[p1].rgbBlue;

            if (r1 == 112 && g1 == 112 && b1 == 113)
            {
                int p2 = (nScreenHeight-y-1)*nScreenWidth+x+74;

                int r2 = rgb[p2].rgbRed;
                int g2 = rgb[p2].rgbGreen;
                int b2 = rgb[p2].rgbBlue;

                if (r2 == 43 && g2 == 101 && b2 == 151)
                    setEquipmentPoint(new Point(x, y));
            }
        }
    }

    delete [] rgb;
}

std::pair<AmuletType, RingType> Client::getEquipmentInfo()
{
    RECT rect;
    GetWindowRect(Globals::getHWnd(), &rect);
    int nScreenWidth = 200;
    int nScreenHeight = rect.bottom - rect.top;

    RGBQUAD* rgb = Util::KzHelper::getRGBRightQuad();
    Point *equipmentPoint = getEquipmentPoint();

    if (nScreenHeight < 200)
    {
        delete [] rgb;
        return std::pair<AmuletType, RingType>((AmuletType)-1, (RingType)-1);
    }


    int amuletPoint = (nScreenHeight-(equipmentPoint->y + 37)-1)*nScreenWidth+(equipmentPoint->x + 17);
    int amuletR = rgb[amuletPoint].rgbRed;

    int ringPoint = (nScreenHeight-(equipmentPoint->y + 100)-1)*nScreenWidth+(equipmentPoint->x + 16);
    int ringR = rgb[ringPoint].rgbRed;

    delete [] rgb;

    return std::pair<AmuletType, RingType>((AmuletType)amuletR, (RingType)ringR);
}

bool Client::getEquipmentInfo(std::pair<AmuletType, RingType>& output)
{
    RECT rect;
    GetWindowRect(Globals::getHWnd(), &rect);
    int nScreenWidth = 200;
    int nScreenHeight = rect.bottom - rect.top;

    RGBQUAD* rgb = Util::KzHelper::getRGBRightQuad();
    Point *equipmentPoint = getEquipmentPoint();

    if (nScreenHeight < 200)
    {
        delete [] rgb;
        output = std::pair<AmuletType, RingType>((AmuletType)-1, (RingType)-1);
        return false;
    }


    int amuletPoint = (nScreenHeight-(equipmentPoint->y + 37)-1)*nScreenWidth+(equipmentPoint->x + 17);
    int amuletR = rgb[amuletPoint].rgbRed;

    int ringPoint = (nScreenHeight-(equipmentPoint->y + 100)-1)*nScreenWidth+(equipmentPoint->x + 16);
    int ringR = rgb[ringPoint].rgbRed;

    delete [] rgb;

    output = std::pair<AmuletType, RingType>((AmuletType)amuletR, (RingType)ringR);
    return false;
}

std::string Client::getCurrentHotkeySetNameFromFile()
{
    std::filesystem::path path = Util::KzHelper::getWindowPath(Globals::getHWnd()).parent_path().parent_path();

    std::string filePath = path.string();
    filePath.append("\\conf\\clientoptions.json");

    QFile file;
    file.setFileName(QString::fromLatin1(filePath));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val);
    QJsonObject jObject = doc.object();
    QVariantMap mainMap = jObject.toVariantMap();

    return mainMap["hotkeyOptions"].toJsonObject()["currentHotkeySetName"].toString().toStdString();
}

void Client::updateHotkeysFromFile()
{
    keybd_event(VK_CONTROL, 0x9d, 0, 0);
    Sleep(1);
    SendMessage(Globals::getHWnd(), WM_KEYDOWN, 0x4B, 0);
    Sleep(1);
    SendMessage(Globals::getHWnd(), WM_KEYUP, 0x4B, 0);
    Sleep(1);
    keybd_event(VK_CONTROL, 0x9d, KEYEVENTF_KEYUP, 0);
    Sleep(1);
    Util::KzHelper::SendKey(VK_ESCAPE);
    Sleep(500);

    std::filesystem::path path = Util::KzHelper::getWindowPath(Globals::getHWnd()).parent_path().parent_path();

    std::string filePath = path.string();
    filePath.append("\\conf\\clientoptions.json");

    QFile file;
    file.setFileName(QString::fromLatin1(filePath));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray val = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(val);
    QJsonObject jObject = doc.object();
    QVariantMap mainMap = jObject.toVariantMap();


    QVariantMap hotkeyOptions = mainMap["hotkeyOptions"].toJsonObject().toVariantMap();
    QString currentHotkeySetName = hotkeyOptions["currentHotkeySetName"].toString();

    QVariantMap hotkeySets = hotkeyOptions["hotkeySets"].toJsonObject().toVariantMap();
    QVariantMap hotkeyCurrentSet = hotkeySets[currentHotkeySetName].toJsonObject().toVariantMap();

    QJsonArray hotkeyActionBarMapping = hotkeyCurrentSet["actionBarOptions"].toJsonObject()["mappings"].toArray();
    QJsonArray hotkeyChatOffOptions = hotkeyCurrentSet["chatOff"].toJsonArray();
    QJsonArray hotkeyChatOnOptions = hotkeyCurrentSet["chatOn"].toJsonArray();

    for (auto hotkey : m_hotkeys)
        delete hotkey;

    m_hotkeys.clear();

    for (QJsonValue setting : hotkeyActionBarMapping)
        parseHotkey(setting);
    for (QJsonValue setting : hotkeyChatOffOptions)
        parseHotkey(setting, false);
    for (QJsonValue setting : hotkeyChatOnOptions)
        parseHotkey(setting, true);
}

void Client::parseHotkey(QJsonValue& jsonValue, int chatStatus)
{
    QVariantMap settingMap = jsonValue.toObject().toVariantMap();
    QVariantMap actionSettingMap = settingMap["actionsetting"].toJsonObject().toVariantMap();

    if (!actionSettingMap["action"].isValid())
    {
        actionSettings* actionSettings = new class actionSettings();
        actionSettings->setActionBarId(settingMap["actionBar"].toInt());
        actionSettings->setActionBarButtonId(settingMap["actionButton"].toInt());

        if (actionSettingMap["chatText"].isValid())
            actionSettings->setChatText(actionSettingMap["chatText"].toString().toStdString());
        if (actionSettingMap["useObject"].isValid())
            actionSettings->setUseObjectId(actionSettingMap["useObject"].toInt());
        if (actionSettingMap["useType"].isValid())
            actionSettings->setUseType(actionSettingMap["useType"].toString().toStdString());

        // Tem Hotkey
        if (settingMap["keysequence"].isValid())
        {
            std::string keySeqString = settingMap["keysequence"].toString().toStdString();
            uint32_t virtualKey = Util::KzHelper::stringToVK(keySeqString);
            bool virtualKeyExtended = Util::KzHelper::stringVKisExtended(keySeqString);

            if (keySeqString.find("+") == std::string::npos || keySeqString.find("Num+") != std::string::npos)
            {
                if (chatStatus == true)
                {
                    actionSettings->setHotkeyChatOn(virtualKey);
                    actionSettings->setHotkeyChatOnExtended(virtualKeyExtended);
                }
                else if (chatStatus == false)
                {
                    actionSettings->setHotkeyChatOff(virtualKey);
                    actionSettings->setHotkeyChatOffExtended(virtualKeyExtended);
                }
            }
        }

        m_hotkeys.push_back(actionSettings);
    }
    else
    {
        std::string action = actionSettingMap["action"].toString().toStdString();

        int actionBarId = 0;
        int actionBarButtonId = 0;
        actionSettings* actionSettings = NULL;

        if (!action._Starts_with("TriggerActionButton_"))
            return;

        std::string s = action.substr(20);
        actionBarId = std::stoi(s.substr(0, s.find(".")));
        actionBarButtonId = std::stoi(s.substr(s.find(".") + 1));

        for (auto hotkey : m_hotkeys)
        {
            if (hotkey->getActionBarId() == actionBarId && hotkey->getActionBarButtonId() == actionBarButtonId)
                actionSettings = hotkey;
        }
        if (actionSettings == NULL)
            return;

        // Tem Hotkey
        if (settingMap["keysequence"].isValid())
        {
            std::string keySeqString = settingMap["keysequence"].toString().toStdString();
            uint32_t virtualKey = Util::KzHelper::stringToVK(keySeqString);
            bool virtualKeyExtended = Util::KzHelper::stringVKisExtended(keySeqString);

            if (keySeqString.find("+") == std::string::npos || keySeqString.find("Num+") != std::string::npos)
            {
                if (chatStatus == true)
                {
                    actionSettings->setHotkeyChatOn(virtualKey);
                    actionSettings->setHotkeyChatOnExtended(virtualKeyExtended);
                }
                else if (chatStatus == false)
                {
                    actionSettings->setHotkeyChatOff(virtualKey);
                    actionSettings->setHotkeyChatOffExtended(virtualKeyExtended);
                }
            }
        }
    }

}

actionSettings* Client::getHotkeyByText(std::string words)
{
    QString wordsText = QString::fromStdString(words);
    for (actionSettings* setting : m_hotkeys)
    {
        QString chatText = QString::fromStdString(setting->getChatText());
        if (chatText.toLower().endsWith(wordsText.toLower()))
            return setting;
    }

    return NULL;
}

actionSettings* Client::getHotkeyByItemId(int itemId)
{
    for (actionSettings* setting : m_hotkeys)
    {
        if (setting->getUseObjectId() == itemId)
            return setting;
    }

    return NULL;
}

actionSettings* Client::getHotkeyByItemId(int itemId, std::string useType)
{
    for (actionSettings* setting : m_hotkeys)
    {
        if (setting->getUseObjectId() == itemId && (useType.empty() || setting->getUseType() == useType))
            return setting;
    }

    return NULL;
}

ChatStatus Client::getChatStatus(uint32_t dataPointer)
{
    std::vector<uint32_t> m_uiChatStatusAddr = Addresses::Client::getUiChatStatus();
    uint32_t addr = dataPointer;

    for (uint32_t offset : m_uiChatStatusAddr)
    {
        addr = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), addr + offset);
    }

    return (ChatStatus)addr;
}

std::string Client::getCurrentUiText()
{
    std::vector<uint32_t> m_uiCurrentTextAddr = Addresses::Client::getUiCurrentText();
    uint32_t addr = 0x0;

    for (uint32_t offset : m_uiCurrentTextAddr)
    {
        addr = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), addr + offset);
        if (addr <= 0x10)
            return "";
    }

    return Util::KzHelper::ReadMemoryStringUnicode(Globals::getHandle(), addr + 0x10);
}

void Client::setCurrentUiText(std::string text)
{
    std::vector<uint32_t> m_uiCurrentTextAddr = Addresses::Client::getUiCurrentText();
    uint32_t addr = 0x0;

    for (uint32_t offset : m_uiCurrentTextAddr)
    {
        addr = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), addr + offset);

        if (addr <= 0x10)
            return;
    }

    //Util::KzHelper::WriteMemoryInt32(Globals::getHandle(), addr + 0x4, text.length());
    Util::KzHelper::WriteMemoryStringUnicode(Globals::getHandle(), addr + 0x10, text);
}

bool Client::getClientFocus()
{
    std::vector<uint32_t> m_clientFocusAddr = Addresses::Client::getClientFocus();
    uint32_t addr = 0x0;

    for (uint32_t offset : m_clientFocusAddr)
        addr = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), addr + offset);

    return Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), addr + 0x1C);
}

void Client::setClientFocus(bool focus)
{
    std::vector<uint32_t> m_clientFocusAddr = Addresses::Client::getClientFocus();
    uint32_t addr = 0x0;

    for (uint32_t offset : m_clientFocusAddr)
        addr = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), addr + offset);

    Util::KzHelper::WriteMemoryUInt32(Globals::getHandle(), addr + 0x1C, (int)focus);
}



std::map<InventorySlot, InventoryItem *> Client::getInventoryItems()
{
    std::map<InventorySlot, InventoryItem *> inventoryItems;

    uint32_t inventoryPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), Addresses::Client::getInventoryPointer());

    auto inventoryDataList = Util::KzHelper::readQtCollection(inventoryPointer);
    for (auto itemData : inventoryDataList)
    {
        uint32_t itemPointer = itemData.first;

        for (uint32_t offset : Addresses::Client::getInventoryPathToItem())
            itemPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), itemPointer + offset);

        InventoryItem* item = new InventoryItem(itemPointer);

        if (item->isEquipped())
            inventoryItems[item->getSlot()] = item;
        else
            delete item;
    }

    return inventoryItems;
}



Point* Client::getSqmPoint(uint32_t dataPointer, Position pos)
{
    return getSqmPoint(dataPointer, pos.X(), pos.Y());
}

Point* Client::getSqmPoint(uint32_t dataPointer, int x, int y)
{
    Creature* p = getPlayerCreature(dataPointer);
    int diffX = x - p->getX();
    int diffY = y - p->getY();

    if (abs(diffX) > 7 || abs(diffY) > 5)
        return nullptr;

    Point* sqmPoint = new Point(0);
    sqmPoint->x = getGameScreenPlayerPoint()->x + (diffX * getGameScreenTileSize());
    sqmPoint->y = getGameScreenPlayerPoint()->y + (diffY * getGameScreenTileSize());

    return sqmPoint;
}

void Client::Target(uint32_t dataPointer, uint32_t cId)
{
    Creature* c = nullptr;

    for (auto creatureEntity : Objects::Battlelist::getCreaturesOnScreen(dataPointer))
    {
        Creature* cr = creatureEntity.second;
        if (cr->getId() == cId)
            c = cr;
    }

    if (c != nullptr)
        Target(dataPointer, c);
}

void Client::Target(uint32_t dataPointer, Creature *c)
{
    Target(dataPointer, c->getPosition());
}

void Client::Target(uint32_t dataPointer, Position p)
{
    Point* targetPoint = getSqmPoint(dataPointer, p);
    if (targetPoint == nullptr)
        return;

    keybd_event(VK_MENU, 0xb8, 0, 0);
    Sleep(1);
    Util::KzHelper::LeftClick(targetPoint);
    keybd_event(VK_MENU, 0xb8, KEYEVENTF_KEYUP, 0);

    delete targetPoint;
}

std::string Client::getCurrentHotkeyName(uint32_t dataPointer)
{
    std::vector<uint32_t> m_currentHotkeyName = Addresses::Client::getCurrentHotkeyName();
    uint32_t addr = dataPointer;

    for (uint32_t offset : m_currentHotkeyName)
    {
        addr = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), addr + offset);
    }

    return Util::KzHelper::ReadMemoryStringUnicode(Globals::getHandle(), addr + 0x10);
}

void Client::updateHotkeys()
{
    // Hotkeys Data
    std::vector<KeyBinding*> keyBindings = Objects::Client::getKeyBindings();
    std::unordered_map<std::string, KeyBinding*> keyBindingsByName;
    for (KeyBinding* k : keyBindings)
    {
        keyBindingsByName[k->getName()] = k;
    }
    std::vector<CachedHotkey> hotkeys;

    for (Hotkey* h : Objects::Client::getHotkeys())
    {
        CachedHotkey _h;
        _h.name = h->getName();

        KeyBinding* keyBinding = keyBindingsByName[_h.name];
        if (keyBinding == nullptr)
        {
            delete h;
            continue;
        }

        _h.key = keyBinding->getKey(_h.extended);

        int hItemId = h->getItemId();
        if (hItemId > 0)
        {
            _h.itemId = hItemId;
            _h.useType = h->getUseType();
        }
        else if (h->getTextSendAutomatically())
        {
            _h.text = h->getText();
        }

        hotkeys.push_back(_h);
        delete h;
    }

    Objects::Game::setHotkeys(hotkeys);

    for (KeyBinding* k : keyBindings)
        delete k;
    keyBindings.clear();
    keyBindingsByName.clear();
}

void Client::Say(std::string text)
{

}

std::vector<KeyBinding*> Client::getKeyBindings()
{
    std::vector<KeyBinding*> keyBindings;

    /*
    uint32_t dataPointer = getDataPointer();
    uint32_t hotkeyCollection = dataPointer;
    for (uint32_t offset : Addresses::Client::getKeyBindingCollection())
        hotkeyCollection = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), hotkeyCollection + offset);
    std::vector<uint32_t> hotkeyPresetQtCollection = Util::KzHelper::readQtCollection(hotkeyCollection);

    for (uint32_t hotkeyAddr : hotkeyPresetQtCollection)
    {
        Objects::KeyBinding* keyBinding = new Objects::KeyBinding(hotkeyAddr);
        keyBindings.push_back(keyBinding);
    }
    */

    return keyBindings;
}

KeyBinding* Client::getKeyBindingByKey(uint32_t key)
{
    uint32_t dataPointer = getDataPointer();
    uint32_t keyBindingCollectionClass = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Client::getKeyBindingCollection()[0]);
    std::map<uint32_t, uint32_t> keyBindingsQtCollection = Util::KzHelper::readQtCollection(keyBindingCollectionClass + Addresses::Client::getKeyBindingCollection()[1]);

    for (auto keyBindingEntry : keyBindingsQtCollection)
    {
        Objects::KeyBinding* keyBinding = new Objects::KeyBinding(keyBindingEntry.first, keyBindingEntry.second);

        bool ext;
        if (keyBinding->getKey(ext) == key)
            return keyBinding;
        else
            delete keyBinding;
    }

    return nullptr;
}

std::vector<Hotkey*> Client::getHotkeys()
{
    std::vector<Hotkey*> hotkeyList;

    /*
    uint32_t dataPointer = getDataPointer();
    uint32_t hotkeyPresetCollection = dataPointer;
    for (uint32_t offset : Addresses::Client::getHotkeyPresetCollection())
        hotkeyPresetCollection = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), hotkeyPresetCollection + offset);
    std::vector<uint32_t> hotkeyPresetQtCollection = Util::KzHelper::readQtCollection(hotkeyPresetCollection);

    for (uint32_t presetAddr : hotkeyPresetQtCollection)
    {
        uint32_t presetNamePointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), presetAddr + Addresses::Client::getHotkeyCollectionName());
        std::string presetName = Util::KzHelper::ReadMemoryStringUnicode(Globals::getHandle(), presetNamePointer + 0x10);

        if (presetName != getCurrentHotkeyName())
            continue;

        uint32_t presetHotkeyActionBarCollection = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), presetAddr + Addresses::Client::getHotkeyActionBarCollection());
        std::vector<uint32_t> presetHotkeyActionBarQtCollection = Util::KzHelper::readQtCollection(presetHotkeyActionBarCollection);

        for (uint32_t actionBarAddr : presetHotkeyActionBarQtCollection)
        {
            uint32_t actionBarRow = Util::KzHelper::ReadMemoryByte(Globals::getHandle(), actionBarAddr + 0x8);
            if (actionBarRow <= 0 || actionBarRow > 12)
                continue;

            uint32_t actionBarHotkeyCollection = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), actionBarAddr + Addresses::Client::getHotkeyCollection());
            std::vector<uint32_t> actionBarHotkeyQtCollection = Util::KzHelper::readQtCollection(actionBarHotkeyCollection);

            for (uint32_t hotkeyAddr : actionBarHotkeyQtCollection)
            {
                Hotkey* h = new Hotkey(hotkeyAddr, actionBarRow);

                int hId = h->getId();

                if (hId <= 0 || hId > 255)
                {
                    delete h;
                    continue;
                }

                hotkeyList.push_back(h);
            }
        }
    }
    */

    return hotkeyList;
}



void Client::Turn(Direction dir)
{
    uint32_t k = 0x0;
    if (dir == Direction::NORTH)
        k = VK_UP;
    else if (dir == Direction::EAST)
        k = VK_RIGHT;
    else if (dir == Direction::SOUTH)
        k = VK_DOWN;
    else if (dir == Direction::WEST)
        k = VK_LEFT;

    Objects::Client::setClientFocus(true);
    keybd_event(VK_CONTROL, 0x9d, 0, 0);
    Sleep(10);
    Util::KzHelper::SendKey(k, true);
    keybd_event(VK_CONTROL, 0x9d, KEYEVENTF_KEYUP, 0);
}

void Client::Goto(Position p)
{
    uint32_t dataPointer = getDataPointer();
    uint32_t gotoDataPointer = Util::KzHelper::ReadMemoryUInt32(Globals::getHandle(), dataPointer + Addresses::Client::getGotoData());

    Util::KzHelper::WriteMemoryUInt32(Globals::getHandle(), gotoDataPointer + Addresses::Client::getGotoX(), p.X());
    Util::KzHelper::WriteMemoryUInt32(Globals::getHandle(), gotoDataPointer + Addresses::Client::getGotoY(), p.Y());
    Util::KzHelper::WriteMemoryUInt32(Globals::getHandle(), gotoDataPointer + Addresses::Client::getGotoZ(), p.Z());
    Util::KzHelper::WriteMemoryByte(Globals::getHandle(), gotoDataPointer + Addresses::Client::getGotoIsWalking(), 1);
}
