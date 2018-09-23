#include "cardfield.h"

#include <cassert>

#include <game/game.h>


CardField::CardField(const QString& name, FieldType type)
	: Field(name, type)
{
    assert(type == FieldType::event_card || type == FieldType::society_card);
}

bool CardField::moveOn(const QString&, Game* game, int)
{
    auto card = (m_type == FieldType::event_card ? game->eventStack() : game->societyStack()).draw();

    // TODO: Announce card

    return card.effect(*game);
}
