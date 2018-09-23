
#pragma once

#include <memory>
#include <vector>

#include <game/card.h>


class CardStack
{
public:
    CardStack(std::vector<Card*>&& stack);

    static CardStack chanceStack();
    static CardStack societyStack();

    Card& draw();

protected:
    void shuffle();

protected:
    std::vector<Card*> m_stack;
    std::vector<Card*>::iterator m_next;
};
