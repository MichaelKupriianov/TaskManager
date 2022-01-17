#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ui/command/Command.h"
#include "ui/controller/ControllerMock.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::_;

using namespace ui::command;

class CommandTest : public ::testing::Test {
public:
    void SetUp() override {
        task_ = std::make_shared<model::Task>();
        id_ = std::make_shared<model::TaskId>();
        simple_task_ = std::make_shared<model::TaskWithId>(*id_, *task_);
        array_simple_tasks_ = std::make_shared<model::ManyTasksWithId>();
        composite_task_ = std::make_shared<model::CompositeTask>(*simple_task_, *array_simple_tasks_);
        array_composite_tasks_=std::make_shared<model::ManyCompositeTasks>();
        array_hierarchical_tasks_=std::make_shared<model::ManyHierarchicalTasks>();

        auto generator = std::make_shared<model::IdGenerator>();
        auto manager = std::make_shared<model::TaskManager>(generator);
        controller_ = std::make_shared<ControllerMock>(manager);
    }

protected:
    std::shared_ptr<model::Task> task_;
    std::shared_ptr<model::TaskId> id_;
    std::shared_ptr<model::TaskWithId> simple_task_;
    std::shared_ptr<model::ManyTasksWithId> array_simple_tasks_;
    std::shared_ptr<model::CompositeTask> composite_task_;
    std::shared_ptr<model::ManyCompositeTasks> array_composite_tasks_;
    std::shared_ptr<model::ManyHierarchicalTasks> array_hierarchical_tasks_;

    std::shared_ptr<ControllerMock> controller_;
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
    auto command = std::make_shared<Show>(true, model::TasksSortBy::ID);
    EXPECT_CALL(*controller_, ShowAll(model::TasksSortBy::ID))
            .Times(1)
            .WillOnce(Return(*array_composite_tasks_));

    Result result{command->execute(controller_)};
    EXPECT_TRUE(result.many_composite_tasks.has_value());
}

TEST_F(CommandTest, shouldShowOnlyTasks) {
    auto command = std::make_shared<Show>(false, model::TasksSortBy::PRIORITY);
    EXPECT_CALL(*controller_, ShowParents(model::TasksSortBy::PRIORITY))
            .Times(1)
            .WillOnce(Return(*array_simple_tasks_));

    Result result{command->execute(controller_)};
    EXPECT_TRUE(result.many_tasks.has_value());
}

TEST_F(CommandTest, shouldShowSomeTask) {
    auto command = std::make_shared<ShowTask>(*id_, model::TasksSortBy::DATE);
    EXPECT_CALL(*controller_, ShowTask(*id_, model::TasksSortBy::DATE))
            .Times(1)
            .WillOnce(Return(*composite_task_));

    Result result{command->execute(controller_)};
    EXPECT_TRUE(result.composite_task.has_value());
}

TEST_F(CommandTest, shouldHandleErrorWhenShowSomeTask) {
    auto command = std::make_shared<ShowTask>(*id_, model::TasksSortBy::ID);
    EXPECT_CALL(*controller_, ShowTask(*id_, model::TasksSortBy::ID))
            .Times(1)
            .WillOnce(Return(std::nullopt));

    Result result{command->execute(controller_)};
    EXPECT_TRUE(result.error.has_value());
}

TEST_F(CommandTest, shouldShowByLabel) {
    auto command = std::make_shared<ShowLabel>("label", model::TasksSortBy::PRIORITY);
    EXPECT_CALL(*controller_, ShowLabel("label", model::TasksSortBy::PRIORITY))
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