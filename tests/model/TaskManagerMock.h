#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "model/TaskManager.h"

class TaskManagerMock : public model::TaskManager {
public:
    TaskManagerMock(const std::shared_ptr<model::IdGenerator>& generator)
            : TaskManager(generator) {}

    MOCK_METHOD(bool, AddTask, (const proto::Task&), (override));
    MOCK_METHOD(bool, AddSubTask, (const proto::Task&, proto::TaskId), (override));
    MOCK_METHOD(bool, Edit, (proto::TaskId, const proto::Task &), (override));
    MOCK_METHOD(bool, Complete, (proto::TaskId), (override));
    MOCK_METHOD(bool, Delete, (proto::TaskId), (override));
    MOCK_METHOD(proto::ArraySimpleTasks, ShowLabel, (const std::string &, model::TasksSortBy), (const, override));
    MOCK_METHOD(proto::ArraySimpleTasks, ShowParents, (model::TasksSortBy), (const, override));
    MOCK_METHOD(std::optional<proto::CompositeTask>, ShowTask, (proto::TaskId, model::TasksSortBy), (const, override));
    MOCK_METHOD(proto::ArrayCompositeTasks, ShowAll, (model::TasksSortBy), (const, override));
};