#include"TaskManager.h"
#include<algorithm>

bool TaskManager::AddTask(const Task &task) {
    TaskId id{generator_->GenerateId()};
    if (tasks_.count(id)) return false;
    tasks_.insert({id, GeneralizedTask::Create(task, std::nullopt)});
    return true;
}


bool TaskManager::AddSubTask(const Task &task, TaskId parent) {
    if (tasks_.count(parent) == 0) return false;
    if (tasks_.at(parent).parent()) return false;
    TaskId id{generator_->GenerateId()};
    tasks_.insert({id, GeneralizedTask::Create(task, parent)});
    return true;
}

bool TaskManager::Edit(TaskId id, const Task &task) {
    if (tasks_.count(id) == 0) return false;
    const std::optional<TaskId> parent{tasks_.at(id).parent()};
    tasks_.erase(id);
    tasks_.insert({id, GeneralizedTask::Create(task, parent)});
    return true;
}

bool TaskManager::Complete(TaskId id) {
    if (tasks_.count(id) == 0) return false;
    completed_tasks_.insert({id, tasks_.at(id)});
    tasks_.erase(id);
    for(const auto &[child_id, task] : tasks_)
        if (task.parent()==id) {
            completed_tasks_.insert({child_id, tasks_.at(child_id)});
            tasks_.erase(child_id);
        }
    return true;
}

bool TaskManager::Delete(TaskId id) {
    if (tasks_.count(id) == 0) return false;
    tasks_.erase(id);
    for(const auto &[child_id, task] : tasks_)
        if (task.parent()==id) {
            tasks_.erase(child_id);
        }
    return true;
}

TaskManager::ArrayTasks TaskManager::ShowLabel(const std::string &label, SortBy sort) const {
    std::vector<std::unique_ptr<IdWithTask>> for_sorting;
    for (const auto &[id, task]: tasks_)
        if (task.task()->label() == label)
            for_sorting.emplace_back(std::make_unique<IdWithTask>(id, *task.task()));

    if (sort == SortBy::ID) std::sort(for_sorting.begin(), for_sorting.end(), ComparatorId);
    if (sort == SortBy::PRIORITY) std::sort(for_sorting.begin(), for_sorting.end(), ComparatorPriority);
    if (sort == SortBy::DATE) std::sort(for_sorting.begin(), for_sorting.end(), ComparatorDate);

    ArrayTasks result;
    for (const auto &task: for_sorting)
        result.emplace_back(*task);
    return result;
}

TaskManager::ArrayTasks TaskManager::ShowParents(SortBy sort) const {
    std::vector<std::unique_ptr<IdWithTask>> for_sorting;
    for (const auto &[id, task]: tasks_)
        if (task.parent() == std::nullopt)
            for_sorting.emplace_back(std::make_unique<IdWithTask>(id, *task.task()));

    if (sort == SortBy::ID) std::sort(for_sorting.begin(), for_sorting.end(), ComparatorId);
    if (sort == SortBy::PRIORITY) std::sort(for_sorting.begin(), for_sorting.end(), ComparatorPriority);
    if (sort == SortBy::DATE) std::sort(for_sorting.begin(), for_sorting.end(), ComparatorDate);

    ArrayTasks result;
    for (const auto &task: for_sorting)
        result.emplace_back(*task);
    return result;
}

std::optional<TaskManager::TaskWithSubtasks> TaskManager::ShowTask(TaskId parent, SortBy sort) const {
    if (!tasks_.count(parent)) return std::nullopt;
    std::vector<std::unique_ptr<IdWithTask>> for_sorting;
    for (const auto &[id, task]: tasks_)
        if (task.parent() == parent)
            for_sorting.emplace_back(std::make_unique<IdWithTask>(id, *task.task()));

    if (sort == SortBy::ID) std::sort(for_sorting.begin(), for_sorting.end(), ComparatorId);
    if (sort == SortBy::PRIORITY) std::sort(for_sorting.begin(), for_sorting.end(), ComparatorPriority);
    if (sort == SortBy::DATE) std::sort(for_sorting.begin(), for_sorting.end(), ComparatorDate);

    TaskWithSubtasks result{{parent, *tasks_.at(parent).task()},
                            {}};
    for (const auto &t: for_sorting)
        result.second.emplace_back(*t);
    return result;
}

std::vector<TaskManager::TaskWithSubtasks> TaskManager::ShowAll(SortBy sort) const {
    std::vector<TaskWithSubtasks> result;
    ArrayTasks parents = ShowParents(sort);
    for (const auto &parent: parents) {
        result.emplace_back(ShowTask(parent.first, sort).value());
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
    if (first->second.date().seconds() < second->second.date().seconds()) return true;
    return false;
}