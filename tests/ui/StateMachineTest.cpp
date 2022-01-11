#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ui/StateMachine.h"
#include "view/ViewMock.h"
#include "FactoryMock.h"
#include "step/StepMock.h"
#include "step/SubStepMock.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::_;

using namespace ui;

class StepMachineTest : public ::testing::Test {
public:
    void SetUp() override {
        auto reader = std::make_shared<ui::Reader>();
        auto printer = std::make_shared<ui::Printer>();
        view_ = std::make_shared<ViewMock>(reader, printer);
        factory_ = std::make_shared<FactoryMock>();
        resources_ = std::make_shared<ui::step::Resources>(factory_, view_, step::Type::ADD);
        machine_ = std::make_shared<StateMachine>(resources_);
    }

protected:
    std::shared_ptr<ViewMock> view_;
    std::shared_ptr<FactoryMock> factory_;
    std::shared_ptr<step::Resources> resources_;
    std::shared_ptr<StateMachine> machine_;
};

TEST_F(StepMachineTest, shouldWorkWithContext) {
    std::shared_ptr<StepRootMock> step_root(new StepRootMock);
    std::shared_ptr<StepHelpMock> step_help(new StepHelpMock);
    std::shared_ptr<step::Quit> step_quit(new step::Quit);
    Context context;

    EXPECT_CALL(*factory_, GetInitialStep())
            .Times(2)
            .WillRepeatedly(Return(step_root));
    EXPECT_CALL(*step_root, execute(_, resources_))
            .WillOnce(Return(step_help));
    EXPECT_CALL(*step_help, execute(_, resources_))
            .WillOnce(Return(step_quit));
    EXPECT_CALL(*view_, PrintQuit())
            .Times(1);

    machine_->Run(context);
    EXPECT_TRUE(testing::Mock::VerifyAndClearExpectations(factory_.get()));
}

TEST_F(StepMachineTest, shouldWorkWithSubContext) {
    std::shared_ptr<SubStepTitleMock> step_title(new SubStepTitleMock);
    std::shared_ptr<SubStepPriorityMock> step_priority(new SubStepPriorityMock);
    std::shared_ptr<step::SubStepLabel> step_label(new step::SubStepLabel);
    SubContext context;

    EXPECT_CALL(*factory_, GetInitialSubStep())
            .WillOnce(Return(step_title));
    EXPECT_CALL(*step_title, execute(_, resources_))
            .WillOnce(Return(step_priority));
    EXPECT_CALL(*step_priority, execute(_, resources_))
            .WillOnce(Return(step_label));
    EXPECT_CALL(*view_, ReadLabel(step::Type::ADD))
            .Times(1);

    machine_->Run(context);
    EXPECT_TRUE(testing::Mock::VerifyAndClearExpectations(factory_.get()));
}