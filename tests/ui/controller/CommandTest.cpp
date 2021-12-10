#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"Command.h"
#include"ViewMock.h"
#include"TaskManagerMock.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::_;

class CommandAddTest : public ::testing::Test {
public:
    void SetUp() override {
        manager_ = std::make_shared<TaskManagerMock>();
        task_ = std::make_shared<Task>(Task::Create(Task::Arguments::Create("first")).value());
        auto reader = std::make_shared<Reader>();
        auto printer = std::make_shared<Printer>();
        view_ = std::make_shared<ViewMock>(reader, printer);
        command_ = std::make_shared<CommandAdd>(*task_, view_);
    }

protected:
    std::shared_ptr<Task> task_;
    std::shared_ptr<TaskManagerMock> manager_;
    std::shared_ptr<CommandAdd> command_;
    std::shared_ptr<ViewMock> view_;
};

TEST_F(CommandAddTest, shouldAddTask) {
    EXPECT_CALL(*manager_, AddTask(*task_))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_TRUE(command_->execute(manager_));
}

TEST_F(CommandAddTest, shouldHandleErrorWhenAddTask) {
    EXPECT_CALL(*manager_, AddTask(*task_))
            .Times(1)
            .WillOnce(Return(false));
    EXPECT_CALL(*view_, PrintException(_))
            .Times(1);
    EXPECT_TRUE(command_->execute(manager_));
}