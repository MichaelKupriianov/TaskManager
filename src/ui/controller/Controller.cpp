#include "Controller.h"

namespace ui {

bool Controller::AddTask(const model::Task& task) {
    return manager_->AddTask(task);
}

bool Controller::AddSubTask(const model::Task& task, model::TaskId id) {
    return manager_->AddSubTask(task, id);
}

bool Controller::Edit(model::TaskId id, const model::Task& task) {
    return manager_->Edit(id, task);
}

bool Controller::Complete(model::TaskId id) {
    return manager_->Complete(id);
}

bool Controller::Delete(model::TaskId id) {
    return manager_->Delete(id);
}

model::ManyTasksWithId Controller::ShowLabel(const std::string& label, model::TasksSortBy sort_by) const {
    return manager_->ShowLabel(label, sort_by);
}

model::ManyTasksWithId Controller::ShowParents(model::TasksSortBy sort_by) const {
    return manager_->ShowParents(sort_by);
}

std::optional<model::CompositeTask> Controller::ShowTask(model::TaskId id, model::TasksSortBy sort_by) const {
    return manager_->ShowTask(id, sort_by);
}

model::ManyCompositeTasks Controller::ShowAll(model::TasksSortBy sort_by) const {
    return manager_->ShowAll(sort_by);
}

bool Controller::Save(const std::string& filename) {
    model::ManyHierarchicalTasks tasks{manager_->GetAllTasks()};
    TaskPersister persister{filename};
    if (!persister.Save(tasks))
        return false;
    else
        return true;
}

bool Controller::Load(const std::string& filename) {
    TaskPersister persister{filename};
    std::optional<model::ManyHierarchicalTasks> tasks{persister.Load()};
    if (!tasks.has_value())
        return false;
    manager_->Overwrite(tasks.value());
    return true;
}
}