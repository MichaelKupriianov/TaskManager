#pragma once

#include <mutex>
#include <shared_mutex>
#include "TaskManager.h"
#include "persistence/TaskPersister.h"

namespace model {
class Model {
public:
    explicit Model(const std::shared_ptr<model::TaskManager>& manager, const std::shared_ptr<std::shared_mutex>& mutex) :
            manager_{manager}, mutex_{mutex} {}
    virtual ~Model() = default;

    virtual bool AddTask(const Task& task);
    virtual bool AddSubTask(const Task& task, const TaskId& id);
    virtual bool Edit(const TaskId& id, const Task& task);
    virtual bool Complete(const TaskId& id);
    virtual bool Delete(const TaskId& id);

    virtual ManyTasksWithId ShowByLabel(const std::string& label, const TasksSortBy&);
    virtual ManyTasksWithId ShowParents(const TasksSortBy&);
    virtual CompositeTask ShowTask(const TaskId& id, const TasksSortBy&);
    virtual ManyCompositeTasks ShowAll(const TasksSortBy&);

    virtual bool Save(const std::string& filename);
    virtual bool Load(const std::string& filename);
private:
    const std::shared_ptr<TaskManager> manager_;
    const std::shared_ptr<std::shared_mutex> mutex_;
};
}

