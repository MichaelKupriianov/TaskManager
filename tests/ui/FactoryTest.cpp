#include "gtest/gtest.h"
#include "ui/Factory.h"

using namespace ui;

class FactoryTest : public ::testing::Test {
};

TEST_F(FactoryTest, shouldCreateStep) {
    Factory factory;
    EXPECT_TRUE(std::dynamic_pointer_cast<step::Quit>(
            factory.CreateStep(step::Type::QUIT)));
    EXPECT_TRUE(std::dynamic_pointer_cast<step::Help>(
            factory.CreateStep(step::Type::HELP)));
    EXPECT_TRUE(std::dynamic_pointer_cast<step::Print>(
            factory.CreateStep(step::Type::PRINT)));
    EXPECT_TRUE(std::dynamic_pointer_cast<step::Add>(
            factory.CreateStep(step::Type::ADD)));
    EXPECT_TRUE(std::dynamic_pointer_cast<step::AddSub>(
            factory.CreateStep(step::Type::ADD_SUB)));
    EXPECT_TRUE(std::dynamic_pointer_cast<step::Edit>(
            factory.CreateStep(step::Type::EDIT)));
    EXPECT_TRUE(std::dynamic_pointer_cast<step::Complete>(
            factory.CreateStep(step::Type::COMPLETE)));
    EXPECT_TRUE(std::dynamic_pointer_cast<step::Delete>(
            factory.CreateStep(step::Type::DELETE)));
    EXPECT_TRUE(std::dynamic_pointer_cast<step::Show>(
            factory.CreateStep(step::Type::SHOW)));
    EXPECT_TRUE(std::dynamic_pointer_cast<step::ShowTask>(
            factory.CreateStep(step::Type::SHOW_TASK)));
    EXPECT_TRUE(std::dynamic_pointer_cast<step::ShowLabel>(
            factory.CreateStep(step::Type::SHOW_LABEL)));
    EXPECT_TRUE(std::dynamic_pointer_cast<step::Save>(
            factory.CreateStep(step::Type::SAVE)));
    EXPECT_TRUE(std::dynamic_pointer_cast<step::Load>(
            factory.CreateStep(step::Type::LOAD)));
}

TEST_F(FactoryTest, shouldReturnInitialStep) {
    Factory factory;
    EXPECT_TRUE(std::dynamic_pointer_cast<step::Root>(
            factory.GetInitialStep()));
}

TEST_F(FactoryTest, shouldReturnInitialSubStep) {
    Factory factory;
    EXPECT_TRUE(std::dynamic_pointer_cast<step::SubStepTitle>(std::shared_ptr(
            factory.GetInitialSubStep())));
}

TEST_F(FactoryTest, shouldReturnNextSubStepAfterTitle) {
    Factory factory;
    step::SubStepTitle step;
    EXPECT_TRUE(std::dynamic_pointer_cast<step::SubStepPriority>(std::shared_ptr(
            factory.GetNextSubStepFrom(step))));
}

TEST_F(FactoryTest, shouldReturnNextSubStepAfterPriprity) {
    Factory factory;
    step::SubStepPriority step;
    EXPECT_TRUE(std::dynamic_pointer_cast<step::SubStepDate>(std::shared_ptr(
            factory.GetNextSubStepFrom(step))));
}

TEST_F(FactoryTest, shouldReturnNextSubStepAfterDate) {
    Factory factory;
    step::SubStepDate step;
    EXPECT_TRUE(std::dynamic_pointer_cast<step::SubStepLabel>(std::shared_ptr(
            factory.GetNextSubStepFrom(step))));
}

TEST_F(FactoryTest, shouldReturnNextSubStepAfterLabel) {
    Factory factory;
    step::SubStepLabel step;
    EXPECT_TRUE(std::dynamic_pointer_cast<step::SubStepLabel>(std::shared_ptr(
            factory.GetNextSubStepFrom(step))));
}