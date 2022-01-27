#pragma once

#include "model/TaskManager.h"
#include "persistence/TaskPersister.h"

namespace ui {
class Controller {
public:
    virtual ~Controller() = default;

    virtual bool AddTask(const model::Task& task) = 0;
    virtual bool AddSubTask(const model::Task& task, const model::TaskId& id) = 0;
    virtual bool Edit(const model::TaskId& id, const model::Task& task) = 0;
    virtual bool Complete(const model::TaskId& id) = 0;
    virtual bool Delete(const model::TaskId& id) = 0;

    virtual model::ManyTasksWithId ShowByLabel(const std::string& label, const model::TasksSortBy&) = 0;
    virtual model::ManyTasksWithId ShowParents(const model::TasksSortBy&) = 0;
    virtual model::CompositeTask ShowTask(const model::TaskId& id, const model::TasksSortBy&) = 0;
    virtual model::ManyCompositeTasks ShowAll(const model::TasksSortBy&) = 0;

    virtual bool Save(const std::string& filename) = 0;
    virtual bool Load(const std::string& filename) = 0;
};
}