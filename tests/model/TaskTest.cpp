#include"gtest/gtest.h"
#include"Task.h"

class TaskTest : public ::testing::Test {
};

TEST_F(TaskTest, shouldCreateRegularTask) {
    const Task task(Task::Create({"first", Task::Priority::NONE, 500, "label", Task::State::DONE}));
    EXPECT_EQ(task.title(), "first");
    EXPECT_EQ(task.priority(), Task::Priority::NONE);
    EXPECT_EQ(task.date(), 500);
    EXPECT_EQ(task.label(), "label");
    EXPECT_EQ(task.state(), Task::State::DONE);
}

TEST_F(TaskTest, shouldCreateDefaultTask) {
    const Task task(Task::Create({"first"}));
    EXPECT_EQ(task.title(), "first");
    EXPECT_EQ(task.priority(), Task::Priority::NONE);
    EXPECT_EQ(task.date(), 0);
    EXPECT_EQ(task.label(), "");
    EXPECT_EQ(task.state(), Task::State::NONE);
}

TEST_F(TaskTest, shouldThrowExceptionIfEmptyTitle) {
    EXPECT_THROW(Task task(Task::Create({"", Task::Priority::NONE, 500})), std::runtime_error);
}

TEST_F(TaskTest, shouldThrowExceptionIfNegativeTime) {
    EXPECT_THROW(Task task(Task::Create({"first", Task::Priority::NONE, -5})), std::runtime_error);
}

TEST_F(TaskTest, shouldCompareTasks) {
    const Task task1(Task::Create({"first", Task::Priority::NONE, 500}));
    const Task task2(Task::Create({"second", Task::Priority::MEDIUM, 1000}));
    EXPECT_EQ(task1, task1);
    EXPECT_FALSE(task1 == task2);
}

TEST_F(TaskTest, shouldConvertPriorityToString) {
    EXPECT_EQ(PriorityToString(Task::Priority::HIGH), "high");
    EXPECT_EQ(PriorityToString(Task::Priority::MEDIUM), "medium");
    EXPECT_EQ(PriorityToString(Task::Priority::LOU), "lou");
    EXPECT_EQ(PriorityToString(Task::Priority::NONE), "none");
}

TEST_F(TaskTest, shouldConvertStringToPriority) {
    EXPECT_EQ(StringToPriority("high"), Task::Priority::HIGH);
    EXPECT_EQ(StringToPriority("medium"), Task::Priority::MEDIUM);
    EXPECT_EQ(StringToPriority("lou"), Task::Priority::LOU);
    EXPECT_EQ(StringToPriority("none"), Task::Priority::NONE);
    EXPECT_THROW(StringToPriority("priority"), std::runtime_error);
}