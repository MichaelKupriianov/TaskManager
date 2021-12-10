#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include<memory>
#include"Reader.h"
#include"Printer.h"
#include"View.h"
#include"Factory.h"
#include"Dependency.h"
#include"StepMachine.h"
#include"TaskManager.h"
#include"Controller.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::_;

class MockReader : public Reader {
public:
    MOCK_METHOD(std::string, ReadString, (), (override));
};

class MockPrinter : public Printer {
public:
    MOCK_METHOD(void, PrintString, (const std::string &), (override));
};

class MainTest : public ::testing::Test {
public:
    void SetUp() override {
        reader_ = std::make_shared<MockReader>();
        printer_ = std::make_shared<MockPrinter>();
        auto view = std::make_shared<View>(reader_, printer_);
        auto factory = std::make_shared<Factory>();
        auto dependency = std::make_shared<Dependency>(factory, view);
        auto step_machine = std::make_shared<StepMachine>(dependency);
        auto task_manager = std::make_shared<TaskManager>();
        controller_ = std::make_shared<Controller>(step_machine, task_manager);
    }
protected:
    std::shared_ptr<MockReader> reader_;
    std::shared_ptr<MockPrinter> printer_;
    std::shared_ptr<Controller> controller_;
};

TEST_F(MainTest, Scenario_1) {
    EXPECT_CALL(*reader_, ReadString())
            .WillOnce(Return("aaa"))
            .WillOnce(Return("help"))

            .WillOnce(Return("add"))
            .WillOnce(Return("first"))
            .WillOnce(Return(""))
            .WillOnce(Return("12/12"))
            .WillOnce(Return("y"))

            .WillOnce(Return("add subtask"))
            .WillOnce(Return("0"))
            .WillOnce(Return("second"))
            .WillOnce(Return("medium"))
            .WillOnce(Return(""))
            .WillOnce(Return("y"))

            .WillOnce(Return("show"))
            .WillOnce(Return("quit"));
    InSequence s;
    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString("There is no such command\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(9);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(4);
    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(5);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString("id: 0, title: first, priority: none, date: Dec 12 00:00")).Times(1);
    EXPECT_CALL(*printer_, PrintString("  :\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString("   id: 1, title: second, priority: medium, date: none\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString("Good luck!\n")).Times(1);
    controller_->Run();
}