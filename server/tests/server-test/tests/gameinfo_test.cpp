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

    QSignalSpy socket_spy(&gameWrapper.info, &GameInfo::change);

    EXPECT_EQ(gameWrapper.info.state(), "initialized");
    gameWrapper.game.onGameStart();
    EXPECT_EQ(gameWrapper.info.state(), "started");
    gameWrapper.game.onGameEnd();
    EXPECT_EQ(gameWrapper.info.state(), "finished");

    EXPECT_EQ(socket_spy.size(), 2);
}

TEST_F(GameInfoTest, store_players)
{
    auto& instance = GameModel::instance();

    auto id = instance.createGame("label");
    auto& gameWrapper = instance.open(id);

    QSignalSpy socket_spy(&gameWrapper.info, &GameInfo::change);

    EXPECT_EQ(gameWrapper.info.players().size(), 0);
    gameWrapper.game.onPlayerJoin("player0");
    EXPECT_EQ(gameWrapper.info.players().size(), 1);
    EXPECT_EQ(gameWrapper.info.players()[0], "player0");
    gameWrapper.game.onPlayerJoin("player1");
    EXPECT_EQ(gameWrapper.info.players().size(), 2);
    EXPECT_EQ(gameWrapper.info.players()[1], "player1");

    EXPECT_EQ(socket_spy.size(), 2);
}
