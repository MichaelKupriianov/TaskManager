#pragma once

#include<memory>
#include"Task.h"
#include"TaskId.h"

class GeneralizedTask {
public:
    static GeneralizedTask Create(const Task &, std::optional<TaskId>);
public:
    std::optional<TaskId> parent() const { return parent_; }
    Task task() const { return task_; }
private:
    GeneralizedTask(const Task &task, std::optional<TaskId> id) : task_(task), parent_(id) {}
private:
    const Task task_;
    const std::optional<TaskId> parent_;
};

bool operator==(const GeneralizedTask &, const GeneralizedTask &);