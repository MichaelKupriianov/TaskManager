#include"gtest/gtest.h"
#include"id/TaskId.h"

class TaskIdTest : public ::testing::Test {};

TEST_F(TaskIdTest, shouldGreateRegularTaskID) {
    EXPECT_EQ(TaskId::Create(0).value(), 0);
    EXPECT_EQ(TaskId::Create(1).value(), 1);
}

TEST_F(TaskIdTest, shouldThrowExceptionIfNegativeID) {
    EXPECT_THROW(TaskId::Create(-1), std::range_error);
}

TEST_F(TaskIdTest, shouldCopyTaskID) {
    TaskId id(TaskId::Create(0));
    EXPECT_EQ(id, TaskId::Create(0));
}

TEST_F(TaskIdTest, shouldWorkComparisonOperator) {
    EXPECT_LT(TaskId::Create(0), TaskId::Create(1));
    EXPECT_EQ(TaskId::Create(3), TaskId::Create(3));
}