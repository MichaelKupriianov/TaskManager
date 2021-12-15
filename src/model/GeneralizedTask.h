#pragma once

#include<memory>
#include"Task.pb.h"
#include"TaskId.pb.h"
#include"Comparison.h"

class GeneralizedTask {
public:
    static GeneralizedTask Create(const Task &, std::optional<TaskId>);
public:
    std::optional<TaskId> parent() const { return parent_; }
    std::shared_ptr<Task> task() const { return task_; }
private:
    GeneralizedTask(const Task &task, std::optional<TaskId> id) : task_(new Task(task)), parent_(id) {}
private:
    std::shared_ptr<Task> task_;
    std::optional<TaskId> parent_;
};

bool operator==(const GeneralizedTask &, const GeneralizedTask &);