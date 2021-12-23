#include "ui/command/Command.h"

namespace ui::command {

    Result Quit::execute(const std::shared_ptr<Resources>&) {
        return Result(true);
    }

    Add::Add(const api::Task& task) : task_{task} {}

    Result Add::execute(const std::shared_ptr<Resources>& dependency) {
        dependency->manager->AddTask(task_);
        return Result(false);
    }

    AddSub::AddSub(const api::Task& task, api::TaskId parent)
            : task_{task}, parent_id_(parent) {}

    Result AddSub::execute(const std::shared_ptr<Resources>& dependency) {
        if (!dependency->manager->AddSubTask(task_, parent_id_))
            return Result("Incorrect parent ID (for example, subtask cannot have child)");
        else
            return Result(false);
    }

    Edit::Edit(api::TaskId id, const api::Task& task) : id_{id}, task_{task} {}

    Result Edit::execute(const std::shared_ptr<Resources>& dependency) {
        if (!dependency->manager->Edit(id_, task_))
            return Result("There are no task with such ID");
        else
            return Result(false);
    }

    Complete::Complete(api::TaskId id) : id_{id} {}

    Result Complete::execute(const std::shared_ptr<Resources>& dependency) {
        if (!dependency->manager->Complete(id_))
            return Result("There are no task with such ID");
        else
            return Result(false);
    }

    Delete::Delete(api::TaskId id) : id_{id} {}

    Result Delete::execute(const std::shared_ptr<Resources>& dependency) {
        if (!dependency->manager->Delete(id_))
            return Result("There are no task with such ID");
        else
            return Result(false);
    }

    Show::Show(bool if_print_subtasks, api::TasksSortBy sort_by)
            : if_print_subtasks_{if_print_subtasks}, sort_by_{sort_by} {}

    Result Show::execute(const std::shared_ptr<Resources>& dependency) {
        if (if_print_subtasks_)
            return Result(dependency->manager->ShowAll(sort_by_));
        else
            return Result(dependency->manager->ShowParents(sort_by_));
    }

    ShowTask::ShowTask(api::TaskId id, api::TasksSortBy sort_by)
            : id_{id}, sort_by_{sort_by} {}

    Result ShowTask::execute(const std::shared_ptr<Resources>& dependency) {
        if (auto result = dependency->manager->ShowTask(id_, sort_by_); result.has_value())
            return Result(result.value());
        else
            return Result("There are no task with such ID");
    }

    ShowLabel::ShowLabel(const std::string& label, api::TasksSortBy sort_by)
            : label_{label}, sort_by_{sort_by} {}

    Result ShowLabel::execute(const std::shared_ptr<Resources>& dependency) {
        return Result(dependency->manager->ShowLabel(label_, sort_by_));
    }

    Save::Save(const std::string& filename) : filename_{filename} {}

    Result Save::execute(const std::shared_ptr<Resources>& dependency) {
        api::ArrayFamilyTasks tasks{dependency->manager->Save()};

        if (!dependency->persister->Save(tasks, filename_))
            return Result("Cannot save to the specified file");
        else
            return Result(false);
    }

    Load::Load(const std::string& filename) : filename_{filename} {}

    Result Load::execute(const std::shared_ptr<Resources>& dependency) {
        std::optional<api::ArrayFamilyTasks> tasks{dependency->persister->Load(filename_)};
        if (!tasks.has_value())
            return Result("Cannot load for the specified file");

        dependency->manager->Load(tasks.value());
        return Result(false);
    }
}