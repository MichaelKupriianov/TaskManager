#include"gtest/gtest.h"
#include"Factory.h"

class FactoryTest : public ::testing::Test {
};

TEST_F(FactoryTest, shouldCreateStep) {
    EXPECT_TRUE(std::dynamic_pointer_cast<StepQuit>(std::shared_ptr(Factory::CreateStep("quit"))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepHelp>(std::shared_ptr(Factory::CreateStep("help"))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepAdd>(std::shared_ptr(Factory::CreateStep("add"))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepEdit>(std::shared_ptr(Factory::CreateStep("edit"))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepComplete>(std::shared_ptr(Factory::CreateStep("complete"))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepDelete>(std::shared_ptr(Factory::CreateStep("delete"))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepLabel>(std::shared_ptr(Factory::CreateStep("label"))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepShow>(std::shared_ptr(Factory::CreateStep("show"))));
}

TEST_F(FactoryTest, shouldThrowExceptionIfStepNonExist) {
    EXPECT_THROW(Factory::CreateStep("first"), std::runtime_error);
    EXPECT_THROW(Factory::CreateStep("add edit"), std::runtime_error);
}

TEST_F(FactoryTest, shouldReturnNextStep) {
    EXPECT_TRUE(std::dynamic_pointer_cast<StepCommand>(std::shared_ptr(Factory::GetNextStep())));
}

TEST_F(FactoryTest, shouldReturnNextSubStep) {
    std::shared_ptr<SubStep> step = Factory::GetNextSubStep();
    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepTitle>(step));
}