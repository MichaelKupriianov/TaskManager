#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"TaskManager.h"

using ::testing::Return;
using ::testing::AtLeast;

class MockIdGenerator : public IdGenerator {
public:
    MOCK_METHOD(TaskId, GenerateId, (), (override));
};

class TaskManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::unique_ptr<MockIdGenerator> ptr_gen(new MockIdGenerator);
        EXPECT_CALL(*ptr_gen, GenerateId())
                .Times(AtLeast(1))
                .WillOnce(Return(TaskId::Create(0).value()))
                .WillRepeatedly(Return(TaskId::Create(1).value()));

        task1_ = std::make_unique<Task>(Task::Create(Task::Arguments::Create("first",
                                                                             Task::Priority::MEDIUM, 500)).value());
        task2_ = std::make_unique<Task>(Task::Create(Task::Arguments::Create("second",
                                                                             Task::Priority::NONE, 1000)).value());
        manager_ = std::make_unique<TaskManager>(std::move(ptr_gen));
        manager_->Add(*task1_);
    }

protected:
    std::unique_ptr<TaskManager> manager_;
    std::unique_ptr<Task> task1_, task2_;
};

TEST_F(TaskManagerTest, shouldCreateTask) {
    EXPECT_EQ(manager_->ShowAll()[0].first.second, *task1_);
}

TEST_F(TaskManagerTest, shouldEditTask) {
    EXPECT_TRUE(manager_->Edit(TaskId::Create(0).value(), *task2_));
    EXPECT_EQ(manager_->ShowAll()[0].first.second, *task2_);
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenEditIfIDNotExist) {
    EXPECT_FALSE(manager_->Edit(TaskId::Create(1).value(), *task2_));
}

TEST_F(TaskManagerTest, shouldCompleteTask) {
    EXPECT_TRUE(manager_->Complete(TaskId::Create(0).value()));
    EXPECT_EQ(manager_->ShowAll().size(), 0);
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenCompleteIfIDNotExist) {
    EXPECT_FALSE(manager_->Complete(TaskId::Create(1).value()));
}

TEST_F(TaskManagerTest, shouldDeleteTask) {
    EXPECT_TRUE(manager_->Delete(TaskId::Create(0).value()));
    EXPECT_EQ(manager_->ShowAll().size(), 0);
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenDeleteIfIDNotExist) {
    EXPECT_FALSE(manager_->Delete(TaskId::Create(1).value()));
}

TEST_F(TaskManagerTest, shouldEditLabel) {
    EXPECT_TRUE(manager_->Label(TaskId::Create(0).value(), "first"));
    EXPECT_EQ(manager_->ShowAll()[0].first.second.label(), "first");
}

TEST_F(TaskManagerTest, shouldReturnFalseIfIdGeneratorWorksdBadly) {
    EXPECT_TRUE(manager_->Add(*task2_));
    EXPECT_FALSE(manager_->Add(*task2_));
}