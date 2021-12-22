#pragma once

#include <map>
#include <utility>
#include <memory>
#include <vector>
#include <optional>
#include "Task.pb.h"
#include "IdGenerator.h"
#include "api/TasksSortBy.h"
#include "api/ComparisonProtoObjects.h"
#include "api/CreateProtoObjects.h"
#include "persistence/Persister.h"

class TaskManager {
public:
    explicit TaskManager(const std::shared_ptr<IdGenerator> &, const std::shared_ptr<Persister> &);
    virtual ~TaskManager() = default;

    virtual bool AddTask(const Task &);
    virtual bool AddSubTask(const Task &, TaskId);
    virtual bool Edit(TaskId, const Task &);
    virtual bool Complete(TaskId);
    virtual bool Delete(TaskId);
public:
    using IdWithTask = std::pair<TaskId, Task>;
    using ArrayTasks = std::vector<IdWithTask>;
    using TaskWithSubtasks = std::pair<IdWithTask, ArrayTasks>;
public:
    virtual ArrayTasks ShowLabel(const std::string &label, TasksSortBy) const;
    virtual ArrayTasks ShowParents(TasksSortBy) const;
    virtual std::optional<TaskWithSubtasks> ShowTask(TaskId, TasksSortBy) const;
    virtual std::vector<TaskWithSubtasks> ShowAll(TasksSortBy) const;

    virtual bool Save(const std::string &);
    virtual bool Load(const std::string &);
private:
    static bool ComparatorPriority(const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
    static bool ComparatorDate(const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
    static bool ComparatorId(const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
private:
    std::map<TaskId, FamilyTask> tasks_;
    std::shared_ptr<IdGenerator> generator_;
    std::shared_ptr<Persister> persister_;
};