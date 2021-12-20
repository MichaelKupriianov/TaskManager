#pragma once

#include"gtest/gtest.h"
#include"gmock/gmock.h"
#include"TaskManager.h"

class TaskManagerMock : public TaskManager {
public:
    TaskManagerMock(const std::shared_ptr<IdGenerator> &generator, const std::shared_ptr<Persister> &persister)
            : TaskManager(generator, persister) {}

    MOCK_METHOD(bool, AddTask, (const Task &), (override));
    MOCK_METHOD(bool, AddSubTask, (const Task &, TaskId), (override));
    MOCK_METHOD(bool, Edit, (TaskId, const Task &), (override));
    MOCK_METHOD(bool, Complete, (TaskId), (override));
    MOCK_METHOD(bool, Delete, (TaskId), (override));
    MOCK_METHOD(ArrayTasks, ShowLabel, (const std::string &, SortBy), (const, override));
    MOCK_METHOD(ArrayTasks, ShowParents, (SortBy), (const, override));
    MOCK_METHOD(std::optional<TaskWithSubtasks>, ShowTask, (TaskId, SortBy), (const, override));
    MOCK_METHOD(std::vector<TaskWithSubtasks>, ShowAll, (SortBy), (const, override));
};