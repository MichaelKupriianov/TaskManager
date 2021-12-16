#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"Command.h"
#include"ViewMock.h"
#include"TaskManagerMock.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::_;

class CommandTest : public ::testing::Test {
public:
    void SetUp() override {
        manager_ = std::make_shared<TaskManagerMock>();
        task_ = std::make_shared<Task>();
        id_ = std::make_shared<TaskId>();
        auto reader = std::make_shared<Reader>();
        auto printer = std::make_shared<Printer>();
        view_ = std::make_shared<ViewMock>(reader, printer);
    }

protected:
    std::shared_ptr<Task> task_;
    std::shared_ptr<TaskId> id_;
    std::shared_ptr<TaskManagerMock> manager_;
    std::shared_ptr<ViewMock> view_;
};

TEST_F(CommandTest, shouldQuit) {
    auto command = std::make_shared<CommandQuit>();
    EXPECT_FALSE(command->execute(manager_));
}

TEST_F(CommandTest, shouldAddTask) {
    auto command = std::make_shared<CommandAdd>(*task_, view_);
    EXPECT_CALL(*manager_, AddTask(*task_))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_TRUE(command->execute(manager_));
}

TEST_F(CommandTest, shouldAddSubTask) {
    auto command = std::make_shared<CommandAddSub>(*task_, *id_, view_);
    EXPECT_CALL(*manager_, AddSubTask(*task_, *id_))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_TRUE(command->execute(manager_));
}

TEST_F(CommandTest, shouldHandleErrorWhenAddSubTask) {
    auto command = std::make_shared<CommandAddSub>(*task_, *id_, view_);
    EXPECT_CALL(*manager_, AddSubTask(*task_, *id_))
            .Times(1)
            .WillOnce(Return(false));
    EXPECT_CALL(*view_, PrintException(_))
            .Times(1);
    EXPECT_TRUE(command->execute(manager_));
}

TEST_F(CommandTest, shouldEditTask) {
    auto command = std::make_shared<CommandEdit>(*id_, *task_, view_);
    EXPECT_CALL(*manager_, Edit(*id_, *task_))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_TRUE(command->execute(manager_));
}

TEST_F(CommandTest, shouldHandleErrorWhenEditTask) {
    auto command = std::make_shared<CommandEdit>(*id_, *task_, view_);
    EXPECT_CALL(*manager_, Edit(*id_, *task_))
            .Times(1)
            .WillOnce(Return(false));
    EXPECT_CALL(*view_, PrintException(_))
            .Times(1);
    EXPECT_TRUE(command->execute(manager_));
}

TEST_F(CommandTest, shouldCompleteTask) {
    auto command = std::make_shared<CommandComplete>(*id_, view_);
    EXPECT_CALL(*manager_, Complete(*id_))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_TRUE(command->execute(manager_));
}

TEST_F(CommandTest, shouldHandleErrorWhenCompletetTask) {
    auto command = std::make_shared<CommandComplete>(*id_, view_);
    EXPECT_CALL(*manager_, Complete(*id_))
            .Times(1)
            .WillOnce(Return(false));
    EXPECT_CALL(*view_, PrintException(_))
            .Times(1);
    EXPECT_TRUE(command->execute(manager_));
}

TEST_F(CommandTest, shouldDeleteTask) {
    auto command = std::make_shared<CommandDelete>(*id_, view_);
    EXPECT_CALL(*manager_, Delete(*id_))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_TRUE(command->execute(manager_));
}

TEST_F(CommandTest, shouldHandleErrorWhenDeleteTask) {
    auto command = std::make_shared<CommandDelete>(*id_, view_);
    EXPECT_CALL(*manager_, Delete(*id_))
            .Times(1)
            .WillOnce(Return(false));
    EXPECT_CALL(*view_, PrintException(_))
            .Times(1);
    EXPECT_TRUE(command->execute(manager_));
}

TEST_F(CommandTest, shouldShowTasksWithSubtasks) {
    auto command = std::make_shared<CommandShow>(true, SortBy::ID, view_);
    EXPECT_CALL(*manager_, ShowAll(SortBy::ID))
            .Times(1);
    command->execute(manager_);
}

TEST_F(CommandTest, shouldShowOnlyTasks) {
    auto command = std::make_shared<CommandShow>(false, SortBy::PRIORITY, view_);
    EXPECT_CALL(*manager_, ShowParents(SortBy::PRIORITY))
            .Times(1);
    command->execute(manager_);
}

TEST_F(CommandTest, shouldShowSomeTask) {
    auto command = std::make_shared<CommandShowTask>(*id_, SortBy::DATE, view_);
    EXPECT_CALL(*manager_, ShowTask(*id_, SortBy::DATE))
            .Times(1);
    command->execute(manager_);
}

TEST_F(CommandTest, shouldHandleErrorWhenShowSomeTask) {
    auto command = std::make_shared<CommandShowTask>(*id_, SortBy::ID, view_);
    EXPECT_CALL(*manager_, ShowTask(*id_, SortBy::ID))
            .Times(1)
            .WillOnce(Return(std::nullopt));
    EXPECT_CALL(*view_, PrintException(_))
            .Times(1);
    command->execute(manager_);
}

TEST_F(CommandTest, shouldShowByLabel) {
    auto command = std::make_shared<CommandShowLabel>("label", SortBy::PRIORITY, view_);
    EXPECT_CALL(*manager_, ShowLabel("label", SortBy::PRIORITY))
            .Times(1);
    command->execute(manager_);
}
