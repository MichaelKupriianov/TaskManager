#include "gtest/gtest.h"
#include "utilities/CreateProtoObjects.h"
#include "utilities/ComparisonProtoObjects.h"

class CreateProtoObjectsTest : public ::testing::Test {
};

TEST_F(CreateProtoObjectsTest, ShiuldCreateTaskId) {
    const int value{3};
    const proto::TaskId id{proto::CreateTaskId(value)};

    EXPECT_EQ(id.value(), value);
}

TEST_F(CreateProtoObjectsTest, ShouldCreateTask) {
    const std::string title{"first"};
    const proto::Task_Priority priority{proto::Task_Priority_MEDIUM};
    const time_t date{1000};
    const std::string label{"label"};
    const proto::Task task{proto::CreateTask(title, priority, date, label)};

    EXPECT_EQ(task.title(), title);
    EXPECT_EQ(task.priority(), priority);
    EXPECT_EQ(task.date().seconds(), date);
    EXPECT_EQ(task.label(), label);
    EXPECT_EQ(task.status(), proto::Task_Status_IN_PROGRESS);
}

TEST_F(CreateProtoObjectsTest, ShouldCreateHierarchicalTask) {
    const int value{3};
    const proto::TaskId id{proto::CreateTaskId(value)};
    const std::string title{"first"};
    const proto::Task task{proto::CreateTask(title)};
    const proto::HierarchicalTask hierarchical_task{proto::CreateHierarchicalTask(task, id)};

    ASSERT_TRUE(hierarchical_task.has_task());
    EXPECT_EQ(hierarchical_task.task(), task);
    ASSERT_TRUE(hierarchical_task.has_parent());
    EXPECT_EQ(hierarchical_task.parent(), id);
}

TEST_F(CreateProtoObjectsTest, ShouldCreateHierarchicalTaskWithoutParent) {
    const std::string title{"first"};
    const proto::Task task{proto::CreateTask(title)};
    const proto::HierarchicalTask hierarchical_task{proto::CreateHierarchicalTask(task, std::nullopt)};

    ASSERT_TRUE(hierarchical_task.has_task());
    EXPECT_EQ(hierarchical_task.task(), task);
    EXPECT_FALSE(hierarchical_task.has_parent());
}