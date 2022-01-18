#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ui/step/SubSteps.h"
#include "ui/view/ViewMock.h"
#include "ui/FactoryMock.h"
#include "ui/ContextMock.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::_;

using namespace ui;
using namespace ui::step;

class SubStepTest : public ::testing::Test {
public:
    void SetUp() override {
        task_ = std::make_shared<model::Task>();
        auto reader = std::make_shared<Reader>();
        auto printer = std::make_shared<Printer>();
        view_ = std::make_shared<ViewMock>(reader, printer);
        factory_ = std::make_shared<Factory>(view_);
        auto Result = std::make_shared<command::Result>(false);
        context_ = std::make_shared<ContextMock>(Result);
    }

protected:
    std::shared_ptr<model::Task> task_;
    std::shared_ptr<ViewMock> view_;
    std::shared_ptr<Factory> factory_;
    std::shared_ptr<ContextMock> context_;
};

TEST_F(SubStepTest, shouldReadTitle) {
    auto step = SubStepTitle(factory_, view_);

    EXPECT_CALL(*view_, ReadTitle(_))
            .Times(1)
            .WillOnce(Return("title"));
    EXPECT_CALL(*context_, command_name())
            .Times(1);
    EXPECT_CALL(*context_, task())
            .Times(1)
            .WillOnce(Return(task_));
    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepPriority>(
            step.execute(*context_)));
}

TEST_F(SubStepTest, shouldReadPriority) {
    auto step = SubStepPriority(factory_, view_);

    EXPECT_CALL(*view_, ReadPriority(_))
            .Times(1)
            .WillOnce(Return(model::Task_Priority_LOW));
    EXPECT_CALL(*context_, command_name())
            .Times(1);
    EXPECT_CALL(*context_, task())
            .Times(1)
            .WillOnce(Return(task_));
    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepDate>(
            step.execute(*context_)));
}

TEST_F(SubStepTest, shouldReadDate) {
    auto step = SubStepDate(factory_, view_);

    EXPECT_CALL(*view_, ReadDate(_))
            .Times(1)
            .WillOnce(Return(google::protobuf::Timestamp()));
    EXPECT_CALL(*context_, command_name())
            .Times(1);
    EXPECT_CALL(*context_, task())
            .Times(1)
            .WillOnce(Return(task_));
    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepLabel>(
            step.execute(*context_)));
}

TEST_F(SubStepTest, shouldReadLabels) {
    auto step = SubStepLabel(factory_, view_);

    EXPECT_CALL(*view_, ReadLabels(_))
            .Times(1)
            .WillOnce(Return(std::vector<std::string>{"label_1", "label_2"}));
    EXPECT_CALL(*context_, command_name())
            .Times(1);
    EXPECT_CALL(*context_, task())
            .Times(2)
            .WillRepeatedly(Return(task_));
    EXPECT_CALL(*context_,finished())
            .Times(1);

    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepLabel>(
            step.execute(*context_)));
}