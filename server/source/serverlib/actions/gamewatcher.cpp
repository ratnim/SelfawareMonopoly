#include "gamewatcher.h"

#include <QJsonDocument>

#include <game/game.h>
#include <models/gamemodel.h>

GameWatcher::GameWatcher(const Game& game)
    : m_game(game)
{
    connect(&game, &Game::onPlayerJoin, this, &GameWatcher::playerJoin);
    connect(&game, &Game::onPlayerReady, this, &GameWatcher::playerReady);

    connect(&game, &Game::onRollDice, this, &GameWatcher::rollDice);
    connect(&game, &Game::onPlayerMove, this, &GameWatcher::playerMove);
    connect(&game, &Game::onTurnChange, this, &GameWatcher::changeTurn);

    connect(&game, &Game::onGameStart, this, &GameWatcher::gameStart);
    connect(&game, &Game::onGameEnd, this, &GameWatcher::gameEnd);
}

const std::vector<QString>& GameWatcher::messages() const
{
    return m_messages;
}

void GameWatcher::event(const QString& message)
{
    m_messages.push_back(message);
    emit send(message);
}

void GameWatcher::playerJoin(const QString& playerName)
{
    QJsonObject answer({ { "name", "join_game" } });
    answer["data"] = QJsonObject{ { "player_name", playerName } };

    event(toString(answer));
}

void GameWatcher::playerReady(const QString& playerName)
{
    QJsonObject answer({ { "name", "player_ready" } });
    answer["data"] = QJsonObject{ { "player_name", playerName } };

    event(toString(answer));
}

void GameWatcher::rollDice(int d1, int d2)
{
    QJsonObject answer({ { "name", "roll_dice" } });
    answer["data"] = QJsonObject{ { "eyes", QJsonArray({ d1, d2 }) } };

    event(toString(answer));
}

void GameWatcher::playerMove(const QString& playerName, int distance)
{
    QJsonObject answer({ { "name", "player_move" } });
    QJsonObject data;
    data["player_name"] = playerName;
    data["distance"] = distance;
    answer["data"] = data;

    event(toString(answer));
}

void GameWatcher::changeTurn(const QString& movingPlayer)
{
    QJsonObject answer({ { "name", "change_turn" } });
    answer["data"] = QJsonObject{ { "player_name", movingPlayer } };

    event(toString(answer));
}

void GameWatcher::gameStart()
{
    QJsonObject answer({ { "name", "game_start" } });

    event(toString(answer));
}

void GameWatcher::gameEnd()
{
    QJsonObject answer({ { "name", "end_game" } });

    event(toString(answer));
}

QString GameWatcher::toString(const QJsonObject& object)
{
    return QJsonDocument(object).toJson();
}
