#ifndef TOOLS_THREAD_H
#define TOOLS_THREAD_H

#include <thread>
#include "../Settings/globals.h"

namespace Threads
{
class Tools
{
public:
    Tools();
    ~Tools();

    void Start();
    void Stop();

private:
    std::thread m_toolsThread;
    bool m_threadStatus = false;
    void m_threadFunc();
    ScriptConfig *scriptConfig;
};
};
#endif // TOOLS_THREAD_H
