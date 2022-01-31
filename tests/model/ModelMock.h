#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "model/Model.h"

class ModelMock : public model::Model {
public:
    ModelMock(const std::shared_ptr<model::TaskManager>& manager)
            : model::Model(manager) {}

    MOCK_METHOD(bool, AddTask, (const model::Task&), (override));
    MOCK_METHOD(bool, AddSubTask, (const model::Task&, const model::TaskId&), (override));
    MOCK_METHOD(bool, Edit, (const model::TaskId&, const model::Task &), (override));
    MOCK_METHOD(bool, Complete, (const model::TaskId&), (override));
    MOCK_METHOD(bool, Delete, (const model::TaskId&), (override));
    MOCK_METHOD(model::ManyTasksWithId, ShowByLabel, (const std::string&, const model::TasksSortBy&), (override));
    MOCK_METHOD(model::ManyTasksWithId, ShowParents, (const model::TasksSortBy&), (override));
    MOCK_METHOD(model::CompositeTask, ShowTask, (const model::TaskId&, const model::TasksSortBy&), (override));
    MOCK_METHOD(model::ManyCompositeTasks, ShowAll, (const model::TasksSortBy&), (override));
    MOCK_METHOD(bool, Save, (const std::string&), (override));
    MOCK_METHOD(bool, Load, (const std::string&), (override));
};