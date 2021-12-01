#pragma once

#include<map>
#include<utility>
#include<memory>
#include<vector>
#include"Task.h"
#include"GeneralizedTask.h"
#include"id/IdGenerator.h"
#include"id/TaskId.h"

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

    TaskId Add(const Task &, TaskId = TaskId::NotExistentId());
    void Edit(TaskId, const Task &);
    void Complete(TaskId);
    void Delete(TaskId);
    void Label(TaskId, const std::string &);
public:
    using IdWithTask = std::pair<TaskId, Task>;
    using ArrayOfIdWithTask =std::vector<IdWithTask>;
public:
    ArrayOfIdWithTask ShowChild(TaskId = TaskId::NotExistentId(),
                                Sort = Sort::ID) const;
    std::vector<std::pair<IdWithTask, ArrayOfIdWithTask>> ShowAll(
            Sort = Sort::ID) const;
private:
    static bool ComparatorPriority( const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
    static bool ComparatorDate(const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
    static bool ComparatorId(const std::unique_ptr<IdWithTask> &, const std::unique_ptr<IdWithTask> &);
private:
    std::map<TaskId, GeneralizedTask> tasks_;
    std::unique_ptr<IdGenerator> generator_;
};