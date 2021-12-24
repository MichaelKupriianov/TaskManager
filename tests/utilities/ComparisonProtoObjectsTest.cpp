#include "gtest/gtest.h"
#include "utilities/ComparisonProtoObjects.h"

class ComparisonProtoObjectsTest : public ::testing::Test {
};

TEST_F(ComparisonProtoObjectsTest, OperatorLessForTaskIdShouldWork) {
    proto::TaskId id_1, id_2;

    id_1.set_value(0);
    id_2.set_value(1);
    EXPECT_LT(id_1, id_2);

    id_1.set_value(1000);
    id_2.set_value(200);
    EXPECT_LT(id_2, id_1);
}

TEST_F(ComparisonProtoObjectsTest, OperatorEqualsForTaskIdShouldWork) {
    proto::TaskId id_1, id_2;

    id_1.set_value(5);
    id_2.set_value(5);
    EXPECT_TRUE(id_1 == id_2);

    id_1.set_value(700);
    id_2.set_value(701);
    EXPECT_FALSE(id_2 == id_1);
}

TEST_F(ComparisonProtoObjectsTest, OperatorEqualsForTaskShouldWork) {
    proto::Task task_1, task_2;

    task_1.set_title("first");
    task_2.set_title("second");
    EXPECT_FALSE(task_1 == task_2);

    task_2.set_title("first");
    EXPECT_TRUE(task_1 == task_2);

    task_1.set_priority(proto::Task_Priority_LOW);
    task_2.set_priority(proto::Task_Priority_LOW);
    EXPECT_TRUE(task_1 == task_2);

    task_1.set_label("label");
    EXPECT_FALSE(task_1 == task_2);

    task_2.set_label("label");
    EXPECT_TRUE(task_1 == task_2);
}

TEST_F(ComparisonProtoObjectsTest, OperatorEqualsForHierarchicalTaskShouldWork) {
    proto::Task t_1, t_2;
    t_1.set_title("first");
    t_2.set_title("second");

    proto::TaskId id_1, id_2;
    id_1.set_value(5);
    id_2.set_value(5);

    proto::HierarchicalTask task_1, task_2;
    task_1.set_allocated_task(new proto::Task(t_1));
    task_2.set_allocated_task(new proto::Task(t_2));
    task_1.set_allocated_parent(new proto::TaskId(id_1));
    task_2.set_allocated_parent(new proto::TaskId(id_2));

    EXPECT_FALSE(task_1 == task_2);

    task_1.mutable_task()->set_title("second");
    EXPECT_TRUE(task_1 == task_2);
}