//#include "gtest/gtest.h"
//#include "gmock/gmock.h"
//#include "ui/controller/Controller.h"
//#include "ui/command/CommandMock.h"
//
//using ::testing::Return;
//using ::testing::AtLeast;
//using ::testing::InSequence;
//using ::testing::_;
//
//using namespace ui;
//
//class ControllerTest : public ::testing::Test {
//public:
//    void SetUp() override {
//        auto generator = std::make_shared<model::IdGenerator>();
//        auto manager = std::make_shared<model::TaskManager>(generator);
//        auto persister = std::make_shared<TaskPersister>();
//        auto resources_for_controller = std::make_shared<ui::command::Resources>(manager, persister);
//
//        auto reader = std::make_shared<ui::Reader>();
//        auto printer = std::make_shared<ui::Printer>();
//        auto view = std::make_shared<ui::View>(reader, printer);
//        auto factory = std::make_shared<ui::Factory>();
//        auto resources_for_machine = std::make_shared<ui::step::Resources>(factory, view);
//
//        command_ = std::make_shared<CommandQuitMock>();
//        machine_ = std::make_shared<StateMachineMock>(resources_for_machine, command_);
//        controller_ = std::make_shared<ui::Controller>(machine_, resources_for_controller);
//    }
//
//protected:
//    std::shared_ptr<CommandQuitMock> command_;
//    std::shared_ptr<StateMachineMock> machine_;
//    std::shared_ptr<Controller> controller_;
//};
//
//TEST_F(ControllerTest, shouldWork) {
//    EXPECT_CALL(*command_, execute(_))
//          .Times(3)
//          .WillOnce(Return(command::Result(false)))
//          .WillOnce(Return(command::Result(command::Error::CANNOT_LOAD_FROM_FILE)))
//          .WillOnce(Return(command::Result(true)));
//
//    controller_->Run();
//}

//TEST_F(CommandTest, shouldSaveToFile) {
//auto command = std::make_shared<Save>("filename");
//
//EXPECT_CALL(*manager_, GetAllTasks())
//.Times(1)
//.WillOnce(Return(*array_hierarchical_tasks_));
//EXPECT_CALL(*persister_, Save(*array_hierarchical_tasks_, "filename"))
//.Times(1)
//.WillOnce(Return(true));
//
//Result result{command->execute(resources_)};
//EXPECT_FALSE(result.finished);
//}
//
//TEST_F(CommandTest, shouldHandleErrorWhenSaveToFile) {
//auto command = std::make_shared<Save>("filename");
//
//EXPECT_CALL(*manager_, GetAllTasks())
//.Times(1)
//.WillOnce(Return(*array_hierarchical_tasks_));
//EXPECT_CALL(*persister_, Save(*array_hierarchical_tasks_, "filename"))
//.Times(1)
//.WillOnce(Return(false));
//
//Result result{command->execute(resources_)};
//EXPECT_TRUE(result.error.has_value());
//}
//
//TEST_F(CommandTest, shouldLoadFromFile) {
//auto command = std::make_shared<Load>("filename");
//
//EXPECT_CALL(*manager_, Rewrite(*array_hierarchical_tasks_))
//.Times(1);
//EXPECT_CALL(*persister_, Load("filename"))
//.Times(1)
//.WillOnce(Return(*array_hierarchical_tasks_));
//
//Result result{command->execute(resources_)};
//EXPECT_FALSE(result.finished);
//}
//
//TEST_F(CommandTest, shouldHandleErrorWhenLoadFromFile) {
//auto command = std::make_shared<Load>("filename");
//
//EXPECT_CALL(*persister_, Load("filename"))
//.Times(1)
//.WillOnce(Return(std::nullopt));
//
//Result result{command->execute(resources_)};
//EXPECT_TRUE(result.error.has_value());
//}