#include <gmock/gmock.h>

#include <models/boardmodel.h>

class BoardModelTest : public ::testing::Test
{
public:
};

TEST_F(BoardModelTest, load_board)
{
    auto& instance = BoardModel::instance();
    auto board = instance.new_board();

	EXPECT_EQ(40, board.size());
}