#include"gtest/gtest.h"
#include"SubDependency.h"

class SubDependencyTest : public ::testing::Test {
};

TEST_F(SubDependencyTest, shouldWorkWithFactoryAndView) {
    auto reader = std::make_shared<Reader>();
    auto printer = std::make_shared<Printer>();
    auto view = std::make_shared<View>(reader, printer);
    auto factory = std::make_shared<SubFactory>();
    TypeOfCommand command{TypeOfCommand::ADD};
    SubDependency dependency(factory, view, command);
    EXPECT_EQ(dependency.view(), view);
    EXPECT_EQ(dependency.factory(), factory);
    EXPECT_EQ(dependency.command(), command);
}