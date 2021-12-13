#include "Command.h"

bool CommandQuit::execute(const std::shared_ptr<TaskManager> &) {
    return false;
}

CommandAdd::CommandAdd(const Task &task, const std::shared_ptr<View> &view)
        : task_{task}, view_{view} {}

bool CommandAdd::execute(const std::shared_ptr<TaskManager> &manager) {
    if (!manager->AddTask(task_))
        view_->PrintException("Incorrect parent ID (for example, subtask cannot have child)");
    return true;
}

CommandAddSub::CommandAddSub(const Task &task, TaskId parent, const std::shared_ptr<View> &view)
        : task_{task}, parent_id_(parent), view_{view} {}

bool CommandAddSub::execute(const std::shared_ptr<TaskManager> &manager) {
    if (!manager->AddSubtask(task_, parent_id_))
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

CommandShow::CommandShow(bool if_print_subtasks, SortBy sort_by,
                         const std::shared_ptr<View> &view)
        : if_print_subtasks_{if_print_subtasks}, sort_by_{sort_by}, view_{view} {}

bool CommandShow::execute(const std::shared_ptr<TaskManager> &manager) {
    if (if_print_subtasks_) view_->PrintAllTasks(manager->ShowAll(sort_by_));
    else view_->PrintArrayOfTasks(manager->ShowParents(sort_by_));
    return true;
}

CommandShowTask::CommandShowTask(TaskId id, SortBy sort_by, const std::shared_ptr<View> &view)
        : id_{id}, sort_by_{sort_by}, view_{view} {}

bool CommandShowTask::execute(const std::shared_ptr<TaskManager> &manager) {
    if (manager->ShowTask(id_, sort_by_).has_value())
        view_->PrintTaskWithSubtasks(manager->ShowTask(id_, sort_by_).value());
    else
        view_->PrintException("There are no task with such ID");
    return true;
}

CommandShowLabel::CommandShowLabel(const std::string &label, SortBy sort_by,
                                   const std::shared_ptr<View> &view)
        : label_{label}, sort_by_{sort_by}, view_{view} {}

bool CommandShowLabel::execute(const std::shared_ptr<TaskManager> &manager) {
    view_->PrintArrayOfTasks(manager->ShowLabel(label_, sort_by_));
    return true;
}