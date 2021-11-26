#include"gtest/gtest.h"
#include"Factory.h"

class FactoryTest : public ::testing::Test {
};

TEST_F(FactoryTest, shouldCreateStep) {
    EXPECT_TRUE(std::dynamic_pointer_cast<StepRoot>(std::shared_ptr(
            Factory::CreateStep(TypeOfStep::ROOT))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepQuit>(std::shared_ptr(
            Factory::CreateStep(TypeOfStep::QUIT))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepHelp>(std::shared_ptr(
            Factory::CreateStep(TypeOfStep::HELP))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepAdd>(std::shared_ptr(
            Factory::CreateStep(TypeOfStep::ADD))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepEdit>(std::shared_ptr(
            Factory::CreateStep(TypeOfStep::EDIT))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepComplete>(std::shared_ptr(
            Factory::CreateStep(TypeOfStep::COMPLETE))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepDelete>(std::shared_ptr(
            Factory::CreateStep(TypeOfStep::DELETE))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepLabel>(std::shared_ptr(
            Factory::CreateStep(TypeOfStep::LABEL))));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepShow>(std::shared_ptr(
            Factory::CreateStep(TypeOfStep::SHOW))));
}

TEST_F(FactoryTest, shouldReturnRootStep) {
    EXPECT_TRUE(std::dynamic_pointer_cast<StepRoot>(std::shared_ptr(
            Factory::GetRootStep())));
}
