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
        task_ = std::make_shared<model::Task>();
        id_ = std::make_shared<model::TaskId>();
        task_with_id_ = std::make_shared<model::TaskWithId>(*id_, *task_);
        many_simple_tasks_ = std::make_shared<model::ManyTasksWithId>();
        composite_task_ = std::make_shared<model::CompositeTask>(*task_with_id_, *many_simple_tasks_);
        many_composite_tasks_=std::make_shared<model::ManyCompositeTasks>();

        auto reader = std::make_shared<Reader>();
        auto printer = std::make_shared<Printer>();
        view_ = std::make_shared<ViewMock>(reader, printer);
        factory_ = std::make_shared<Factory>(view_);
        auto Result = std::make_shared<command::Result>(false);
        context_ = std::make_shared<ContextMock>(Result);
    }

protected:
    std::shared_ptr<model::Task> task_;
    std::shared_ptr<model::TaskId> id_;
    std::shared_ptr<model::TaskWithId> task_with_id_;
    std::shared_ptr<model::ManyTasksWithId> many_simple_tasks_;
    std::shared_ptr<model::CompositeTask> composite_task_;
    std::shared_ptr<model::ManyCompositeTasks> many_composite_tasks_;

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

TEST_F(StepTest, shouldPrintError) {
    auto step = Print(factory_, view_);
    EXPECT_CALL(*context_, result())
            .Times(5)
            .WillRepeatedly(Return(std::make_shared<command::Result>(command::Error::INCORRECT_PARENT_ID)));
    EXPECT_CALL(*view_, PrintError(_))
            .Times(1);
    EXPECT_CALL(*context_, set_result())
            .Times(1);
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldPrintCompositeTask) {
    auto step = Print(factory_, view_);

    EXPECT_CALL(*context_, result())
            .Times(5)
            .WillRepeatedly(Return(std::make_shared<command::Result>(*composite_task_)));
    EXPECT_CALL(*view_, PrintCompositeTask(_))
            .Times(1);
    EXPECT_CALL(*context_, set_result())
            .Times(1);
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldPrintManyTasks) {
    auto step = Print(factory_, view_);

    EXPECT_CALL(*context_, result())
            .Times(5)
            .WillRepeatedly(Return(std::make_shared<command::Result>(*many_simple_tasks_)));
    EXPECT_CALL(*view_, PrintManyTasksWithId(_))
            .Times(1);
    EXPECT_CALL(*context_, set_result())
            .Times(1);
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldPrintManyCompositeTasks) {
    auto step = Print(factory_, view_);

    EXPECT_CALL(*context_, result())
            .Times(5)
            .WillRepeatedly(Return(std::make_shared<command::Result>(*many_composite_tasks_)));
    EXPECT_CALL(*view_, PrintManyCompositeTasks(_))
            .Times(1);
    EXPECT_CALL(*context_, set_result())
            .Times(1);
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldCreateCommandComplete) {
    auto step = Complete(factory_, view_);

    EXPECT_CALL(*view_, ReadId(_))
            .Times(1)
            .WillOnce(Return(model::CreateTaskId(0)));
    EXPECT_CALL(*view_, Confirm())
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*context_, set_command(_))
            .Times(1);
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldWorkIfNotConfirmComplete) {
    auto step = Complete(factory_, view_);

    EXPECT_CALL(*view_, ReadId(_))
            .Times(1)
            .WillOnce(Return(model::CreateTaskId(0)));
    EXPECT_CALL(*view_, Confirm())
            .Times(1)
            .WillOnce(Return(false));
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldCreateCommandDelete) {
    auto step = Delete(factory_, view_);

    EXPECT_CALL(*view_, ReadId(_))
            .Times(1)
            .WillOnce(Return(model::CreateTaskId(0)));
    EXPECT_CALL(*view_, Confirm())
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*context_, set_command(_))
            .Times(1);
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldWorkIfNotConfirmDelete) {
    auto step = Delete(factory_, view_);

    EXPECT_CALL(*view_, ReadId(_))
            .Times(1)
            .WillOnce(Return(model::CreateTaskId(0)));
    EXPECT_CALL(*view_, Confirm())
            .Times(1)
            .WillOnce(Return(false));
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldCreateCommandSave) {
    auto step = Save(factory_, view_);

    EXPECT_CALL(*view_, ReadFilename(_))
            .Times(1)
            .WillOnce(Return(""));
    EXPECT_CALL(*view_, Confirm())
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*context_, set_command(_))
            .Times(1);
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldWorkIfNotConfirmSave) {
    auto step = Save(factory_, view_);

    EXPECT_CALL(*view_, ReadFilename(_))
            .Times(1)
            .WillOnce(Return(""));
    EXPECT_CALL(*view_, Confirm())
            .Times(1)
            .WillOnce(Return(false));
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldCreateCommandLoad) {
    auto step = Load(factory_, view_);

    EXPECT_CALL(*view_, ReadFilename(_))
            .Times(1)
            .WillOnce(Return(""));
    EXPECT_CALL(*view_, Confirm())
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*context_, set_command(_))
            .Times(1);
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldWorkIfNotConfirmLoad) {
    auto step = Load(factory_, view_);

    EXPECT_CALL(*view_, ReadFilename(_))
            .Times(1)
            .WillOnce(Return(""));
    EXPECT_CALL(*view_, Confirm())
            .Times(1)
            .WillOnce(Return(false));
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldCreateCommandShow) {
    auto step = Show(factory_, view_);

    EXPECT_CALL(*view_, ReadIfPrintSubtasks(_))
            .Times(1);
    EXPECT_CALL(*view_, ReadSortBy(_))
            .Times(1);
    EXPECT_CALL(*context_, set_command(_))
            .Times(1);
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldCreateCommandShowTask) {
    auto step = ShowTask(factory_, view_);

    EXPECT_CALL(*view_, ReadId(_))
            .Times(1);
    EXPECT_CALL(*view_, ReadSortBy(_))
            .Times(1);
    EXPECT_CALL(*context_, set_command(_))
            .Times(1);
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldCreateCommandShowLabel) {
    auto step = ShowByLabel(factory_, view_);

    EXPECT_CALL(*view_, ReadLabel(_))
            .Times(1);
    EXPECT_CALL(*view_, ReadSortBy(_))
            .Times(1);
    EXPECT_CALL(*context_, set_command(_))
            .Times(1);
    EXPECT_TRUE(std::dynamic_pointer_cast<Root>(
            step.execute(*context_)));
}

TEST_F(StepTest, shouldAddTask) {
    auto factory = std::make_shared<FactoryMock>(view_);
    auto step = Add(factory, view_);

    EXPECT_CALL(*factory, GetInitialSubStep())
              .Times(1)
              .WillOnce(Return(std::make_shared<SubStepLabel>(factory_, view_)));

    EXPECT_CALL(*view_, ReadLabels(_))
            .Times(1)
            .WillOnce(Return(std::vector<std::string>{"label"}));
    EXPECT_CALL(*view_, Confirm())
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*context_, set_command(_))
            .Times(1);
    EXPECT_CALL(*factory, GetInitialStep())
            .Times(1);

    step.execute(*context_);
}

TEST_F(StepTest, shouldAddSubTask) {
    auto factory = std::make_shared<FactoryMock>(view_);
    auto step = AddSub(factory, view_);

    EXPECT_CALL(*view_, ReadParentId(_))
            .Times(1)
            .WillOnce(Return(model::CreateTaskId(0)));
    EXPECT_CALL(*factory, GetInitialSubStep())
            .Times(1)
            .WillOnce(Return(std::make_shared<SubStepLabel>(factory_, view_)));

    EXPECT_CALL(*view_, ReadLabels(_))
            .Times(1)
            .WillOnce(Return(std::vector<std::string>{"label"}));
    EXPECT_CALL(*view_, Confirm())
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*context_, set_command(_))
            .Times(1);
    EXPECT_CALL(*factory, GetInitialStep())
            .Times(1);

    step.execute(*context_);
}

TEST_F(StepTest, shouldEditTask) {
    auto factory = std::make_shared<FactoryMock>(view_);
    auto step = Edit(factory, view_);

    EXPECT_CALL(*view_, ReadId(_))
            .Times(1)
            .WillOnce(Return(model::CreateTaskId(0)));
    EXPECT_CALL(*factory, GetInitialSubStep())
            .Times(1)
            .WillOnce(Return(std::make_shared<SubStepLabel>(factory_, view_)));

    EXPECT_CALL(*view_, ReadLabels(_))
            .Times(1)
            .WillOnce(Return(std::vector<std::string>{"label"}));
    EXPECT_CALL(*view_, Confirm())
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*context_, set_command(_))
            .Times(1);
    EXPECT_CALL(*factory, GetInitialStep())
            .Times(1);

    step.execute(*context_);
}