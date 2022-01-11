#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ui/command/Command.h"

class CommandQuitMock : public ui::command::Quit {
public:
    MOCK_METHOD(ui::command::Result, execute, (const std::shared_ptr<ui::command::Resources>&), (override));
};

class CommandAddMock : public ui::command::Add {
public:
    CommandAddMock(const proto::Task &task) : ui::command::Add{task} {}
    MOCK_METHOD(ui::command::Result, execute, (const std::shared_ptr<ui::command::Resources>&), (override));
};

class CommandEditMock : public ui::command::Edit {
public:
    CommandEditMock(proto::TaskId id, const proto::Task &task) : ui::command::Edit{id, task} {}
    MOCK_METHOD(ui::command::Result, execute, (const std::shared_ptr<ui::command::Resources>&), (override));
};