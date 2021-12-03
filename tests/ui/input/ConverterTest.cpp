#include"gtest/gtest.h"
#include"Converter.h"

class ConverterTest : public ::testing::Test {
};

TEST_F(ConverterTest, shouldConvertStringToPriority) {
    EXPECT_EQ(Converter::StringToPriority("high"), Task::Priority::HIGH);
    EXPECT_EQ(Converter::StringToPriority("medium"), Task::Priority::MEDIUM);
    EXPECT_EQ(Converter::StringToPriority("lou"), Task::Priority::LOU);
    EXPECT_EQ(Converter::StringToPriority("none"), Task::Priority::NONE);
    EXPECT_EQ(Converter::StringToPriority(""), Task::Priority::NONE);
    EXPECT_EQ(Converter::StringToPriority("priority"), std::nullopt);
}

TEST_F(ConverterTest, shouldConvertStringToDate) {
    EXPECT_EQ(Converter::StringToDate(""), 0);
    EXPECT_EQ(Converter::StringToDate("23:00 11/11"), 61594808400);
    EXPECT_EQ(Converter::StringToDate("11:00 3/5"), 61578176400);
    EXPECT_EQ(Converter::StringToDate("10:12 7/7"), 61583789520);
    EXPECT_EQ(Converter::StringToDate("4/4"), 61575631200);
    EXPECT_EQ(Converter::StringToDate("5/11"), 61594207200);
    EXPECT_EQ(Converter::StringToDate("25:00 3/5"), std::nullopt);
    EXPECT_EQ(Converter::StringToDate("40/13"), std::nullopt);
}

TEST_F(ConverterTest, shouldConvertStringToStepType) {
    EXPECT_EQ(Converter::StringToStepType("quit"), TypeOfStep::QUIT);
    EXPECT_EQ(Converter::StringToStepType("help"), TypeOfStep::HELP);
    EXPECT_EQ(Converter::StringToStepType("add"), TypeOfStep::ADD);
    EXPECT_EQ(Converter::StringToStepType("edit"), TypeOfStep::EDIT);
    EXPECT_EQ(Converter::StringToStepType("complete"), TypeOfStep::COMPLETE);
    EXPECT_EQ(Converter::StringToStepType("delete"), TypeOfStep::DELETE);
    EXPECT_EQ(Converter::StringToStepType("label"), TypeOfStep::LABEL);
    EXPECT_EQ(Converter::StringToStepType("show"), TypeOfStep::SHOW);
    EXPECT_EQ(Converter::StringToStepType("title"), std::nullopt);
    EXPECT_EQ(Converter::StringToStepType("command"), std::nullopt);
    EXPECT_EQ(Converter::StringToStepType(""), std::nullopt);
}

TEST_F(ConverterTest, shouldConvertStringToId) {
    EXPECT_EQ(Converter::StringToId("523"), 523);
    EXPECT_EQ(Converter::StringToId("0"), 0);
    EXPECT_EQ(Converter::StringToId("1429"), 1429);
    EXPECT_EQ(Converter::StringToId("fyg21"), std::nullopt);
    EXPECT_EQ(Converter::StringToId("-65463"), std::nullopt);
    EXPECT_EQ(Converter::StringToId(""), std::nullopt);
}

TEST_F(ConverterTest, shouldConvertPriorityToString) {
    EXPECT_EQ(Converter::PriorityToString(Task::Priority::HIGH), "high");
    EXPECT_EQ(Converter::PriorityToString(Task::Priority::MEDIUM), "medium");
    EXPECT_EQ(Converter::PriorityToString(Task::Priority::LOU), "lou");
    EXPECT_EQ(Converter::PriorityToString(Task::Priority::NONE), "none");
}

TEST_F(ConverterTest, shouldConvertDateToString) {
    EXPECT_EQ(Converter::DateToString(0), "none");
    EXPECT_EQ(Converter::DateToString(61594808400), "Nov 11 23:00");
    EXPECT_EQ(Converter::DateToString(61578176400), "May  3 12:00");
    EXPECT_EQ(Converter::DateToString(61583789520), "Jul  7 11:12");
    EXPECT_EQ(Converter::DateToString(61575631200), "Apr  4 01:00");
    EXPECT_EQ(Converter::DateToString(61594207200), "Nov  5 00:00");
}

TEST_F(ConverterTest, shouldConvertTypeOfStepToString) {
    EXPECT_EQ(Converter::StepTypeToString(TypeOfStep::ADD), "Add");
    EXPECT_EQ(Converter::StepTypeToString(TypeOfStep::EDIT), "Edit");
    EXPECT_EQ(Converter::StepTypeToString(TypeOfStep::COMPLETE), "Complete");
    EXPECT_EQ(Converter::StepTypeToString(TypeOfStep::DELETE), "Delete");
    EXPECT_EQ(Converter::StepTypeToString(TypeOfStep::LABEL), "Label");
    EXPECT_EQ(Converter::StepTypeToString(TypeOfStep::ROOT), "");
    EXPECT_EQ(Converter::StepTypeToString(TypeOfStep::HELP), "");
    EXPECT_EQ(Converter::StepTypeToString(TypeOfStep::QUIT), "");
    EXPECT_EQ(Converter::StepTypeToString(TypeOfStep::SHOW), "");
}