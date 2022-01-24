#pragma once

#include <map>
#include <memory>
#include <vector>
#include <optional>
#include "Task.pb.h"
#include "IdGenerator.h"
#include "utilities/AliasesProtoObjects.h"
#include "utilities/ComparisonProtoObjects.h"
#include "utilities/CreateProtoObjects.h"
#include "utilities/SortingProtoObjects.h"
#include "utilities/TasksSortBy.h"

namespace model {
class TaskManager {
public:
    explicit TaskManager(const std::shared_ptr<IdGenerator>& generator);
    virtual ~TaskManager() = default;

    virtual bool AddTask(const Task& task);
    virtual bool AddSubTask(const Task& task, const TaskId& id);
    virtual bool Edit(const TaskId& id, const Task& task);
    virtual bool Complete(const TaskId& id);
    virtual bool Delete(const TaskId& id);

    virtual ManyTasksWithId ShowByLabel(const std::string& label, const TasksSortBy&) const;
    virtual ManyTasksWithId ShowParents(const TasksSortBy&) const;
    virtual std::optional<CompositeTask> ShowTask(const TaskId& id, const TasksSortBy&) const;
    virtual ManyCompositeTasks ShowAll(const TasksSortBy&) const;

    virtual ManyHierarchicalTasks GetAllTasks() const;
    virtual void Overwrite(const ManyHierarchicalTasks&);
private:
    std::map<TaskId, HierarchicalTask> tasks_;
    std::shared_ptr<IdGenerator> generator_;
};
}