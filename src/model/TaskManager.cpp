#include "TaskManager.h"
#include<stdexcept>

TaskId TaskManager::Add(const Task &task) {
    TaskId id(generator_->GenerateId());
    if (tasks_.count(id) == 1) throw std::range_error("There is already a task with such ID");
    tasks_.insert({id, task});
    return id;
}

void TaskManager::Edit(TaskId id, const Task &task) {
    if (tasks_.count(id) == 0) throw std::range_error("There is no task with such ID");
    tasks_.erase(id);
    tasks_.insert({id, task});
}

void TaskManager::Complete(TaskId id) {
    if (tasks_.count(id) == 0) throw std::range_error("There is no task with such ID");
    tasks_.erase(id);
}

void TaskManager::Delete(TaskId id) {
    tasks_.erase(id);
}

std::map<TaskId, Task> TaskManager::Show() const {
    return tasks_;
}

Task TaskManager::getTask(TaskId id) const {
    if (tasks_.count(id) == 0) throw std::range_error("There is no task with such ID");
    return tasks_.at(id);
}