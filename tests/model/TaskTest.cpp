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