#include "gtest/gtest.h"
#include "utilities/CreateProtoObjects.h"
#include "utilities/ComparisonProtoObjects.h"

class CreateProtoObjectsTest : public ::testing::Test {
};

TEST_F(CreateProtoObjectsTest, ShiuldCreateTaskId) {
    const int value{3};
    const model::TaskId id{model::CreateTaskId(value)};

    EXPECT_EQ(id.value(), value);
}

TEST_F(CreateProtoObjectsTest, ShouldCreateTask) {
    const std::string title{"first"};
    const model::Task_Priority priority{model::Task_Priority_MEDIUM};
    const time_t date{1000};
    const std::vector<std::string> labels{"label_1", "label_2"};
    const model::Task task{model::CreateTask(title, priority, date, labels)};

    EXPECT_EQ(task.title(), title);
    EXPECT_EQ(task.priority(), priority);
    EXPECT_EQ(task.date().seconds(), date);
    EXPECT_EQ(task.labels()[0], labels[0]);
    EXPECT_EQ(task.labels()[1], labels[1]);
    EXPECT_EQ(task.status(), model::Task_Status_IN_PROGRESS);
}

TEST_F(CreateProtoObjectsTest, ShouldCreateHierarchicalTask) {
    const int value{3};
    const model::TaskId id{model::CreateTaskId(value)};
    const std::string title{"first"};
    const model::Task task{model::CreateTask(title)};
    const model::HierarchicalTask hierarchical_task{model::CreateHierarchicalTask(task, id)};

    ASSERT_TRUE(hierarchical_task.has_task());
    EXPECT_EQ(hierarchical_task.task(), task);
    ASSERT_TRUE(hierarchical_task.has_parent());
    EXPECT_EQ(hierarchical_task.parent(), id);
}

TEST_F(CreateProtoObjectsTest, ShouldCreateHierarchicalTaskWithoutParent) {
    const std::string title{"first"};
    const model::Task task{model::CreateTask(title)};
    const model::HierarchicalTask hierarchical_task{model::CreateHierarchicalTask(task, std::nullopt)};

    ASSERT_TRUE(hierarchical_task.has_task());
    EXPECT_EQ(hierarchical_task.task(), task);
    EXPECT_FALSE(hierarchical_task.has_parent());
}