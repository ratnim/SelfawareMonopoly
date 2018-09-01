#pragma once

#include <map>
#include <vector>

#include <game/player.h>
#include <game/turn/turnstate.h>

class InitState : public TurnState
{
public:
    InitState(Game* game);

	void requestPossibleRequests(const QString& playerName) override;

    void requestPlayerJoin(const QString& playerName) override;
    void requestPlayerReady(const QString& playerName) override;
    void requestGameStart() override;

protected:
    std::vector<Player> joinedPlayers();
    bool allPlayersReady() const;
    bool minimalPlayersJoined() const;
    bool maximalPlayersJoined() const;
    bool gameIsStartable() const;

	void handleGameStart();
    void broadcastPossibleRequests() override;

    std::map<QString, bool> m_playersReady;
};
