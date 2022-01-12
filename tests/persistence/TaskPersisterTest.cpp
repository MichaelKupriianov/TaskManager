#include "gtest/gtest.h"
#include "persistence/TaskPersister.h"
#include "utilities/ComparisonProtoObjects.h"
#include "utilities/CreateProtoObjects.h"

class TaskPersisterTest : public ::testing::Test {
};

TEST_F(TaskPersisterTest, shouldSaveLoadOneTask) {
    model::ManyHierarchicalTasks tasks;
    tasks.emplace_back(model::CreateTaskId(1),
                       model::CreateHierarchicalTask(model::CreateTask("first"),
                                                     std::nullopt));
    TaskPersister persister;
    ASSERT_TRUE(persister.Save(tasks, "persister_test_1"));

    std::optional<model::ManyHierarchicalTasks> result = persister.Load("persister_test_1");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), tasks);
    remove("persister_test_1");
}

TEST_F(TaskPersisterTest, shouldSaveLoadSeveralTasks) {
    model::ManyHierarchicalTasks tasks;
    tasks.emplace_back(model::CreateTaskId(3),
                       model::CreateHierarchicalTask(model::CreateTask("first"),
                                                     model::CreateTaskId(0)));
    tasks.emplace_back(model::CreateTaskId(4),
                       model::CreateHierarchicalTask(model::CreateTask("second"),
                                                     model::CreateTaskId(1)));
    tasks.emplace_back(model::CreateTaskId(5),
                       model::CreateHierarchicalTask(model::CreateTask("third"),
                                                     model::CreateTaskId(2)));
    TaskPersister persister;
    ASSERT_TRUE(persister.Save(tasks, "persister_test_2"));

    std::optional<model::ManyHierarchicalTasks> result = persister.Load("persister_test_2");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), tasks);
    remove("persister_test_2");
}

TEST_F(TaskPersisterTest, shouldSaveLoadTasksWithAndWithoutAParent) {
    model::ManyHierarchicalTasks tasks;
    tasks.emplace_back(model::CreateTaskId(1),
                       model::CreateHierarchicalTask(model::CreateTask("first"),
                                                     std::nullopt));
    tasks.emplace_back(model::CreateTaskId(2),
                       model::CreateHierarchicalTask(model::CreateTask("second"),
                                                     model::CreateTaskId(0)));
    TaskPersister persister;
    ASSERT_TRUE(persister.Save(tasks, "persister_test_3"));

    std::optional<model::ManyHierarchicalTasks> result;
    result = persister.Load("persister_test_3");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), tasks);
    remove("persister_test_3");
}