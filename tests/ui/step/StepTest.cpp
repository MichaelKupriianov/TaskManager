#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ui/step/Step.h"
#include "ui/view/ViewMock.h"
#include "ui/FactoryMock.h"
#include "ui/ContextMock.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::_;

using namespace ui;
using namespace ui::step;

class StepTest : public ::testing::Test {
public:
    void SetUp() override {
        auto reader = std::make_shared<Reader>();
        auto printer = std::make_shared<Printer>();
        view_ = std::make_shared<ViewMock>(reader, printer);
        factory_ = std::make_shared<Factory>(view_);
        auto Result = std::make_shared<command::Result>(false);
        context_ = std::make_shared<ContextMock>(Result);
    }

protected:
    std::shared_ptr<ViewMock> view_;
    std::shared_ptr<Factory> factory_;
    std::shared_ptr<ContextMock> context_;
};

TEST_F(StepTest, shouldReadNextStep) {
    auto step = Root(factory_, view_);

    EXPECT_CALL(*view_, ReadCommand())
            .Times(1)
            .WillOnce(Return(Type::QUIT));
    EXPECT_CALL(*context_, result())
            .Times(1)
            .WillOnce(Return(std::make_shared<command::Result>(false)));
    EXPECT_TRUE(std::dynamic_pointer_cast<Quit>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldPrintResultIfNessesary) {
    auto step = Root(factory_, view_);

    EXPECT_CALL(*context_, result())
            .Times(1)
            .WillOnce(Return(std::make_shared<command::Result>(command::Error::CANNOT_LOAD_FROM_FILE)));
    EXPECT_TRUE(std::dynamic_pointer_cast<Print>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldQuit) {
    auto step = Quit(factory_, view_);

    EXPECT_CALL(*view_, PrintQuit())
            .Times(1);
    EXPECT_CALL(*context_, set_command(_))
            .Times(1);
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldHelp) {
    auto step = Help(factory_, view_);

    EXPECT_CALL(*view_, PrintHelp())
            .Times(1);
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}