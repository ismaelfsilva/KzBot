
#ifndef PARTYHUNT_THREAD_H
#define PARTYHUNT_THREAD_H

#include <thread>
#include "../Settings/globals.h"

namespace Threads
{

class PartyHunt
{
public:
    PartyHunt();
    ~PartyHunt();

    void Start();
    void Stop();

private:
    std::thread m_partyHuntThread;
    bool m_threadStatus = false;
    void m_threadFunc();
    ScriptConfig *scriptConfig;
};

}

#endif // PARTYHUNT_THREAD_H
