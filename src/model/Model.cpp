#include "Model.h"

namespace model {

bool Model::AddTask(const model::Task& task) {
    return manager_->AddTask(task);
}

bool Model::AddSubTask(const model::Task& task, model::TaskId id) {
    return manager_->AddSubTask(task, id);
}

bool Model::Edit(model::TaskId id, const model::Task& task) {
    return manager_->Edit(id, task);
}

bool Model::Complete(model::TaskId id) {
    return manager_->Complete(id);
}

bool Model::Delete(model::TaskId id) {
    return manager_->Delete(id);
}

model::ManyTasksWithId Model::ShowByLabel(const std::string& label, model::TasksSortBy sort_by) {
    return manager_->ShowByLabel(label, sort_by);
}

model::ManyTasksWithId Model::ShowParents(model::TasksSortBy sort_by) {
    return manager_->ShowParents(sort_by);
}

model::CompositeTask Model::ShowTask(model::TaskId id, model::TasksSortBy sort_by) {
    return manager_->ShowTask(id, sort_by);
}

model::ManyCompositeTasks Model::ShowAll(model::TasksSortBy sort_by) {
    return manager_->ShowAll(sort_by);
}

bool Model::Save(const std::string& filename) {
    std::vector<std::pair<model::TaskId, model::HierarchicalTask>> tasks{manager_->GetAllTasks()};
    TaskPersister persister{filename};
    if (!persister.Save(tasks))
        return false;
    else
        return true;
}

bool Model::Load(const std::string& filename) {
    TaskPersister persister{filename};
    std::optional<std::vector<std::pair<model::TaskId, model::HierarchicalTask>>> tasks{persister.Load()};
    if (!tasks.has_value())
        return false;
    manager_->Overwrite(tasks.value());
    return true;
}
}