#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ui/StateMachine.h"
#include "FactoryMock.h"
#include "ContextMock.h"
#include "step/StepMock.h"
#include "view/ViewMock.h"
#include "controller/ControllerMock.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::_;

using namespace ui;

class StepMachineTest : public ::testing::Test {
public:
    void SetUp() override {
        auto reader = std::make_shared<Reader>();
        auto printer = std::make_shared<Printer>();
        view_ = std::make_shared<ViewMock>(reader, printer);
        factory_ = std::make_shared<Factory>(view_);
        auto Result = std::make_shared<command::Result>(false);
        context_ = std::make_shared<ContextMock>(Result);

        auto generator = std::make_shared<model::IdGenerator>();
        auto manager = std::make_shared<model::TaskManager>(generator);
        controller_ = std::make_shared<ControllerMock>(manager);
    }
protected:
    std::shared_ptr<ViewMock> view_;
    std::shared_ptr<Factory> factory_;
    std::shared_ptr<ContextMock> context_;
    std::shared_ptr<ControllerMock> controller_;
};

TEST_F(StepMachineTest, shouldRunWuthContext) {
    auto step_root = std::make_shared<StepRootMock>(factory_, view_);
    auto step_help = std::make_shared<StepHelpMock>(factory_, view_);
    auto step_quit = std::make_shared<StepQuitMock>(factory_, view_);

    StateMachine machine(step_root);

    EXPECT_CALL(*step_root, execute(_))
            .Times(1)
            .WillOnce(Return(step_help));
    EXPECT_CALL(*step_help, execute(_))
            .Times(1)
            .WillOnce(Return(step_quit));
    EXPECT_CALL(*step_quit, execute(_))
            .Times(1)
            .WillOnce(Return(step_root));
    EXPECT_CALL(*context_, if_finished())
            .Times(4)
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillOnce(Return(true));

    machine.Run(*context_);
    EXPECT_TRUE(testing::Mock::VerifyAndClearExpectations(step_root.get()));
}

TEST_F(StepMachineTest, shouldRunWuthController) {
    auto step_root = std::make_shared<StepRootMock>(factory_, view_);
    auto step_help = std::make_shared<StepHelpMock>(factory_, view_);
    auto step_quit = std::make_shared<step::Quit>(factory_, view_);

    StateMachine machine(step_root);

    EXPECT_CALL(*step_root, execute(_))
            .Times(1)
            .WillOnce(Return(step_help));
    EXPECT_CALL(*step_help, execute(_))
            .Times(1)
            .WillOnce(Return(step_quit));
    EXPECT_CALL(*view_, PrintQuit())
            .Times(1);

    machine.Run(controller_);
}