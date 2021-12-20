#include"gtest/gtest.h"
#include"Persister.h"
#include"Comparison.h"

class PersisterTest : public ::testing::Test {
public:
    using GenTask = std::pair<TaskId, GeneralizedTask>;
public:
    GenTask CreateGenTask(const std::string &title, Task_Priority priority, time_t time,
                          const std::string &label, int task_id, int parent_id) {
        Task task;
        task.set_title(title);
        task.set_priority(priority);
        google::protobuf::Timestamp date;
        date.set_seconds(time);
        task.set_allocated_date(new google::protobuf::Timestamp(date));
        task.set_label(label);
        TaskId parent;
        parent.set_value(parent_id);

        GeneralizedTask generalized_task;
        generalized_task.set_allocated_task(new Task(task));
        if (parent.value() != -1) generalized_task.set_allocated_parent(new TaskId(parent));

        TaskId id;
        id.set_value(task_id);
        return {id, generalized_task};
    }
};

TEST_F(PersisterTest, shouldSaveLoadOneTask) {
    std::vector<GenTask> tasks;
    tasks.emplace_back(CreateGenTask("first", Task_Priority_LOW,
                                     1000, "label", 0, 1));
    Persister persister;
    ASSERT_TRUE(persister.Save(tasks, "first"));
    std::optional<std::vector<GenTask>> result;
    result = persister.Load("first");
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value().size(), 1);
    EXPECT_EQ(result.value()[0], tasks[0]);
}

TEST_F(PersisterTest, shouldSaveLoadSeveralTasks) {
    std::vector<GenTask> tasks;
    tasks.emplace_back(CreateGenTask("first", Task_Priority_LOW,
                                     1000, "label", 1, 0));
    tasks.emplace_back(CreateGenTask("second", Task_Priority_MEDIUM,
                                     2000, "", 2, 1));
    tasks.emplace_back(CreateGenTask("third", Task_Priority_HIGH,
                                     3000, "label", 3, 2));
    Persister persister;
    ASSERT_TRUE(persister.Save(tasks, "first"));
    std::optional<std::vector<GenTask>> result;
    result = persister.Load("first");
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value().size(), 3);
    EXPECT_EQ(result.value()[0], tasks[0]);
    EXPECT_EQ(result.value()[1], tasks[1]);
    EXPECT_EQ(result.value()[2], tasks[2]);
}

TEST_F(PersisterTest, shouldSaveLoadTasksWithAndWithoutAParent) {
    std::vector<GenTask> tasks;
    tasks.emplace_back(CreateGenTask("first", Task_Priority_NONE,
                                     1000, "", 0, 1));
    tasks.emplace_back(CreateGenTask("second", Task_Priority_LOW,
                                     2000, "", 1, -1));
    Persister persister;
    ASSERT_TRUE(persister.Save(tasks, "first"));
    std::optional<std::vector<GenTask>> result;
    result = persister.Load("first");
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result.value().size(), 2);
    EXPECT_EQ(result.value()[0], tasks[0]);
    EXPECT_EQ(result.value()[1], tasks[1]);
}