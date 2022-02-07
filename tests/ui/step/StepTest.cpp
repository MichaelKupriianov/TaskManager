#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ui/step/Step.h"
#include "ui/view/ViewMock.h"
#include "ui/FactoryMock.h"
#include "logging/Initialisation.h"

using ::testing::Return;
using ::testing::_;

using namespace ui;
using namespace ui::step;

class StepTest : public ::testing::Test {
public:
    void SetUp() override {
        ConsoleLogging{boost::log::trivial::fatal};

        view_ = std::make_shared<ViewMock>(std::make_shared<Reader>(), std::make_shared<Printer>());
        factory_ = std::make_shared<FactoryMock>(view_);
    }

protected:
    std::shared_ptr<ViewMock> view_;
    std::shared_ptr<FactoryMock> factory_;
};

TEST_F(StepTest, shouldReadNextStep) {
    auto step = Root(factory_, view_);
    auto context = Context(std::make_shared<command::Result>(false));

    EXPECT_CALL(*view_, ReadCommand()).WillOnce(Return(Type::QUIT));
    EXPECT_CALL(*factory_, CreateStep(Type::QUIT)).Times(1);

    step.execute(context);
}

TEST_F(StepTest, shouldPrintResultIfNessesary) {
    auto step = Root(factory_, view_);
    auto context = Context(std::make_shared<command::Result>(command::Error::CANNOT_LOAD_FROM_FILE));

    EXPECT_CALL(*factory_, CreateStep(Type::PRINT)).Times(1);

    step.execute(context);
}

TEST_F(StepTest, shouldQuit) {
    auto step = Quit(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, PrintQuit()).Times(1);
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_TRUE(std::dynamic_pointer_cast<command::Quit>(context.command()));
}

TEST_F(StepTest, shouldHelp) {
    auto step = Help(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, PrintHelp()).Times(1);
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
}

TEST_F(StepTest, shouldPrintError) {
    auto step = Print(factory_, view_);
    auto context = Context(std::make_shared<command::Result>(command::Error::INCORRECT_PARENT_ID));

    EXPECT_CALL(*view_, PrintError(command::Error::INCORRECT_PARENT_ID)).Times(1);
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_FALSE(context.result()->has_value());
}

TEST_F(StepTest, shouldPrintCompositeTask) {
    auto step = Print(factory_, view_);
    auto context = Context(std::make_shared<command::Result>(CompositeTask()));

    EXPECT_CALL(*view_, PrintCompositeTask(_)).Times(1);
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_FALSE(context.result()->has_value());
}

TEST_F(StepTest, shouldPrintManyTasks) {
    auto step = Print(factory_, view_);
    auto context = Context(std::make_shared<command::Result>(ManyTasksWithId()));

    EXPECT_CALL(*view_, PrintManyTasksWithId(_)).Times(1);
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_FALSE(context.result()->has_value());
}

TEST_F(StepTest, shouldPrintManyCompositeTasks) {
    auto step = Print(factory_, view_);
    auto context = Context(std::make_shared<command::Result>(ManyCompositeTasks()));

    EXPECT_CALL(*view_, PrintManyCompositeTasks(_)).Times(1);
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_FALSE(context.result()->has_value());
}

TEST_F(StepTest, shouldCreateCommandComplete) {
    auto step = Complete(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, ReadId("[Complete Task]")).WillOnce(Return(TaskId()));
    EXPECT_CALL(*view_, Confirm()).WillOnce(Return(true));
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_TRUE(std::dynamic_pointer_cast<command::Complete>(context.command()));
}

TEST_F(StepTest, shouldWorkIfNotConfirmComplete) {
    auto step = Complete(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, ReadId("[Complete Task]")).WillOnce(Return(TaskId()));
    EXPECT_CALL(*view_, Confirm()).WillOnce(Return(false));
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_EQ(context.command(), nullptr);
}

TEST_F(StepTest, shouldCreateCommandDelete) {
    auto step = Delete(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, ReadId("[Delete Task]")).WillOnce(Return(TaskId()));
    EXPECT_CALL(*view_, Confirm()).WillOnce(Return(true));
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_TRUE(std::dynamic_pointer_cast<command::Delete>(context.command()));
}

TEST_F(StepTest, shouldWorkIfNotConfirmDelete) {
    auto step = Delete(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, ReadId("[Delete Task]")).WillOnce(Return(TaskId()));
    EXPECT_CALL(*view_, Confirm()).WillOnce(Return(false));
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_EQ(context.command(), nullptr);
}

TEST_F(StepTest, shouldCreateCommandSave) {
    auto step = Save(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, ReadFilename("[Save to file]")).WillOnce(Return(""));
    EXPECT_CALL(*view_, Confirm()).WillOnce(Return(true));
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_TRUE(std::dynamic_pointer_cast<command::Save>(context.command()));
}

TEST_F(StepTest, shouldWorkIfNotConfirmSave) {
    auto step = Save(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, ReadFilename("[Save to file]")).WillOnce(Return(""));
    EXPECT_CALL(*view_, Confirm()).WillOnce(Return(false));
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_EQ(context.command(), nullptr);
}

TEST_F(StepTest, shouldCreateCommandLoad) {
    auto step = Load(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, ReadFilename("[Load from file]")).WillOnce(Return(""));
    EXPECT_CALL(*view_, Confirm()).WillOnce(Return(true));
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_TRUE(std::dynamic_pointer_cast<command::Load>(context.command()));
}

TEST_F(StepTest, shouldWorkIfNotConfirmLoad) {
    auto step = Load(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, ReadFilename("[Load from file]")).WillOnce(Return(""));
    EXPECT_CALL(*view_, Confirm()).WillOnce(Return(false));
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_EQ(context.command(), nullptr);
}

TEST_F(StepTest, shouldCreateCommandShow) {
    auto step = Show(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, ReadIfPrintSubtasks("[Show]")).Times(1);
    EXPECT_CALL(*view_, ReadSortBy("[Show]")).Times(1);
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_TRUE(std::dynamic_pointer_cast<command::Show>(context.command()));
}

TEST_F(StepTest, shouldCreateCommandShowTask) {
    auto step = ShowTask(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, ReadId("[Show Task]")).Times(1);
    EXPECT_CALL(*view_, ReadSortBy("[Show Task]")).Times(1);
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_TRUE(std::dynamic_pointer_cast<command::ShowTask>(context.command()));
}

TEST_F(StepTest, shouldCreateCommandShowLabel) {
    auto step = ShowByLabel(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, ReadLabel("[Show by label]")).Times(1);
    EXPECT_CALL(*view_, ReadSortBy("[Show by label]")).Times(1);
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_TRUE(std::dynamic_pointer_cast<command::ShowByLabel>(context.command()));
}

TEST_F(StepTest, shouldAddTask) {
    auto step = Add(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*factory_, GetInitialSubStep())
            .WillOnce(Return(std::make_shared<SubStepLabel>(std::make_shared<Factory>(view_), view_)));

    EXPECT_CALL(*view_, ReadLabels("[Add Task]")).WillOnce(Return(std::vector<std::string>{"label"}));
    EXPECT_CALL(*view_, Confirm()).WillOnce(Return(true));
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_TRUE(std::dynamic_pointer_cast<command::Add>(context.command()));
}

TEST_F(StepTest, shouldAddSubTask) {
    auto step = AddSub(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, ReadParentId("[Add SubTask]")).WillOnce(Return(TaskId()));
    EXPECT_CALL(*factory_, GetInitialSubStep())
            .WillOnce(Return(std::make_shared<SubStepLabel>(std::make_shared<Factory>(view_), view_)));

    EXPECT_CALL(*view_, ReadLabels("[Add SubTask]")).WillOnce(Return(std::vector<std::string>{"label"}));
    EXPECT_CALL(*view_, Confirm()).WillOnce(Return(true));
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_TRUE(std::dynamic_pointer_cast<command::AddSub>(context.command()));
}

TEST_F(StepTest, shouldEditTask) {
    auto step = Edit(factory_, view_);
    auto context = Context("");

    EXPECT_CALL(*view_, ReadId("[Edit Task]")).WillOnce(Return(TaskId()));
    EXPECT_CALL(*factory_, GetInitialSubStep())
            .WillOnce(Return(std::make_shared<SubStepLabel>(std::make_shared<Factory>(view_), view_)));

    EXPECT_CALL(*view_, ReadLabels("[Edit Task]")).WillOnce(Return(std::vector<std::string>{"label"}));
    EXPECT_CALL(*view_, Confirm()).WillOnce(Return(true));
    EXPECT_CALL(*factory_, GetInitialStep()).Times(1);

    step.execute(context);
    EXPECT_TRUE(std::dynamic_pointer_cast<command::Edit>(context.command()));
}