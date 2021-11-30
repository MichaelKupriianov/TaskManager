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
    TaskManager(std::unique_ptr<IdGenerator> gen) : generator_(std::move(gen)) {}

    TaskId Add(const Task &, TaskId = TaskId::NotExistentId());
    void Edit(TaskId, const Task &);
    void Complete(TaskId);
    void Delete(TaskId);
    void Label(TaskId, const std::string &);

    std::vector<std::pair<TaskId, Task>> ShowChild(TaskId = TaskId::NotExistentId(),
                                                   Sort = Sort::ID) const;
    std::vector<std::pair<std::pair<TaskId, Task>, std::vector<std::pair<TaskId, Task>>>> ShowAll(
                                                   Sort = Sort::ID) const;
private:
    static bool ComparatorPriority(const std::pair<TaskId, Task> &, const std::pair<TaskId, Task> &);
    static bool ComparatorDate(const std::pair<TaskId, Task> &, const std::pair<TaskId, Task> &);
    static bool ComparatorId(const std::pair<TaskId, Task> &, const std::pair<TaskId, Task> &);
private:
    std::map<TaskId, GeneralizedTask> tasks_;
    std::unique_ptr<IdGenerator> generator_;
};