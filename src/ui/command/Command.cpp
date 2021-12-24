#include "ui/command/Command.h"

namespace ui::command {

    Result Quit::execute(const std::shared_ptr<Resources>&) {
        return Result(true);
    }

    Add::Add(const proto::Task& task) : task_{task} {}

    Result Add::execute(const std::shared_ptr<Resources>& resources) {
        resources->manager->AddTask(task_);
        return Result(false);
    }

    AddSub::AddSub(const proto::Task& task, proto::TaskId parent)
            : task_{task}, parent_id_(parent) {}

    Result AddSub::execute(const std::shared_ptr<Resources>& resources) {
        if (!resources->manager->AddSubTask(task_, parent_id_))
            return Result(Error::INCORRECT_PARENT_ID);
        else
            return Result(false);
    }

    Edit::Edit(proto::TaskId id, const proto::Task& task) : id_{id}, task_{task} {}

    Result Edit::execute(const std::shared_ptr<Resources>& resources) {
        if (!resources->manager->Edit(id_, task_))
            return Result(Error::NO_TASK_WITH_SUCH_ID);
        else
            return Result(false);
    }

    Complete::Complete(proto::TaskId id) : id_{id} {}

    Result Complete::execute(const std::shared_ptr<Resources>& resources) {
        if (!resources->manager->Complete(id_))
            return Result(Error::NO_TASK_WITH_SUCH_ID);
        else
            return Result(false);
    }

    Delete::Delete(proto::TaskId id) : id_{id} {}

    Result Delete::execute(const std::shared_ptr<Resources>& resources) {
        if (!resources->manager->Delete(id_))
            return Result(Error::NO_TASK_WITH_SUCH_ID);
        else
            return Result(false);
    }

    Show::Show(bool if_print_subtasks, model::TasksSortBy sort_by)
            : if_print_subtasks_{if_print_subtasks}, sort_by_{sort_by} {}

    Result Show::execute(const std::shared_ptr<Resources>& resources) {
        if (if_print_subtasks_)
            return Result(resources->manager->ShowAll(sort_by_));
        else
            return Result(resources->manager->ShowParents(sort_by_));
    }

    ShowTask::ShowTask(proto::TaskId id, model::TasksSortBy sort_by)
            : id_{id}, sort_by_{sort_by} {}

    Result ShowTask::execute(const std::shared_ptr<Resources>& resources) {
        if (auto result = resources->manager->ShowTask(id_, sort_by_); result.has_value())
            return Result(result.value());
        else
            return Result(Error::NO_TASK_WITH_SUCH_ID);
    }

    ShowLabel::ShowLabel(const std::string& label, model::TasksSortBy sort_by)
            : label_{label}, sort_by_{sort_by} {}

    Result ShowLabel::execute(const std::shared_ptr<Resources>& resources) {
        return Result(resources->manager->ShowLabel(label_, sort_by_));
    }

    Save::Save(const std::string& filename) : filename_{filename} {}

    Result Save::execute(const std::shared_ptr<Resources>& resources) {
        proto::ArrayHierarchicalTasks tasks{resources->manager->GetAllTasks()};

        if (!resources->persister->Save(tasks, filename_))
            return Result(Error::CANNOT_SAVE_TO_FILE);
        else
            return Result(false);
    }

    Load::Load(const std::string& filename) : filename_{filename} {}

    Result Load::execute(const std::shared_ptr<Resources>& resources) {
        std::optional<proto::ArrayHierarchicalTasks> tasks{resources->persister->Load(filename_)};
        if (!tasks.has_value())
            return Result(Error::CANNOT_LOAD_FROM_FILE);

        resources->manager->Rewrite(tasks.value());
        return Result(false);
    }
}