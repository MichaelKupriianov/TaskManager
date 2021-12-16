#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"StepMachine.h"
#include"ViewMock.h"
#include"FactoryMock.h"
#include"StepMock.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::_;

class StepMachineTest : public ::testing::Test {
public:
    void SetUp() override {
        auto reader = std::make_shared<Reader>();
        auto printer = std::make_shared<Printer>();
        view_ = std::make_shared<ViewMock>(reader, printer);
        factory_ = std::make_shared<FactoryMock>();
        dependency_ = std::make_shared<Dependency>(factory_, view_);
        machine_ = std::make_shared<StepMachine>(dependency_);
    }

protected:
    std::shared_ptr<ViewMock> view_;
    std::shared_ptr<FactoryMock> factory_;
    std::shared_ptr<Dependency> dependency_;
    std::shared_ptr<StepMachine> machine_;
};

TEST_F(StepMachineTest, shouldWork) {
    std::shared_ptr<StepRootMock> step_root(new StepRootMock);
    std::shared_ptr<StepHelpMock> step_help(new StepHelpMock);
    std::shared_ptr<StepQuit> step_quit(new StepQuit);

    InSequence s;
    EXPECT_CALL(*factory_, GetRootStep())
            .WillOnce(Return(step_root));
    EXPECT_CALL(*step_root, execute(_, dependency_))
            .WillOnce(Return(step_help));
    EXPECT_CALL(*step_help, execute(_, dependency_))
            .WillOnce(Return(step_quit));
    EXPECT_CALL(*view_, Quit())
            .Times(1);
    EXPECT_CALL(*factory_, GetRootStep())
            .WillOnce(Return(step_root));
    EXPECT_TRUE(std::dynamic_pointer_cast<CommandQuit>(std::shared_ptr(
            machine_->GetCommand())));
}