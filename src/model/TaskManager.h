#pragma once

#include <map>
#include <utility>
#include <memory>
#include <vector>
#include <optional>
#include "Task.pb.h"
#include "IdGenerator.h"
#include "TasksSortBy.h"
#include "utilities/ComparisonProtoObjects.h"
#include "utilities/CreateProtoObjects.h"
#include "utilities/AliasesProtoObjects.h"
#include "persistence/TaskPersister.h"

namespace model {
class TaskManager {
public:
    explicit TaskManager(const std::shared_ptr<IdGenerator>& generator);
    virtual ~TaskManager() = default;

    virtual bool AddTask(const model::Task& task);
    virtual bool AddSubTask(const model::Task& task, model::TaskId id);
    virtual bool Edit(model::TaskId id, const model::Task& task);
    virtual bool Complete(model::TaskId id);
    virtual bool Delete(model::TaskId id);

    virtual model::ManyTasksWithId ShowByLabel(const std::string& label, TasksSortBy sort) const;
    virtual model::ManyTasksWithId ShowParents(TasksSortBy) const;
    virtual std::optional<model::CompositeTask> ShowTask(model::TaskId id, TasksSortBy) const;
    virtual model::ManyCompositeTasks ShowAll(TasksSortBy) const;

    virtual model::ManyHierarchicalTasks GetAllTasks() const;
    virtual void Overwrite(const model::ManyHierarchicalTasks&);
private:
    static bool ComparatorPriority(const std::unique_ptr<model::TaskWithId>&,
                                   const std::unique_ptr<model::TaskWithId>&);
    static bool ComparatorDate(const std::unique_ptr<model::TaskWithId>&,
                               const std::unique_ptr<model::TaskWithId>&);
    static bool ComparatorId(const std::unique_ptr<model::TaskWithId>&,
                             const std::unique_ptr<model::TaskWithId>&);
private:
    std::map<model::TaskId, model::HierarchicalTask> tasks_;
    std::shared_ptr<IdGenerator> generator_;
};
}