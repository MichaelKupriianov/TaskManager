#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "model/TaskManager.h"

class TaskManagerMock : public model::TaskManager {
public:
    TaskManagerMock(const std::shared_ptr<model::IdGenerator>& generator)
            : TaskManager(generator) {}

    MOCK_METHOD(bool, AddTask, (const model::Task&), (override));
    MOCK_METHOD(bool, AddSubTask, (const model::Task&, model::TaskId), (override));
    MOCK_METHOD(bool, Edit, (model::TaskId, const model::Task &), (override));
    MOCK_METHOD(bool, Complete, (model::TaskId), (override));
    MOCK_METHOD(bool, Delete, (model::TaskId), (override));
    MOCK_METHOD(model::ManyTasksWithId, ShowLabel, (const std::string &, model::TasksSortBy), (const, override));
    MOCK_METHOD(model::ManyTasksWithId, ShowParents, (model::TasksSortBy), (const, override));
    MOCK_METHOD(std::optional<model::CompositeTask>, ShowTask, (model::TaskId, model::TasksSortBy), (const, override));
    MOCK_METHOD(model::ManyCompositeTasks, ShowAll, (model::TasksSortBy), (const, override));
    MOCK_METHOD(model::ManyHierarchicalTasks, GetAllTasks, (), (const, override));
    MOCK_METHOD(void, Overwrite, (const model::ManyHierarchicalTasks&), (override));
};