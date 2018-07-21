#include "dead.h"

#include <game/state/active.h>
#include <game/state/passive.h>

Dead::Dead(Active& old)
    : State(old)
{
}

Dead::Dead(Passive& old)
    : State(old)
{
}
