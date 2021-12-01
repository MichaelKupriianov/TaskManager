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

TaskManager::ArrayOfIdWithTask TaskManager::ShowChild(TaskId parent, Sort sort) const {
    std::vector<std::unique_ptr<IdWithTask>> for_sorting;
    for (const auto &[id, task]: tasks_)
        if (task.parent() == parent && task.task().condition() == Task::Condition::NONE)
            for_sorting.emplace_back(std::make_unique<IdWithTask>(id, task.task()));
    if (sort == Sort::ID) std::sort(for_sorting.begin(), for_sorting.end(), ComparatorId);
    if (sort == Sort::PRIORITY) std::sort(for_sorting.begin(), for_sorting.end(), ComparatorPriority);
    if (sort == Sort::DATE) std::sort(for_sorting.begin(), for_sorting.end(), ComparatorDate);
    ArrayOfIdWithTask result;
    for (const auto &t: for_sorting)
        result.emplace_back(*t);
    return result;
}

std::vector<std::pair<TaskManager::IdWithTask, TaskManager::ArrayOfIdWithTask>> TaskManager::ShowAll(
        Sort sort) const {
    std::vector<std::pair<IdWithTask, ArrayOfIdWithTask>> result;
    ArrayOfIdWithTask parents = ShowChild(TaskId::NotExistentId(), sort);
    for (const auto &parent: parents) {
        result.emplace_back(parent, ShowChild(parent.first, sort));
    }
    return result;
}

bool TaskManager::ComparatorId(const std::unique_ptr<IdWithTask> &first, const std::unique_ptr<IdWithTask> &second) {
    if (first->first < second->first) return true;
    return false;
}

bool
TaskManager::ComparatorPriority(const std::unique_ptr<IdWithTask> &first, const std::unique_ptr<IdWithTask> &second) {
    if (static_cast<int>(first->second.priority()) < static_cast<int>(second->second.priority())) return true;
    return false;
}

bool TaskManager::ComparatorDate(const std::unique_ptr<IdWithTask> &first, const std::unique_ptr<IdWithTask> &second) {
    if (first->second.date() < second->second.date()) return true;
    return false;
}