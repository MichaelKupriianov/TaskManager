#include"gtest/gtest.h"
#include"GeneralizedTask.h"

class GeneralizedTaskTest : public ::testing::Test {
};

TEST_F(GeneralizedTaskTest, shouldCreateGeneralizedTest) {
    Task task(Task::Create(Task::Arguments::Create("first", Task::Priority::LOU)));
    TaskId parent(TaskId::NotExistentId());
    GeneralizedTask gen_task(GeneralizedTask::Create(task, parent));
    EXPECT_EQ(gen_task.task(), task);
    EXPECT_EQ(gen_task.parent(), parent);
}

TEST_F(GeneralizedTaskTest, shouldCompareGeneralizedTasks) {
    Task task(Task::Create(Task::Arguments::Create("first", Task::Priority::LOU)));
    TaskId parent1(TaskId::NotExistentId());
    TaskId parent2(TaskId::Create(0));
    GeneralizedTask gen_task1(GeneralizedTask::Create(task, parent1));
    GeneralizedTask gen_task2(GeneralizedTask::Create(task, parent2));
    EXPECT_EQ(gen_task1, gen_task1);
    EXPECT_FALSE(gen_task1 == gen_task2);
}