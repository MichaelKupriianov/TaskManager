#pragma once

#include<map>
#include<utility>
#include<memory>
#include<vector>
#include<optional>
#include"Task.h"
#include"GeneralizedTask.h"
#include"IdGenerator.h"
#include"TaskId.h"

class TaskManager {
public:
    enum class Sort {
        PRIORITY,
        DATE,
        ID
    };
public:
    TaskManager() : generator_(new IdGenerator) {}
    explicit TaskManager(std::unique_ptr<IdGenerator> gen) : generator_(std::move(gen)) {}
    ~TaskManager() = default;

    virtual bool AddTask(const Task &);
    virtual bool AddSubtask(const Task &, TaskId);
    virtual bool Edit(TaskId, const Task &);
    virtual bool Complete(TaskId);
    virtual bool Delete(TaskId);
    virtual bool Label(TaskId, const std::string &);
public:
    using IdWithTask = std::pair<TaskId, Task>;
    using ArrayOfIdWithTask = std::vector<IdWithTask>;
public:
    virtual ArrayOfIdWithTask ShowChild(std::optional<TaskId> = std::nullopt,
                                Sort = Sort::ID) const;
    virtual std::vector<std::pair<IdWithTask, ArrayOfIdWithTask>> ShowAll(
            Sort = Sort::ID) const;
private:
    static bool ComparatorPriority(const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
    static bool ComparatorDate(const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
    static bool ComparatorId(const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
private:
    std::map<TaskId, GeneralizedTask> tasks_;
    std::unique_ptr<IdGenerator> generator_;
};