#pragma once

#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"ui/view/View.h"

class ViewMock : public ui::View {
public:
    ViewMock(const std::shared_ptr<ui::Reader> &reader, const std::shared_ptr<ui::Printer> &printer)
            : View(reader, printer) {}

    MOCK_METHOD(void, PrintHelp, (), (override));
    MOCK_METHOD(void, PrintQuit, (), (override));
    MOCK_METHOD(ui::step::Type, ReadCommand, (), (override));
    MOCK_METHOD(proto::TaskId, ReadId, (ui::step::Type), (override));
    MOCK_METHOD(proto::TaskId, ReadParentId, (ui::step::Type), (override));
    MOCK_METHOD(std::string, ReadTitle, (ui::step::Type), (override));
    MOCK_METHOD(proto::Task::Priority, ReadPriority, (ui::step::Type), (override));
    MOCK_METHOD(google::protobuf::Timestamp, ReadDate, (ui::step::Type), (override));
    MOCK_METHOD(std::string, ReadLabel, (ui::step::Type), (override));
    MOCK_METHOD(bool, Confirm, (), (override));
    MOCK_METHOD(bool, ReadIfPrintSubtasks, (ui::step::Type), (override));
    MOCK_METHOD(model::TasksSortBy, ReadSortBy, (ui::step::Type), (override));

    MOCK_METHOD(void, PrintArraySimpleTasks, (const proto::ArraySimpleTasks&), (override));
    MOCK_METHOD(void, PrintCompositeTask, (const proto::CompositeTask&), (override));
    MOCK_METHOD(void, PrintArrayCompositeTasks, (const proto::ArrayCompositeTasks&), (override));
    MOCK_METHOD(void, PrintError, (ui::command::Error), (override));
};