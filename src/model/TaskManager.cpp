#include "TaskManager.h"
#include <algorithm>

namespace model {
    TaskManager::TaskManager(const std::shared_ptr<IdGenerator>& generator) :
            generator_{generator} {}

    bool TaskManager::AddTask(const api::Task& task) {
        api::TaskId id{generator_->GenerateId()};
        if (tasks_.count(id))
            return false;
        tasks_.insert({id, CreateFamilyTask(task, std::nullopt)});
        return true;
    }

    bool TaskManager::AddSubTask(const api::Task& task, api::TaskId parent) {
        if (tasks_.count(parent) == 0 ||
            tasks_.at(parent).has_parent() ||
            tasks_.at(parent).task().status() == api::Task_Status_COMPLETED)
            return false;

        api::TaskId id{generator_->GenerateId()};
        tasks_.insert({id, CreateFamilyTask(task, parent)});
        return true;
    }

    bool TaskManager::Edit(api::TaskId id, const api::Task& task) {
        if (tasks_.count(id) == 0)
            return false;

        std::optional<api::TaskId> parent;
        if (tasks_.at(id).has_parent())
            parent = tasks_.at(id).parent();
        else
            parent = std::nullopt;

        tasks_.erase(id);
        tasks_.insert({id, CreateFamilyTask(task, parent)});
        return true;
    }

    bool TaskManager::Complete(api::TaskId id) {
        if (tasks_.count(id) == 0)
            return false;

        tasks_.at(id).mutable_task()->set_status(api::Task_Status_COMPLETED);
        for (const auto &[child_id, task]: tasks_)
            if (task.has_parent() && task.parent() == id)
                tasks_.at(id).mutable_task()->set_status(api::Task_Status_COMPLETED);

        return true;
    }

    bool TaskManager::Delete(api::TaskId id) {
        if (tasks_.count(id) == 0)
            return false;

        for (const auto &[child_id, task]: tasks_)
            if (task.has_parent() && task.parent() == id)
                tasks_.erase(child_id);
        tasks_.erase(id);

        return true;
    }

    api::ArrayTasks TaskManager::ShowLabel(const std::string& label, api::TasksSortBy sort) const {
        std::vector<std::unique_ptr<api::IdWithTask>> for_sorting;
        for (const auto &[id, task]: tasks_)
            if (task.task().label() == label && task.task().status() != api::Task_Status_COMPLETED)
                for_sorting.emplace_back(std::make_unique<api::IdWithTask>(id, task.task()));

        if (sort == api::TasksSortBy::ID)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorId);
        if (sort == api::TasksSortBy::PRIORITY)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorPriority);
        if (sort == api::TasksSortBy::DATE)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorDate);

        api::ArrayTasks result;
        for (const auto& task: for_sorting)
            result.emplace_back(*task);
        return result;
    }

    api::ArrayTasks TaskManager::ShowParents(api::TasksSortBy sort) const {
        std::vector<std::unique_ptr<api::IdWithTask>> for_sorting;
        for (const auto &[id, task]: tasks_)
            if (!task.has_parent() && task.task().status() != api::Task_Status_COMPLETED)
                for_sorting.emplace_back(std::make_unique<api::IdWithTask>(id, task.task()));

        if (sort == api::TasksSortBy::ID)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorId);
        if (sort == api::TasksSortBy::PRIORITY)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorPriority);
        if (sort == api::TasksSortBy::DATE)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorDate);

        api::ArrayTasks result;
        for (const auto& task: for_sorting)
            result.emplace_back(*task);
        return result;
    }

    std::optional<api::TaskWithSubtasks> TaskManager::ShowTask(api::TaskId parent, api::TasksSortBy sort) const {
        if (!tasks_.count(parent))
            return std::nullopt;

        std::vector<std::unique_ptr<api::IdWithTask>> for_sorting;
        for (const auto &[id, task]: tasks_)
            if (task.has_parent() && task.parent() == parent &&
                task.task().status() != api::Task_Status_COMPLETED)
                for_sorting.emplace_back(std::make_unique<api::IdWithTask>(id, task.task()));

        if (sort == api::TasksSortBy::ID)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorId);
        if (sort == api::TasksSortBy::PRIORITY)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorPriority);
        if (sort == api::TasksSortBy::DATE)
            std::sort(for_sorting.begin(), for_sorting.end(), ComparatorDate);

        api::TaskWithSubtasks result{{parent, tasks_.at(parent).task()},
                                {}};
        for (const auto& t: for_sorting)
            result.second.emplace_back(*t);
        return result;
    }

    api::AllTasks TaskManager::ShowAll(api::TasksSortBy sort) const {
        std::vector<api::TaskWithSubtasks> result;
        api::ArrayTasks parents = ShowParents(sort);

        for (const auto& parent: parents)
            result.emplace_back(ShowTask(parent.first, sort).value());
        return result;
    }

    bool TaskManager::ComparatorId(const std::unique_ptr<api::IdWithTask>& first,
                                   const std::unique_ptr<api::IdWithTask>& second) {
        if (first->first < second->first) return true;
        return false;
    }

    bool TaskManager::ComparatorPriority(const std::unique_ptr<api::IdWithTask>& first,
                                         const std::unique_ptr<api::IdWithTask>& second) {
        if (static_cast<int>(first->second.priority()) < static_cast<int>(second->second.priority())) return true;
        return false;
    }

    bool TaskManager::ComparatorDate(const std::unique_ptr<api::IdWithTask>& first,
                                     const std::unique_ptr<api::IdWithTask>& second) {
        if (first->second.date().seconds() < second->second.date().seconds()) return true;
        return false;
    }

    bool TaskManager::Save(const std::string& filename) {
        Persister::Tasks tasks;
        for (const auto& task: tasks_)
            tasks.push_back(task);
        return persister_->Save(tasks, filename);
    }

    bool TaskManager::Load(const std::string& filename) {
        std::optional<Persister::Tasks> tasks{persister_->Load(filename)};
        if (!tasks.has_value())
            return false;

        tasks_.clear();
        for (const auto& task: tasks.value())
            tasks_.insert(task);

        int max_id;
        if (tasks_.empty()) max_id = 0;
        max_id = (*prev(tasks_.end())).first.value();
        generator_ = std::make_shared<IdGenerator>(max_id);
        return true;
    }
}