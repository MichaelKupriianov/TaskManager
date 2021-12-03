#include"gtest/gtest.h"
#include"SubFactory.h"

class SubFactoryTest : public ::testing::Test {
};

TEST_F(SubFactoryTest, shouldReturnRootStep) {
    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepTitle>(std::shared_ptr(
            SubFactory::GetRootSubStep())));
}

TEST_F(SubFactoryTest, shouldReturnNextStepAfterTitle) {
    SubStepTitle step;
    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepPriority>(std::shared_ptr(
            SubFactory::GetNextSubStep(step))));
}

TEST_F(SubFactoryTest, shouldReturnNextStepAfterPriprity) {
    SubStepPriority step;
    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepDate>(std::shared_ptr(
            SubFactory::GetNextSubStep(step))));
}

TEST_F(SubFactoryTest, shouldReturnNextStepAfterTime) {
    SubStepDate step;
    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepDate>(std::shared_ptr(
            SubFactory::GetNextSubStep(step))));
}