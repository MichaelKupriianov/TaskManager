#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ui/controller/Controller.h"

class ControllerMock : public ui::Controller {
public:
    ControllerMock(const std::shared_ptr<model::TaskManager>& manager)
            : Controller(manager) {}

    MOCK_METHOD(bool, AddTask, (const model::Task&), (override));
    MOCK_METHOD(bool, AddSubTask, (const model::Task&, model::TaskId), (override));
    MOCK_METHOD(bool, Edit, (model::TaskId, const model::Task &), (override));
    MOCK_METHOD(bool, Complete, (model::TaskId), (override));
    MOCK_METHOD(bool, Delete, (model::TaskId), (override));
    MOCK_METHOD(model::ManyTasksWithId, ShowByLabel, (const std::string &, model::TasksSortBy), ( override));
    MOCK_METHOD(model::ManyTasksWithId, ShowParents, (model::TasksSortBy), (override));
    MOCK_METHOD(model::CompositeTask, ShowTask, (model::TaskId, model::TasksSortBy), (override));
    MOCK_METHOD(model::ManyCompositeTasks, ShowAll, (model::TasksSortBy), (override));
    MOCK_METHOD(bool, Save, (const std::string &), (override));
    MOCK_METHOD(bool, Load, (const std::string &), (override));
};