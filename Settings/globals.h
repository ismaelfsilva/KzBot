
#ifndef GLOBALS_H
#define GLOBALS_H


#include "qjsonobject.h"
#include "qwindowdefs.h"
#include <cstdint>
#include <windows.h>
#include "../Objects/spell.h"
#include "scriptconfig.h"
#include "../Util/Enums.h"
#include "../Objects/position.h"


struct Point {
    int x, y;
    Point(int x_, int y_) {x = x_; y = y_;};
    Point(int x_) : x(x_), y(0) {}
    Point(const Point& p) : x(p.x), y(p.y) {}
    Point operator, (int y_) const { Point p=*this; p.y = y_; return p; }
};

class Input
{
public:
    std::string text;
    int itemId;
    uint64_t gameTime = 0;
    ItemUseType itemUseType;
    uint32_t targetId = 0;
    bool requiresRealTarget = false;
    bool usesCrosshair = false;
    bool canRepeat = false;
    Position position;
};

class Globals
{
public:
    Globals() {};
    ~Globals() { CloseHandle(m_handle); };

    static bool isSet;

    static ScriptConfig *getScriptConfig() { return m_scriptConfig; };
    static void resetScriptConfig() {
        delete m_scriptConfig;
        m_scriptConfig = new ScriptConfig();
    };

    static void setProcessId(int pId) { m_pId = pId; };
    static void setHandle(HANDLE handle) {
        if (m_handle != NULL) CloseHandle(m_handle);
        m_handle = handle;
    };
    static void setHWnd(HWND hWnd) { m_hWnd = hWnd; };
    static void setBaseAddress(uint32_t baseAddress) { m_baseAddress = baseAddress; };

    static int getProcessId() { return m_pId; };
    static HANDLE &getHandle() { return m_handle; };
    static HWND getHWnd() { return m_hWnd; };
    static uint32_t getBaseAddress() { return m_baseAddress; };

    static int getUserId() { return m_userId; }
    static void setUserId(const int& userId) { m_userId = userId; }

    static QString getUsername() { return m_username; }
    static void setUsername(const QString& username) { m_username = username; }

    static QString getEmail() { return m_email; }
    static void setEmail(const QString& email) { m_email = email; }

    static QString getPassword() { return m_password; }
    static void setPassword(const QString& password) { m_password = password; }

    static int getLoginTimestamp() { return m_loginTimestamp; }
    static void setLoginTimestamp(int timestamp) { m_loginTimestamp = timestamp; }

    static QString getUserSignature() { return m_userSignature; }
    static void setUserSignature(const QString& signature) { m_userSignature = signature; }

    static int getAuthErrorCount() { return m_authErrorCount; }
    static void setAuthErrorCount(int errorCount) { m_authErrorCount = errorCount; }
    static void increaseAuthErrorCount() { m_authErrorCount++; }

    static int getAuthSuccessCount() { return m_authSuccessCount; }
    static void setAuthSuccessCount(int count) { m_authSuccessCount = count; }
    static void increaseAuthSuccessCount() { m_authSuccessCount++; }

    static int getAuthTickCount() { return m_authTickCount; }
    static void setAuthTickCount(int count) { m_authTickCount = count; }
    static int increaseAuthTickCount() { return ++m_authTickCount; }

    static QJsonObject getUserObject() { return userObject; }
    static void setUserObject(const QJsonObject& obj) { userObject = obj; }

    static void closeHandle() {
        if (m_handle != NULL) CloseHandle(m_handle);
    };

    static void updateHotkeys();

    static Spell* getSpell(std::string value);
    static Spell* getSpell(int value);
    static std::vector<Spell*> Spells;
    static bool UpdateSpells();

    static int getInputCount() { return m_inputList.size(); };
    static std::vector<Input*>& getInputs() { return m_inputList; };
    static void removeFirstInput() { m_inputList.erase(m_inputList.begin()); };
    static void clearInputs() {
        std::remove(m_inputList.begin(), m_inputList.end(), nullptr);
    };
    static void addInput(Input* input) { m_inputList.push_back(input); };
    static std::string hash;
private:
    static int m_pId;
    static HANDLE m_handle;
    static HWND m_hWnd;
    static uint32_t m_baseAddress;

    static int m_userId;
    static QString m_username;
    static QString m_email;
    static QString m_password;
    static int m_loginTimestamp;
    static QString m_userSignature;
    static int m_authErrorCount;
    static int m_authSuccessCount;
    static int m_authTickCount;
    static QJsonObject userObject;

    static std::vector<Input*> m_inputList;
    static ScriptConfig *m_scriptConfig;
};

#endif // GLOBALS_H
