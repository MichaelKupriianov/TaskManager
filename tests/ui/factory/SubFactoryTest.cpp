#include"gtest/gtest.h"
#include"SubFactory.h"

class SubFactoryTest : public ::testing::Test {
};

TEST_F(SubFactoryTest, shouldReturnRootStep) {
    SubFactory factory;
    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepTitle>(std::shared_ptr(
            factory.GetRootSubStep())));
}

TEST_F(SubFactoryTest, shouldReturnNextStepAfterTitle) {
    SubFactory factory;
    SubStepTitle step;
    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepPriority>(std::shared_ptr(
            factory.GetNextSubStep(step))));
}

TEST_F(SubFactoryTest, shouldReturnNextStepAfterPriprity) {
    SubFactory factory;
    SubStepPriority step;
    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepDate>(std::shared_ptr(
            factory.GetNextSubStep(step))));
}

TEST_F(SubFactoryTest, shouldReturnNextStepAfterDate) {
    SubFactory factory;
    SubStepDate step;
    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepLabel>(std::shared_ptr(
            factory.GetNextSubStep(step))));
}

TEST_F(SubFactoryTest, shouldReturnNextStepAfterLabel) {
    SubFactory factory;
    SubStepLabel step;
    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepLabel>(std::shared_ptr(
            factory.GetNextSubStep(step))));
}