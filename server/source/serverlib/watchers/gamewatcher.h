#pragma once

#include <QJsonArray>
#include <QJsonObject>

#include <watchers/watcher.h>

class Game;

class GameWatcher : public Watcher
{
    Q_OBJECT
public:
    GameWatcher(const Game& game);

    const std::vector<QString>& messages() const;
signals:
    void broadcastPlayerMessage(const QString& player, const QString& message);

protected:
    void broadcastEvent(const QJsonObject &object);
    void singlePlayerEvent(const QString& player, const QJsonObject& object);

    void requestPlayerJoin(const QString& playerName);
    void boardRequest(const QJsonObject& gameBoard);
    void playerReady(const QString& playerName);

    void rollDice(const QString& playerName, int d1, int d2);
    void moneyChange(const QString& playerName, int balance);
    void playerMove(const QString& playerName, int fieldIndex, const QString& type);
    void changeTurn(const QString& movingPlayer);

    void gameStart();
    void gameEnd();

	void possibleRequests(const QString& playerName, const QJsonArray& possibleRequests);

    static QString toString(const QJsonObject& object);

    std::vector<QString> m_messages;
};
