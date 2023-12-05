
#ifndef VERSIONS_H
#define VERSIONS_H

#include <string>
#include <windows.h>

namespace Addresses {


class Versions
{
public:
    static bool isSupportedVersion(std::string versionString);
    static void setVersion(std::string versionString);

    static std::string getVersion(HANDLE& handle, uint32_t baseAddress);
private:
    static void setV130512827(uint32_t baseAddress);
    static void setV131012892(uint32_t baseAddress);
    static void setV132013560(uint32_t baseAddress);
    static void setV132113743(uint32_t baseAddress);
    static void setV132013709(uint32_t baseAddress);
    static void setV132013623(uint32_t baseAddress);
    static void setV132113775(uint32_t baseAddress);
    static void setV132113810(uint32_t baseAddress);
    static void setV132113839(uint32_t baseAddress);
    static void setV132114172(uint32_t baseAddress);
    static void setV132214282(uint32_t baseAddress);
    static void setV132214366(uint32_t baseAddress);

    static void setOffsetsA();
    static void setOffsetsB();
    static void setOffsetsC();
};

}
#endif // VERSIONS_H
