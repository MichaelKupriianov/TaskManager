#include "Show.h"
#include "Resources.h"
#include "model/TasksSortBy.h"

namespace ui::step {

    Show::Show() : type_{step::Type::SHOW} {}

    std::shared_ptr<Step> Show::execute(Context& context, const std::shared_ptr<Resources>& resources) {
        bool print_subtasks{resources->view->ReadIfPrintSubtasks(type_)};
        model::TasksSortBy sort_by{resources->view->ReadSortBy(type_)};

        context.set_command(std::make_shared<command::Show>(print_subtasks, sort_by));
        return resources->factory->GetInitialStep();
    }

    ShowTask::ShowTask() : type_{step::Type::SHOW_TASK} {}

    std::shared_ptr<Step> ShowTask::execute(Context& context, const std::shared_ptr<Resources>& resources) {
        proto::TaskId id{resources->view->ReadId(type_)};
        model::TasksSortBy sort_by{resources->view->ReadSortBy(type_)};

        context.set_command(std::make_shared<command::ShowTask>(id, sort_by));
        return resources->factory->GetInitialStep();
    }

    ShowLabel::ShowLabel() : type_{step::Type::SHOW_LABEL} {}

    std::shared_ptr<Step> ShowLabel::execute(Context& context, const std::shared_ptr<Resources>& resources) {
        std::string label{resources->view->ReadLabel(type_)};
        model::TasksSortBy sort_by{resources->view->ReadSortBy(type_)};

        context.set_command(std::make_shared<command::ShowLabel>(label, sort_by));
        return resources->factory->GetInitialStep();
    }
}