#include "TaskManager.h"
#include <algorithm>

namespace model {
TaskManager::TaskManager(const std::shared_ptr<IdGenerator>& generator) :
        generator_{generator} {}

bool TaskManager::AddTask(const model::Task& task) {
    model::TaskId id{generator_->GenerateId()};
    if (tasks_.count(id))
        return false;
    tasks_.insert({id, model::CreateHierarchicalTask(task, std::nullopt)});
    return true;
}

bool TaskManager::AddSubTask(const model::Task& task, model::TaskId parent) {
    if (tasks_.count(parent) == 0 ||
        tasks_.at(parent).has_parent() ||
        tasks_.at(parent).task().status() == model::Task_Status_COMPLETED)
        return false;

    model::TaskId id{generator_->GenerateId()};
    tasks_.insert({id, model::CreateHierarchicalTask(task, parent)});
    return true;
}

bool TaskManager::Edit(model::TaskId id, const model::Task& task) {
    if (tasks_.count(id) == 0)
        return false;

    std::optional<model::TaskId> parent;
    if (tasks_.at(id).has_parent())
        parent = tasks_.at(id).parent();
    else
        parent = std::nullopt;

    tasks_.erase(id);
    tasks_.insert({id, model::CreateHierarchicalTask(task, parent)});
    return true;
}

bool TaskManager::Complete(model::TaskId id) {
    if (tasks_.count(id) == 0)
        return false;

    tasks_.at(id).mutable_task()->set_status(model::Task_Status_COMPLETED);
    for (const auto &[child_id, task]: tasks_)
        if (task.has_parent() && task.parent() == id)
            tasks_.at(id).mutable_task()->set_status(model::Task_Status_COMPLETED);

    return true;
}

bool TaskManager::Delete(model::TaskId id) {
    if (tasks_.count(id) == 0)
        return false;

    for (const auto &[child_id, task]: tasks_)
        if (task.has_parent() && task.parent() == id)
            tasks_.erase(child_id);
    tasks_.erase(id);

    return true;
}

model::ManyTasksWithId TaskManager::ShowByLabel(const std::string& label, TasksSortBy sort) const {
    std::vector<std::unique_ptr<model::TaskWithId>> for_sorting;
    for (const auto &[id, task]: tasks_) {
        auto begin = task.task().labels().begin();
        auto end = task.task().labels().end();
        if (std::count(begin, end, label) > 0 && task.task().status() != model::Task_Status_COMPLETED)
            for_sorting.emplace_back(std::make_unique<model::TaskWithId>(id, task.task()));
    }

    if (sort == TasksSortBy::ID)
        std::sort(for_sorting.begin(), for_sorting.end(), ComparatorId);
    if (sort == TasksSortBy::PRIORITY)
        std::sort(for_sorting.begin(), for_sorting.end(), ComparatorPriority);
    if (sort == TasksSortBy::DATE)
        std::sort(for_sorting.begin(), for_sorting.end(), ComparatorDate);

    model::ManyTasksWithId result;
    for (const auto& task: for_sorting)
        result.emplace_back(*task);
    return result;
}

model::ManyTasksWithId TaskManager::ShowParents(TasksSortBy sort) const {
    std::vector<std::unique_ptr<model::TaskWithId>> for_sorting;
    for (const auto &[id, task]: tasks_)
        if (!task.has_parent() && task.task().status() != model::Task_Status_COMPLETED)
            for_sorting.emplace_back(std::make_unique<model::TaskWithId>(id, task.task()));

    if (sort == TasksSortBy::ID)
        std::sort(for_sorting.begin(), for_sorting.end(), ComparatorId);
    if (sort == TasksSortBy::PRIORITY)
        std::sort(for_sorting.begin(), for_sorting.end(), ComparatorPriority);
    if (sort == TasksSortBy::DATE)
        std::sort(for_sorting.begin(), for_sorting.end(), ComparatorDate);

    model::ManyTasksWithId result;
    for (const auto& task: for_sorting)
        result.emplace_back(*task);
    return result;
}

std::optional<model::CompositeTask> TaskManager::ShowTask(model::TaskId parent, TasksSortBy sort) const {
    if (!tasks_.count(parent))
        return std::nullopt;

    std::vector<std::unique_ptr<model::TaskWithId>> for_sorting;
    for (const auto &[id, task]: tasks_)
        if (task.has_parent() && task.parent() == parent &&
            task.task().status() != model::Task_Status_COMPLETED)
            for_sorting.emplace_back(std::make_unique<model::TaskWithId>(id, task.task()));

    if (sort == TasksSortBy::ID)
        std::sort(for_sorting.begin(), for_sorting.end(), ComparatorId);
    if (sort == TasksSortBy::PRIORITY)
        std::sort(for_sorting.begin(), for_sorting.end(), ComparatorPriority);
    if (sort == TasksSortBy::DATE)
        std::sort(for_sorting.begin(), for_sorting.end(), ComparatorDate);

    model::CompositeTask result{{parent, tasks_.at(parent).task()},
                                {}};
    for (const auto& t: for_sorting)
        result.second.emplace_back(*t);
    return result;
}

model::ManyCompositeTasks TaskManager::ShowAll(TasksSortBy sort) const {
    std::vector<model::CompositeTask> result;
    model::ManyTasksWithId parents = ShowParents(sort);

    for (const auto& parent: parents)
        result.emplace_back(ShowTask(parent.first, sort).value());
    return result;
}

bool TaskManager::ComparatorId(const std::unique_ptr<model::TaskWithId>& first,
                               const std::unique_ptr<model::TaskWithId>& second) {
    if (first->first < second->first) return true;
    return false;
}

bool TaskManager::ComparatorPriority(const std::unique_ptr<model::TaskWithId>& first,
                                     const std::unique_ptr<model::TaskWithId>& second) {
    if (static_cast<int>(first->second.priority()) < static_cast<int>(second->second.priority())) return true;
    return false;
}

bool TaskManager::ComparatorDate(const std::unique_ptr<model::TaskWithId>& first,
                                 const std::unique_ptr<model::TaskWithId>& second) {
    if (first->second.date().seconds() < second->second.date().seconds()) return true;
    return false;
}

model::ManyHierarchicalTasks TaskManager::GetAllTasks() const {
    model::ManyHierarchicalTasks tasks;
    for (const auto& task: tasks_)
        tasks.push_back(task);
    return tasks;
}

void TaskManager::Overwrite(const model::ManyHierarchicalTasks& tasks) {
    tasks_.clear();
    for (const auto& task: tasks)
        tasks_.insert(task);

    int max_id;
    if (tasks_.empty()) max_id = 0;
    max_id = (*prev(tasks_.end())).first.value();
    generator_ = std::make_shared<IdGenerator>(max_id);
}
}