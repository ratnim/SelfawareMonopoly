#include "start.h"

#include <game/game.h>

Start::Start(const QString& name)
	: Field(name, FieldType::start)
{
}

void Start::passBy(const QString& playerName, Game* game)
{
    game->doCurrentPlayerEarnMoney(moneyFromStart);
}