#pragma once


#include <QObject>
#include <game/game.h>

class GamePhaseStringConverter :QObject
{
	Q_OBJECT
public:
    enum GameStage
    {
        INITIALIZED,
        STARTED,
        FINISHED
    };
    Q_ENUM(GameStage);

	static GamePhaseStringConverter::GameStage stateByName(const QString& name);
    static QString nameByState(GameStage stage);
};

using GameStage = GamePhaseStringConverter::GameStage;

class GameInfo : public QObject
{
    Q_OBJECT
public:

    GameInfo(const Game& game, const QString& label);

    QString label() const;
    GameStage stage() const;
    std::vector<QString> players() const;

signals:
    void change();

protected:
    void playerJoin(const QString& playerName);
    void gameStart();
    void gameEnd();

    const QString m_label;
    GameStage m_gamePhase;
    std::vector<QString> m_players;
};
