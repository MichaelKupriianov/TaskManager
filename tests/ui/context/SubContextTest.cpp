#include"gtest/gtest.h"
#include"SubContext.h"
#include"Comparison.h"

class SubContextTest : public ::testing::Test {
};

TEST_F(SubContextTest, shouldWorkWithTask) {
    SubContext context;
    context.task()->set_title("title");
    context.task()->set_priority(Task_Priority_LOW);
    context.task()->set_label("qwerty");
    EXPECT_EQ(context.task()->title(), "title");
    EXPECT_EQ(context.task()->priority(), Task_Priority_LOW);
    EXPECT_FALSE(context.task()->has_date());
    EXPECT_EQ(context.task()->label(), "qwerty");
}

TEST_F(SubContextTest, shouldFinished) {
    SubContext context;
    EXPECT_EQ(context.if_finished(), false);
    context.finished();
    EXPECT_EQ(context.if_finished(), true);
}