#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"model/TaskManager.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;

class IdGeneratorMock : public model::IdGenerator {
public:
    MOCK_METHOD(model::TaskId, GenerateId, (), (override));
};

class TaskManagerTest : public ::testing::Test {
public:
    void SetUp() override {
        generator_ = std::make_shared<IdGeneratorMock>();
        manager_ = std::make_shared<model::TaskManager>(generator_);
    }

protected:
    std::shared_ptr<IdGeneratorMock> generator_;
    std::shared_ptr<model::TaskManager> manager_;
};

TEST_F(TaskManagerTest, shouldAddTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(model::CreateTaskId(0)))
            .WillOnce(Return(model::CreateTaskId(1)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_EQ(manager_->ShowTask(model::CreateTaskId(0), model::TasksSortBy::ID).task().task(),
              model::CreateTask("first"));
    EXPECT_TRUE(manager_->AddTask(model::CreateTask("second")));
    EXPECT_EQ(manager_->ShowTask(model::CreateTaskId(1), model::TasksSortBy::ID).task().task(),
              model::CreateTask("second"));
}

TEST_F(TaskManagerTest, shouldReturnFalseIfIdGeneratorWorksdBadly) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(model::CreateTaskId(0)))
            .WillOnce(Return(model::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_FALSE(manager_->AddTask(model::CreateTask("first")));
}

TEST_F(TaskManagerTest, shouldAddSubTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(model::CreateTaskId(0)))
            .WillOnce(Return(model::CreateTaskId(1)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(model::CreateTask("second"), model::CreateTaskId(0)));
    EXPECT_EQ(manager_->ShowTask(model::CreateTaskId(1), model::TasksSortBy::ID).task().task(),
              model::CreateTask("second"));
}

TEST_F(TaskManagerTest, shouldReturnFalseIfParentsIdIsIncorrect) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(model::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_FALSE(manager_->AddSubTask(model::CreateTask("second"), model::CreateTaskId(3)));
}

TEST_F(TaskManagerTest, shouldReturnFalseIfAddSubtaskToSubtask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(model::CreateTaskId(0)))
            .WillOnce(Return(model::CreateTaskId(1)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(model::CreateTask("second"), model::CreateTaskId(0)));
    EXPECT_FALSE(manager_->AddSubTask(model::CreateTask("third"), model::CreateTaskId(1)));
}

TEST_F(TaskManagerTest, shouldReturnFalseIfAddSubtaskToCompletedTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(model::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_TRUE(manager_->Complete(model::CreateTaskId(0)));
    EXPECT_FALSE(manager_->AddSubTask(model::CreateTask("second"), model::CreateTaskId(0)));
}

TEST_F(TaskManagerTest, shouldEditTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(model::CreateTaskId(0)))
            .WillOnce(Return(model::CreateTaskId(1)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(model::CreateTask("second"), model::CreateTaskId(0)));
    EXPECT_TRUE(manager_->Edit(model::CreateTaskId(0), model::CreateTask("third")));
    EXPECT_TRUE(manager_->Edit(model::CreateTaskId(1), model::CreateTask("fourth")));
    EXPECT_EQ(manager_->ShowTask(model::CreateTaskId(0), model::TasksSortBy::ID).task().task(),
              model::CreateTask("third"));
    EXPECT_EQ(manager_->ShowTask(model::CreateTaskId(1), model::TasksSortBy::ID).task().task(),
              model::CreateTask("fourth"));
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenEditIfIDNotExist) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(model::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_FALSE(manager_->Edit(model::CreateTaskId(1), model::CreateTask("second")));
}

TEST_F(TaskManagerTest, shouldReturnFalseIfEditCompletedTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(model::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_TRUE(manager_->Complete(model::CreateTaskId(0)));
    EXPECT_FALSE(manager_->Edit(model::CreateTaskId(0), model::CreateTask("second")));
}

TEST_F(TaskManagerTest, shouldCompleteTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(model::CreateTaskId(0)))
            .WillOnce(Return(model::CreateTaskId(1)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(model::CreateTask("second"), model::CreateTaskId(0)));
    EXPECT_TRUE(manager_->Complete(model::CreateTaskId(0)));
    EXPECT_EQ(manager_->ShowAll(model::TasksSortBy::ID).tasks().size(), 0);
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenCompleteIfIDNotExist) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(model::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_FALSE(manager_->Complete(model::CreateTaskId(1)));
}

TEST_F(TaskManagerTest, shouldDeleteTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(model::CreateTaskId(0)))
            .WillOnce(Return(model::CreateTaskId(1)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(model::CreateTask("second"), model::CreateTaskId(0)));
    EXPECT_TRUE(manager_->Delete(model::CreateTaskId(0)));
    EXPECT_EQ(manager_->ShowAll(model::TasksSortBy::ID).tasks().size(), 0);
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenDeleteIfIDNotExist) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(model::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_FALSE(manager_->Delete(model::CreateTaskId(1)));
}

TEST_F(TaskManagerTest, shouldShowTaskWithSubtasks) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(3)
            .WillOnce(Return(model::CreateTaskId(0)))
            .WillOnce(Return(model::CreateTaskId(1)))
            .WillOnce(Return(model::CreateTaskId(2)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(model::CreateTask("second"), model::CreateTaskId(0)));
    EXPECT_TRUE(manager_->AddSubTask(model::CreateTask("third"), model::CreateTaskId(0)));

    std::optional<model::CompositeTask> result =
            manager_->ShowTask(model::CreateTaskId(0), model::TasksSortBy::ID);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().task().task(), model::CreateTask("first"));
    EXPECT_EQ(result.value().children()[0].task(), model::CreateTask("second"));
    EXPECT_EQ(result.value().children()[1].task(), model::CreateTask("third"));
}

TEST_F(TaskManagerTest, shouldShowTasksByLabel) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(4)
            .WillOnce(Return(model::CreateTaskId(0)))
            .WillOnce(Return(model::CreateTaskId(1)))
            .WillOnce(Return(model::CreateTaskId(2)))
            .WillOnce(Return(model::CreateTaskId(3)));

    model::Task first(model::CreateTask("first", model::Task_Priority_LOW, 100, {"label_1", "label_2"}));
    model::Task second(model::CreateTask("second", model::Task_Priority_MEDIUM, 200, {"label_2", "label_3"}));
    model::Task third(model::CreateTask("third", model::Task_Priority_NONE, 300, {"label_1", "label_3"}));
    model::Task fourth(model::CreateTask("fourth", model::Task_Priority_HIGH, 500, {"label_2"}));
    ASSERT_TRUE(manager_->AddTask(first));
    ASSERT_TRUE(manager_->AddSubTask(second, model::CreateTaskId(0)));
    ASSERT_TRUE(manager_->AddTask(third));
    ASSERT_TRUE(manager_->AddSubTask(fourth, model::CreateTaskId(2)));

    model::ManyTasksWithId result =
            manager_->ShowByLabel("label_2", model::TasksSortBy::ID);
    ASSERT_EQ(result.tasks().size(), 3);
    EXPECT_EQ(result.tasks()[0].task(), first);
    EXPECT_EQ(result.tasks()[1].task(), second);
    EXPECT_EQ(result.tasks()[2].task(), fourth);
}

TEST_F(TaskManagerTest, shouldReturnNullptrIfIDNotExist) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(model::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    model::CompositeTask result = manager_->ShowTask(model::CreateTaskId(1), model::TasksSortBy::ID);
    ASSERT_FALSE(result.has_task());
}

TEST_F(TaskManagerTest, shouldShowAll) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(4)
            .WillOnce(Return(model::CreateTaskId(0)))
            .WillOnce(Return(model::CreateTaskId(1)))
            .WillOnce(Return(model::CreateTaskId(2)))
            .WillOnce(Return(model::CreateTaskId(3)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(model::CreateTask("second"), model::CreateTaskId(0)));
    EXPECT_TRUE(manager_->AddTask(model::CreateTask("third")));
    EXPECT_TRUE(manager_->AddSubTask(model::CreateTask("fourth"), model::CreateTaskId(2)));

    model::ManyCompositeTasks result =
            manager_->ShowAll(model::TasksSortBy::ID);
    EXPECT_EQ(result.tasks()[0].task().task(), model::CreateTask("first"));
    EXPECT_EQ(result.tasks()[0].children()[0].task(), model::CreateTask("second"));
    EXPECT_EQ(result.tasks()[1].task().task(), model::CreateTask("third"));
    EXPECT_EQ(result.tasks()[1].children()[0].task(), model::CreateTask("fourth"));
}

TEST_F(TaskManagerTest, shouldGetAllTasks) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(model::CreateTaskId(0)))
            .WillOnce(Return(model::CreateTaskId(1)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(model::CreateTask("second"), model::CreateTaskId(0)));

    model::ManyHierarchicalTasks result = manager_->GetAllTasks();
    EXPECT_EQ(result[0].first, model::CreateTaskId(0));
    EXPECT_EQ(result[0].second, model::CreateHierarchicalTask(model::CreateTask("first"), std::nullopt));
    EXPECT_EQ(result[1].first, model::CreateTaskId(1));
    EXPECT_EQ(result[1].second, model::CreateHierarchicalTask(model::CreateTask("second"), model::CreateTaskId(0)));
}

TEST_F(TaskManagerTest, shouldRewriteTaskManager) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(model::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(model::CreateTask("first")));

    model::ManyHierarchicalTasks tasks;
    tasks.emplace_back(model::CreateTaskId(1),
                       model::CreateHierarchicalTask(model::CreateTask("first"),
                                                     std::nullopt));
    tasks.emplace_back(model::CreateTaskId(2),
                       model::CreateHierarchicalTask(model::CreateTask("second"),
                                                     model::CreateTaskId(0)));
    manager_->Overwrite(tasks);

    model::ManyHierarchicalTasks result = manager_->GetAllTasks();
    EXPECT_EQ(result, tasks);
}