
#ifndef TARGETRULE_H
#define TARGETRULE_H

#include "healrule.h"
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

enum class TargetType
{
    None,
    SingleTarget,
    AreaSpell,
    AreaRune,
    Wave
};

enum class TargetArea
{
    None,
    Target,
    Small,
    Default,
    Ultimate
};

enum class CooldownType
{
    None,
    Heal,
    Attack,
    Support
};

class TargetRule : public ActionRule
{
public:
    TargetRule();


};

#endif // TARGETRULE_H
