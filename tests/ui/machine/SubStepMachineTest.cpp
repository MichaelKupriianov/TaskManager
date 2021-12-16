#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"SubStepMachine.h"
#include"ViewMock.h"
#include"SubFactoryMock.h"
#include"SubStepMock.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::_;

class SubStepMachineTest : public ::testing::Test {
public:
    void SetUp() override {
        auto reader = std::make_shared<Reader>();
        auto printer = std::make_shared<Printer>();
        view_ = std::make_shared<ViewMock>(reader, printer);
        factory_ = std::make_shared<SubFactoryMock>();
        dependency_ = std::make_shared<SubDependency>(factory_, view_, TypeOfCommand::ADD);
        machine_ = std::make_shared<SubStepMachine>(dependency_);
    }
protected:
    std::shared_ptr<ViewMock> view_;
    std::shared_ptr<SubFactoryMock> factory_;
    std::shared_ptr<SubDependency> dependency_;
    std::shared_ptr<SubStepMachine> machine_;
};

TEST_F(SubStepMachineTest, shouldWork) {
    std::shared_ptr<SubStepTitleMock> step_title(new SubStepTitleMock);
    std::shared_ptr<SubStepPriorityMock> step_priority(new SubStepPriorityMock);
    std::shared_ptr<SubStepLabel> step_label(new SubStepLabel);

    InSequence s;
    EXPECT_CALL(*factory_, GetRootSubStep())
            .WillOnce(Return(step_title));
    EXPECT_CALL(*step_title, execute(_, dependency_))
            .WillOnce(Return(step_priority));
    EXPECT_CALL(*step_priority, execute(_, dependency_))
            .WillOnce(Return(step_label));
    EXPECT_CALL(*view_, ReadLabel(TypeOfCommand::ADD))
            .Times(1);
    machine_->GetTask();
}