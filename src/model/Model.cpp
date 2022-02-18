#include "Model.h"

namespace model {

bool Model::AddTask(const Task& task) {
    std::unique_lock lock(mutex_);
    return manager_->AddTask(task);
}

bool Model::AddSubTask(const Task& task, const TaskId& id) {
    std::unique_lock lock(mutex_);
    return manager_->AddSubTask(task, id);
}

bool Model::Edit(const TaskId& id, const Task& task) {
    std::unique_lock lock(mutex_);
    return manager_->Edit(id, task);
}

bool Model::Complete(const TaskId& id) {
    std::unique_lock lock(mutex_);
    return manager_->Complete(id);
}

bool Model::Delete(const TaskId& id) {
    std::unique_lock lock(mutex_);
    return manager_->Delete(id);
}

ManyTasksWithId Model::ShowByLabel(const std::string& label, const TasksSortBy& sort_by) {
    std::shared_lock lock(mutex_);
    return manager_->ShowByLabel(label, sort_by);
}

ManyTasksWithId Model::ShowParents(const TasksSortBy& sort_by) {
    std::shared_lock lock(mutex_);
    return manager_->ShowParents(sort_by);
}

CompositeTask Model::ShowTask(const TaskId& id, const TasksSortBy& sort_by) {
    std::shared_lock lock(mutex_);
    return manager_->ShowTask(id, sort_by);
}

ManyCompositeTasks Model::ShowAll(const TasksSortBy& sort_by) {
    std::shared_lock lock(mutex_);
    return manager_->ShowAll(sort_by);
}

bool Model::Save(const std::string& filename) {
    std::unique_lock lock(mutex_);
    std::vector<std::pair<TaskId, HierarchicalTask>> tasks{manager_->GetAllTasks()};
    TaskPersister persister{filename};
    if (!persister.Save(tasks))
        return false;
    else
        return true;
}

bool Model::Load(const std::string& filename) {
    std::unique_lock lock(mutex_);
    TaskPersister persister{filename};
    std::optional<std::vector<std::pair<TaskId, HierarchicalTask>>> tasks{persister.Load()};
    if (!tasks.has_value())
        return false;
    manager_->Overwrite(tasks.value());
    return true;
}
}