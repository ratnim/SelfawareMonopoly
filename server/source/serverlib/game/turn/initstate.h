#pragma once

#include <map>
#include <vector>

#include <game/player.h>
#include <game/turn/turnstate.h>

class InitState : public TurnState
{
public:
    InitState(Game* game);

    void playerJoin(const QString& playerName) override;
    void playerReady(const QString& playerName) override;
    void gameStart() override;

protected:
    std::vector<Player> joinedPlayers();
    bool allPlayersReady() const;
    bool minimalPlayersJoined() const;
    bool maximalPlayersJoined() const;
    bool gameIsStartable() const;

    void broadcastPossibleRequests() const;
    void broadcastGameIsStartable() const;
    void broadcastPlayerReadyRequest() const;

    std::map<QString, bool> m_playersReady;
};
