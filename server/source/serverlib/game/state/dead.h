#pragma once 

#include <game/state/state.h>

class Active;
class Passive;

class Dead : public State
{
public:
    Dead(Active& old);
    Dead(Passive& old);
};
