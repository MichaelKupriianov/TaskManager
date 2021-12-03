#include"gtest/gtest.h"
#include"Context.h"

class ContextTest : public ::testing::Test {
};

TEST_F(ContextTest, shouldWorkWithCommand) {
    Context context;
    EXPECT_EQ(context.command(), Command::NONE);
    context.set_command(Command::ADD);
    EXPECT_EQ(context.command(), Command::ADD);
    context.set_command(Command::QUIT);
    EXPECT_EQ(context.command(), Command::QUIT);
}

TEST_F(ContextTest, shouldWorkWithTaskId) {
    Context context;
    context.set_id(17);
    EXPECT_EQ(context.id(), TaskId::Create(17));
    context.set_id(118);
    EXPECT_EQ(context.id(), TaskId::Create(118));
}

TEST_F(ContextTest, shouldWorkWithLabel) {
    Context context;
    context.set_label("first");
    EXPECT_EQ(context.label(), "first");
    context.set_label("second");
    EXPECT_EQ(context.label(), "second");
}

TEST_F(ContextTest, shouldWorkWithTask) {
    Context context;
    Task task(Task::Create(Task::Arguments::Create("title", Task::Priority::LOU, 1000, "label")).value());
    context.set_task(task);
    EXPECT_EQ(context.task(), task);
}