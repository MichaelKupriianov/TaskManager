#include"gtest/gtest.h"
#include"Context.h"

class ContextTest : public ::testing::Test {
};

TEST_F(ContextTest, shouldWorkWithTaskId) {
    Context context;
    context.set_id(17);
    EXPECT_EQ(context.id(), TaskId::Create(17));
    context.set_id(118);
    EXPECT_EQ(context.id(), TaskId::Create(118));
}

TEST_F(ContextTest, shouldFinished) {
    Context context;
    EXPECT_EQ(context.if_finished(), false);
    context.finished();
    EXPECT_EQ(context.if_finished(), true);
}