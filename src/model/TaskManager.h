#pragma once

#include<map>
#include <utility>
#include <memory>
#include"Task.h"
#include"id/IdGenerator.h"
#include"id/TaskId.h"

class TaskManager {
public:
    TaskManager(): generator_(new IdGenerator) {}
    TaskManager(std::unique_ptr<IdGenerator> gen) : generator_(std::move(gen)) {}
public:
    TaskId Add(const Task &);
    void Edit(TaskId, const Task &);
    void Complete(TaskId);
    void Delete(TaskId);

    std::map<TaskId, Task> Show() const;
    Task getTask(TaskId) const;
private:
    std::map<TaskId, Task> tasks_;
    std::unique_ptr<IdGenerator> generator_;
};
