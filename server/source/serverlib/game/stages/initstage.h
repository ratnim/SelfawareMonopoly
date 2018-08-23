#pragma once

#include <map>

#include <game/player.h>
#include <game/stages/stage.h>

class InitStage : public Stage
{
public:
    InitStage(Game* game);

    void join(const QString& playerName) override;
    void ready(const QString& playerName) override;
    void start() override;

protected:
    std::vector<Player> turnOrder();
    bool allPlayersReady() const;
    bool minimalPlayersJoined() const;
    bool maximalPlayersJoined() const;
    bool gameIsStartable() const;

    void broadcastPossibleRequests() const;
    void broadcastGameIsStartable() const;
    void broadcastPlayerReadyRequest() const;

	QJsonObject createPossibleRequest(const QString& requestName) const;

    Game* m_game;
    std::map<QString, bool> m_playersReady;
};
