
#ifndef VERSIONS_H
#define VERSIONS_H

#include <string>

namespace Addresses {


class Versions
{
public:
    static bool isSupportedVersion(std::string versionString);
    static void setVersion(std::string versionString);
private:
    static void setV131012892(uint32_t baseAddress);
    static void setV131213018(uint32_t baseAddress);
    static void setV131713405(uint32_t baseAddress);
    static void setV132013560(uint32_t baseAddress);
    static void setV132013623(uint32_t baseAddress);
};

}
#endif // VERSIONS_H
