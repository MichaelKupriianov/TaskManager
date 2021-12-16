#pragma once

#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"Command.h"

class CommandQuitMock : public CommandQuit {
public:
    MOCK_METHOD(bool, execute, (const std::shared_ptr<TaskManager> &), (override));
};

class CommandAddMock : public CommandAdd {
public:
    CommandAddMock(const Task &task, const std::shared_ptr<View> &view)
            : CommandAdd{task, view} {}
    MOCK_METHOD(bool, execute, (const std::shared_ptr<TaskManager> &), (override));
};

class CommandEditMock : public CommandEdit {
public:
    CommandEditMock(TaskId id, const Task &task, const std::shared_ptr<View> &view)
            : CommandEdit{id, task, view} {}
    MOCK_METHOD(bool, execute, (const std::shared_ptr<TaskManager> &), (override));
};