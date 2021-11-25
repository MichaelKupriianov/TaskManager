#include"gtest/gtest.h"
#include"ConsoleManager.h"

class ConsoleManagerTest : public ::testing::Test {
};

TEST_F(ConsoleManagerTest, shouldConvertPriorityToString) {
    EXPECT_EQ(PriorityToString(Task::Priority::HIGH), "high");
    EXPECT_EQ(PriorityToString(Task::Priority::MEDIUM), "medium");
    EXPECT_EQ(PriorityToString(Task::Priority::LOU), "lou");
    EXPECT_EQ(PriorityToString(Task::Priority::NONE), "none");
}

TEST_F(ConsoleManagerTest, shouldConvertStringToPriority) {
    EXPECT_EQ(StringToPriority("high"), Task::Priority::HIGH);
    EXPECT_EQ(StringToPriority("medium"), Task::Priority::MEDIUM);
    EXPECT_EQ(StringToPriority("lou"), Task::Priority::LOU);
    EXPECT_EQ(StringToPriority("none"), Task::Priority::NONE);
    EXPECT_THROW(StringToPriority("priority"), std::runtime_error);
}