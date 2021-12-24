#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"model/TaskManager.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::_;

class IdGeneratorMock : public model::IdGenerator {
public:
    MOCK_METHOD(proto::TaskId, GenerateId, (), (override));
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
            .WillOnce(Return(proto::CreateTaskId(0)))
            .WillOnce(Return(proto::CreateTaskId(1)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_EQ(manager_->ShowTask(proto::CreateTaskId(0), model::TasksSortBy::ID).value().first.second,
              proto::CreateTask("first"));
    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("second")));
    EXPECT_EQ(manager_->ShowTask(proto::CreateTaskId(1), model::TasksSortBy::ID).value().first.second,
              proto::CreateTask("second"));
}

TEST_F(TaskManagerTest, shouldReturnFalseIfIdGeneratorWorksdBadly) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(proto::CreateTaskId(0)))
            .WillOnce(Return(proto::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_FALSE(manager_->AddTask(proto::CreateTask("first")));
}

TEST_F(TaskManagerTest, shouldAddSubTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(proto::CreateTaskId(0)))
            .WillOnce(Return(proto::CreateTaskId(1)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(proto::CreateTask("second"), proto::CreateTaskId(0)));
    EXPECT_EQ(manager_->ShowTask(proto::CreateTaskId(1), model::TasksSortBy::ID).value().first.second,
              proto::CreateTask("second"));
}

TEST_F(TaskManagerTest, shouldReturnFalseIfParentsIdIsIncorrect) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(proto::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_FALSE(manager_->AddSubTask(proto::CreateTask("second"), proto::CreateTaskId(3)));
}

TEST_F(TaskManagerTest, shouldReturnFalseIfAddSubtaskToSubtask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(proto::CreateTaskId(0)))
            .WillOnce(Return(proto::CreateTaskId(1)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(proto::CreateTask("second"), proto::CreateTaskId(0)));
    EXPECT_FALSE(manager_->AddSubTask(proto::CreateTask("third"), proto::CreateTaskId(1)));
}

TEST_F(TaskManagerTest, shouldReturnFalseIfAddSubtaskToCompletedTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(proto::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_TRUE(manager_->Complete(proto::CreateTaskId(0)));
    EXPECT_FALSE(manager_->AddSubTask(proto::CreateTask("second"), proto::CreateTaskId(0)));
}

TEST_F(TaskManagerTest, shouldEditTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(proto::CreateTaskId(0)))
            .WillOnce(Return(proto::CreateTaskId(1)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(proto::CreateTask("second"), proto::CreateTaskId(0)));
    EXPECT_TRUE(manager_->Edit(proto::CreateTaskId(0), proto::CreateTask("third")));
    EXPECT_TRUE(manager_->Edit(proto::CreateTaskId(1), proto::CreateTask("fourth")));
    EXPECT_EQ(manager_->ShowTask(proto::CreateTaskId(0), model::TasksSortBy::ID).value().first.second,
              proto::CreateTask("third"));
    EXPECT_EQ(manager_->ShowTask(proto::CreateTaskId(1), model::TasksSortBy::ID).value().first.second,
              proto::CreateTask("fourth"));
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenEditIfIDNotExist) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(proto::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_FALSE(manager_->Edit(proto::CreateTaskId(1), proto::CreateTask("second")));
}

TEST_F(TaskManagerTest, shouldCompleteTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(proto::CreateTaskId(0)))
            .WillOnce(Return(proto::CreateTaskId(1)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(proto::CreateTask("second"), proto::CreateTaskId(0)));
    EXPECT_TRUE(manager_->Complete(proto::CreateTaskId(0)));
    EXPECT_EQ(manager_->ShowAll(model::TasksSortBy::ID).size(), 0);
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenCompleteIfIDNotExist) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(proto::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_FALSE(manager_->Complete(proto::CreateTaskId(1)));
}

TEST_F(TaskManagerTest, shouldDeleteTask) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(proto::CreateTaskId(0)))
            .WillOnce(Return(proto::CreateTaskId(1)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(proto::CreateTask("second"), proto::CreateTaskId(0)));
    EXPECT_TRUE(manager_->Delete(proto::CreateTaskId(0)));
    EXPECT_EQ(manager_->ShowAll(model::TasksSortBy::ID).size(), 0);
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenDeleteIfIDNotExist) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(proto::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_FALSE(manager_->Delete(proto::CreateTaskId(1)));
}

TEST_F(TaskManagerTest, shouldSortById) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(3)
            .WillOnce(Return(proto::CreateTaskId(0)))
            .WillOnce(Return(proto::CreateTaskId(1)))
            .WillOnce(Return(proto::CreateTaskId(2)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("second")));
    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("third")));
    EXPECT_EQ(manager_->ShowParents(model::TasksSortBy::ID)[0].second, proto::CreateTask("first"));
    EXPECT_EQ(manager_->ShowParents(model::TasksSortBy::ID)[1].second, proto::CreateTask("second"));
    EXPECT_EQ(manager_->ShowParents(model::TasksSortBy::ID)[2].second, proto::CreateTask("third"));
}

TEST_F(TaskManagerTest, shouldSortByPriority) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(3)
            .WillOnce(Return(proto::CreateTaskId(0)))
            .WillOnce(Return(proto::CreateTaskId(1)))
            .WillOnce(Return(proto::CreateTaskId(2)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("", proto::Task_Priority_LOW)));
    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("", proto::Task_Priority_NONE)));
    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("", proto::Task_Priority_HIGH)));
    EXPECT_EQ(manager_->ShowParents(model::TasksSortBy::PRIORITY)[0].second,
              proto::CreateTask("", proto::Task_Priority_HIGH));
    EXPECT_EQ(manager_->ShowParents(model::TasksSortBy::PRIORITY)[1].second,
              proto::CreateTask("", proto::Task_Priority_LOW));
    EXPECT_EQ(manager_->ShowParents(model::TasksSortBy::PRIORITY)[2].second,
              proto::CreateTask("", proto::Task_Priority_NONE));
}

TEST_F(TaskManagerTest, shouldSortByDate) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(3)
            .WillOnce(Return(proto::CreateTaskId(0)))
            .WillOnce(Return(proto::CreateTaskId(1)))
            .WillOnce(Return(proto::CreateTaskId(2)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("", proto::Task_Priority_NONE, 100)));
    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("", proto::Task_Priority_NONE, 300)));
    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("", proto::Task_Priority_NONE, 200)));
    EXPECT_EQ(manager_->ShowParents(model::TasksSortBy::DATE)[0].second,
              CreateTask("", proto::Task_Priority_NONE, 100));
    EXPECT_EQ(manager_->ShowParents(model::TasksSortBy::DATE)[1].second,
              CreateTask("", proto::Task_Priority_NONE, 200));
    EXPECT_EQ(manager_->ShowParents(model::TasksSortBy::DATE)[2].second,
              CreateTask("", proto::Task_Priority_NONE, 300));
}

TEST_F(TaskManagerTest, shouldShowTaskWithSubtasks) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(3)
            .WillOnce(Return(proto::CreateTaskId(0)))
            .WillOnce(Return(proto::CreateTaskId(1)))
            .WillOnce(Return(proto::CreateTaskId(2)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(proto::CreateTask("second"), proto::CreateTaskId(0)));
    EXPECT_TRUE(manager_->AddSubTask(proto::CreateTask("third"), proto::CreateTaskId(0)));

    std::optional<proto::CompositeTask> result =
            manager_->ShowTask(proto::CreateTaskId(0), model::TasksSortBy::ID);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().first.second, proto::CreateTask("first"));
    EXPECT_EQ(result.value().second[0].second, proto::CreateTask("second"));
    EXPECT_EQ(result.value().second[1].second, proto::CreateTask("third"));
}

TEST_F(TaskManagerTest, shouldReturnNullptrIfIDNotExist) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(proto::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    std::optional<proto::CompositeTask> result =
            manager_->ShowTask(proto::CreateTaskId(1), model::TasksSortBy::ID);
    ASSERT_FALSE(result.has_value());
}

TEST_F(TaskManagerTest, shouldShowAll) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(4)
            .WillOnce(Return(proto::CreateTaskId(0)))
            .WillOnce(Return(proto::CreateTaskId(1)))
            .WillOnce(Return(proto::CreateTaskId(2)))
            .WillOnce(Return(proto::CreateTaskId(3)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(proto::CreateTask("second"), proto::CreateTaskId(0)));
    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("third")));
    EXPECT_TRUE(manager_->AddSubTask(proto::CreateTask("fourth"), proto::CreateTaskId(2)));

    proto::ArrayCompositeTasks result =
            manager_->ShowAll(model::TasksSortBy::ID);
    EXPECT_EQ(result[0].first.second, proto::CreateTask("first"));
    EXPECT_EQ(result[0].second[0].second, proto::CreateTask("second"));
    EXPECT_EQ(result[1].first.second, proto::CreateTask("third"));
    EXPECT_EQ(result[1].second[0].second, proto::CreateTask("fourth"));
}

TEST_F(TaskManagerTest, shouldGetAllTasks) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(2)
            .WillOnce(Return(proto::CreateTaskId(0)))
            .WillOnce(Return(proto::CreateTaskId(1)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));
    EXPECT_TRUE(manager_->AddSubTask(proto::CreateTask("second"), proto::CreateTaskId(0)));

    proto::ArrayHierarchicalTasks result = manager_->GetAllTasks();
    EXPECT_EQ(result[0].first, proto::CreateTaskId(0));
    EXPECT_EQ(result[0].second, proto::CreateHierarchicalTask(proto::CreateTask("first"), std::nullopt));
    EXPECT_EQ(result[1].first, proto::CreateTaskId(1));
    EXPECT_EQ(result[1].second, proto::CreateHierarchicalTask(proto::CreateTask("second"), proto::CreateTaskId(0)));
}

TEST_F(TaskManagerTest, shouldRewriteTaskManager) {
    EXPECT_CALL(*generator_, GenerateId())
            .Times(1)
            .WillOnce(Return(proto::CreateTaskId(0)));

    EXPECT_TRUE(manager_->AddTask(proto::CreateTask("first")));

    proto::ArrayHierarchicalTasks tasks;
    tasks.emplace_back(proto::CreateTaskId(1),
                       proto::CreateHierarchicalTask(proto::CreateTask("first"),
                                                     std::nullopt));
    tasks.emplace_back(proto::CreateTaskId(2),
                       proto::CreateHierarchicalTask(proto::CreateTask("second"),
                                                     proto::CreateTaskId(0)));
    manager_->Rewrite(tasks);

    proto::ArrayHierarchicalTasks result = manager_->GetAllTasks();
    EXPECT_EQ(result, tasks);
}
