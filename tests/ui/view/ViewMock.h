#pragma once

#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"ui/view/View.h"

class ViewMock : public ui::View {
public:
    ViewMock(const std::shared_ptr<ui::Reader>& reader, const std::shared_ptr<ui::Printer>& printer)
            : View(reader, printer) {}

    MOCK_METHOD(void, PrintHelp, (), (override));
    MOCK_METHOD(void, PrintQuit, (), (override));
    MOCK_METHOD(ui::step::Type, ReadCommand, (), (override));
    MOCK_METHOD(model::TaskId, ReadId, (const std::string&), (override));
    MOCK_METHOD(model::TaskId, ReadParentId, (const std::string&), (override));
    MOCK_METHOD(std::string, ReadTitle, (const std::string&), (override));
    MOCK_METHOD(model::Task::Priority, ReadPriority, (const std::string&), (override));
    MOCK_METHOD(google::protobuf::Timestamp, ReadDate, (const std::string&), (override));
    MOCK_METHOD(std::string, ReadLabel, (const std::string&), (override));
    MOCK_METHOD(bool, Confirm, (), (override));
    MOCK_METHOD(bool, ReadIfPrintSubtasks, (const std::string&), (override));
    MOCK_METHOD(model::TasksSortBy, ReadSortBy, (const std::string&), (override));

    MOCK_METHOD(void, PrintArraySimpleTasks, (const model::ManyTasksWithId&), (override));
    MOCK_METHOD(void, PrintCompositeTask, (const model::CompositeTask&), (override));
    MOCK_METHOD(void, PrintArrayCompositeTasks, (const model::ManyCompositeTasks&), (override));
    MOCK_METHOD(void, PrintError, (ui::command::Error), (override));
};