
#include "cardstack.h"

#include <algorithm>
#include <random>

#include <game/game.h>
#include <game/turn/paystate.h>


CardStack::CardStack(std::vector<Card*>&& stack)
: m_stack(std::move(stack))
{
    shuffle();
}

CardStack CardStack::chanceStack()
{
    static std::vector<Card> s_cards {
       //{[](Game & game){game.doCurrentPlayerMove(-3); return true;}, "Move back 3 spaces."} // Excluded until backward movement is possible
       {[](Game & game){game.doCurrentPlayerEarnMoney(50); return false;}, "Banking error in your favour. You recieve $50."},
       {[](Game & game){game.stateChange<PayState, std::vector<Debt>>({{game.currentPlayer().name(), "", 20}}); return true;}, "Illegal parking, pay $20."}
    };

    // ugly, but the only way i could make it work
    std::vector<Card*> cards;
    std::transform(s_cards.begin(), s_cards.end(), std::back_inserter(cards), [](Card& card){return &card;});

    return {std::move(cards)};
}

CardStack CardStack::societyStack()
{
    return chanceStack(); // for now
    /*
    static std::vector<Card> s_cards {
        //...
    };

    std::vector<Card*> cards;
    std::transform(s_cards.begin(), s_cards.end(), std::back_inserter(cards), [](Card& card){return &card;});

    return {std::move(cards)};
    */
}

Card& CardStack::draw()
{
    if (m_next == m_stack.end())
        shuffle();

    return **m_next++;
}

void CardStack::shuffle()
{
    static std::random_device generator;
    std::shuffle(m_stack.begin(), m_stack.end(), generator);

    m_next = m_stack.begin();
}
