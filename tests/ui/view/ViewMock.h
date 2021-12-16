#pragma once

#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"View.h"

class ViewMock : public View {
public:
    ViewMock(const std::shared_ptr<Reader> &reader, const std::shared_ptr<Printer> &printer)
            : View(reader, printer) {}

    MOCK_METHOD(void, Help, (), (override));
    MOCK_METHOD(void, Quit, (), (override));
    MOCK_METHOD(TypeOfStep, ReadCommand, (), (override));
    MOCK_METHOD(TaskId, ReadId, (TypeOfCommand), (override));
    MOCK_METHOD(TaskId, ReadParentId, (TypeOfCommand), (override));
    MOCK_METHOD(std::string, ReadTitle, (TypeOfCommand), (override));
    MOCK_METHOD(Task::Priority, ReadPriority, (TypeOfCommand), (override));
    MOCK_METHOD(google::protobuf::Timestamp, ReadDate, (TypeOfCommand), (override));
    MOCK_METHOD(std::string, ReadLabel, (TypeOfCommand), (override));
    MOCK_METHOD(bool, Confirm, (), (override));
    MOCK_METHOD(bool, ReadIfPrintSubtasks, (TypeOfCommand), (override));
    MOCK_METHOD(SortBy, ReadSortBy, (TypeOfCommand), (override));
    MOCK_METHOD(void, PrintException, (const std::string &), (override));
};