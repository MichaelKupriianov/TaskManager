#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"StepMachine.h"
#include"ViewMock.h"

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
        auto factory = std::make_shared<Factory>();
        auto dependency = std::make_shared<Dependency>(factory, view_);
        machine_ = std::make_shared<StepMachine>(dependency);
    }

protected:
    std::shared_ptr<ViewMock> view_;
    std::shared_ptr<StepMachine> machine_;
};

TEST_F(StepMachineTest, shouldReturnCommandQuit) {
    InSequence s;
    EXPECT_CALL(*view_, ReadCommand())
            .WillOnce(Return(TypeOfStep::QUIT));
    EXPECT_CALL(*view_, Quit())
            .Times(1);
    EXPECT_TRUE(std::dynamic_pointer_cast<CommandQuit>(std::shared_ptr(
            machine_->GetCommand())));
}

TEST_F(StepMachineTest, shouldReturnCommandAdd) {
    InSequence s;
    EXPECT_CALL(*view_, ReadCommand())
            .WillOnce(Return(TypeOfStep::HELP));
    EXPECT_CALL(*view_, Help())
            .Times(1);

    EXPECT_CALL(*view_, ReadCommand())
            .WillOnce(Return(TypeOfStep::ADD));
    EXPECT_CALL(*view_, ReadTitle(TypeOfCommand::ADD))
            .WillOnce(Return("first"));
    EXPECT_CALL(*view_, ReadPriority(TypeOfCommand::ADD))
            .WillOnce(Return(Task::Priority::NONE));
    EXPECT_CALL(*view_, ReadDate(TypeOfCommand::ADD))
            .WillOnce(Return(1));
    EXPECT_CALL(*view_, Confirm())
            .WillOnce(Return(true));

    EXPECT_TRUE(std::dynamic_pointer_cast<CommandAdd>(std::shared_ptr(
            machine_->GetCommand())));
}
