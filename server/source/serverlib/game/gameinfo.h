#pragma once


#include <QObject>
#include <game/game.h>

class GamePhaseStringConverter :QObject
{
	Q_OBJECT
public:
    enum GamePhase
    {
        INITIALIZED,
        STARTED,
        FINISHED
    };
    Q_ENUM(GamePhase);

	static GamePhaseStringConverter::GamePhase stateByName(const QString& name);
    static QString nameByState(GamePhase phase);
};

using GamePhase = GamePhaseStringConverter::GamePhase;

class GameInfo : public QObject
{
    Q_OBJECT
public:

    GameInfo(const Game& game, const QString& label);

    QString label() const;
    GamePhase phase() const;
    std::vector<QString> players() const;

signals:
    void change();

protected:
    void playerJoin(const QString& playerName);
    void gameStart();
    void gameEnd();

    const QString m_label;
    GamePhase m_gamePhase;
    std::vector<QString> m_players;
};
