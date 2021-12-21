#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "controller/Controller.h"

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
        auto generator = std::make_shared<IdGenerator>();
        auto persister = std::make_shared<Persister>();
        auto task_manager = std::make_shared<TaskManager>(generator, persister);

        reader_ = std::make_shared<MockReader>();
        printer_ = std::make_shared<MockPrinter>();
        auto view = std::make_shared<View>(reader_, printer_);
        auto factory = std::make_shared<Factory>();
        auto dependency = std::make_shared<DependencyForSteps>(factory, view);
        auto step_machine = std::make_shared<StepMachine>(dependency);

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
            .WillOnce(Return(""))
            .WillOnce(Return("y"))

            .WillOnce(Return("add_subtask"))
            .WillOnce(Return("0"))
            .WillOnce(Return("second"))
            .WillOnce(Return("medium"))
            .WillOnce(Return(""))
            .WillOnce(Return("label"))
            .WillOnce(Return("y"))

            .WillOnce(Return("show"))
            .WillOnce(Return("y"))
            .WillOnce(Return(""))

            .WillOnce(Return("edit"))
            .WillOnce(Return("0"))
            .WillOnce(Return("third"))
            .WillOnce(Return("none"))
            .WillOnce(Return("13:00 11/11"))
            .WillOnce(Return("label"))
            .WillOnce(Return("y"))

            .WillOnce(Return("show_label"))
            .WillOnce(Return("label"))
            .WillOnce(Return(""))

            .WillOnce(Return("quit"));

    InSequence s;

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString("There is no such command\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(12);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(5);
    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(6);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString(
            "id: 0, title: first, priority: none, date: Dec 12 00:00  :\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString(
            "   id: 1, title: second, priority: medium, date: none, label: label\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(6);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString(
            "id: 0, title: third, priority: none, date: Nov 11 13:00, label: label\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString(
            "id: 1, title: second, priority: medium, date: none, label: label\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString("Good luck!\n")).Times(1);

    controller_->Run();
}

TEST_F(MainTest, Scenario_2) {
    EXPECT_CALL(*reader_, ReadString())
            .WillOnce(Return("add"))
            .WillOnce(Return(""))
            .WillOnce(Return("first"))
            .WillOnce(Return("cgf"))
            .WillOnce(Return("medium"))
            .WillOnce(Return("25:25"))
            .WillOnce(Return("12:00 23/12"))
            .WillOnce(Return("label"))
            .WillOnce(Return("yes"))
            .WillOnce(Return("y"))

            .WillOnce(Return("add"))
            .WillOnce(Return("second"))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return("y"))

            .WillOnce(Return("add_subtask"))
            .WillOnce(Return("213jhb"))
            .WillOnce(Return("1"))
            .WillOnce(Return(""))
            .WillOnce(Return("third"))
            .WillOnce(Return("Medium"))
            .WillOnce(Return("medium"))
            .WillOnce(Return("61:12 11/11"))
            .WillOnce(Return("00:00 24/12"))
            .WillOnce(Return("label"))
            .WillOnce(Return("yes"))
            .WillOnce(Return("y"))

            .WillOnce(Return("edit"))
            .WillOnce(Return("fourth"))
            .WillOnce(Return("1"))
            .WillOnce(Return(""))
            .WillOnce(Return("fourth"))
            .WillOnce(Return("abc"))
            .WillOnce(Return(""))
            .WillOnce(Return("11:11 21/21"))
            .WillOnce(Return("06:06 11/1"))
            .WillOnce(Return("label"))
            .WillOnce(Return(""))
            .WillOnce(Return("y"))

            .WillOnce(Return("show"))
            .WillOnce(Return("yes"))
            .WillOnce(Return("y"))
            .WillOnce(Return("ID"))
            .WillOnce(Return("date"))

            .WillOnce(Return("complete"))
            .WillOnce(Return(""))
            .WillOnce(Return("2"))
            .WillOnce(Return("y"))

            .WillOnce(Return("show"))
            .WillOnce(Return("y"))
            .WillOnce(Return("priority"))

            .WillOnce(Return("delete"))
            .WillOnce(Return("ygj"))
            .WillOnce(Return("0"))
            .WillOnce(Return("y"))

            .WillOnce(Return("show"))
            .WillOnce(Return("y"))
            .WillOnce(Return(""))

            .WillOnce(Return("quit"));

    InSequence s;

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(12);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(5);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(15);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(15);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(4);
    EXPECT_CALL(*printer_, PrintString(
            "id: 1, title: fourth, priority: none, date: Jan 11 06:06, label: label  :\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString(
            "   id: 2, title: third, priority: medium, date: Dec 24 00:00, label: label\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString(
            "id: 0, title: first, priority: medium, date: Dec 23 12:00, label: label\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(4);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString(
            "id: 0, title: first, priority: medium, date: Dec 23 12:00, label: label\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString(
            "id: 1, title: fourth, priority: none, date: Jan 11 06:06, label: label\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(4);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString(
            "id: 1, title: fourth, priority: none, date: Jan 11 06:06, label: label\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString("Good luck!\n")).Times(1);

    controller_->Run();
}

TEST_F(MainTest, Scenario_3) {
    EXPECT_CALL(*reader_, ReadString())
            .WillOnce(Return("add"))
            .WillOnce(Return("first"))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return("n"))

            .WillOnce(Return("add"))
            .WillOnce(Return("zero"))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return("label_1"))
            .WillOnce(Return("y"))

            .WillOnce(Return("add_subtask"))
            .WillOnce(Return("0"))
            .WillOnce(Return("first"))
            .WillOnce(Return("high"))
            .WillOnce(Return("23:59 31/12"))
            .WillOnce(Return("label_1"))
            .WillOnce(Return("y"))

            .WillOnce(Return("add_subtask"))
            .WillOnce(Return("0"))
            .WillOnce(Return("second"))
            .WillOnce(Return("low"))
            .WillOnce(Return("0:0 1/1"))
            .WillOnce(Return("label_2"))
            .WillOnce(Return("y"))

            .WillOnce(Return("add_subtask"))
            .WillOnce(Return("0"))
            .WillOnce(Return("third"))
            .WillOnce(Return("medium"))
            .WillOnce(Return("6:6 6/6"))
            .WillOnce(Return("label_2"))
            .WillOnce(Return("y"))

            .WillOnce(Return("show_task"))
            .WillOnce(Return("0"))
            .WillOnce(Return(""))

            .WillOnce(Return("show_task"))
            .WillOnce(Return("0"))
            .WillOnce(Return("date"))

            .WillOnce(Return("show_task"))
            .WillOnce(Return("0"))
            .WillOnce(Return("priority"))

            .WillOnce(Return("show_task"))
            .WillOnce(Return("1"))
            .WillOnce(Return(""))

            .WillOnce(Return("show_label"))
            .WillOnce(Return("label_1"))
            .WillOnce(Return(""))

            .WillOnce(Return("show_label"))
            .WillOnce(Return("label_2"))
            .WillOnce(Return(""))

            .WillOnce(Return("show"))
            .WillOnce(Return("n"))
            .WillOnce(Return(""))

            .WillOnce(Return("quit"));

    const std::string zero{"id: 0, title: zero, priority: none, date: none, label: label_1"};
    const std::string first{"id: 1, title: first, priority: high, date: Dec 31 23:59, label: label_1"};
    const std::string second{"id: 2, title: second, priority: low, date: Jan  1 00:00, label: label_2"};
    const std::string third{"id: 3, title: third, priority: medium, date: Jun  6 06:06, label: label_2"};

    InSequence s;

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(5);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(5);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(6);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(6);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(6);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString(zero + "  :\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString("   " + first + "\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString("   " + second + "\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString("   " + third + "\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString(zero + "  :\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString("   " + second + "\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString("   " + third + "\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString("   " + first + "\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString(zero + "  :\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString("   " + first + "\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString("   " + third + "\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString("   " + second + "\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString(first + "\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString(zero + "\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString(first + "\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString(second + "\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString(third + "\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString(zero + "\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString("Good luck!\n")).Times(1);

    controller_->Run();
}

TEST_F(MainTest, Scenario_4) {
    EXPECT_CALL(*reader_, ReadString())
            .WillOnce(Return("add"))
            .WillOnce(Return("first"))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return("y"))

            .WillOnce(Return("add_subtask"))
            .WillOnce(Return("1"))
            .WillOnce(Return("second"))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return("y"))

            .WillOnce(Return("edit"))
            .WillOnce(Return("1"))
            .WillOnce(Return("second"))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return("y"))

            .WillOnce(Return("complete"))
            .WillOnce(Return("1"))
            .WillOnce(Return("y"))

            .WillOnce(Return("delete"))
            .WillOnce(Return("1"))
            .WillOnce(Return("y"))

            .WillOnce(Return("show_task"))
            .WillOnce(Return("1"))
            .WillOnce(Return(""))

            .WillOnce(Return("complete"))
            .WillOnce(Return("0"))
            .WillOnce(Return("y"))

            .WillOnce(Return("show"))
            .WillOnce(Return("y"))
            .WillOnce(Return(""))

            .WillOnce(Return("quit"));


    InSequence s;

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(5);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(6);
    EXPECT_CALL(*printer_, PrintString(_)).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(6);
    EXPECT_CALL(*printer_, PrintString(_)).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString(_)).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString(_)).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString(_)).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);
    EXPECT_CALL(*printer_, PrintString("There are no outstanding tasks now.\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString("Good luck!\n")).Times(1);

    controller_->Run();
}

TEST_F(MainTest, Scenario_5) {
    EXPECT_CALL(*reader_, ReadString())
            .WillOnce(Return("add"))
            .WillOnce(Return("first"))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return("y"))

            .WillOnce(Return("save"))
            .WillOnce(Return("first"))
            .WillOnce(Return("y"))

            .WillOnce(Return("add"))
            .WillOnce(Return("second"))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return(""))
            .WillOnce(Return("y"))

            .WillOnce(Return("show"))
            .WillOnce(Return("y"))
            .WillOnce(Return(""))

            .WillOnce(Return("save"))
            .WillOnce(Return("second"))
            .WillOnce(Return("y"))

            .WillOnce(Return("load"))
            .WillOnce(Return("first"))
            .WillOnce(Return("y"))

            .WillOnce(Return("show"))
            .WillOnce(Return("y"))
            .WillOnce(Return(""))

            .WillOnce(Return("load"))
            .WillOnce(Return("second"))
            .WillOnce(Return("y"))

            .WillOnce(Return("show"))
            .WillOnce(Return("y"))
            .WillOnce(Return(""))

            .WillOnce(Return("quit"));


    InSequence s;

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(5);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(5);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);

    EXPECT_CALL(*printer_, PrintString(
            "id: 0, title: first, priority: none, date: none\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString(
            "id: 1, title: second, priority: none, date: none\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);

    EXPECT_CALL(*printer_, PrintString(
            "id: 0, title: first, priority: none, date: none\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString(_)).Times(2);

    EXPECT_CALL(*printer_, PrintString(
            "id: 0, title: first, priority: none, date: none\n")).Times(1);
    EXPECT_CALL(*printer_, PrintString(
            "id: 1, title: second, priority: none, date: none\n")).Times(1);

    EXPECT_CALL(*printer_, PrintString("> ")).Times(1);
    EXPECT_CALL(*printer_, PrintString("Good luck!\n")).Times(1);

    controller_->Run();
}