#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "model/TaskManager.h"

class TaskManagerMock : public model::TaskManager {
public:
    TaskManagerMock(const std::shared_ptr<model::IdGenerator>& generator)
            : TaskManager(generator) {}

    MOCK_METHOD(bool, AddTask, (const Task&), (override));
    MOCK_METHOD(bool, AddSubTask, (const Task&, const TaskId&), (override));
    MOCK_METHOD(bool, Edit, (const TaskId&, const Task &), (override));
    MOCK_METHOD(bool, Complete, (const TaskId&), (override));
    MOCK_METHOD(bool, Delete, (const TaskId&), (override));
    MOCK_METHOD(ManyTasksWithId, ShowByLabel, (const std::string&, const TasksSortBy&),
                (const, override));
    MOCK_METHOD(ManyTasksWithId, ShowParents, (const TasksSortBy&), (const, override));
    MOCK_METHOD(CompositeTask, ShowTask, (const TaskId&, const TasksSortBy&),
                (const, override));
    MOCK_METHOD(ManyCompositeTasks, ShowAll, (const TasksSortBy&), (const, override));
    MOCK_METHOD(model::ManyHierarchicalTasks, GetAllTasks, (), (const, override));
    MOCK_METHOD(void, Overwrite, (const model::ManyHierarchicalTasks&), (override));
};