#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"Controller.h"
#include"StepMachineMock.h"
#include"CommandMock.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::_;

class ControllerTest : public ::testing::Test {
public:
    void SetUp() override {
        task_ = std::make_shared<Task>();
        id_ = std::make_shared<TaskId>();

        auto generator = std::make_shared<IdGenerator>();
        auto persister = std::make_shared<Persister>();
        manager_ = std::make_shared<TaskManager>(generator, persister);

        auto reader = std::make_shared<Reader>();
        auto printer = std::make_shared<Printer>();
        view_ = std::make_shared<View>(reader, printer);
        auto factory = std::make_shared<Factory>();
        auto dependency = std::make_shared<Dependency>(factory, view_);
        machine_ = std::make_shared<StepMachineMock>(dependency);

        controller_ = std::make_shared<Controller>(machine_, manager_);
    }

protected:
    std::shared_ptr<Task> task_;
    std::shared_ptr<TaskId> id_;
    std::shared_ptr<TaskManager> manager_;
    std::shared_ptr<View> view_;
    std::shared_ptr<StepMachineMock> machine_;
    std::shared_ptr<Controller> controller_;
};

TEST_F(ControllerTest, shouldWork) {
    auto command_add = std::make_shared<CommandAddMock>(*task_, view_);
    auto command_edit = std::make_shared<CommandEditMock>(*id_, *task_, view_);
    auto command_quit = std::make_shared<CommandQuitMock>();
    EXPECT_CALL(*machine_, GetCommand())
            .Times(3)
            .WillOnce(Return(command_add))
            .WillOnce(Return(command_edit))
            .WillOnce(Return(command_quit));

    EXPECT_CALL(*command_add, execute(manager_))
          .Times(1)
          .WillOnce(Return(true));
    EXPECT_CALL(*command_edit, execute(manager_))
            .Times(1)
            .WillOnce(Return(true));
    EXPECT_CALL(*command_quit, execute(manager_))
            .Times(1)
            .WillOnce(Return(false));
    controller_->Run();
}