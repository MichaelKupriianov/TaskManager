#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ui/command/Command.h"
#include "ui/controller/DefaultControllerMock.h"
#include "utilities/CreateProtoObjects.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::_;

using namespace ui::command;

class CommandTest : public ::testing::Test {
public:
    void SetUp() override {
        task_ = std::make_shared<Task>();
        id_ = std::make_shared<TaskId>();
        simple_task_ = std::make_shared<TaskWithId>(CreateTaskWithId(*id_, *task_));
        array_simple_tasks_ = std::make_shared<ManyTasksWithId>();
        composite_task_ = std::make_shared<CompositeTask>(CreateCompositeTask(*simple_task_, *array_simple_tasks_));
        array_composite_tasks_ = std::make_shared<ManyCompositeTasks>();

        auto generator = std::make_shared<model::IdGenerator>();
        auto manager = std::make_shared<model::TaskManager>(generator);
        auto model = std::make_shared<model::Model>(manager);
        controller_ = std::make_shared<DefaultControllerMock>(model);
    }

protected:
    std::shared_ptr<Task> task_;
    std::shared_ptr<TaskId> id_;
    std::shared_ptr<TaskWithId> simple_task_;
    std::shared_ptr<ManyTasksWithId> array_simple_tasks_;
    std::shared_ptr<CompositeTask> composite_task_;
    std::shared_ptr<ManyCompositeTasks> array_composite_tasks_;

    std::shared_ptr<DefaultControllerMock> controller_;
};

TEST_F(CommandTest, shouldQuit) {
    auto command = std::make_shared<Quit>();
    Result result{command->execute(controller_)};
    EXPECT_TRUE(result.finished);
}

TEST_F(CommandTest, shouldAddTask) {
    auto command = std::make_shared<Add>(*task_);
    EXPECT_CALL(*controller_, AddTask(*task_))
            .Times(1)
            .WillOnce(Return(true));

    Result result{command->execute(controller_)};
    EXPECT_FALSE(result.finished);
}

TEST_F(CommandTest, shouldAddSubTask) {
    auto command = std::make_shared<AddSub>(*task_, *id_);
    EXPECT_CALL(*controller_, AddSubTask(*task_, *id_))
            .Times(1)
            .WillOnce(Return(true));

    Result result{command->execute(controller_)};
    EXPECT_FALSE(result.finished);
}

TEST_F(CommandTest, shouldHandleErrorWhenAddSubTask) {
    auto command = std::make_shared<AddSub>(*task_, *id_);
    EXPECT_CALL(*controller_, AddSubTask(*task_, *id_))
            .Times(1)
            .WillOnce(Return(false));

    Result result{command->execute(controller_)};
    EXPECT_FALSE(result.finished);
    EXPECT_TRUE(result.error.has_value());
}

TEST_F(CommandTest, shouldEditTask) {
    auto command = std::make_shared<Edit>(*id_, *task_);
    EXPECT_CALL(*controller_, Edit(*id_, *task_))
            .Times(1)
            .WillOnce(Return(true));

    Result result{command->execute(controller_)};
    EXPECT_FALSE(result.finished);
}

TEST_F(CommandTest, shouldHandleErrorWhenEditTask) {
    auto command = std::make_shared<Edit>(*id_, *task_);
    EXPECT_CALL(*controller_, Edit(*id_, *task_))
            .Times(1)
            .WillOnce(Return(false));

    Result result{command->execute(controller_)};
    EXPECT_FALSE(result.finished);
    EXPECT_TRUE(result.error.has_value());
}

TEST_F(CommandTest, shouldCompleteTask) {
    auto command = std::make_shared<Complete>(*id_);
    EXPECT_CALL(*controller_, Complete(* id_))
            .Times(1)
            .WillOnce(Return(true));

    Result result{command->execute(controller_)};
    EXPECT_FALSE(result.finished);
}

TEST_F(CommandTest, shouldHandleErrorWhenCompletetTask) {
    auto command = std::make_shared<Complete>(*id_);
    EXPECT_CALL(*controller_, Complete(* id_))
            .Times(1)
            .WillOnce(Return(false));

    Result result{command->execute(controller_)};
    EXPECT_FALSE(result.finished);
    EXPECT_TRUE(result.error.has_value());
}

TEST_F(CommandTest, shouldDeleteTask) {
    auto command = std::make_shared<Delete>(*id_);
    EXPECT_CALL(*controller_, Delete(* id_))
            .Times(1)
            .WillOnce(Return(true));

    Result result{command->execute(controller_)};
    EXPECT_FALSE(result.finished);
}

TEST_F(CommandTest, shouldHandleErrorWhenDeleteTask) {
    auto command = std::make_shared<Delete>(*id_);
    EXPECT_CALL(*controller_, Delete(* id_))
            .Times(1)
            .WillOnce(Return(false));

    Result result{command->execute(controller_)};
    EXPECT_FALSE(result.finished);
    EXPECT_TRUE(result.error.has_value());
}

TEST_F(CommandTest, shouldShowTasksWithSubtasks) {
    auto command = std::make_shared<Show>(true, TasksSortBy::ID);
    EXPECT_CALL(*controller_, ShowAll(TasksSortBy::ID))
            .Times(1)
            .WillOnce(Return(*array_composite_tasks_));

    Result result{command->execute(controller_)};
    EXPECT_TRUE(result.many_composite_tasks.has_value());
}

TEST_F(CommandTest, shouldShowOnlyTasks) {
    auto command = std::make_shared<Show>(false, TasksSortBy::PRIORITY);
    EXPECT_CALL(*controller_, ShowParents(TasksSortBy::PRIORITY))
            .Times(1)
            .WillOnce(Return(*array_simple_tasks_));

    Result result{command->execute(controller_)};
    EXPECT_TRUE(result.many_tasks.has_value());
}

TEST_F(CommandTest, shouldShowSomeTask) {
    auto command = std::make_shared<ShowTask>(*id_, TasksSortBy::DATE);
    EXPECT_CALL(*controller_, ShowTask(*id_, TasksSortBy::DATE))
            .Times(1)
            .WillOnce(Return(*composite_task_));

    Result result{command->execute(controller_)};
    EXPECT_TRUE(result.composite_task.has_value());
}

TEST_F(CommandTest, shouldHandleErrorWhenShowSomeTask) {
    auto command = std::make_shared<ShowTask>(*id_, TasksSortBy::ID);
    EXPECT_CALL(*controller_, ShowTask(*id_, TasksSortBy::ID))
            .Times(1)
            .WillOnce(Return(CompositeTask()));

    Result result{command->execute(controller_)};
    EXPECT_TRUE(result.error.has_value());
}

TEST_F(CommandTest, shouldShowByLabel) {
    auto command = std::make_shared<ShowByLabel>("label", TasksSortBy::PRIORITY);
    EXPECT_CALL(*controller_, ShowByLabel("label", TasksSortBy::PRIORITY))
            .Times(1)
            .WillOnce(Return(*array_simple_tasks_));

    Result result{command->execute(controller_)};
    EXPECT_TRUE(result.many_tasks.has_value());
}

TEST_F(CommandTest, shouldSaveToFile) {
    auto command = std::make_shared<Save>("filename");
    EXPECT_CALL(*controller_, Save("filename"))
            .Times(1)
            .WillOnce(Return(true));

    Result result{command->execute(controller_)};
    EXPECT_FALSE(result.finished);
}

TEST_F(CommandTest, shouldHandleErrorWhenSaveToFile) {
    auto command = std::make_shared<Save>("filename");
    EXPECT_CALL(*controller_, Save("filename"))
            .Times(1)
            .WillOnce(Return(false));

    Result result{command->execute(controller_)};
    EXPECT_TRUE(result.error.has_value());
}

TEST_F(CommandTest, shouldLoadFromFile) {
    auto command = std::make_shared<Load>("filename");
    EXPECT_CALL(*controller_, Load("filename"))
            .Times(1)
            .WillOnce(Return(true));

    Result result{command->execute(controller_)};
    EXPECT_FALSE(result.finished);
}

TEST_F(CommandTest, shouldHandleErrorWhenLoadFromFile) {
    auto command = std::make_shared<Load>("filename");
    EXPECT_CALL(*controller_, Load("filename"))
            .Times(1)
            .WillOnce(Return(false));

    Result result{command->execute(controller_)};
    EXPECT_TRUE(result.error.has_value());
}