#include"gtest/gtest.h"
#include"Converter.h"

class ConverterTest : public ::testing::Test {
};

TEST_F(ConverterTest, shouldConvertStringToPriority) {
    EXPECT_EQ(Converter::StringToPriority("high"), Task::Priority::HIGH);
    EXPECT_EQ(Converter::StringToPriority("medium"), Task::Priority::MEDIUM);
    EXPECT_EQ(Converter::StringToPriority("lou"), Task::Priority::LOU);
    EXPECT_EQ(Converter::StringToPriority("none"), Task::Priority::NONE);
    EXPECT_EQ(Converter::StringToPriority("priority"), std::nullopt);
    EXPECT_EQ(Converter::StringToPriority(""), std::nullopt);
}

TEST_F(ConverterTest, shouldConvertStringToTime) {
    EXPECT_EQ(Converter::StringToTime("23:00 11/11/2021"), 1636664400);
    EXPECT_EQ(Converter::StringToTime("11:00 3/5/2022"), 1651568400);
    EXPECT_EQ(Converter::StringToTime("10:12 7/7/2025"), 1751875920);
    EXPECT_EQ(Converter::StringToTime("15:15 4/4/1990"), 639231300);
    EXPECT_EQ(Converter::StringToTime("25:00 3/5/1970"), std::nullopt);
    EXPECT_EQ(Converter::StringToTime("23:00 40/13/1979"), std::nullopt);
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