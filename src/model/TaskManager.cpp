#include "TaskManager.h"
#include "logging/Log.h"
#include "ui/view/Convert.h"

namespace model {
TaskManager::TaskManager(const std::shared_ptr<IdGenerator>& generator) :
        generator_{generator} {}

bool TaskManager::AddTask(const Task& task) {
    TaskId id{generator_->GenerateId()};
    if (tasks_.find(id) != tasks_.end()) {
        LOG(warning, "IdGenerator returns the id" + std::to_string(id.value()) + ", that is already in use.");
        return false;
    }
    tasks_.insert({id, CreateHierarchicalTask(task, std::nullopt)});
    LOG(info, "Task with {" + ui::convert::TaskToString(CreateTaskWithId(id, task)) + "} successfully added.");
    return true;
}

bool TaskManager::AddSubTask(const Task& task, const TaskId& parent) {
    if (tasks_.find(parent) == tasks_.end() || tasks_[parent].has_parent() ||
        tasks_[parent].task().status() == Task_Status_COMPLETED)
        return false;

    TaskId id{generator_->GenerateId()};
    tasks_.insert({id, CreateHierarchicalTask(task, parent)});
    return true;
}

bool TaskManager::Edit(const TaskId& id, const Task& task) {
    if (tasks_.find(id) == tasks_.end() || tasks_[id].task().status() == Task_Status_COMPLETED)
        return false;

    tasks_[id].set_allocated_task(new Task(task));
    return true;
}

bool TaskManager::Complete(const TaskId& id) {
    if (tasks_.find(id) == tasks_.end())
        return false;

    tasks_[id].mutable_task()->set_status(Task_Status_COMPLETED);
    for (const auto &[child_id, task]: tasks_)
        if (task.has_parent() && task.parent() == id)
            tasks_[child_id].mutable_task()->set_status(Task_Status_COMPLETED);

    return true;
}

bool TaskManager::Delete(const TaskId& id) {
    if (tasks_.find(id) == tasks_.end())
        return false;

    for (const auto &[child_id, task]: tasks_)
        if (task.has_parent() && task.parent() == id)
            tasks_.erase(child_id);
    tasks_.erase(id);

    return true;
}

ManyTasksWithId TaskManager::ShowByLabel(const std::string& label, const TasksSortBy& sort_by) const {
    ManyTasksWithId result;
    for (const auto &[id, task]: tasks_) {
        auto begin = task.task().labels().begin();
        auto end = task.task().labels().end();
        if (std::find(begin, end, label) != end && task.task().status() != Task_Status_COMPLETED) {
            result.mutable_tasks()->Add(CreateTaskWithId(id, task.task()));
        }
    }

    SortTasksWithId(result, sort_by);
    return result;
}

ManyTasksWithId TaskManager::ShowParents(const TasksSortBy& sort_by) const {
    ManyTasksWithId result;
    for (const auto &[id, task]: tasks_)
        if (!task.has_parent() && task.task().status() != Task_Status_COMPLETED)
            result.mutable_tasks()->Add(CreateTaskWithId(id, task.task()));

    SortTasksWithId(result, sort_by);
    return result;
}

CompositeTask TaskManager::ShowTask(const TaskId& parent, const TasksSortBy& sort_by) const {
    CompositeTask result;
    if (!tasks_.count(parent))
        return result;

    ManyTasksWithId child;
    for (const auto &[id, task]: tasks_)
        if (task.has_parent() && task.parent() == parent && task.task().status() != Task_Status_COMPLETED)
            child.mutable_tasks()->Add(CreateTaskWithId(id, task.task()));
    SortTasksWithId(child, sort_by);

    result.set_allocated_task(new TaskWithId(CreateTaskWithId(parent, tasks_.at(parent).task())));
    result.mutable_children()->Add(child.tasks().begin(), child.tasks().end());

    return result;
}

ManyCompositeTasks TaskManager::ShowAll(const TasksSortBy& sort) const {
    ManyCompositeTasks result;
    ManyTasksWithId parents = ShowParents(sort);

    for (const auto& parent: parents.tasks())
        result.mutable_tasks()->Add(ShowTask(parent.id(), sort));
    return result;
}

ManyHierarchicalTasks TaskManager::GetAllTasks() const {
    ManyHierarchicalTasks tasks;
    for (const auto& task: tasks_)
        tasks.push_back(task);
    return tasks;
}

void TaskManager::Overwrite(const ManyHierarchicalTasks& tasks) {
    tasks_.clear();
    for (const auto& task: tasks)
        tasks_.insert(task);

    int max_id = 0;
    if (!tasks_.empty())
        max_id = (*prev(tasks_.end())).first.value();

    generator_ = std::make_shared<IdGenerator>(max_id);
}
}