#include"gtest/gtest.h"
#include"SubContext.h"

class SubContextTest : public ::testing::Test {
};

TEST_F(SubContextTest, shouldWorkWithTask) {
    SubContext context;
    context.set_task(Task::Arguments::Create("title", Task::Priority::LOU, 1000, "label"));
    EXPECT_EQ(context.task_title(), "title");
    EXPECT_EQ(context.task_priority(), Task::Priority::LOU);
    EXPECT_EQ(context.task_date(), 1000);
    EXPECT_EQ(context.task_label(), "label");
    EXPECT_EQ(context.task_state(), Task::Condition::NONE);
}

TEST_F(SubContextTest, shouldFinished) {
    SubContext context;
    EXPECT_EQ(context.if_finished(), false);
    context.finished();
    EXPECT_EQ(context.if_finished(), true);
}