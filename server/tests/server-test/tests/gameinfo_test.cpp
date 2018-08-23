#include <gmock/gmock.h>

#include <QSignalSpy>

#include <models/gamemodel.h>
#include <utils/program.h>

class GameInfoTest : public ::testing::Test, public Program
{
public:
};

TEST_F(GameInfoTest, store_label)
{
    auto& instance = GameModel::instance();

    auto id = instance.createGame("label");
    auto& gameWrapper = instance.open(id);

    EXPECT_EQ(gameWrapper.info.label(), "label");
}

TEST_F(GameInfoTest, store_state)
{
    auto& instance = GameModel::instance();

    auto id = instance.createGame("label");
    auto& gameWrapper = instance.open(id);

    QSignalSpy change_spy(&gameWrapper.info, &GameInfo::change);

    EXPECT_EQ(gameWrapper.info.stage(), GameStage::INITIALIZED);
    gameWrapper.game.onGameStart();
    EXPECT_EQ(gameWrapper.info.stage(), GameStage::STARTED);
    gameWrapper.game.onGameEnd();
    EXPECT_EQ(gameWrapper.info.stage(), GameStage::FINISHED);

    EXPECT_EQ(change_spy.size(), 2);
}

TEST_F(GameInfoTest, convert_state)
{
    QString initialized_name = "initialized";
    QString started_name = "started";
    QString finished_name = "finished";
	
    EXPECT_EQ(GameStage::INITIALIZED, GamePhaseStringConverter::stateByName(initialized_name));
    EXPECT_EQ(GameStage::STARTED, GamePhaseStringConverter::stateByName(started_name));
    EXPECT_EQ(GameStage::FINISHED, GamePhaseStringConverter::stateByName(finished_name));
	
	EXPECT_EQ(initialized_name, GamePhaseStringConverter::nameByState(GameStage::INITIALIZED));
    EXPECT_EQ(started_name, GamePhaseStringConverter::nameByState(GameStage::STARTED));
    EXPECT_EQ(finished_name, GamePhaseStringConverter::nameByState(GameStage::FINISHED));
}

   

TEST_F(GameInfoTest, store_players)
{
    auto& instance = GameModel::instance();

    auto id = instance.createGame("label");
    auto& gameWrapper = instance.open(id);

    QSignalSpy change_spy(&gameWrapper.info, &GameInfo::change);

    EXPECT_EQ(gameWrapper.info.players().size(), 0);
    gameWrapper.game.onPlayerJoin("player0");
    EXPECT_EQ(gameWrapper.info.players().size(), 1);
    EXPECT_EQ(gameWrapper.info.players()[0], "player0");
    gameWrapper.game.onPlayerJoin("player1");
    EXPECT_EQ(gameWrapper.info.players().size(), 2);
    EXPECT_EQ(gameWrapper.info.players()[1], "player1");

    EXPECT_EQ(change_spy.size(), 2);
}
