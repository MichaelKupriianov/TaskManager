#pragma once

#include<string>
#include"Task.h"
#include"id/TaskId.h"

class GeneralizedTask {
public:
    static GeneralizedTask Create(const Task &, TaskId);
public:
    TaskId parent() const { return parent_; }
    Task task() const { return task_; }
private:
    GeneralizedTask(const Task &task, TaskId id) : task_(task), parent_(id) {}
private:
    const Task task_;
    const TaskId parent_;
};

bool operator==(const GeneralizedTask &, const GeneralizedTask &);