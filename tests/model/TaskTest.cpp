#include"gtest/gtest.h"
#include"Task.h"

class TaskTest : public ::testing::Test {};

TEST_F(TaskTest, shouldCreateRegularTask) {
    const Task task(Task::Create("first", Task::Priority::NONE, 500));
    EXPECT_EQ(task.title(), "first");
    EXPECT_EQ(task.priority(), Task::Priority::NONE);
    EXPECT_EQ(task.date(), 500);
}

TEST_F(TaskTest, shouldThrowExceptionIfEmptyTitle) {
    EXPECT_THROW(Task task(Task::Create("", Task::Priority::NONE, 500)), std::runtime_error);
}

TEST_F(TaskTest, shouldThrowExceptionIfNegativeTime) {
    EXPECT_THROW(Task task(Task::Create("first", Task::Priority::NONE, -5)), std::runtime_error);
}