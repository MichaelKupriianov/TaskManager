#include"gtest/gtest.h"
#include"Context.h"

class ContextTest : public ::testing::Test {
};

TEST_F(ContextTest, shouldWorkWithCommand) {
    Context context;
    EXPECT_EQ(context.command(), nullptr);
    auto command = std::make_shared<CommandQuit>();
    context.set_command(command);
    EXPECT_TRUE(std::dynamic_pointer_cast<CommandQuit>(std::shared_ptr(
            context.command())));
}
