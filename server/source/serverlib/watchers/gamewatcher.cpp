#include "gamewatcher.h"

#include <iostream>

#include <QJsonDocument>

#include <game/game.h>
#include <models/gamemodel.h>

GameWatcher::GameWatcher(const Game& game)
{
    connect(&game, &Game::onPlayerJoin, this, &GameWatcher::playerJoin);
    connect(&game, &Game::onBoardRequest, this, &GameWatcher::boardRequest);
    connect(&game, &Game::onPlayerReady, this, &GameWatcher::playerReady);

    connect(&game, &Game::onRollDice, this, &GameWatcher::rollDice);
    connect(&game, &Game::onPlayerMove, this, &GameWatcher::playerMove);
    connect(&game, &Game::onTurnChange, this, &GameWatcher::changeTurn);

    connect(&game, &Game::onGameStart, this, &GameWatcher::gameStart);
    connect(&game, &Game::onGameEnd, this, &GameWatcher::gameEnd);

    connect(&game, &Game::onPossibleRequests, this, &GameWatcher::possibleRequests);
}

const std::vector<QString>& GameWatcher::messages() const
{
    return m_messages;
}

void GameWatcher::broadcastEvent(const QJsonObject& object)
{
    auto message = toString(object);
    m_messages.push_back(message);
    std::cout << "Send: " + message.toStdString() << std::endl;
    emit broadcast(message);
}

void GameWatcher::singlePlayerEvent(const QString& player, const QJsonObject& object)
{
    auto message = toString(object);
    m_messages.push_back(message);
    std::cout << "Send: " + message.toStdString() << std::endl;
    emit broadcastPlayerMessage(player, message);
}

void GameWatcher::playerJoin(const QString& playerName)
{
    QJsonObject answer({ { "name", "join_game" } });
    answer["data"] = QJsonObject{ { "player_name", playerName } };

    broadcastEvent(answer);
}

void GameWatcher::boardRequest(const QJsonObject& board)
{
    QJsonObject answer({ { "name", "game_board" } });
    answer["data"] = board;
    broadcastEvent(answer);
}

void GameWatcher::playerReady(const QString& playerName)
{
    QJsonObject answer({ { "name", "player_ready" } });
    answer["data"] = QJsonObject{ { "player_name", playerName } };

    broadcastEvent(answer);
}

void GameWatcher::rollDice(const QString& playerName, int d1, int d2)
{
    QJsonObject answer({ { "name", "roll_dice" } });
    answer["data"] = QJsonObject({ { "eyes", QJsonArray({ d1, d2 }) }, { "player_name", playerName } });

    broadcastEvent(answer);
}

void GameWatcher::playerMove(const QString& playerName, int distance)
{
    QJsonObject answer({ { "name", "player_move" } });
    answer["data"] = QJsonObject({ { "player_name", playerName }, { "distance", distance } });

    broadcastEvent(answer);
}

void GameWatcher::changeTurn(const QString& movingPlayer)
{
    QJsonObject answer({ { "name", "change_turn" } });
    answer["data"] = QJsonObject{ { "player_name", movingPlayer } };

    broadcastEvent(answer);
}

void GameWatcher::gameStart()
{
    QJsonObject answer({ { "name", "game_start" } });

    broadcastEvent(answer);
}

void GameWatcher::gameEnd()
{
    QJsonObject answer({ { "name", "end_game" } });

    broadcastEvent(answer);
}

void GameWatcher::possibleRequests(const QString& playerName, const QJsonArray& possibleRequests)
{
    QJsonObject answer({ { "name", "possible_requests" } });
    answer["data"] = QJsonObject{ { "requests", possibleRequests } };

	singlePlayerEvent(playerName, answer);
}


QString GameWatcher::toString(const QJsonObject& object)
{
    return QJsonDocument(object).toJson();
}
