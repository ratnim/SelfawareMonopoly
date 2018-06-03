#include "gameaction.h"

GameAction::GameAction(const QString& playerName, Game& game)
    : m_playerName(playerName)
    , m_game(game)
{
}
