#include "gamestate.h"

#include <QJsonArray>
#include <QVariantMap>

std::map<int, BoardState> g_games;
int g_nextGameID = 0;

int createNewGame()
{
    const int id = g_nextGameID++;
    g_games.emplace(id, BoardState());
    return id;
}

BoardState * getGame(const int id)
{
    const auto it = g_games.find(id);

    if (it != g_games.end())
        return &(*it).second;
    else
        return nullptr;
}
