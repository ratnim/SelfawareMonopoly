#include "passive.h"

#include <game/state/State.h>
#include <game/state/active.h>

Passive::Passive(Enter old)
    : State(old)
{
}

Passive::Passive(Active old)
    : State(old)
    , m_jail(old.m_jail)
{
}
