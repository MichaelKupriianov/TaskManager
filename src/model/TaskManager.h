#pragma once

#include<map>
#include<utility>
#include<memory>
#include<vector>
#include<optional>
#include"Task.pb.h"
#include"IdGenerator.h"
#include"SortBy.h"
#include"Comparison.h"
#include"Persister.h"

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
    virtual ArrayTasks ShowLabel(const std::string &label, SortBy) const;
    virtual ArrayTasks ShowParents(SortBy) const;
    virtual std::optional<TaskWithSubtasks> ShowTask(TaskId, SortBy) const;
    virtual std::vector<TaskWithSubtasks> ShowAll(SortBy) const;

    virtual bool Save(const std::string &);
    virtual bool Load(const std::string &);
private:
    static GeneralizedTask CreateGeneralizedTask(const Task &, std::optional<TaskId>);

    static bool ComparatorPriority(const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
    static bool ComparatorDate(const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
    static bool ComparatorId(const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
private:
    std::map<TaskId, GeneralizedTask> tasks_;
    std::shared_ptr<IdGenerator> generator_;
    std::shared_ptr<Persister> persister_;
};