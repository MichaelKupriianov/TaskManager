#include "TaskManager.h"
#include<stdexcept>
#include<algorithm>

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
                                                              task.date(), label, task.condition()));
    TaskId parent = tasks_.at(id).parent();
    tasks_.erase(id);
    tasks_.insert({id, GeneralizedTask::Create(modified_task, parent)});
}

std::vector<std::pair<TaskId, Task>> TaskManager::ShowChild(TaskId parent, Sort sort) const {
    std::vector<std::pair<TaskId, Task>> result;
    for (const auto &[id, task]: tasks_)
        if (task.parent() == parent && task.task().condition() == Task::Condition::NONE)
            result.emplace_back(id, task.task());
    if (sort == Sort::ID) std::sort(result.begin(), result.end(), ComparatorId);
    if (sort == Sort::PRIORITY) std::sort(result.begin(), result.end(), ComparatorPriority);
    if (sort == Sort::DATE) std::sort(result.begin(), result.end(), ComparatorDate);
    return result;
}

std::vector<std::pair<std::pair<TaskId, Task>, std::vector<std::pair<TaskId, Task>>>> TaskManager::ShowAll(
        Sort sort) const {
    std::vector<std::pair<std::pair<TaskId, Task>, std::vector<std::pair<TaskId, Task>>>> result;
    std::vector<std::pair<TaskId, Task>> parents = ShowChild(TaskId::NotExistentId(), sort);
    for (const auto &parent: parents) {
        result.emplace_back(parent, ShowChild(parent.first, sort));
    }
    return result;
}

bool TaskManager::ComparatorId(const std::pair<TaskId, Task> &first, const std::pair<TaskId, Task> &second) {
    if (first.first > second.first) return true;
    return false;
}

bool TaskManager::ComparatorPriority(const std::pair<TaskId, Task> &first, const std::pair<TaskId, Task> &second) {
    if (static_cast<int>(first.second.priority()) > static_cast<int>(second.second.priority())) return true;
    return false;
}

bool TaskManager::ComparatorDate(const std::pair<TaskId, Task> &first, const std::pair<TaskId, Task> &second) {
    if (first.second.date() > second.second.date()) return true;
    return false;
}