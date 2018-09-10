#include <gmock/gmock.h>

#include <models/boardmodel.h>

class BoardModelTest : public ::testing::Test
{
public:
};

TEST_F(BoardModelTest, default_dir_assets_boards)
{
    auto& instance = BoardModel::instance();

    auto gameBoard = std::move(instance.getFieldsForNewBoard("berlin_en.json"));

    EXPECT_EQ(40, gameBoard.size());
    EXPECT_EQ(FieldType::start, gameBoard[0]->type());
}

TEST_F(BoardModelTest, board_file_not_exists)
{
    BoardModel::setBoardDir("./assets/boards");
    auto& instance = BoardModel::instance();

    EXPECT_THROW(instance.getFieldsForNewBoard("not_there.json"), std::runtime_error);
}

TEST_F(BoardModelTest, load_board)
{
    BoardModel::setBoardDir("./assets/boards");
    auto& instance = BoardModel::instance();
    auto gameBoard = std::move(instance.getFieldsForNewBoard("berlin_en.json"));

    EXPECT_EQ(40, gameBoard.size());
    EXPECT_EQ(FieldType::start, gameBoard[0]->type());
}