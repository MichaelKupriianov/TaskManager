#pragma once

#include "Task.pb.h"
#include "TaskStructures.pb.h"

namespace ui {
class Controller {
public:
    virtual ~Controller() = default;

    virtual bool AddTask(const Task& task) = 0;
    virtual bool AddSubTask(const Task& task, const TaskId& id) = 0;
    virtual bool Edit(const TaskId& id, const Task& task) = 0;
    virtual bool Complete(const TaskId& id) = 0;
    virtual bool Delete(const TaskId& id) = 0;

    virtual ManyTasksWithId ShowByLabel(const std::string& label, const TasksSortBy&) = 0;
    virtual ManyTasksWithId ShowParents(const TasksSortBy&) = 0;
    virtual CompositeTask ShowTask(const TaskId& id, const TasksSortBy&) = 0;
    virtual ManyCompositeTasks ShowAll(const TasksSortBy&) = 0;

    virtual bool Save(const std::string& filename) = 0;
    virtual bool Load(const std::string& filename) = 0;
};
}