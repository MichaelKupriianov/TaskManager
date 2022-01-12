#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "persistence/TaskPersister.h"

class TaskPersisterMock : public TaskPersister {
public:
    MOCK_METHOD(bool, Save, (const proto::ArrayHierarchicalTasks&, const std::string&), (override));
    MOCK_METHOD(std::optional<model::ManyHierarchicalTasks>, Load, (const std::string&), (override));
};