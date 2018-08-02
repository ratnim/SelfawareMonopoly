#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/state/runstate.h>
#include <utils/exception.h>
#include <utils/program.h>

namespace
{
const QString player("Heinz");
}

class RunStateTest : public ::testing::Test, public Program
{
public:
    std::unique_ptr<RunState> construct()
    {
        return std::make_unique<RunState>(&game, std::vector<Player>({ { player } }));
    }

protected:
    Game game;
};

TEST_F(RunStateTest, start_game)
{
    QSignalSpy start_spy(&game, &Game::onGameStart);
    QSignalSpy turn_spy(&game, &Game::onTurnChange);

    auto state = construct();

    EXPECT_EQ(state->player().name, player);

    EXPECT_EQ(start_spy.size(), 1);
    EXPECT_EQ(turn_spy.size(), 1);
    EXPECT_EQ(turn_spy.at(0).at(0).toString(), player);
}
