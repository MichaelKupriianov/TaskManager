#include"gtest/gtest.h"
#include"TaskManager.h"

class TaskManagerTest : public ::testing::Test {};

TEST_F(TaskManagerTest, shouldCreateTask) {
    TaskManager manager;
    Task task(Task::Create("first", Task::Priority::MEDIUM, 500));
    manager.Add(task);
    EXPECT_EQ(manager.getTask(TaskId::Create(0)), task);
}

TEST_F(TaskManagerTest, shouldEditTask) {
    TaskManager manager;
    manager.Add(Task::Create("first", Task::Priority::MEDIUM, 500));
    const Task modified_task(Task::Create("second", Task::Priority::NONE, 700));
    manager.Edit(TaskId::Create(0), modified_task);
    EXPECT_EQ(manager.getTask(TaskId::Create(0)), modified_task);
}

TEST_F(TaskManagerTest, shouldThrowExceptionWhenEditIfIDNotExist) {
    TaskManager manager;
    manager.Add(Task::Create("first", Task::Priority::MEDIUM, 500));
    const Task modified_task(Task::Create("second", Task::Priority::NONE, 700));
    EXPECT_THROW(manager.Edit(TaskId::Create(1), modified_task), std::range_error);
}

TEST_F(TaskManagerTest, shouldCompareTask) {
    TaskManager manager;
    manager.Add(Task::Create("first", Task::Priority::MEDIUM, 500));
    manager.Complete(TaskId::Create(0));
    EXPECT_EQ(manager.Show().size(), 0);
}

TEST_F(TaskManagerTest, shouldThrowExceptionWhenCompleteIfIDNotExist) {
    TaskManager manager;
    manager.Add(Task::Create("first", Task::Priority::MEDIUM, 500));
    EXPECT_THROW(manager.Complete(TaskId::Create(1)), std::range_error);
}

TEST_F(TaskManagerTest, shouldDeletTask) {
    TaskManager manager;
    manager.Add(Task::Create("first", Task::Priority::MEDIUM, 500));
    manager.Delete(TaskId::Create(0));
    EXPECT_EQ(manager.Show().size(), 0);
}

TEST_F(TaskManagerTest, shouldShowTasks) {
    TaskManager manager;
    const Task task1(Task::Create("first", Task::Priority::MEDIUM, 500));
    const Task task2(Task::Create("second", Task::Priority::HIGH, 1000));
    manager.Add(task1);
    manager.Add(task2);

    std::map<TaskId, Task> expected;
    expected.insert({TaskId::Create(0), task1});
    expected.insert({TaskId::Create(1), task2});

    EXPECT_EQ(manager.Show(), std::move(expected));
}