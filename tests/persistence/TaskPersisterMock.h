#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "persistence/TaskPersister.h"

class TaskPersisterMock : public TaskPersister {
public:
    explicit TaskPersisterMock(const std::string& filename) : TaskPersister(filename) {}

    MOCK_METHOD(bool, Save, (const ManyHierarchicalTasks&), (override));
    MOCK_METHOD(std::optional<ManyHierarchicalTasks>, Load, (), (override));
};