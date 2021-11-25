#include"gtest/gtest.h"
#include"Context.h"

class ContextTest : public ::testing::Test {
};

TEST_F(ContextTest, shouldWorkWithTask) {
    Context context;
    context.set_task({"title", Task::Priority::LOU, 1000, "label"});
    EXPECT_EQ(context.task_title(), "title");
    EXPECT_EQ(context.task_priority(), Task::Priority::LOU);
    EXPECT_EQ(context.task_date(), 1000);
    EXPECT_EQ(context.task_label(), "label");
    EXPECT_EQ(context.task_state(), Task::State::NONE);
}

TEST_F(ContextTest, shouldGlobalFinished) {
    Context context;
    EXPECT_EQ(context.global_finished(), false);
    context.set_global_finished();
    EXPECT_EQ(context.global_finished(), true);
}

TEST_F(ContextTest, shouldAddFinished) {
    Context context;
    context.set_local_finished(true);
    EXPECT_EQ(context.local_finished(), true);
    context.set_local_finished(false);
    EXPECT_EQ(context.local_finished(), false);
}

TEST_F(ContextTest, shouldEditCurrentStep) {
    Context context;
    context.set_current_step("Add");
    EXPECT_EQ(context.current_step(), "Add");
    context.set_current_step("Edit");
    EXPECT_EQ(context.current_step(), "Edit");
}