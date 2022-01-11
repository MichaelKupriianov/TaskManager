#include "TaskManager.h"
#include <algorithm>

namespace model {
    TaskManager::TaskManager(const std::shared_ptr<IdGenerator>& generator) :
            generator_{generator} {}

    bool TaskManager::AddTask(const proto::Task& task) {
        proto::TaskId id{generator_->GenerateId()};
        if (tasks_.count(id))
            return false;
        tasks_.insert({id, proto::CreateHierarchicalTask(task, std::nullopt)});
        return true;
    }

    bool TaskManager::AddSubTask(const proto::Task& task, proto::TaskId parent) {
        if (tasks_.count(parent) == 0 ||
            tasks_.at(parent).has_parent() ||
            tasks_.at(parent).task().status() == proto::Task_Status_COMPLETED)
            return false;

        proto::TaskId id{generator_->GenerateId()};
        tasks_.insert({id, proto::CreateHierarchicalTask(task, parent)});
        return true;
    }

    bool TaskManager::Edit(proto::TaskId id, const proto::Task& task) {
        if (tasks_.count(id) == 0)
            return false;

        std::optional<proto::TaskId> parent;
        if (tasks_.at(id).has_parent())
            parent = tasks_.at(id).parent();
        else
            parent = std::nullopt;

        tasks_.erase(id);
        tasks_.insert({id, proto::CreateHierarchicalTask(task, parent)});
        return true;
    }

    bool TaskManager::Complete(proto::TaskId id) {
        if (tasks_.count(id) == 0)
            return false;

        tasks_.at(id).mutable_task()->set_status(proto::Task_Status_COMPLETED);
        for (const auto &[child_id, task]: tasks_)
            if (task.has_parent() && task.parent() == id)
                tasks_.at(id).mutable_task()->set_status(proto::Task_Status_COMPLETED);

        return true;
    }

    bool TaskManager::Delete(proto::TaskId id) {
        if (tasks_.count(id) == 0)
            return false;

        for (const auto &[child_id, task]: tasks_)
            if (task.has_parent() && task.parent() == id)
                tasks_.erase(child_id);
        tasks_.erase(id);

        return true;
    }

    proto::ArraySimpleTasks TaskManager::ShowLabel(const std::string& label, TasksSortBy sort) const {
        std::vector<std::unique_ptr<proto::SimpleTask>> for_sorting;
        for (const auto &[id, task]: tasks_)
            if (task.task().label() == label && task.task().status() != proto::Task_Status_COMPLETED)
                for_sorting.emplace_back(std::make_unique<proto::SimpleTask>(id, task.task()));

        if (sort == TasksSortBy::ID)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorId);
        if (sort == TasksSortBy::PRIORITY)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorPriority);
        if (sort == TasksSortBy::DATE)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorDate);

        proto::ArraySimpleTasks result;
        for (const auto& task: for_sorting)
            result.emplace_back(*task);
        return result;
    }

    proto::ArraySimpleTasks TaskManager::ShowParents(TasksSortBy sort) const {
        std::vector<std::unique_ptr<proto::SimpleTask>> for_sorting;
        for (const auto &[id, task]: tasks_)
            if (!task.has_parent() && task.task().status() != proto::Task_Status_COMPLETED)
                for_sorting.emplace_back(std::make_unique<proto::SimpleTask>(id, task.task()));

        if (sort == TasksSortBy::ID)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorId);
        if (sort == TasksSortBy::PRIORITY)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorPriority);
        if (sort == TasksSortBy::DATE)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorDate);

        proto::ArraySimpleTasks result;
        for (const auto& task: for_sorting)
            result.emplace_back(*task);
        return result;
    }

    std::optional<proto::CompositeTask> TaskManager::ShowTask(proto::TaskId parent, TasksSortBy sort) const {
        if (!tasks_.count(parent))
            return std::nullopt;

        std::vector<std::unique_ptr<proto::SimpleTask>> for_sorting;
        for (const auto &[id, task]: tasks_)
            if (task.has_parent() && task.parent() == parent &&
                task.task().status() != proto::Task_Status_COMPLETED)
                for_sorting.emplace_back(std::make_unique<proto::SimpleTask>(id, task.task()));

        if (sort == TasksSortBy::ID)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorId);
        if (sort == TasksSortBy::PRIORITY)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorPriority);
        if (sort == TasksSortBy::DATE)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorDate);

        proto::CompositeTask result{{parent, tasks_.at(parent).task()},
                                    {}};
        for (const auto& t: for_sorting)
            result.second.emplace_back(*t);
        return result;
    }

    proto::ArrayCompositeTasks TaskManager::ShowAll(TasksSortBy sort) const {
        std::vector<proto::CompositeTask> result;
        proto::ArraySimpleTasks parents = ShowParents(sort);

        for (const auto& parent: parents)
            result.emplace_back(ShowTask(parent.first, sort).value());
        return result;
    }

    bool TaskManager::ComparatorId(const std::unique_ptr<proto::SimpleTask>& first,
                                   const std::unique_ptr<proto::SimpleTask>& second) {
        if (first->first < second->first) return true;
        return false;
    }

    bool TaskManager::ComparatorPriority(const std::unique_ptr<proto::SimpleTask>& first,
                                         const std::unique_ptr<proto::SimpleTask>& second) {
        if (static_cast<int>(first->second.priority()) < static_cast<int>(second->second.priority())) return true;
        return false;
    }

    bool TaskManager::ComparatorDate(const std::unique_ptr<proto::SimpleTask>& first,
                                     const std::unique_ptr<proto::SimpleTask>& second) {
        if (first->second.date().seconds() < second->second.date().seconds()) return true;
        return false;
    }

    proto::ArrayHierarchicalTasks TaskManager::GetAllTasks() const {
        proto::ArrayHierarchicalTasks tasks;
        for (const auto& task: tasks_)
            tasks.push_back(task);
        return tasks;
    }

    void TaskManager::Rewrite(const proto::ArrayHierarchicalTasks& tasks) {
        tasks_.clear();
        for (const auto& task: tasks)
            tasks_.insert(task);

        int max_id;
        if (tasks_.empty()) max_id = 0;
        max_id = (*prev(tasks_.end())).first.value();
        generator_ = std::make_shared<IdGenerator>(max_id);
    }
}