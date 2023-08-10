#ifndef UPDATER_H
#define UPDATER_H

#include <thread>
#include "../Settings/scriptconfig.h"
#include "healer.h"
#include "partyhunt.h"
#include "pvptools.h"
#include "qwindowdefs_win.h"
#include "tools.h"

namespace Threads
{
class Updater : public QObject
{
    Q_OBJECT

public:
    Updater();
    ~Updater();

    void Start();
    void Stop();

signals:
    void hasFocus(const HWND& HWnd);
    void loadSetting(const QString& fileName);
    void changeStatus(const QString& statusName);

private:
    std::thread m_updaterThread;
    std::thread m_actionThread;

    bool m_threadStatus = false;
    void m_threadFunc();
    void m_actionThreadFunc();

    int m_tickCount = 0;
    ScriptConfig *scriptConfig;
    HWND m_lastForegroundWindow;
    int m_lastHotkeyTick = 0;
};
};
#endif // UPDATER_H
