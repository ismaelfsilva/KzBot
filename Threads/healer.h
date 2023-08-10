
#ifndef HEALER_THREAD_H
#define HEALER_THREAD_H

#include <thread>
#include "../Settings/globals.h"

namespace Threads
{

class Healer
{
public:
    Healer();
    ~Healer();

    void Start();
    void Stop();

private:
    std::thread m_healerThread;
    bool m_threadStatus = false;
    void m_threadFunc();
    ScriptConfig *scriptConfig;
};

}

#endif // HEALER_THREAD_H
