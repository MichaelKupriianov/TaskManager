#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ui/step/SubSteps.h"
#include "ui/Factory.h"
#include "ui/view/ViewMock.h"
#include "ui/ContextMock.h"

using ::testing::Return;

using namespace ui;
using namespace ui::step;

class SubStepTest : public ::testing::Test {
public:
    void SetUp() override {
        task_ = std::make_shared<Task>();
        view_ = std::make_shared<ViewMock>(std::make_shared<Reader>(), std::make_shared<Printer>());
        factory_ = std::make_shared<Factory>(view_);
        context_ = std::make_shared<ContextMock>("");
    }

protected:
    std::shared_ptr<Task> task_;
    std::shared_ptr<ViewMock> view_;
    std::shared_ptr<Factory> factory_;
    std::shared_ptr<ContextMock> context_;
};

TEST_F(SubStepTest, shouldReadTitle) {
    auto step = SubStepTitle(factory_, view_);

    EXPECT_CALL(*context_, wizard_string()).WillOnce(Return("Add"));
    EXPECT_CALL(*view_, ReadTitle("Add")).WillOnce(Return("title"));
    EXPECT_CALL(*context_, task()).WillOnce(Return(task_));

    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepPriority>(step.execute(*context_)));
    EXPECT_EQ(task_->title(), "title");
}

TEST_F(SubStepTest, shouldReadPriority) {
    auto step = SubStepPriority(factory_, view_);

    EXPECT_CALL(*context_, wizard_string()).WillOnce(Return("Add"));
    EXPECT_CALL(*view_, ReadPriority("Add")).WillOnce(Return(Task_Priority_LOW));
    EXPECT_CALL(*context_, task()).WillOnce(Return(task_));

    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepDate>(step.execute(*context_)));
    EXPECT_EQ(task_->priority(), Task_Priority_LOW);
}

TEST_F(SubStepTest, shouldReadDate) {
    auto step = SubStepDate(factory_, view_);

    EXPECT_CALL(*context_, wizard_string()).WillOnce(Return("Edit"));

    google::protobuf::Timestamp date;
    date.set_seconds(100);
    EXPECT_CALL(*view_, ReadDate("Edit")).WillOnce(Return(date));

    EXPECT_CALL(*context_, task()).WillOnce(Return(task_));

    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepLabel>(step.execute(*context_)));
    ASSERT_TRUE(task_->has_date());
    EXPECT_EQ(task_->date().seconds(), 100);
}

TEST_F(SubStepTest, shouldReadLabels) {
    auto step = SubStepLabel(factory_, view_);

    EXPECT_CALL(*context_, wizard_string()).WillOnce(Return("Add"));
    EXPECT_CALL(*view_, ReadLabels("Add")).WillOnce(Return(std::vector<std::string>{"label_1", "label_2"}));

    EXPECT_CALL(*context_, task())
            .Times(2)
            .WillRepeatedly(Return(task_));
    EXPECT_CALL(*context_, finished()).Times(1);

    EXPECT_TRUE(std::dynamic_pointer_cast<SubStepLabel>(step.execute(*context_)));
    ASSERT_EQ(task_->labels().size(), 2);
    EXPECT_EQ(task_->labels()[0], "label_1");
    EXPECT_EQ(task_->labels()[1], "label_2");
}