#include "gtest/gtest.h"
#include "ui/view/Convert.h"
#include "utilities/CreateProtoObjects.h"

using namespace ui;

class ConvertTest : public ::testing::Test {
};

TEST_F(ConvertTest, shouldConvertStringToPriority) {
    EXPECT_EQ(convert::StringToPriority("high"), proto::Task_Priority_HIGH);
    EXPECT_EQ(convert::StringToPriority("medium"), proto::Task_Priority_MEDIUM);
    EXPECT_EQ(convert::StringToPriority("low"), proto::Task_Priority_LOW);
    EXPECT_EQ(convert::StringToPriority("none"), proto::Task_Priority_NONE);
    EXPECT_EQ(convert::StringToPriority(""), proto::Task_Priority_NONE);
    EXPECT_EQ(convert::StringToPriority("priority"), std::nullopt);
}

TEST_F(ConvertTest, shouldConvertStringToDate) {
    EXPECT_EQ(convert::StringToDate(""), 0);
    EXPECT_EQ(convert::StringToDate("23:00 11/11"), 61594808400);
    EXPECT_EQ(convert::StringToDate("11:00 3/5"), 61578172800);
    EXPECT_EQ(convert::StringToDate("10:12 7/7"), 61583785920);
    EXPECT_EQ(convert::StringToDate("4/4"), 61575627600);
    EXPECT_EQ(convert::StringToDate("5/11"), 61594207200);
    EXPECT_EQ(convert::StringToDate("25:00 3/5"), std::nullopt);
    EXPECT_EQ(convert::StringToDate("40/13"), std::nullopt);
}

TEST_F(ConvertTest, shouldConvertStringToStepType) {
    EXPECT_EQ(convert::StringToStepType("quit"), step::Type::QUIT);
    EXPECT_EQ(convert::StringToStepType("help"), step::Type::HELP);
    EXPECT_EQ(convert::StringToStepType("add"), step::Type::ADD);
    EXPECT_EQ(convert::StringToStepType("add_subtask"), step::Type::ADD_SUB);
    EXPECT_EQ(convert::StringToStepType("edit"), step::Type::EDIT);
    EXPECT_EQ(convert::StringToStepType("complete"), step::Type::COMPLETE);
    EXPECT_EQ(convert::StringToStepType("delete"), step::Type::DELETE);
    EXPECT_EQ(convert::StringToStepType("show"), step::Type::SHOW);
    EXPECT_EQ(convert::StringToStepType("show_task"), step::Type::SHOW_TASK);
    EXPECT_EQ(convert::StringToStepType("show_label"), step::Type::SHOW_LABEL);
    EXPECT_EQ(convert::StringToStepType("save"), step::Type::SAVE);
    EXPECT_EQ(convert::StringToStepType("load"), step::Type::LOAD);
    EXPECT_EQ(convert::StringToStepType("title"), std::nullopt);
    EXPECT_EQ(convert::StringToStepType("command"), std::nullopt);
    EXPECT_EQ(convert::StringToStepType(""), std::nullopt);
}

TEST_F(ConvertTest, shouldConvertStringToId) {
    EXPECT_EQ(convert::StringToId("523"), 523);
    EXPECT_EQ(convert::StringToId("0"), 0);
    EXPECT_EQ(convert::StringToId("1429"), 1429);
    EXPECT_EQ(convert::StringToId("fyg21"), std::nullopt);
    EXPECT_EQ(convert::StringToId("-65463"), std::nullopt);
    EXPECT_EQ(convert::StringToId(""), std::nullopt);
}

TEST_F(ConvertTest, shouldConvertStringToSortBy) {
    EXPECT_EQ(convert::StringToSortBy("id"), model::TasksSortBy::ID);
    EXPECT_EQ(convert::StringToSortBy("date"), model::TasksSortBy::DATE);
    EXPECT_EQ(convert::StringToSortBy("priority"), model::TasksSortBy::PRIORITY);
    EXPECT_EQ(convert::StringToSortBy(""), model::TasksSortBy::ID);
    EXPECT_EQ(convert::StringToSortBy("idd"), std::nullopt);
    EXPECT_EQ(convert::StringToSortBy("1"), std::nullopt);
}

TEST_F(ConvertTest, shouldConvertPriorityToString) {
    EXPECT_EQ(convert::PriorityToString(proto::Task_Priority_HIGH), "high");
    EXPECT_EQ(convert::PriorityToString(proto::Task_Priority_MEDIUM), "medium");
    EXPECT_EQ(convert::PriorityToString(proto::Task_Priority_LOW), "low");
    EXPECT_EQ(convert::PriorityToString(proto::Task_Priority_NONE), "none");
}

TEST_F(ConvertTest, shouldConvertDateToString) {
    google::protobuf::Timestamp date;
    date.set_seconds(0);
    EXPECT_EQ(convert::DateToString(date), "none");
    date.set_seconds(61594808400);
    EXPECT_EQ(convert::DateToString(date), "Nov 11 23:00");
    date.set_seconds(61578176400);
    EXPECT_EQ(convert::DateToString(date), "May  3 12:00");
    date.set_seconds(61583789520);
    EXPECT_EQ(convert::DateToString(date), "Jul  7 11:12");
    date.set_seconds(61575631200);
    EXPECT_EQ(convert::DateToString(date), "Apr  4 01:00");
    date.set_seconds(61594207200);
    EXPECT_EQ(convert::DateToString(date), "Nov  5 00:00");
}

TEST_F(ConvertTest, shouldConvertCommandToString) {
    EXPECT_EQ(convert::CommandToString(step::Type::ADD), "[Add Task]");
    EXPECT_EQ(convert::CommandToString(step::Type::ADD_SUB), "[Add SubTask]");
    EXPECT_EQ(convert::CommandToString(step::Type::EDIT), "[Edit Task]");
    EXPECT_EQ(convert::CommandToString(step::Type::COMPLETE), "[Complete Task]");
    EXPECT_EQ(convert::CommandToString(step::Type::DELETE), "[Delete Task]");
    EXPECT_EQ(convert::CommandToString(step::Type::SHOW), "[Show]");
    EXPECT_EQ(convert::CommandToString(step::Type::SHOW_TASK), "[Show Task]");
    EXPECT_EQ(convert::CommandToString(step::Type::SHOW_LABEL), "[Show by label]");
    EXPECT_EQ(convert::CommandToString(step::Type::SAVE), "[Save to file]");
    EXPECT_EQ(convert::CommandToString(step::Type::LOAD), "[Load from file]");
}

TEST_F(ConvertTest, shouldConvertTaskToString) {
    EXPECT_EQ(convert::TaskToString({proto::CreateTaskId(0), proto::CreateTask("first")}),
              "id: 0, title: first, priority: none, date: none");
    EXPECT_EQ(convert::TaskToString({proto::CreateTaskId(11),
                                     proto::CreateTask("second", proto::Task_Priority_LOW)}),
              "id: 11, title: second, priority: low, date: none");
    EXPECT_EQ(convert::TaskToString({proto::CreateTaskId(101),
                                     proto::CreateTask("third", proto::Task_Priority_MEDIUM, 61594808400)}),
              "id: 101, title: third, priority: medium, date: Nov 11 23:00");
}

TEST_F(ConvertTest, shouldConvertErrorToString) {
    EXPECT_EQ(convert::ErrorToString(command::Error::INCORRECT_PARENT_ID),
              "Incorrect parent ID (for example, subtask cannot have child)");
    EXPECT_EQ(convert::ErrorToString(command::Error::NO_TASK_WITH_SUCH_ID),
              "There are no task with such ID");
    EXPECT_EQ(convert::ErrorToString(command::Error::CANNOT_SAVE_TO_FILE),
              "Cannot save to the specified file");
    EXPECT_EQ(convert::ErrorToString(command::Error::CANNOT_LOAD_FROM_FILE),
              "Cannot load from the specified file");

}