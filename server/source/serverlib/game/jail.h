#pragma once

class Jail
{
public:
    bool inJail();
    bool escape();
protected:
    bool m_jailed;
    int m_turns;
};
