#include "gameinfo.h"

#include <QMetaEnum>

GamePhaseStringConverter::GameStage GamePhaseStringConverter::stateByName(const QString& name)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<GamePhaseStringConverter::GameStage>();
    QByteArray latin1 = name.toLatin1().toUpper();
    int result = metaEnum.keyToValue(latin1.constData());
    return static_cast<GamePhaseStringConverter::GameStage>(result);
}
QString GamePhaseStringConverter::nameByState(GameStage stage)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<GamePhaseStringConverter::GameStage>();
    return QString(metaEnum.valueToKey(stage)).toLower();
}

GameInfo::GameInfo(const Game& game, const QString& label)
    : m_label(label)
    , m_gamePhase(GameStage::INITIALIZED)
{
    connect(&game, &Game::onGameStart, this, &GameInfo::gameStart);
    connect(&game, &Game::onGameEnd, this, &GameInfo::gameEnd);
    connect(&game, &Game::onPlayerJoin, this, &GameInfo::requestPlayerJoin);
}

QString GameInfo::label() const
{
    return m_label;
}

GameStage GameInfo::stage() const
{
    return m_gamePhase;
}

std::vector<QString> GameInfo::players() const
{
    return m_players;
}

void GameInfo::requestPlayerJoin(const QString& playerName)
{
    m_players.push_back(playerName);
    emit change();
}

void GameInfo::gameStart()
{
    m_gamePhase = GameStage::STARTED;
    emit change();
}

void GameInfo::gameEnd()
{
    m_gamePhase = GameStage::FINISHED;
    emit change();
}
