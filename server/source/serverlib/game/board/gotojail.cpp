#include "gotojail.h"

#include <game/game.h>

GoToJail::GoToJail(const QString& name) : Field(name, FieldType::go_to_jail)
{
}

bool GoToJail::moveOnTriggersStateChange(const QString& name) const
{
    return true;
}

void GoToJail::moveOn(const QString& playerName, Game* game)
{
    game->doJailCurrentPlayer();
}
