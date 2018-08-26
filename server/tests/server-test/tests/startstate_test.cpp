#include <gmock/gmock.h>

#include <QSignalSpy>

#include <game/game.h>

#include <game/turn/startstate.h>
#include <game/turn/rollstate.h>

#include <utils/exception.h>


namespace
{
const QString player("Heinz");
}

TEST(StartStateTest, start_game)
{
    Game game;
    QSignalSpy start_spy(&game, &Game::onGameStart);
    QSignalSpy turn_spy(&game, &Game::onTurnChange);

	game.stateChange<StartState>(std::vector<Player>({ { player } }));

    EXPECT_EQ(start_spy.size(), 1);
    EXPECT_EQ(turn_spy.size(), 1);

	EXPECT_NE(nullptr, dynamic_cast<RollState*>(game.state()));
}
