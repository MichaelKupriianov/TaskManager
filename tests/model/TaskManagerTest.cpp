#include"gtest/gtest.h"
#include"../../src/model/TaskManager.h"

class TaskManagerTest : public ::testing::Test {
protected:
    bool CompareTasks(Task first, Task second) {
        return (first.title() == second.title() && first.priority() == second.priority() &&
                first.date() == second.date());
    }

    bool CompareMaps(std::map<TaskId, Task> &&first, std::map<TaskId, Task> &&second) {
        if (first.size() != second.size()) return false;
        bool result = true;
        auto it1 = first.begin();
        auto it2 = second.begin();
        while (it1 != first.end()) {
            result &= ((*it1).first == (*it2).first);
            result &= CompareTasks((*it1).second, (*it2).second);
            it1++; it2++;
        }
        return result;
    }
};

TEST_F(TaskManagerTest, shouldCreateTask) {
    TaskManager manager;
    Task task(Task::Create("first", Task::Priority::MEDIUM, 500));
    manager.Add(task);
    EXPECT_TRUE(CompareTasks(manager.getTask(TaskId::Create(0)), task));
}

TEST_F(TaskManagerTest, shouldEditTask) {
    TaskManager manager;
    manager.Add(Task::Create("first", Task::Priority::MEDIUM, 500));
    Task modified_task(Task::Create("second", Task::Priority::NONE, 700));
    manager.Edit(TaskId::Create(0), modified_task);
    EXPECT_TRUE(CompareTasks(manager.getTask(TaskId::Create(0)), modified_task));
}

TEST_F(TaskManagerTest, shouldThrowExceptionWhenEditIfIDNotExist) {
    TaskManager manager;
    manager.Add(Task::Create("first", Task::Priority::MEDIUM, 500));
    Task modified_task(Task::Create("second", Task::Priority::NONE, 700));
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
    Task task1(Task::Create("first", Task::Priority::MEDIUM, 500));
    Task task2(Task::Create("second", Task::Priority::HIGH, 1000));
    std::map<TaskId, Task> map;
    map.insert({TaskId::Create(0), task1});
    map.insert({TaskId::Create(1), task2});
    manager.Add(task1);
    manager.Add(task2);
    EXPECT_TRUE(CompareMaps(manager.Show(), std::move(map)));
}