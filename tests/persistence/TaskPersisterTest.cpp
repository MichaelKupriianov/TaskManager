#include "gtest/gtest.h"
#include "persistence/TaskPersister.h"
#include "utilities/ComparisonProtoObjects.h"
#include "utilities/CreateProtoObjects.h"

class TaskPersisterTest : public ::testing::Test {
};

TEST_F(TaskPersisterTest, shouldSaveLoadOneTask) {
    proto::ArrayHierarchicalTasks tasks;
    tasks.emplace_back(proto::CreateTaskId(1),
                       proto::CreateHierarchicalTask(proto::CreateTask("first"),
                                                     std::nullopt));
    TaskPersister persister;
    ASSERT_TRUE(persister.Save(tasks, "persister_test_1"));

    std::optional<proto::ArrayHierarchicalTasks> result = persister.Load("persister_test_1");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), tasks);
    remove("persister_test_1");
}

TEST_F(TaskPersisterTest, shouldSaveLoadSeveralTasks) {
    proto::ArrayHierarchicalTasks tasks;
    tasks.emplace_back(proto::CreateTaskId(3),
                       proto::CreateHierarchicalTask(proto::CreateTask("first"),
                                                     proto::CreateTaskId(0)));
    tasks.emplace_back(proto::CreateTaskId(4),
                       proto::CreateHierarchicalTask(proto::CreateTask("second"),
                                                     proto::CreateTaskId(1)));
    tasks.emplace_back(proto::CreateTaskId(5),
                       proto::CreateHierarchicalTask(proto::CreateTask("third"),
                                                     proto::CreateTaskId(2)));
    TaskPersister persister;
    ASSERT_TRUE(persister.Save(tasks, "persister_test_2"));

    std::optional<proto::ArrayHierarchicalTasks> result = persister.Load("persister_test_2");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), tasks);
    remove("persister_test_2");
}

TEST_F(TaskPersisterTest, shouldSaveLoadTasksWithAndWithoutAParent) {
    proto::ArrayHierarchicalTasks tasks;
    tasks.emplace_back(proto::CreateTaskId(1),
                       proto::CreateHierarchicalTask(proto::CreateTask("first"),
                                                     std::nullopt));
    tasks.emplace_back(proto::CreateTaskId(2),
                       proto::CreateHierarchicalTask(proto::CreateTask("second"),
                                                     proto::CreateTaskId(0)));
    TaskPersister persister;
    ASSERT_TRUE(persister.Save(tasks, "persister_test_3"));

    std::optional<proto::ArrayHierarchicalTasks> result;
    result = persister.Load("persister_test_3");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), tasks);
    remove("persister_test_3");
}