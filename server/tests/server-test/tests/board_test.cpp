#include <gmock/gmock.h>

#include <memory>
#include <vector>

#include <QJsonArray>
#include <QJsonObject>

#include <game/board/board.h>

#include <test_utils/helpers.h>

TEST(BoardTest, get_description)
{
    Board gameBoard(std::move(fieldsSingleJail()));
    auto description = gameBoard.description();

    EXPECT_EQ(5, description["fields"].toArray().size());
    EXPECT_EQ("free", description["fields"].toArray()[0].toObject()["name"].toString().toStdString());
    EXPECT_EQ("jail", description["fields"].toArray()[4].toObject()["name"].toString().toStdString());
}

TEST(BoardTest, target_for_move)
{
    Board board(std::move(fieldsSingleJail()));

    EXPECT_EQ(0, board.targetForMove(0, 0));
    EXPECT_EQ(1, board.targetForMove(1, 0));
    EXPECT_EQ(2, board.targetForMove(1, 6));
    EXPECT_EQ(0, board.targetForMove(1, 4));
    EXPECT_EQ(4, board.targetForMove(1, 3));

    EXPECT_EQ(0, board.targetForMove(1, -1));
    EXPECT_EQ(4, board.targetForMove(1, -2));
}

TEST(BoardTest, find_jail_non_existing)
{
    Board board(std::move(fieldsFree()));
    EXPECT_EQ(0, board.jailIndex());
}

TEST(BoardTest, find_jail)
{
    Board board(std::move(fieldsSingleJail()));
    EXPECT_EQ(4, board.jailIndex());
}
