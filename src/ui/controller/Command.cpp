#include "Command.h"

CommandAdd::CommandAdd(const Task &task, TaskId parent_id, const std::shared_ptr<View> &view)
        : task_{task}, parent_id_{parent_id}, view_{view} {}

bool CommandAdd::execute(const std::shared_ptr<TaskManager> &manager) {
    if (!manager->Add(task_, parent_id_))
        view_->PrintException("Incorrect parent ID (for example, subtask cannot have child)");
    return true;
}

CommandEdit::CommandEdit(TaskId id, const Task &task, const std::shared_ptr<View> &view)
        : view_{view}, id_{id}, task_{task} {}

bool CommandEdit::execute(const std::shared_ptr<TaskManager> &manager) {
    if (!manager->Edit(id_, task_))
        view_->PrintException("There are no task with such ID");
    return true;
}

CommandComplete::CommandComplete(TaskId id, const std::shared_ptr<View> &view)
        : view_{view}, id_{id} {}

bool CommandComplete::execute(const std::shared_ptr<TaskManager> &manager) {
    if (!manager->Complete(id_))
        view_->PrintException("There are no task with such ID");
    return true;
}

CommandDelete::CommandDelete(TaskId id, const std::shared_ptr<View> &view)
        : view_{view}, id_{id} {}

bool CommandDelete::execute(const std::shared_ptr<TaskManager> &manager) {
    if (!manager->Delete(id_))
        view_->PrintException("There are no task with such ID");
    return true;
}

CommandShow::CommandShow(const std::shared_ptr<View> &view) : view_{view} {}

bool CommandShow::execute(const std::shared_ptr<TaskManager> &manager) {
    view_->PrintAllTasks(manager->ShowAll());
    return true;
}

bool CommandQuit::execute(const std::shared_ptr<TaskManager> &) {
    return false;
}