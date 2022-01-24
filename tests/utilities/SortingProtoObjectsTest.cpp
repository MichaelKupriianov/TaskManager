#include "gtest/gtest.h"
#include "utilities/SortingProtoObjects.h"
#include "utilities/ComparisonProtoObjects.h"
#include "utilities/CreateProtoObjects.h"

using namespace model;

class SortingProtoObjectsTest : public ::testing::Test {
};

TEST_F(SortingProtoObjectsTest, shouldSortById) {
    TaskWithId task_1{CreateTaskId(0), CreateTask("first")},
            task_2{CreateTaskId(2), CreateTask("second")},
            task_3{CreateTaskId(1), CreateTask("third")};
    ManyTasksWithId tasks{task_1, task_2, task_3};

    SortTasksWithId(tasks, TasksSortBy::ID);
    EXPECT_EQ(tasks[0], task_1);
    EXPECT_EQ(tasks[1], task_3);
    EXPECT_EQ(tasks[2], task_2);
}

TEST_F(SortingProtoObjectsTest, shouldSortByPriority) {
    TaskWithId task_1{CreateTaskId(0), CreateTask("", model::Task_Priority_LOW)},
            task_2{CreateTaskId(1), CreateTask("", model::Task_Priority_NONE)},
            task_3{CreateTaskId(2), CreateTask("", model::Task_Priority_HIGH)};
    ManyTasksWithId tasks{task_1, task_2, task_3};

    SortTasksWithId(tasks, TasksSortBy::PRIORITY);
    EXPECT_EQ(tasks[0], task_3);
    EXPECT_EQ(tasks[1], task_1);
    EXPECT_EQ(tasks[2], task_2);
}

TEST_F(SortingProtoObjectsTest, shouldSortByDate) {
    TaskWithId task_1{CreateTaskId(0), CreateTask("", model::Task_Priority_NONE, 200)},
            task_2{CreateTaskId(1), CreateTask("", model::Task_Priority_NONE, 100)},
            task_3{CreateTaskId(2), CreateTask("", model::Task_Priority_NONE, 300)};
    ManyTasksWithId tasks{task_1, task_2, task_3};

    SortTasksWithId(tasks, TasksSortBy::DATE);
    EXPECT_EQ(tasks[0], task_2);
    EXPECT_EQ(tasks[1], task_1);
    EXPECT_EQ(tasks[2], task_3);
}