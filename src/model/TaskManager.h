#pragma once

#include<map>
#include <utility>
#include <memory>
#include"Task.h"
#include"GeneralizedTask.h"
#include"id/IdGenerator.h"
#include"id/TaskId.h"

class TaskManager {
public:
    TaskManager() : generator_(new IdGenerator) {}
    TaskManager(std::unique_ptr<IdGenerator> gen) : generator_(std::move(gen)) {}

    TaskId Add(const Task &, TaskId = TaskId::NotExistentId());
    void Edit(TaskId, const Task &);
    void Complete(TaskId);
    void Delete(TaskId);
    void Label(TaskId, const std::string &);

    std::map<TaskId, GeneralizedTask> Show() const;
    GeneralizedTask getTask(TaskId) const;
private:
    std::map<TaskId, GeneralizedTask> tasks_;
    std::unique_ptr<IdGenerator> generator_;
};
