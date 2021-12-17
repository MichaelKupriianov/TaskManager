#pragma once

#include<map>
#include<utility>
#include<memory>
#include<vector>
#include<optional>
#include"Task.pb.h"
#include"TaskId.pb.h"
#include"GeneralizedTask.h"
#include"IdGenerator.h"
#include"SortBy.h"
#include"Comparison.h"

class TaskManager {
public:
    TaskManager() : generator_(new IdGenerator) {}
    explicit TaskManager(std::unique_ptr<IdGenerator> gen) : generator_(std::move(gen)) {}
    ~TaskManager() = default;

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
private:
    static bool ComparatorPriority(const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
    static bool ComparatorDate(const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
    static bool ComparatorId(const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
private:
    std::map<TaskId, GeneralizedTask> tasks_;
    std::map<TaskId, GeneralizedTask> completed_tasks_;
    std::unique_ptr<IdGenerator> generator_;
};