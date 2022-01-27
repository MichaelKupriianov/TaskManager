#pragma once

#include "TaskManager.h"
#include "persistence/TaskPersister.h"

namespace model {
class Model {
public:
    explicit Model(const std::shared_ptr<model::TaskManager>& manager) :
            manager_{manager} {}
    virtual ~Model() = default;

    virtual bool AddTask(const model::Task& task);
    virtual bool AddSubTask(const model::Task& task, const model::TaskId& id);
    virtual bool Edit(const model::TaskId& id, const model::Task& task);
    virtual bool Complete(const model::TaskId& id);
    virtual bool Delete(const model::TaskId& id);

    virtual model::ManyTasksWithId ShowByLabel(const std::string& label, const model::TasksSortBy&);
    virtual model::ManyTasksWithId ShowParents(const model::TasksSortBy&);
    virtual model::CompositeTask ShowTask(const model::TaskId& id, const model::TasksSortBy&);
    virtual model::ManyCompositeTasks ShowAll(const model::TasksSortBy&);

    virtual bool Save(const std::string& filename);
    virtual bool Load(const std::string& filename);
private:
    const std::shared_ptr<TaskManager> manager_;
};
}
