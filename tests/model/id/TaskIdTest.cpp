#include"gtest/gtest.h"
#include"TaskId.h"

class TaskIdTest : public ::testing::Test {
};

TEST_F(TaskIdTest, shouldGreateRegularTaskID) {
    EXPECT_EQ(TaskId::Create(0).has_value(), true);
    EXPECT_EQ(TaskId::Create(1).has_value(), true);
    EXPECT_EQ(TaskId::Create(15).has_value(), true);
    EXPECT_EQ(TaskId::Create(0).value().value(), 0);
    EXPECT_EQ(TaskId::Create(1).value().value(), 1);
    EXPECT_EQ(TaskId::Create(15).value().value(), 15);
}

TEST_F(TaskIdTest, shouldReturnNulloptIfNegativeID) {
    EXPECT_EQ(TaskId::Create(-1).has_value(), false);
    EXPECT_EQ(TaskId::Create(-10).has_value(), false);
}

TEST_F(TaskIdTest, shouldCopyTaskID) {
    TaskId id(TaskId::Create(0).value());
    EXPECT_EQ(id, TaskId::Create(0).value());
}

TEST_F(TaskIdTest, shouldWorkComparisonOperators) {
    EXPECT_LT(TaskId::Create(0).value(), TaskId::Create(1).value());
    EXPECT_GT(TaskId::Create(5).value(), TaskId::Create(4).value());
    EXPECT_EQ(TaskId::Create(3).value(), TaskId::Create(3).value());
}

TEST_F(TaskIdTest, shouldReturnNonExistentId) {
    EXPECT_EQ(TaskId::NotExistentId().value(), -1);
}