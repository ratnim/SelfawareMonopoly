#include <gmock/gmock.h>

#include <models/boardmodel.h>

class BoardModelTest : public ::testing::Test
{
public:
};

TEST_F(BoardModelTest, board_dir_not_set)
{
    auto& instance = BoardModel::instance();

    EXPECT_THROW(instance.new_board("berlin.json"), std::runtime_error);
}

TEST_F(BoardModelTest, board_file_not_exists)
{
    BoardModel::setBoardDir("./../../../assets/boards");
    auto& instance = BoardModel::instance();

    EXPECT_THROW(instance.new_board("not_there.json"), std::runtime_error);
}

TEST_F(BoardModelTest, load_board)
{
    BoardModel::setBoardDir("./../../../assets/boards");
    auto& instance = BoardModel::instance();
    auto board = std::move(instance.new_board("berlin.json"));

    EXPECT_EQ(40, board.size());
    EXPECT_EQ(FieldType::start, board[0]->type());
}