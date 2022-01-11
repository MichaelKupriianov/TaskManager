#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ui/command/Command.h"
#include "model/TaskManagerMock.h"
#include "persistence/TaskPersisterMock.h"
#include "model/IdGenerator.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::_;

using namespace ui::command;

class CommandTest : public ::testing::Test {
public:
    void SetUp() override {
        task_ = std::make_shared<proto::Task>();
        id_ = std::make_shared<proto::TaskId>();
        simple_task_ = std::make_shared<proto::SimpleTask>(*id_, *task_);
        array_simple_tasks_ = std::make_shared<proto::ArraySimpleTasks>();
        composite_task_ = std::make_shared<proto::CompositeTask>(*simple_task_, *array_simple_tasks_);
        array_composite_tasks_=std::make_shared<proto::ArrayCompositeTasks>();
        array_hierarchical_tasks_=std::make_shared<proto::ArrayHierarchicalTasks>();

        auto generator = std::make_shared<model::IdGenerator>();
        persister_ = std::make_shared<TaskPersisterMock>();
        manager_ = std::make_shared<TaskManagerMock>(generator);
        resources_ = std::make_shared<Resources>(manager_, persister_);
    }

protected:
    std::shared_ptr<proto::Task> task_;
    std::shared_ptr<proto::TaskId> id_;
    std::shared_ptr<proto::SimpleTask> simple_task_;
    std::shared_ptr<proto::ArraySimpleTasks> array_simple_tasks_;
    std::shared_ptr<proto::CompositeTask> composite_task_;
    std::shared_ptr<proto::ArrayCompositeTasks> array_composite_tasks_;
    std::shared_ptr<proto::ArrayHierarchicalTasks> array_hierarchical_tasks_;

    std::shared_ptr<TaskPersisterMock> persister_;
    std::shared_ptr<TaskManagerMock> manager_;
    std::shared_ptr<Resources> resources_;
};

TEST_F(CommandTest, shouldQuit) {
    auto command = std::make_shared<Quit>();
    Result result{command->execute(resources_)};
    EXPECT_TRUE(result.finished);
}

TEST_F(CommandTest, shouldAddTask) {
    auto command = std::make_shared<Add>(*task_);
    EXPECT_CALL(*manager_, AddTask(*task_))
            .Times(1)
            .WillOnce(Return(true));

    Result result{command->execute(resources_)};
    EXPECT_FALSE(result.finished);
}

TEST_F(CommandTest, shouldAddSubTask) {
    auto command = std::make_shared<AddSub>(*task_, *id_);
    EXPECT_CALL(*manager_, AddSubTask(*task_, *id_))
            .Times(1)
            .WillOnce(Return(true));

    Result result{command->execute(resources_)};
    EXPECT_FALSE(result.finished);
}

TEST_F(CommandTest, shouldHandleErrorWhenAddSubTask) {
    auto command = std::make_shared<AddSub>(*task_, *id_);
    EXPECT_CALL(*manager_, AddSubTask(*task_, *id_))
            .Times(1)
            .WillOnce(Return(false));

    Result result{command->execute(resources_)};
    EXPECT_FALSE(result.finished);
    EXPECT_TRUE(result.error.has_value());
}

TEST_F(CommandTest, shouldEditTask) {
    auto command = std::make_shared<Edit>(*id_, *task_);
    EXPECT_CALL(*manager_, Edit(*id_, *task_))
            .Times(1)
            .WillOnce(Return(true));

    Result result{command->execute(resources_)};
    EXPECT_FALSE(result.finished);
}

TEST_F(CommandTest, shouldHandleErrorWhenEditTask) {
    auto command = std::make_shared<Edit>(*id_, *task_);
    EXPECT_CALL(*manager_, Edit(*id_, *task_))
            .Times(1)
            .WillOnce(Return(false));

    Result result{command->execute(resources_)};
    EXPECT_FALSE(result.finished);
    EXPECT_TRUE(result.error.has_value());
}

TEST_F(CommandTest, shouldCompleteTask) {
    auto command = std::make_shared<Complete>(*id_);
    EXPECT_CALL(*manager_, Complete(* id_))
            .Times(1)
            .WillOnce(Return(true));

    Result result{command->execute(resources_)};
    EXPECT_FALSE(result.finished);
}

TEST_F(CommandTest, shouldHandleErrorWhenCompletetTask) {
    auto command = std::make_shared<Complete>(*id_);
    EXPECT_CALL(*manager_, Complete(* id_))
            .Times(1)
            .WillOnce(Return(false));

    Result result{command->execute(resources_)};
    EXPECT_FALSE(result.finished);
    EXPECT_TRUE(result.error.has_value());
}

TEST_F(CommandTest, shouldDeleteTask) {
    auto command = std::make_shared<Delete>(*id_);
    EXPECT_CALL(*manager_, Delete(* id_))
            .Times(1)
            .WillOnce(Return(true));

    Result result{command->execute(resources_)};
    EXPECT_FALSE(result.finished);
}

TEST_F(CommandTest, shouldHandleErrorWhenDeleteTask) {
    auto command = std::make_shared<Delete>(*id_);
    EXPECT_CALL(*manager_, Delete(* id_))
            .Times(1)
            .WillOnce(Return(false));

    Result result{command->execute(resources_)};
    EXPECT_FALSE(result.finished);
    EXPECT_TRUE(result.error.has_value());
}

TEST_F(CommandTest, shouldShowTasksWithSubtasks) {
    auto command = std::make_shared<Show>(true, model::TasksSortBy::ID);
    EXPECT_CALL(*manager_, ShowAll(model::TasksSortBy::ID))
            .Times(1)
            .WillOnce(Return(*array_composite_tasks_));

    Result result{command->execute(resources_)};
    EXPECT_TRUE(result.all_tasks.has_value());
}

TEST_F(CommandTest, shouldShowOnlyTasks) {
    auto command = std::make_shared<Show>(false, model::TasksSortBy::PRIORITY);
    EXPECT_CALL(*manager_, ShowParents(model::TasksSortBy::PRIORITY))
            .Times(1)
            .WillOnce(Return(*array_simple_tasks_));

    Result result{command->execute(resources_)};
    EXPECT_TRUE(result.array.has_value());
}

TEST_F(CommandTest, shouldShowSomeTask) {
    auto command = std::make_shared<ShowTask>(*id_, model::TasksSortBy::DATE);
    EXPECT_CALL(*manager_, ShowTask(*id_, model::TasksSortBy::DATE))
            .Times(1)
            .WillOnce(Return(*composite_task_));

    Result result{command->execute(resources_)};
    EXPECT_TRUE(result.task.has_value());
}

TEST_F(CommandTest, shouldHandleErrorWhenShowSomeTask) {
    auto command = std::make_shared<ShowTask>(*id_, model::TasksSortBy::ID);
    EXPECT_CALL(*manager_, ShowTask(*id_, model::TasksSortBy::ID))
            .Times(1)
            .WillOnce(Return(std::nullopt));

    Result result{command->execute(resources_)};
    EXPECT_TRUE(result.error.has_value());
}

TEST_F(CommandTest, shouldShowByLabel) {
    auto command = std::make_shared<ShowLabel>("label", model::TasksSortBy::PRIORITY);
    EXPECT_CALL(*manager_, ShowLabel("label", model::TasksSortBy::PRIORITY))
            .Times(1)
            .WillOnce(Return(*array_simple_tasks_));

    Result result{command->execute(resources_)};
    EXPECT_TRUE(result.array.has_value());
}

TEST_F(CommandTest, shouldSaveToFile) {
    auto command = std::make_shared<Save>("filename");

    EXPECT_CALL(*manager_, GetAllTasks())
            .Times(1)
            .WillOnce(Return(*array_hierarchical_tasks_));
    EXPECT_CALL(*persister_, Save(*array_hierarchical_tasks_, "filename"))
            .Times(1)
            .WillOnce(Return(true));

    Result result{command->execute(resources_)};
    EXPECT_FALSE(result.finished);
}

TEST_F(CommandTest, shouldHandleErrorWhenSaveToFile) {
    auto command = std::make_shared<Save>("filename");

    EXPECT_CALL(*manager_, GetAllTasks())
            .Times(1)
            .WillOnce(Return(*array_hierarchical_tasks_));
    EXPECT_CALL(*persister_, Save(*array_hierarchical_tasks_, "filename"))
            .Times(1)
            .WillOnce(Return(false));

    Result result{command->execute(resources_)};
    EXPECT_TRUE(result.error.has_value());
}

TEST_F(CommandTest, shouldLoadFromFile) {
    auto command = std::make_shared<Load>("filename");

    EXPECT_CALL(*manager_, Rewrite(*array_hierarchical_tasks_))
            .Times(1);
    EXPECT_CALL(*persister_, Load("filename"))
            .Times(1)
            .WillOnce(Return(*array_hierarchical_tasks_));

    Result result{command->execute(resources_)};
    EXPECT_FALSE(result.finished);
}

TEST_F(CommandTest, shouldHandleErrorWhenLoadFromFile) {
    auto command = std::make_shared<Load>("filename");

    EXPECT_CALL(*persister_, Load("filename"))
            .Times(1)
            .WillOnce(Return(std::nullopt));

    Result result{command->execute(resources_)};
    EXPECT_TRUE(result.error.has_value());
}