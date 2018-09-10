#include "gotojail.h"

#include <game/game.h>

GoToJail::GoToJail(const QString& name) : Field(name, FieldType::go_to_jail)
{
}

bool GoToJail::moveOn(const QString& playerName, Game* game, int)
{
    game->doCurrentPlayerGoToJail();
    return true;
}
