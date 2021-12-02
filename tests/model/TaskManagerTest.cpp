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
                .WillOnce(Return(TaskId::Create(1).value()))
                .WillRepeatedly(Return(TaskId::Create(2).value()));

        task1_ = std::make_unique<Task>(Task::Create(Task::Arguments::Create("first",
                                                                             Task::Priority::MEDIUM, 500)).value());
        task2_ = std::make_unique<Task>(Task::Create(Task::Arguments::Create("second",
                                                                             Task::Priority::NONE, 1000)).value());
        task3_ = std::make_unique<Task>(Task::Create(Task::Arguments::Create("third",
                                                                             Task::Priority::HIGH, 750)).value());
        manager_ = std::make_unique<TaskManager>(std::move(ptr_gen));
    }

protected:
    std::unique_ptr<TaskManager> manager_;
    std::unique_ptr<Task> task1_, task2_, task3_;
};

TEST_F(TaskManagerTest, shouldAddTask) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_EQ(manager_->ShowChild().front().second, *task1_);
    EXPECT_TRUE(manager_->Add(*task2_, TaskId::Create(0).value()));
    EXPECT_EQ(manager_->ShowChild(TaskId::Create(0).value()).front().second, *task2_);
}

TEST_F(TaskManagerTest, shouldReturnFalseIfIdGeneratorWorksdBadly) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_FALSE(manager_->Add(*task1_));
}

TEST_F(TaskManagerTest, shouldReturnFalseIfParentsIdIsIncorrect) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_FALSE(manager_->Add(*task2_, TaskId::Create(5).value()));
    EXPECT_FALSE(manager_->Add(*task2_, TaskId::Create(1).value()));
}

TEST_F(TaskManagerTest, shouldEditTask) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_TRUE(manager_->Edit(TaskId::Create(0).value(), *task2_));
    EXPECT_EQ(manager_->ShowChild().front().second, *task2_);
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenEditIfIDNotExist) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_FALSE(manager_->Edit(TaskId::Create(1).value(), *task2_));
}

TEST_F(TaskManagerTest, shouldCompleteTask) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_TRUE(manager_->Complete(TaskId::Create(0).value()));
    EXPECT_EQ(manager_->ShowChild().size(), 0);
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenCompleteIfIDNotExist) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_FALSE(manager_->Complete(TaskId::Create(1).value()));
}

TEST_F(TaskManagerTest, shouldDeleteTask) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_TRUE(manager_->Delete(TaskId::Create(0).value()));
    EXPECT_EQ(manager_->ShowChild().size(), 0);
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenDeleteIfIDNotExist) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_FALSE(manager_->Delete(TaskId::Create(1).value()));
}

TEST_F(TaskManagerTest, shouldEditLabel) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_TRUE(manager_->Label(TaskId::Create(0).value(), "first"));
    EXPECT_EQ(manager_->ShowChild().front().second.label(), "first");
}

TEST_F(TaskManagerTest, shouldReturnFalseWhenLabelIfIdNotExist) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_FALSE(manager_->Label(TaskId::Create(1).value(), "first"));
}

TEST_F(TaskManagerTest, shouldSortById) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_TRUE(manager_->Add(*task2_));
    EXPECT_TRUE(manager_->Add(*task3_));
    EXPECT_EQ(manager_->ShowChild()[0].second, *task1_);
    EXPECT_EQ(manager_->ShowChild()[1].second, *task2_);
    EXPECT_EQ(manager_->ShowChild()[2].second, *task3_);
}

TEST_F(TaskManagerTest, shouldSortByPriority) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_TRUE(manager_->Add(*task2_));
    EXPECT_TRUE(manager_->Add(*task3_));
    EXPECT_EQ(manager_->ShowChild(TaskId::NotExistentId(), TaskManager::Sort::PRIORITY)[0].second, *task3_);
    EXPECT_EQ(manager_->ShowChild(TaskId::NotExistentId(), TaskManager::Sort::PRIORITY)[1].second, *task1_);
    EXPECT_EQ(manager_->ShowChild(TaskId::NotExistentId(), TaskManager::Sort::PRIORITY)[2].second, *task2_);
}

TEST_F(TaskManagerTest, shouldSortByDate) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_TRUE(manager_->Add(*task2_));
    EXPECT_TRUE(manager_->Add(*task3_));
    EXPECT_EQ(manager_->ShowChild(TaskId::NotExistentId(), TaskManager::Sort::DATE)[0].second, *task1_);
    EXPECT_EQ(manager_->ShowChild(TaskId::NotExistentId(), TaskManager::Sort::DATE)[1].second, *task3_);
    EXPECT_EQ(manager_->ShowChild(TaskId::NotExistentId(), TaskManager::Sort::DATE)[2].second, *task2_);
}

TEST_F(TaskManagerTest, shouldShowChild) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_TRUE(manager_->Add(*task2_, TaskId::Create(0).value()));
    EXPECT_TRUE(manager_->Add(*task3_, TaskId::Create(0).value()));
    EXPECT_EQ(manager_->ShowChild(TaskId::NotExistentId())[0].second, *task1_);
    EXPECT_EQ(manager_->ShowChild(TaskId::Create(0).value())[0].second, *task2_);
    EXPECT_EQ(manager_->ShowChild(TaskId::Create(0).value())[1].second, *task3_);
}

TEST_F(TaskManagerTest, shouldShowAll) {
    EXPECT_TRUE(manager_->Add(*task1_));
    EXPECT_TRUE(manager_->Add(*task2_, TaskId::Create(0).value()));
    EXPECT_TRUE(manager_->Add(*task3_, TaskId::Create(0).value()));
    EXPECT_EQ(manager_->ShowAll().size(), 1);
    EXPECT_EQ(manager_->ShowAll()[0].first.second, *task1_);
    EXPECT_EQ(manager_->ShowAll()[0].second[0].second, *task2_);
    EXPECT_EQ(manager_->ShowAll()[0].second[1].second, *task3_);
}