#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"TaskManager.h"

using::testing::Return;
using::testing::AtLeast;

class MockIdGenerator: public IdGenerator {
public:
    MOCK_METHOD(TaskId, GenerateId, (), (override));
};

class TaskManagerTest : public ::testing::Test {
protected:
    void SetUp() {
        std::unique_ptr<MockIdGenerator> ptr_gen(new MockIdGenerator);
        EXPECT_CALL(*ptr_gen, GenerateId())
                .Times(AtLeast(1))
                .WillOnce(Return(TaskId::Create(0)))
                .WillRepeatedly(Return(TaskId::Create(1)));

        task1_=std::make_unique<Task>(Task::Create("first", Task::Priority::MEDIUM, 500));
        task2_=std::make_unique<Task>(Task::Create("second", Task::Priority::NONE, 1000));
        manager_=std::make_unique<TaskManager>(std::move(ptr_gen));
        manager_->Add(*task1_);
    }
protected:
    std::unique_ptr<TaskManager> manager_;
    std::unique_ptr<Task> task1_, task2_;
};

TEST_F(TaskManagerTest, shouldCreateTask) {
    EXPECT_EQ(manager_->getTask(TaskId::Create(0)), *task1_);
}

TEST_F(TaskManagerTest, shouldEditTask) {
    manager_->Edit(TaskId::Create(0), *task2_);
    EXPECT_EQ(manager_->getTask(TaskId::Create(0)), *task2_);
}

TEST_F(TaskManagerTest, shouldThrowExceptionWhenEditIfIDNotExist) {
    EXPECT_THROW(manager_->Edit(TaskId::Create(1), *task2_), std::range_error);
}

TEST_F(TaskManagerTest, shouldCompareTask) {
    manager_->Complete(TaskId::Create(0));
    EXPECT_EQ(manager_->Show().size(), 0);
}

TEST_F(TaskManagerTest, shouldThrowExceptionWhenCompleteIfIDNotExist) {
    EXPECT_THROW(manager_->Complete(TaskId::Create(1)), std::range_error);
}

TEST_F(TaskManagerTest, shouldDeleteTask) {
    manager_->Delete(TaskId::Create(0));
    EXPECT_EQ(manager_->Show().size(), 0);
}

TEST_F(TaskManagerTest, shouldShowTasks) {
    manager_->Add(*task2_);
    std::map<TaskId, Task> expected;
    expected.insert({TaskId::Create(0), *task1_});
    expected.insert({TaskId::Create(1), *task2_});

    EXPECT_EQ(manager_->Show(), std::move(expected));
}

TEST_F(TaskManagerTest, shouldThrowExceptionIfIdGeneratorWorksdBadly) {
    manager_->Add(*task2_);
    EXPECT_THROW(manager_->Add(*task2_), std::runtime_error);
}