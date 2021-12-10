#include"gtest/gtest.h"
#include"Factory.h"

class FactoryTest : public ::testing::Test {
};

TEST_F(FactoryTest, shouldCreateStep) {
    Factory factory;
    EXPECT_TRUE(std::dynamic_pointer_cast<StepRoot>(
            factory.CreateStep(TypeOfStep::ROOT)));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepQuit>(
            factory.CreateStep(TypeOfStep::QUIT)));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepHelp>(
            factory.CreateStep(TypeOfStep::HELP)));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepAdd>(
            factory.CreateStep(TypeOfStep::ADD)));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepEdit>(
            factory.CreateStep(TypeOfStep::EDIT)));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepComplete>(
            factory.CreateStep(TypeOfStep::COMPLETE)));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepDelete>(
            factory.CreateStep(TypeOfStep::DELETE)));
    EXPECT_TRUE(std::dynamic_pointer_cast<StepShow>(
            factory.CreateStep(TypeOfStep::SHOW)));
}

TEST_F(FactoryTest, shouldReturnRootStep) {
    Factory factory;
    EXPECT_TRUE(std::dynamic_pointer_cast<StepRoot>(
            factory.GetRootStep()));
}
