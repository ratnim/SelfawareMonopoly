#pragma once

#include <game/state/state.h>

class Enter : public State
{
public:
    Enter(Player& player);

    void ready(bool ready);
	bool isReady() const;

protected:
    bool m_ready = false;
};
