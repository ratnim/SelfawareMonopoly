#include <gmock/gmock.h>

#include <QSignalSpy>

#include <models/gamemodel.h>
#include <utils/program.h>

class GameModelTest : public ::testing::Test, public Program
{
public:
};

TEST_F(GameModelTest, create_multiple_games)
{
    auto& instance = GameModel::instance();

    instance.createGame("first");
    instance.createGame("second");
    instance.createGame("third");

    EXPECT_EQ(instance.numberOfGames(), 3);

    EXPECT_EQ(instance.open(0).info.label(), "first");
    EXPECT_EQ(instance.open(1).info.label(), "second");
    EXPECT_EQ(instance.open(2).info.label(), "third");
}

TEST_F(GameModelTest, signal_send)
{
    auto& instance = GameModel::instance();

    QSignalSpy socket_spy(&instance, &GameModel::onCreateGame);

    instance.createGame("new");

    EXPECT_TRUE(socket_spy.size());
}
