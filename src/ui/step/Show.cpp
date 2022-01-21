#include "Show.h"
#include "ui/Factory.h"
#include "utilities/TasksSortBy.h"

namespace ui::step {

Show::Show(const std::shared_ptr<Factory>& factory, const std::shared_ptr<View>& view) :
        factory_{factory}, view_{view} {}

std::shared_ptr<Step> Show::execute(Context& context) {
    bool print_subtasks{view_->ReadIfPrintSubtasks(name())};
    model::TasksSortBy sort_by{view_->ReadSortBy(name())};

    context.set_command(std::make_shared<command::Show>(print_subtasks, sort_by));
    return factory_->GetInitialStep();
}

std::string Show::name() {return "[Show]";}

ShowTask::ShowTask(const std::shared_ptr<Factory>& factory, const std::shared_ptr<View>& view) :
        factory_{factory}, view_{view} {}

std::shared_ptr<Step> ShowTask::execute(Context& context) {
    model::TaskId id{view_->ReadId(name())};
    model::TasksSortBy sort_by{view_->ReadSortBy(name())};

    context.set_command(std::make_shared<command::ShowTask>(id, sort_by));
    return factory_->GetInitialStep();
}

std::string ShowTask::name() {return "[Show Task]";}

ShowByLabel::ShowByLabel(const std::shared_ptr<Factory>& factory, const std::shared_ptr<View>& view) :
        factory_{factory}, view_{view} {}

std::shared_ptr<Step> ShowByLabel::execute(Context& context) {
    std::string label{view_->ReadLabel(name())};
    model::TasksSortBy sort_by{view_->ReadSortBy(name())};

    context.set_command(std::make_shared<command::ShowByLabel>(label, sort_by));
    return factory_->GetInitialStep();
}

std::string ShowByLabel::name() {return "[Show by label]";}
}