#include"gtest/gtest.h"
#include"Dependency.h"

class DependencyTest : public ::testing::Test {
};

TEST_F(DependencyTest, shouldWorkWithFactoryAndView) {
    auto reader = std::make_shared<Reader>();
    auto printer = std::make_shared<Printer>();
    auto view = std::make_shared<View>(reader, printer);
    auto factory = std::make_shared<Factory>();
    Dependency dependency(factory, view);
    EXPECT_EQ(dependency.view(), view);
    EXPECT_EQ(dependency.factory(), factory);
}