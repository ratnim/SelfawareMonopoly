#include "gamestate.h"

#include <QJsonArray>
#include <QVariantMap>

GameState::GameState()
    : turn(-1)
{
}

QByteArray GameState::handle(const Request& request)
{
    if (request.path == "/lobby")
    {
        return handleLobby(request);
    }

    if (request.path == "/game")
    {
        return handleGame(request);
    }

    return Request::generateHttpError(404);
}

QByteArray GameState::handleLobby(const Request& request)
{
    if (!request.body.contains("player"))
    {
        return Request::toJsonError("missing player name");
    }

    if (turn >= 0)
    {
        return Request::toJsonError("the game already started");
    }

    gameJoin(request.body);
    return Request::toHttpAnswer("{ok : true}");
}

QByteArray GameState::handleGame(const Request& request)
{
    auto body = request.body.toVariantMap();
    if (!body.contains("action"))
    {
        return Request::toJsonError("missing action field");
    }

    auto action = body["player"].toJsonObject();
    if (!action.contains("name"))
    {
        return Request::toJsonError("missing action name");
    }

    auto knownId = -1;
    if (body.contains("id"))
    {
        knownId = body["id"].toInt();
    }

    auto actionName = action["name"].toString();
    if (actionName == "startGame")
    {
        if (turn >= 0)
        {
            return Request::toJsonError("game already started");
        }

        if (playerNames.empty())
        {
            return Request::toJsonError("no players to start");
        }

        gameStart();
        turnStart();
        // return all missing actions
    }

    if (actionName == "review")
    {
        // return all missing actions
    }

    if (actionName == "rollDice")
    {
        if (turn < 0)
        {
            return Request::toJsonError("game did not start");
        }

        if (!body.contains("player"))
        {
            return Request::toJsonError("missing player name");
        }

        auto player = body["player"].toString();
        if (playerNames[0] != player)
        {
            return Request::toJsonError("not your turn");
        }

        // roll dices


        actions.push_back("turn end " + playerNames[turn]);
        turn = (turn + 1) % playerNames.size();
        actions.push_back("turn start " + playerNames[turn]);

        // return all missing actions
    }

    return Request::generateHttpError(404);
}

QJsonObject GameState::toAction(const QString& name)
{
    QJsonObject action;
    action["action"] = QJsonObject({ { "name", name } });
    action["id"] = static_cast<int>(actions.size());

    return action;
}

void GameState::gameJoin(const QJsonObject& request)
{
    auto playerName = request["player"].toString();
    playerNames.push_back(playerName);
    auto action = toAction("join");
    action["player"] = playerName;
    actions.push_back(action);
}

void GameState::gameStart()
{
    QJsonArray players;
    for (const auto& player : playerNames)
    {
        players.append(player);
    }
    auto action = toAction("start");
    action["players"] = players;
    actions.push_back(action);
}

void GameState::turnStart()
{
    ++turn;

    auto action = toAction("turnStart");
    action["player"] = playerNames[turn];
    actions.push_back(action);
}

void GameState::turnEnd()
{
    auto action = toAction("turnEnd");
    action["player"] = playerNames[turn];
    actions.push_back(action);
}

void GameState::rollDice()
{
    auto action = toAction("turnStart");
    action["rollDice"] = playerNames[turn];
    action["dices"] = QJsonArray({ rand() % 6 + 1, rand() % 6 + 1 });
    actions.push_back(action);
}
