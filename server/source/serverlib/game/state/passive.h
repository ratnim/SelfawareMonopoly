#pragma once

#include <game/state/enter.h>
#include <game/jail.h>

class Active;
class Passive : public State
{
    friend Active;

public:
    Passive(Active old);
    Passive(Enter old);

protected:
    Jail m_jail;
};
