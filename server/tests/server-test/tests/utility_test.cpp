#include <gmock/gmock.h>

#include <game/board/board.h>
#include <game/board/utility.h>

#include <test_utils/helpers.h>

TEST(UtilityTest, get_description)
{
    Utility util("Test", 5, 200, std::vector<int>{2});

    auto description = util.description();

    EXPECT_EQ("Test", description["name"].toString().toStdString());
    EXPECT_EQ("utility", description["type"].toString().toStdString());
    EXPECT_EQ(5, description["group"].toInt());
    EXPECT_EQ(200, description["price"].toInt());
    EXPECT_EQ(1, description["rent"].toArray().size());
    EXPECT_EQ(2, description["rent"].toArray()[0].toInt());
}

// State transfers are commmon to all OwnableFields

TEST(UtilityTest, rent_calculation)
{
    Board board(std::move(fieldsUtilities()));

    auto utilA = dynamic_cast<Utility*>(board[1]); // Group 0
    auto utilB = dynamic_cast<Utility*>(board[2]); // Group 0
    auto utilC = dynamic_cast<Utility*>(board[3]); // Group 0
    auto utilD = dynamic_cast<Utility*>(board[4]); // Group 1

    // All stations are owned by "", so maximum owner bonus applies
    EXPECT_EQ(35, utilA->rent(board, 7)); // 7 * 5
    EXPECT_EQ(35, utilD->rent(board, 7)); // 7 * 5

    // Split ownership of group 0
    utilC->changeOwner("someone");

    EXPECT_EQ(21, utilA->rent(board, 7)); // 7 * 3
    EXPECT_EQ(14, utilC->rent(board, 7)); // 7 * 2
    EXPECT_EQ(35, utilD->rent(board, 7)); // 7 * 5
}
