#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "persistence/TaskPersister.h"

class TaskPersisterMock : public TaskPersister {
public:
    TaskPersisterMock(const std::string& filename)
            : TaskPersister(filename) {}

    MOCK_METHOD(bool, Save, (const model::ManyHierarchicalTasks&), (override));
    MOCK_METHOD(std::optional<model::ManyHierarchicalTasks>, Load, (), (override));
};