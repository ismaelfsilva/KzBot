#ifndef PVPTOOLS_THREAD_H
#define PVPTOOLS_THREAD_H

#include <thread>
#include "../Settings/globals.h"

namespace Threads
{
class PvPTools
{
public:
    PvPTools();
    ~PvPTools();

    void Start();
    void Stop();

private:
    std::thread m_pvpToolsThread;
    bool m_threadStatus = false;
    void m_threadFunc();
    ScriptConfig *scriptConfig;
};
};
#endif // PVPTOOLS_THREAD_H
