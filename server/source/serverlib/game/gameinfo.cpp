#include "gameinfo.h"

#include <QMetaEnum>

GamePhaseStringConverter::GamePhase GamePhaseStringConverter::stateByName(const QString& name)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<GamePhaseStringConverter::GamePhase>();
    QByteArray latin1 = name.toLatin1().toUpper();
    int result = metaEnum.keyToValue(latin1.constData());
    return static_cast<GamePhaseStringConverter::GamePhase>(result);
}
QString GamePhaseStringConverter::nameByState(GamePhase phase)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<GamePhaseStringConverter::GamePhase>();
    return QString(metaEnum.valueToKey(phase)).toLower();
}

GameInfo::GameInfo(const Game& game, const QString& label)
    : m_label(label)
    , m_gamePhase(GamePhase::INITIALIZED)
{
    connect(&game, &Game::onGameStart, this, &GameInfo::gameStart);
    connect(&game, &Game::onGameEnd, this, &GameInfo::gameEnd);
    connect(&game, &Game::onPlayerJoin, this, &GameInfo::playerJoin);
}

QString GameInfo::label() const
{
    return m_label;
}

GamePhase GameInfo::phase() const
{
    return m_gamePhase;
}

std::vector<QString> GameInfo::players() const
{
    return m_players;
}

void GameInfo::playerJoin(const QString& playerName)
{
    m_players.push_back(playerName);
    emit change();
}

void GameInfo::gameStart()
{
    m_gamePhase = GamePhase::STARTED;
    emit change();
}

void GameInfo::gameEnd()
{
    m_gamePhase = GamePhase::FINISHED;
    emit change();
}
