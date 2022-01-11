#include "gtest/gtest.h"
#include "ui/Context.h"

using namespace ui;

class ContextTest : public ::testing::Test {
};

TEST_F(ContextTest, shouldWorkWithCommand) {
    ui::Context context;
    ASSERT_FALSE(context.has_command());

    auto command = std::make_shared<command::Quit>();
    context.set_command(command);
    ASSERT_TRUE(context.has_command());
    EXPECT_TRUE(std::dynamic_pointer_cast<command::Quit>(std::shared_ptr(
            context.command())));

    context.set_command(std::nullopt);
    EXPECT_FALSE(context.has_command());
}

TEST_F(ContextTest, shouldWorkWithResult) {
    ui::Context context;
    ASSERT_FALSE(context.has_result());

    auto result = std::make_shared<command::Result>(true);
    context.set_result(result);
    ASSERT_TRUE(context.has_result());
    EXPECT_TRUE(context.result()->finished);

    context.set_result(std::nullopt);
    EXPECT_FALSE(context.has_result());
}

TEST_F(ContextTest, shouldWorkWithTask) {
    SubContext context;
    context.task()->set_title("title");
    context.task()->set_priority(proto::Task_Priority_LOW);
    context.task()->set_label("qwerty");

    EXPECT_EQ(context.task()->title(), "title");
    EXPECT_EQ(context.task()->priority(), proto::Task_Priority_LOW);
    EXPECT_FALSE(context.task()->has_date());
    EXPECT_EQ(context.task()->label(), "qwerty");
}

TEST_F(ContextTest, shouldFinished) {
    SubContext context;
    EXPECT_EQ(context.if_finished(), false);
    context.finished();
    EXPECT_EQ(context.if_finished(), true);
}