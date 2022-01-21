#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "model/TaskManager.h"

class TaskManagerMock : public model::TaskManager {
public:
    TaskManagerMock(const std::shared_ptr<model::IdGenerator>& generator)
            : TaskManager(generator) {}

    MOCK_METHOD(bool, AddTask, (const model::Task&), (override));
    MOCK_METHOD(bool, AddSubTask, (const model::Task&, const model::TaskId&), (override));
    MOCK_METHOD(bool, Edit, (const model::TaskId&, const model::Task &), (override));
    MOCK_METHOD(bool, Complete, (const model::TaskId&), (override));
    MOCK_METHOD(bool, Delete, (const model::TaskId&), (override));
    MOCK_METHOD(model::ManyTasksWithId, ShowByLabel, (const std::string&, const model::TasksSortBy&),
                (const, override));
    MOCK_METHOD(model::ManyTasksWithId, ShowParents, (const model::TasksSortBy&), (const, override));
    MOCK_METHOD(std::optional<model::CompositeTask>, ShowTask, (const model::TaskId&, const model::TasksSortBy&),
                (const, override));
    MOCK_METHOD(model::ManyCompositeTasks, ShowAll, (const model::TasksSortBy&), (const, override));
    MOCK_METHOD(model::ManyHierarchicalTasks, GetAllTasks, (), (const, override));
    MOCK_METHOD(void, Overwrite, (const model::ManyHierarchicalTasks&), (override));
};