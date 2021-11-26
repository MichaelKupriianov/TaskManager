#include "TaskManager.h"
#include<stdexcept>

TaskId TaskManager::Add(const Task &task, TaskId parent) {
    TaskId id(generator_->GenerateId());
    if (tasks_.count(id) == 1) throw std::range_error("There is already a task with such ID");
    tasks_.insert({id, GeneralizedTask::Create(task, parent)});
    return id;
}

void TaskManager::Edit(TaskId id, const Task &task) {
    if (tasks_.count(id) == 0) throw std::range_error("There is no task with such ID");
    const TaskId parent = tasks_.at(id).parent();
    tasks_.erase(id);
    tasks_.insert({id, GeneralizedTask::Create(task, parent)});
}

void TaskManager::Complete(TaskId id) {
    if (tasks_.count(id) == 0) throw std::range_error("There is no task with such ID");
    Task task = tasks_.at(id).task();
    Task modified_task = Task::Create(Task::Arguments::Create(task.title(), task.priority(),
                                                              task.date(), task.label(), Task::Condition::COMPLETED));
    TaskId parent = tasks_.at(id).parent();
    tasks_.erase(id);
    tasks_.insert({id, GeneralizedTask::Create(modified_task, parent)});
}

void TaskManager::Delete(TaskId id) {
    tasks_.erase(id);
}

void TaskManager::Label(TaskId id, const std::string &label) {
    if (tasks_.count(id) == 0) throw std::range_error("There is no task with such ID");
    Task task = tasks_.at(id).task();
    Task modified_task = Task::Create(Task::Arguments::Create(task.title(), task.priority(),
                                                              task.date(), label, task.state()));
    TaskId parent = tasks_.at(id).parent();
    tasks_.erase(id);
    tasks_.insert({id, GeneralizedTask::Create(modified_task, parent)});
}

std::map<TaskId, GeneralizedTask> TaskManager::Show() const {
    return tasks_;
}

GeneralizedTask TaskManager::getTask(TaskId id) const {
    if (tasks_.count(id) == 0) throw std::range_error("There is no task with such ID");
    return tasks_.at(id);
}