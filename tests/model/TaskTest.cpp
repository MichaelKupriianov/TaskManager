#include"gtest/gtest.h"
#include"Task.h"

class TaskTest : public ::testing::Test {
};

TEST_F(TaskTest, shouldCreateRegularTask) {
    const Task task(Task::Create(Task::Arguments::Create("first", Task::Priority::NONE, 500,
                                                         "label", Task::Condition::COMPLETED)).value());
    EXPECT_EQ(task.title(), "first");
    EXPECT_EQ(task.priority(), Task::Priority::NONE);
    EXPECT_EQ(task.date(), 500);
    EXPECT_EQ(task.label(), "label");
    EXPECT_EQ(task.condition(), Task::Condition::COMPLETED);
}

TEST_F(TaskTest, shouldCreateDefaultTask) {
    const Task task(Task::Create(Task::Arguments::Create("first")).value());
    EXPECT_EQ(task.title(), "first");
    EXPECT_EQ(task.priority(), Task::Priority::NONE);
    EXPECT_EQ(task.date(), 0);
    EXPECT_EQ(task.label(), "");
    EXPECT_EQ(task.condition(), Task::Condition::NONE);
}

TEST_F(TaskTest, shouldReturnNulloptIfEmptyTitle) {
    EXPECT_EQ(Task::Create(Task::Arguments::Create("", Task::Priority::NONE, 500)).has_value(),
              false);
}

TEST_F(TaskTest, shouldCompareTasks) {
    const Task task1(Task::Create(Task::Arguments::Create("first", Task::Priority::NONE, 500)).value());
    const Task task2(Task::Create(Task::Arguments::Create("second", Task::Priority::MEDIUM, 1000)).value());
    EXPECT_EQ(task1, task1);
    EXPECT_FALSE(task1 == task2);
}